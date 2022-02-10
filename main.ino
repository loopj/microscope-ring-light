// Super simple sketch to set brightness levels on NeoPixel Ring

#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>

// Assumes Adafruit QT Py 2040
// Assumes Adafruit NeoPixel Ring 16 RGBW

#define NEOPIXEL_PIN        29 // Pin A0
#define NEOPIXEL_NUMPIXELS  16
#define BUTTON_PIN          21 // Built-in boot button
#define BRIGHTNESS_STEPS    4

Adafruit_NeoPixel pixels(NEOPIXEL_NUMPIXELS, NEOPIXEL_PIN, NEO_RGBW + NEO_KHZ800);
Bounce b = Bounce();

// Off by default
int brightness = 0;

void setBrightness() {
    int brightnessVal = (int)(((float)brightness/BRIGHTNESS_STEPS)*255);

    pixels.clear();
    pixels.fill(pixels.Color(brightnessVal, brightnessVal, brightnessVal, brightnessVal), 0, NEOPIXEL_NUMPIXELS);
    pixels.show();
}

void setup() {
    // Set up Neopixels
    pixels.begin();

    // Set up button debouncer with a debounce interval of 25ms
    b.attach(BUTTON_PIN, INPUT);
    b.interval(10);

    // Turn on the LEDs
    setBrightness();
}

void loop() {
    b.update();

    if(b.fell()) {
        if(brightness == 0) {
            brightness = BRIGHTNESS_STEPS;
        } else {
            brightness--;
        }

        setBrightness();
    }
}
