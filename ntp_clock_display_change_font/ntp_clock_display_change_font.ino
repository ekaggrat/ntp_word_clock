#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

//const char *ssid     = "DLINK_zhefang";
//const char *password = "12345678";

const char *ssid     = "CU_UXB2";
const char *password = "5giayarx";



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
const int LEDMATRIX_SEGMENTS = 2;
const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;

// The LEDMatrixDriver class instance
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);

// Marquee text
char text[] = "** LED MATRIX DEMO! ** (1234567890) ++ \"ABCDEFGHIJKLMNOPQRSTUVWXYZ\" ++ <$%/=?'.@,> --";

// Marquee speed (lower nubmers = faster)
const int ANIM_DELAY = 30;
String minutes;
String hours;









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

int x = 0, y = 0; // start top left

// This is the font definition. You can use http://gurgleapps.com/tools/matrix to create your own font or sprites.
// If you like the font feel free to use it. I created it myself and donate it to the public domain.
byte font[95][8] = { {0, 0, 0, 0, 0, 0, 0, 0}, // SPACE

  {0x00, 0xe0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xe0}, // 0 cc
  {0x00, 0x40, 0xc0, 0x40, 0x40, 0x40, 0x40, 0xe0}, // 1 cc
  {0x00, 0xe0, 0x20, 0x20, 0xe0, 0x80, 0x80, 0xe0}, // 2 cc
  {0x00, 0xe0, 0x20, 0x20, 0xe0, 0x20, 0x20, 0xe0}, // 3 cc
  {0x00, 0xa0, 0xa0, 0xa0, 0xe0, 0x20, 0x20, 0x20}, // 4 cc
  {0x00, 0xe0, 0x80, 0x80, 0xe0, 0x20, 0x20, 0xe0}, // 5 cc
  {0x00, 0xe0, 0x80, 0x80, 0xe0, 0xa0, 0xa0, 0xe0}, // 6 cc
  {0x00, 0xe0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}, // 7 cc
  {0x00, 0xe0, 0xa0, 0xa0, 0xe0, 0xa0, 0xa0, 0xe0}, // 8 cc
  {0x00, 0xe0, 0xa0, 0xa0, 0xe0, 0x20, 0x20, 0xe0}, // 9 cc
  {0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00}, // :
  {0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x08}, // ;
  {0x00, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10}, // <
  {0x00, 0x00, 0x7e, 0x00, 0x00, 0xfc, 0x00, 0x00}, // =
  {0x00, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08}, // >
  {0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x00, 0x10}, // ?
  {0x00, 0x30, 0x48, 0xba, 0xba, 0x84, 0x78, 0x00}, // @
  {0x00, 0x1c, 0x22, 0x42, 0x42, 0x7e, 0x42, 0x42}, // A
  {0x00, 0x78, 0x44, 0x44, 0x78, 0x44, 0x44, 0x7c}, // B
  {0x00, 0x3c, 0x44, 0x40, 0x40, 0x40, 0x44, 0x7c}, // C
  {0x00, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x44, 0x78}, // D
  {0x00, 0x78, 0x40, 0x40, 0x70, 0x40, 0x40, 0x7c}, // E
  {0x00, 0x7c, 0x40, 0x40, 0x78, 0x40, 0x40, 0x40}, // F
  {0x00, 0x3c, 0x40, 0x40, 0x5c, 0x44, 0x44, 0x78}, // G
  {0x00, 0x42, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42}, // H
  {0x00, 0x7c, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7e}, // I
  {0x00, 0x7e, 0x02, 0x02, 0x02, 0x02, 0x04, 0x38}, // J
  {0x00, 0x44, 0x48, 0x50, 0x60, 0x50, 0x48, 0x44}, // K
  {0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7c}, // L
  {0x00, 0x82, 0xc6, 0xaa, 0x92, 0x82, 0x82, 0x82}, // M
  {0x00, 0x42, 0x42, 0x62, 0x52, 0x4a, 0x46, 0x42}, // N
  {0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x44, 0x38}, // O
  {0x00, 0x78, 0x44, 0x44, 0x48, 0x70, 0x40, 0x40}, // P
  {0x00, 0x3c, 0x42, 0x42, 0x52, 0x4a, 0x44, 0x3a}, // Q
  {0x00, 0x78, 0x44, 0x44, 0x78, 0x50, 0x48, 0x44}, // R
  {0x00, 0x38, 0x40, 0x40, 0x38, 0x04, 0x04, 0x78}, // S
  {0x00, 0x7e, 0x90, 0x10, 0x10, 0x10, 0x10, 0x10}, // T
  {0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3e}, // U
  {0x00, 0x42, 0x42, 0x42, 0x42, 0x44, 0x28, 0x10}, // V
  {0x80, 0x82, 0x82, 0x92, 0x92, 0x92, 0x94, 0x78}, // W
  {0x00, 0x42, 0x42, 0x24, 0x18, 0x24, 0x42, 0x42}, // X
  {0x00, 0x44, 0x44, 0x28, 0x10, 0x10, 0x10, 0x10}, // Y
  {0x00, 0x7c, 0x04, 0x08, 0x7c, 0x20, 0x40, 0xfe}, // Z
  // (the font does not contain any lower case letters. you can add your own.)
};    // {}, //




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


  if (blinkState == LOW)
  {
    minutes = "  ";
  }
  else {

    int actual_min = timeClient.getMinutes();
    if (actual_min < 10) {
      minutes = "0" + String(actual_min);
    }
    else {
      minutes = timeClient.getMinutes();
    }

  }




  hours = timeClient.getHours();
  //hours = "13";
  // minutes = "06";
  timeClient.update();
  int str_len1 = hours.length() + 1;
  int str_len2 = minutes.length() + 1;

  // Prepare the character array (the buffer)
  char min_array[str_len2];
  char hour_array[str_len1];
  // Copy it over
  minutes.toCharArray(min_array, str_len2);
  hours.toCharArray(hour_array, str_len1);
  drawString(hour_array, str_len1, 0, 0);
  drawString(min_array, str_len2, 9, 0);

  Serial.print(hour_array);
  Serial.print(":");
  Serial.println(min_array);

  delay(1000);
}



/**
   This function draws a string of the given length to the given position.
*/
void drawString(char* text, int len, int x, int y )
{
  for ( int idx = 0; idx < len; idx ++ )
  {
    int c = text[idx] - 32;

    // stop if char is outside visible area
    //if ( x + idx * 8  > LEDMATRIX_WIDTH )
    //return;

    // only draw if char is visible
    //if ( 9 + x + idx * 8 > 0 )
    drawSprite( font[c], x + idx * 4, y, 4, 8 );
  }
}

/**
   This draws a sprite to the given position using the width and height supplied (usually 8x8)
*/
void drawSprite( byte * sprite, int x, int y, int width, int height )
{
  // The mask is used to get the column bit from the sprite row
  byte mask = B10000000;

  for ( int iy = 0; iy < height; iy++ )
  {
    for ( int ix = 0; ix < width; ix++ )
    {
      lmd.setPixel(x + ix, y + iy, (bool)(sprite[iy] & mask ));

      // shift the mask by one pixel to the right
      mask = mask >> 1;
    }

    // reset column mask
    mask = B10000000;
  }
}







