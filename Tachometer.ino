/* Arduino Tachometer
 *
 * This code will display the RPM count on 4x 7 segment displays as well as
 * print RPM to serial port at 250 ms intervals.
 *
 * WARNING: Author has not yet tested this code. It might not even compile yet.
 *
 * Copyright (c) 2015, Adam Carmichael <carneeki@carneeki.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "SevSeg.h"

#define T_INT 2;      // Tachometer interrupt change according to:
                      // http://arduino.cc/en/Reference/attachInterrupt

#define MULTIPLIER 1; // Signals per revolution
#define UPDATE 250;   // Milliseconds between updates
#define BAUDRATE 9600; // serial baudrate

#define TRIGGER RISING; // RISING edge or FALLING edge

// Seven segment display. Refer to SevSeg.README.md for full details
#define SEGS_COMMON COMMON_ANODE; // COMMON_ANODE, COMMON_CATHODE
                                  // or one of the transistor variants
byte numDigits     = 4;
byte digitPins[]   = {2,3,4,5};
byte segmentPins[] = {6,7,8,9,10,11,12,13};
SevSeg segs;


unsigned long period;  // period between pulses
unsigned long prev;    // previous time
unsigned long display; // counter for display time
unsigned int rpm;      // rpm to be printed

void setup()
{
  segs.begin(SEGS_COMMON, 4)
  Serial.begin(BAUDRATE);

  attachInterrupt(T_INT, pulse, TRIGGER);

  period = 0;
  prev = 0;
  display = 0;
}

void loop()
{
  if( (millis() - display) >= UPDATE )
  {
    display = millis();

    if(period!=0)
      rpm = (unsigned int) (60000)/(period * MULTIPLIER);
    else
      rpm = 0;

    Serial.print("RPM" + rpm); // display RPM
    segs.setNumber(rpm, 0);
  }

  segs.refreshDisplay();
}

void pulse()
{
  period = (millis()-prev);
  prev = millis();
}
