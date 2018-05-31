#ifndef __MASTER_DATASTRUCT_H
#define __MASTER_DATASTRUCT_H


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nordic_common.h"





#define MAX_DEVICE_NUM  8							//��������豸����



//08F ���ݽṹ

//08F �����������ݽṹ

typedef enum{
    E_MOTOR_OFF 	= 0X00,
	E_MOTOR_LOW 	= 0X01,
	E_MOTOR_MIDDLE  = 0X02,
	E_MOTOR_HIGH    = 0X03
}_e_08f_motor;


//�豸״̬����
typedef struct{
	uint8_t 		Device_08F_POWER;       //���ػ�
	_e_08f_motor    Motor_Level;            //�����λ
	uint32_t        PM2_5_Value;            //pm2.5 �ȼ�
	uint8_t         Anion;                  //������Ũ��
	uint8_t         Filter;                 //����
}_real_staus_08F;



//�豸��������

typedef struct{
	uint8_t 		Device_08F_POWER;       //���ػ�
	_e_08f_motor    Motor_Level;            //�����λ

}_control_08F;




//�·����ݽṹ
typedef struct{
	uint8_t      Device_09_Power;          //���ػ�
	uint8_t      Motor_Level;              //���ﵵλ	
}_contorl_09;


typedef struct{
	uint8_t      Device_09_Power;          //���ػ�
	uint8_t      Motor_Level;              //���ﵵλ
	uint8_t      Work_Time;                //�豸����ʱ��
}_real_status_09;





//mac ��ַ �� Array ����ƥ��
typedef struct{

	uint8_t mac_addr[6];             //����mac ��ַ
	uint8_t index;                   //����
	
}_mac_index_fix;



typedef struct{
	uint8_t         device_num; 					  //�豸����
	uint8_t         max_index_decice;                 //�������
	uint8_t         index_sort[MAX_DEVICE_NUM];       //�����������
	_mac_index_fix  mac_list_array[MAX_DEVICE_NUM];   //�豸mac list ��index �б�
}_mac_index_data;



typedef struct{
	uint8_t         Device_Num;                     			//���豸����
	_real_staus_08F Device_08F_Array[MAX_DEVICE_NUM];    		//08 ʵʱ����
	_control_08F 	Device_Control_08F_Array[MAX_DEVICE_NUM];   //08 ��������

	_mac_index_data mac_index; 									//mac list index				

}_datastruct_08F;



typedef struct{
	uint8_t         Device_Num;                     			//���豸����
	_real_status_09 Device_09_Array[MAX_DEVICE_NUM];			//09 ʵʱ����
	_contorl_09    	Device_Control_09_Array[MAX_DEVICE_NUM];	//09 ��������
}_datastruct_09;





uint8_t Del_Device_List(_mac_index_data *device_list,uint8_t mac_addr[6]);
uint8_t Add_Device_List(_mac_index_data *device_list,uint8_t mac_addr[6]);




extern _datastruct_08F   System_08F;        //08F  ϵͳ����



#endif


