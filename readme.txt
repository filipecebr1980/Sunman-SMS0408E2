+=======================================================================+
+	SUNMAN  SMS0408 7 SEGMENT 4 DIGIT LCD BASIC FUNCTIONS		+
+       ARDUINO LIBRARY - V1.0						+
+	BY FILIPE CESAR BRANDAO - budegarower@gmail.com			+
+=======================================================================+

This library contains basic methods to use the SMS0408E2 7 segment, 4 digits LCD. It was 
written in cpp language and is supposed to work with most Arduino boards.

========================================================================
1.0 - Object constructor
========================================================================

Sms0408 objectName(di, clk, bla)

Where:
di, clk and bla are type int (integer);
di is to be assigned to pin used to be connected to the LCD DI (data input);
clk is to be assigned to LCD CLK (clock) input;
bla is to be assigned to LCD BLA (back light led anode) input.

Example: Assigns pins 3, 4 and 5 of Arduino board to DI, CLK and BLA

Sms0408 myLCD(3,4,5);
=========================================================================
2.0 Methods
=========================================================================
adjust();
Parameters: void
Returns: void

This  method is necessary to be called after some methods, in the end of the transmission 
of a sequence of symbols sent to the LCD. 
The exception is the method showTime(int time), it does not need to be adjusted because it 
calls the method by itself.

=========================================================================
backLight();
Parameters: void
Returns: void

This method is used to toggle the state of BLA pin, turning on and off the LCD's back light.

=========================================================================
checkNumber(int);
Parameters: Integer number. 
returns: an integer which is the number of digits of an integer number

This int method is an auxiliary method for other methods such as displayFLoat(float)  and
displayInt(int)

Example: 

a= myLCD.checkNumber(99);

In this case a=2 because "99" is composed by 2 digits

=========================================================================
clearDigit(int);
Parameters: integer number of "blank" digits to be sent to the LCD. 
Returns: void

This is equivalent to sending "spaces" to separate numbers or symbols.

=========================================================================
clearLCD();
Parameters: void
Returns: void

This method cleans the LCD (all digits). It is necessary to call it all times you want to update 
the content of the LCD. Not necessary to call the adjust() method after it.

=========================================================================
clock(int);
Parameters: integer number of clock cycles
Returns: void

This is an accessory to almost all other methods. It is necessary to sync all data transfer to 
the synchronous serial DI port on the LCD.

=========================================================================
codig(int, boolean);
Parameters: 
int number -  according to the implemented characters map (from 0 to 20)
boolean dot - true (1) or false (0). Use true if you want your digit to be preceded by a dot 
(decimal separator). Use false, if you don't want to represent the dot within the digit sent.
Returns: void

This method is used to codify an integer in to a specific figure to be sent to the LCD. The 
implemented symbols can be seen on the table below (mapping):

INDEX:	0   1   2   3   4   5   6   7   8   9   10   11   12  13  14   15   16   17   18   19   20   21   22
FIG.	0   1   2   3   4   5   6   7   8   9    A    b    C   d   E    F    h    r    °    -    .    L    P

EXAMPLES:

myLCD.codig(3,0); 
Sends the number 3 to the LCD.

myLCD.clearLCD();
myLCD.codig(0,0)
myLCD.codig(8,1);
myLCD.codig(10,0)
myLCD.adjust();
 
clears LCD, sends the symbol "0", sends the symbol "8" with the dot, sends the character "A", 
adjusts the LCD. The result is: 

0.8A 

is displayed on the LCD.

The customization of symbols is possible with good care when editing the boolean array 
segments[], inside the library.

=========================================================================
displayError();
parameters: void
returns: void

This  method  shows the word "Err." on the LCD.  You can call it to signalize an error condition. 
It is called when you try to represent
a number which exceeds the number of digits or decimals possible to be shown on the LCD. 
You must call adjust() method after it.
	
=========================================================================
displayFloat(float, int);
Parameters: float number to be displayed.  Integer number of decimals to be represented.
Returns: void
displayInt(int)

This function can represent generic positive  floating point numbers.  The total amount 
of digits must be less then 4, which means: integer digits+decimals < 4. So,  pay attention  
when trying to represent the numbers. So you can fit any number from 0.000 to 999.9, 
respecting the maximum number of digits. The number will be aligned to the right.

=========================================================================
displayFloatAuto(float, int);
Parameters: float number to be displayed.
Returns: void

This function can represent generic floating point numbers (positive and negative between -99.9 to 999.9).  
The total amount of digits must be less then 4, it will be automatically adjusted, trimming 
the extra decimals. If you call the function with some argument out of the boundaries it 
will call displayError() method. As the other display functions, you have to call the adjust() 
method after sending the numbers to the LCD to have the correct display.

=========================================================================
displayInt(int);
Parameters: Integer positive number to be displayed. Must fit the LCD (4 digits).
Returns: void

The number will be aligned to the right. You must call the adjust() method  after displayInt(), 
displayFLoat() or displayFloatAuto() for correct displaying.

=========================================================================
fillLCD();
Parameters: void
Returns: void

This is used to turn ON all LCD segments. This is good to test the LCD. Not necessary to call 
adjust() method after it.

=========================================================================
showColumn()
Parameters: void
Returns: void

This is used to represent time format HH:MM and is called to send on buffer 0 the 
character ":"  on the LCD column.  This method is used by showTime() method.

=========================================================================
split(int,int)
Parameters: int number to be split in separate digits. Integer number of digits you want
to split a number.
Returns:  void

Accessory method to displayInt() and displayFloat() methods. Besides it is void and a 
public method, it can provide the separation of an integer in different digits, starting 
from  the least significant digit and finishing up to the most significant digit. The digits 
are stored in a private array aux[],  no access outside the class Sms0408.

=========================================================================
showTime(int);
Parameters: Integer time to be displayed.
Returns: void

This is to show time in the format HH:MM. The argument is an integer which represents 
12 or 24 hours format as follows:
From 00:00 to 00:59: 0, 1,2......58, 59.  Just use  the minutes as argument. Do not put zero 
before, like 01, 02, 03.
From 01:00 to 23:59: 100, 101, ...159, 200, 201...259, 300..359, 400...500...600..700..800..900...
1000...1100...1200...1900..2000..2100...2200, 2201..2259, 2300...2359, 0.

Example:
myLCD.showTime(5);
Shows 00:05 on the display.

myLCD.showTime(420);
shows 4:20.

myLCD.showTime(1235);
shows 12:35.

OBS: Not necessary to call adjust() method after showTime(int). It does it inside the method.























































