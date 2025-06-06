	#include "stm32f10x.h"
	#include "gpio.h"
	#include "delay.h"
#define LCD_RS_PIN    (1 << 0)  // PA0
#define LCD_E_PIN     (1 << 1)  // PA1
#define LCD_D4_PIN    (1 << 2)  // PA2
#define LCD_D5_PIN    (1 << 3)  // PA3
#define LCD_D6_PIN    (1 << 4)  // PA4
#define LCD_D7_PIN    (1 << 5)  // PA5

#define LCD_GPIO      GPIOA


	
		
// Función de escritura en GPIO
	void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int BitVal)
{
    if (BitVal) {
        GPIOx->BSRR = GPIO_Pin;
    } else {
        GPIOx->BRR = GPIO_Pin;
    }
}

// Generar pulso en Enable
void LCD_EnablePulse(void)
{		
    GPIO_WriteBit(LCD_GPIO, LCD_E_PIN, 1);
    delay_ms(5);
    GPIO_WriteBit(LCD_GPIO, LCD_E_PIN, 0);
    delay_ms(5);
}

// Enviar 4 bits al LCD
void LCD_Send4Bits(uint8_t data)
{
    GPIO_WriteBit(LCD_GPIO, LCD_D4_PIN, (data & 0x01) ? 1 : 0);
    GPIO_WriteBit(LCD_GPIO, LCD_D5_PIN, (data & 0x02) ? 1 : 0);
    GPIO_WriteBit(LCD_GPIO, LCD_D6_PIN, (data & 0x04) ? 1 : 0);
    GPIO_WriteBit(LCD_GPIO, LCD_D7_PIN, (data & 0x08) ? 1 : 0);

    LCD_EnablePulse();
}

// Función para enviar comandos al LCD
void LCD_Command(uint8_t cmd)
{
    GPIO_WriteBit(LCD_GPIO, LCD_RS_PIN, 0); // RS = 0 (comando)
    LCD_Send4Bits(cmd >> 4);
    LCD_Send4Bits(cmd & 0x0F);
}

// Función para enviar caracteres al LCD
void LCD_Char(char data)
{
    GPIO_WriteBit(LCD_GPIO, LCD_RS_PIN, 1); // RS = 1 (datos)
    LCD_Send4Bits(data >> 4);
    LCD_Send4Bits(data & 0x0F);
}

// Función para posicionar el cursor en la pantalla
void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0) ? 0x80 + col : 0xC0 + col;
    LCD_Command(addr);
}

// Función para imprimir una cadena de texto en el LCD
void LCD_String(const char *str)
{
    while (*str) {
        LCD_Char(*str++);
    }
}

void LCD_Init(void)
{		
    LCD_Send4Bits(0x03); delay_ms(5);
    LCD_Send4Bits(0x03); delay_ms(5);
    LCD_Send4Bits(0x03); delay_ms(5);
    LCD_Send4Bits(0x02); delay_ms(1);

    LCD_Command(0x28);  // Configurar LCD: 4 bits, 2 líneas, 5x8
    delay_ms(2);
    LCD_Command(0x0C);  // Display ON, Cursor OFF
    delay_ms(2);
    LCD_Command(0x06);  // Mover cursor a la derecha
    delay_ms(2);
    LCD_Command(0x01);  // Limpiar pantalla
    delay_ms(5);
}
