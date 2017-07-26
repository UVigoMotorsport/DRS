
#include <Servo.h>
#include <EEPROM.h>
#define ABSMAX 2500
#define ABSMIN 500

//brake
#define HIGHTHRES 1
#define LOWTHRES 2

Servo UpRight; //D12
Servo UpLeft; //D11
Servo DownRight; //D10
Servo DownLeft; //D9

int CLOSE_UpRight = 900;
int addr_CLOSE_UpRight = 0;
int OPEN_UpRight = 2100;
int addr_OPEN_UpRight = addr_CLOSE_UpRight + sizeof(CLOSE_UpRight);

int CLOSE_UpLeft = 900;
int addr_CLOSE_UpLeft = addr_OPEN_UpRight + sizeof(OPEN_UpRight);
int OPEN_UpLeft = 2100;
int addr_OPEN_UpLeft = addr_CLOSE_UpLeft + sizeof(CLOSE_UpLeft);

int CLOSE_DownRight = 900;
int addr_CLOSE_DownRight = addr_OPEN_UpLeft + sizeof(OPEN_UpLeft);
int OPEN_DownRight = 2100;
int addr_OPEN_DownRight = addr_CLOSE_DownRight + sizeof(CLOSE_DownRight);

int CLOSE_DownLeft = 900;
int addr_CLOSE_DownLeft = addr_OPEN_DownRight + sizeof(OPEN_DownRight);
int OPEN_DownLeft = 2100;
int addr_OPEN_DownLeft = addr_CLOSE_DownLeft + sizeof(CLOSE_DownLeft);

int THRES_TYPE = LOWTHRES;
int addr_THRES_TYPE = addr_OPEN_DownLeft + sizeof(OPEN_DownLeft);
int THRES_VALUE = 120;
int addr_THRES_VALUE = addr_THRES_TYPE + sizeof(THRES_TYPE);

//steering
int LIMIT1 = 0;
int addr_LIMIT1 = addr_THRES_VALUE + sizeof(THRES_VALUE);
int LIMIT2 = 1023;
int addr_LIMIT2 = addr_LIMIT1 + sizeof(LIMIT1);
int CENTRE = 511;
int addr_CENTRE = addr_LIMIT2 + sizeof(LIMIT2);
float ZONE = 0.25;
int addr_ZONE = addr_CENTRE + sizeof(CENTRE);

int WRITTEN = 0;
int addr_WRITTEN = addr_ZONE + sizeof(ZONE);



int DRS_STATE = 0;

void setup() {
  // put your setup code here, to run once:
  EEPROM.get(addr_WRITTEN, WRITTEN);
  if (WRITTEN != 1)
  {
    EEPROM.put(addr_CLOSE_UpRight, CLOSE_UpRight);
    EEPROM.put(addr_OPEN_UpRight, OPEN_UpRight);
    EEPROM.put(addr_CLOSE_UpLeft, CLOSE_UpLeft);
    EEPROM.put(addr_OPEN_UpLeft, OPEN_UpLeft);
    EEPROM.put(addr_CLOSE_DownRight, CLOSE_DownRight);
    EEPROM.put(addr_OPEN_DownRight, OPEN_DownRight);
    EEPROM.put(addr_CLOSE_DownLeft, CLOSE_DownLeft);
    EEPROM.put(addr_OPEN_DownLeft, OPEN_DownLeft);
    EEPROM.put(addr_THRES_TYPE, THRES_TYPE);
    EEPROM.put(addr_THRES_VALUE, THRES_VALUE);
    EEPROM.put(addr_LIMIT1, LIMIT1);
    EEPROM.put(addr_LIMIT2, LIMIT2);
    EEPROM.put(addr_CENTRE, CENTRE);
    EEPROM.put(addr_ZONE, ZONE);
    WRITTEN = 1;
    EEPROM.put(addr_WRITTEN, WRITTEN);
  }
  else
  {
    EEPROM.get(addr_CLOSE_UpRight, CLOSE_UpRight);
    EEPROM.get(addr_OPEN_UpRight, OPEN_UpRight);
    EEPROM.get(addr_CLOSE_UpLeft, CLOSE_UpLeft);
    EEPROM.get(addr_OPEN_UpLeft, OPEN_UpLeft);
    EEPROM.get(addr_CLOSE_DownRight, CLOSE_DownRight);
    EEPROM.get(addr_OPEN_DownRight, OPEN_DownRight);
    EEPROM.get(addr_CLOSE_DownLeft, CLOSE_DownLeft);
    EEPROM.get(addr_OPEN_DownLeft, OPEN_DownLeft);
    EEPROM.get(addr_THRES_TYPE, THRES_TYPE);
    EEPROM.get(addr_THRES_VALUE, THRES_VALUE);
    EEPROM.get(addr_LIMIT1, LIMIT1);
    EEPROM.get(addr_LIMIT2, LIMIT2);
    EEPROM.get(addr_CENTRE, CENTRE);
    EEPROM.get(addr_ZONE, ZONE);
  }
  pinMode(2, INPUT);
  UpRight.attach(12);
  UpLeft.attach(11);
  DownRight.attach(10);
  DownLeft.attach(9);
  UpRight.writeMicroseconds (CLOSE_UpRight);
  UpLeft.writeMicroseconds (CLOSE_UpLeft);
  DownRight.writeMicroseconds (CLOSE_DownRight);
  DownLeft.writeMicroseconds (CLOSE_DownLeft);
  Serial.begin (57600);
  Serial.println ("HEY YO");
}

