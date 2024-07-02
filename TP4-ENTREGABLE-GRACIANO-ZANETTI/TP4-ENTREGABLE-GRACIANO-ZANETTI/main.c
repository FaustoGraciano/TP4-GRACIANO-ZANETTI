#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "serialPort.h"
#include "PWMsoft.h"

#define BR9600 0x67	// 0x67=103 configura BAUDRATE=9600@16MHz

void set_pwm(uint8_t red, uint8_t green, uint8_t blue);
volatile uint8_t red = 255;
volatile uint8_t selected_color;
//TIMERS
void configurarTimer1();
void configurarTimer0();

int main(void)
{  	DDRB |= (1<<PORTB5) | (1<<PORTB1)| (1<<PORTB2);
	configurarTimer0();
	configurarTimer1();
    configurarUART();
	sei();								// habilitacion de interrupciones globales
	uint8_t green = 255, blue = 255;
	
    while (1) 
    {


	 /*  switch (selected_color) {
	       case 'R':
	       red = pwm_value;
	       break;
	       case 'G':
	       green = pwm_value;
	       break;
	       case 'B':
	       blue = pwm_value;
	       break;
       }
*/	   // Establecer el valor PWM
	   set_pwm(red, green, blue);
    }
return 0;
}


// Función para configurar el Timer1
void configurarTimer1() {
	 TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM10); // Modo inv
	TCCR1B |=(1<<WGM12) | (1<<WGM10) | (1<<CS11); // Modo 5 PWM, prescaler de 8
  //	TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); // Habilitar interrupción de comparador A y B
}
//Configuracion de TIMER0

void configurarTimer0()
{	TCNT0=0;	//valor inicial de conteo
	TCCR0A|=(1<<WGM01);	//modo de conteo CTC
	TCCR0B|=(1<<CS01);		//registro de configuracion, prescaler 8
	OCR0A=155;		//(156-1)	//valor maximo de conteo con modo de ctc
	TIMSK0|=(1<<OCIE0A);				//habilitar las interrupciones del timer.

}


void configurarUART()
{ SerialPort_Init(BR9600);   // Inicializo formato 8N1 y BAUDRATE = 9600bps
  SerialPort_TX_Enable();		// Activo el transmisor del Puerto Serie
  SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
  SerialPort_RX_Interrupt_Enable(); // habilitacion de las interrupciones del receptor
}


void set_pwm(uint8_t red, uint8_t green, uint8_t blue) {
	OCR0A = red;   // PB5
	OCR1B = green; // PB2
	OCR1A = blue;  // PB1
}

ISR(TIMER0_COMPA_vect){
	PWM_update();
}