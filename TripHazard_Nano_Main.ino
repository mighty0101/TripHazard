#include <FastLED.h>
#include <Wire.h>

#define LED_TYPE            WS2811
#define COLOR_ORDER        GRB
#define LED_TYPE           WS2812B
#define COLOR_ORDER        GRB
#define DATA_PIN           3
#define NUM_LEDS           98
#define SLAVE_ADDRESS      0x08
#define BRIGHTNESS         125
#define FRAMES_PER_SECOND  120
#define UPDATES_PER_SECOND 100

volatile boolean receiveFlag = false;
volatile boolean rgbShineFlag = true;

char temp[32];
unsigned long pasttime;
unsigned long currenttime;
unsigned long timepassed;



// Define the array of leds
CRGB leds[NUM_LEDS];



 void setup() {
         
         // initialize i2c as slave
         Wire.begin(SLAVE_ADDRESS);

         Serial.begin(115200);
         Serial.println("TripHazard Nano Ready");
         
         Wire.onReceive(receiveEvent);
         
         FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
         FastLED.setBrightness(BRIGHTNESS);


         pasttime= millis();


//Clear all LEDs

         clearLEDs();

                } 

 void loop() {


//Serial.println(rgbShineFlag + "\n");

 //police_lights();
 //rgbShine();
 //ws2812_fill_all();
 //trails();
 //sinelon();
 //rgb_chasing();
  
  
  if (receiveFlag == true) {


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
        Serial.println("command = " + command +"\n\nsubCommand1 = "+ subCommand1 + "\nsubCommand2 = " + subCommand2 +"\nsubCommand3 = "+ subCommand3 + "\nsubCommand4 = "+ subCommand4 + "\nsubCommand5 = "+ subCommand5 + "\n\n");
     
        
        Serial.println("\n\n\n\n***************************");
        Serial.println("--Mega current flag state--"); 
        Serial.println("***************************\n");
     //   Serial.println("rgbShineFlag = " + rgbShineFlag + "\n\n");


    
     //   Serial.println(getValue(tempString,":",1));
        //Serial.println(found[0]);
      //  Serial.println(strIndex[1]);   //++"--"++slitdata[1]++"--"++splitdata[2])  ;


  if ((command == "rgbShine") && (subCommand1 == "on")){
         rgbShineFlag = true;
        
  }

  if ((command == "rgbShine") && (subCommand1 == "off")){
         rgbShineFlag = false;
  }



  
 if (rgbShineFlag == true){ 
 currenttime = millis();
 timepassed = currenttime - pasttime;
      if (timepassed > 12000){
        rgbShine();
        pasttime=millis();
      }
  }

  if (command == "rgbRed") {
            
        Serial.println("LEDs are red");     

        for (int i = 0; i < NUM_LEDS; i++)  
        {
        leds[i]  =  CRGB::Red;
        FastLED.show();
        }
  }

  if (command == "hoodlighton") {
            
        Serial.println("hood lamp is on");     

        for (int i = 0; i < 29; i++)  
        {
        leds[i]  =  CRGB::White;
        FastLED.show();
        }
         
        for (int i = 69; i < 98; i++)  
        {
        leds[i]  =  CRGB::White;
        FastLED.show();
        }
  }
  if (command == "hoodlightoff") {
            
        Serial.println("hood lamp is off");     

        for (int i = 0; i < 98; i++)  
        {
        leds[i]  =  CRGB::Black;
        FastLED.show();
        }
         
        for (int i = 82; i < 98; i++)  
        {
        leds[i]  =  CRGB::Black;
        FastLED.show();
        }
                             
                               
                               }

  if (command == "rgbPolice") 
        {
        Serial.println("police lights are running");
        police_lights();
        }

      // tempString == "";
       }   
  }


void clearLEDs()  {
         for (int i = 0; i < NUM_LEDS; i++){
         leds[i]  =  CRGB::Black;
         FastLED.show();
                                           }

                   }

                   
void ws2812_fill_all() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
 //   delay(50);
    FastLED.show();
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
   // delay(50);
    FastLED.show();
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green;
    //delay(50);
    FastLED.show();
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
   // delay(50);
    FastLED.show();
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
  //  delay(50);
    FastLED.show();
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
 //   delay(50);
    FastLED.show();
  }
}


void rgbShine() {



//pasttime = millis();
//Serial.println ("\nold time was - " + pasttime);

   // delay(12000);  

   int z = 49;
   for (int i =48; i < NUM_LEDS; i++) {
     
   leds[i]   = CRGB::White;
   leds[i+1] = CRGB::White;
   leds[i]   = CRGB::Black;
  
   leds[z]   = CRGB::White;
   leds[z-1] = CRGB::White;
   leds[z]   = CRGB::Black;

       z=z-1; 
  
FastLED.show();
  
}
}


void police_lights() {
 //  BRIGHTNESS==225;
    //delay(2000);  
     
   int z = 48;
   for (int i =49; i <= NUM_LEDS; i++) {
     
   leds[i]  =  CRGB::Red;
   leds[i + 1] = CRGB::Red;
 //  leds[i + 2] = CRGB::White;
 //  leds[i + 3] = CRGB::Blue;
   leds[i] =     CRGB::Black;
  
   leds[z]  =  CRGB::Blue;
  //leds[z - 2] = CRGB::White;
  leds[z-1] = CRGB::Blue;
  // leds[z + 3] = CRGB::White;
   leds[z] =     CRGB::Black;
  z=z-1; 
FastLED.show();
  }
}

void rgb_chasing() {
  int ms = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(100, 0, 0);
    FastLED.show();
  //  delay(ms);
  }
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 100, 0);
    FastLED.show();
  //  delay(ms);
  }
  
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,100);
    FastLED.show();
   // delay(ms);
  }
}

void trails() {
uint8_t gHue = 0;
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);

}




// https://stackoverflow.com/questions/9072320/split-string-into-string-array
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