void loop() {
  if (DRS_STATE == 0)
  {
    UpRight.writeMicroseconds (CLOSE_UpRight);
    UpLeft.writeMicroseconds (CLOSE_UpLeft);
    DownRight.writeMicroseconds (CLOSE_DownRight);
    DownLeft.writeMicroseconds (CLOSE_DownLeft);
    if (digitalRead (2) == 1)
    {
      DRS_STATE++;
    }
  }
  else if (DRS_STATE == 1)
  {
    UpRight.writeMicroseconds (OPEN_UpRight);
    UpLeft.writeMicroseconds (OPEN_UpLeft);
    DownRight.writeMicroseconds (OPEN_DownRight);
    DownLeft.writeMicroseconds (OPEN_DownLeft);
    if (digitalRead (2) == 0)
    {
      DRS_STATE++;
    }
  }
  else if (DRS_STATE == 2)
  {
    UpRight.writeMicroseconds (OPEN_UpRight);
    UpLeft.writeMicroseconds (OPEN_UpLeft);
    DownRight.writeMicroseconds (OPEN_DownRight);
    DownLeft.writeMicroseconds (OPEN_DownLeft);
    if (digitalRead (2) == 1)
    {
      DRS_STATE ++;
    }
  }
  else if (DRS_STATE == 3)
  {
    UpRight.writeMicroseconds (CLOSE_UpRight);
    UpLeft.writeMicroseconds (CLOSE_UpLeft);
    DownRight.writeMicroseconds (CLOSE_DownRight);
    DownLeft.writeMicroseconds (CLOSE_DownLeft);
    if (digitalRead (2) == 0)
    {
      DRS_STATE = 0;
    }
  }
  else
  {
    UpRight.writeMicroseconds (CLOSE_UpRight);
    UpLeft.writeMicroseconds (CLOSE_UpLeft);
    DownRight.writeMicroseconds (CLOSE_DownRight);
    DownLeft.writeMicroseconds (CLOSE_DownLeft);
    DRS_STATE = 0;
  }

  int steeringpos = analogRead(A0);
  if (LIMIT1 < LIMIT2)
  {
    if (((LIMIT2 - CENTRE)*ZONE) + CENTRE < steeringpos || steeringpos < CENTRE - (CENTRE - LIMIT1)*ZONE)
    {
      DRS_STATE = 0;
    }
  }
  else if (LIMIT1 > LIMIT2)
  {
    if (((LIMIT1 - CENTRE)*ZONE) + CENTRE < steeringpos || steeringpos < CENTRE - (CENTRE - LIMIT2)*ZONE)
    {
      DRS_STATE = 0;
    }
  }
  else
  {
    DRS_STATE = 0;
  }

  int brakepos = analogRead(A1);
  if (THRES_TYPE == HIGHTHRES)
  {
    if (THRES_VALUE > brakepos)
    {
      DRS_STATE = 0;
    }
  }
  else if (THRES_TYPE == LOWTHRES)
  {
    if (THRES_VALUE < brakepos)
    {
      DRS_STATE = 0;
    }
  }
  else
  {
    DRS_STATE = 0;
  }

  int in = Serial.read();
  if (in == 'a')
  {
    Serial.println("what");
  }
  else if (in == 's')
  {
    int in2 = 0;
    while (in != 'q')
    {
      in = Serial.read();
      if (in == '1')
      {
        in2 = 0;
        UpRight.writeMicroseconds (OPEN_UpRight);
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (OPEN_UpRight < ABSMAX)
            {
              OPEN_UpRight++;
              UpRight.writeMicroseconds (OPEN_UpRight);
              Serial.print("OPEN_UpRight is ");
              Serial.println(OPEN_UpRight);
            }
          }
          else if (in2 == '-')
          {
            if (OPEN_UpRight > ABSMIN)
            {
              OPEN_UpRight--;
              UpRight.writeMicroseconds (OPEN_UpRight);
              Serial.print("OPEN_UpRight is ");
              Serial.println(OPEN_UpRight);
            }
          }
        }
        EEPROM.put(addr_OPEN_UpRight, OPEN_UpRight);
      }
      else if (in == '2')
      {
        in2 = 0;
        UpLeft.writeMicroseconds (OPEN_UpLeft);
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (OPEN_UpLeft < ABSMAX)
            {
              OPEN_UpLeft++;
              UpLeft.writeMicroseconds (OPEN_UpLeft);
              Serial.print("OPEN_UpLeft is ");
              Serial.println(OPEN_UpLeft);
            }
          }
          else if (in2 == '-')
          {
            if (OPEN_UpLeft > ABSMIN)
            {
              OPEN_UpLeft--;
              UpLeft.writeMicroseconds (OPEN_UpLeft);
              Serial.print("OPEN_UpLeft is ");
              Serial.println(OPEN_UpLeft);
            }
          }
        }
        EEPROM.put(addr_OPEN_UpLeft, OPEN_UpLeft);
      }
      else if (in == '3')
      {
        in2 = 0;
        DownRight.writeMicroseconds (OPEN_DownRight);
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (OPEN_DownRight < ABSMAX)
            {
              OPEN_DownRight++;
              UpLeft.writeMicroseconds (OPEN_DownRight);
              Serial.print("OPEN_DownRight is ");
              Serial.println(OPEN_DownRight);
            }
          }
          else if (in2 == '-')
          {
            if (OPEN_DownRight > ABSMIN)
            {
              OPEN_DownRight--;
              DownRight.writeMicroseconds (OPEN_DownRight);
              Serial.print("OPEN_DownRight is ");
              Serial.println(OPEN_DownRight);
            }
          }
        }
        EEPROM.put(addr_OPEN_DownRight, OPEN_DownRight);
      }
      else if (in == '4')
      {
        in2 = 0;
        DownLeft.writeMicroseconds (OPEN_DownLeft);
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (OPEN_DownLeft < ABSMAX)
            {
              OPEN_DownLeft++;
              DownLeft.writeMicroseconds (OPEN_DownLeft);
              Serial.print("OPEN_DownLeft is ");
              Serial.println(OPEN_DownLeft);
            }
          }
          else if (in2 == '-')
          {
            if (OPEN_DownLeft > ABSMIN)
            {
              OPEN_DownLeft--;
              DownLeft.writeMicroseconds (OPEN_DownLeft);
              Serial.print("OPEN_DownLeft is ");
              Serial.println(OPEN_DownLeft);
            }
          }
        }
        EEPROM.put(addr_OPEN_DownLeft, OPEN_DownLeft);
      }
      else if (in == '5')
      {
        in2 = 0;
        UpRight.writeMicroseconds (CLOSE_UpRight);
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (CLOSE_UpRight < ABSMAX)
            {
              CLOSE_UpRight++;
              UpRight.writeMicroseconds (CLOSE_UpRight);
              Serial.print("CLOSE_UpRight is ");
              Serial.println(CLOSE_UpRight);
            }
          }
          else if (in2 == '-')
          {
            if (CLOSE_UpRight > ABSMIN)
            {
              CLOSE_UpRight--;
              UpRight.writeMicroseconds (CLOSE_UpRight);
              Serial.print("CLOSE_UpRight is ");
              Serial.println(CLOSE_UpRight);
            }
          }
        }
        EEPROM.put(addr_CLOSE_UpRight, CLOSE_UpRight);
      }
      else if (in == '6')
      {
        in2 = 0;
        UpLeft.writeMicroseconds (CLOSE_UpLeft);
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (CLOSE_UpLeft < ABSMAX)
            {
              CLOSE_UpLeft++;
              UpLeft.writeMicroseconds (CLOSE_UpLeft);
              Serial.print("CLOSE_UpLeft is ");
              Serial.println(CLOSE_UpLeft);
            }
          }
          else if (in2 == '-')
          {
            if (CLOSE_UpLeft > ABSMIN)
            {
              CLOSE_UpLeft--;
              UpLeft.writeMicroseconds (CLOSE_UpLeft);
              Serial.print("CLOSE_UpLeft is ");
              Serial.println(CLOSE_UpLeft);
            }
          }
        }
        EEPROM.put(addr_CLOSE_UpLeft, CLOSE_UpLeft);
      }
      else if (in == '7')
      {
        in2 = 0;
        DownRight.writeMicroseconds (CLOSE_DownRight);
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (CLOSE_DownRight < ABSMAX)
            {
              CLOSE_DownRight++;
              DownRight.writeMicroseconds (CLOSE_DownRight);
              Serial.print("CLOSE_DownRight is ");
              Serial.println(CLOSE_DownRight);
            }
          }
          else if (in2 == '-')
          {
            if (CLOSE_DownRight > ABSMIN)
            {
              CLOSE_DownRight--;
              DownRight.writeMicroseconds (CLOSE_DownRight);
              Serial.print("CLOSE_DownRight is ");
              Serial.println(CLOSE_DownRight);
            }
          }
        }
        EEPROM.put(addr_CLOSE_DownRight, CLOSE_DownRight);
      }
      else if (in == '8')
      {
        in2 = 0;
        DownLeft.writeMicroseconds (CLOSE_DownLeft);
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (CLOSE_DownLeft < ABSMAX)
            {
              CLOSE_DownLeft++;
              DownLeft.writeMicroseconds (CLOSE_DownLeft);
              Serial.print("CLOSE_DownLeft is ");
              Serial.println(CLOSE_DownLeft);
            }
          }
          else if (in2 == '-')
          {
            if (CLOSE_DownLeft > ABSMIN)
            {
              CLOSE_DownLeft--;
              DownLeft.writeMicroseconds (CLOSE_DownLeft);
              Serial.print("CLOSE_DownLeft is ");
              Serial.println(CLOSE_DownLeft);
            }
          }
        }
        EEPROM.put(addr_CLOSE_DownLeft, CLOSE_DownLeft);
      }
      else if (in == 's')
      {
        Serial.println("Center the steering wheel and press d");
        in = Serial.read();
        while (in != 'd')
        {
          in = Serial.read();
        }
        CENTRE = analogRead(A0);
        EEPROM.put(addr_CENTRE, CENTRE);
        Serial.println("Turn the steering wheel all the way to one side and press d");
        in = Serial.read();
        while (in != 'd')
        {
          in = Serial.read();
        }
        LIMIT1 = analogRead(A0);
        EEPROM.put(addr_LIMIT1, LIMIT1);
        Serial.println("Turn the steering wheel all the way to the other side and press d");
        in = Serial.read();
        while (in != 'd')
        {
          in = Serial.read();
        }
        LIMIT2 = analogRead(A0);
        EEPROM.put(addr_LIMIT2, LIMIT2);
      }
      else if (in == 'z')
      {
        in2 = 0;
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (ZONE < 1.0)
            {
              ZONE += 0.01;
              Serial.print("ZONE is ");
              Serial.println(ZONE);
            }
          }
          else if (in2 == '-')
          {
            if (ZONE > 0.02)
            {
              ZONE -= .01;
              Serial.print("ZONE is ");
              Serial.println(ZONE);
            }
          }
        }
        EEPROM.put(addr_ZONE, ZONE);
      }
      else if (in == 'b')
      {
        Serial.println("Don't touch the brake and press d");
        in = Serial.read();
        while (in != 'd')
        {
          in = Serial.read();
        }
        int brakenone = analogRead(A1);
        Serial.println("Apply the level of pressure where you would want the DRS to deactivate and press d");
        in = Serial.read();
        while (in != 'd')
        {
          in = Serial.read();
        }
        THRES_VALUE = analogRead(A1);
        EEPROM.put(addr_THRES_VALUE, THRES_VALUE);
        if(THRES_VALUE < brakenone)
        {
          THRES_TYPE = LOWTHRES;
        }
        else
        {
          THRES_TYPE = HIGHTHRES;
        }
        EEPROM.put(addr_THRES_TYPE, THRES_TYPE);
      }
    }
  }
}

