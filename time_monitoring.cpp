/* 
*************************************************************************
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS 
   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
   TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
   PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT 
   HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
   OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF THE COPYRIGHT HOLDERS OR 
   CONTRIBUTORS ARE AWARE OF THE POSSIBILITY OF SUCH DAMAGE.
************************************************************************
*/

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
String atCmdSetText = "AT+CMGF=1";
String atCmdSendSms = "AT+CMGS=";

const char CR = 13;
const char CTRLZ = 26;
const char ESCP = 27;
const char SPACE = 32;
const char VIRGO = 34;

const int HOUR_INITIAL_TIME = 12;
const int HOUR_END_TIME = 13;
const int MIN_INITIAL_TIME = 10;
const int MIN_END_TIME = 59;
const int endAlarm = 1000;

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

  Serial.print(atCmdSetText + CR);
  

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
  //Serial.print(rtc.getDOWStr());
  //Serial.print(" ");
  
  // Send date
  //Serial.print(rtc.getDateStr());
  //Serial.print(" -- ");

  // Send time
  //Serial.println(rtc.getTimeStr(FORMAT_SHORT));
  
  // Serial.print(t.hour, DEC);
  
  if (alarm1Value == HIGH) {

	      digitalWrite(led1_Pin, HIGH );



	      Serial.println("ATD"+telefonNumber+";");
	      delay(25000); // Ring for four times
	      Serial.println("ATH");

		  while  (!alarm1.update()){
			;    }
		  delay(endAlarm);

		  Serial.println("ATD"+telefonNumber+";");
		  	      delay(25000); // Ring for four times at alarm release
	                             // only for power monitoring
		  	      Serial.println("ATH");

}

else {
	      digitalWrite(led1_Pin, LOW );
	  }


if (alarm2Value == HIGH) {

			  digitalWrite(led2_Pin, HIGH );


			  Serial.println("ATD"+telefonNumber+";");
			  delay(30000); // ring for six times
			  Serial.println("ATH");

			   	while  (!alarm2.update()){
			   				;    }
			   	delay(endAlarm);
	  }

else {
	  	      digitalWrite(led2_Pin, LOW );
	  }

if (alarm3Value == HIGH) {

	digitalWrite(led3_Pin, HIGH );



	Serial.println("ATD"+telefonNumber+";");
	delay(50000); // ring for ten times
	Serial.println("ATH");

			    while  (!alarm3.update()){
			    ;    }
			    delay(endAlarm);
	  	   }
else {
	  	  	digitalWrite(led3_Pin, LOW );
	  	   }



/*
if (alarm4Value == HIGH) {
Serial.println("ATD"+telefonNumber+";");
delay(23500); // ring four times
Serial.println("ATH");
	  		digitalWrite(led4_Pin, HIGH );
	  	   }
else {
	  	  	digitalWrite(led4_Pin, LOW );
	  	  }
*/
}

  
/*  switch (alarm1Value) {
      case LOW:
        if ( t.hour >= HOUR_INITIAL_TIME && t.hour < HOUR_END_TIME && t.min > MIN_INITIAL_TIME && t.min < MIN_END_TIME) 
           {
      
            Serial.print(atCmdSendSms + VIRGO + telefonNumber + VIRGO + CR );
            Serial.print("Device 1 not active");
            Serial.print(CTRLZ);
            Serial.print(ESCP);
              while  (alarm1.update()){
                ;    }     
            }
        
        break;
      case HIGH:
          if ( t.hour <= HOUR_INITIAL_TIME && t.hour > HOUR_END_TIME && t.min < MIN_INITIAL_TIME && t.min > MIN_END_TIME) 
           {
      
            Serial.print(atCmdSendSms + VIRGO + telefonNumber + VIRGO + CR );
            Serial.print("Device 1 active out time window");
            Serial.print(CTRLZ);
            Serial.print(ESCP);
              while  (!alarm1.update()){
                ;    }
                   
            }
            
           break;                  
        }
 
  
} */
