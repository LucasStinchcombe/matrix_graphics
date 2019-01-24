#include "adc.h"

#include <avr/io.h>

void ADC_init()
{
    // enable ADC
    ADCSRA |= (1 << ADEN);
    // set clock division factor to 128
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // set free running mode
    ADCSRB &= ~(1 << ADTS0) & ~(1 << ADTS1) & ~(1 << ADTS2);

    // set left adjusted, AVcc as reference
    ADMUX = (1 << ADLAR) | (1 << REFS0);
}

uint8_t get_value(uint8_t channel)
{
    ADMUX &= 0xF0;
    ADMUX |= (0x0F & channel);

    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
        ;

    return ADCH;
}
