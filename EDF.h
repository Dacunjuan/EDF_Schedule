#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define true 1
#define false 0

#define Max_Task_Count 10

typedef struct Task Task;
typedef struct Task_Schedule Task_Schedule;
typedef struct Str Str;

struct Task
{
    int id, period, wset;
};

struct Task_Schedule
{
    int execution_time;
    char status;
    struct Str *codeword;
    struct Task *task;
};

struct Str
{
    int len, size;
    char *s;
    char radix;
};
// Str
int max(int a, int b);
Str *StrNew();
void StrAppend(Str *str, char *s);
// Debug
void Debug_PrintAll(Task *tasks, int count);
// Sort
void Sort_Tasks(Task *tasks, int count);
void SwapTask(Task *main, int a, int b);
// Schedule
void Schedule_Check(Task *tasks, int count, int LCM);
void Schedule_init(Task_Schedule *tasks_schedule, Task *tasks, int count);
void Schedule_print(Task_Schedule *tasks_schedule, int count);
int Schedule_schedule(Task_Schedule *tasks_schedule, int count, int LCM);
void Schedule_printChart(Task_Schedule *tasks_schedule, int count);
// Schedulability
void Schedulability_main(Task *tasks, int count);

//------
/* #Str */
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
Str *StrNew()
{
    Str *str = (Str *)malloc(sizeof(Str));
    str->s = (char *)malloc(1);
    str->s[0] = '\0';
    str->len = 0;
    str->size = 1;
    return str;
}

void StrAppend(Str *str, char *s)
{
    int newLen = str->len + strlen(s);
    if (newLen + 1 > str->size)
    {
        int newSize = max(str->size * 2, newLen + 1);
        char *t = (char *)malloc(newSize);
        sprintf(t, "%s%s", str->s, s);
        free(str->s);
        str->s = t;
        str->len = newLen;
        str->size = newSize;
    }
    else
    {
        strcat(&str->s[str->len], s);
        str->len += strlen(s);
    }
}
/* #Debug */
// 印出所有資訊
void Debug_PrintAll(Task *tasks, int count)
{
    int i = 0;
    printf("#DEBUG PrintAll#\n");
    for (i = 0; i < count; i++)
    {
        printf("%d %d:%d:%d\n", i, tasks[i].id, tasks[i].period, tasks[i].wset);
    }
    printf("#END#\n");
}
/* #Sort */
// 交換兩個值
void SwapTask(Task *main, int a, int b)
{
    Task temp;
    temp.id = main[a].id;
    temp.period = main[a].period;
    temp.wset = main[a].wset;
    //
    main[a].id = main[b].id;
    main[a].period = main[b].period;
    main[a].wset = main[b].wset;
    //
    main[b].id = temp.id;
    main[b].period = temp.period;
    main[b].wset = temp.wset;
}
// 選擇排序法
void Sort_Tasks(Task *tasks, int count)
{
    int i, j, min;
    for (i = 0; i < count; i++)
    {
        min = i;
        for (j = i + 1; j < count; j++)
        {
            if (tasks[j].period < tasks[min].period)
            {
                min = j;
            }
        }
        SwapTask(tasks, i, min);
    }
}
/* Schedule */
void Schedule_Check(Task *tasks, int count, int LCM)
{
    Task_Schedule tasks_schedule[count];
    Schedule_init(tasks_schedule, tasks, count);
    // Schedule_print(tasks_schedule, count);
    Schedule_schedule(tasks_schedule, count, LCM);
    // Schedule_print(tasks_schedule, count);
    Schedule_printChart(tasks_schedule, count);
}
void Schedule_init(Task_Schedule *tasks_schedule, Task *tasks, int count)
{
    int i = 0;
    for (i = 0; i < count; i++)
    {
        tasks_schedule[i].task = &tasks[i];
        tasks_schedule[i].codeword = StrNew();
        // StrAppend(tasks_schedule[i].codeword, "");
        tasks_schedule[i].execution_time = 0;
        tasks_schedule[i].status = 'I';
    }
}
void Schedule_print(Task_Schedule *tasks_schedule, int count)
{
    int i = 0;
    for (i = 0; i < count; i++)
    {
        Str *str_temp = tasks_schedule[i].codeword;
        printf("%d status:%c execTime:%d String:%s\t", i, tasks_schedule[i].status, tasks_schedule[i].execution_time, str_temp->s);
        Task *temp = tasks_schedule[i].task;
        printf("%d:%d:%d\n", temp->id, temp->period, temp->wset);
    }
}

void Schedule_MissDeadLine(Task_Schedule task_schedule)
{
    StrAppend(task_schedule.codeword, "X");
    task_schedule.status = 'X';
}

void Schedule_Idle(Task_Schedule task_schedule)
{
    StrAppend(task_schedule.codeword, "I");
    task_schedule.status = 'I';
}

void Schedule_Exec(Task_Schedule task_schedule)
{
    StrAppend(task_schedule.codeword, "E");
    task_schedule.status = 'E';
}

