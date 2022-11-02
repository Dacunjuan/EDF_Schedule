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

// Debug
void Debug_PrintAll(Task *tasks, int count);
// Sort
void Sort_Tasks(Task *tasks, int count);
void SwapTask(Task *main, int a, int b);
// Utilization test
void Utilization_Check(Task *tasks, int count);
double Utilization_Tasks(Task *tasks, int count);
double Utilization_UpperBound(int count);
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