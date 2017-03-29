#include <Adafruit_NeoPixel.h>
//LED Thresholds
const float SLOW = 20000;
const float MED = SLOW * 2;
const float FAST = SLOW * 3;
const float CRAT = 52.6;


//hall sensor
volatile byte half_revolutions;
unsigned int rpm;
unsigned long timeold;
float velocity;
int WHEEL_RADIUS = 2.05;
float ct = 0;
float ct_prev = 0;

//Globals
struct color {
  uint16_t red;
  uint16_t grn;
  uint16_t blu;
};

char val; // variable to receive data from the serial port
color curColor;
color bruinColor1;
color bruinColor2;

//LED pins
#define PIN1 2
#define PIN2 5
#define numLED1 61
#define numLED2 58
#define HALL_EFFECT_SENSOR 3 // only interrupt pins are 2 and 3
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(numLED1, PIN1);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(numLED2, PIN2);


void setup() {
  //Light Strip
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();
  setBright(99);

  //Hall Sensor
  Serial.begin(9600); //Serial.begin(9600);
  pinMode(HALL_EFFECT_SENSOR, INPUT);
  attachInterrupt(HALL_EFFECT_SENSOR, magnet_detect, RISING);//Initialize the interrupt pin (Arduino digital pin 4)
  half_revolutions = 0;
  rpm = 0;
  timeold = 0;

  velocity = 0;
  curColor = {0, 0, 255};
  bruinColor1 = {0, 0, 255};
  bruinColor2 = {255, 255, 0};
  lightAll(1, bruinColor1);
  lightAll(2, bruinColor2);
  Serial.println("Starting");
}

void loop() {
  //hall sensor
  /*
    if (half_revolutions >= 10) {
    updateVelocity();
    curColor = v2C(velocity, curColor);

    Serial.print("red: ");
    Serial.println(curColor.red);
    Serial.print("grn: ");
    Serial.println(curColor.grn);
    Serial.print("blu: ");
    Serial.println(curColor.blu);

    lightAll(1, curColor);
    lightAll(2, curColor);
    }
  */

  if ( Serial.available() )      // if data is available to read
  {
    val = Serial.read();         // read it and store it in 'val'
    Serial.print(val);
    Serial.print("got here");
  }
  switch (val) {
    case '1':
      lightAll(1, {255, 0, 0});
      lightAll(2, {255, 0, 0});
      break;
    case '2':
      lightAll(1, {0, 255, 0});
      lightAll(2, {0, 255, 0});
      break;
    case '3':
      lightAll(1, {0, 0, 255});
      lightAll(2, {0, 0, 255});
      break;
    case '4':
      lightAll(1, {255, 255, 0});
      lightAll(2, {0, 0, 0});
      delay(100);
      lightAll(1, {0, 0, 0});
      delay(100);
      break;
    case '5':
      lightAll(1, {0, 0, 0});
      lightAll(2, {255, 255, 0});
      delay(100);
      lightAll(2, {0, 0, 0});
      delay(100);
      break;
    case '0':
      lightAll(1, {0, 0, 0});
      lightAll(2, {0, 0, 0});
      break;
  }

  /*
    //Light Test
    color F1 = {255, 0, 0};
    color F2 = {255, 255, 0};
    color F3 = {0, 255, 0};
    color F4 = {0, 0, 255};
    lightAll(1, F1);
    lightAll(2, F1);
    delay(1500);
    lightAll(1, F2);
    lightAll(2, F2);
    delay(1500);
    lightAll(1, F3);
    lightAll(2, F3);
    delay(1500);
    lightAll(1, F4);
    lightAll(2, F4);
    delay(1500);
  */

}
