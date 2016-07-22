#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Bounce.h"
#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

Time t;
String telefonNumber = "00000000000";

int orario_on;
const int HOUR_INITIAL_TIME = 19;
const int HOUR_END_TIME = 20;
const int MIN_INITIAL_TIME = 01;
const int MIN_END_TIME = 45;

// declare alarm pin

const int alarm1_Pin = 2;
const int alarm2_Pin = 3;
const int alarm3_Pin = 4;
const int alarm4_Pin = 5;

// declare LED pin

const int led1_Pin = 8;
const int led2_Pin = 9;
const int led3_Pin = 10;
const int led4_Pin = 11;
const int led5_Pin = 13;

// Instantiate a Alarm Bounce object with a 5 millisecond debounce time
Bounce alarm1 = Bounce( alarm1_Pin,150);
Bounce alarm2 = Bounce( alarm2_Pin,150);
Bounce alarm3 = Bounce( alarm3_Pin,150);
Bounce alarm4 = Bounce( alarm4_Pin,150);

void setup()
{
  
  Serial.begin(9600);

  rtc.begin();
  
  // initialize the pushbutton alarm pin as an input:
   pinMode(alarm1_Pin, INPUT);
   pinMode(alarm2_Pin, INPUT);
   pinMode(alarm3_Pin, INPUT);
   pinMode(alarm4_Pin, INPUT);

   pinMode(led1_Pin, OUTPUT);
   pinMode(led2_Pin, OUTPUT);
   pinMode(led3_Pin, OUTPUT);
   pinMode(led4_Pin, OUTPUT);
   pinMode(led5_Pin, OUTPUT);
  
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014

}

void loop()
{
  // read the state of the pushbutton value:
	alarm1.update();
	alarm2.update();
	alarm3.update();
	//alarm4.update();

	int alarm1Value = alarm1.read();
	int alarm2Value = alarm2.read();
	int alarm3Value = alarm3.read();
//int alarm4Value = alarm4.read();
  
  t = rtc.getTime();
  
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr(FORMAT_SHORT));
  
  // Serial.print(t.hour, DEC);
  
  orario_on = t.hour;
  
  if ( orario_on >= HOUR_INITIAL_TIME && < HOUR_END_TIME ) 
     {
        Serial.print("\n We are inside in hour Test Time window");
        
        if ( t.min > MIN_INITIAL_TIME && t.min < MIN_END_TIME)
        {
          Serial.print("\n We are inside in minuts Test Time Window");
        }
             
     }
  
 
  delay (1000);
  Serial.print("\n\n");
  Serial.print("Chip Temperature: ");
  Serial.print(rtc.getTemp());
  Serial.println(" C\n");
  delay (10000);
  
}
