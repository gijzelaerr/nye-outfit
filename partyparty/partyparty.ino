#include "FastLED.h"


#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 150
#define DATA_PIN 8
#define BRIGHTNESS 64


// Define the array of leds
CRGB leds[NUM_LEDS];


//nightrider stuff
#define NIGHTRIDER_STEP_DELAY 50

#define ARM_LEFT_UP 0
#define ARM_LEFT_DOWN 15
#define ARM_RIGHT_UP 30
#define ARM_RIGHT_DOWN 45
#define LEG_LEFT_UP 60
#define LEG_LEFT_DOWN 83
#define LEG_RIGHT_UP 105
#define LEG_RIGHT_DOWN 128

#define ARM_LENGTH  30
#define LEG_LENGTH 45
#define LIMB_LENGTH 15


//blocks stuff
const int LIMBS_NUM = 8;
const int limbs[] = {ARM_LEFT_UP, ARM_LEFT_DOWN, ARM_RIGHT_UP, ARM_RIGHT_DOWN, LEG_LEFT_UP, LEG_LEFT_DOWN, LEG_RIGHT_UP, LEG_RIGHT_DOWN, NUM_LEDS};

//const int num_colors = 7;
//CRGB colors[] = {CRGB::Red, CRGB::Blue, CRGB::Green, CRGB::Gray, CRGB::Yellow, CRGB::Orange, CRGB::Purple};

const int num_colors = 4;
CRGB colors[] = {CRGB::Red, CRGB::Blue, CRGB::Green, CRGB::Purple};


// rainbow stuff
#define RAINBOW_UPDATES_PER_SECOND 50
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

// blocks stuff
int block_index = 0;


void setup() { 
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  // rainbow settings   
  currentPalette = RainbowColors_p;
  currentBlending = BLEND;
  
  block_index = 0;
}


void all_black() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}



void blocks() {
 
  for (int j = 0; j <= LIMBS_NUM; j++) {
    for (int i = limbs[j]; i < limbs[j+1]; i++) {
      leds[i] = colors[block_index];
    }
    block_index = (block_index + 1)  % num_colors;
  }
  FastLED.show();
}

void blocks_loop() {
    for (int i = 0; i < (2*30); i++) {
      blocks();
      delay(200);  
    }
}

void nightrider(CRGB color) { 
  for(int i = 0; i < ARM_LENGTH; i++) {
    leds[i] = color;
    leds[i + ARM_RIGHT_UP] = color;
    leds[i + LEG_LEFT_UP] = color;
    leds[i + LEG_RIGHT_UP] = color;

    FastLED.show();

    leds[i] = CRGB::Black;
    leds[i + ARM_RIGHT_UP] = CRGB::Black;
    leds[i + LEG_LEFT_UP] = CRGB::Black;
    leds[i + LEG_RIGHT_UP] = CRGB::Black;

    delay(NIGHTRIDER_STEP_DELAY);
  }

  for(int i = ARM_LENGTH-1; i >= 0; i--) {
    leds[i] = color;
    leds[i + ARM_RIGHT_UP] = color;
    leds[i + LEG_LEFT_UP] = color;
    leds[i + LEG_RIGHT_UP] = color;

    FastLED.show();

    leds[i] = CRGB::Black;
    leds[i + ARM_RIGHT_UP] = CRGB::Black;
    leds[i + LEG_LEFT_UP] = CRGB::Black;
    leds[i + LEG_RIGHT_UP] = CRGB::Black;

    delay(NIGHTRIDER_STEP_DELAY);
  }
  FastLED.show();
  delay(NIGHTRIDER_STEP_DELAY * 10);
}



