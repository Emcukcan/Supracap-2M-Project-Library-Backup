#ifndef can_bms_h
#define can_bms_h

#include <can_smart.h>



String AlarmArrayCan[28] = {"Cell High", "Cell High 2", "Cell Low", "Cell Low 2", "Sum High", "Sum High 2", "Sum Low", "Sum Low 2",
                         "Charge Temp High", "Charge Temp High", "Charge Temp Low", "Charge Temp Low", "Disc. Temp High", "Disc. Temp High",
                         "Disc. Temp Low", "Disc. Temp Low",
                         "Charge Over Curr.", "Charge Over Curr.", "Disch. Over Curr.", "Disch. Over Curr.", "SOC High", "SOC High", "SOC Low", "SOC Low",
                         "Diffence Voltage", "Diffence Voltage", "Diffence Temp.", "Diffence Temp."
                        };

String firmversion_can;

struct Bms_can {

  uint32_t rated_volt_can;                      //0x50
  uint32_t rated_cap_can;

  uint8_t boardnum_can;
  uint8_t board1cellnum_can;             //0X51
  uint8_t board2cellnum_can;
  uint8_t board1tempnum_can;

  uint8_t cumilative_charge_can;
  uint8_t cumilative_discharge_can;             //0X52


  uint8_t boardtypebm_can;
  uint8_t activebm_can;                         // 0x53
  uint8_t boardyear_can;
  uint8_t boardmonth_can;
  uint8_t boardday_can;
  uint16_t secondsleepbm_can;


  String Firmwarevers_can;                       //0x54
  
 
						
	uint8_t AlarmStatus_can=99;
    String AlarmStatus_can_String="No Alarm";


  uint16_t cell_volthigh1_can;                   //0x59
  uint16_t cell_volthigh2_can;
  uint16_t cell_voltlow1_can;
  uint16_t cell_voltlow2_can;

  uint16_t short_current_can;                    //0x60
  uint16_t cur_sampling_res_can;

  uint8_t board_number_can;                       //0x60
  uint8_t slave_number_can;


  uint16_t sumv_high1_can;                    //0x5A
  uint16_t sumv_high2_can;
  uint16_t sumv_low1_can;
  uint16_t sumv_low2_can;

  uint16_t dischar_curr1_can;                    //0x5B
  uint16_t dischar_curr2_can;
  uint16_t charge_curr1_can;
  uint16_t charge_curr2_can;


  uint8_t charge_temp_high1_can;
  uint8_t charge_temp_high2_can;             //0X5C
  int charge_temp_low1_can;
  int charge_temp_low2_can;
  uint8_t discharge_temp_high1_can;
  uint8_t discharge_temp_high2_can;
  int discharge_temp_low1_can;
  int discharge_temp_low2_can;


  uint16_t SOC_high1_can;
  uint16_t SOC_high2_can;                   //0X5D
  uint16_t SOC_low1_can;
  uint16_t SOC_low2_can;


  uint16_t volt_diff1_can;
  uint16_t volt_diff2_can;                   //0X5E
  uint8_t temp_diff1_can;
  uint8_t temp_diff2_can;


  uint16_t balance_volt_can;
  uint16_t balance_volt_diff_can;                   //0X5F




  uint16_t sum_voltage_can;
  uint16_t gather_voltage_can;                   //0X90
  uint16_t current_can;
  uint16_t SOC_can;

  uint16_t max_cell_volt_can;
  uint8_t max_cell_volt_number_can;             //0X91
  uint16_t min_cell_volt_can;
  uint8_t min_cell_volt_number_can;

  uint8_t max_cell_temp_can;
  uint8_t max_cell_temp_number_can;             //0X92
  uint8_t min_cell_temp_can;
  uint8_t min_cell_temp_number_can;

  uint8_t state_can;                                           //0 stationary 1 cahrge 2 discharge
  uint8_t charge_can;
  uint8_t discharge_can;                       //0X93
  uint8_t bms_life_can;                                      // 0-255 cycles
  uint32_t rem_cap_can;                                      //remain capacity mAH


  uint8_t bat_str_can;                                      //battery string
  uint8_t bat_temp_can;                       //0X94        //temperature number
  uint8_t charg_sts_can;                                    //charge status
  uint8_t load_sts_can;                                     //load status

  uint16_t cell_voltage_can[24];                 //0x95         //cell voltage array

  uint8_t cell_temperature_can[14];                 //0x96       //cell temperature array

  uint8_t cell_balance_can[24];                 //0x97       //cell balance  0 closed   1 open

  uint8_t error_can[48];                 //0x98       //No error 0  error 1

};
struct Bms_can BMS_can;

uint8_t senddata[]={0x50,0xE4,0x70,0x25,0x42,0x00,0x00,0x00};

uint8_t datacanrec[8];

float encap_volt = 0;
float encap_current = 0;
uint8_t encap_soc = 0;


