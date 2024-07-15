#include <avr/io.h>
#include <stdint.h>

#define PWM_PERIOD 255 //PARA 8 BITS
#define PWM_OFF PORTB &= ~(1<<PORTB5)
#define PWM_ON PORTB |= (1<<PORTB5)

extern volatile uint8_t red;

void PWM_update();