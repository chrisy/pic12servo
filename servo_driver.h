/* 
 * File:   servo_driver.h
 * Author:  Chris Luke <chrisy@flirble.org>
 * License: MIT (c) 2014 Chris Luke
 */

#ifndef SERVO_DRIVER_H
#define	SERVO_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif


// Sometimes the IDE doesn't define these implicitly
#ifndef __PICCPRO__
#define __PICCPRO__
#endif
#if defined(_12F683) && !defined(__12F683)
#define __12F683
#endif


/* With a processor clock of 1MHz and 16:1 prescaler, PR2 0xff gives
 * us a 16.38ms PWM period (aka  61Hz) */
#define SET_PR2 (0xff)          /* Maximum period - 16.38ms */

#define SET_IRCF (0b100)        /* 1MHz */
#define _XTAL_FREQ (1000000)    /* 1MHz */


#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_DRIVER_H */

