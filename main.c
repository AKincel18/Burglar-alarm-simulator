    /*
* main.c    ATmega16    F_CPU = 8000000 Hz
*
* Created on: 17.11.2018
*     Author: admin
*/
// do³¹czanie systemowych plików nag³ówkowych
#include <avr/io.h>
#include <util/delay.h>
#include "INIT/init.h"
#include "KEYPAD/keypad.h"

int main( void ) {

    init();  // sekcja inicjalizacji peryferiów
    //zmienne sterujace prace programu
    int beep = 0;
    int alarm = 0;
    int end = 0;

    TCCR1B |= ((1 << CS10) | (1 << CS11)); //Ustawia timer z preskalerem Fcpu/64

    while ( 1 ) {

        if ( !( PINB & ( 1 << PB1 ) ) ) { //uzbrojenie alarmu
            _delay_ms( 200 ); //czas na uzbrojenie alarmu
            PORTC &= ~( 1 << PC6 ); //zalaczenie diody niebieskiej
            alarm = 0;
            while ( alarm == 0 ) {

                if ( !( PINA & ( 1 << PA7 ) ) ) {    //jesli wystapi dzwiek
                    PORTC |= ( 1 << PC6 ); //wylaczenie diody niebieskiej -> koniec uzbrojenia alarmu


                    PORTD &= ~( 1 << PD2);  //dioda zolta -> czas na wpisanie alarmu
                    getPassword();   //wpisanie hasla
                    PORTD |= ( 1 << PD2);   //wylaczenie diody zoltej


                    if ( checkPassword() == 1 ) { //dobre haslo


                        PORTC |= (1<<PC0);  //dioda zielona -> dobre haslo
                        end = 0;
                        while (end == 0)
                        {
                           if ( !( PINB & ( 1 << PB0 ) ) ) { // po nacisnieciu przycisku powrot do stanu poczatkowego
                               PORTC &= ~( (1<<PC0));
                               end=1;
                           }

                        }


                    } else { //zle haslo
                        PORTC |= 1<<PC1; //dioda czerwona
                        beep = 1;
                        PORTD &= ~( 1 << PD0 );  //wlaczenie buzzera

                        while ( beep == 1 )  {


                            if ( !( PINB & ( 1 << PB0 ) ) ) { //po nacisnieciu przycisku powrot do stanu poczatkowego

                                PORTD |= ( 1 << PD0 );
                                beep = 0;
                                PORTC &= ~( 1<<PC1);

                            }
                        }
                    }
                    alarm = 1;


                }
            }



        }
            PORTC |= ( 1 << PC6 ); //wylaczenie diody niebieskiej


    }
}