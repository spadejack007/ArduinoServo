#include "include.h"
#include <string.h>
static bool UartBusy = FALSE;
u32 gSystemTickCount = 0;	               //
uint8 BuzzerState = 0;
uint16 BatteryVoltage;
bool R_Running = FALSE;
bool L_Running = FALSE;
PS2X ps2X;                                //
int speed = 4;//�����ٶ� 4�������ٵ� 1/4��2�������ٵ�1/2��1��������--jack

void InitPS2()
{
  ps2X.config_gamepad(A0, A2, A1, A3);   // (clk, cmd, att, dat)  ����ң�ؽ�����clk, cmd, att, dat��Ӧ��IO�� 
}

<<<<<<< HEAD
//jack����setSpeed����
void setSpeed(int speed)
=======
//jack���setSpeed����
void setSpeed()
>>>>>>> c65c54dd2e7064c3d1cc6d245e65b04e855548b8
{
	switch(speed){
		case 4:
		  speed = 2;
		  break;
		case 2:
		  speed = 2;
		  break;
		case 1:
		  speed = 2;
		  break;
		default:
		  speed = 4;
		  break;
	}

}

void ps2Handle() {
  static uint32_t Timer;
  unsigned char PSS_RX_VALUE;
  unsigned char PSS_LY_VALUE;
  if (Timer > millis())
    return;
  ps2X.read_gamepad();                  //��ȡң�������µļ�ֵ        
  
<<<<<<< HEAD
  PSS_RX_VALUE = ps2X.Analog(PSS_RX);  //  ҡ��x�������ֵ
  PSS_LY_VALUE = ps2X.Analog(PSS_LY);  // ҡ��Y�������ֵ
  //jack-���ݰ��������ٶ�--�������
  if (ps2X.NewButtonState()){        //will be TRUE if any button changes state (on to off, or off to on)
    if(ps2X.Button(PSB_R2)){
        Serial.println("R2 pressed");
		setSpeed(speed);
	  }
    }

  if (PSS_RX_VALUE == 255 && PSS_LY_VALUE == 255)    //��Чֵ
=======
  PSS_RX_VALUE = ps2X.Analog(PSS_RX);  //  ҡ��x�������ֵ
  PSS_RY_VALUE = ps2X.Analog(PSS_RY);  // ҡ��Y�������ֵ
  //jack-���ݰ��������ٶ�--�������
  if (ps2X.NewButtonState()){        //will be TRUE if any button changes state (on to off, or off to on)
    if(ps2X.Button(PSB_R2)){
        Serial.println("R2 pressed");
		    setSpeed();
	    }
    }

  if (PSS_RX_VALUE == 255 && PSS_RY_VALUE == 255)    //��Чֵ
>>>>>>> c65c54dd2e7064c3d1cc6d245e65b04e855548b8
    return;
  #if 1
  if (PSS_RX_VALUE == 128 && PSS_LY_VALUE == 255){  // debug
  	
         ps2X.read_gamepad();   
		 PSS_RX_VALUE = ps2X.Analog(PSS_RX);
         PSS_LY_VALUE = ps2X.Analog(PSS_LY);
		 if(PSS_RX_VALUE == 128 && PSS_LY_VALUE == 255){
		 }
		 else return;   
	     Serial.println("Error!");
  }
	  
  #endif

<<<<<<< HEAD
// ҡ����ԭ�����ֵΪPSS_RX_VALUE = 128 ,PSS_LY_VALUE = 128

// PSS_RX_VALUE �ķ�ΧΪ 0 - 255    PSS_LY_VALUE �ķ�ΧΪ 0 - 255
=======
// ҡ����ԭ�����ֵΪPSS_RX_VALUE = 128 ,PSS_RY_VALUE = 128

// PSS_RX_VALUE �ķ�ΧΪ 0 - 255    PSS_RY_VALUE �ķ�ΧΪ 0 - 255
>>>>>>> c65c54dd2e7064c3d1cc6d245e65b04e855548b8


  if (PSS_RX_VALUE < 120) {   // x�Ḻ����left
		Serial.print("x= "); 
		Serial.println(PSS_RX_VALUE);
		analogWrite(M0,((128 - PSS_RX_VALUE) * 2 -10 )/speed);   // ������������pwm�ź�
		digitalWrite(DIR0, 0);   // ������������pwm�ź�
		analogWrite(M1, ((128 - PSS_RX_VALUE) * 2 -10)/speed);   // ������������pwm�ź�
		digitalWrite(DIR1,0);   // ������������pwm�ź� 

  }
  else if (PSS_RX_VALUE > 144)  //  X�������� right
  {
    Serial.print("x= ");
    Serial.println(PSS_RX_VALUE);
    analogWrite(M0, (510-PSS_RX_VALUE*2+10)/speed);
	digitalWrite(DIR0, 1);   // ������������pwm�ź�
    analogWrite(M1, (510-PSS_RX_VALUE*2+10)/speed);
	digitalWrite(DIR1, 1);   // ������������pwm�ź�
  }
   else{
<<<<<<< HEAD
         //  x����ҡ���޶���     qian
		if (PSS_LY_VALUE < 120)        //  Y ������x����ͬ��
		  {
			Serial.print("y= ");
			Serial.println(PSS_LY_VALUE);
			analogWrite(M0, ((128 - PSS_LY_VALUE) *2 -10 )/speed);   // ������������pwm�ź�
			digitalWrite(DIR0, 0);   // ������������pwm�ź�
			analogWrite(M1,  ((128 - PSS_LY_VALUE) *2 -10 )/speed);   // ������������pwm�ź�
			digitalWrite(DIR1, 1);   // ������������pwm�ź�
=======
         //  x����ҡ���޶���     qian
		if (PSS_RY_VALUE < 120)        //  Y ������x����ͬ��
		  {
			Serial.print("y= ");
			Serial.println(PSS_RY_VALUE);
			analogWrite(M0, ((128 - PSS_RY_VALUE) *2 -10 )/speed);   // ������������pwm�ź�
			digitalWrite(DIR0, 0);   // ������������pwm�ź�
			analogWrite(M1,  (2*PSS_RY_VALUE+10)/speed);   // ������������pwm�ź�
			digitalWrite(DIR1, 1);   // ������������pwm�ź�
>>>>>>> c65c54dd2e7064c3d1cc6d245e65b04e855548b8
		  }
		else if (PSS_LY_VALUE > 138) {     // hou
			Serial.print("y= ");
<<<<<<< HEAD
			Serial.println(PSS_LY_VALUE);
			analogWrite(M0, (510-PSS_LY_VALUE*2+10)/speed);   // ������������pwm�ź�
			digitalWrite(DIR0, 1);   // ������������pwm�ź�
			analogWrite(M1, (510-PSS_LY_VALUE*2+10)/speed);   // ������������pwm�ź�
			digitalWrite(DIR1, 0);   // ������������pwm�ź�
=======
			Serial.println(PSS_RY_VALUE);
			analogWrite(M0, (510-PSS_RY_VALUE*2+10)/speed);   // ������������pwm�ź�
			digitalWrite(DIR0, 1);   // ������������pwm�ź�
			analogWrite(M1, (2*PSS_RY_VALUE-256 -10)/speed);   // ������������pwm�ź�
			digitalWrite(DIR1, 0);   // ������������pwm�ź�
>>>>>>> c65c54dd2e7064c3d1cc6d245e65b04e855548b8
		}
		else {
		      analogWrite(M0,0);   // ������������pwm�ź�
		      digitalWrite(DIR0,0);   // ������������pwm�ź�
		      analogWrite(M1, 0);   // ������������pwm�ź�
		      digitalWrite(DIR1,0);   // ������������pwm�ź�
		     }
   	}
<<<<<<< HEAD
  	Timer = millis() + 50;       //ÿ50msִ��һ��
=======
  	Timer = millis() + 50;       //ÿ50msִ��һ��

>>>>>>> c65c54dd2e7064c3d1cc6d245e65b04e855548b8
 }
 
void TaskRun(void)
{
  ps2Handle();
}
