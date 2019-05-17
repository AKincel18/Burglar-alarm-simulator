/*
 * diode.c    atmega16    F_CPU = 8000000 Hz
 *
 * Created on: 02.01.2019
 *     Author: admin
*/
#include <avr/io.h>
#include "diode.h"
void switchOnDiode(int pos)
{
    switch(pos)
    {
       case 0:
            PORTD &= ~( 1 << PD6 );
            break;
       case 1:
            PORTD &= ~( 1 << PD5 );
            break;
       case 2:
            PORTD &= ~( 1 << PD4 );
            break;
       case 3:
            PORTD &= ~( 1 << PD3 );
            break;
    }
}
void switchOffDiode(int pos)
{
    switch(pos)
    {
       case 0:
            PORTD |= ( 1 << PD6 );
            break;
       case 1:
            PORTD |= ( 1 << PD5 );
            break;
       case 2:
            PORTD |= ( 1 << PD4 );
            break;
       case 3:
            PORTD |= ( 1 << PD3 );
            break;


    }
}
void resetDiode()
{
    PORTD |= ( 1 << PD6 );
    PORTD |= ( 1 << PD5 );
    PORTD |= ( 1 << PD4 );
    PORTD |= ( 1 << PD3 );
}