#include "include.h"
#include <string.h>
static bool UartBusy = FALSE;
u32 gSystemTickCount = 0;	               //
uint8 BuzzerState = 0;
uint16 BatteryVoltage;
bool R_Running = FALSE;
bool L_Running = FALSE;
PS2X ps2X;                                //
int speed = 4;//设置速度 4代表满速的 1/4；2代表，满速的1/2；1代表满速--jack

void InitPS2()
{
  ps2X.config_gamepad(A0, A2, A1, A3);   // (clk, cmd, att, dat)  设置遥控接收器clk, cmd, att, dat对应的IO口 
}

//jack添加setSpeed函数
void setSpeed()
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
  unsigned char PSS_RY_VALUE;
  if (Timer > millis())
    return;
  ps2X.read_gamepad();                  //读取遥控器按下的键值        
  
  PSS_RX_VALUE = ps2X.Analog(PSS_RX);  //  摇杆x方向的数值
  PSS_RY_VALUE = ps2X.Analog(PSS_RY);  // 摇杆Y方向的数值
  //jack-根据按键设置速度--函数入口
  if (ps2x.NewButtonState()){        //will be TRUE if any button changes state (on to off, or off to on)
    if(ps2x.Button(PSB_R2)){
        Serial.println("R2 pressed");
		setSpeed()
	  }
    }

  if (PSS_RX_VALUE == 255 && PSS_RY_VALUE == 255)    //无效值
    return;
  #if 1
  if (PSS_RX_VALUE == 128 && PSS_RY_VALUE == 255){  // debug
  	
         ps2X.read_gamepad();   
		 PSS_RX_VALUE = ps2X.Analog(PSS_RX);
         PSS_RY_VALUE = ps2X.Analog(PSS_RY);
		 if(PSS_RX_VALUE == 128 && PSS_RY_VALUE == 255){
		 }
		 else return;   
	     Serial.println("Error!");
  }
	  
  #endif

// 摇杆在原点的中值为PSS_RX_VALUE = 128 ,PSS_RY_VALUE = 128

// PSS_RX_VALUE 的范围为 0 - 255    PSS_RY_VALUE 的范围为 0 - 255


  if (PSS_RX_VALUE < 120) {   // x轴负方向left
		Serial.print("x= "); 
		Serial.println(PSS_RX_VALUE);
		analogWrite(M0,((128 - PSS_RX_VALUE) * 2 -10 )/speed);   // 给电机驱动板的pwm信号
		digitalWrite(DIR0, 0);   // 给电机驱动板的pwm信号
		analogWrite(M1, ((128 - PSS_RX_VALUE) * 2 -10)/speed);   // 给电机驱动板的pwm信号
		digitalWrite(DIR1,0);   // 给电机驱动板的pwm信号 

  }
  else if (PSS_RX_VALUE > 144)  //  X轴正方向 right
  {
    Serial.print("x= ");
    Serial.println(PSS_RX_VALUE);
    analogWrite(M0, (510-PSS_RX_VALUE*2+10)/speed);
	digitalWrite(DIR0, 1);   // 给电机驱动板的pwm信号
    analogWrite(M1, (510-PSS_RX_VALUE*2+10)/speed);
	digitalWrite(DIR1, 1);   // 给电机驱动板的pwm信号
  }
   else{
         //  x方向摇杆无动作     qian
		if (PSS_RY_VALUE < 120)        //  Y 方向与x方向同理
		  {
			Serial.print("y= ");
			Serial.println(PSS_RY_VALUE);
			analogWrite(M0, ((128 - PSS_RY_VALUE) *2 -10 )/speed);   // 给电机驱动板的pwm信号
			digitalWrite(DIR0, 0);   // 给电机驱动板的pwm信号
			analogWrite(M1,  (2*PSS_RY_VALUE+10)/speed);   // 给电机驱动板的pwm信号
			digitalWrite(DIR1, 1);   // 给电机驱动板的pwm信号
		  }
		else if (PSS_RY_VALUE > 138) {     // hou
			Serial.print("y= ");
			Serial.println(PSS_RY_VALUE);
			analogWrite(M0, (510-PSS_RY_VALUE*2+10)/speed);   // 给电机驱动板的pwm信号
			digitalWrite(DIR0, 1);   // 给电机驱动板的pwm信号
			analogWrite(M1, (2*PSS_RY_VALUE-256 -10)/speed);   // 给电机驱动板的pwm信号
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


