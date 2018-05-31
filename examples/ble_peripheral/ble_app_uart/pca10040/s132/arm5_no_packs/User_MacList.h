#ifndef __maclist_h
#define __maclist_h

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nordic_common.h"


#define  MAX_LIST_LENGTH  8      //列表最大个数
#define  MAC_ADDR_LENGTH  6      //MAC 地址长度

typedef enum{
	E_01G = 0X00,
	E_01H = 0X01,
	E_03F = 0X02,
	E_03H = 0X03,
	E_06H = 0X04,
	E_06F = 0X05,
	E_08A = 0X06,
	E_08F = 0X07,
	E_09A = 0X08,
	E_09F = 0X0A
	
}_e_machine_model;



//单个设备信息
typedef struct{
	uint8_t 	mac_addr[MAC_ADDR_LENGTH];        	//设备mac 地址
	uint16_t 	conn_handle;       					//连接句柄
	uint8_t 	connected_flag;   					//连接状态
	int8_t     	rssi;             	  				//rssi 信号强度
	_e_machine_model model;             			//设备型号
    uint8_t     hard_version;                       //硬件版本,包含硬件芯片型号和硬件版本号
    uint8_t     software_version;                   //软件版本号
	uint8_t     device_datastruct_index;            //对应设备数据结构索引
	
	
}_t_ble_status;


typedef enum{
    E_BIND_NONE = 0X00,     //未绑定状态
    E_BIND_ING  = 0X01,     //正在绑定
    E_BIND_CMPT = 0X02      //绑定完成
}_e_band_status;



typedef struct{
	_t_ble_status   ble_dev[MAX_LIST_LENGTH];  //设备基本信息
    uint8_t         empty_flag;                //设备连接数标志
	_e_band_status  scan_bind_flag;            //允许扫描标志位
    uint8_t         bing_timeout_cnt;          //绑定超时
}_t_dev_mac_match;





#define  BIND_TIMEOUT_CNT           60      //绑定超时时间

//复位超时时间
#define Reset_Timeout_Cnt do{\
dev_info.scan_bind_flag = 0;\
dev_info.bing_timeout_cnt = BIND_TIMEOUT_CNT;\
}while(0)







extern  _t_dev_mac_match dev_info;    //连接设备的所有信息





bool dev_check_empty(void);
void Device_Info_Reset(_t_ble_status *s_ble_info);
void Debug_Device_match_info(uint16_t  connected_handle);
void Device_Disconnected_handle(uint16_t  connected_handle);
void Debug_Device_match_connected_mac(ble_gap_addr_t mac_peer_addr,uint16_t handle);
void USER_DEBUG_printf(void);
_e_band_status Ret_Device_Bind_status(void);
uint8_t Ret_Device_Bind_Time(void);



#endif

