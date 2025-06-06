#include <stm32f10x.h>


void init_gpio(void){
	
			// Habilitar reloj de GPIOA
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 

			//PA0
			GPIOA->CRL &= ~(0x0F << 0); 
			GPIOA->CRL |= (0x03 << 0); 
		
			//PA1
			GPIOA->CRL &= ~(0x0F << 4);  
			GPIOA->CRL |= (0x03 << 4); 
		
			//PA2
			GPIOA->CRL &= ~(0x0F << 8); 
			GPIOA->CRL |= (0x03 << 8); 
		
			//PA3
			GPIOA->CRL &= ~(0x0F << 12); 
			GPIOA->CRL |= (0x03 << 12); 
		
			//PA4
			GPIOA->CRL &= ~(0x0F << 16); 
			GPIOA->CRL |= (0x03 << 16); 
			
			//PA5
			GPIOA->CRL &= ~(0x0F << 20);  
			GPIOA->CRL |= (0x03 << 20); 
}