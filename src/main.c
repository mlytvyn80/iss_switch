#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "hal.h"
#include "rc5.h"
#include "timer.h"


#define BTN_PRESS_DETECT_THRESHOLD 10


static uint8_t selected_input = 1;
static uint8_t btn1_counter = 0;
static uint8_t btn2_counter = 0;
static uint8_t btn3_counter = 0;

void set_selected_input(uint8_t value)
{
    selected_input = value;
    eeprom_update_byte((uint8_t*)SELECTED_INPUT_ADDR, selected_input);
}

void init_selected_input()
{
    selected_input = eeprom_read_byte((uint8_t*)SELECTED_INPUT_ADDR);

    if(selected_input > RELAIS_COUNT)
        set_selected_input(1);

}

void switch_all_relais_off()
{
    RELAIS_PORT &= ~_BV(RELAIS1_PIN);
    RELAIS_PORT &= ~_BV(RELAIS2_PIN);
    RELAIS_PORT &= ~_BV(RELAIS3_PIN);
}

void switch_relay_on(uint8_t relay_id)
{
    switch_all_relais_off();

    switch(relay_id)
    {
        case(1) : RELAIS_PORT |= _BV(RELAIS1_PIN); return;
        case(2) : RELAIS_PORT |= _BV(RELAIS2_PIN); return;
        case(3) : RELAIS_PORT |= _BV(RELAIS3_PIN); return;
    }

}

void switch_all_leds_off()
{
    LED_PORT &= ~_BV(LED1_PIN);
    LED_PORT &= ~_BV(LED2_PIN);
    LED_PORT &= ~_BV(LED3_PIN);
}

void led_on(uint8_t relay_id)
{
    switch_all_leds_off();

    switch(relay_id)
    {
        case(1) : LED_PORT |= _BV(LED1_PIN); return;
        case(2) : LED_PORT |= _BV(LED2_PIN); return;
        case(3) : LED_PORT |= _BV(LED3_PIN); return;
    }
}

uint8_t button_press_threshold_overflow()
{
    if(btn1_counter >= BTN_PRESS_DETECT_THRESHOLD)
    {
        return 1;
    } else if(btn2_counter >= BTN_PRESS_DETECT_THRESHOLD)
    {
        return 2;
    }else if(btn3_counter >= BTN_PRESS_DETECT_THRESHOLD)
    {
        return 3;
    }

    return 0;
}

void keyscan()
{
    cli();
    if(bit_is_set(BUTTON_PORT, BUTTON1_PIN))
    {
        btn1_counter++;
    }

    if(bit_is_set(BUTTON_PORT, BUTTON2_PIN))
    {
        btn2_counter++;
    }

    if(bit_is_set(BUTTON_PORT, BUTTON3_PIN))
    {
        btn3_counter++;
    }
    sei();
}

void reset_button_counters()
{
    btn1_counter = 0;
    btn2_counter = 0;
    btn3_counter = 0;
}

void manage_relays()
{
    cli();
    uint8_t index = button_press_threshold_overflow();
    if(index != 0)
    {
        set_selected_input(index);
        switch_relay_on(index);
        led_on(index);
        reset_button_counters();
    }
    sei();
}

void process_rt5_command()
{
    uint16_t command;

    if(RC5_NewCommandReceived(&command))
    {
        RC5_Reset();

        /* On command received Toggle the LED3 */
        if(!bit_is_set(LED_PORT, LED3_PIN))
            LED_PORT |= _BV(LED3_PIN);
        else
            LED_PORT &= ~_BV(LED3_PIN);
    }
}


/*
 *  PIN config function
 *  =====================================
 *  PB0 out    RELAIS1
 *  PB1 out    RELAIS2
 *  PB2 out    RELAIS3
 *  PB3 out    LED1
 *  PB4 in     IR_SENSOR (configured by  RC5_Init)
 *  PB5 out    LED3
 *
 *  PD0 in     BUTTON1
 *  PD1 in     BUTTON2
 *  PD2 in     BUTTON3
 */
void ioinit (void)
{
    RELAIS_REGISTER |= _BV(RELAIS1_PIN);
    RELAIS_REGISTER |= _BV(RELAIS2_PIN);
    RELAIS_REGISTER |= _BV(RELAIS3_PIN);

    LED_REGISTER |= _BV(LED1_PIN);
    LED_REGISTER |= _BV(LED2_PIN);
    LED_REGISTER |= _BV(LED3_PIN);

    BUTTON_REGISTER &= ~_BV(BUTTON1_PIN);
    BUTTON_REGISTER &= ~_BV(BUTTON2_PIN);
    BUTTON_REGISTER &= ~_BV(BUTTON3_PIN);
}


void init()
{
    ioinit();
    RC5_Init();
    switch_all_relais_off();
    switch_all_leds_off();
    init_selected_input();

    switch_relay_on(selected_input);
    led_on(selected_input);

    sei();
}

int main (void)
{
    init ();
    
    for (;;)
    {
        process_rt5_command();
        keyscan();
        manage_relays();
    }
        
    return (0);
}
