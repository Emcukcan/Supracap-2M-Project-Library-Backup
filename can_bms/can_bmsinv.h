
#ifndef can_bmsinv_h
#define can_bmsinv_h


#include <can_smart.h>



bool set_chargediscurr(float max_curr, float max_discurr, float charge_cutoffvolt, float discharge_cutoffvolt, uint32_t device_id)

{

	uint16_t high1 = 0;
	uint16_t low1 = 0;
	uint8_t checksm = 0;
	uint16_t chargemax = (charge_cutoffvolt * 10);
	uint16_t dischargemax = (discharge_cutoffvolt * 10);
	high1 = (30000 + (max_curr * 10));
	low1 = (30000 + (max_discurr * 10));
	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[1] = highByte(chargemax);
	sendpara[0] = lowByte(chargemax);
	sendpara[3] = highByte(dischargemax);
	sendpara[2] = lowByte(dischargemax);
	sendpara[5] = highByte(high1);
	sendpara[4] = lowByte(high1);
	sendpara[7] = highByte(low1);
	sendpara[6] = lowByte(low1);
	delay(5);
	can_send(sendpara, device_id, 8);
	delay(1);

}


bool set_total_invert(uint8_t soc, uint8_t soh, uint16_t total_volt, float temp, float total_curr, uint32_t device_id)

{

	uint16_t high1 = 0;
	uint8_t checksm = 0;
	uint16_t chargemax = (total_volt * 10);
	uint16_t temp_1 = ((temp * 10) + 100);
	high1 = (30000 + (total_curr * 10));
	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[1] = highByte(chargemax);
	sendpara[0] = lowByte(chargemax);
	sendpara[3] = highByte(high1);
	sendpara[2] = lowByte(high1);
	sendpara[4] = highByte(temp_1);
	sendpara[5] = lowByte(temp_1);
	sendpara[6] = soc;
	sendpara[7] = soh;
	delay(5);
	can_send(sendpara, device_id, 8);
	delay(1);

}

bool set_alarm_invert(uint32_t device_id)

{
	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	delay(5);
	can_send(sendpara, device_id, 8);
	delay(5);

}

bool set_total_capacity(uint16_t bat_module_qu, uint8_t bat_mod_ser, uint8_t cell_qu, uint16_t voltage_lev, uint16_t capacity, uint32_t device_id)

{
	uint8_t checksm = 0;
	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[1] = highByte(bat_module_qu);
	sendpara[0] = lowByte(bat_module_qu);
	sendpara[3] = bat_mod_ser;
	sendpara[2] = cell_qu;
	sendpara[5] = highByte(voltage_lev);
	sendpara[4] = lowByte(voltage_lev);
	sendpara[7] = highByte(capacity);
	sendpara[6] = lowByte(capacity);
	delay(5);
	can_send(sendpara, device_id, 8);
	delay(1);

}


bool set_total_temp(uint16_t maxcell, uint16_t mincell, uint16_t batt_cell, uint16_t cell_tempnum, uint32_t device_id)

{
	uint8_t checksm = 0;
	uint16_t maxcell1 = ((maxcell * 10) + 100);
	uint16_t mincell1 = ((mincell * 10) + 100);
	uint8_t sendpara[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	sendpara[1] = highByte(maxcell1);
	sendpara[0] = lowByte(maxcell1);
	sendpara[3] = highByte(mincell1);
	sendpara[2] = lowByte(mincell1);
	sendpara[5] = highByte(batt_cell);
	sendpara[4] = lowByte(batt_cell);
	sendpara[7] = highByte(cell_tempnum);
	sendpara[6] = lowByte(cell_tempnum);
	delay(5);
	can_send(sendpara, device_id, 8);
	delay(1);

}

bool set_hardware(uint32_t device_id)

{
	uint8_t sendpara[] = { 0x00, 0x00, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00 };
	delay(5);
	can_send(sendpara, device_id, 8);
	delay(1);
}






#endif