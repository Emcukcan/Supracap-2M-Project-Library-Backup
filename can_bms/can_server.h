#ifndef can_server_h
#define can_server_h


#include <can_smart.h>

uint8_t battery_balance = 0;
uint8_t silence = 0;
uint8_t rec_data[8];
uint8_t heartbeat =0;
uint8_t inverter_state = 0;
uint16_t power = 0;

static uint16_t crc161_blue(uint16_t crc, uint8_t a)
{
	int i;

	crc ^= a;
	for (i = 0; i < 8; ++i)
	{
		if (crc & 1)
			crc = (crc >> 1) ^ 0xA001;
		else
			crc = (crc >> 1);
	}

	return crc;
}



uint16_t MORC16_blue(uint8_t* buf, uint8_t len)
{
	uint16_t u16CRC = 0xFFFF;
	for (int i = 0; i < len; i++)
	{
		u16CRC = crc161_blue(u16CRC, buf[i]);
	}

	return u16CRC;
}

bool recieve_data(void)
{
	
	can_recieve(rec_data, 0x1801F150);
	if (receive_id == 0x1801F150)
	{
		heartbeat = rec_data[0];
		inverter_state = rec_data[1];
		power = rec_data[2] << 8 + rec_data[3];
		silence=bitRead(2,0);
		battery_balance = bitRead(4, 2);
		return 1;
		receive_id = 0;
	}
	receive_id = 0;
	return 0;

}


//ID: 0x180150F1

bool set_maxvoltage(float max_cellvolt, float min_cellvolt, uint8_t SOC, uint8_t SOH, uint8_t relay_state, uint32_t device_id)

{
	//relay_state 0 open 1 close
	uint16_t maxvolt = 0;
	uint16_t minvolt = 0;
	uint8_t checksm = 0;
	maxvolt = (max_cellvolt * 1000);
	minvolt = (min_cellvolt * 1000);
	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[0] = highByte(maxvolt);
	sendpara[1] = lowByte(maxvolt);
	sendpara[2] = highByte(minvolt);
	sendpara[3] = lowByte(minvolt);
	sendpara[4] = SOC;
	sendpara[5] = SOH;
	sendpara[6] = 0;
	sendpara[7] = relay_state;
	delay(5);
	can_send(sendpara, device_id, 8);
	delay(200);
	return recieve_data();
}


//ID: 0x180250F1
bool set_totalvoltage(float totalvolt, float totalcurrent, float charge_maxcurr, float discharge_maxcurr ,uint32_t device_id)

{
	
	uint16_t totalvolts = 0;
	uint16_t totalcurrents = 0;
	uint16_t charge_curr = 0;
	uint16_t discharge_curr = 0;
	uint8_t checksm = 0;
	totalvolts = totalvolt * 10;
	totalcurrents = totalcurrent * 10;
	charge_curr = charge_maxcurr*10;
	discharge_curr = discharge_maxcurr * 10;
	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[0] = highByte(totalvolts);
	sendpara[1] = lowByte(totalvolts);
	sendpara[2] = highByte(totalcurrents);
	sendpara[3] = lowByte(totalcurrents);
	sendpara[4] = highByte(charge_curr);
	sendpara[5] = lowByte(charge_curr);
	sendpara[6] = highByte(discharge_curr);
	sendpara[7] = lowByte(discharge_curr);
	delay(5);
	can_send(sendpara, device_id, 8);
	delay(200);
	return recieve_data();

}

//ID: 0x180350F1
bool set_groupnumber(uint8_t maxvolt_grpnm, uint8_t maxvolt_packnm, uint8_t maxvolt_boxnm, uint8_t maxtemp_grpnm, uint8_t maxtemp_packnm, uint8_t maxtemp, uint32_t device_id)

{

	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[0] = maxvolt_grpnm;
	sendpara[1] = maxvolt_packnm;
	sendpara[2] = maxvolt_boxnm;
	sendpara[3] = maxtemp_grpnm;
	sendpara[4] = maxtemp_packnm;
	sendpara[5] = maxtemp;
	sendpara[6] = 0;
	sendpara[7] = 0;
	delay(5);
	can_send(sendpara, device_id, 8);
	delay(200);
	return recieve_data();

}

//ID: 0x180450F1
bool set_groupnumbermin(uint8_t minvolt_grpnm, uint8_t minvolt_packnm, uint8_t minvolt_boxnm, uint8_t maxtemp_grpnm, uint8_t maxtemp_packnm, uint8_t maxtemp, uint32_t device_id)

{

	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[0] = minvolt_grpnm;
	sendpara[1] = minvolt_packnm;
	sendpara[2] = minvolt_boxnm;
	sendpara[3] = maxtemp_grpnm;
	sendpara[4] = maxtemp_packnm;
	sendpara[5] = maxtemp ;
	sendpara[6] = 0;
	sendpara[7] = 0;
	delay(5);
	can_send(sendpara, device_id, 8);
	delay(200);
	return recieve_data();

}

