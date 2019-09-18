#include <FastLED.h>
#define LED_CHAINS 60
CRGB leds[LED_CHAINS];
#define PIN 6

void setup(){
	FastLED.addLeds<WS2811, PIN, GRB>(leds, LED_CHAINS).setCorrection( TypicalLEDStrip );
}

void loop(){
	rainbowCycle(20);
}

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
	 strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
	 FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
	 strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
	 leds[Pixel].r = red;
	 leds[Pixel].g = green;
	 leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
	for(int i = 0; i < LED_CHAINS; i++ ) {
		setPixel(i, red, green, blue);
	}
	showStrip();
}

void rainbowCycle(int SpeedDelay) {
	byte *c;
	uint16_t i, j;

	for(j=0; j<256*5; j++) {
		for(i=0; i< LED_CHAINS; i++) {
			c=Wheel(((i * 256 / LED_CHAINS) + j) & 255);
			setPixel(i, *c, *(c+1), *(c+2));
		}
		showStrip();
		delay(SpeedDelay);
	}
}

byte * Wheel(byte WheelPos) {
	static byte c[3];
	if(WheelPos < 85) {
		c[0]=WheelPos * 3;
	 	c[1]=255 - WheelPos * 3;
	 	c[2]=0;
	} else if(WheelPos < 170) {
	 	WheelPos -= 85;
		c[0]=255 - WheelPos * 3;
	 	c[1]=0;
	 	c[2]=WheelPos * 3;
	} else {
	 	WheelPos -= 170;
	 	c[0]=0;
	 	c[1]=WheelPos * 3;
	 	c[2]=255 - WheelPos * 3;
	}
	return c;
}
