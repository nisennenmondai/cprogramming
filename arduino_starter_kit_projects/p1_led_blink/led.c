/*
 * =============================================================================
 *
 *       Filename:  led.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/08/2018 01:42:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void)
{
        /* set pin 5 of PORTB for output*/
        DDRB |= _BV(DDB5);

        while(1) {
                /* set pin 5 high to turn led on */
                PORTB |= _BV(PORTB5);
                _delay_ms(BLINK_DELAY_MS);

                /* set pin 5 low to turn led off */
                PORTB &= ~_BV(PORTB5);
                _delay_ms(BLINK_DELAY_MS);
        }
}
