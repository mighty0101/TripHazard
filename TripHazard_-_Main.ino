
/*
  ████████╗██████╗ ██╗██████╗ ██╗  ██╗ █████╗ ███████╗ █████╗ ██████╗ ██████╗ 
  ╚══██╔══╝██╔══██╗██║██╔══██╗██║  ██║██╔══██╗╚══███╔╝██╔══██╗██╔══██╗██╔══██╗
     ██║   ██████╔╝██║██████╔╝███████║███████║  ███╔╝ ███████║██████╔╝██║  ██║
     ██║   ██╔══██╗██║██╔═══╝ ██╔══██║██╔══██║ ███╔╝  ██╔══██║██╔══██╗██║  ██║
     ██║   ██║  ██║██║██║     ██║  ██║██║  ██║███████╗██║  ██║██║  ██║██████╔╝
     ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ 

###############################################################################
###############################################################################
#####                                                                     #####
#####                      Welcome to TripHazard V0.7                     #####
#####                      (Experimental, but stable)                     #####
#####                      Last edit: 3.20.22 5:13PM                      #####
#####                                                                     #####
###############################################################################
###############################################################################

*/


// Needed libraries
#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include <RobojaxBTS7960.h>
#include <stdio.h>
#include <string.h>

// Define shoulder stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define shoulderDirPin 2
#define shoulderStepPin 3
#define motorInterfaceType 1

//buzzPin!!!
#define buzzPin 53

#define shoulderEnablePin 51


// pins for motor 1
#define RPWM_2 4 // define pin 3 for RPWM pin (output)
#define LPWM_2 5 // define pin 6 for LPWM pin (output)
#define RPWM_3 6 // define pin 3 for RPWM pin (output)
#define LPWM_3 7 // define pin 6 for LPWM pin (output)
#define RPWM_4 8 // define pin 3 for RPWM pin (output)
#define LPWM_4 9 // define pin 6 for LPWM pin (output)
#define RPWM_1 10 // define pin 3 for RPWM pin (output)
#define LPWM_1 11 // define pin 6 for LPWM pin (output)


#define R_EN_1 0 // define pin 2 for R_EN pin (input)
#define R_IS_1 0 // define pin 5 for R_IS pin (output)
#define L_EN_1 0 // define pin 7 for L_EN pin (input)
#define L_IS_1 0 // define pin 8 for L_IS pin (output)
// motor 1 pins end here

/* pins for motor 2
#define RPWM_2 9 // define pin 9 for RPWM pin (output)
#define R_EN_2 10 // define pin 10 for R_EN pin (input)
#define R_IS_2 12 // define pin 12 for R_IS pin (output)

#define LPWM_2 11 // define pin 11 for LPWM pin (output)
#define L_EN_2 A0 // define pin 7 for L_EN pin (input)
#define L_IS_2 A1 // define pin 8 for L_IS pin (output)
// motor 2 pins end here
*/
  
/*
 * //Define Wheel Motor Pins
#define RPWM 10
#define LPWM 11
#define REN 8
#define LEN 9

 
//    Right Front Wheel Motor
#define RPWM 2
#define LPWM 3
//    Right Front Wheel Motor
*/
//#define RPWM 8
//#define LPWM 9
#define Forward 1
#define CForward 0
#define debug 0
/*
//    Right Rear Wheel Motor
#define RPWM 6
#define LPWM 7
*/

//   RobojaxBTS7960 motor_LR(1,8,1,1,9,1,0);
   RobojaxBTS7960 motor_LR(1,RPWM_1,R_IS_1, L_EN_1,LPWM_1,L_IS_1,debug);
   RobojaxBTS7960 motor_LF(1,RPWM_2,R_IS_1, L_EN_1,LPWM_2,L_IS_1,debug);
   RobojaxBTS7960 motor_RF(1,RPWM_3,R_IS_1, L_EN_1,LPWM_3,L_IS_1,debug);
   RobojaxBTS7960 motor_RR(1,RPWM_4,R_IS_1, L_EN_1,LPWM_4,L_IS_1,debug);
    
 

AccelStepper stepper = AccelStepper(motorInterfaceType, shoulderStepPin, shoulderDirPin);// Create a new instance of the AccelStepper class:

// Declare String Splitting Variables
         const byte numChars = 32;
         char receivedChars[numChars];
         char tempChars[numChars];        // temporary array for use when parsing
         
         // variables to hold the parsed data
         char commandFromPi[numChars] = {0};
         int integerFromPi = 0;
         float floatFromPi = 0.0;
         boolean newData = false;
 
String receivedCommand;
String receivedInteger;
String receivedFloat;


