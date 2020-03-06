/*  Soil Mositure Basic Example
    This sketch was written by SparkFun Electronics
    Joel Bartlett 
    August 31, 2015

    Basic skecth to print out soil moisture values to the Serial Monitor 

    Released under the MIT License(http://opensource.org/licenses/MIT)
*/

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */


#include <LiquidCrystal.h>

int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
int soilPower = 2;//Variable for Soil moisture Power

const int pump = 13;

int threshold = 600;

//Rather than powering the sensor through the 3.3V or 5V pins, 
//we'll use a digital pin to power the sensor. This will 
//prevent corrosion of the sensor as it sits in the soil. 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(3, 4, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);

  pinMode(soilPower, OUTPUT);
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor

  pinMode (pump, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {

  lcd.clear();
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);

  //Serial.print("Soil Moisture = ");    
  //Serial.println(readSoil());

  // Print a message to the LCD.
  lcd.print("Moisture = ");
  lcd.print(readSoil());

  int sensorValue = readSoil();
  Serial.println(sensorValue);
  
  delay(1000);//take a reading every second. For in-plant applications, you will want to take readings much less frequently.

  if (sensorValue <= threshold){
    digitalWrite (pump, HIGH);
  } else {
    digitalWrite (pump, LOW);
  }
  
}

//This is a function used to get the soil moisture content
int readSoil() {
    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(10);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value
}
