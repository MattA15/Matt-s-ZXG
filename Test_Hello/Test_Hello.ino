#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <avr/power.h>
#include <ZX_Sensor.h>

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();

const int ZX_ADDR = 0x10;

ZX_Sensor zx_sensor = ZX_Sensor(ZX_ADDR);
uint8_t x_pos;
uint8_t z_pos;
int z;
int x;
int i = 0;
int b;


static const uint8_t PROGMEM
smile_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
},
neutral_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10111101,
  B10000001,
  B01000010,
  B00111100
},
frown_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};


void setup() {

  Serial.begin(9600);
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
  uint8_t ver;

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println("SparkFun/GestureSense - I2C ZX Demo");

  if ( zx_sensor.init() ) {
    Serial.println("ZX Sensor initialization complete");
  } else {
    Serial.println("Something went wrong during ZX Sensor init!");
  }

  ver = zx_sensor.getModelVersion();
  if ( ver == ZX_ERROR ) {
    Serial.println("Error reading model version number");
  } else {
    Serial.print("Model version: ");
    Serial.println(ver);
  }
  if ( ver != ZX_MODEL_VER ) {
    Serial.print("Model version needs to be ");
    Serial.print(ZX_MODEL_VER);
    Serial.print(" to work with this library. Stopping.");
    while (1);
  }

  ver = zx_sensor.getRegMapVersion();
  if ( ver == ZX_ERROR ) {
    Serial.println("Error reading register map version number");
  } else {
    Serial.print("Register Map Version: ");
    Serial.println(ver);
  }
  if ( ver != ZX_REG_MAP_VER ) {
    Serial.print("Register map version needs to be ");
    Serial.print(ZX_REG_MAP_VER);
    Serial.print(" to work with this library. Stopping.");
    while (1);
  }
  /*for (z = -5; z <= 19; z++) {
    matrix.drawCircle(z, 4, 4, 64);
    delay(300);
    matrix.clear();
    }*/
}


void loop() {

  if ( zx_sensor.positionAvailable() ) {
    x_pos = zx_sensor.readX();
    if ( x_pos != ZX_ERROR ) {
      Serial.print("X: ");
      Serial.print(x_pos);
    }
    z_pos = zx_sensor.readZ();

    x = map(x_pos, 0, 240, -6, 20);
    z = map(z_pos, 0, 240, -6, 20);
    if ( z_pos != ZX_ERROR ) {
      if (x_pos > 20) {
        matrix.clear();
        matrix.drawPixel(z, x, 64);
      } else {
        matrix.clear();
      }
      Serial.print(" Z: ");
      Serial.println(z_pos);
    }
  }

  /*matrix.setRotation(0);

    matrix.clear();
    matrix.drawBitmap(3, 0, smile_bmp, 8, 8, 255);

    matrix.clear();
    matrix.drawBitmap(3, 0, neutral_bmp, 8, 8, 64);

    matrix.clear();
    matrix.drawBitmap(3, 0, frown_bmp, 8, 8, 32);

    matrix.clear();
    matrix.drawPixel(0, 0, 255);

    matrix.clear();
    matrix.drawLine(0, 0, matrix.width() - 1, matrix.height() - 1, 127);

    matrix.clear();
    matrix.drawRect(0, 0, matrix.width(), matrix.height(), 255);
    matrix.fillRect(2, 2, matrix.width() - 4, matrix.height() - 4, 20);

    matrix.clear();
    matrix.drawCircle(8, 4, 4, 64);
    matrix.drawCircle(8, 4, 2, 32);*/


  /*matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(100);
    for (int8_t x = 0; x >= -32; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Hello");
    }*/
  /*
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(100);
    for (int8_t x = 7; x >= -32; x--) {
      matrix.clear();
      matrix.setCursor(x, 0);
      matrix.print("World");
    }*/
}
