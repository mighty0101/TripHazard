#include <FastLED.h>

#include <Wire.h>

#define SLAVE_ADDRESS 0x08
#define buzzPin 49

// FastLED
#define LED_PIN     10
#define NUM_LEDS    144
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRBq  
#define UPDATES_PER_SECOND 100
CRGB leds[NUM_LEDS];

// End FastLED


volatile boolean receiveFlag = false;
char temp[32];
String command;


//######  Assign Motor Controller Variables to pin numbers

//Motor 4
  int M4__RPWM = 2;  // Digital/PWM pin 5 to the M4__RPWM on the BTS7960
  int M4__LPWM = 3;  // Digital/PWM pin 6 to the M4__LPWM on the BTS7960
  int M4__L_EN = 22;  // connect Digital/PWM pin 7 to M4__L_EN on the BTS7960
  int M4__R_EN = 23;  // connect Digital/PWM pin 8 to M4__R_EN on the BTS7960

//Motor 3
  int M3__RPWM = 4;  // Digital/PWM pin 5 to the M4__RPWM on the BTS7960
  int M3__LPWM = 5;  // Digital/PWM pin 6 to the M4__LPWM on the BTS7960
  int M3__L_EN = 24;  // connect Digital/PWM pin 7 to M4__L_EN on the BTS7960
  int M3__R_EN = 25;  // connect Digital/PWM pin 8 to M4__R_EN on the BTS7960
  
//Motor 2
  int M2__RPWM = 6;  // Digital/PWM pin 5 to the M4__RPWM on the BTS7960
  int M2__LPWM = 7;  // Digital/PWM pin 6 to the M4__LPWM on the BTS7960
  int M2__L_EN = 26;  // connect Digital/PWM pin 7 to M4__L_EN on the BTS7960
  int M2__R_EN = 27;  // connect Digital/PWM pin 8 to M4__R_EN on the BTS7960
 
//Motor 1
  int M1__RPWM = 8;  // Digital/PWM pin 5 to the M4__RPWM on the BTS7960
  int M1__LPWM = 9;  // Digital/PWM pin 6 to the M4__LPWM on the BTS7960
  int M1__L_EN = 28;  // connect Digital/PWM pin 7 to M4__L_EN on the BTS7960
  int M1__R_EN = 29;  // connect Digital/PWM pin 8 to M4__R_EN on the BTS7960



// constants won't change
const int RELAY_PIN0 = 30;  
const int RELAY_PIN1 = 31;  
const int RELAY_PIN2 = 32;  
const int RELAY_PIN3 = 33;  
const int RELAY_PIN4 = 34;  
const int RELAY_PIN5 = 35;  
const int RELAY_PIN6 = 36;  
const int RELAY_PIN7 = 37;



void setup() {
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);
  Serial.println("TripHazard Mega Ready");
  // end i2c initialization

  // Setup Relay Pins
  pinMode(RELAY_PIN0, OUTPUT);
  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);
  pinMode(RELAY_PIN3, OUTPUT);
  pinMode(RELAY_PIN4, OUTPUT);
  pinMode(RELAY_PIN5, OUTPUT);
  pinMode(RELAY_PIN6, OUTPUT);
  pinMode(RELAY_PIN7, OUTPUT);

  digitalWrite(RELAY_PIN0, HIGH);
  digitalWrite(RELAY_PIN1, HIGH);
  digitalWrite(RELAY_PIN2, LOW);
  digitalWrite(RELAY_PIN3, HIGH);
  digitalWrite(RELAY_PIN4, HIGH);
  digitalWrite(RELAY_PIN5, HIGH);
  digitalWrite(RELAY_PIN6, HIGH);
  digitalWrite(RELAY_PIN7, HIGH);
  //############ end Relay Setup  #####################

  //############  MOTOR DRIVER SETUP  #####################

//######  BEGIN Motor-4 pins initialization
    pinMode(M4__RPWM, OUTPUT);
    pinMode(M4__LPWM, OUTPUT);
    pinMode(M4__L_EN, OUTPUT);
    pinMode(M4__R_EN, OUTPUT);

  // set all the pins to LOW

    digitalWrite(M4__RPWM, LOW);
    digitalWrite(M4__LPWM, LOW);
    digitalWrite(M4__L_EN, LOW);
    digitalWrite(M4__R_EN, LOW);
//######  END Motor-4 pins initialization

    
//######  BEGIN Motor-3 pins initialization
    pinMode(M3__RPWM, OUTPUT);
    pinMode(M3__LPWM, OUTPUT);
    pinMode(M3__L_EN, OUTPUT);
    pinMode(M3__R_EN, OUTPUT);

  // set all the pins to LOW

    digitalWrite(M3__RPWM, LOW);
    digitalWrite(M3__LPWM, LOW);
    digitalWrite(M3__L_EN, LOW);
    digitalWrite(M3__R_EN, LOW);
