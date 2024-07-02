#include "PWMsoft.h"


//FUNCION DE PWM
void PWM_update(){
	static uint16_t PWM_position=0;
	if (++PWM_position>=PWM_PERIOD){
		PWM_position=0;
	}
	if(PWM_position< red){
	PWM_OFF;}
	else{
		PWM_ON;
	}
	
}
