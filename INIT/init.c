/*
 * init.c    atmega16    F_CPU = 8000000 Hz
 *
 * Created on: 02.01.2019
 *     Author: admin
*/
#include <avr/io.h>
#include "init.h"
 void init ()
{
    //DIODY
    //dioda niebieska -> uzbrojenie alarmu
    DDRC  |= ( 1 << PC6 ); //wyjscie
    PORTC |= ( 1 << PC6 );    //stan wysoki -> nie swieci

    //dioda zielona - swieci ciagle -> zasilanie
    DDRB  |= ( 1 << PB2 ); //wyjscie
    PORTB &= ~( 1 << PB2 );    //stan niski -> swieci zielona

    //RGB -> zielona PC0, czerwona PC1 -> poprawnosc kodu
    DDRC |= (1<<PC0) |  1<<PC1 ;
    PORTC &= ~( (1<<PC0) |  1<<PC1);

    //czerwone
    DDRD  |= ( 1 << PD6 );
    PORTD |= ( 1 << PD6 );

    DDRD  |= ( 1 << PD5 );
    PORTD |= ( 1 << PD5 );

    DDRD  |= ( 1 << PD4 );
    PORTD |= ( 1 << PD4 );

    DDRD  |= ( 1 << PD3 );
    PORTD |= ( 1 << PD3 );

    //zolta - jest wprowadzany kod
    DDRD  |= ( 1 << PD2 );
    PORTD |= ( 1 << PD2 );

    //PRZYCISKI
    DDRB &= ~ ( 1 << PB1 );  //uzbrojenie alarmu
    PORTB |= ( 1 << PB1 );

    DDRB &= ~ ( 1 << PB0 );  //resetowanie urzadzenia po wprowadzniu kodu
    PORTB |= ( 1 << PB0 );


    //CZUJNIK DZWIEKU
    DDRA &= ~( 1 << PA7 );    //wejscie
    //BUZZER
    DDRD  |= ( 1 << PD0 );
    PORTD |= ( 1 << PD0 );    //wyjscie
}