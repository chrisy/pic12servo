/* 
 * File:    servo_driver.c
 * Author:  Chris Luke <chrisy@flirble.org>
 * License: MIT (c) 2014 Chris Luke
 *
 * Created on February 28, 2014, 8:46 AM
 */

#include "config.h"
#include <xc.h>

#include <stdio.h>
#include <stdlib.h>


/*
 * Simple loop to read ADC value and set PWM duty
 * to the same value as a ratio of its range.
 * GP0 is the analog input. Pin 7.
 * GP2 is the PWM outut. Pin 5.
 */
int main(int argc, char** argv) {
    TRISIO = 0x00; /* Default all IO to input */

    /* Setup ADC */

    ADCON0bits.ADFM = 1; /* right justified result */
    ADCON0bits.VCFG = 0; /* Use Vdd as Vref */

    /* We only need one ADC input */
    ADCON0bits.CHS = 0;
    ANSELbits.ANS = 1;
    TRISIObits.TRISIO0 = 1;
    
    /* 16 TOSC on an 8MHz internal clock gives us 2us
     * sample time. We need minimum of 1.6us */
    ANSELbits.ADCS = 0b101;

    ADON = 1; /* Emable the ADC */

    /* Setup PWM */
    TRISIObits.TRISIO2 = 0; /* Output pin */
    PR2 = 0xff; /* Slowest PWM possible */
    CCP1CONbits.DC1B = 0;
    CCPR1L = 0;
    T2CONbits.T2CKPS = 2; /* Timer 2 16:1 prescale */
    T2CONbits.TMR2ON = 1; /* TImer 2 on */
    CCP1CONbits.CCP1M = 0b1100; /* PWM mode */

    /* Let it all settle */
    __delay_ms(1);
    
    for(;;) { /* Loop forver */
        unsigned int value;
        
        /* Trigger ADC */
        ADCON0bits.CHS = 0;
        ADCON0bits.GO = 1;

        /* Wait for conversion */
        while(ADCON0bits.GO);;

        /* Read ADC */
        value = ADRESH << 8;
        value |= ADRESL;

        /* Set PWM */
        CCP1CONbits.DC1B = value & 0x03; /* Two LSB's */
        CCPR1L = (value >> 2) & 0xff; /* Eight LSB's */

        /* Wait a while - mostly to let ADC reset */
        __delay_us(100);
    }
}

