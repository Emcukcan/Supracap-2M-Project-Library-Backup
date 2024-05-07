#ifndef bms_comm2_h
#define bms_comm2_h



#include <Wire.h>


#define SDA_0 33
#define SCL_0 32

#define I2C_ADDRESS 0x48

TwoWire I2C_0 = TwoWire(1);

bool result=false;
uint8_t read_input[2];
uint8_t configer[3];
float adc_value=0;

bool i2c_search(uint8_t adress)
{
  
 uint8_t error;
 
     I2C_0.beginTransmission(adress);
    error =  I2C_0.endTransmission();
    if (error == 0) {

  
      //nDevices++;
       return true;
    }
    else  {
     
    return false;
    }    
 }
  
uint16_t readReger(uint8_t reg) {
	
configer[0] = reg;
 
 I2C_0.requestFrom(0x48,2);
	
for(int i=0;i<2;i++)
{
    configer[i] = I2C_0 .read();
}

  return ((configer[0] << 8) | configer[1]);

}


bool conversionCompleter() {
	
  return (( readReger(configer[0]) & 0x8000) != 0);
	
}


  

void send_config(uint8_t analog)
{
switch(analog)

{
case 1:
 configer[1]=0xC1;
 break;

 case 2:
 configer[1]=0xD1;
 break;
 
  case 3:
 configer[1]=0xE1;
 break;
	
  case 4:
 configer[1]=0xF1;
 break;
	
 default:
  break;
}

  configer[0]=0x01;
 
  configer[2]=0xC3;
  
   I2C_0.beginTransmission(0x48); // transmit to device adress 1001 0000
    
   for(int i=0;i<3;i++)
   {
   I2C_0.write(configer[i]);  
   }
	 
   I2C_0.endTransmission();  
	 
   while (!conversionCompleter());
	 
   configer[0]=0x00;
	 
   I2C_0.beginTransmission(0x48); 
   I2C_0.write(configer[0]);  
   I2C_0.endTransmission();    // stop transmitting



adc_value=(readReger(configer[0])*0.0001875); 

   
}




    

























#endif