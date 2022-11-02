#include <stdio.h>
#include "rm.h"

int main(int argc, char *argv[])
{
    Task tasks[Max_Task_Count];
    int count = 0;
    // input取值
    while (scanf("%d:%d:%d", &tasks[count].id, &tasks[count].period, &tasks[count].wsct) != EOF)
    {
        if (tasks[count].id == 0)
        {
            tasks[count].period = -1;
            tasks[count].wsct = -1;
            count -= 1;
            break;
        }
        printf("%d:%d:%d\n", tasks[count].id, tasks[count].period, tasks[count].wsct);
        count += 1;
        // printf("count = %d\n", count);
        if (count == Max_Task_Count + 1)
            break;
    }
    Debug_PrintAll(tasks, count);
    Sort_Tasks(tasks, count);
    Debug_PrintAll(tasks, count);
}
