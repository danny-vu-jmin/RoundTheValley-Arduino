#include <Joystick.h>

// VALUES TO MODIFY ARE HERE =================================================

int sensorPin = A0; // IR SENSOR PIN

int button0 = 10; // LEFT BUTTON PIN
int button1 = 11; // CONFIRM BUTTON PIN
int button2 = 12; // RIGHT BUTTON PIN
int settingsButton = 6; // SETTINGS BUTTON PIN


const int READINGS_COUNT = 25; // INCREASE VALUE TO REDUCE IR SENSOR NOISE (LEADS TO MORE INPUT LAG)

int min = 20; // LOWEST IR SENSOR VALUE
int max = 600; // HIGHEST IR SENSOR VALUE

// VALUES THAT DETERMINE WHEN THE TRAIN GOES FROM STOP TO SLOW TO FAST
int minToMiddle = 185;
int middleToMax = 350;
// SPEED = FAST (middleToMax < [IR Sensor value])
// ---------  middleToMax  -----------
// SPEED = SLOW (minToMiddle < [IR Sensor value] < middleToMax)
//  ---------  minToMiddle  -----------
// SPEED = STOP ([IR Sensor value] < minToMiddle)

int waitTime = 50; // TIME IN MILLISECONDS BETWEEN UPDATES ; INCREASE VALUE TO REDUCE INPUT LAG (MAY LEAD TO MALFUNCTIONING)

int ledPin = 13;
// ==========================================================================

int readings[READINGS_COUNT];
int currentIndex = 0;

int holdTime;

double invMin = 1.0;
double invMax = 10.0;

int sensorValue = 0;
Joystick_ Joystick(0x15, JOYSTICK_TYPE_GAMEPAD, 4,0, false, true, false, false, false, false, false, false, false, false, false);

int previousButtonState0 = 0;
int previousButtonState1 = 0;
int previousButtonState2 = 0;
int previousButtonStateSettings = 0;


const bool initAutoSendState = true;
void setup() {
  currentIndex = 0;
  pinMode(ledPin, OUTPUT);
  pinMode(button0, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(settingsButton, INPUT);
  pinMode(A0, INPUT);
  for(int i = 0; i<READINGS_COUNT; i++)
  {
    readings[i] = 0;
  }
  // Uncomment to Debug
  //Serial.begin(9600);
  
  Joystick.begin(initAutoSendState);
  holdTime = 0;
}

void loop() {
  int pinVal = analogRead(sensorPin);
  readings[currentIndex%READINGS_COUNT] = pinVal;
  currentIndex++;
  if(currentIndex>READINGS_COUNT)
    currentIndex -= READINGS_COUNT;

  int average = 0;
  for(int i = 0; i<READINGS_COUNT; i++)
  {
    average += readings[i];
  }

  average = average/READINGS_COUNT;

  if(average < min)
    average = min;
  if(average > max)
    average = max;
  

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

  // Uncomment to Debug ========================================
  /*
  int lerpAverage = map(average, 0, max, 0, 1024);
  Serial.print("lerp:");
  Serial.println(average);
  double invAverage = 1.0/((lerpAverage+min)/(1024.0))-0.1;

  if(invAverage < invMin)
    invAverage = invMin;
  if(invAverage > invMax)
    invAverage = invMax;
  
  invAverage = 

  Serial.print("lerpAvg:");
  Serial.println(invAverage);
  */
  /*
  Serial.print("average:");
  Serial.println(average);
  */
  //analogWrite(ledPin, average);

  // ===========================================================

  int stickOutput = 0;
  if(average > minToMiddle)
    stickOutput = 512;
  if(average > middleToMax)
    stickOutput = 1024;
  
  stickOutput = 1024 - stickOutput;
  int max = 1280;
  int min = 0;

  // Uncomment to Debug ========================================
  /*
  
  Serial.print("Output:");
  Serial.println(stickOutput);
  Serial.println(max);
  Serial.println(min);
  */
  // ===========================================================

  Joystick.setYAxis(stickOutput);
  
  delay(waitTime);
}
