// I Sanjay Kumar, 000811237 certify that the given work is my own work. I have not 
// used any other person and not allowed anyone to use without due acknowledgment.

// COMP-10184 – Mohawk College
// PIR Sensor Test Application
// Turn on the blue LED with motion is detected.

#include <Arduino.h>
// saves the bool value if the motion dectected or not
bool motionDected = false; 
// save the active state of alarm enabled or disavbled
bool alarmActive = true;
// save the button state pressed or not pressed
bool buttonPressed = false;
// this is the counter to stop the light blink from motion and set the dark light
bool flag = true;
// startup initially set to true to turn off the light initially
bool startup = true;

//  digital input pin definitions
#define PIN_PIR D5
#define PIN_BUTTON D6
// buttons delays definitions
#define BUTTON_DELAY 2000
#define BLINK_DELAY 150

// *************************************************************
void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // configure the LED output
  pinMode(LED_BUILTIN, OUTPUT);

  // PIR sensor is an INPUT
  pinMode(PIN_PIR, INPUT);

  // Button is an INPUT
  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

// *************************************************************
void loop()
{
  bool bPIR;   // store motion dectector value
  int iButton; // store button value
  // read the motion detector value
  bPIR = digitalRead(PIN_PIR);
  // read the push button input...
  iButton = digitalRead(D6);

  // Here I turn off the light initially used only once
  if (startup)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    startup = false;
  }

  // if the alarm is active then we procedd further intialy set to true
  if (alarmActive)
  {
    if (bPIR == 1)
    {
      motionDected = true;
      // Serial.println("motion dected");
    }
    if (motionDected && flag)
    {
      // Serial.println("turning on the light");
      int i;
      for (i = 1; i <= 10; ++i)
      {
        if (alarmActive)
        {
          // turn the LED ON
          digitalWrite(LED_BUILTIN, LOW);
          delay(BLINK_DELAY);
          // turn the LED OFF
          digitalWrite(LED_BUILTIN, HIGH);
          delay(BLINK_DELAY);
          // turn the LED ON
          digitalWrite(LED_BUILTIN, LOW);
          delay(BLINK_DELAY);
          // turn the LED OFF
          digitalWrite(LED_BUILTIN, HIGH);
          delay(BLINK_DELAY);
          // turn the LED ON
          digitalWrite(LED_BUILTIN, LOW);
          delay(BLINK_DELAY);
          // turn the LED OFF
          digitalWrite(LED_BUILTIN, HIGH);
          delay(BLINK_DELAY);
          // turn the LED ON
          digitalWrite(LED_BUILTIN, LOW);
          delay(BLINK_DELAY);
          // turn the LED OFF
          digitalWrite(LED_BUILTIN, HIGH);
          delay(BLINK_DELAY);
        }
        else
        {
          break;
        }
      }
      digitalWrite(LED_BUILTIN, LOW); // turns on the light after blink
      flag = false;
      motionDected = false;
    }
  }
  // if the button is pressed now then it will reverse the alarm state and change the flag
  if (iButton == 0 && buttonPressed == false)
  {
    buttonPressed = true;
    alarmActive = !alarmActive;
    if (alarmActive)
    {
      flag = true;
      //Serial.println("activaed the alarm");
    }
    else
    {
      flag = false;
      //Serial.println("decactivaed the alarm");
    }
    digitalWrite(LED_BUILTIN, HIGH);
    delay(BUTTON_DELAY);
  }
  else if (iButton == 1)
  {
    buttonPressed = false;
  }
}