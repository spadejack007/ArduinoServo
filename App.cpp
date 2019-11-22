#include "include.h"
#include <string.h>
static bool UartBusy = FALSE;
u32 gSystemTickCount = 0;	               //
uint8 BuzzerState = 0;
uint16 BatteryVoltage;
bool R_Running = FALSE;
bool L_Running = FALSE;
PS2X ps2X;                                //
int speed = 4;//ï¿½ï¿½ï¿½ï¿½ï¿½Ù¶ï¿½ 4ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ùµï¿½ 1/4ï¿½ï¿½2ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ùµï¿½1/2ï¿½ï¿½1ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½--jack

void InitPS2()
{
  ps2X.config_gamepad(A0, A2, A1, A3);   // (clk, cmd, att, dat)  ï¿½ï¿½ï¿½ï¿½Ò£ï¿½Ø½ï¿½ï¿½ï¿½ï¿½ï¿½clk, cmd, att, datï¿½ï¿½Ó¦ï¿½ï¿½IOï¿½ï¿½ 
}

<<<<<<< HEAD
//jackÌí¼ÓsetSpeedº¯Êý
void setSpeed(int speed)
=======
//jackï¿½ï¿½ï¿½setSpeedï¿½ï¿½ï¿½ï¿½
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
  ps2X.read_gamepad();                  //ï¿½ï¿½È¡Ò£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÂµÄ¼ï¿½Öµ        
  
<<<<<<< HEAD
  PSS_RX_VALUE = ps2X.Analog(PSS_RX);  //  Ò¡¸Ëx·½ÏòµÄÊýÖµ
  PSS_LY_VALUE = ps2X.Analog(PSS_LY);  // Ò¡¸ËY·½ÏòµÄÊýÖµ
  //jack-¸ù¾Ý°´¼üÉèÖÃËÙ¶È--º¯ÊýÈë¿Ú
  if (ps2X.NewButtonState()){        //will be TRUE if any button changes state (on to off, or off to on)
    if(ps2X.Button(PSB_R2)){
        Serial.println("R2 pressed");
		setSpeed(speed);
	  }
    }

  if (PSS_RX_VALUE == 255 && PSS_LY_VALUE == 255)    //ÎÞÐ§Öµ
=======
  PSS_RX_VALUE = ps2X.Analog(PSS_RX);  //  Ò¡ï¿½ï¿½xï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Öµ
  PSS_RY_VALUE = ps2X.Analog(PSS_RY);  // Ò¡ï¿½ï¿½Yï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Öµ
  //jack-ï¿½ï¿½ï¿½Ý°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ù¶ï¿½--ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
  if (ps2X.NewButtonState()){        //will be TRUE if any button changes state (on to off, or off to on)
    if(ps2X.Button(PSB_R2)){
        Serial.println("R2 pressed");
		    setSpeed();
	    }
    }

  if (PSS_RX_VALUE == 255 && PSS_RY_VALUE == 255)    //ï¿½ï¿½Ð§Öµ
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
// Ò¡¸ËÔÚÔ­µãµÄÖÐÖµÎªPSS_RX_VALUE = 128 ,PSS_LY_VALUE = 128

// PSS_RX_VALUE µÄ·¶Î§Îª 0 - 255    PSS_LY_VALUE µÄ·¶Î§Îª 0 - 255
=======
// Ò¡ï¿½ï¿½ï¿½ï¿½Ô­ï¿½ï¿½ï¿½ï¿½ï¿½ÖµÎªPSS_RX_VALUE = 128 ,PSS_RY_VALUE = 128

