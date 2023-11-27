/*
Ler o canal 5 do Conversor AD (PORTC – PC5 – ADC5), com referência em VCC.
▪ Usar um potenciômetro de 1 ou 5 kΩ entre o VCC e o terra. O pino central
deve ser ligado em PC5.
▪ Leds ligados em PORTB, PB0 e PB1.

      valor ADC < 255  : Apagar leds
255 ≤ valor ADC < 511  : Acender led PB0
511 ≤ valor ADC < 767  : Acender led PB1
767 ≤ valor ADC        : Acender ambos os leds
*/


#define F_CPU 16000000
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

short aux_h, aux_l;
int valor_adc;

ISR(ADC_vect){
    aux_l = ADCL;
    aux_h = ADCH;

    valor_adc = aux_h*256 + aux_l;

    ADCSRA |= (1<<PB6);
}

int main(){
    DDRB = DDRB | ((1<<0) + (1<<1));
    PORTB = PORTB & ~((1<<0) + (1<<1));

    ADMUX = ADMUX |  ((1<<2) + (1<<0));
    ADMUX = ADMUX & ~((1<<1) + (1<<3));

    ADMUX = (ADMUX | (1<<6)) & ~(1<<7);

    ADMUX &= ~(1<<5);

    DIDR0 |= (1<<5);

    ADCSRA |= ((1<<0) + (1<<1) + (1<<2));

    ADCSRA &= ~(1<<5);

    ADCSRA |= (1<<3);

    ADCSRA |= (1<<7);

    sei();

    ADCSRA |= (1<<6);

    while(1){
        if(valor_adc<255){
            PORTB = PORTB & ~((1<<0)+(1<<1));
        }
        if(valor_adc<511){
            PORTB = (PORTB | (1<<1)) & ~(1<<0);
        }
        if(valor_adc<767){
            PORTB = (PORTB | (1<<0)) & ~(1<<1);
        }
        else{
            PORTB |= ((1<<0)+(1<1));
        }
    }
}

