/*
 *    Copyright 2013 Alberto Ruiz <aruiz@gnome.org>
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

