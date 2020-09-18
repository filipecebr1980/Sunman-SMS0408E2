#include <Sms0408.h>

/*FIGURES TABLE IMPLEMENTED ON FUNCTION CODIG:
*INDEX: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
*FIG.   0 1 2 3 4 5 6 7 8 9 A  b  C  d  E  F  h  r  °  -  .

-HARDWARE:

SMS0408E2_LCD_DI ------> D3_ARDUINO
SMS0408E2_LCD_CLK------> D4_ARDUINO
SMS0408E2_LCD_BLA------> D5_ARDUINO
SMS0408E2_LCD_VDD------> 5V_ARDUINO
SMS0408E2_LCD_VSS------>GND_ARDUINO
*/

int di=3;
int clk=4;
int backlight=5;
int time=500;

//create an LCD object
Sms0408 myLCD(di,clk,backlight);

void setup(){
  Serial.begin(9600);
}

void loop(){
//Examples of use for the lybrary Sms0408
  
  //toogle backlight ON/OFF
  myLCD.backLight();
  
  //fills LCD (all segments on- good to test if has any 
  //bad segment
  myLCD.fillLCD();    
  delay(1000);
  
  //clears LCD
  myLCD.clearLCD();
  delay(1000);
  
  //shows collum (buffer 0 ) for time format display
  myLCD.showColumn();
  //just to send a sequence of 4 "empty" digits
  myLCD.clearDigit(4);
  
  //this need to be done after sending what you want
  //to adjust the display (2 clock pulses and a HIGH level on data)
  myLCD.adjust();
  delay(1000);
  
  //shows all characters implemented in a sequence
  for(int i=0;i<18;i++){
  myLCD.clearLCD();
  if (i!=17){  
  myLCD.codig(i,0);
  myLCD.codig(i+1,0);
  myLCD.codig(i+2,0);
  myLCD.codig(i+3,0);
    }
  else{
  myLCD.codig(i,0);
  myLCD.codig(i+1,0);
  myLCD.codig(i+2,0);
  myLCD.codig(i+3,1);
  }
  myLCD.adjust();
  delay(time);
 }
  myLCD.clearLCD();
  //shows time in format HH:MM
  myLCD.clearLCD();
  myLCD.showColumn();
  myLCD.showTime(420);
  delay(2*time);
 
 //shows integers up to the max amount possible
  int a=2;
  for(int i=0; i<15;i++){
  myLCD.clearLCD();
  myLCD.displayInt(pow(a,i)+1);
  myLCD.adjust();
  delay(time);
  }
  
  //shows floating point numbers
  float b=1.0;
  for(int i=1; i<4;i++){
  myLCD.clearLCD();
  myLCD.displayFloat((b*pow(10,-i)),3);
  myLCD.adjust();
  delay(2*time);
  }
    b=999.9;
  for(int i=1; i<4;i++){
  myLCD.clearLCD();
  myLCD.displayFloat(b,i);
  myLCD.adjust();
  delay(2*time);
  b=b*pow(10,-1);
  }
  
  //Show mixed numbers and symbols
  //shows -2°C
  myLCD.clearLCD();
  myLCD.codig(19,0);
  myLCD.codig(2,0);
  myLCD.codig(18,0);
  myLCD.codig(12,0);
  myLCD.adjust();
  delay(3*time);
  
  //shows 2.5 A
  myLCD.clearLCD();
  myLCD.displayFloat(2.5,1);
  myLCD.clearDigit(1);
  myLCD.codig(10,0);
  myLCD.adjust();
  delay(3*time);
  
  //displays a float (auto format)
  myLCD.clearLCD();
  myLCD.displayFloatAuto(-0.998);
  myLCD.adjust();
  delay(3*time);
  
  //This will trow an error display:
  //the number does not fit the LCD
  myLCD.clearLCD();
  myLCD.displayFloatAuto(-201.99);
  myLCD.adjust();
  delay(3*time);


}
