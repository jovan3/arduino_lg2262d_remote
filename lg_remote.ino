#include <IRremote.h>

IRsend irsend;

const unsigned long POWER = 0x20DF10EF;
const unsigned long CH_UP = 0x20DF00FF;
const unsigned long CH_DOWN = 0x20DF807F;
const unsigned long VOL_UP = 0x20DF40BF;
const unsigned long VOL_DOWN = 0x20DFC03F;

const int  buttonPowerPin = 5;
const int  buttonVolUpPin = 6;
const int  buttonVolDownPin = 7;

int buttonPowerState = 0;
int lastButtonPowerState = 0;

int buttonVolUpState = 0;
int lastButtonVolUpState = 0;

int buttonVolDownState = 0;
int lastButtonVolDownState = 0;


void setup()
{
  pinMode(buttonPowerPin, INPUT);
  pinMode(buttonVolUpPin, INPUT);
  pinMode(buttonVolDownPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  lastButtonPowerState = checkButtonState(buttonPowerState, lastButtonPowerState, buttonPowerPin, POWER);
  lastButtonVolUpState = checkButtonState(buttonVolUpState, lastButtonVolUpState, buttonVolUpPin, VOL_UP);
  lastButtonVolDownState = checkButtonState(buttonVolDownState, lastButtonVolDownState, buttonVolDownPin, VOL_DOWN);
}

void sendIR(long irSignal) {
  Serial.println("sending IR signal");
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(irSignal, 32);
    delay(100);
  }
}

int checkButtonState(int buttonState, int lastButtonState, int buttonPin, unsigned long irSignal) {
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      Serial.println("button ON " + buttonPin);
      sendIR(irSignal);
    } else {
      Serial.println(buttonPin + " off");
    }
    delay(50);
  }

  return buttonState;
}
