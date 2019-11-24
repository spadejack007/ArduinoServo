#include "include.h"
#include <string.h>
static bool UartBusy = FALSE;
u32 gSystemTickCount = 0;	               //
uint8 BuzzerState = 0;
uint16 BatteryVoltage;
bool R_Running = FALSE;
bool L_Running = FALSE;
PS2X ps2X;                                //
void InitPS2()
{
  ps2X.config_gamepad(A0, A2, A1, A3);   // (clk, cmd, att, dat)  ����ң�ؽ�����clk, cmd, att, dat��Ӧ��IO�� 
}

void ps2Handle() {
  static uint32_t Timer;
  unsigned char PSS_RX_VALUE;
  unsigned char PSS_LY_VALUE;
  if (Timer > millis())
    return;
  ps2X.read_gamepad();                  //��ȡң�������µļ�ֵ        
  
  PSS_RX_VALUE = ps2X.Analog(PSS_RX);  //  ҡ��x�������ֵ
  PSS_LY_VALUE = ps2X.Analog(PSS_LY);  // ҡ��Y�������ֵ

  if (PSS_RX_VALUE == 255 && PSS_LY_VALUE == 255)    //��Чֵ
    return;
 
  if (PSS_RX_VALUE == 128 && PSS_LY_VALUE == 128){  // debug
  	
	analogWrite(M0,0);   // ������������pwm�ź�
	digitalWrite(DIR0,0);   // ������������pwm�ź�
	analogWrite(M1, 0);   // ������������pwm�ź�
	digitalWrite(DIR1,0);   // ������������pwm�ź�
  }
	

// ҡ����ԭ�����ֵΪPSS_RX_VALUE = 128 ,PSS_LY_VALUE = 128

// PSS_RX_VALUE �ķ�ΧΪ 0 - 255    PSS_LY_VALUE �ķ�ΧΪ 0 - 255
//analogWrite(ledpin,value) value����0-255֮�䣬�����ٶȡ�
//digitalWrite(pin,value) value 0����ת��1������ת;

  if (PSS_RX_VALUE < 120) {   // x�Ḻ����left
		Serial.print("x= "); 
		Serial.println(PSS_RX_VALUE);
		analogWrite(M0,(128 - PSS_RX_VALUE) * 2 -10 );   // ������������pwm�ź�
		digitalWrite(DIR0, 0);   // ������������pwm�ź�
		analogWrite(M1, (128 - PSS_RX_VALUE) * 2 -10);   // ������������pwm�ź�
		digitalWrite(DIR1,0);   // ������������pwm�ź� 

  }
  else if (PSS_RX_VALUE > 144)  //  X�������� right
  {
    Serial.print("x= ");
    Serial.println(PSS_RX_VALUE);
    analogWrite(M0, 510-PSS_RX_VALUE*2+10);
	digitalWrite(DIR0, 1);   // ������������pwm�ź�
    analogWrite(M1, 510-PSS_RX_VALUE*2+10);
	digitalWrite(DIR1, 1);   // ������������pwm�ź�
  }
   else{
         //  x����ҡ���޶���     qian
		if (PSS_LY_VALUE < 120)        //  Y ������x����ͬ��
		  {
			Serial.print("y= ");
			Serial.println(PSS_LY_VALUE);
			analogWrite(M0, (128 - PSS_LY_VALUE) *2 -10 );   // ������������pwm�ź�
			digitalWrite(DIR0, 0);   // ������������pwm�ź�
			analogWrite(M1,  2*PSS_LY_VALUE+10);   // ������������pwm�ź�
			digitalWrite(DIR1, 1);   // ������������pwm�ź�
		  }
		else if (PSS_LY_VALUE > 138) {     // hou
			Serial.print("y= ");
			Serial.println(PSS_LY_VALUE);
			analogWrite(M0, 510-PSS_LY_VALUE*2+10 );   // ������������pwm�ź�
			digitalWrite(DIR0, 1);   // ������������pwm�ź�
			analogWrite(M1, 2*PSS_LY_VALUE-256 -10);   // ������������pwm�ź�
			digitalWrite(DIR1, 0);   // ������������pwm�ź�
		}
		else {
		      analogWrite(M0,0);   // ������������pwm�ź�
		      digitalWrite(DIR0,0);   // ������������pwm�ź�
		      analogWrite(M1, 0);   // ������������pwm�ź�
		      digitalWrite(DIR1,0);   // ������������pwm�ź�
		     }
   	}
  	Timer = millis() + 50;       //ÿ50msִ��һ��

 }
void TaskRun(void)
{
  ps2Handle();
}


