#include <SoftwareSerial.h>

// These are the radio function pins (except for GND) 
// https://wiki.dfrobot.com/APC220_Radio_Data_Module_SKU_TEL0005_
// with defined pin number being the one each is connected to the Arduino
#define RADIO_PIN_2_VCC 13
#define RADIO_PIN_3_EN  12
#define RADIO_PIN_4_RXD 11
#define RADIO_PIN_5_TXD 10
#define RADIO_PIN_6_AUX 9
#define RADIO_PIN_7_SET 8

// The SoftwareSerial doc https://www.arduino.cc/en/Reference/SoftwareSerialConstructor
// documents constructor SoftwareSerial(rxPin, txPin) 
//     rxPin: the pin on which to receive serial data
//     txPin: the pin on which to transmit serial data
// To send from the Arduino to the Radio, we need to "transmit serial data"
//   but we need to transmit this data to the Radio's RX (Receive) pin. So
//   this looks a little backwards at first, but it's the way to do this :)
// This call gives us a variable called "apc220" we can use to communcate with the radio
SoftwareSerial apc220(RADIO_PIN_5_TXD, RADIO_PIN_4_RXD);

void setup() {

  // enable serial commms
  Serial.begin(9600);
  apc220.begin(9600);

  // Setup non-TX/RX radio pins as OUTPUTs
  pinMode(RADIO_PIN_2_VCC, OUTPUT);
  pinMode(RADIO_PIN_3_EN, OUTPUT);
  pinMode(RADIO_PIN_6_AUX, OUTPUT);
  pinMode(RADIO_PIN_7_SET, OUTPUT);
  
  // ensure we are out of configuration mode
  digitalWrite(RADIO_PIN_7_SET,HIGH);

  // enable the radio; we can disable if we want to go into a lower-power mode
  digitalWrite(RADIO_PIN_3_EN,HIGH);

  // power up the radio
  digitalWrite(RADIO_PIN_2_VCC,HIGH);

  // set the radio in transmit mode as this is a "broadcast" program
  digitalWrite(RADIO_PIN_6_AUX,HIGH);
}

void loop() {
  // Send something for the world to see
  Serial.println('Hello, world!');
  apc220.println('Hello, world!');
  delay(1000);
}
