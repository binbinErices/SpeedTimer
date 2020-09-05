/*
 * test.cc
 * brief: 测试耗时统计工具
 * Created on: 2020-9-5
 *      Author: erices
 */
#include <iostream>

#include "SpendTimer.h"

uint64_t Fibonacci(uint32_t i)
{
    if (1 == i)
    {
        return 1;
    }
    else if(2 == i)
    {
        return 2;
    }

    return Fibonacci(i-1) + Fibonacci(i-2);
}

int main()
{
    SPEND_TIMG_CONTROL(true);
    {
        SPEND_TIME_MSG(1, "Fibonacci(20) spend time ");
        Fibonacci(20);
    }

    {
        SPEND_TIME_MSG(2, "Fibonacci(30) spend time ");
        Fibonacci(30);
    }

    {
        SPEND_TIME_MSG(3, "Fibonacci(40) spend time ");
        Fibonacci(40);
    }
    
    return 0;
}