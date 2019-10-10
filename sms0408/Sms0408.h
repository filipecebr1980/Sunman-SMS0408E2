#ifndef SMS0408_H
#define SMS0408_H

#include <Arduino.h> 

class Sms0408
{
public:
Sms0408(int di, int clk, int bla);
void adjust();
void backLight();
int checkNumber(int number);
void clearDigit(int n);
void clearLCD();
void clock(int n);
void codig(int digit, boolean dot);
void displayError();
void displayFloat(float number, int decimals);
void displayFloatAuto(float number);
void displayInt(int number);
void fillLCD();
void showColumn();
void showTime(int hour);
void split(int number, int digits );

private:
//PIN PARAMETERS
int clkPin;
int dataPin;
int backLightPin;
//USED FOR CLOCK
int delay_t; //[microsseconds]
int aux[4];
}; 
#endif