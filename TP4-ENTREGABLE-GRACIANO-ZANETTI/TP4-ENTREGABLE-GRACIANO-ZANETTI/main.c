#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "serialPort.h"

#define BR9600 0x67	// 0x67=103 configura BAUDRATE=9600@16MHz

//PWM
#define PWM_PERIOD 255 //PARA 8 BITS
//#define PWM_DELTA 64	//ANCHO DE PULSO (HACERLO VARIABLE DARA LA INTENSIDAD DEL COLOR) (TODO MODO INVERTIDO) 
#define PWM_OFF PORTB &= ~(1<<PORTB5)
#define PWM_ON PORTB |= (1<<PORTB5)
#define PWM_START DDRB |= (1<<PORTB5)

void PWM_update();
uint8_t PWM_DELTA=250;

//TIMERS
//void configurarTimer1();
void configurarTimer0();

int main(void)
{	PWM_START; //inicio pwm
	configurarTimer0();
//	configurarTimer1();
	SerialPort_Init(BR9600);   // Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();		// Activo el transmisor del Puerto Serie
	SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
	SerialPort_RX_Interrupt_Enable(); // habilitacion de las interrupciones del receptor
	sei();								// habilitacion de interrupciones globales
	
    while (1) 
    {

    }
return 0;
}


// Función para configurar el Timer1
/*void configurarTimer1() {
	TCCR1A = 0;
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10); // Modo CTC, prescaler de 64
	OCR1A = 249; // Configurar OCR1A para que el comparador coincida cada 1 milisegundo
	TIMSK1 |= (1 << OCIE1A); // Habilitar interrupción de comparador A
}*/


// ISR del TIMER1
//ISR(TIMER1_COMPA_vect) {
	
//}



//Configuracion de TIMER0

void configurarTimer0()
{	TCNT0=0;	//valor inicial de conteo
	TCCR0A|=(1<<WGM01);	//modo de conteo CTC
	TCCR0B|=(1<<CS01);		//registro de configuracion, prescaler 8
	OCR0A=155;		//(156-1)	//valor maximo de conteo con modo de ctc
	TIMSK0|=(1<<OCIE0A);				//habilitar las interrupciones del timer.

}

//FUNCION DE PWM
void PWM_update(){
static uint16_t PWM_position=0;
	if (++PWM_position>=PWM_PERIOD){
		PWM_position=0;
	}
	if(PWM_position<PWM_DELTA){
		PWM_ON;}
	else{
		PWM_OFF;	
	}	
	
}

ISR(TIMER0_COMPA_vect){
	PWM_update(PWM_DELTA);
}