#include "include.h"
#include <avr/wdt.h>    //看门狗头文件
void setup()             //  只执行一次
{ 
   pinMode(DIR0,OUTPUT); 
   pinMode(DIR1,OUTPUT); 
   TCCR1B=((1<<CS10));   // 配置定时器1和2的时钟分频系数
   TCCR2B=((1<<CS20));
   Serial.begin(9600);   //  使能串口0 并设波特率为9600
   wdt_enable(WDTO_1S);  //
   InitPS2();            //  初始化PS2控制器
   analogWrite(M0, 0);   //   设置四个电机的初始状态为停止
   analogWrite(M1, 0);
   digitalWrite(DIR0,0);
   digitalWrite(DIR1,0);
}
void loop()             // 循环执行
{
   TaskRun();          // 功能函数
   wdt_reset();        //  喂狗操作
}