void BMS_recieve(uint8_t id,uint8_t device_id)
{
	uint32_t slaveid=0x18000040;
  uint32_t recid=0x18004000;
  uint8_t checksm = 0;
  int a = 0;
  uint16_t shift = 0;
	uint32_t rem1=0;
	uint32_t rem2=0;
	uint32_t rem3=0;
	uint32_t rem4=0;
 int art=1;

slaveid=(((id<<16)+(device_id<<8))|slaveid);  
recid=(((id<<16)+(device_id))|recid); 
  
//Serial.println(slaveid,HEX);
//Serial.println(recid,HEX);
  switch (id)
  {
				
		

    case 0x50:                    //rated cap rated volt
      can_send(senddata ,slaveid,8);
		  		 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);
 

        BMS_can.rated_cap_can = ((datacanrec[0] << 24) + (datacanrec[1]<< 16)+(datacanrec[2] << 8) + datacanrec[3]);
        BMS_can.rated_volt_can = ((datacanrec[4] << 24) + (datacanrec[5]<< 16)+(datacanrec[6] << 8) + datacanrec[7]);
   
      break;


    case 0x51:                             //BOARD NUMBER
        can_send(senddata ,slaveid,8);
		 		 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);
		
        BMS_can.boardnum_can = datacanrec[0];
        BMS_can.board1cellnum_can = datacanrec[1];
        BMS_can.board2cellnum_can = datacanrec[2];
        BMS_can.board1tempnum_can = datacanrec[4];
      
      break;

    case 0x52:                          //total time of charge and discharge
       can_send(senddata ,slaveid,8);
		  		 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);

        BMS_can.cumilative_charge_can = ((datacanrec[0] << 24) + (datacanrec[1]<< 16)+(datacanrec[2] << 8) + datacanrec[3]);
        BMS_can.cumilative_discharge_can =((datacanrec[4] << 24) + (datacanrec[5]<< 16)+(datacanrec[6] << 8) + datacanrec[7]);

      
      break;

    case 0x53:                                //battery type sleep time battery prod
       can_send(senddata ,slaveid,8);
		 		 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);




        BMS_can.boardtypebm_can =datacanrec[0];
        BMS_can.activebm_can = datacanrec[1];
        BMS_can.boardyear_can = datacanrec[2];
        BMS_can.boardmonth_can = datacanrec[3];
        BMS_can.boardday_can = datacanrec[4];
        BMS_can.secondsleepbm_can = ((datacanrec[5] << 8) + datacanrec[6]);




      
      break;

    case 0x54:                              //FIRMWARE INDEx number
       can_send(senddata ,slaveid,8);
		  delay(1);
		  can_recieve(datacanrec,recid);
		
        for (int a = 4; a < 12; a++)
        {
          if (datacanrec[a] > 0x20)
          {
            BMS_can.Firmwarevers_can += String((datacanrec[a] - 0x30));
          } else
          {
            BMS_can.Firmwarevers_can += "0";
          }
        }


       // firmversion_can = BMS_can.Firmwarevers_can;
       // BMS_can.Firmwarevers_can = "";

      
      break;
/*
    case 0x56:                                  //ip
       send_read_BMS(0x56);
	   delay(500);
      recieve_back(0x56);
      checksum8_recieve(13, BMS_Recieve, checksm);
      if (BMS_Recieve[12] == checksm)
      {
        //       BMS.bat_str=BMS_Recieve[4];
        //       BMS.bat_temp=BMS_Recieve[5];
        //       BMS.charg_sts=BMS_Recieve[6];
        //       BMS.load_sts=BMS_Recieve[7];
      }
      break;

    case 0x57:                                //BATTERY CODE 5 frame
       send_read_BMS(0x57);
	   delay(500);
      recieve_back(0x57);
      checksum8_recieve(13, BMS_Recieve, checksm);
      if (BMS_Recieve[12] == checksm)
      {
        //       BMS.bat_str=BMS_Recieve[4];
        //       BMS.bat_temp=BMS_Recieve[5];
        //       BMS.charg_sts=BMS_Recieve[6];
        //       BMS.load_sts=BMS_Recieve[7];
      }
      break;
*/
    case 0x59:                                //cell volt high
      can_send(senddata ,slaveid,8);
		  		 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);
		
		
		
        BMS_can.cell_volthigh1_can = ((datacanrec[0] << 8) + datacanrec[1]);
        BMS_can.cell_volthigh2_can = ((datacanrec[2] << 8) + datacanrec[3]);
        BMS_can.cell_voltlow1_can = ((datacanrec[4] << 8) + datacanrec[5]);
        BMS_can.cell_voltlow2_can = ((datacanrec[6] << 8) + datacanrec[7]);



      
      break;

    case 0x60:                               //SHORT CURRENT
    can_send(senddata ,slaveid,8);
		 		 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);


        BMS_can.short_current_can = ((datacanrec[0] << 8) + datacanrec[1]);
        BMS_can.cur_sampling_res_can = ((datacanrec[2] << 8) + datacanrec[3]);           //(BMS.cur_sampling_res/1000);

        //BMS.cur_sampling_resistance= (BMS.cur_sampling_res/1000);
      
      break;

    case 0x61:
			//???
      can_send(senddata ,slaveid,8);
		  delay(1);
		  can_recieve(datacanrec,recid);
        //       BMS.bat_str=BMS_Recieve[4];
        //       BMS.bat_temp=BMS_Recieve[5];
        //       BMS.charg_sts=BMS_Recieve[6];
        //       BMS.load_sts=BMS_Recieve[7];
      
      break;
