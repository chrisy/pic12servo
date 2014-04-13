The ServoDriver hardware
========================

servodriver.sch and servodriver.brd are Eagle diagrams.

servodriver.*.tap are G-Code CAM scripts generated using gcode-pcb.ulp.

Bill of Materials
=================

IC1		PIC12F683P (programmed, with 8 pin IC socket)
IC2		7805

R1		10K Pot
R2		Link
R3		620R
R4		620R

C1		0.1uF
C2		0.1uF
C3		0.1uF
C4		100uF electrolytic (25V or higher)
C5		10uF electrolytic (10V or higher)
C6		0.1uF

D1		1N4004

LED1	3mm red LED
LED2	3mm red LED

JP1		2-way Screw terminal
JP2		3-way 0.1" pitch pin header
