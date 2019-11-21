#include "include.h"
#include <avr/wdt.h>    //���Ź�ͷ�ļ�
void setup()             //  ִֻ��һ��
{ 
   pinMode(DIR0,OUTPUT); 
   pinMode(DIR1,OUTPUT); 
   TCCR1B=((1<<CS10));   // ���ö�ʱ��1��2��ʱ�ӷ�Ƶϵ��
   TCCR2B=((1<<CS20));
   Serial.begin(9600);   //  ʹ�ܴ���0 ���貨����Ϊ9600
   wdt_enable(WDTO_1S);  //
   InitPS2();            //  ��ʼ��PS2������
   analogWrite(M0, 0);   //   �����ĸ�����ĳ�ʼ״̬Ϊֹͣ
   analogWrite(M1, 0);
   digitalWrite(DIR0,0);
   digitalWrite(DIR1,0);
}
void loop()             // ѭ��ִ��
{
   TaskRun();          // ���ܺ���
   wdt_reset();        //  ι������
}