int Schedule_DeadDetect(Task_Schedule *tasks_schedule, int count, int time)
{
    int i;
    if (time == 0)
    {
        return 1;
    }
    for (i = 0; i < count; i++) // Task
    {
        Task *task_temp = tasks_schedule[i].task;
        if (time % task_temp->period == 0) // Task Arrive
        {
            // 當新的週期已到達，已執行時間沒有等於WSCT 代表發生 Miss Deadline
            if (tasks_schedule[i].execution_time != task_temp->wset) // Miss Deadline
            {
                Schedule_MissDeadLine(tasks_schedule[i]);
                printf("%d:X:%d\n", time, task_temp->id);
                return 0;
            }
            else
            {
                tasks_schedule[i].execution_time = 0;
                tasks_schedule[i].status = 'I';
            }
        }
    }
    return 1;
}

int Schedule_ExecDetect(Task_Schedule *tasks_schedule, int count, int time)
{
    int i, execFlag = 0, deadline_close = -1, deadline_index = -1;
    for (i = 0; i < count; i++) // Task
    {
        Task *task_temp = tasks_schedule[i].task;
        int deadline_temp = task_temp->period * ((time / task_temp->period) + 1) - time; // if time=16,wset=15 -> 15*((16/15)+1) - time -> 15*2-16 =14
        if (tasks_schedule[i].execution_time >= task_temp->wset)
        {
            continue;
        }
        else if (deadline_close == -1)
        {
            deadline_close = deadline_temp;
            deadline_index = i;
        }
        else if (deadline_close > deadline_temp && tasks_schedule[i].execution_time < task_temp->wset)
        {
            deadline_close = deadline_temp;
            deadline_index = i;
        }
    }
    Task *task_temp = tasks_schedule[deadline_index].task;
    if (deadline_index != -1 && tasks_schedule[deadline_index].execution_time < task_temp->wset)
    {
        Schedule_Exec(tasks_schedule[deadline_index]);
        tasks_schedule[deadline_index].execution_time += 1;
        tasks_schedule[deadline_index].status = 'E';
        printf("%d:E:%d\n ", time, task_temp->id);
        execFlag = 1;
    }
    else
    {
        // Schedule_Idle(tasks_schedule[deadline_index]);
    }
    for (i = 0; i < count; i++) // not exec task
    {
        if (i == deadline_index)
        {
            continue;
        }
        else
        {
            Schedule_Idle(tasks_schedule[i]);
        }
    }
    if (execFlag == 1)
    {
        return 1;
    }
    return 0;
}

void Schedule_IdleDetect(Task_Schedule *tasks_schedule, int count, int time)
{
    int i;
    for (i = 0; i < count; i++) // Task
    {
        Task *task_temp = tasks_schedule[i].task;
        if (tasks_schedule[i].status != 'E')
        {
            Schedule_Idle(tasks_schedule[i]);
        }
    }
    printf("%d:I\n", time);
}

int Schedule_schedule(Task_Schedule *tasks_schedule, int count, int LCM)
{
    int time;

    for (time = 0; time < LCM; time++) // Time
    {
        if (Schedule_DeadDetect(*(&tasks_schedule), count, time) == false)
        {
            return false;
        }
        if (Schedule_ExecDetect(*(&tasks_schedule), count, time) == false)
        {
            Schedule_IdleDetect(*(&tasks_schedule), count, time);
        }
        // Schedule_IdleDetect(*(&tasks_schedule), count, time);
    }
    return 0;
}

void Schedule_printChart(Task_Schedule *tasks_schedule, int count)
{
    int i = 0, j = 0;
    for (i = 0; i < count; i++)
    {
        Str *str_temp = tasks_schedule[i].codeword;
        Task *temp = tasks_schedule[i].task;
        printf("T%d\t", temp->id);
        for (j = 0; j < str_temp->len; j++)
        {
            switch (str_temp->s[j])
            {
            case 'E':
                printf("#");
                break;
            case 'I':
                printf("-");
                break;
            case 'X':
                printf("X");
                break;
            }
        }
        printf("\n");
    }
}

/* Math */
int LCM_Tasks(Task *tasks, int count)
{
    int i = 0, LCM = 2, LCM_count = 0;
    while (1)
    {
        LCM_count = 0;
        for (i = 0; i < count; i++)
        {
            if (LCM % tasks[i].period != 0)
            {
                break;
            }
            LCM_count += 1;
        }
        if (LCM_count == count)
        {
            return LCM;
        }
        else
        {
            LCM += 1;
        }
    }
    return false;
}
// Schedulability_test
void Schedulability_main(Task *tasks, int count)
{
    int i;
    double utilization = 0;
    for (i = 0; i < count; i++)
    {
        utilization += (double)tasks[i].wset / (double)tasks[i].period;
    }
    if (utilization > 1.0)
    {
        printf("EDF:U=%lf > 1\n", utilization);
        printf("Schedulability test fail\n");
    }
    else
    {
        printf("EDF:U=%lf <= 1\n", utilization);
        printf("Schedulability test pass\n");
    }
}