// PSS_RX_VALUE ï¿½Ä·ï¿½Î§Îª 0 - 255    PSS_RY_VALUE ï¿½Ä·ï¿½Î§Îª 0 - 255
>>>>>>> c65c54dd2e7064c3d1cc6d245e65b04e855548b8


  if (PSS_RX_VALUE < 120) {   // xï¿½á¸ºï¿½ï¿½ï¿½ï¿½left
		Serial.print("x= "); 
		Serial.println(PSS_RX_VALUE);
		analogWrite(M0,((128 - PSS_RX_VALUE) * 2 -10 )/speed);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
		digitalWrite(DIR0, 0);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
		analogWrite(M1, ((128 - PSS_RX_VALUE) * 2 -10)/speed);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
		digitalWrite(DIR1,0);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½ 

  }
  else if (PSS_RX_VALUE > 144)  //  Xï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ right
  {
    Serial.print("x= ");
    Serial.println(PSS_RX_VALUE);
    analogWrite(M0, (510-PSS_RX_VALUE*2+10)/speed);
	digitalWrite(DIR0, 1);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
    analogWrite(M1, (510-PSS_RX_VALUE*2+10)/speed);
	digitalWrite(DIR1, 1);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
  }
   else{
<<<<<<< HEAD
         //  x·½ÏòÒ¡¸ËÎÞ¶¯×÷     qian
		if (PSS_LY_VALUE < 120)        //  Y ·½ÏòÓëx·½ÏòÍ¬Àí
		  {
			Serial.print("y= ");
			Serial.println(PSS_LY_VALUE);
			analogWrite(M0, ((128 - PSS_LY_VALUE) *2 -10 )/speed);   // ¸øµç»úÇý¶¯°åµÄpwmÐÅºÅ
			digitalWrite(DIR0, 0);   // ¸øµç»úÇý¶¯°åµÄpwmÐÅºÅ
			analogWrite(M1,  ((128 - PSS_LY_VALUE) *2 -10 )/speed);   // ¸øµç»úÇý¶¯°åµÄpwmÐÅºÅ
			digitalWrite(DIR1, 1);   // ¸øµç»úÇý¶¯°åµÄpwmÐÅºÅ
=======
         //  xï¿½ï¿½ï¿½ï¿½Ò¡ï¿½ï¿½ï¿½Þ¶ï¿½ï¿½ï¿½     qian
		if (PSS_RY_VALUE < 120)        //  Y ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½xï¿½ï¿½ï¿½ï¿½Í¬ï¿½ï¿½
		  {
			Serial.print("y= ");
			Serial.println(PSS_RY_VALUE);
			analogWrite(M0, ((128 - PSS_RY_VALUE) *2 -10 )/speed);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
			digitalWrite(DIR0, 0);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
			analogWrite(M1,  (2*PSS_RY_VALUE+10)/speed);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
			digitalWrite(DIR1, 1);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
>>>>>>> c65c54dd2e7064c3d1cc6d245e65b04e855548b8
		  }
		else if (PSS_LY_VALUE > 138) {     // hou
			Serial.print("y= ");
<<<<<<< HEAD
			Serial.println(PSS_LY_VALUE);
			analogWrite(M0, (510-PSS_LY_VALUE*2+10)/speed);   // ¸øµç»úÇý¶¯°åµÄpwmÐÅºÅ
			digitalWrite(DIR0, 1);   // ¸øµç»úÇý¶¯°åµÄpwmÐÅºÅ
			analogWrite(M1, (510-PSS_LY_VALUE*2+10)/speed);   // ¸øµç»úÇý¶¯°åµÄpwmÐÅºÅ
			digitalWrite(DIR1, 0);   // ¸øµç»úÇý¶¯°åµÄpwmÐÅºÅ
=======
			Serial.println(PSS_RY_VALUE);
			analogWrite(M0, (510-PSS_RY_VALUE*2+10)/speed);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
			digitalWrite(DIR0, 1);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
			analogWrite(M1, (2*PSS_RY_VALUE-256 -10)/speed);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
			digitalWrite(DIR1, 0);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
>>>>>>> c65c54dd2e7064c3d1cc6d245e65b04e855548b8
		}
		else {
		      analogWrite(M0,0);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
		      digitalWrite(DIR0,0);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
		      analogWrite(M1, 0);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
		      digitalWrite(DIR1,0);   // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pwmï¿½Åºï¿½
		     }
   	}
<<<<<<< HEAD
  	Timer = millis() + 50;       //Ã¿50msÖ´ÐÐÒ»´Î
=======
  	Timer = millis() + 50;       //Ã¿50msÖ´ï¿½ï¿½Ò»ï¿½ï¿½

>>>>>>> c65c54dd2e7064c3d1cc6d245e65b04e855548b8
 }
 
void TaskRun(void)
{
  ps2Handle();
}
