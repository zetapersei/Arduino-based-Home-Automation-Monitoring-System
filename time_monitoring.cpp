
#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

Time t;

int orario_on;
const int HOUR_INITIAL_TIME = 19;
const int HOUR_END_TIME = 20;
const int MIN_INITIAL_TIME = 01;
const int MIN_END_TIME = 45;

void setup()
{
  
  Serial.begin(9600);
  
  
  rtc.begin();
  
  
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014

}

void loop()
{
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
