
#ifndef modbusslaveen_h
#define modbusslaveen_h


 
 
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h" 
#include "driver/uart.h"
#include "esp_system.h"

uint32_t baudbaud;
uint8_t RXS;
uint8_t TXS;
static QueueHandle_t uart2_queue;

//master
#define TXD2   23
#define RXD2   4


//slave
//#define TXD2   17
//#define RXD2   16


#define RTS_485   (25)   //14

// CTS is not used in RS485 Half-Duplex Mode
#define ECHO_TEST_CTS   (UART_PIN_NO_CHANGE)  //12


#define ECHO_TASK_PRIO          (10)

#define PACKET_READ_TICS        (100 / portTICK_PERIOD_MS)


//#define UARTA_PORT_NUM      UART_NUM_2
#define UARTA_BAUD_RATE     2400
#define ECHO_READ_TOUT          (3) // 3.5T * 8 = 28 ticks, TOUT=3 -> ~24..33 ticks

#define BUF_SIZE (2048)

//uint8_t UART_data[BUF_SIZE];
 uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
 uint8_t en_rs485=25;
 

 void config_uartslave( )
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = baudbaud,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
			 .rx_flow_ctrl_thresh = 122,
        //.source_clk = UART_SCLK_APB,
    };
		 uart_param_config(UART_NUM_2 , &uart_config);
		/*
    int intr_alloc_flags = 0;

#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif
*/
    uart_driver_install(UART_NUM_2, BUF_SIZE * 2, 0, 0,NULL, 0);
 
    uart_set_pin(UART_NUM_2 , TXS ,RXS, en_rs485, UART_PIN_NO_CHANGE);
		
		 ESP_ERROR_CHECK(uart_set_mode(UART_NUM_2 , UART_MODE_RS485_HALF_DUPLEX));
    //   uart_set_rs485_hd_mode(UART_NUM_2, 1);
		
	 ESP_ERROR_CHECK(uart_set_rx_timeout(UART_NUM_2 , ECHO_READ_TOUT));	
		
		
    // Configure a temporary buffer for the incoming data

        // Write data back to the UART
        //uart_write_bytes(ECHO_UART_PORT_NUM, (const char *) data, len);
    
		
		// xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 12, NULL);
}

int read_serial(uint8_t *rec_dat){
      uint8_t UART2_data[600];
	    int datrt=0;
	
	
	
                int UART3_data_length= 0;
                ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_2, (size_t*)&UART3_data_length));
	   if(UART3_data_length >0)
					{
                UART3_data_length = uart_read_bytes(UART_NUM_2,  data, UART3_data_length, 100 );
					}
					         
					    
					        for(byte i=0; i<UART3_data_length;i++)
							{
							     rec_dat[i]=data[i];
							     //  Serial.println( rec_dat[i],HEX);
							}
							      datrt=UART3_data_length;
							// Serial.println(" UART3_data_length");
							// Serial.println( UART3_data_length,HEX);
							delay(5);
          
				

						

esp_err_t uart_flush(UART_NUM_2) ;
esp_err_t uart_flush_input(UART_NUM_2);						
		return datrt;
					}

					
	uint8_t isavailable(void)
		{			
			// uint8_t UART2_data[600];
	 int len = uart_read_bytes(UART_NUM_2 ,data , BUF_SIZE, 100 );
			
					return len;
		}			
					
		
		
		
		
void write_serial(char* rec_dat,uint16_t u8Buffize){
					
//esp_err_t uart_flush(UART_NUM_2) ;
//esp_err_t uart_flush_input(UART_NUM_2);		
//				delay(10);

   if (uart_write_bytes(UART_NUM_2 , rec_dat, u8Buffize) != u8Buffize) {
       // ESP_LOGE(TAG, "Send data critical failure.");
		// Serial.println("Send data critical failure.");
        // add your code to handle sending failure here
        abort();
    }
   

//	for(int i=0;i<9;i++)
//	{
//			Serial.println(rec_dat[i],HEX);
//	}
			
		//Serial.println(u8Buffize,HEX);
//Serial.println(rec_dat[178],HEX);
				}				















					
					
#endif