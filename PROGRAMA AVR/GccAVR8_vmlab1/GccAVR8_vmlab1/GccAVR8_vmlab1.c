/*
 * 
 * Created: 12/26/2015 3:59:15 PM
 *  Author: Juan Manuel Mendoza Jacinto
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void configura_puertos(void)
{
	DDRC = 0x00; //ENTRADA
	DDRB = 0xFF; //SALIDA
	DDRD = 0xFF; //SALIDA
}

void leds(int led)
{
switch (led)
{
case 1:
	PORTD=0x31; //MODO 1
	break;
case 2:
	PORTD=0x32; //MODO 2
	break;
case 3:
	PORTD=0x31; //MODO OPE
	break;
}
	
} 
// nuevo led

int apreto_boton2(int number)
{
	if(number==5)
	{
		number=30;
	}
	else
	{
	 number--;
	}
	return number;
}
int apreto_boton1(int number)
{
	if(number==30)
	{
		number=5;
	}
	else
	{
		number++;
	}
	return number;
}
//nuevo numero
void mostrar_number(int number)
{
	int num1 = number/10;
	int num2 = number%10;
	PORTB = num1*16+num2;
}

void esperar_sec(int sec)
{//falta arreglar
	
 for (int i = sec; i>0;i--)
 {	mostrar_number(i);
	 _delay_ms(1000);
	
 }

}
int main(void)
{	int number=5;
	int number1=5;//numero de seg en on
	int number2=5;//numero de seg en off
	int compare=0;//lee el dato de switch de entrada
	int end=1;
	int endres=1;
	configura_puertos();
	
	while(1){
		end=1;
		endres=1;
		number=5;
		leds(1);
		mostrar_number(number);
    while(end&&endres)
    {
		while((PINC&0x0F)==0);
		compare=PINC&0x0F;
		while((PINC&0x0F)!=0);
		if(compare==1){number=apreto_boton1(number);mostrar_number(number);}
		if(compare==2){number=apreto_boton2(number);mostrar_number(number);}  
		if(compare==4){leds(2); number1=number;end=0;} //guarda número 1, cambia led, sale del bucle   
		if(compare==8){endres=0;}   //RESET sale de los dos bucles
    }
	
		end=1;
		number=5;
		mostrar_number(number);
	while(end&&endres)
	{
	   while((PINC&0x0F)==0);
	   compare=PINC&0x0F;
	   while((PINC&0x0F)!=0);
	   if(compare==1){number=apreto_boton1(number);mostrar_number(number);}
	   if(compare==2){number=apreto_boton2(number);mostrar_number(number);}
	   if(compare==4){leds(3); number2=number;end=0;} //guarda número 1, cambia led, sale del bucle
	   if(compare==8){endres=0;}   //RESET sale de los dos bucles
	 }
	PORTB=15*16+15; //Vacío en los displays
	while(endres)
	{
		PORTD=0x30;
		esperar_sec(number1);
		PORTD=0x0B;//INFLA
		esperar_sec(number2);
		if((PINC&0x0F)!=0){endres=0;};
	}
}	
}