#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
//#include "english.h"
#include "english_2.h"
const char *ssid     = "Eskphone";
const char *password = "tanu1234";

//const char *ssid     = "CU_UXB2";
//const char *password = "5giayarx";

unsigned long disp_sec;
unsigned long disp_min;
unsigned long disp_hrs;

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP, (28800)); // 8 hours x minutes x seconds offset from gmt

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

#include <LEDMatrixDriver.hpp>

// This sketch draw marquee text on your LED matrix using the hardware SPI driver Library by Bartosz Bielawski.
// Example written 16.06.2017 by Marko Oette, www.oette.info

// Define the ChipSelect pin for the led matrix (Dont use the SS or MISO pin of your Arduino!)
// Other pins are Arduino specific SPI pins (MOSI=DIN, SCK=CLK of the LEDMatrix) see https://www.arduino.cc/en/Reference/SPI
const uint8_t LEDMATRIX_CS_PIN = D4;

// Number of 8x8 segments you are connecting
const int LEDMATRIX_SEGMENTS = 1;
const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;

// The LEDMatrixDriver class instance
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);






boolean blink_enable = true;
boolean blinknow = false;



void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  lmd.setEnabled(true);
  lmd.setIntensity(10);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );

  }

  timeClient.begin();
}

unsigned long previousMillis = 0;
int blinkState = LOW;

void loop() {
  // Draw the text to the current position

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (blinkState == LOW) {
      blinkState = HIGH;
    } else {
      blinkState = LOW;
    }
  }

  // Toggle display of the new framebuffer
  lmd.display();

  // Wait to let the human read the display

  timeClient.update();
  delay(1000);
  updateTime();
  display_time();
}





void display_time() {
  {
    // The mask is used to get the column bit from the sprite row
    byte mask = B10000000;

    for ( int iy = 0; iy < 8; iy++ )
    {
      for ( int ix = 0; ix < 8; ix++ )
      {
        if (blinkState == LOW) {
          lmd.setPixel(ix, iy, (bool)((minutes_a[0][iy] | hours_a[disp_hrs][iy]) & mask ));

        }
        else {
          lmd.setPixel(ix, iy, (bool)((minutes_a[disp_min][iy] | hours_a[disp_hrs][iy]) & mask ));
        }

        //Serial.print(hours_a[disp_hrs][iy]);

        // shift the mask by one pixel to the right
        mask = mask >> 1;
      }

      // reset column mask
      mask = B10000000;
    }
    //Serial.println(":");
  }



}


void updateTime() {
  // Adjust 2.5 minutes = 150 seconds forward
  // So at 12:03 it already reads "five past 12"
  //DateTime now = rtc.now().unixtime() + 150;


  disp_min = timeClient.getMinutes();
  disp_hrs = timeClient.getHours();
  disp_min /= 5;



  if (disp_min >= min_offset)
    ++disp_hrs %= 12;
  else
    disp_hrs   %= 12;
}



