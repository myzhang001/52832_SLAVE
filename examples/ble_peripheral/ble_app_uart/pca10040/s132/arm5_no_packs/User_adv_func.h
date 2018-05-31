#ifndef __user_adv_func_h
#define __user_adv_func_h

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nordic_common.h"
#include "ble_db_discovery.h"




typedef enum{
    E_MATCH_NAME     = 0X00,  //匹配名字
    E_MATCH_SCNA_RSP = 0X01,   //匹配扫描应答
    E_CONNECTED_TARGET = 0X02  //连接到目标设备
}_e_match_dev;



#define USER_ADV_NAME      0X00
#define USER_ADV_SCAN_RSP  0X01      //扫描应答 1 表示 scan_rsp 里面的数据








extern bool  User_Match_Adv_Addr(ble_gap_addr_t addr,ble_gap_addr_t *dev_mac);
extern void  find_target_device_mac(ble_evt_t const * p_ble_evt,ble_gap_addr_t * device_addr);
extern void match_scanrsp_func(ble_gap_evt_adv_report_t *adv_report,ble_gap_addr_t addr_mac);

#endif


