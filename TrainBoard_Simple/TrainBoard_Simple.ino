#include <Joystick.h>

// VALUES TO MODIFY ARE HERE =================================================
int sensorPin = A0; // SLIDER PIN
bool invertSensor = false;

int button0 = 10; // LEFT BUTTON PIN
int button1 = 11; // CONFIRM BUTTON PIN
int button2 = 12; // RIGHT BUTTON PIN
int settingsButton = 6; // SETTINGS BUTTON PIN

int ledPin = 13;
// ==========================================================================

int sensorValue = 0;
Joystick_ Joystick(0x15, JOYSTICK_TYPE_GAMEPAD, 4,0, false, true, false, false, false, false, false, false, false, false, false);

int previousButtonState0 = 0;
int previousButtonState1 = 0;
int previousButtonState2 = 0;
int previousButtonStateSettings = 0;

const bool initAutoSendState = true;
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(button0, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(settingsButton, INPUT);
  pinMode(A0, INPUT);

  Joystick.begin(initAutoSendState);
}

void loop() {
  int pinVal = analogRead(sensorPin);

  if(invertSensor)
    pinVal = 1024 - pinVal;
  
  Joystick.setYAxis(pinVal);

  int buttonVal = digitalRead(button0);

  if(previousButtonState0 != buttonVal){
    Joystick.setButton(0, buttonVal);
    previousButtonState0 = buttonVal;
  }
  
  buttonVal = digitalRead(button1);

  if(previousButtonState1 != buttonVal){
    Joystick.setButton(1, buttonVal);
    previousButtonState1 = buttonVal;
  }

    
  buttonVal = digitalRead(button2);

  if(previousButtonState2 != buttonVal){
    Joystick.setButton(2, buttonVal);
    previousButtonState2 = buttonVal;
  }

  buttonVal = digitalRead(settingsButton);

  if(previousButtonStateSettings != buttonVal){
    Joystick.setButton(3, buttonVal);
    previousButtonStateSettings = buttonVal;
  }
  
  delay(50);
}
