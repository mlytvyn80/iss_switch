/* HAL (Hardware Abstraction Layer)
 * Here all Microsontroller-dependant code have to be placed
 *
 */
#ifndef HAL_H_
#define HAL_H_

#include <avr/io.h>

#define LED_PORT PORTB
#define LED_REGISTER DDRB
#define LED1_PIN 3
#define LED2_PIN 4
#define LED3_PIN 5

#define RELAIS_PORT PORTB
#define RELAIS_REGISTER DDRB
#define RELAIS1_PIN 0
#define RELAIS2_PIN 1
#define RELAIS3_PIN 2
#define RELAIS_COUNT 3

#define BUTTON_PORT PORTD
#define BUTTON_REGISTER DDRD
#define BUTTON1_PIN 0
#define BUTTON2_PIN 1
#define BUTTON3_PIN 3

#define SELECTED_INPUT_ADDR 46 //!< Address of selected input channel at the EEPROMs


#endif // HAL_H_
