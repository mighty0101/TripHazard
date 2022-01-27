    #include <AccelStepper.h>
    #include <RobojaxBTS7960.h>
    #include "Arduino.h"

    String serialResponse = "";
    char sz[] = "Here; is some; sample;100;data;1.414;1020";
    #define dirPin 15
    #define stepPin 14
    #define motorInterfaceType 1
    #define LMotorSPD 0
    #define RMotorSPD 0
    #define piezoPin 16
    
//right Motor
#define RPWM 3 // define pin 3 for RPWM pin (output)
#define R_EN 4 // define pin 4 for R_EN pin (input)
#define R_IS 5 // define pin 5 for R_IS pin (output)
#define LPWM 6 // define pin 6 for LPWM pin (output)
#define L_EN 7 // define pin 7 for L_EN pin (input)
#define L_IS 8 // define pin 8 for L_IS pin (output)
#define Rev 0 //do not change
#define For 1 //do not change
#define debug 0 //change to 0 to hide serial monitor debugging information or set to 1 to view

// left Motor
#define RPWM_L 9 // define pin 9 for RPWM pin (output)
#define R_EN_L 2 // define pin 2 for R_EN pin (input)
#define R_IS_L 10 // define pin 10 for R_IS pin (output)
#define LPWM_L 11 // define pin 11 for LPWM pin (output)
#define L_EN_L 12 // define pin 12 for L_EN pin (input)
#define L_IS_L 13 // define pin 13 for L_IS pin (output)
#define Rev 0 //do not change
#define For 1 //do not change
#define debug 0 //change to 0 to hide serial monitor debugging information or set to 1 to view
#define speed 50

    
    RobojaxBTS7960 motor(R_EN,RPWM,R_IS, L_EN,LPWM,L_IS,debug);
    RobojaxBTS7960 motor_L(R_EN_L,RPWM_L,R_IS_L, L_EN_L,LPWM_L,L_IS_L,debug);
    
    AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
      

    
  void setup() {
 
      pinMode(stepPin, OUTPUT);
      pinMode(dirPin, OUTPUT);
       
      Serial.begin( 9600 );
      
      motor.begin();
      motor_L.begin();
      
  //  INITIALIZE

      digitalWrite(stepPin, HIGH);
      digitalWrite(dirPin, LOW);
  
      //  Boot Sound
      tone(piezoPin, 200, 4800);
      delay(400);
      tone(piezoPin, 400, 600);
      
  
//  END INITIALIZATION

  
//Wait for serial connection.

 while (!Serial) {
            Serial.write("Serial is connecting/n");       
                 }
          
//Serial is connected sound

      tone(piezoPin, 1200, 200);
      delay(100);
      tone(piezoPin, 1000, 100);

      delay(1000);

      Serial.write("Serial is connected/n");

    }

// END void setup bitches.

    void loop() {


 
 //Test time!!

    // speed up the motor from 100% to 0 with 
    for(int i=0; i<50; i++){ 
        motor.rotate(i,For);
        motor_L.rotate(i,For);
       
 delay(50);
    }
 
  // slowly speed up the motor from 0 to 100% speed

        motor.rotate(speed,For);
        motor_L.rotate(speed,For);

   

    // slow down the motor from 100% to 0 with 
    for(int i=50; i<50; i--){ 
        motor.rotate(i,For);
        motor_L.rotate(i,For);
       
 delay(50);
    }

 


        
 delay(6000);
//end Test time!!


    // Convert from String Object to String.
    char buf[sizeof(sz)];
    serialResponse.toCharArray(buf, sizeof(buf));
    char *p = buf;
    char *str;
    while ((str = strtok_r(p, ":", &p)) != NULL) // delimiter is the colon
      Serial.println(str);

      
motor.rotate(LMotorSPD, For);
motor_L.rotate(RMotorSPD, For);
      
digitalWrite(stepPin, HIGH);
      digitalWrite(dirPin, LOW);
      int i;
      char input;
       
    if (Serial.available()>0) 
    { 
      
  serialResponse = Serial.readStringUntil('\n');
      
       input = Serial.read();
         turnShoulderMotor(input , 400);
         delay(1); 

           
    }

  }    
    


 //Func - Shoulder Joint Control ###########################################
 void turnShoulderMotor (char dir, int deg){

        if (dir == 'R'){
          Serial.write("Right"); 
          digitalWrite(dirPin, LOW);
          
          }

        if (dir == 'L') {
          Serial.write("Left");
          digitalWrite(dirPin, HIGH);
          }


        if (dir == 'F') {
          Serial.write("Forward");
          LMotorSPD ==10;
          RMotorSPD ==10;
          motor.rotate(10, For);
          motor_L.rotate(10, For);
          }


        if (dir == 'S') {
          Serial.write("Stop");
          LMotorSPD == 0;
          RMotorSPD == 0;
          motor.rotate(LMotorSPD, For);
          motor_L.rotate(RMotorSPD, For);
          }

        
        int i = 0;
        
        for (i = 0; i <= deg; i++){
        digitalWrite(stepPin, HIGH);
        delay(1);         
        digitalWrite(stepPin, LOW);
        delay(1);
          }
        return;
    }
