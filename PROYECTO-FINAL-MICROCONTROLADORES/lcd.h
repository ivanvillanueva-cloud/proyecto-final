#include "stm32f10x.h"

#ifndef _lcd
#define _lcd
	void LCD_Init(void);
	void LCD_Command(uint8_t cmd);
	void LCD_Char(char data);
	void LCD_String(const char *str);
	void LCD_SetCursor(uint8_t row, uint8_t col);
	void LCD_Send4Bits(uint8_t data);
	void LCD_EnablePulse(void);
	void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int BitVal);
#endif