/*
    case 0x62:                                 //SOFTWARE VERS
       send_read_BMS(0x62);
	   delay(500);
      recieve_back(0x62);
      checksum8_recieve(13, BMS_Recieve, checksm);
      if (BMS_Recieve[12] == checksm)
      {
        //       BMS.bat_str=BMS_Recieve[4];
        //       BMS.bat_temp=BMS_Recieve[5];
        //       BMS.charg_sts=BMS_Recieve[6];
        //       BMS.load_sts=BMS_Recieve[7];
      }
      break;

    case 0x63:                               //hardware version
       send_read_BMS(0x63);
	   delay(500);
      recieve_back(0x63);
      checksum8_recieve(13, BMS_Recieve, checksm);
      if (BMS_Recieve[12] == checksm)
      {
        //       BMS.bat_str=BMS_Recieve[4];
        //       BMS.bat_temp=BMS_Recieve[5];
        //       BMS.charg_sts=BMS_Recieve[6];
        //       BMS.load_sts=BMS_Recieve[7];
      }
      break;

*/

    case 0x65:                               //board num slave
    can_send(senddata ,slaveid,8);
		  		 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);
		
        BMS_can.board_number_can = datacanrec[0];
        BMS_can.slave_number_can = datacanrec[1];

      
      break;



    case 0x5A:                               //sum volt high
      can_send(senddata ,slaveid,8);
		  		 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);

        BMS_can.sumv_high1_can = ((datacanrec[0] << 8) + datacanrec[1]); //  sumv/10
        BMS_can.sumv_high2_can = ((datacanrec[2] << 8) + datacanrec[3]);
        BMS_can.sumv_low1_can = ((datacanrec[4] << 8) + datacanrec[5]);
        BMS_can.sumv_low2_can = ((datacanrec[6] << 8) + datacanrec[7]);
      
      break;

    case 0x5B:                               //discharge  CHARGE CURRENT
      can_send(senddata ,slaveid,8);
		 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
	
		  can_recieve(datacanrec,recid);




        BMS_can.charge_curr1_can = ((datacanrec[0] << 8) + datacanrec[1]);
        BMS_can.charge_curr2_can = ((datacanrec[2] << 8) + datacanrec[3]);
        BMS_can.dischar_curr1_can = ((datacanrec[4] << 8) + datacanrec[5]);
        BMS_can.dischar_curr2_can = ((datacanrec[6] << 8) + datacanrec[7]);

        BMS_can.charge_curr1_can = ((30000 - BMS_can.charge_curr1_can) / 10);
        BMS_can.charge_curr2_can = ((30000 - BMS_can.charge_curr2_can) / 10);
        BMS_can.dischar_curr1_can = ((BMS_can.dischar_curr1_can - 30000) / 10);
        BMS_can.dischar_curr2_can = ((BMS_can.dischar_curr2_can - 30000) / 10);

      
      break;

    case 0x5C:                                //TEMP HIGH TEMP LOW
      can_send(senddata ,slaveid,8);
		 	 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);



        BMS_can.charge_temp_high1_can = (datacanrec[0] - 40);
        BMS_can.charge_temp_high2_can = (datacanrec[1] - 40);
        BMS_can.charge_temp_low1_can = (datacanrec[2] - 40);
        BMS_can.charge_temp_low2_can = (datacanrec[3] - 40);
        BMS_can.discharge_temp_high1_can = (datacanrec[4] - 40);
        BMS_can.discharge_temp_high2_can = (datacanrec[5] - 40);
        BMS_can.discharge_temp_low1_can = (datacanrec[6] - 40);
        BMS_can.discharge_temp_low2_can = (datacanrec[7] - 40);
      
      break;

    case 0x5D:                              //SOC
      can_send(senddata ,slaveid,8);
		  	 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);


        BMS_can.SOC_high1_can = (((datacanrec[0] << 8) + datacanrec[1]) / 10);
        BMS_can.SOC_high2_can = (((datacanrec[2] << 8) + datacanrec[3]) / 10);
        BMS_can.SOC_low1_can = (((datacanrec[4] << 8) + datacanrec[5]) / 10);
        BMS_can.SOC_low2_can = (((datacanrec[6] << 8) + datacanrec[7]) / 10);
      
      break;

    case 0x5E:                               //VOLT DIFFERENCE
      can_send(senddata ,slaveid,8);
	 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);


        BMS_can.volt_diff1_can = (((datacanrec[0] << 8) + datacanrec[1])); //   VOLTDIFF/1000
        BMS_can.volt_diff2_can = (((datacanrec[2] << 8) + datacanrec[3])); //   VOLTDIFF/1000
        BMS_can.temp_diff1_can = datacanrec[4];
        BMS_can.temp_diff2_can = datacanrec[5];

        //BMS.volt_diffir1=BMS.volt_diff1/1000;
        //BMS.volt_diffir2=BMS.volt_diff2/1000;

      
      break;

    case 0x5F:                             //BALANCE START
      can_send(senddata ,slaveid,8);
		 	 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
