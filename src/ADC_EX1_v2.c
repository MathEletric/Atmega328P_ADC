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
#include<avr/interrupt.h>

int valor_adc = 0;

ISR(ADC_vect){
    valor_adc = ADC;
    ADCSRA |= (1<<6);
}


void pinConfig(){
    PORTB = ((PORTB | (1<<0)) | (1<<1)); 
    //PORTC &= ~(1<<5);
}
void adcConfig(){

    ADMUX = 0b01000101;
    DIDR0 = 0b00100000;
    ADCSRA = 0b11011111;
    sei();


}





int main(){
    pinConfig();
    adcConfig();
    while(1){
        if(ADC<255){
            PORTB = ((PORTB & ~(1<<0)) & ~(1<<1));
        }
        if(255<ADC<511){
            PORTB |= (1<<0);
        }
        if(511<ADC<767){
            PORTB |= (1<<1);
        }
        if(ADC>767){
            PORTB |= (1<<0);
            PORTB |= (1<<1);
        }
    }
}
