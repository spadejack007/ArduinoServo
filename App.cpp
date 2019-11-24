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
  ps2X.config_gamepad(A0, A2, A1, A3);   // (clk, cmd, att, dat)  设置遥控接收器clk, cmd, att, dat对应的IO口 
}

void ps2Handle() {
  static uint32_t Timer;
  unsigned char PSS_RX_VALUE;
  unsigned char PSS_LY_VALUE;
  if (Timer > millis())
    return;
  ps2X.read_gamepad();                  //读取遥控器按下的键值        
  
  PSS_RX_VALUE = ps2X.Analog(PSS_RX);  //  摇杆x方向的数值
  PSS_LY_VALUE = ps2X.Analog(PSS_LY);  // 摇杆Y方向的数值

  if (PSS_RX_VALUE == 255 && PSS_LY_VALUE == 255)    //无效值
    return;
 
  if (PSS_RX_VALUE == 128 && PSS_LY_VALUE == 128){  // debug
  	
	analogWrite(M0,0);   // 给电机驱动板的pwm信号
	digitalWrite(DIR0,0);   // 给电机驱动板的pwm信号
	analogWrite(M1, 0);   // 给电机驱动板的pwm信号
	digitalWrite(DIR1,0);   // 给电机驱动板的pwm信号
  }
	

// 摇杆在原点的中值为PSS_RX_VALUE = 128 ,PSS_LY_VALUE = 128

// PSS_RX_VALUE 的范围为 0 - 255    PSS_LY_VALUE 的范围为 0 - 255
//analogWrite(ledpin,value) value介于0-255之间，代表速度。
//digitalWrite(pin,value) value 0代表反转；1代表正转;

  if (PSS_RX_VALUE < 120) {   // x轴负方向left
		Serial.print("x= "); 
		Serial.println(PSS_RX_VALUE);
		analogWrite(M0,(128 - PSS_RX_VALUE) * 2 -10 );   // 给电机驱动板的pwm信号
		digitalWrite(DIR0, 0);   // 给电机驱动板的pwm信号
		analogWrite(M1, (128 - PSS_RX_VALUE) * 2 -10);   // 给电机驱动板的pwm信号
		digitalWrite(DIR1,0);   // 给电机驱动板的pwm信号 

  }
  else if (PSS_RX_VALUE > 144)  //  X轴正方向 right
  {
    Serial.print("x= ");
    Serial.println(PSS_RX_VALUE);
    analogWrite(M0, 510-PSS_RX_VALUE*2+10);
	digitalWrite(DIR0, 1);   // 给电机驱动板的pwm信号
    analogWrite(M1, 510-PSS_RX_VALUE*2+10);
	digitalWrite(DIR1, 1);   // 给电机驱动板的pwm信号
  }
   else{
         //  x方向摇杆无动作     qian
		if (PSS_LY_VALUE < 120)        //  Y 方向与x方向同理
		  {
			Serial.print("y= ");
			Serial.println(PSS_LY_VALUE);
			analogWrite(M0, (128 - PSS_LY_VALUE) *2 -10 );   // 给电机驱动板的pwm信号
			digitalWrite(DIR0, 0);   // 给电机驱动板的pwm信号
			analogWrite(M1,  2*PSS_LY_VALUE+10);   // 给电机驱动板的pwm信号
			digitalWrite(DIR1, 1);   // 给电机驱动板的pwm信号
		  }
		else if (PSS_LY_VALUE > 138) {     // hou
			Serial.print("y= ");
			Serial.println(PSS_LY_VALUE);
			analogWrite(M0, 510-PSS_LY_VALUE*2+10 );   // 给电机驱动板的pwm信号
			digitalWrite(DIR0, 1);   // 给电机驱动板的pwm信号
			analogWrite(M1, 2*PSS_LY_VALUE-256 -10);   // 给电机驱动板的pwm信号
			digitalWrite(DIR1, 0);   // 给电机驱动板的pwm信号
		}
		else {
		      analogWrite(M0,0);   // 给电机驱动板的pwm信号
		      digitalWrite(DIR0,0);   // 给电机驱动板的pwm信号
		      analogWrite(M1, 0);   // 给电机驱动板的pwm信号
		      digitalWrite(DIR1,0);   // 给电机驱动板的pwm信号
		     }
   	}
  	Timer = millis() + 50;       //每50ms执行一次

 }
void TaskRun(void)
{
  ps2Handle();
}