can_recieve(datacanrec,recid);

        BMS_can.balance_volt_can = (((datacanrec[0] << 8) + datacanrec[1]));
        BMS_can.balance_volt_diff_can = (((datacanrec[2] << 8) + datacanrec[3]));

        //BMS.balance_voltage=float(BMS.balance_volt/0x03E8);
        //BMS.balance_volt_diffir=float(BMS.balance_volt_diff/1000);


      
      break;

    case 0xD8:                             //??
 can_send(senddata ,slaveid,8);
		 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		 can_recieve(datacanrec,recid);
		
       
      
      break;



    case 0x90:
      can_send(senddata ,slaveid,8);
		 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);
      
        BMS_can.sum_voltage_can = ((datacanrec[0] << 8) + datacanrec[1]);
      
      
        BMS_can.current_can = ((datacanrec[4] << 8) + datacanrec[5]);
      

        BMS_can.gather_voltage_can = ((datacanrec[2] << 8) + datacanrec[3]);

  
        BMS_can.SOC_can = ((datacanrec[6] << 8) + datacanrec[7]);
		


      
      break;

    case 0x91:
			//Serial.println("data91");
      can_send(senddata ,slaveid,8);
		 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}

		
				  can_recieve(datacanrec,recid);
        
          BMS_can.max_cell_volt_can = ((datacanrec[0] << 8) + datacanrec[1]);
          BMS_can.max_cell_volt_number_can = datacanrec[2];
          BMS_can. min_cell_volt_can = ((datacanrec[3] << 8) + datacanrec[4]);
          BMS_can.min_cell_volt_number_can = datacanrec[5];
    
      break;

    case 0x92:
      can_send(senddata ,slaveid,8);
				 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);
		
   
          BMS_can.max_cell_temp_can = datacanrec[0];
          BMS_can.max_cell_temp_number_can = datacanrec[1];
          BMS_can. min_cell_temp_can = datacanrec[2];
          BMS_can.min_cell_temp_number_can = datacanrec[3];
     
      
      break;

    case 0x93:
      can_send(senddata ,slaveid,8);
		 		 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);
		

        BMS_can.state_can = datacanrec[0];
        BMS_can.charge_can =datacanrec[1];
        BMS_can.discharge_can = datacanrec[2];
        BMS_can.bms_life_can = datacanrec[3];
					
		rem1=datacanrec[4] << 24 ;
		rem2=datacanrec[5] << 16;
        rem3=datacanrec[6] << 8;
        rem4=datacanrec[7] ; 					
		BMS_can.rem_cap_can = (rem1+rem2+rem3+rem4);
				
      
      break;


    case 0x94:
      can_send(senddata ,slaveid,8);
				 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		  can_recieve(datacanrec,recid);

       BMS_can.bat_str_can = datacanrec[0];
        BMS_can.bat_temp_can = datacanrec[1];
       BMS_can.charg_sts_can = datacanrec[2];
        BMS_can.load_sts_can =datacanrec[3];
      
      break;

    case 0x95:
		//	Serial.println("data95");
		     can_send(senddata ,slaveid,8);
     delay(1);
	//	can_send(senddata ,0x18950140,8);
	      // delay(5);
        //  delay(1);
      for (int x = 0; x <6; x++)
      {
				
		for(int ab=0;ab<15;ab++)
		{
		     // Serial.println("a");
			// Serial.println(x);
		  can_recieve(datacanrec,recid);
				if(receive_id==recid&&datacanrec[0]==x+1)
			{
				break;
			}
      
		}
     
					
		
            BMS_can.cell_voltage_can[a] = ((datacanrec[1] << 8) + datacanrec[2]);
            BMS_can.cell_voltage_can[a + 1] = ((datacanrec[3] << 8) + datacanrec[4]);
            BMS_can.cell_voltage_can[a + 2] = ((datacanrec[5] << 8) + datacanrec[6]);
          a += 3;
        //delay(1);
				//Serial.println(x);
				//	Serial.println(datacanrec[0]);
    //delay(2);
      }
      break;
			
			
    case 0x96:
         can_send(senddata ,slaveid,8);
		delay(1);
		for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
		can_recieve(datacanrec,recid);
		
		
		
    //  for (int i = 0; i < 1; i++)
   //   {
			
     //  can_recieve(datacanrec,recid);

            BMS_can.cell_temperature_can[a] = datacanrec[1];
            BMS_can.cell_temperature_can[a + 1] = datacanrec[2];
            BMS_can.cell_temperature_can[a + 2] = datacanrec[3];
            BMS_can.cell_temperature_can[a + 3] = datacanrec[4];
            BMS_can.cell_temperature_can[a + 4] = datacanrec[5];
            BMS_can.cell_temperature_can[a + 5] = datacanrec[6];
            BMS_can.cell_temperature_can[a + 6] = datacanrec[7];
          
         // a += 7;
        

     // }


      break;

    case 0x97:

    can_send(senddata ,slaveid,8);
			 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}

        for (int c = 0; c < 8; c++)
        {
          BMS_can.cell_balance_can[c + 0] = bitRead(datacanrec[0], c);
        }

        for (int c = 0; c < 8; c++)
        {
          BMS_can.cell_balance_can[c + 7] = bitRead(datacanrec[1], c);
        }

        for (int c = 0; c < 8; c++)
        {
         BMS_can.cell_balance_can[c + 14] = bitRead(datacanrec[2], c);
        }



      

      break;

    case 0x98:

    can_send(senddata ,slaveid,8);
		 delay(1);

		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}


        for (int k = 0; k < 8; k++)
        {
          BMS_can.error_can[k + 0] = bitRead(datacanrec[0], k);
        }
        for (int k = 0; k < 8; k++)
        {
          BMS_can.error_can[k + 8] = bitRead(datacanrec[1], k);

        }

        for (int k = 0; k < 8; k++)
        {
          BMS_can.error_can[k + 16] = bitRead(datacanrec[2], k);

        }

        for (int k = 0; k < 8; k++)
        {
          BMS_can.error_can[k + 24] = bitRead(datacanrec[3], k);

        }

        for (int k = 0; k < 8; k++)
        {
          BMS_can.error_can[k + 32] = bitRead(datacanrec[4], k);

        }

        for (int k = 0; k < 8; k++)
        {
          BMS_can.error_can[k + 40] = bitRead(datacanrec[5], k);

        }
		
	        for (int b= 0; b < 28; b++) {
                if (BMS_can.error_can[b]==1) {
                   BMS_can.AlarmStatus_can=b;   
                  break;
                  }
				  else{
					 BMS_can.AlarmStatus_can=99; 
				  }
                }
				
        
              
      







      break;

    default:
      break;
	  


	}
  








}




//// SET   BMS   PARAMETERS    /////////////

bool set_boardnumber_BMS_can(uint8_t board_number, uint8_t *BMS_Set,uint8_t slave_id,uint8_t device_id)

{
	
	uint32_t slaveid=0x18220040;
  uint32_t recid=0x18224000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 
	
	
	
	uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

  sendpara[0] =board_number;
  sendpara[1] =  slave_id;
  sendpara[2] = 0x00;
  sendpara[3] = 0x00;
  sendpara[4] = 0x00;
  sendpara[5] = 0x00;
  sendpara[6] = 0x00;
  sendpara[7] = 0x00;
	
	   can_send(sendpara ,slaveid,8);
		delay(1);
	
			 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
	
	
	
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
        //param_save = false;
        return false;

      }
    

 

}


bool set_balancevolt_BMS(float balance_v, float diff_volt, uint8_t *BMS_Set,uint8_t device_id)

{

uint32_t slaveid=0x181F0040;
  uint32_t recid=0x181F4000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 

  
 


  uint16_t balancevolt = 0;
  uint16_t diffvolt = 0;

  balancevolt = balance_v * 1000;
  diffvolt = diff_volt * 1000;




uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

  sendpara[0] = highByte(balancevolt);
  sendpara[1] = lowByte(balancevolt);
  sendpara[2] = highByte(diffvolt);
  sendpara[3] = lowByte(diffvolt);

	
	   can_send(sendpara ,slaveid,8);
		 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}





