#include "PWMsoft.h"


//FUNCION DE PWM
void PWM_update(){
	static uint16_t PWM_position=0;		//variable contador
	if (++PWM_position>=PWM_PERIOD){	//si llego a valor de periodo la reinicio.
		PWM_position=0;
	}
	if(PWM_position< red){		//si es menor a valor de pulso, terminal en nivel bajo
	PWM_OFF;}
	else{
		PWM_ON;		//si no terminal en nivel alto.
	}
	
}