void nightrider_short(CRGB color) { 
  for(int i = 0; i < LIMB_LENGTH; i++) {
    leds[i] = color;
    leds[i + ARM_RIGHT_UP] = color;
    leds[i + LEG_LEFT_UP] = color;
    leds[i + LEG_RIGHT_UP] = color;
    leds[i + ARM_LEFT_DOWN] = color;
    leds[i + ARM_RIGHT_DOWN] = color;
    leds[i + LEG_LEFT_DOWN] = color;
    leds[i + LEG_RIGHT_DOWN] = color;

    FastLED.show();

    leds[i] = CRGB::Black;
    leds[i + ARM_RIGHT_UP] = CRGB::Black;
    leds[i + LEG_LEFT_UP] = CRGB::Black;
    leds[i + LEG_RIGHT_UP] = CRGB::Black;
    leds[i + ARM_LEFT_DOWN] = CRGB::Black;
    leds[i + ARM_RIGHT_DOWN] = CRGB::Black;
    leds[i + LEG_LEFT_DOWN] = CRGB::Black;
    leds[i + LEG_RIGHT_DOWN] = CRGB::Black;

    delay(NIGHTRIDER_STEP_DELAY);
  }

  for(int i = LIMB_LENGTH-1; i >= 0; i--) {
    leds[i] = color;
    leds[i + ARM_RIGHT_UP] = color;
    leds[i + LEG_LEFT_UP] = color;
    leds[i + LEG_RIGHT_UP] = color;
    leds[i + ARM_LEFT_DOWN] = color;
    leds[i + ARM_RIGHT_DOWN] = color;
    leds[i + LEG_LEFT_DOWN] = color;
    leds[i + LEG_RIGHT_DOWN] = color;


    FastLED.show();

    leds[i] = CRGB::Black;
    leds[i + ARM_RIGHT_UP] = CRGB::Black;
    leds[i + LEG_LEFT_UP] = CRGB::Black;
    leds[i + LEG_RIGHT_UP] = CRGB::Black;
    leds[i + ARM_LEFT_DOWN] = CRGB::Black;
    leds[i + ARM_RIGHT_DOWN] = CRGB::Black;
    leds[i + LEG_LEFT_DOWN] = CRGB::Black;
    leds[i + LEG_RIGHT_DOWN] = CRGB::Black;

    delay(NIGHTRIDER_STEP_DELAY);
  }
  FastLED.show();
  delay(NIGHTRIDER_STEP_DELAY * 10);
}



void nightrider_loop() {
  nightrider(CRGB::Red);
  nightrider(CRGB::Red);
  nightrider_short(CRGB::Red);
  nightrider_short(CRGB::Red);
  nightrider(CRGB::Blue);
  nightrider_short(CRGB::Blue);
  nightrider_short(CRGB::Blue);
  nightrider(CRGB::Green);
  nightrider_short(CRGB::Green);
  nightrider_short(CRGB::Green);

}

void loop() {
  all_black();
  FastLED.setBrightness(  64 );
  blocks_loop();
  all_black();
  FastLED.setBrightness(  128 );
  nightrider_loop();
  FastLED.setBrightness(  64 );
  rainbow_loop();
  all_black();
}




void rainbow_loop() {
  for (int i = 0; i < (60 * 20); i++) {
    rainbow();
  }
}


void rainbow() {
  ChangePalettePeriodically();
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
  FastLED.delay(1000 / RAINBOW_UPDATES_PER_SECOND);
}


void FillLEDsFromPaletteColors( uint8_t colorIndex){
  uint8_t brightness = 255;
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}


void ChangePalettePeriodically() {
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if( lastSecond != secondHand) {
    lastSecond = secondHand;
    if( secondHand ==  0)  { 
      currentPalette = RainbowColors_p;         
      currentBlending = BLEND; 
    }
    if( secondHand == 10)  { 
      currentPalette = RainbowStripeColors_p;   
      currentBlending = NOBLEND;  
    }
    if( secondHand == 15)  { 
      currentPalette = RainbowStripeColors_p;   
      currentBlending = BLEND; 
    }
    if( secondHand == 20)  { 
      SetupPurpleAndGreenPalette();             
      currentBlending = BLEND; 
    }
    if( secondHand == 25)  { 
      SetupTotallyRandomPalette();              
      currentBlending = BLEND; 
    }
    if( secondHand == 30)  { 
      SetupBlackAndWhiteStripedPalette();       
      currentBlending = NOBLEND; 
    }
    if( secondHand == 35)  { 
      SetupBlackAndWhiteStripedPalette();       
      currentBlending = BLEND; 
    }
    if( secondHand == 40)  { 
      currentPalette = CloudColors_p;           
      currentBlending = BLEND; 
    }
    if( secondHand == 45)  { 
      currentPalette = PartyColors_p;           
      currentBlending = BLEND; 
    }
    if( secondHand == 50)  { 
      currentPalette = myRedWhiteBluePalette_p; 
      currentBlending = NOBLEND;  
    }
    if( secondHand == 55)  { 
      currentPalette = myRedWhiteBluePalette_p; 
      currentBlending = BLEND; 
    }
  }
}

void SetupTotallyRandomPalette() {
  for( int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV( random8(), 255, random8());
  }
}


void SetupBlackAndWhiteStripedPalette() {
  fill_solid( currentPalette, 16, CRGB::Black);
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}


void SetupPurpleAndGreenPalette() {
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;

  currentPalette = CRGBPalette16( 
  green,  green,  black,  black,
  purple, purple, black,  black,
  green,  green,  black,  black,
  purple, purple, black,  black );
}



const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM = {
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};


