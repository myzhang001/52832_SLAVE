#ifndef __SOMPUTON_BLE_HANDLE_H
#define __SOMPUTON_BLE_HANDLE_H


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nordic_common.h"


#include "Protocol_Analysis.h"








void get_real_time_data_cmd(void);
void bond_cmd(void);
void clear_history_data_cmd(void);
void set_device_time_cmd(uint8_t *data_info);
void get_device_time_cmd(uint32_t second);
void control_device_cmd(uint8_t *ctrl_data,uint8_t length);
void Clife_GetHisData(uint16_t cmd, uint8_t* data, uint16_t len);
void Clife_GenerateHisData(void);
void bond_cmd(void);



#endif