bool set_cellvolt_BMS(float cellhigh_v, float celllow_volt, uint8_t *BMS_Set,uint8_t device_id)

{
  uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 


uint32_t slaveid=0x18190040;
  uint32_t recid=0x18194000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 

	
	
  uint16_t cellhvolt = 0;
  uint16_t celllvolt = 0;

  cellhvolt = cellhigh_v * 1000;
  celllvolt = celllow_volt * 1000;


  BMS_Set[4] = highByte(cellhvolt);
  BMS_Set[5] = lowByte(cellhvolt);
  BMS_Set[6] = highByte(cellhvolt);
  BMS_Set[7] = lowByte(cellhvolt);

  BMS_Set[8] = highByte(celllvolt);
  BMS_Set[9] = lowByte(celllvolt);
  BMS_Set[10] = highByte(celllvolt);
  BMS_Set[11] = lowByte(celllvolt);




  sendpara[0] = highByte(cellhvolt);
  sendpara[1] = lowByte(cellhvolt);
  sendpara[2] = highByte(cellhvolt);
  sendpara[3] = lowByte(cellhvolt);
  sendpara[4] = highByte(celllvolt);
  sendpara[5] = lowByte(celllvolt);
  sendpara[6] = highByte(celllvolt);
  sendpara[7] = lowByte(celllvolt);
 
	
	   can_send(sendpara ,slaveid,8);
			 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}


bool set_chargecurrent_BMS(float charge_cur, float discharge_cur, uint8_t *BMS_Set,uint8_t device_id)

{

 

uint32_t slaveid=0x181B0040;
  uint32_t recid=0x181B4000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 
 
  uint16_t chargecur = 0;
  uint16_t discharecur = 0;

  chargecur = (30000 - (charge_cur * 10));
  discharecur = (30000 + (discharge_cur * 10));





uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

  sendpara[0] = highByte(chargecur);
  sendpara[1] = lowByte(chargecur);
  sendpara[2] = highByte(chargecur);
  sendpara[3] = lowByte(chargecur);
  sendpara[4] = highByte(discharecur);
  sendpara[5] = lowByte(discharecur);
  sendpara[6] = highByte(discharecur);
  sendpara[7] = lowByte(discharecur);
 

	
	   can_send(sendpara ,slaveid,8);
			 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}





bool set_chargetemp_BMS(int charge_t, int charge_tl, int discharge_t, int discharge_tl, uint8_t *BMS_Set,uint8_t device_id)

{

uint32_t slaveid=0x181C0040;
  uint32_t recid=0x181C4000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 


  uint16_t chargetemp = 0;
  uint16_t dischargtemp = 0;
  uint16_t chargetempl = 0;
  uint16_t dischargtempl = 0;

  chargetemp = charge_t + 40;
  chargetempl = charge_tl + 40;
  dischargtemp = discharge_t + 40;
  dischargtempl = discharge_tl + 40;





uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

  sendpara[0] = chargetemp;;
  sendpara[1] = chargetemp;;
  sendpara[2] = chargetempl;
  sendpara[3] = chargetempl;
  sendpara[4] = dischargtemp;
  sendpara[5] = dischargtemp;
  sendpara[6] = dischargtempl;
  sendpara[7] = dischargtempl;
 

	
	   can_send(sendpara ,slaveid,8);
			 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}




bool set_soc_BMS(float soc, uint8_t *BMS_Set,uint8_t device_id)

{



uint32_t slaveid=0x18210040;
  uint32_t recid=0x18214000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 	
	

  uint16_t bmsoc = 0;


  bmsoc = soc * 10;




 


uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


  sendpara[6] = highByte(bmsoc);
  sendpara[7] = lowByte(bmsoc);
 

	
	   can_send(sendpara ,slaveid,8);
			 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}


bool set_rated_BMS(float ratedcap, float ratedvolt, uint8_t *BMS_Set,uint8_t device_id)

{
	
	uint32_t slaveid=0x18100040;
  uint32_t recid=0x18104000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 



  uint8_t checksm = 0;
  uint32_t ratedc = 0;
  uint32_t ratedv = 0;
	
  uint16_t ratedc2=0;
	uint16_t ratedc3=0;
	
  uint16_t ratedv2=0;
	uint16_t ratedv3=0;
	
  ratedc = ratedcap * 1000;
  ratedv = ratedvolt * 1000;
	
	
ratedc2=(0xffff0000&ratedc)>>16;
ratedc3=0x0000ffff&ratedc;

ratedv2=(0xffff0000&ratedv)>>16;
ratedv3=0x0000ffff&ratedv;
	

	



uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

  sendpara[0] = highByte(ratedc2);
  sendpara[1] = lowByte(ratedc2);
  sendpara[2] = highByte(ratedc3);
  sendpara[3] = lowByte(ratedc3);
  sendpara[4] = highByte(ratedv2);
  sendpara[5] = lowByte(ratedv2);
  sendpara[6] = highByte(ratedv3);
  sendpara[7] = lowByte(ratedv3);
 

	
	   can_send(sendpara ,slaveid,8);
			 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}


bool set_board_BMS(uint8_t boardnum , uint8_t *boardnumvolt, uint8_t *boardnumtemp, uint8_t *BMS_Set,uint8_t device_id)

{






uint32_t slaveid=0x18110040;
  uint32_t recid=0x18114000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 



uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

  sendpara[0] = boardnum;
  sendpara[1] = boardnumvolt[0];
  sendpara[2] = boardnumvolt[1];
  sendpara[3] = boardnumvolt[2];
  sendpara[4] = boardnumtemp[0];
  sendpara[5] = boardnumtemp[1];
  sendpara[6] = boardnumtemp[2];
  sendpara[7] = 0;
 

	
	   can_send(sendpara ,slaveid,8);
				 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }
			
}



