#include <Servo.h>

Servo x;
Servo y;

void setup ()
{
  Serial.begin(9600);
  x.attach (3);
  y.attach (2);

  x.write (90);
  y.write (90);
  
  delay (3000);
}

void logLight (int n, int s, int e, int w)
{
  Serial.print (n);
  Serial.print ("-");
  Serial.print (s);
  Serial.print ("-");
  Serial.print (e);
  Serial.print ("-");
  Serial.print (w);
  Serial.println ("");
}

void loop ()
{
  bool jump = false;
  int n = analogRead(0);
  int s = analogRead(1);
  int e = analogRead(2);
  int w = analogRead(3);

  logLight (n,s,e,w);

  if (sqrt(pow(n - s, 2)) > 60 )
  {
    int pos = y.read ();

    if (s > n)
      pos = pos + 1;
    if (n > s)
      pos = pos - 1;

    if (pos > 180)
    {
      pos = 180;
      jump = true;
    }
    if (pos < 5)
    {
      pos = 5;
      jump = true;
    }

    y.write (pos);
  }

  if ( (jump || sqrt(pow(n - s, 2)) < 60) && (pow(e - w, 2)) > 80 )
  {
    int pos = x.read ();

    if (e > w)
      pos = pos + 1;
    if (w > e)
      pos = pos - 1;

    if (pos > 168)
      pos = 168;
    if (pos < 0)
      pos = 0;

    x.write (pos);
  }

  delay (30);
}

