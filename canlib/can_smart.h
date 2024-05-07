#ifndef can_smart_h
#define can_smart_h


#include <ESP32CAN.h>
#include <CAN_config.h>

CAN_device_t CAN_cfg;

struct battery_value{

float batt_voltage;
//uint16_t batt_chvoltage;
float batt_chcurrent;	

float batt_discurrent;
	
uint16_t batt_SOC;
uint16_t batt_SOH;
uint16_t batt_temp;	
uint16_t batt_alarms;	



};
struct battery_value batt;


 uint32_t receive_id=0;




void can_start(int baud)
{
	switch (baud)
	{

	case 125:

		CAN_cfg.speed = CAN_SPEED_125KBPS;
		// CAN_cfg.speed=CAN_SPEED_500KBPS;
		CAN_cfg.tx_pin_id = GPIO_NUM_23;
		CAN_cfg.rx_pin_id = GPIO_NUM_4;
		// CAN_cfg.tx_pin_id = GPIO_NUM_17;
		// CAN_cfg.rx_pin_id = GPIO_NUM_16;
		 // CAN_cfg.tx_pin_id = GPIO_NUM_33;
	   // CAN_cfg.rx_pin_id = GPIO_NUM_32;
		CAN_cfg.rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));
		//start CAN Module
		ESP32Can.CANInit();


		break;

	case 250:

		CAN_cfg.speed = CAN_SPEED_250KBPS;
		// CAN_cfg.speed=CAN_SPEED_500KBPS;
		CAN_cfg.tx_pin_id = GPIO_NUM_23;
		CAN_cfg.rx_pin_id = GPIO_NUM_4;
		// CAN_cfg.tx_pin_id = GPIO_NUM_17;
		// CAN_cfg.rx_pin_id = GPIO_NUM_16;
		 // CAN_cfg.tx_pin_id = GPIO_NUM_33;
	   // CAN_cfg.rx_pin_id = GPIO_NUM_32;
		CAN_cfg.rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));
		//start CAN Module
		ESP32Can.CANInit();


		break;

	case 500:

		CAN_cfg.speed = CAN_SPEED_500KBPS;
		// CAN_cfg.speed=CAN_SPEED_500KBPS;
		CAN_cfg.tx_pin_id = GPIO_NUM_23;
		CAN_cfg.rx_pin_id = GPIO_NUM_4;
		// CAN_cfg.tx_pin_id = GPIO_NUM_33;
	  // CAN_cfg.rx_pin_id = GPIO_NUM_32;
		CAN_cfg.rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));
		//start CAN Module
		ESP32Can.CANInit();

		break;
	default:
		break;
	
	}
 
}




void can_send(uint8_t *datac ,uint32_t id,uint8_t clength)
{
      CAN_frame_t tx_frame;
         
      tx_frame.FIR.B.FF = CAN_frame_ext;  // forbms
	
	   // tx_frame.FIR.B.FF = CAN_frame_std;
      tx_frame.MsgID =id;
      tx_frame.FIR.B.DLC = clength;
   //    Serial.println(tx_frame.FIR.B.DLC,HEX);
	   //Serial.println(tx_frame.MsgID,HEX);
      for(int i=0;i<8;i++)
      {
        tx_frame.data.u8[i]=datac[i];
			//	Serial.println(datac[i],HEX);
      }
      
      ESP32Can.CANWriteFrame(&tx_frame);
   
		 

     
  
}



void can_recieve(uint8_t *datarec,uint32_t rec_id)

{
 
	uint8_t DLC=0;

    CAN_frame_t rx_frame;
	rx_frame.FIR.B.FF = CAN_frame_ext;
    //receive next CAN frame from queue
	// Serial.println(rx_frame.MsgID);
    if(xQueueReceive(CAN_cfg.rx_queue,&rx_frame, 3*portTICK_PERIOD_MS)==pdTRUE){

      //do stuff!
    //  if(rx_frame.FIR.B.FF==CAN_frame_std)
    //    Serial.println("New standard frame");
    //  else
     //   printf("New extended frame");

     // if(rx_frame.FIR.B.RTR==CAN_RTR)
     //   printf(" RTR from 0x%08x, DLC %d\r\n",rx_frame.MsgID,  rx_frame.FIR.B.DLC);
     // else{
      // Serial.println("ID");

			DLC=rx_frame.FIR.B.DLC;
		//	Serial.println(DLC);
       receive_id=rx_frame.MsgID;
	   //Serial.println(receive_id,HEX);
	

			if(rec_id== receive_id)
       {
			//Serial.println("ID");
      //Serial.println(receive_id,HEX);
       // Serial.println(receive_id,HEX);
        for(int i = 0; i < DLC; i++){
      
          datarec[i]= rx_frame.data.u8[i];
		 //Serial.println( datarec[i],HEX);
        } 
        
       }

			 
       // Serial.println("\n");
      }


  
}





bool send_id(uint16_t id)
{
	uint8_t datac[8];
	
	 datac[0]=0x0A;
	  for(int i=1;i<8;i++)
      {
        datac[i]=0;
      }
	
	can_send(datac , id,8);
	delay(100);
	 datac[0]=0;		
	can_recieve(datac,id)	;	
	if(datac[0]==0x0A)
	{
		return 1;
		
	} else
	
	{
		return 0;
	}
	
}
	
void read_battery_volt(float battery_v,uint16_t tempr)
{
	
	uint16_t batt_voltage=0;
	uint16_t temp=0;
	
	uint8_t buffer[8];
	
	can_recieve(buffer,502)	;	
	
batt_voltage=(buffer[1]<<8+buffer[0]);
temp=(buffer[2]<<8+buffer[3]);
	
	
battery_v=(batt_voltage/10);	
tempr=(temp/10);	
	
}


void read_soc(uint16_t soc,uint16_t soh)
{
	
  uint16_t socs=0;
	uint16_t sohs=0;
	
	uint8_t buffer[8];
	
	can_recieve(buffer,503)	;	
	
	
socs=(buffer[1]<<8+buffer[0]);
sohs=(buffer[2]<<8+buffer[3]);
	
	soc=(socs/10);
	soh=(sohs/10);
	
}



void read_current(float char_cur,float disch_cur)
{
	
	uint16_t chcurrent=0;
	uint16_t dischcurrent=0;	
	uint8_t buffer[8];
	
	
	
	can_recieve(buffer,504)	;	
	
	
chcurrent=(buffer[1]<<8+buffer[0]);
dischcurrent=(buffer[2]<<8+buffer[3]);
	
	
	char_cur=(chcurrent/10);
	disch_cur=((0xFFFF-dischcurrent)/10);
	
	
}

void read_battery(void)
	
{
	
	 read_battery_volt(batt.batt_voltage,batt.batt_temp);
	 read_soc(batt.batt_SOC,batt.batt_SOH);
	 read_current(batt.batt_chcurrent,batt.batt_discurrent);
	
	
}












#endif