bool set_manufect_BMS(uint8_t boardtype , uint8_t *boardmanu, uint16_t secondsleep, uint8_t *BMS_Set, uint8_t active,uint8_t device_id)

{
uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  uint8_t checksm = 0;



uint32_t slaveid=0x18130040;
  uint32_t recid=0x18134000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 


  sendpara[0] = boardtype;
  sendpara[1] = active;                       // battery operation type    1 long press  2 short press
  sendpara[2] = boardmanu[0];             //manufect year
  sendpara[3]  = boardmanu[1];             //manufect month
  sendpara[4] = boardmanu[2];            //manufect day
  sendpara[5]= highByte(secondsleep);
  sendpara[6] = lowByte(secondsleep);
  sendpara[7] = 0;




	
	   can_send(sendpara ,slaveid,8);
				 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }
			
}


bool set_cumilative_charge(uint8_t cumi_charge , uint8_t cumi_dischar ,uint8_t device_id)

{


	
	uint32_t slaveid=0x18120040;
  uint32_t recid=0x18124000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 
	


uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 

  sendpara[0] = 0;
  sendpara[1] = 0;                       
  sendpara[2] = 0;             
  sendpara[3]  = cumi_charge;            
  sendpara[4] = 0;            
  sendpara[5]= 0;
  sendpara[6] =0;
  sendpara[7] = cumi_dischar;




	
	   can_send(sendpara ,slaveid,8);
			 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}


bool set_shortcurr_sampres(uint8_t short_curr , uint8_t miliohm,uint8_t device_id)

{

	uint32_t slaveid=0x18200040;
  uint32_t recid=0x18204000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 
	
	
  uint16_t mohm = 0;
 


  mohm = miliohm * 1000;





uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 

  sendpara[0] = 0;
  sendpara[1] = short_curr;                       
  sendpara[2] = highByte(mohm);        
  sendpara[3]  = lowByte(mohm);           
  sendpara[4] = 0;            
  sendpara[5]= 0;
  sendpara[6] =0;
  sendpara[7] = 0;




	
	   can_send(sendpara ,slaveid,8);
				 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}
/*
bool set_FW(String vers_num )

{
  int a = 0;
  uint8_t digits = 0;
  uint8_t checksm = 0;

  BMS_Set[0] = 0xA5;
  BMS_Set[1] = 0x40;
  BMS_Set[2] = 0x14;
  BMS_Set[3] = 0x08;

  digits = vers_num.length();
  for (int i = 0; i < digits; i++)
  {
    BMS_Set[i + 4] = ((vers_num.substring(i)).toInt());
  }
  if (digits < 8)
  {
    a = digits + 5;
    for (a; a < 12; a++)
    {
      BMS_Set[a] = 0x20;
    }

  }


  checksum8(13 , BMS_Set);

  for (int a = 0; a < 13; a++)
  {

    Serial2.write(BMS_Set[a]);
    //Serial.println(BMS_Send[a],HEX);
  }

  delay(100);

  recieve_parameter();

  checksum8_recieve(13, BMS_Recieve_parameter, checksm);

  if (BMS_Recieve_parameter[12] == checksm)
  {

    if (BMS_Recieve_parameter[2] == 0x14)
    {
      if (BMS_Recieve_parameter[4] == 0x01)
      {
        param_save = true;
        return true;
      } else if (BMS_Recieve_parameter[4] == 0x00)
      {
        param_save = false;
        return true;

      }
    } else

    {
      return false;

    }


  } else

  {
    return false;

  }

  for (int i = 0; i < 13; i++)
  {
    BMS_Recieve_parameter[i] = 0;
  }

}

bool set_charge_mode(bool status, uint8_t *BMS_Set_blue,uint8_t device_id)

{

  uint32_t slaveid=0x181F0040;
  uint32_t recid=0x181F4000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 


  BMS_Set_blue[0] = 0xD2;
  BMS_Set_blue[1] = 0x06;
  BMS_Set_blue[2] = 0x00;
  BMS_Set_blue[3] = 0xA5;

  BMS_Set_blue[4] = 0x00;
	
  if ( status == true)
  {
     sendpara[5] = 0x01;
  } else
  {
     sendpara[5] = 0x00;
  }



 uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 


  sendpara[1] = 0;                       
  sendpara[2] = 0;        
  sendpara[3]  = 0;          
  sendpara[4] = 0;            
  sendpara[5]= 0;
  sendpara[6] =0;
  sendpara[7] = 0;




	
	   can_send(sendpara ,slaveid,8);
		delay(1);
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}


bool set_discharge_mode(bool status, uint8_t *BMS_Set_blue,uint8_t device_id)

{

  uint16_t checksm = 0;


  BMS_Set_blue[0] = 0xD2;
  BMS_Set_blue[1] = 0x06;
  BMS_Set_blue[2] = 0x00;
  BMS_Set_blue[3] = 0xA6;

  BMS_Set_blue[4] = 0x00;
  if ( status == true)
  {
     sendpara[0] = 0x01;
  } else
  {
     sendpara[0] = 0x00;
  }




uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 

  sendpara[0] = 0;
  sendpara[1] = short_curr;                       
  sendpara[2] = highByte(mohm);        
  sendpara[3]  = lowByte(mohm);           
  sendpara[4] = 0;            
  sendpara[5]= 0;
  sendpara[6] =0;
  sendpara[7] = 0;




	
	   can_send(sendpara ,slaveid,8);
		delay(1);
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}
*/

bool set_cellvolt_alarm(float high_level1 , float high_level2, float low_level1, float low_level2,uint8_t device_id)

