#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Max_Task_Count 10

typedef struct Task Task;

struct Task
{
    int id, period, wsct;
};

void Debug_PrintAll(Task *tasks, int count);
void Sort_Tasks(Task *tasks, int count);
void SwapTask(Task main[], int a, int b);
//------
// 印出所有資訊
void Debug_PrintAll(Task *tasks, int count)
{
    int i = 0;
    for (i = 0; i < count; i++)
    {
        printf("%d %d:%d:%d\n", i, tasks[i].id, tasks[i].period, tasks[i].wsct);
    }
    printf("count = %d\n", count);
}
// 交換兩個值
void SwapTask(Task main[], int a, int b)
{
    Task temp;
    temp.id = main[a].id;
    temp.period = main[a].period;
    temp.wsct = main[a].wsct;
    //
    main[a].id = main[b].id;
    main[a].period = main[b].period;
    main[a].wsct = main[b].wsct;
    //
    main[b].id = temp.id;
    main[b].period = temp.period;
    main[b].wsct = temp.wsct;
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

int RMS_check(Task *tasks, int count)
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < i; j++)
        {
        }
    }
}