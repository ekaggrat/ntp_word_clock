/*
 
 HATWENTY
 FIFVTEEN
 LF*PASTO
 NINEIGHT
 ONETHREE
 TWELEVEN
 FOURFIVE
 SIXSEVEN
 
 // */

const int min_offset=7; // 12:00 + 5*7 min = twentyfive to ONE

byte minutes_a[12][8] ={
  { // o'clock
     0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  , { // five past
    0B00000000,
    0B11010100,
    0B00011110,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  , { // ten past
    0B00000000,
    0B00001101,
    0B00011110,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // fifteen past
    0B00000000,
    0B11101111,
    0B00011110,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // twenty past
    0B00111111,
    0B00000000,
    0B00011110,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // twentyfive past
    0B00111111,
    0B11010100,
    0B00011110,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // half past
    0B11000000,
    0B00000000,
    0B11011110,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // twentyfive to
    0B00111111,
    0B11010100,
    0B00000011,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // twenty to
    0B00111111,
    0B00000000,
    0B00000011,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // fifteen to
    0B00000000,
    0B11101111,
    0B00000011,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // ten to
    0B00000000,
    0B00001101,
    0B00000011,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // five to
    0B00000000,
    0B11010100,
    0B00000011,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
};

byte hours_a[12][8] ={
  { // twelve
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B11110110,
    0B00000000,
    0B00000000
  }
  ,{ // one
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B11100000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // two
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B11000000,
    0B01000000,
    0B00000000
  }
  ,{ // three
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00011111,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // four
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B11110000,
    0B00000000
  }
  ,{ // five
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00001111,
    0B00000000
  }
  ,{ // six
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B11100000
  }
  ,{ // seven
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00011111
  }
  ,{ // eight
    0B00000000,
    0B00000000,
    0B00000000,
    0B00011111,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // nine
    0B00000000,
    0B00000000,
    0B00000000,
    0B11110000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000
  }
  ,{ // ten
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000001,
    0B00000001,
    0B00000001,
    0B00000000,
    0B00000000
  }
  ,{ // eleven
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00111111,
    0B00000000,
    0B00000000
  }
};

const char blinky[8] ={
  0B00000000,
  0B00000000,
  0B00100000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000
};