/*
 Warning Level1_2：                                
Bit0  Charge current high
Bit1  Discharge current high
Bit2  SOC high
Bit3  SOC low
Bit4  Group voltage different high
Bit5  Reserved
Bit6  Reserved
Bit7  Reserved
system_state
Bit0 System waiting
Bit1 Charging finish
Bit2    Discharging finish
Bit3 Level 1 warning
Bit4 Level 2 warning
Bit5 Level 3 protection
Bit6 Level 4 protection
Bit7 Reserved

Warning Level1_1：
Bit0 Temp high
Bit1 Temp low
Bit2 Temp different high
Bit3 total voltage high
Bit4 total voltage low
Bit5 Cell voltage high
Bit6 Cell voltage low
Bit7 Cell voltage different high
BMS_CONTROLBIT
Bit0-Bit1 0:Normal 1:Silence
Bit2-Bit3 0:Normal 1:Battery forbid balance
Bit4-Bit7 Reserved
BATTERY STATE
0：Wait 1：Forbid charge and discharge:2：Forbid charge 3：Forbid discharge 4:charging
5：discharging


*/
/*
//ID:0x180650F1
bool set_warnings(uint8_t battery_state, uint8_t system_state[7], uint8_t warning_level1[8], uint8_t warning_level2[5], uint8_t control_bit[2] , uint32_t device_id)

{

uint16_t checksm = 0;

uint8_t systems = 0;
/*
systems =  (system_state[6] << 6) + (system_state[5] << 5) + (system_state[4] << 4) + (system_state[3] << 3) + (system_state[2] << 2) + (system_state[1] << 1) + system_state[0];


uint8_t warning1 = 0;
warning1 = (warning_level1[7] << 7) + (warning_level1[6] << 6) + (warning_level1[5] << 5) + (warning_level1[4] << 4) + (warning_level1[3] << 3) + (warning_level1[2] << 2) + (warning_level1[1] << 1) + warning_level1[0];

uint8_t warning2 = 0;

warning2 =  (warning_level2[4] << 4) + (warning_level2[3] << 3) + (warning_level2[2] << 2) + (warning_level2[1] << 1) + warning_level2[0];



uint8_t control = 0;

control = ((control_bit[0]<<2) +control_bit[0]);


	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[0] = battery_state;
	sendpara[1] = systems;
	sendpara[2] = warning1;
	sendpara[3] = warning2;
	sendpara[4] = control;
	sendpara[5] = 0;

	checksm = MORC16_blue(sendpara, 6);

	sendpara[7] = highByte(checksm);
	sendpara[6] = lowByte(checksm);

	
	delay(5);
	can_send(sendpara, device_id, 8);
		delay(200);
	return recieve_data();

}
*/
//ID:0x180650F1
bool set_warnings(uint8_t battery_state, uint8_t system_state, uint8_t warning_level1, uint8_t warning_level2, uint8_t control_bit, uint32_t device_id)

{

	uint16_t checksm = 0;

	uint8_t systems = 0;
	/*
	systems =  (system_state[6] << 6) + (system_state[5] << 5) + (system_state[4] << 4) + (system_state[3] << 3) + (system_state[2] << 2) + (system_state[1] << 1) + system_state[0];


	uint8_t warning1 = 0;
	warning1 = (warning_level1[7] << 7) + (warning_level1[6] << 6) + (warning_level1[5] << 5) + (warning_level1[4] << 4) + (warning_level1[3] << 3) + (warning_level1[2] << 2) + (warning_level1[1] << 1) + warning_level1[0];

	uint8_t warning2 = 0;

	warning2 =  (warning_level2[4] << 4) + (warning_level2[3] << 3) + (warning_level2[2] << 2) + (warning_level2[1] << 1) + warning_level2[0];



	uint8_t control = 0;

	control = ((control_bit[0]<<2) +control_bit[0]);
	*/

	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[0] = battery_state;
	sendpara[1] = system_state;
	sendpara[2] = warning_level1;
	sendpara[3] = warning_level2;
	sendpara[4] = control_bit;
	sendpara[5] = 0;

	checksm = MORC16_blue(sendpara, 6);

	sendpara[7] = highByte(checksm);
	sendpara[6] = lowByte(checksm);


	delay(5);
	can_send(sendpara, device_id, 8);
	delay(200);
	return recieve_data();

}








