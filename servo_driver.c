/* 
 * File:    servo_driver.c
 * Author:  Chris Luke <chrisy@flirble.org>
 * License: MIT (c) 2014 Chris Luke
 */

#include "servo_driver.h"
#include "config.h"
#include <xc.h>


/*
 * Simple loop to read ADC value and set PWM duty
 * to the same value as a ratio of its range.
 * GP0 is the analog input. Pin 7.
 * GP1 is unused though the board connects it to 0v for shielding. Pin 6.
 * GP2 is the PWM outut. Pin 5.
 * GP3 is unused. Pin 4.
 * GP4 is a loop-interval toggle output. Pin 3.
 * GP5 is an LED output. Pin 2.
 */
int main(int argc, char **argv) {
    unsigned int period, count;
    char o4, o5;

    /* Set the clock speed */
    OSCCONbits.IRCF = SET_IRCF;
    WDTCON = 0x0; /* Make sure watchdog is disabled */

    di(); /* No need for interrupts */

    /* Make sure unused timers are off */
    TMR1ON = 0;
    T1OSCEN = 0;
    CMCON1 = 0;

    /* Setup the I/O */
    GPIO = 0; /* Make sure all outputs are low */
    CMCON0bits.CM = 0b111; /* Disable comparators */
    TRISIO = 0b001111; /* 4,5=out, 0,1,2,3=in */
    nGPPU = 0; /* Enable pullups */


    /* Setup ADC */
    ADCON0bits.ADFM = 1; /* right justified result */
    ADCON0bits.VCFG = 0; /* Use Vdd as Vref */
    WPU0 = 0; /* Disable pullup on this input */
    ADCON0bits.CHS = 0; /* Select channel 0 */
    GO_DONE = 0; /* Make sure this is cleared */
    ANSELbits.ANS = 1; /* Only channel 0 is enabled */
    ANSELbits.ADCS = 0b111; /* Use internal RC oscilator */
    ADON = 1; /* Emable the ADC */

    /* Setup PWM */
    TRISIO2 = 1; /* Disable output on this pin for now */
    PR2 = SET_PR2; /* Set the PWM period (we aim for ~20ms, see config.h)  */
    CCP1CONbits.CCP1M = 0b1100; /* PWM mode */
    CCPR1L = 0; /* Reset PWM output to 0 */
    CCP1CONbits.DC1B = 0;

    /* Set the timer up for PWM operation */
    TMR2IF = 0; /* Make sure this is clear */
    T2CONbits.T2CKPS = 2; /* Timer 2 16:1 prescale */
    T2CONbits.TMR2ON = 1; /* TImer 2 on */

    while(!TMR2IF) { /* Wait for Timer 2 */
        continue;
    }
    TRISIO2 = 0; /* Set the pin as output */
    WPU2 = 0; /* Disable any pullup */

    /* Calculate the PWM period from what we set PR2 to.
     * This will be ms*100, something like 1638 (61Hz) */
    period = (unsigned int)(
            ( ((float)SET_PR2) + 1.0 ) *
            4.0 *
            (1.0/(float)_XTAL_FREQ) *
            16.0 *
            1000.0 *
            100.0
    );

    /* We have an LED on GP5 */
    TRISIO5 = 0;
    WPU5 = 0; /* Disable any pullup */
    o5 = 1;
    count = 0;

    /* And we will toggle GP4 for each iteration of the loop;
     * There's no real reason for this, other than we can
     * hook it up to an oscilloscope to time the loop
     * interval */
    TRISIO4 = 0;
    WPU4 = 0; /* Disable any pullup */
    o4 = 1;

    /* Let it all settle */
    __delay_ms(10);
    
    for(;;) { /* Loop forver */
        unsigned int value, pulse;
        
        /* Trigger ADC. */
        GO_DONE = 1;

        /* Wait for conversion to complete. */
        while(GO_DONE) {
            continue;
        }

        /* Read ADC */
        value = ADRESH << 8;
        value |= ADRESL;

        /* Calculate the target pulse width in ms*100.
         * Useful range for most servos is 1ms to 2ms.
         * The values here give us a bit either side, just in case */
        pulse = 93 + (value / 9);

        /* Now adjust for the period of the timer.
         * We use floating point math for now, for accuracy.
         * Ideally we'd use integer math for speed, though we seem to
         * have enough cycles and memory for this. */
        pulse = (unsigned int)(1024.0 / ((float)period / (float)pulse));

        /* Set PWM */
        CCP1CONbits.DC1B = pulse & 0x03; /* Two LSB's */
        CCPR1L = (pulse >> 2) & 0xff; /* Eight MSB's */

        /* Wait a while - mostly to let ADC reset. */
        __delay_us(100);

        /* Flash the LED */
        ++count;
        if(!count) {
            o5 = o5 == 1 ? 0 : 1;
            GP5 = o5;
        }

        /* Toggle GP4 */
        o4 = o4 == 1 ? 0 : 1;
        GP4 = o4;
    }
}

