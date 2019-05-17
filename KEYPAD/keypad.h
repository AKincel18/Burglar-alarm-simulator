/*
 * keypad    atmega16    F_CPU = 8000000 Hz
 *
 * Created on: 02.01.2019
 *     Author: admin
*/

#ifndef KEYPAD_
#define KEYPAD_
uint8_t GetKeyPressed();
int checkPassword();
int timeOut();
void setWrongPassword();
void getPassword();
#endif  /* KEYPAD_ */