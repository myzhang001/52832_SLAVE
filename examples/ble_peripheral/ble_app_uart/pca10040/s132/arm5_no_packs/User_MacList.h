#ifndef __maclist_h
#define __maclist_h

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nordic_common.h"


#define  MAX_LIST_LENGTH  8      //�б�������
#define  MAC_ADDR_LENGTH  6      //MAC ��ַ����

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



//�����豸��Ϣ
typedef struct{
	uint8_t 	mac_addr[MAC_ADDR_LENGTH];        	//�豸mac ��ַ
	uint16_t 	conn_handle;       					//���Ӿ��
	uint8_t 	connected_flag;   					//����״̬
	int8_t     	rssi;             	  				//rssi �ź�ǿ��
	_e_machine_model model;             			//�豸�ͺ�
    uint8_t     hard_version;                       //Ӳ���汾,����Ӳ��оƬ�ͺź�Ӳ���汾��
    uint8_t     software_version;                   //�����汾��
	uint8_t     device_datastruct_index;            //��Ӧ�豸���ݽṹ����
	
	
}_t_ble_status;


typedef enum{
    E_BIND_NONE = 0X00,     //δ��״̬
    E_BIND_ING  = 0X01,     //���ڰ�
    E_BIND_CMPT = 0X02      //�����
}_e_band_status;



typedef struct{
	_t_ble_status   ble_dev[MAX_LIST_LENGTH];  //�豸������Ϣ
    uint8_t         empty_flag;                //�豸��������־
	_e_band_status  scan_bind_flag;            //����ɨ���־λ
    uint8_t         bing_timeout_cnt;          //�󶨳�ʱ
}_t_dev_mac_match;





#define  BIND_TIMEOUT_CNT           60      //�󶨳�ʱʱ��

//��λ��ʱʱ��
#define Reset_Timeout_Cnt do{\
dev_info.scan_bind_flag = 0;\
dev_info.bing_timeout_cnt = BIND_TIMEOUT_CNT;\
}while(0)







extern  _t_dev_mac_match dev_info;    //�����豸��������Ϣ





bool dev_check_empty(void);
void Device_Info_Reset(_t_ble_status *s_ble_info);
void Debug_Device_match_info(uint16_t  connected_handle);
void Device_Disconnected_handle(uint16_t  connected_handle);
void Debug_Device_match_connected_mac(ble_gap_addr_t mac_peer_addr,uint16_t handle);
void USER_DEBUG_printf(void);
_e_band_status Ret_Device_Bind_status(void);
uint8_t Ret_Device_Bind_Time(void);



#endif
