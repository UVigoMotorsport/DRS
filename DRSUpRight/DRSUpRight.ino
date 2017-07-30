
#include <Servo.h>
#define ABSMAX 2500
#define ABSMIN 500

//brake
#define HIGHTHRES 1
#define LOWTHRES 2

#define STEERING A0
#define BRAKE A1

#define TESTMODE 0

#define MINPRESS 25

Servo UpRight; //D12
Servo UpLeft; //D11
Servo DownRight; //D10
Servo DownLeft; //D9

#define CLOSE_UpRight 1500
#define OPEN_UpRight 1200

#define CLOSE_UpLeft 1500
#define OPEN_UpLeft  1800

#define CLOSE_DownRight 1500
#define OPEN_DownRight 1200

#define CLOSE_DownLeft 1500
#define OPEN_DownLeft 1800

int THRES_TYPE = LOWTHRES;
#define THRES_VALUE 120

int debounce = 0;
unsigned int debouncetime = 0;

//steering
#define LIMIT1 600
#define LIMIT2 700
#define CENTRE 511



int DRS_STATE = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  UpRight.attach(12);
  UpLeft.attach(11);
  DownRight.attach(10);
  DownLeft.attach(9);
  UpRight.writeMicroseconds (CLOSE_UpRight);
  UpLeft.writeMicroseconds (CLOSE_UpLeft);
  DownRight.writeMicroseconds (CLOSE_DownRight);
  DownLeft.writeMicroseconds (CLOSE_DownLeft);
  Serial.begin(9600);
}

void loop() {
  if (DRS_STATE == 0)
  {
    digitalWrite(LED_BUILTIN, 0);
    UpRight.writeMicroseconds (CLOSE_UpRight);
    UpLeft.writeMicroseconds (CLOSE_UpLeft);
    DownRight.writeMicroseconds (CLOSE_DownRight);
    DownLeft.writeMicroseconds (CLOSE_DownLeft);
    if (digitalRead (2) == 0)
    {
      if(debounce == 0)
      {
        debounce = 1;
        debouncetime = millis();
      }
      else if(debounce == 1 && ((millis() - debouncetime) > MINPRESS))
      {
        DRS_STATE++;
      }
    }
    else if(digitalRead (2) == 1)
    {
      debounce = 0;
    }
  }
  else if (DRS_STATE == 1)
  {
    digitalWrite(LED_BUILTIN, 1);
    UpRight.writeMicroseconds (OPEN_UpRight);
    UpLeft.writeMicroseconds (OPEN_UpLeft);
    DownRight.writeMicroseconds (OPEN_DownRight);
    DownLeft.writeMicroseconds (OPEN_DownLeft);
    if (digitalRead (2) == 1)
    {
      if(debounce == 0)
      {
        debounce = 1;
        debouncetime = millis();
      }
      else if(debounce == 1 && ((millis() - debouncetime) > MINPRESS))
      {
        DRS_STATE++;
      }
    }
    else if(digitalRead (2) == 0)
    {
      debounce = 0;
    }
  }
  else if (DRS_STATE == 2)
  {
    digitalWrite(LED_BUILTIN, 1);
    UpRight.writeMicroseconds (OPEN_UpRight);
    UpLeft.writeMicroseconds (OPEN_UpLeft);
    DownRight.writeMicroseconds (OPEN_DownRight);
    DownLeft.writeMicroseconds (OPEN_DownLeft);
    if (digitalRead (2) == 0)
    {
      if(debounce == 0)
      {
        debounce = 1;
        debouncetime = millis();
      }
      else if(debounce == 1 && ((millis() - debouncetime) > MINPRESS))
      {
        DRS_STATE++;
      }
    }
    else if(digitalRead (2) == 1)
    {
      debounce = 0;
    }
  }
  else if (DRS_STATE == 3)
  {
    digitalWrite(LED_BUILTIN, 0);
    UpRight.writeMicroseconds (CLOSE_UpRight);
    UpLeft.writeMicroseconds (CLOSE_UpLeft);
    DownRight.writeMicroseconds (CLOSE_DownRight);
    DownLeft.writeMicroseconds (CLOSE_DownLeft);
    if (digitalRead (2) == 1)
    {
      if(debounce == 0)
      {
        debounce = 1;
        debouncetime = millis();
      }
      else if(debounce == 1 && ((millis() - debouncetime) > MINPRESS))
      {
        DRS_STATE++;
      }
    }
    else if(digitalRead (2) == 0)
    {
      debounce = 0;
    }
  }
  else
  {
    digitalWrite(LED_BUILTIN, 0);
    UpRight.writeMicroseconds (CLOSE_UpRight);
    UpLeft.writeMicroseconds (CLOSE_UpLeft);
    DownRight.writeMicroseconds (CLOSE_DownRight);
    DownLeft.writeMicroseconds (CLOSE_DownLeft);
    DRS_STATE = 0;
  }

  if (TESTMODE == 0)
  {
    int steeringpos = analogRead(STEERING);
    if (LIMIT1 < LIMIT2)
    {
      if (steeringpos <= LIMIT1 || steeringpos >= LIMIT2)
      {
        DRS_STATE = 0;
      }
    }
    else if (LIMIT1 > LIMIT2)
    {
      if (steeringpos >= LIMIT1 || steeringpos <= LIMIT2)
      {
        DRS_STATE = 0;
      }
    }
    else
    {
      DRS_STATE = 0;
    }

    int brakepos = analogRead(BRAKE);
    if (THRES_TYPE == HIGHTHRES)
    {
      if (THRES_VALUE >= brakepos)
      {
        DRS_STATE = 0;
      }
    }
    else if (THRES_TYPE == LOWTHRES)
    {
      if (THRES_VALUE <= brakepos)
      {
        DRS_STATE = 0;
      }
    }
    else
    {
      DRS_STATE = 0;
    }
  }
  if (Serial.read() == 't')
  {
    Serial.print("Steering: ");
    Serial.println(analogRead(STEERING));
    Serial.print("Brake: ");
    Serial.println(analogRead(BRAKE));
  }
}

