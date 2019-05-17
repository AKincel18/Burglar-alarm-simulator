/*
 * keypad.c    atmega16    F_CPU = 8000000 Hz
 *
 * Created on: 02.01.2019
 *     Author: admin
*/
#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"
#include "diode.h"

int tab[4];  //tablica reprezentujaca kod wpisany z klawiatury
int sec;     //ilosc sekund ktore minely przy wpisywaniu kodu

uint8_t GetKeyPressed() { //obsluga klawiatury, zwraca kod klawisza
    uint8_t r, c;

    PORTA |= 0x0F;
    for ( c = 0;c < 3;c++ ) {
        DDRA &= ~( 0x7F );
        DDRA |= ( 0x40 >> c );

        for ( r = 0;r < 4;r++ ) {
            if ( !( PINA & ( 0x08 >> r ) ) ) { //sprawdzenie czy nastapilo nacisniecie klawisza
                return ( r*3 + c +1);   //zwracanie kodu klawisza: 1->1, 2->2, ..., 10->'*', 11->0, 12->"#"
            }
        }
    }


    return 0xFF;//zwracanie 255 gdy klawisz nie zostal wcisniety

}
int checkPassword()  //password= 1234
{

    if ( tab[0] == 1 && tab[1] == 2 && tab[2] == 3 &&  tab[3] == 4 )
        return 1;
    else
        return 0;
}

int timeOut()
{
    if (TCNT1 >= 15625) //15625 - jedna sekunda
    {
        TCNT1 = 0; //Zerowanie Timera
        sec++;
        if (sec >= 10)
        {
            return 1;
        }

    }
    return 0;
}

void setWrongPassword()
{
    tab[0] = 0;
    tab[1] = 0;
    tab[2] = 0;
    tab[3] = 0;
}

void getPassword() {
    int key; //kod klawisza
    int pos = 0; //ktora pozycja jest wpisywana
    int enterCode = 0; //czy wprowadzany jest kod
    TCNT1 = 0; //Zerowanie Timera
    sec = 0;

    while ( enterCode == 0)
    {
        if (timeOut() == 0)
        {
            while ( GetKeyPressed() != 255 )
            {
                if (timeOut() == 0) //czas sie nie skonczyl
                {

                    key = GetKeyPressed();
                    if ( (key < 10 || key == 11) && (pos<4) )
                    {
                        switchOnDiode(pos);
                        tab[pos] = key;
                        pos++;
                        _delay_ms( 50 );
                    }
                    else if (key == 10) //kasowanie znaku
                    {
                        if (pos != 0)
                        {
                            pos=pos-1;
                            switchOffDiode(pos);
                            _delay_ms( 50 );
                        }
                    }
                    else if (pos == 4 && key==12) //zatwierdzenie kodu
                    {
                        enterCode = 1;
                    }
                }
                else  //czas sie skonczyl
                {
                    enterCode = 1;
                    setWrongPassword();
                }
            }
        }
        else
        {
            enterCode = 1;
            setWrongPassword();
        }

    }
    _delay_ms( 50 );
    resetDiode();
}

