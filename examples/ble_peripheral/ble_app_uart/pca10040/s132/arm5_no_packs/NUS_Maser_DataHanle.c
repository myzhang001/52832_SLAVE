#include "Nus_Master_DataHandle.h"

#include "Protocol_Analysis.h"
#include "Somputon_BLE_DataHandle.h"
#include "ble_gap.h"
#include "ble_srv_common.h"
#include "sdk_common.h"

#include "System_Variable.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


extern uint8_t mac_addr[6];

typedef struct{
	uint8_t  Data_Length;      //保存数据长度
	uint16_t Common_World;     //保存命令字
	uint8_t  Device_Type;      //设备类型
	uint8_t  MacAddr_Device;   //设备mac 地址
}_s_analsis_word;


_s_analsis_word  Common_Word;

somputon_data_recv_t  data_recv;    //数据处理数据结构



//crc8 校验
unsigned char Crc8( unsigned char *Address, unsigned char Length )
{
		static unsigned char crc;
		static unsigned char crcbuff;
		static unsigned char i;
		crc = 0;
	
		while( Length-- )
		{
			crcbuff = *Address ++;
			for(i = 0; i < 8; i++)
			{
				if((crc ^ crcbuff) & 0x01)
				{
					crc ^= 0x18;
					crc >>= 1;
					crc |= 0x80;
				}
				else
				{
					crc >>= 1;
				}
				crcbuff >>= 1;
			}
		}
		return crc;
}



uint16_t turn_to_u16(uint8_t high, uint8_t low)
{
	uint16_t data_all = 0;
	data_all = high;
	data_all = data_all<<8;
	data_all |= low&0x00FF;
	
	return data_all;
}



//获取mac 地址
 void get_mac_addr(uint8_t *p_mac_addr)
{
		uint32_t error_code;
		ble_gap_addr_t p_mac_addr_t ;
		error_code = sd_ble_gap_addr_get(&p_mac_addr_t);
		//APP_ERROR_CHECK(error_code);
		uint8_t *d = p_mac_addr_t.addr;
		for ( uint8_t i = 6; i >0;)
		{	
			i--;
			p_mac_addr[5-i]= d[i];
		}
}



void User_Get_Addr(void)
{
    get_mac_addr(&system_work.device_mac_addr[0]);

    #if 1
    
    for(uint8_t i = 0; i < 6;i++)
    {
        
        printf("0x%02x : ",system_work.device_mac_addr[i]);
		
    }
    #if 0
    mac_addr[0] = system_work.device_mac_addr[5];
    mac_addr[1] = system_work.device_mac_addr[4];
	mac_addr[2] = system_work.device_mac_addr[3];
	#endif
    
    #endif
    

}


static uint8_t s_data_buffer[100];  //存放临时变量

static uint8_t step_status = 0;


//处理串口数据
void nus_data_handle(uint8_t *data, uint8_t length)
{
	
	uint8_t data_buffer[100];       	//接收数据缓冲区大小
	
	memcpy(data_buffer,data,length);
	//memset(data,0,length);
	
	//printf("------------------------------");
	//答应接收的数据
    #if 0     
    for(uint8_t i = 0; i< length;i++)
    {
        printf("\r\nDATA 0x%02x",data_buffer[i]);
    }
    #endif

    

   #if 1
        if((data_buffer[0]== 0x3a)&&(data_recv.receive_start_flag == false))
		{
            //printf("Flag OK!\r\n");
			memcpy(&data_recv.rece_data[data_recv.data_index],data_buffer,length);
			data_recv.data_index += length;			
			data_recv.total_len= turn_to_u16(data_recv.rece_data[1],data_recv.rece_data[2])+3;	
            
            //printf("data_index %d  data_recv.total_len %d",data_recv.data_index,data_recv.total_len);
            
            
			data_recv.receive_start_flag = true;			
		}
		else if((data_recv.rece_data[0] == 0x3a)&&(data_recv.receive_start_flag == true))
		{
			//printf("data_index %d  data_recv.total_len %d",data_recv.data_index,data_recv.total_len);
			if(data_recv.data_index < data_recv.total_len)
			{
               // printf("still recv\r\n");
				memcpy(&data_recv.rece_data[data_recv.data_index],data_buffer,length);
				data_recv.data_index += length; 
			}

		}
		else
		{
				//printf("other data\r\n");
				data_recv.data_index = 0;
				data_recv.receive_start_flag = false;
				data_recv.total_len = 0;
				memset(data_recv.rece_data,0,sizeof(data_recv.rece_data));
		}

		if(data_recv.data_index >= data_recv.total_len)										//receive data end					
		{				
			//for(uint8_t i=0;i<data_recv.data_index;i++)
			//printf("0x%02x ",data_recv.rece_data[i]);
			//printf("\r\n");		
			if( data_recv.rece_data[data_recv.data_index - 1] != Crc8( &data_recv.rece_data[1], data_recv.data_index - 2 ) )
			{
				//printf("APP->BT: crc error\r\n");
				memset(data_recv.rece_data,0,sizeof(data_recv.rece_data));
				data_recv.receive_start_flag = false;
				data_recv.total_len = 0;
				data_recv.data_index = 0;				
				return;
			}
            
            //printf("APP->BT: crc ok\r\n");
            
            Common_Word.Data_Length  = data_recv.rece_data[DATA_LENGTH_INDIX_LOW];    //获取数据包长度
            Common_Word.Data_Length = Common_Word.Data_Length>>8;
            Common_Word.Data_Length |= data_recv.rece_data[DATA_LENGTH_INDIX_HIGH];

            //printf("DATA LENGHT : %d",(uint8_t)Common_Word.Data_Length);

            Common_Word.Common_World = data_recv.rece_data[DATA_COMMOND_WORD];	   //获取命令字
            Common_Word.Common_World = Common_Word.Common_World << 8;
            Common_Word.Common_World |= data_recv.rece_data[DATA_COMMOND_WORD +1 ];        

           //printf("COMMAND WORLD:  0X%04x",Common_Word.Common_World);

            Common_Word.Device_Type = data_recv.rece_data[DATA_DEVICE_TYPE_INDEX];     //获取设备类型
            

            if(receive_data_from_app != NULL)
            {
                receive_data_from_app(Common_Word.Common_World,&data_recv.rece_data[DATA_CONTENT_INDEX],Common_Word.Data_Length - 11); 
            }
			memset(data_recv.rece_data,0,sizeof(data_recv.rece_data));
			data_recv.receive_start_flag = false;
			data_recv.total_len = 0;
			data_recv.data_index = 0;
		}
  
    #endif 
}


