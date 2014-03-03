pic12servo
==========

This is a simple program to drive a hobby servo with a PIC12F683.

The code sets up an analog-to-digital convertor input on pin 7 and
a PWM output on pin 5.

It loops reading the 10-bit value from the ADC and sets the duty cycle
of the PWM to that value.

By hooking up a simple linear potentiometer wiper to pin 7, with the
pot ends across 0v and Vdd (the positive power to the PIC, for example
5v) then the relative position of the pot will represent the relative
position of the servo motor across its full range.

