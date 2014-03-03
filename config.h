/* 
 * File:    config.h
 * Author:  Chris Luke <chrisy@flirble.org>
 * License: MIT (c) 2014 Chris Luke
 *
 * Created on February 28, 2014, 8:52 AM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif


// System configuration
#if defined(_12F683) && !defined(__12F683)
#define __12F683
#endif

#if defined(__12F683)
#pragma config FCMEN = OFF          // Failsafe clock monitor
#pragma config IESO = OFF           // Internal/external osc switchover
//#pragma config BODEN = 0x0          // Brown-out detect off
#pragma config CPD = OFF            // Data EEPROM protection
#pragma config CP = OFF             // Code EEPROM protection
#pragma config MCLRE = OFF          // !MCLR disable
#pragma config PWRTE = OFF          // Power up timer disable
#pragma config WDTE = OFF           // Watchdog timer disable
#pragma config FOSC = 0x6           // Internal clock, I/O on RA4/RA5
#else
#error This code is designed for a PIC12F683!
#endif

#define _XTAL_FREQ 8000000

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

