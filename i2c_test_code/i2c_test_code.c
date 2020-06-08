#include "project.h"
#include "i2c_test.h"

#define TASKSTACKSIZE   512

Void task_init(UArg arg0, UArg arg1);
Void task_i2c(UArg arg0, UArg arg1);

Int resource = 0;
Int finishCount = 0;
UInt32 sleepTickCount;

Task_Struct task1Struct, task2Struct;
Char task1Stack[TASKSTACKSIZE], task2Stack[TASKSTACKSIZE];

Semaphore_Struct init_semStruct;
Semaphore_Handle init_semHandle;

/*Semaphore_Struct i2c_semStruct;
Semaphore_Handle i2c_semHandle;*/

uint8_t rxBuffer[8];

Int main()
{
    Task_Params taskParams;
    Semaphore_Params semParams;

    Task_Params_init(&taskParams);
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task1Stack;
    taskParams.priority = 1;
    Task_construct(&task1Struct, (Task_FuncPtr)task_init, &taskParams, NULL);

    taskParams.stack = &task2Stack;
    taskParams.priority = 2;
    Task_construct(&task2Struct, (Task_FuncPtr)task_i2c, &taskParams, NULL);

    Semaphore_Params_init(&semParams);
    Semaphore_construct(&init_semStruct, 0, &semParams);

    /*Semaphore_Params_init(&semParams);
    Semaphore_construct(&i2c_semStruct, 2, &semParams);*/

    init_semHandle = Semaphore_handle(&init_semStruct);
    /*i2c_semHandle = Semaphore_handle(&i2c_semStruct);*/

    sleepTickCount = 10000 / Clock_tickPeriod;

    BIOS_start();
    return(0);
}

Void task_init(UArg arg0, UArg arg1)
{
        Board_initGeneral();
        Board_initGPIO();
        Board_initI2C();
        i2c_kurulum();

        Semaphore_post(init_semHandle);
        Task_sleep(sleepTickCount);
}

Void task_i2c(UArg arg0, UArg arg1)
{
    Semaphore_pend(init_semHandle, BIOS_WAIT_FOREVER);
    for (;;)
    {
        i2c_oku(0x68, 0x01, rxBuffer, 8);
    }
}
