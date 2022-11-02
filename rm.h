#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define true 1
#define false 0

#define Max_Task_Count 10

typedef struct Task Task;

struct Task
{
    int id, period, wsct;
};

// Debug
void Debug_PrintAll(Task *tasks, int count);
// Sort
void Sort_Tasks(Task *tasks, int count);
void SwapTask(Task *main, int a, int b);
// Utilization Test
void Utilization_Check(Task *tasks, int count);
double Utilization_Tasks(Task *tasks, int count);
double Utilization_UpperBound(int count);
// Exact Test
void Exact_Test_Check(Task *tasks, int count);
int Exact_Test_Detect(Task *tasks, int count);

//------
/* #Debug */
// 印出所有資訊
void Debug_PrintAll(Task *tasks, int count)
{
    int i = 0;
    printf("#DEBUG PrintAll#\n");
    for (i = 0; i < count; i++)
    {
        printf("%d %d:%d:%d\n", i, tasks[i].id, tasks[i].period, tasks[i].wsct);
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
/* #Utilization test */
void Utilization_Check(Task *tasks, int count)
{
    double utilization = 0, upperbound = 0;
    utilization = Utilization_Tasks(*(&tasks), count);
    upperbound = Utilization_UpperBound(count);
    if (utilization > upperbound)
    {
        printf("RMS:U=%.4lf>%.4lf\n", utilization, upperbound);
    }
    else if (utilization <= upperbound)
    {
        printf("RMS:U=%.4lf<=%.4lf\n", utilization, upperbound);
    }
}
double Utilization_Tasks(Task *tasks, int count)
{
    int i;
    double utilization = 0;
    for (i = 0; i < count; i++)
    {
        utilization += (double)tasks[i].wsct / (double)tasks[i].period;
    }
    return utilization;
}
double Utilization_UpperBound(int count)
{
    double upperbound = (double)count * (pow(2, (1 / (double)count)) - 1);
    return upperbound;
    // U(n) = n( 2^[1/2] - 1)
}
/* #Exact Test */
void Exact_Test_Check(Task *tasks, int count)
{
    if (Exact_Test_Detect(*(&tasks), count))
        printf("exact test sucess\n");
    else
        printf("exact test fail\n");
}
int Exact_Test_Detect(Task *tasks, int count)
{
    int i, j, k;
    double rj = 0;
    for (i = 0; i < count; i++) // T1 T2 T3
    {
        // printf("------------\n");
        // printf("#T%d start\n", i + 1);
        for (j = 0; j <= i; j++) // r0 r1 r2
        {
            double total = 0;
            for (k = 0; k <= i; k++) // r0 Cj r1 Cj
            {
                if (j == 0)
                {
                    total += tasks[k].wsct;
                }
                else
                {
                    total += (double)tasks[k].wsct * (ceil((rj / (double)tasks[k].period)));
                }
            }
            if (total > tasks[i].period) // total > Period #exact test Fail
            {
                // printf("* r%d , total=%lf > %d\n", j, total, tasks[i].period);
                // printf("fail\n");
                return false;
            }
            else
            {
                // printf("* r%d , total=%lf <= %d\n", j, total, tasks[i].period);
                rj = total;
            }
            // printf("@@ rj = %lf\n", total);
        }
    }
    // printf("True\n");
    return true;
}