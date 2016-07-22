#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Bounce.h"
//#include <TC74.h>
#include "PduEncoder.h"




//String resultingPDU;
//String sendedPDU;
String telefonNumber = "00000000000";
String hdsInit = "02";
const int endMsg = 4500;
const int endAlarm = 1000;

//TC74 sensor(5);

//PduEncoder MyPDU;
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




void setup() {

//delay(2000);



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

//Initialize GH688

   Serial.begin(9600);



}

void loop() {


	// read the state of the pushbutton value:
	alarm1.update();
	alarm2.update();
	alarm3.update();
	//alarm4.update();

	int alarm1Value = alarm1.read();
	int alarm2Value = alarm2.read();
	int alarm3Value = alarm3.read();
	//int alarm4Value = alarm4.read();

	// as result send appropriate ring number with Hayes code
	//delay(5000);



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











