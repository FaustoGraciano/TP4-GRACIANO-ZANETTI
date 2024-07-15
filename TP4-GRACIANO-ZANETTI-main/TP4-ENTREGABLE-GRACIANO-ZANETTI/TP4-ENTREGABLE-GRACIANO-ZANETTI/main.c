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

//funciones ADC
void adc_init();
uint16_t adc_read();

//funcion UART
void configurarUART();

//Funcion PWM
void set_pwm(uint8_t green, uint8_t blue);

//Variables globales
volatile uint8_t red = 0;
volatile uint8_t selected_color='E';
uint8_t pwm_value;

//FUNCIONES DE TIMERS
void configurarTimer1();
void configurarTimer0();

int main(void)
{  	DDRB |= (1<<PORTB5) | (1<<PORTB1)| (1<<PORTB2); //seteo terminales PB1,PB2, PB5 como salida
	DDRC &= ~(1<<PORTC3);							//seteo terminal PB3 como entrada
	adc_init();					//configuro adc
	configurarTimer0();			//configuro timer0
	configurarTimer1();			//configuro timer1
    SerialPort_Init(BR9600);   // Inicializo formato 8N1 y BAUDRATE = 9600bps
    SerialPort_TX_Enable();		// Activo el transmisor del Puerto Serie
    SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
    SerialPort_RX_Interrupt_Enable(); // habilitacion de las interrupciones del receptor
	sei();								// habilitacion de interrupciones globales
	uint8_t green = 0, blue = 0;		//variables de colores

    while (1) 
    {	
		if (selected_color != 'E') {	//si selected color es diferente al enter entro a modificar un color
	   
			pwm_value = adc_read();		//leo el adc
			
         switch (selected_color) {		//modifico color segun lectura
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
// Establecer el valor PWM
	   set_pwm(green, blue);		//seteo colores segun el valor leido.
    }
	}
return 0;
}

uint16_t adc_read() {
	ADCSRA |= (1 << ADSC); // Iniciar la conversión
	
	while((ADCSRA&(1<<ADIF))==0);//wait for conversion to finish
	
	ADCSRA |= (1<<ADIF); //borrar flag
	
	return ADCH;
}
	
void adc_init() {
	// Configurar el ADC
	ADMUX |= (1 << REFS0) | (1 << MUX0)|(1<<MUX1)|(1<<ADLAR); // AVcc con capacitor en AREF y ADC3
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1)| (1 << ADPS0); // Habilitar ADC y prescaler de 128
	DIDR0 |= (1 << ADC3D); // Deshabilitar la entrada digital en ADC3
}

// Función para configurar el Timer1
void configurarTimer1() {
	 TCCR1A |= (1<< COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM10); // Modo inv
	TCCR1B |=(1<<WGM12) | (1<<CS11); // Modo 5 PWM, prescaler de 8
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


void set_pwm(uint8_t green, uint8_t blue) {
	OCR1B = green; // PB2
	OCR1A = blue;  // PB1
}

ISR(TIMER0_COMPA_vect){
	PWM_update();			//actualizo la señal PWM del color rojo
}