//######  END Motor-3 pins initialization

    
//######  BEGIN Motor-2 pins initialization
    pinMode(M2__RPWM, OUTPUT);
    pinMode(M2__LPWM, OUTPUT);
    pinMode(M2__L_EN, OUTPUT);
    pinMode(M2__R_EN, OUTPUT);

  // set all the pins to LOW

    digitalWrite(M2__RPWM, LOW);
    digitalWrite(M2__LPWM, LOW);
    digitalWrite(M2__L_EN, LOW);
    digitalWrite(M2__R_EN, LOW);
//######  END Motor-2 pins initialization

    
//######  BEGIN Motor-1 pins initialization
    pinMode(M1__RPWM, OUTPUT);
    pinMode(M1__LPWM, OUTPUT);
    pinMode(M1__L_EN, OUTPUT);
    pinMode(M1__R_EN, OUTPUT);

  // set all the pins to LOW

    digitalWrite(M1__RPWM, LOW);
    digitalWrite(M1__LPWM, LOW);
    digitalWrite(M1__L_EN, LOW);
    digitalWrite(M1__R_EN, LOW);
//######  END Motor-1 pins initialization

  
 //FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
 //FastLED.setBrightness(BRIGHTNESS);

  
}

void loop() {



if (receiveFlag == true) {
    Serial.println(temp);
    String tempString(temp);





if (tempString == "lighton")                             // ############# Relay 7 Activated ##############
       {
       Serial.println("Turning on the headlight");
       digitalWrite(RELAY_PIN7, LOW);
       }     


if (tempString == "lightoff")                            // ############# Relay 7 Deactivataed ##############
       {
       Serial.println("Turning off the headlight");
       digitalWrite(RELAY_PIN7, HIGH);
       }

       
if (tempString == "relay6on")                            //  ############# Relay 6 Activated ##############
       {
       Serial.println("Relay 6 on");
       digitalWrite(RELAY_PIN6, LOW);
       }

       
if (tempString == "relay6off")                            //  ############# Relay 6 Deactivated ##############
       {
       Serial.println("Relay 6 off");
       digitalWrite(RELAY_PIN6, HIGH);
       }

       if (tempString == "relay5on")                            //  ############# Relay 5 Activated ##############
       {
       Serial.println("Relay 5 on");
       digitalWrite(RELAY_PIN5, LOW);
       }

       
if (tempString == "relay5off")                            //  ############# Relay 5 Deactivated ##############
       {
       Serial.println("Relay 5 off");
       digitalWrite(RELAY_PIN5, HIGH);
       }


if (tempString == "relay4on")                            //  ############# Relay 4 Activated ##############
       {
       Serial.println("Relay 4 on");
       digitalWrite(RELAY_PIN4, LOW);
       }

       
if (tempString == "relay4off")                            //  ############# Relay 4 Deactivated ##############
       {
       Serial.println("Relay 4 off");
       digitalWrite(RELAY_PIN4, HIGH);
       }


if (tempString == "relay3on")                            //  ############# Relay 3 Activated ##############
       {
       Serial.println("Relay 3 on");
       digitalWrite(RELAY_PIN3, LOW);
       }

       
if (tempString == "relay3off")                            //  ############# Relay 3  Deactivated ##############
       {
       Serial.println("Relay 3 off");
       digitalWrite(RELAY_PIN3, HIGH);
       }


if (tempString == "screenon")                            //  ############# Relay 2 Activated ##############
       {
       Serial.println("Relay 2 on");
       digitalWrite(RELAY_PIN2, LOW);
       }

       
if (tempString == "screenoff")                            //  ############# Relay 2 Deactivated ##############
       {
       Serial.println("Relay 2 off");
       digitalWrite(RELAY_PIN2, HIGH);
       }


if (tempString == "relay1on")                            //  ############# Relay 1 Activated ##############
       {
       Serial.println("Relay 1 on");
       digitalWrite(RELAY_PIN1, LOW);
       }

       
if (tempString == "relay1off")                            //  ############# Relay 1 Deactivated ##############
       {
       Serial.println("Relay 1 off");
       digitalWrite(RELAY_PIN1, HIGH);
       }


if (tempString == "relay0on")                            //  ############# Relay 0 Activated ##############
       {
       Serial.println("Relay 0 on");
       digitalWrite(RELAY_PIN0, LOW);
       }

       
if (tempString == "relay0off")                            //  ############# Relay 0 Deactivated ##############
       {
       Serial.println("Relay 0 off");
       digitalWrite(RELAY_PIN0, HIGH);
       }



if (tempString == "hello")
       {
       Serial.println("What do you want, human?");
       }



if (tempString == "nigga")
       {
       
       }


if (tempString == "reset")
       {
       digitalWrite(RELAY_PIN0, HIGH);
       digitalWrite(RELAY_PIN1, HIGH);
       digitalWrite(RELAY_PIN2, LOW);
       digitalWrite(RELAY_PIN3, HIGH);
       digitalWrite(RELAY_PIN4, HIGH);
       digitalWrite(RELAY_PIN5, HIGH);
       digitalWrite(RELAY_PIN6, HIGH);
       digitalWrite(RELAY_PIN7, HIGH);
       }

       
if (tempString == "motor2test")
       {
       motorctl();
       
       }

       


       
if (tempString == "beep")
       {
       tone(buzzPin,587.33,400);
       delay(150);
       tone(buzzPin,554.37,300);
       delay(100);
       tone(buzzPin,800,300);
       }
       
       receiveFlag = false;
  }

}


