/*
 * =============================================================================
 *
 *       Filename:  spaceship_interface.c
 *
 *    Description:  project 2 arduino starter kit 
 *
 *        Version:  1.0
 *        Created:  10/10/2018 10:20:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nisennenmondai
 *   Organization:  
 *
 * =============================================================================
 */

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

#define TRUE  0x01
#define DELAY 500

int main(void)
{
        /* set digital pin 3, 4, 5 of PORTD for output*/
        DDRD |= 0x38;




init:   while(TRUE) {
                /* turns on green led */
                PORTD |= 1 << DDD3;
                /* checks state of PIND2 */
                if (PIND & (1 << PIND2)) {
                        /* turns off green led */
                        PORTD &= ~(1 << DDD3);
                        /* turns on red led */
                        PORTD |= 1 << DDD4;
                        PORTD |= 1 << DDD5;
                        _delay_ms(DELAY);

                        break;
                }
        }

        while(TRUE) {
                if (PIND & (1 << PIND2)) {
                        /* turns off red led */
                        PORTD &= ~(1 << DDD4);
                        PORTD &= ~(1 << DDD5);
                        _delay_ms(DELAY/2);
                        goto init;
                }
        }
}