/*
 Warning Level4：
Bit0  Charge current high
Bit1  Discharge current high
Bit2  SOC high
Bit3  SOC low
Bit4  Group voltage different high
Bit5  Reserved
Bit6  Reserved
Bit7  Reserved

protect Level1：
Bit0 Temp high
Bit1 Temp low
Bit2 Temp different high
Bit3 total voltage high
Bit4 total voltage low
Bit5 Cell voltage high
Bit6 Cell voltage low
Bit7 Cell voltage different high

protect Level2：
Bit0  Charge current high
Bit1  Discharge current high
Bit2  Short circuit fault
Bit3  Reserved
Bit4  Battery open circuit fault
Bit5  Cell SPI acquisition Fault
Bit6  Master Slave communication Fault
Bit7  Reserved

protect Level3：
Bit0  Positive relay backcheck fault
Bit1  Negative relay backcheck fault
Bit2  The battery tripping
Bit3  Insulation fault
Bit4  Temp Level 4 Fault
Bit5  Reserved
Bit6  Reserved
Bit7  Reserved

Warning Level3：
Bit0 Temp high
Bit1 Temp low
Bit2 Temp different high
Bit3 total voltage high
Bit4 total voltage low
Bit5 Cell voltage high
Bit6 Cell voltage low
Bit7 Cell voltage different high



*/

//ID: 0x180750F1
/*
bool set_warnings2(uint8_t *warning_level3, uint8_t *warning_level4, uint8_t *protect_level1, uint8_t *protect_level2, uint8_t *protect_level3, uint32_t device_id)

{
	uint16_t checksm = 0;

	uint8_t warning3 = 0;

	warning3 = (warning_level3[7] << 7) + (warning_level3[6] << 6) + (warning_level3[5] << 5) + (warning_level3[4] << 4) + (warning_level3[3] << 3) + (warning_level3[2] << 2) + (warning_level3[1] << 1) + warning_level3[0];


	uint8_t warning4 = 0;
	warning4 =  (warning_level4[3] << 3) + (warning_level4[2] << 2) + (warning_level4[1] << 1) + warning_level4[0];

	uint8_t  protect1 = 0;

	protect1 = (protect_level1[7] << 7) + (protect_level1[6] << 6) + (protect_level1[5] << 5) + (protect_level1[4] << 4) + (protect_level1[3] << 3) + (protect_level1[2] << 2) + (protect_level1[1] << 1) + protect_level1[0];


	uint8_t  protect2 = 0;

	protect2 =  (protect_level2[6] << 6) + (protect_level2[5] << 5) + (protect_level2[4] << 4) + (protect_level2[3] << 3) + (protect_level2[2] << 2) + (protect_level2[1] << 1) + protect_level2[0];


	uint8_t  protect3 = 0;

	protect3 =  (protect_level3[4] << 4) + (protect_level3[3] << 3) + (protect_level3[2] << 2) + (protect_level3[1] << 1) + protect_level3[0];

	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[0] = warning3;
	sendpara[1] = warning4;
	sendpara[2] = protect1;
	sendpara[3] = protect2;
	sendpara[4] = protect3;
	sendpara[5] = 0;

	checksm = MORC16_blue(sendpara, 6);

	sendpara[7] = highByte(checksm);
	sendpara[6] = lowByte(checksm);


	delay(5);
	can_send(sendpara, device_id, 8);
		delay(200);
	return recieve_data();

}
*/


void set_warnings2(uint8_t warning_level3, uint8_t warning_level4, uint8_t protect_level1, uint8_t protect_level2, uint8_t protect_level3, uint32_t device_id)

{
	uint16_t checksm = 0;

	uint8_t warning3 = 0;
	/*
	warning3 = (warning_level3[7] << 7) + (warning_level3[6] << 6) + (warning_level3[5] << 5) + (warning_level3[4] << 4) + (warning_level3[3] << 3) + (warning_level3[2] << 2) + (warning_level3[1] << 1) + warning_level3[0];


	uint8_t warning4 = 0;
	warning4 = (warning_level4[3] << 3) + (warning_level4[2] << 2) + (warning_level4[1] << 1) + warning_level4[0];

	uint8_t  protect1 = 0;

	protect1 = (protect_level1[7] << 7) + (protect_level1[6] << 6) + (protect_level1[5] << 5) + (protect_level1[4] << 4) + (protect_level1[3] << 3) + (protect_level1[2] << 2) + (protect_level1[1] << 1) + protect_level1[0];


	uint8_t  protect2 = 0;

	protect2 = (protect_level2[6] << 6) + (protect_level2[5] << 5) + (protect_level2[4] << 4) + (protect_level2[3] << 3) + (protect_level2[2] << 2) + (protect_level2[1] << 1) + protect_level2[0];


	uint8_t  protect3 = 0;

	protect3 = (protect_level3[4] << 4) + (protect_level3[3] << 3) + (protect_level3[2] << 2) + (protect_level3[1] << 1) + protect_level3[0];
	*/
	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[0] = warning_level3;
	sendpara[1] = warning_level4;
	sendpara[2] = protect_level1;
	sendpara[3] = protect_level2;
	sendpara[4] = protect_level3;
	sendpara[5] = 0;

	checksm = MORC16_blue(sendpara, 6);

	sendpara[7] = highByte(checksm);
	sendpara[6] = lowByte(checksm);


	delay(5);
	can_send(sendpara, device_id, 8);
	delay(1);

}





#endif