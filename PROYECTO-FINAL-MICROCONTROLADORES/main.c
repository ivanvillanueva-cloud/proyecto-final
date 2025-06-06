#include "stm32f10x.h"
#include <string.h>
#include <stdio.h>
#include "usart.h"
#include "Satelite.h"
#include "BME280.h"
#include "delay.h"
#include "i2c.h"
#include "gpio.h"
#include "lcd.h"

// Buffers y estructuras
char gps_buffer[128];
gps_point_t gps_point;
GPS_Time_t gps_time;

int main(void) {
	
		delay_init();
		//--------------inicializacion pantalla-----------
		init_gpio();
		delay_ms(40);
		LCD_Init();
		delay_ms(15);
		//------------------------------------------------
	
	LCD_String("SISTEMA SENSADOR");  	
	  LCD_SetCursor(1, 0);  
    LCD_String("DE CONDICIONES"); 
		delay_ms(5000);
		LCD_Command(0x01);
	
	
	
		LCD_String("PANTALLA LCD");  	
	  LCD_SetCursor(1, 0);  
    LCD_String("inicializada"); 
		delay_ms(2000);
		LCD_Command(0x01);
	
	
    uart_dma_init(gps_buffer, sizeof(gps_buffer)); // USART1 RX con DMA
    uart_send_string("USART1-DMA inicializado.\r\n");
		
		LCD_String("USART1-DMA");  	
	  LCD_SetCursor(1, 0);  
    LCD_String("inicializado"); 
		delay_ms(2000);
		LCD_Command(0x01);
	
    I2C1_Init();
    uart_send_string("I2C1 inicializado.\r\n");
	
		LCD_String("I2C1");  	
	  LCD_SetCursor(1, 0);  
    LCD_String("inicializado"); 
		delay_ms(2000);
		LCD_Command(0x01);


    BME280_Init_t bmeInit;
    bmeInit.T_StandBy = 0x00;        // 0.5ms standby
    bmeInit.Filter = 0x00;           // Filter off
    bmeInit.SPI_EnOrDis = 0x00;    	  // SPI off
    bmeInit.OverSampling_H = 0x01;   // 1x
    bmeInit.OverSampling_T = 0x01;   // 1x
    bmeInit.OverSampling_P = 0x01;   // 1x
    bmeInit.Mode = 0x03;  
    
    Reset_BME280();
    Calibdata_BME280();
			BME280_Config(&bmeInit);

    uart_send_string("BME280 inicializado.\r\n");
		BME280_Data_t bmeData;
				

		LCD_String("BME280");  	
	  LCD_SetCursor(1, 0);  
    LCD_String("inicializado"); 
		delay_ms(2000);
		
    while (1) {
				
        procesar_gps(gps_buffer, &gps_point, &gps_time);
				LCD_Command(0x01);
        
        //BME280Calculation(&bmeData);

        uart_send_string("\r\n------ DATOS Satelite\r\n"); 	
			
				LCD_String("DATOS Satelite");  	
				delay_ms(1000);
				LCD_Command(0x01);
				
			
				//HORA
        char time_str[16];
        sprintf(time_str, "%02d:%02d:%02d UTC", gps_time.hour, gps_time.minute, gps_time.second);
        uart_send_string(time_str);
        uart_send_string("\r\n");
				LCD_String(time_str);  	
				delay_ms(2000);
				LCD_Command(0x01);			
				
				
				//DATOS DE LATITUD
        uart_send_string("Lat: ");
        uart_send_double(gps_point.latitude);
				
				
				char lat_str[16];
				sprintf(lat_str, "%.6f", gps_point.latitude);
				LCD_String("LATITUD");  	
				LCD_SetCursor(1, 0);  
				LCD_String(lat_str); 
				delay_ms(2000);
				LCD_Command(0x01);
				
				
				//DATOS DE LONGITUD
        uart_send_string(" Lon: ");
        uart_send_double(gps_point.longitude);
				
				char lon_str[16];
				sprintf(lon_str, "%.6f", gps_point.longitude);
				LCD_String("LONGITUD");  	
				LCD_SetCursor(1, 0);  
				LCD_String(lon_str); 
				delay_ms(2000);
				LCD_Command(0x01);
				
				
				//DATOS DE VELOCIDAD
        uart_send_string(" Vel: ");
        uart_send_double(gps_point.speed);
        uart_send_string(" m/s\r\n");
				
				
				char vel_str[16];
				sprintf(vel_str, "%.2f m/s", gps_point.speed);
				LCD_String("VELOCIDAD");  	
				LCD_SetCursor(1, 0);  
				LCD_String(vel_str); 
				delay_ms(2000);
				LCD_Command(0x01);

        print_bme280_data(&bmeData);
				LCD_String("Datos Ambiente");  	
				delay_ms(2000);
				LCD_Command(0x01);
				
				// Obtener los datos del sensor
				BME280Calculation(&bmeData);

				// Mostrar temperatura
				char temp_str[16];
				sprintf(temp_str, "Temp: %.2fC", bmeData.Temperature);
				LCD_String("Temperatura:");
				LCD_SetCursor(1, 0);
				LCD_String(temp_str);
				delay_ms(2000);
				LCD_Command(0x01);

				// Mostrar presión
				char press_str[16];
				sprintf(press_str, "Pres: %.2fhPa", bmeData.Pressure / 100.0);
				LCD_String("Presion:");
				LCD_SetCursor(1, 0);
				LCD_String(press_str);
				delay_ms(2000);
				LCD_Command(0x01);

				// Mostrar humedad
				char hum_str[16];
				sprintf(hum_str, "Hum: %.1f%%", bmeData.Humidity);
				LCD_String("Humedad:");
				LCD_SetCursor(1, 0);
				LCD_String(hum_str);
				delay_ms(2000);

    }
}
