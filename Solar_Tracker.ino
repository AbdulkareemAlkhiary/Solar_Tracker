#include <LiquidCrystal.h> //Import LCD Library
#include <Servo.h> // Import Servo Library

LiquidCrystal LcdDriver(11, 9, 5, 6, 7, 8); // Defines for LCD
Servo myservo;  // create servo object to control a servo

int pot1pin = A3;  // analog pin used to connect the sensor
int pot2pin = A2;  // analog pin used to connect the sensor
int pos = 0; // Initial value for position of servo
float pot1val; // Creating potentiometer variable
float pot2val; // Creating potentiometer variable
unsigned long Timer1; // Timer1 variabl
unsigned long Timer2; // Timer2 variable
unsigned long Timer3; // Timer3 variable
int dayTime = 12; // dayTime integer
int realAngle = 0; // Angle integer
String input; // Input String
int seconds; // seconds integer
boolean count = false; // Counting true/false

void setup() { // Setup
  
  LcdDriver.begin(16, 2); // Begin LCD Driver
  Serial.begin(9600); // Begin Serial
  Timer1 = millis(); // Set Timer1 millis
  Timer2 = millis(); // Set Timer2 millis
  Timer3 = millis(); // Set Timer3 millis

  pot1val = analogRead(pot1pin); // Read potentiometer values
  pot2val = analogRead(pot2pin); // Read potentiometer values
  myservo.attach(10);  // Attaches Servo to pin
  pos = 90; // Initial position (Middle)

}

void loop() { // Loop

  if (Serial.available() != 0) { // If something is in the Serial
    input = Serial.readString(); // Read input from Serial

    if (input == "6AM" || input ==  "6 AM") { // All of these are pretty self-explanatory
      pos = 180;
    } else if (input == "7AM" || input ==  "7 AM") { // "   "
      pos = 165;
    } else if (input == "8AM" || input ==  "8 AM") { // "   "
      pos = 150;
    } else if (input == "9AM" || input ==  "9 AM") { // "   "
      pos = 135;
    } else if (input == "10AM" || input ==  "11 AM") { // "   "
      pos = 120;
    } else if (input == "12PM" || input ==  "12 PM") { // "   "
      pos = 105;
    } else if (input == "1PM" || input ==  "1 PM") { // "   "
      pos = 90;
    } else if (input == "2PM" || input ==  "2 PM") { // "   "
      pos = 75;
    } else if (input == "3PM" || input ==  "3 PM") { // "   "
      pos = 60;
    } else if (input == "4PM" || input ==  "4 PM") { // "   "
      pos = 45;
    } else if (input == "5PM" || input ==  "5 PM") { // "   "
      pos = 30;
    } else if (input == "6PM" || input ==  "6 PM") { // "   "
      pos = 15;
    }
  }

  pot1val = pot1val - pot2val; // Correction for some offset in the potentiometers

  /* // Reading of data to Serial. Testing of values
    Serial.print("POS: ");
    Serial.print(pos); // Log the sensor value
    Serial.print(" | POT1VAL: ");
    Serial.print(pot1val); // Log the sensor value
    Serial.print(" | POT2VAL: ");
    Serial.println(pot2val); // Log the sensor value
  */

  if ( millis() - Timer3 >= 1000) { // Timer of 1 second
    if (count == true) { // If told to count
      seconds ++; //  Add second
      if (seconds > 240) { // If 240 seconds AKA 4 minutes
        pos -= 1; // Increment once (In clockwise direction)
        seconds = 0; // Reset seconds back to 0
      }
    }
    Timer3 += 1000; // Add back to Timer
  }

  if ( millis() - Timer1 >= 30) { // Timer of 30 ms

    if (pot1val < pot2val && count == false) { // If left pot is brighter
      pos += 1; // Increment in counter-clockwise direction
    } else if (pot1val > pot2val && count == false) { // If right pot if brighter
      pos -= 1; // Increment in clock-wise direction
    }

    if (pot1val > 200 && pot2val > 200) { // If light is insufficient
      count = true; // Start counting
    } else {
      count = false; // Don't count
    }



    if (pos < 0) { // If position is less than 0 degrees
      pos = 180; // Move to max min left side
    } else if ( pos > 180) { //  If more than right side
      pos = 180; // Move to max right side
    }
    Timer1 += 30; // Add back to Timer
  }
  if ( millis() - Timer2 >= 300) { // Timer of 300 ms

    LcdDriver.clear(); // Clear LCD screen
    if (dayTime > 12) { // If dayTime is bigger than 12
      dayTime = 1; // Reset back to 1
    }

    realAngle = -pos + 180; // Calculation to get angle from position

    if (realAngle >= 0 && realAngle <= 7.5) { // If real angle is between values (*)
      dayTime = 6; // Set dayTime corresponding time of day to value (#)

    } else if (realAngle >= 7.5 && realAngle <= 22.5) { // (*)
      dayTime = 7; // (#)

    } else if (realAngle >= 22.5 && realAngle <= 37.5) { // (*)
      dayTime = 8; // (#)

    } else if (realAngle >= 37.5 && realAngle <= 52.5) { // (*)
      dayTime = 9; // (#)

    } else if (realAngle >= 52.5 && realAngle <= 67.5) { // (*)
      dayTime = 10; // (#)

    } else if (realAngle >= 67.5 && realAngle <= 82.5) { // (*)
      dayTime = 11; // (#)

    } else if (realAngle >= 82.5 && realAngle <= 97.5) { // (*)
      dayTime = 12; // (#)

    } else if (realAngle >= 97.5 && realAngle <= 112.5) { // (*)
      dayTime = 1; // (#)

    } else if (realAngle >= 112.5 && realAngle <= 127.5) { // (*)
      dayTime = 2; // (#)

    } else if (realAngle >= 127.5 && realAngle <= 142.5) { // (*)
      dayTime = 3; // (#)

    } else if (realAngle >= 142.5 && realAngle <= 157.5) { // (*)
      dayTime = 4; // (#)

    } else if (realAngle >= 157.5 && realAngle <= 172.5) { // (*)
      dayTime = 5; // (#)

    } else if (realAngle >= 172.5 && realAngle <= 180) { // (*)
      dayTime = 6; // (#)
    }

    LcdDriver.setCursor(0, 0); // Set cursor on LCD
    LcdDriver.print("Time: "); // Print String onto LCD
    LcdDriver.print(dayTime); // Print dayTime onto LCD
    
    if (realAngle > 90) { // If realAngle is above 90 degrees
      LcdDriver.print(" PM"); // It is PM
    } else {
      LcdDriver.print(" AM"); // Iit is AM
    }

    LcdDriver.setCursor(0, 1); // Set cursor on LCD (Second line now)
    LcdDriver.print("Angle: "); // Print String onto LCD
    LcdDriver.print(realAngle); // Print Angle onto LCD
    Timer2 += 300; // Add time to Timer
  }
  // pos = max(0,pos); pos = min(180,pos); // Confine to limits. Test
  myservo.write(pos); // Make servo to to position
  pot1val = 0; // Reset potentiometer value
  pot2val = 0; // "  "
  for (int i = 0; i < 20; i++) { // Get an average reading
    pot1val += analogRead(pot1pin) / 20.0;
  } for (int p = 0; p < 20; p++) {
    pot2val += analogRead(pot2pin) / 20.0;
  }
}
