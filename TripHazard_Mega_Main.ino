#include <FastLED.h>

#include <Wire.h>

#define SLAVE_ADDRESS 0x08
#define buzzPin 49



volatile boolean receiveFlag = false;
char temp[32];
String command;


//######  Assign Motor Controller Variables to pin numbers
/*
//Motor 4
  int M4__RPWM = 2;  // Digital/PWM pin 5 to the M4__RPWM on the BTS7960
  int M4__LPWM = 3;  // Digital/PWM pin 6 to the M2__LPWM on the BTS7960
  int M4__L_EN = 22;  // connect Digital/PWM pin 7 to M2__L_EN on the BTS7960
  int M4__R_EN = 23;  // connect Digital/PWM pin 8 to M2__R_EN on the BTS7960
*/
//Motor 2
  int M2__RPWM = 4;  // Green
  int M2__LPWM = 5;  // Grey
  int M2__L_EN = 24;  // White
  int M2__R_EN = 25;  // Blue
 
//Motor 4
  int M4__RPWM = 6;  // Digital/PWM pin 5 to the M4__RPWM on the BTS7960
  int M4__LPWM = 7;  // Digital/PWM pin 6 to the M2__LPWM on the BTS7960
  int M4__L_EN = 26;  // connect Digital/PWM pin 7 to M2__L_EN on the BTS7960
  int M4__R_EN = 27;  // connect Digital/PWM pin 8 to M2__R_EN on the BTS7960
 
//Motor 1
  int M1__RPWM = 8;  // Digital/PWM pin 5 to the M4__RPWM on the BTS7960
  int M1__LPWM = 9;  // Digital/PWM pin 6 to the M2__LPWM on the BTS7960
  int M1__L_EN = 28;  // connect Digital/PWM pin 7 to M2__L_EN on the BTS7960
  int M1__R_EN = 29;  // connect Digital/PWM pin 8 to M2__R_EN on the BTS7960



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

//######  BEGIN Motor-4 pins initialization
    pinMode(M2__RPWM, OUTPUT);
    pinMode(M2__LPWM, OUTPUT);
    pinMode(M2__L_EN, OUTPUT);
    pinMode(M2__R_EN, OUTPUT);

  // set all the pins to LOW

    digitalWrite(M2__RPWM, LOW);
    digitalWrite(M2__LPWM, LOW);
    digitalWrite(M2__L_EN, LOW);
    digitalWrite(M2__R_EN, LOW);
//######  END Motor-4 pins initialization

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

    



  delay(1000);// wait a second
  Serial.begin(9600);
  
  //enable "Right" and "Left" movement on the HBridge
  // Notice use of digitalWrite to simply turn it on and keep it on.


  digitalWrite(M4__R_EN, HIGH);  
  digitalWrite(M4__L_EN, HIGH); 
  
  digitalWrite(M2__R_EN, HIGH);  
  digitalWrite(M2__L_EN, HIGH);
  
  digitalWrite(M1__R_EN, HIGH);  
  digitalWrite(M1__L_EN, HIGH);



  
}

