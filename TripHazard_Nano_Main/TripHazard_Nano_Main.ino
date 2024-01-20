#include <FastLED.h>
#include <Wire.h>

#define LED_TYPE            WS2811
#define COLOR_ORDER        GRB
#define LED_TYPE           WS2812B
#define COLOR_ORDER        GRB
#define DATA_PIN           3
#define NUM_LEDS           98
#define BRIGHTNESS         100
#define SLAVE_ADDRESS      0x08
#define BRIGHTNESS         125
#define FRAMES_PER_SECOND  120
#define UPDATES_PER_SECOND 100

volatile boolean receiveFlag = false;
char temp[32];


// Define the array of leds
CRGB leds[NUM_LEDS];



 void setup() {
         // initialize i2c as slave
         Wire.begin(SLAVE_ADDRESS);

         Serial.begin(9600);
         Serial.println("TripHazard Nano Ready");
         Wire.onReceive(receiveEvent);
         FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
         FastLED.setBrightness(BRIGHTNESS);


//Clear all LEDs

         clearLEDs();

                } 





 void loop() {

 //police_lights();
 //moving_three_led();
 //ws2812_fill_all();
 // trails();
 //sinelon();
 //rgb_chasing();
  
  
  if (receiveFlag == true) {
        Serial.println(temp);
        String tempString(temp);



  if (tempString == "rgbRed") {
            
        Serial.println("LEDs are red");     

        for (int i = 0; i < NUM_LEDS; i++)  
        {
        leds[i]  =  CRGB::Red;
        FastLED.show();
        }
                               }

  if (tempString == "rgbPolice") 
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

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( 1, 255, 192);
}

void moving_three_led() {

    //delay(10000);  
     
   int z = 49;
   for (int i =50; i <= NUM_LEDS; i++) {
     
   leds[i]  =  CRGB::White;
   leds[i + 1] = CRGB::White;
 //  leds[i + 2] = CRGB::White;
 //  leds[i + 3] = CRGB::Blue;
   leds[i] =     CRGB::Black;
  
   leds[z]  =  CRGB::White;
  //leds[z - 2] = CRGB::White;
  leds[z-1] = CRGB::White;
  // leds[z + 3] = CRGB::White;
   leds[z] =     CRGB::Black;
  z=z-1; 
FastLED.show();
  }
}


void police_lights() {
 //  BRIGHTNESS==225;
   // delay(10000);  
     
   int z = 49;
   for (int i =50; i <= NUM_LEDS; i++) {
     
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
