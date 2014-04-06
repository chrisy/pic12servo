pic12servo
==========

This is a simple program to drive a hobby servo with a PIC12F683. It was
prepared using the MPLAB X IDE and the xc8 compiler.

The code sets up an analog-to-digital convertor input on pin 7 and
a PWM output on pin 5. It also sets up pulse outputs on pins 2 and 3
to allow us to measure the loop timing on an oscilloscope. The output
on pin 2 should be slow enough for a blinking LED.

The program loops reading the 10-bit value from the ADC and sets the
duty cycle of the PWM to a value derived from it.

The usable range for most servos requires a pulse length of between
about 1ms to 2ms (which represents the full range of motion for the
servo) with an overall pulse rate greater than 50Hz. This program
configures the PWM output to something close to 61Hz and calculates
the duty cycle value to correspond to a pulse of between about 1 and
2ms.

By hooking up a simple 10K ohm linear potentiometer wiper to pin 7,
with the pot ends across 0v and Vdd (the positive power to the PIC,
for example 5v) then the relative position of the pot will represent
the relative position of the servo motor across its full range.

Suitable hardware designs to facilitate this are in the hardware
directory.