void setup() {

  Serial.begin(115200);
  Serial.setTimeout(1);
  
  stepper.setMaxSpeed(600);
  stepper.setAcceleration(800);
  
  pinMode(shoulderEnablePin, OUTPUT);
  digitalWrite(shoulderEnablePin, HIGH);
// Setup Complete Buzzer Sound
tone(buzzPin,587.33,400);
delay(150);
tone(buzzPin,554.37,300);
delay(100);
tone(buzzPin,800,300);


String combinedVars = "";
}
 
 
void loop() {



    recvWithStartEndMarkers();
        
        if (newData == true){
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            // because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
        }
  
            }


//################## Functions ##########################


void testMotors() {
                  // Test time!!
 
  // slowly speed up the Left-Rear motor from 0 to 100% speed
   for(int i=0; i<=100; i++){ 
        motor_LR.rotate(i,Forward);
         delay(50);
    } 
 
   // slow down the Left-Rear motor from 100% to 0 with 
    for(int i=100; i>0; i--){ 
        motor_LR.rotate(i,Forward);
       
        delay(50);
    }

      // slowly speed up the Right-Rear motor from 0 to 100% speed
   for(int i=0; i<=100; i++){ 
        motor_RR.rotate(i,Forward);
         delay(50);
    } 
 
   // slow down the Right-Rear motor from 100% to 0 with 
    for(int i=100; i>0; i--){ 
        motor_RR.rotate(i,Forward);
       
        delay(50);
    }
 
  // slowly speed up the Left-Front motor from 0 to 100% speed
   for(int i=0; i<=100; i++){ 
        motor_LF.rotate(i,Forward);
         delay(50);
    } 
 
   // slow down the Left-Front motor from 100% to 0 with 
    for(int i=100; i>0; i--){ 
        motor_LF.rotate(i,Forward);
       
        delay(50);
    } 
  // slowly speed up the Right-Front motor from 0 to 100% speed
   for(int i=0; i<=100; i++){ 
        motor_RF.rotate(i,Forward);
         delay(50);
    } 
 
   // slow down the Right-Front motor from 100% to 0 with 
    for(int i=100; i>0; i--){ 
        motor_RF.rotate(i,Forward);
       
        delay(50);
    }

//end Test time!!

                  }
                  
void lockMotors() {
                  digitalWrite(shoulderEnablePin, LOW);
                  }                   

                             
void unlockMotors() {
                  digitalWrite(shoulderEnablePin, HIGH);
                  }                


void shoulderMove(int len){
                  Serial.println(len);
                  digitalWrite(shoulderEnablePin, LOW);
                  int move;
                  //for (move = 0; move < len; move++)
                  stepper.moveTo(len);     // Set the target position:
                  stepper.runToPosition();  // Run to target position with set speed and acceleration/deceleration:
                  digitalWrite(shoulderEnablePin, HIGH);
                  }


void recvWithStartEndMarkers() {
                 static boolean recvInProgress = false;
                 static byte ndx = 0;
                 char startMarker = '<';
                 char endMarker = '>';
                 char rc;

                     while (Serial.available() > 0 && newData == false) {
                     rc = Serial.read();

                         if (recvInProgress == true) {                
                            if (rc != endMarker) {
                            receivedChars[ndx] = rc;
                            ndx++;
                            if (ndx >= numChars) {
                            ndx = numChars - 1;
                                                 }
                            }
                            
                   else {
                            receivedChars[ndx] = '\0'; // terminate the string
                            recvInProgress = false;
                            ndx = 0;
                            newData = true;
                        }
                   }

                   else if (rc == startMarker) {
                            recvInProgress = true;
                   }
    }
}


void parseData() {      // split the data into its parts
                  char * strtokIndx; // this is used by strtok() as an index
                  strtokIndx = strtok(tempChars,",");      // get the first part - the string
                  strcpy(commandFromPi, strtokIndx); // copy it to commandFromPi
                  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
                  integerFromPi = atoi(strtokIndx);     // convert this part to an integer
                  strtokIndx = strtok(NULL, ",");
                  floatFromPi = atof(strtokIndx);     // convert this part to a float
                 }


void showParsedData() {
                  String receivedCommand = String(commandFromPi);
                  int receivedInteger = int(integerFromPi);
                  int receivedFloat = int(floatFromPi);
                  
//################# received commands ########################

                
                  
                  
                  if(receivedCommand == "hello?"){
                  Serial.println("I'm still alive");
                  }                
                  
                  
                  if(receivedCommand == "shoulderMove"){
                    shoulderMove(integerFromPi);
                    
                  Serial.println("Shoulder moved to position: "+integerFromPi);
                  }

               
              
                  if(receivedCommand == "lockMotors"){
                    lockMotors(); 
                  Serial.println("Motors are Locked");
                  }                  
                  
                  
                  if(receivedCommand == "unlockMotors"){
                    unlockMotors();
                  Serial.println("Motors are unlocked");
                  }                  
                  
                  
                  if(receivedCommand == "testMotors"){
                    testMotors();
                  Serial.println("Testing Motors");
                  }
      

}