{

  uint16_t high1 = 0;
  uint16_t high2 = 0;
  uint16_t low1 = 0;
  uint16_t low2 = 0;
  

  high1 = high_level1 * 1000;
  high2 = high_level2 * 1000;
  low1 = low_level1 * 1000;
  low2 = low_level2 * 1000;





 uint32_t slaveid=0x18190040;
  uint32_t recid=0x18194000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 



uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 

  sendpara[0] = highByte(high1);
  sendpara[1] = lowByte(high1);                      
  sendpara[2] = highByte(high2);       
  sendpara[3]  = lowByte(high2);           
  sendpara[4] = highByte(low1);            
  sendpara[5]= lowByte(low1);
  sendpara[6] =highByte(low2);
  sendpara[7] =lowByte(low2);




	
	   can_send(sendpara ,slaveid,8);
			 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}

bool set_sumvolt_alarm(float high_level1 , float high_level2, float low_level1, float low_level2,uint8_t device_id)

{

  uint16_t high1 = 0;
  uint16_t high2 = 0;
  uint16_t low1 = 0;
  uint16_t low2 = 0;
  uint8_t checksm = 0;

  high1 = high_level1 * 10;
  high2 = high_level2 * 10;
  low1 = low_level1 * 10;
  low2 = low_level2 * 10;



uint32_t slaveid=0x181A0040;
  uint32_t recid=0x181A4000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 


uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 

  sendpara[0] = highByte(high1);
  sendpara[1] = lowByte(high1);                      
  sendpara[2] = highByte(high2);       
  sendpara[3]  = lowByte(high2);           
  sendpara[4] = highByte(low1);            
  sendpara[5]= lowByte(low1);
  sendpara[6] =highByte(low2);
  sendpara[7] =lowByte(low2);




	
	   can_send(sendpara ,slaveid,8);
				 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}



bool set_chargediscurr_alarm(float charge_level1 , float charge_level2, float discharge_level1, float discharge_level2,uint8_t device_id)

{

  uint16_t high1 = 0;
  uint16_t high2 = 0;
  uint16_t low1 = 0;
  uint16_t low2 = 0;
  uint8_t checksm = 0;

  high1 = (30000 - (charge_level1 * 10));
  high2 = (30000 - (charge_level2 * 10));
  low1 = ((discharge_level1 * 10) + 30000);
  low2 = ((discharge_level2 * 10) + 30000);



uint32_t slaveid=0x181B0040;
  uint32_t recid=0x181B4000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 




  
uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 

  sendpara[0] = highByte(high1);
  sendpara[1] = lowByte(high1);                      
  sendpara[2] = highByte(high2);       
  sendpara[3]  = lowByte(high2);           
  sendpara[4] = highByte(low1);            
  sendpara[5]= lowByte(low1);
  sendpara[6] =highByte(low2);
  sendpara[7] =lowByte(low2);




	
	   can_send(sendpara ,slaveid,8);
				 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}


bool set_volttemp_diff_alarm(float voltdiff_level1 , float voltdiff_level2, uint8_t temp_level1, uint8_t temp_level2,uint8_t device_id)

{

  uint16_t high1 = 0;
  uint16_t high2 = 0;

  uint8_t checksm = 0;

  high1 = voltdiff_level1 * 1000;
  high2 = voltdiff_level2 * 1000;




uint32_t slaveid=0x181E0040;
  uint32_t recid=0x181E4000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 

 


uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 

  sendpara[0] = highByte(high1);
  sendpara[1] = lowByte(high1);                      
  sendpara[2] = highByte(high2);       
  sendpara[3]  = lowByte(high2);           
  sendpara[4] = temp_level1;            
  sendpara[5]= temp_level2;
  sendpara[6] =0;
  sendpara[7] =0;




	
	   can_send(sendpara ,slaveid,8);
				 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}

bool set_soc_alarm(float high_level1 , float high_level2, float low_level1, float low_level2,uint8_t device_id)

{

  uint16_t high1 = 0;
  uint16_t high2 = 0;
  uint16_t low1 = 0;
  uint16_t low2 = 0;
  uint8_t checksm = 0;

  high1 = high_level1 * 10;
  high2 = high_level2 * 10;
  low1 = low_level1 * 10;
  low2 = low_level2 * 10;





uint32_t slaveid=0x181D0040;
  uint32_t recid=0x181D4000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 


uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 

  sendpara[0] = highByte(high1);
  sendpara[1] = lowByte(high1);                      
  sendpara[2] = highByte(high2);       
  sendpara[3]  = lowByte(high2);           
  sendpara[4] = highByte(low1);            
  sendpara[5]= lowByte(low1);
  sendpara[6] =highByte(low2);
  sendpara[7] =lowByte(low2);




	
	   can_send(sendpara ,slaveid,8);
				 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}


bool set_bmscurr_calibr(float curr_level , uint8_t calibr_type,uint8_t device_id)

{
 // ZERO DRIFT 1  FULL PARTIAL 2 CURRENT CORRECTION 3 CALIBRE TYPE  FOR 0 CURRENT CHOOSE 1 ONE OTHER THIGS CHOOSE 2
  uint16_t high1 = 0;


  high1 = (30000 - (curr_level * 10));




uint32_t slaveid=0x18D40040;
  uint32_t recid=0x18D44000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 




  
uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 

  sendpara[0] = highByte(high1);
  sendpara[1] = lowByte(high1);                      
  sendpara[2] = calibr_type;       

	   can_send(sendpara ,slaveid,8);
				 delay(10); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}

     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}

bool set_voltbms_calib(float volt_level , uint8_t calib_type,uint8_t device_id)