/*oid moving_three_led() {
  for (int i = 0; i < NUM_LEDS; i++) {
 int x = 71+i;
 int y = 70-i;
//int  y = (x - i);   
  //  leds[i]     = CRGB::White;
    leds[i] = CRGB::Red;
    leds[y] = CRGB::Red;
  //  leds[i + 2] = CRGB::Red;
   // leds[i + 3] = CRGB::Blue;
     delay(5);
     //leds[i] = CRGB::Black;
   
    FastLED.show();
   // delay(50);
  //  for (int i = 0; i < NUM_LEDS; i++) {
    //  leds[i] = CRGB::Black;
      //delay(5);
   }
   
  }
}
*/


void receiveEvent(int howMany) {

  for (int i = 0; i < howMany; i++) {
    temp[i] = Wire.read();
    temp[i + 1] = '\0'; //add null after ea. char
  }

  //RPi first byte is cmd byte so shift everything to the left 1 pos so temp contains our string
  for (int i = 0; i < howMany; ++i)
    temp[i] = temp[i + 1];
          
  receiveFlag = true;

}


void motorctl() {

/*
 put your main code here, to run repeatedly:

  // Use an analogWrite(pin,  which tells it to send a modulated
  // signal (PWM) to specific pin at a specific "duty cycle".
  // Valid values are 0 to 255.  0 means always off(or no power) and 255 means always on(full power)
  // https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
  analogWrite(M4__RPWM, 64); // pulse a signal continually at the rate of 64 
  // the analogWrite line above should start the motor turning in one direction at about 1/4 of power.
  delay(1000); // wait 5 seconds, motor continues to move because the analogWrite is still pulsing
  analogWrite(M4__RPWM, 128); // pulse signal now at 128 (about half power... half of max 255).
  delay(1000);
*/

/*

  // after 5 seconds at half power, stop the motor moving
  analogWrite(M4__RPWM, 0);
  delay(1000);
  // now start moving in opposite direction.
  analogWrite(M4__LPWM, 64);
  delay(1000);
  analogWrite(M4__LPWM, 128);
  delay(1000);
  analogWrite(M4__LPWM, 0); // Stop moving in this direction
  // at this point should be no movement.





 analogWrite(M3__RPWM, 64); // pulse a signal continually at the rate of 64 
  // the analogWrite line above should start the motor turning in one direction at about 1/4 of power.
  delay(1000); // wait 5 seconds, motor continues to move because the analogWrite is still pulsing
  analogWrite(M3__RPWM, 128); // pulse signal now at 128 (about half power... half of max 255).
  delay(1000);

  // after 5 seconds at half power, stop the motor moving
  analogWrite(M3__RPWM, 0);
  delay(1000);
  // now start moving in opposite direction.
  analogWrite(M3__LPWM, 64);
  delay(1000);
  analogWrite(M3__LPWM, 128);
  delay(1000);
  analogWrite(M3__LPWM, 0); // Stop moving in this direction
  // at this point should be no movement.
  

 analogWrite(M2__RPWM, 64); // pulse a signal continually at the rate of 64 
  // the analogWrite line above should start the motor turning in one direction at about 1/4 of power.
  delay(1000); // wait 5 seconds, motor continues to move because the analogWrite is still pulsing
  analogWrite(M2__RPWM, 128); // pulse signal now at 128 (about half power... half of max 255).
  delay(1000);

  // after 5 seconds at half power, stop the motor moving
  analogWrite(M2__RPWM, 0);
  delay(1000);
  // now start moving in opposite direction.
  analogWrite(M2__LPWM, 64);
  delay(1000);
  analogWrite(M2__LPWM, 128);
  delay(1000);
  analogWrite(M2__LPWM, 0); // Stop moving in this direction
  // at this point should be no movement

*/
  
 analogWrite(M1__RPWM, 64); // pulse a signal continually at the rate of 64 
  // the analogWrite line above should start the motor turning in one direction at about 1/4 of power.
  delay(1000); // wait 5 seconds, motor continues to move because the analogWrite is still pulsing
  analogWrite(M1__RPWM, 128); // pulse signal now at 128 (about half power... half of max 255).
  delay(1000);

  // after 5 seconds at half power, stop the motor moving
  analogWrite(M1__RPWM, 0);
  delay(1000);
  // now start moving in opposite direction.
  analogWrite(M1__LPWM, 64);
  delay(1000);
  analogWrite(M1__LPWM, 128);
  delay(1000);
  analogWrite(M1__LPWM, 0); // Stop moving in this direction
  // at this point should be no movement.
  
  delay(1000);

}