void loop() {




  if (receiveFlag == true) {
        //Serial.println(temp);
        String tempString(temp);


        String command = getValue(tempString,';',0);
        String subCommand1 = getValue(tempString,';',1);
        String subCommand2 = getValue(tempString,';',2);
        String subCommand3 = getValue(tempString,';',3);
        String subCommand4 = getValue(tempString,';',4);
        String subCommand5 = getValue(tempString,';',5);
        
        Serial.println("\n\n\n\n**************************");
        Serial.println("--Mega incoming commands--"); 
        Serial.println("**************************\n");
        Serial.println("command = " + command);
        Serial.println("\n\nsubCommand1 = "+ subCommand1);
        Serial.println("\nsubCommand2 = " + subCommand2);
        Serial.println("\nsubCommand3 = "+ subCommand3);
        Serial.println("\nsubCommand4 = "+ subCommand4);
        Serial.println("\nsubCommand5 = "+ subCommand5 + "\n\n");
     


if (command == "lighton")                             // ############# Relay 7 Activated ##############
       {
       Serial.println("Turning on the headlight");
       digitalWrite(RELAY_PIN7, LOW);
       }     


if (command == "lightoff")                            // ############# Relay 7 Deactivataed ##############
       {
       Serial.println("Turning off the headlight");
       digitalWrite(RELAY_PIN7, HIGH);
       }

       
if (command == "relay6on")                            //  ############# Relay 6 Activated ##############
       {
       Serial.println("Relay 6 on");
       digitalWrite(RELAY_PIN6, LOW);
       }

       
if (command == "relay6off")                            //  ############# Relay 6 Deactivated ##############
       {
       Serial.println("Relay 6 off");
       digitalWrite(RELAY_PIN6, HIGH);
       }

       if (tempString == "relay5on")                            //  ############# Relay 5 Activated ##############
       {
       Serial.println("Relay 5 on");
       digitalWrite(RELAY_PIN5, LOW);
       }

       
if (command == "relay5off")                            //  ############# Relay 5 Deactivated ##############
       {
       Serial.println("Relay 5 off");
       digitalWrite(RELAY_PIN5, HIGH);
       }


if (command == "relay4on")                            //  ############# Relay 4 Activated ##############
       {
       Serial.println("Relay 4 on");
       digitalWrite(RELAY_PIN4, LOW);
       }

       
if (command == "relay4off")                            //  ############# Relay 4 Deactivated ##############
       {
       Serial.println("Relay 4 off");
       digitalWrite(RELAY_PIN4, HIGH);
       }


if (command == "relay3on")                            //  ############# Relay 3 Activated ##############
       {
       Serial.println("Relay 3 on");
       digitalWrite(RELAY_PIN3, LOW);
       }

       
if (command == "relay3off")                            //  ############# Relay 3  Deactivated ##############
       {
       Serial.println("Relay 3 off");
       digitalWrite(RELAY_PIN3, HIGH);
       }


if (command == "screenon")                            //  ############# Relay 2 Activated ##############
       {
       Serial.println("Relay 2 on");
       digitalWrite(RELAY_PIN2, LOW);
       }

       
if (command == "screenoff")                            //  ############# Relay 2 Deactivated ##############
       {
       Serial.println("Relay 2 off");
       digitalWrite(RELAY_PIN2, HIGH);
       }


if (command == "relay1on")                            //  ############# Relay 1 Activated ##############
       {
       Serial.println("Relay 1 on");
       digitalWrite(RELAY_PIN1, LOW);
       }

       
if (command == "relay1off")                            //  ############# Relay 1 Deactivated ##############
       {
       Serial.println("Relay 1 off");
       digitalWrite(RELAY_PIN1, HIGH);
       }


if (command == "relay0on")                            //  ############# Relay 0 Activated ##############
       {
       Serial.println("Relay 0 on");
       digitalWrite(RELAY_PIN0, LOW);
       }

       
if (command == "relay0off")                            //  ############# Relay 0 Deactivated ##############
       {
       Serial.println("Relay 0 off");
       digitalWrite(RELAY_PIN0, HIGH);
       }


if (command == "hello")
       {
       Serial.println("What do you want, human?");
       }


if (command == "reset")
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

       
if (command == "motortest")
       {
       motortest();       
       }

       
if (command == "beep")
       {
        Serial.println("beep");
       tone(buzzPin,587.33,400);
       delay(150);
       tone(buzzPin,554.37,300);
       delay(100);
       tone(buzzPin,800,300);
       }
       
       receiveFlag = false;
  }

}



//################  Break incoming data String into multiple chunks ###################

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


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


void motortest() {

  // Motor 4
  Serial.println("motor 4 start forward");
  analogWrite(M4__RPWM, 64);     
  delay(3000);                  
  analogWrite(M4__RPWM, 128);    
  delay(3000);                   
  analogWrite(M4__RPWM, 0);      
  Serial.println("motor 4 stop\n");
  Serial.println("Wait for 2 seconds...\n");
  delay(2000);

  // start moving in opposite direction.
  Serial.println("motor 4 start reverse");
  analogWrite(M4__LPWM, 64);
  delay(3000);
  analogWrite(M4__LPWM, 128);
  delay(3000);
  analogWrite(M4__LPWM, 0); 
  Serial.println("motor 4 stop\n"); 
  Serial.println("Wait for 2 seconds...\n");
  delay(2000);  
  
  // Motor 2
  Serial.println("motor 2 start forward");
  analogWrite(M2__RPWM, 64);     
  delay(3000);                   
  analogWrite(M2__RPWM, 128);    
  delay(3000);                   
  analogWrite(M2__RPWM, 0);      
  Serial.println("motor 2 stop\n");
  Serial.println("Wait for 2 seconds...\n");
  delay(2000);

  // start moving in opposite direction.
  Serial.println("motor 2 start reverse\n");
  analogWrite(M2__LPWM, 64);
  delay(3000);
  analogWrite(M2__LPWM, 128);
  delay(3000);
  analogWrite(M2__LPWM, 0); 
  Serial.println("motor 2 stop\n"); 
  Serial.println("Wait for 2 seconds...\n");
  delay(2000); 
  
  // Motor 1
  Serial.println("motor 1 start forward");
  analogWrite(M1__RPWM, 64);     
  delay(3000);                   
  analogWrite(M1__RPWM, 128);    
  delay(3000);                   
  analogWrite(M1__RPWM, 0);      
  Serial.println("motor 1 stop\n");
  Serial.println("Wait for 2 seconds...\n");
  delay(2000);

  // start moving in opposite direction.
  Serial.println("motor 1 start reverse\n");
  analogWrite(M1__LPWM, 64);
  delay(3000);
  analogWrite(M1__LPWM, 128);
  delay(3000);
  analogWrite(M1__LPWM, 0); 
  Serial.println("motor 1 stop\n"); 
  Serial.println("Wait for 2 seconds...\n");
  delay(2000);

}