{
// ZERO DRIFT 1  FULL PARTIAL 2 CURRENT CORRECTION 3 CALIBRE TYPE  FOR 0 CURRENT CHOOSE 1 ONE OTHER THIGS CHOOSE 2
	
	
  uint16_t high1 = 0;


 

  high1 = volt_level * 10;





uint32_t slaveid=0x18D10040;
  uint32_t recid=0x18D14000;

slaveid=(((device_id<<8))|slaveid);  
recid=(((device_id))|recid); 

 


uint8_t sendpara[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 

  sendpara[0] = highByte(high1);
  sendpara[1] = lowByte(high1);                      
  sendpara[2] = calib_type;       




	
	   can_send(sendpara ,slaveid,8);
				 delay(1); 		 
	for(int ab=0;ab<10;ab++)
		{
		
		  can_recieve(datacanrec,recid);
				if(receive_id==recid)
			{
				break;
			}

		}
     can_recieve(datacanrec,recid);
	
	



 

  
      if (datacanrec[0] == 0x01)
      {
       // param_save = true;
        return true;
      } else if (datacanrec[0] == 0x00)
      {
       // param_save = false;
        return false;

      }

}




// not working*****************************************
/*
bool set_temp_alarm(uint8_t chigh_level1 , uint8_t chigh_level2, uint8_t clow_level1, uint8_t clow_level2, uint8_t dhigh_level1 , uint8_t dhigh_level2, uint8_t dlow_level1, uint8_t dlow_level2)

{

  uint8_t chigh1 = 0;
  uint8_t  chigh2 = 0;
  uint8_t  clow1 = 0;
  uint8_t clow2 = 0;

  uint8_t dhigh1 = 0;
  uint8_t  dhigh2 = 0;
  uint8_t  dlow1 = 0;
  uint8_t dlow2 = 0;

  uint8_t checksm = 0;

  chigh1 = chigh_level1 + 40;
  chigh2 = chigh_level2 + 40;
  clow1 = clow_level1 + 40;
  clow2 = clow_level2 + 40;

  dhigh1 = dhigh_level1 + 40;
  dhigh2 = dhigh_level2 + 40;
  dlow1 = dlow_level1 + 40;
  dlow2 = dlow_level2 + 40;

  BMS_Set[0] = 0xA5;
  BMS_Set[1] = 0x40;
  BMS_Set[2] = 0x1C;
  BMS_Set[3] = 0x08;


  BMS_Set[4] = chigh1;
  BMS_Set[5] = chigh2;
  BMS_Set[6] = clow1;
  BMS_Set[7] = clow2;
  BMS_Set[8] = dhigh1;
  BMS_Set[9] = dhigh2;
  BMS_Set[10] = dlow1;
  BMS_Set[11] = dlow2;


  checksum8(13 , BMS_Set);

  for (int a = 0; a < 13; a++)
  {

    Serial2.write(BMS_Set[a]);
    //Serial.println(BMS_Set[a],HEX);
  }

  delay(100);

  recieve_parameter();

  checksum8_recieve(13, BMS_Recieve_parameter, checksm);

  if (BMS_Recieve_parameter[12] == checksm)
  {

    if (BMS_Recieve_parameter[2] == 0x1C)
    {
      if (BMS_Recieve_parameter[4] == 0x01)
      {
        param_save = true;
        return true;
      } else if (BMS_Recieve_parameter[4] == 0x00)
      {
        param_save = false;
        return true;

      }
    } else

    {
      return false;

    }

  } else

  {
    return false;

  }

  for (int i = 0; i < 13; i++)
  {
    BMS_Recieve_parameter[i] = 0;
  }

}

*/








 void send_inverter(float soc, float total_volt, float total_current,  uint32_t device_id)

{
	                  
	 uint32_t slaveid = device_id;
	 //uint32_t slaveid = 0x18D10040;
						
	 //slaveid = (((device_id << 8)) | slaveid);
	



uint16_t socc=soc*10;

	uint16_t current1 = 0;
	uint8_t checksm = 0;
	uint16_t volt_total = (total_volt * 10);
	current1 = (30000 + (total_current * 10));

	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	
	sendpara[0] = highByte(volt_total);
	sendpara[1] = lowByte(volt_total);
	sendpara[2] = highByte(current1);
	sendpara[3] = lowByte(current1);
	sendpara[4] = highByte(socc);
	sendpara[5] = lowByte(socc);
	sendpara[6] = 0;
	sendpara[7] = 0;
	
	delay(10);
	can_send(sendpara, slaveid, 8);
	delay(1);
	//Serial.println("sendpara[i], HEX");
	for(int i=0;i<8;i++)
	{ 
		//Serial.println(sendpara[i], HEX);

 }
	//Serial.println("sendpara[i], HEX");

}





 void encap_canrec(uint8_t id, uint8_t device_id)
 {
	 uint32_t slaveid = 0x12000050;
	 uint32_t recid =   0x12005000;
	 uint8_t checksm = 0;


	 slaveid = (((id << 16) + (device_id << 8)) | slaveid);
	 recid = (((id << 16) + (device_id)) | recid);

	 uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	 //Serial.println(slaveid,HEX);
	 //Serial.println(recid,HEX);
	 switch (id)
	 {

	 case 0x01:
		 //Serial.println("data91");
		// for (int i = 0; i < 1; i++)
		// {
			 can_send(sendpara, slaveid, 8);
			 //delay(5);
		 //}
		 //delay(2000);
		 delay(500);
		 for (int ab = 0; ab < 10; ab++)
		 {
			// Serial.println(receive_id, HEX);
			 can_recieve(datacanrec, recid);
			 if (receive_id == recid)
			 {
				 break;
			 }

		 }


		 can_recieve(datacanrec, recid);

		 encap_volt = (((datacanrec[0] << 8) + datacanrec[1]) / 10);
		 encap_current = (((datacanrec[2] << 8) + datacanrec[3]) /10);
		 encap_soc = datacanrec[4];

		 for (int i = 0; i < 8; i++)
		 {
			 datacanrec[i] = 0;

		 }
		// encap_discurrent = (((datacanrec[5] << 8) + datacanrec[6])/10);
		// encap_current = ((30000 - encap_current) / 10);
		// encap_discurrent = ((( encap_discurrent) -30000)/10);


		// Serial.println(encap_volt);
		// Serial.println(encap_current);
		// Serial.println(encap_discurrent);
		// Serial.println(encap_soc);
		 break;

	 default:
		 break;
	 }
 }






















#endif