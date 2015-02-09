Tacho
=====

This will display the RPM count on 4x 7 segment displays as well as print RPM to
serial port at 250 ms intervals.

# Wiring it up
The input pin needs to be a digital input on which an interrupt can be attached.
Please see http://arduino.cc/en/Reference/attachInterrupt for details on which
pins can have interrupts attached. For many of the clone Arduino boards, you
will need to figure out which board you have. The 'Due' might be a good starting
point.

The input will need to either pulse HIGH or pulse LOW. Change RISING / FALLING
in attachInterrupt() in the setup to suit. Alternatively, a NOT gate can be
added. Voltage will need to be 0V and 5V to trigger rising and falling edges.

## Possible inputs
* Hall effect sensors
* IR LEDs and IR LDRs
* Frequency generators (though this is limited to ~166Hz as that is about
  9999 BPM).

## Other configuration items
Greater accuracy can be achieved through increasing the number of sensor
triggers, for example, three magnets evenly spaced on a shaft you are measuring
and set the MULTIPLIER macro to 3.

# Known issues
* WONTFIX: Approximately every 50 days the milliseconds timer will rollover
causing one erroneous measurement. This is a limitation of how Arduino handles
the millisecond counter internally, and is unlikely to affect most users.
* WONTFIX: Clock drift on the Arduino will affect overall accuracy. The amount
will vary depending on reference clock used and the environment the counter is
placed in.

# Libraries
The tachometer project uses (and includes) the SevSeg library available from:
https://github.com/DeanIsMe/SevSeg
