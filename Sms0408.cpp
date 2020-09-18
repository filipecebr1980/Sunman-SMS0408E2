#include"Sms0408.h"

//FIGURES TABLE IMPLEMENTED ON FUNCTION CODIG:
//INDEX: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22
//FIG.   0 1 2 3 4 5 6 7 8 9 A  b  C  d  E  F  h  r  °  -  .	L  P

//constructor params: Digital Input Pin, Clock Pin, Back Light Anode Pin
Sms0408::Sms0408(int di, int clk, int bla)
{
pinMode(di, OUTPUT);
pinMode(clk, OUTPUT);
pinMode(bla, OUTPUT);
clkPin=clk;
dataPin=di;
backLightPin=bla;

//PARAMETERS
//defines output pins to test lcd

//defines clock frequency = 1/(2xdelay_t)
//in this case, fclock=500Hz.
int delay_t=1;
//auxiliary array to split digits
int aux[4];
}
//this function adjusts the lcd
//after the transmission of the buffers (digits /frames)
void Sms0408::adjust(){
	digitalWrite(dataPin,HIGH);
  	clock(2);
}
void Sms0408::backLight(){
//toogle back light ON/OFF
digitalWrite(backLightPin,!digitalRead(backLightPin));
}

int Sms0408::checkNumber(int number){	
int digits=1;  
  //inicializes digits in 0:
  for(int i=0; i<4; i++){
  aux[i]=0;
  }
 
  if (number<10){
    digits=1;
    aux[0]=number;        
  }
  else{
    if (number<100){
      split(number,2);
      digits=2;         
    }
    else{
      if (number < 1000){
      split(number,3);
      digits=3;          
      }
      else{
        if (number<10000){
          split(number,4);
          digits=4;         
        }
        else{
        	digits=5;
        }      
      }
    }
  }
return(digits);
}
void Sms0408::clearDigit(int n){
  for (int i=0; i<n; i++){
  digitalWrite(dataPin,HIGH);
  clock(8);
  }
}
//clears the LCD
void Sms0408::clearLCD(){
  digitalWrite(dataPin,HIGH);
  clock(40);
}
void Sms0408::clock(int n){ 
  for(int i=1; i<n+1;i++){
  digitalWrite(clkPin,HIGH);
  delay(delay_t);
  digitalWrite(clkPin,LOW);
  delay(delay_t);  
  }
}

//function to print symbols on the LCD
//the parameter number is the number of the 
//figure you want to send, according to the table
//on the beggining of the code.
//the parameter boolean is to be set to true if
//you want to print the decimal point.
void Sms0408::codig(int number, boolean dot){
//Digits mapping 	    |   Figure  0 |  Figure  1  |  Figure  2  |  Figure  3  |  Figure  4  |  Figure  5  |  Figure  6  |  Figure  7  |  Figure  8  |  Figure  9  |  Figure  A  |  Figure  b  |  Figure  C  |  Figure  d  |  Figure  E  |  Figure  F  |  Figure  h  |  Figure  r  |  Figure  °  |  Figure  -  |  Figure  .  |  Figure  L  |  Figure  P  |            
//This to help modify  6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0 6 5 4 3 2 1 0
boolean segments[161]={0,0,0,1,0,0,0,1,1,0,1,1,1,0,1,0,0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,1,1,0,1,1,0,0,1,0,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,0,0,0,0,0,1,1};

	//if you need the decimal point
	//send boolean parameter TRUE (1).
	if (dot){
		digitalWrite(dataPin,LOW);			
		}
		else{
		digitalWrite(dataPin,HIGH);
		}
	clock(1);
	for (int i=0; i<7; i++){
		digitalWrite(dataPin, segments[(7*number)+i]);
		clock(1);	
	}			
}

//displays the word Err.
//must call adjust after this funcion.
void Sms0408::displayError(){
clearLCD();
codig(14,0);
codig(17,0);
codig(17,0);
codig(20,1);
}
//this function automatically fits a non negative float
//up to 4 digits on the display, aligned right,
//and with n number of decimals passed by argument 2.
//must call the method adjust() after it.
//shows only positive numbers.
void Sms0408::displayFloat(float number, int decimals){
	
	if (number>1000.0 || number<0.0){
  	displayError();
  }
  else{
  	//converts the number into a integer:  
  	int temp=(int)(floor((number*pow(10.0,decimals))+0.001));
  	int digits=checkNumber(temp);
  	
   	//check if exceeded display digits
  	if (digits<5){
  		
  		 if(digits<=decimals){
  			digits=decimals+1;
  		}  			
  			for(int j=digits; j>0; j--){
  				if(j==decimals){  					
  						codig(aux[j-1],1);  					  					
  				}
  					else{
  					codig(aux[j-1],0);
  					}
  				}  		
  		}   		
  		else
  		{
  			displayError();
  		}
	}
}

//Fits a positive or negative float on the 
//display. It cut the excess of digits acording 
// to the range [-X.xx, -XX.x, X.XX, XX.xx, XXX.x]
//As it occupies the entire LCD. 
void Sms0408::displayFloatAuto(float number){
	int decimals=1;
	if (number<0.0){
		if(number>-10.0){
			decimals=2;
		}
		else{
			if(number>-100.0){
				decimals=1;
			}
			else{
				decimals=2;//will provoke a Display error.
			}					
		}
		codig(19,0);//represents minus symbol.			
	}
	else{
		if(number<10.0){
			decimals=3;
		}
		else{
			if(number<100.0){
				decimals=2;
			}
			else{
				decimals=1;
			}
		}
	}	
	displayFloat(abs(number),decimals);
	
}
//this function automatically fits a integer
//up to 4 digits on the display, aligned right.
//shows only positive numbers.
//must call the method adjust() after it.
void Sms0408::displayInt(int number){
	int digits=checkNumber(number);
	if (number>10000 || number<0){
  	displayError();
  }
  else
  {  	
	for (int i=digits; i>0; i--){
	codig(aux[i-1],0);
	} 
  }
} 
 
//fills the LCD (for testing segments)
void Sms0408::fillLCD(){
  digitalWrite(dataPin,LOW);
  clock(40);
}

//Shows buffer 0 Column (for time diplay format - HH:MM)
void Sms0408::showColumn(){
  digitalWrite(dataPin,LOW);
  clock(8);  
}

//this function shows time in the format HH:MM
//if you want to represent time in 24h
//format, remember to represent only minutes
//during the 0 (zero) hour: 0,1,2...59,100.
//this dos not need to call adjust() method.
void Sms0408::showTime(int hour){
	showColumn();
	if (hour<10){
		clearDigit(1);
		codig(0,0);
		codig(0,0);
		codig(hour,0);
		adjust();
	}
	else{
		if (hour<60){
		clearDigit(1);
		codig(0,0);
		displayInt(hour);
		adjust();		
		}
		else{
			if (hour<1000){
		clearDigit(1);
		displayInt(hour);
		adjust();
			}
			else{
				displayInt(hour);
				adjust();
			}				
		}		
	}	
}

//splits an integer in n digits stored in the aux array.
//aux[]=[DIGIT1(LSD), DIGIT2, DIGIT3, DIGIT4(MSD)]

void Sms0408::split(int number, int digits){
  float temp=(float)number;
  for (int i=0; i<digits; i++){
  temp=temp/10.0;
  aux[i]=(int)((10.0*(temp-floor(temp)))+0.001);
  temp=floor(temp);
  }
}















