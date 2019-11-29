#include <PS3BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);
int DIR[2][2] = {{2, 4}, {8, 7}};
int PWM_M[2][2] = {{9, 6}, {5, 3}};
bool state = LOW;
int i, j;
const int maxSpeed = 150;
const int minSpeed = 70;
void setup() {
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 2; j++)
    {
      pinMode(DIR[i][j], OUTPUT);
      pinMode(PWM_M[i][j], OUTPUT);
    }
  }
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial);
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatY) > 140)
    {
      digitalWrite(DIR[dir1][dir2], HIGH);
      digitalWrite(DIR[dir1][!dir2], LOW);
      analogWrite(PWM_M[dir1][dir2], constrain(map(PS3.getAnalogHat(LeftHatY), 140, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
      analogWrite(PWM_M[dir1][!dir2], constrain(map(PS3.getAnalogHat(LeftHatY), 140, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
      Serial.println(constrain(map(PS3.getAnalogHat(LeftHatY), 140, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
    }
    else if (PS3.getAnalogHat(LeftHatY) < 100)

    {
      digitalWrite(DIR[dir1][dir2], LOW);
      digitalWrite(DIR[dir1][!dir2], HIGH);
      analogWrite(PWM_M[dir1][dir2], constrain(map(PS3.getAnalogHat(LeftHatY), 100, 0, minSpeed, maxSpeed), minSpeed, maxSpeed));
      analogWrite(PWM_M[dir1][!dir2], constrain(map(PS3.getAnalogHat(LeftHatY), 100, 0, minSpeed, maxSpeed), minSpeed, maxSpeed));
      Serial.println(constrain(map(PS3.getAnalogHat(LeftHatY), 100, 0, minSpeed, maxSpeed), minSpeed, maxSpeed));

    }
    else if (PS3.getAnalogHat(LeftHatY) < 140 && PS3.getAnalogHat(LeftHatY) > 100 && !(PS3.getAnalogButton(R2)) && !(PS3.getAnalogButton(L2)))
    {
      analogWrite(PWM_M[dir1][dir2], 0);
      analogWrite(PWM_M[dir1][!dir2], 0);
    }
    if (PS3.getAnalogHat(RightHatX) > 140)
    {
      digitalWrite(DIR[!dir1][dir2], state);
      digitalWrite(DIR[!dir1][!dir2], !(state));
      analogWrite(PWM_M[!dir1][dir2], constrain(map(PS3.getAnalogHat(RightHatX), 140, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
      analogWrite(PWM_M[!dir1][!dir2], constrain(map(PS3.getAnalogHat(RightHatX), 140, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
      Serial.println(constrain(map(PS3.getAnalogHat(RightHatX), 140, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
    }
    else if (PS3.getAnalogHat(RightHatX) < 100)

    {
      digitalWrite(DIR[!dir1][dir2], !(state));
      digitalWrite(DIR[!dir1][!dir2], state);
      analogWrite(PWM_M[!dir1][dir2], constrain(map(PS3.getAnalogHat(RightHatX), 100, 0, minSpeed, maxSpeed), minSpeed, maxSpeed));
      analogWrite(PWM_M[!dir1][!dir2], constrain(map(PS3.getAnalogHat(RightHatX), 100, 0, minSpeed, maxSpeed), minSpeed, maxSpeed));
      Serial.println(constrain(map(PS3.getAnalogHat(RightHatX), 100, 0, minSpeed, maxSpeed), minSpeed, maxSpeed));

    }
    else if (PS3.getAnalogHat(RightHatX) < 140 && PS3.getAnalogHat(RightHatX) > 100 && !(PS3.getAnalogButton(R2)) && !(PS3.getAnalogButton(L2)))

    {
      analogWrite(PWM_M[!dir1][dir2], 0);
      analogWrite(PWM_M[!dir1][!dir2], 0);
    }



     if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {

      if (PS3.getButtonClick(SQUARE)) {

        dir1 = !dir1;
        dir2 = dir1 ^ dir2;
        state = !state;
        Serial.println(dir1);

        Serial.println(dir2);
      }

      if (PS3.getButtonClick(CIRCLE))
      {

        dir1 = !dir1;
        dir2 = !(dir1 ^ dir2);
        state = !state;


        Serial.println(dir1);

        Serial.println(dir2);
      }
      if (PS3.getAnalogButton(L2))
      {
        digitalWrite(DIR[dir1][dir2], HIGH);
        digitalWrite(DIR[dir1][!dir2], HIGH);
        digitalWrite(DIR[!dir1][dir2], LOW);
        digitalWrite(DIR[!dir1][!dir2], LOW);
        analogWrite(PWM_M[dir1][dir2], constrain(map(PS3.getAnalogButton(L2), 0, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
        analogWrite(PWM_M[dir1][!dir2], constrain(map(PS3.getAnalogButton(L2), 0, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
        analogWrite(PWM_M[!dir1][dir2], constrain(map(PS3.getAnalogButton(L2), 0, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
        analogWrite(PWM_M[!dir1][!dir2], constrain(map(PS3.getAnalogButton(L2), 0, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
      }
      if (PS3.getAnalogButton(R2))
      {
        digitalWrite(DIR[dir1][dir2], LOW);
        digitalWrite(DIR[dir1][!dir2], LOW);
        digitalWrite(DIR[!dir1][dir2], HIGH);
        digitalWrite(DIR[!dir1][!dir2], HIGH);
        analogWrite(PWM_M[dir1][dir2], constrain(map(PS3.getAnalogButton(R2), 0, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
        analogWrite(PWM_M[dir1][!dir2], constrain(map(PS3.getAnalogButton(R2), 0, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
        analogWrite(PWM_M[!dir1][dir2], constrain(map(PS3.getAnalogButton(R2), 0, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
        analogWrite(PWM_M[!dir1][!dir2], constrain(map(PS3.getAnalogButton(R2), 0, 255, minSpeed, maxSpeed), minSpeed, maxSpeed));
      }

    }

  }
}
