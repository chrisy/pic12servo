/* 
 * File:    config.h
 * Author:  Chris Luke <chrisy@flirble.org>
 * License: MIT (c) 2014 Chris Luke
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "servo_driver.h"
// System configuration
#if defined(__12F683)
#pragma config FCMEN = ON           // Failsafe clock monitor
#pragma config IESO = OFF           // Internal/external osc switchover
#pragma config BOREN = 0x0          // Brown-out detect off
#pragma config CPD = OFF            // Data EEPROM protection
#pragma config CP = OFF             // Code EEPROM protection
#pragma config MCLRE = ON          // !MCLR disable
#pragma config PWRTE = ON           // Power up timer disable
#pragma config WDTE = OFF           // Watchdog timer disable
#pragma config FOSC = INTOSCIO           // Internal clock, I/O on RA4/RA5
#else
#error This code is designed for a PIC12F683!
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

