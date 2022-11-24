#include <stdio.h>
#include "EDF.h"

int main(int argc, char *argv[])
{
    Task tasks[Max_Task_Count];

    int count = 0;
    // input取值
    while (scanf("%d:%d:%d", &tasks[count].id, &tasks[count].period, &tasks[count].wset) != EOF)
    {
        if (tasks[count].id == 0)
        {
            tasks[count].period = -1;
            tasks[count].wset = -1;
            break;
        }
        count += 1;
        if (count == Max_Task_Count + 1)
            break;
    }
    // Sort_Tasks(tasks, count);
    Schedulability_main(tasks, count);
    // Utilization_Check(tasks, count);
    // Exact_Test_Check(tasks, count);
    Schedule_Check(tasks, count, LCM_Tasks(tasks, count));
}
