#include "Somputon_BLE_DataHandle.h"
#include "System_Variable.h"

#include "NUS_Master_DataHandle.h"
#include "ble_nus.h"

#include "nrf_gpio.h"

#include "led_control.h"


uint8_t SendBuffer[256];
extern uint8_t mac_addr[6];

 
extern void send_data_proc(uint8_t *aSendBuffer,uint16_t len);     //发送函数





/**@brief get_real_time_data_cmd     
 *
 *	Function for replying to get real time data.
 *
 * @param[in]   void  
 *
 * @return      void
 */
void get_real_time_data_cmd(void)
{
	uint8_t aSendBuffer[50];
    
    aSendBuffer[0] = START_FLAG;                                //数据头
    aSendBuffer[1] = 0x00;                                      //数据长度
    aSendBuffer[2] = 13;
    aSendBuffer[3] = PROTOCOL_VERSION;                          //协议版本号
    aSendBuffer[4] = 0x00;                                      //设备类型 
    memcpy(&aSendBuffer[5],&system_work.device_mac_addr,6);     //获取mac 地址

    aSendBuffer[11] =  (uint8_t)(GET_REAL_TIME_DATA_COMMAND_REPLY>>8);   //命令控制字
    aSendBuffer[12] =  (uint8_t)GET_REAL_TIME_DATA_COMMAND_REPLY;        //命令控制字
    aSendBuffer[13] =  0x12;                                       //数据
    aSendBuffer[14] =  0x01;    
    aSendBuffer[15] = Crc8(&aSendBuffer[1],14);                    //crc 校验

    send_data_proc(aSendBuffer,16);                               //发送数据
}


uint8_t send_buff[50];

/**@brief clear_history_data_cmd     
 *
 *	Function for replying to the clear history data command from the APP and wouldn't contain any data.
 *
 * @param[in]   void   Point to the time struct data.
 *
 * @return      void
 */
void bond_cmd(void)
{
    uint8_t aSendBuffer[256];

    
    send_buff[0] = START_FLAG;                                //数据头
    send_buff[1] = 0x00;                                      //数据长度
    send_buff[2] = 11;
    send_buff[3] = PROTOCOL_VERSION;                          //协议版本号
    send_buff[4] = 0x00;                                      //设备类型 
    memcpy(&send_buff[5],&system_work.device_mac_addr[0],6);  //获取mac 地址
	
	
	
    send_buff[11] =  (uint8_t)(BOND_COMMAND_REPLY>>8);         //命令控制字
    send_buff[12] =  (uint8_t)BOND_COMMAND_REPLY;              //命令控制字

    send_buff[13] = Crc8(&send_buff[1],12);               //crc 校验

    send_data_proc(send_buff, 14);                       //发送数据
}

/**@brief clear_history_data_cmd     
 *
 *	Function for replying to the clear history data command from the APP and wouldn't contain any data.
 *
 * @param[in]   void   Point to the time struct data.
 *
 * @return      void
 */

void clear_history_data_cmd(void)
{


}


/**@brief set_device_time_cmd     
 *
 *	Function for setting time.
 *
 * @param[in]   data_info   Point to the time struct data.
 *
 * @return      void
 */
void set_device_time_cmd(uint8_t *data_info)
{



}


/**@brief get_device_time_cmd     
 *
 *	Function for getting time.
 *
 * @param[in]   second   use second to stand for the current time.
 *
 * @return      void
 */
void get_device_time_cmd(uint32_t second)
{


}


/**@brief control_device_cmd     
 *
 *	Function for dealing with control command.
 *
 * @param[in]   ctrl_data   clife control word data
 *
 * @return      void
 */
void control_device_cmd(uint8_t *ctrl_data,uint8_t length)
{
    if( ctrl_data[10] == 0x20)
    {
        if(ctrl_data[5] == 0x01)
        {
           door_on();
           // nrf_gpio_pin_clear(18);
        }
        else if( ctrl_data[5] == 0x00)
        {
           door_off();
           // nrf_gpio_pin_set(18);
        }
    }
    if(ctrl_data[10] == 0x01)  //大厅灯
    {
        if(ctrl_data[0] == 0x01)
        {
           halllight_on();
           
        }
        else if( ctrl_data[0] == 0x00)
        {
           hallight_off();
        }
    }
    if(ctrl_data[10] == 0x02)
    {
         if(ctrl_data[1] == 0x01)
        {
           bedroomlight_on();
           
        }
        else if( ctrl_data[1] == 0x00)
        {
           bedroomlight_off();
        }

    }
     if(ctrl_data[10] == 0x04)
    {
        if(ctrl_data[2] == 0x01)
        {
           GardenLight_on();
           
        }
        else if( ctrl_data[2] == 0x00)
        {
           GardenLight_off();
        }
    
    }
     if(ctrl_data[10] == 0x08)
    {
          if(ctrl_data[3] == 0x02)  //停
        {
           //curtain_on();
            nrf_gpio_pin_clear(26);
            nrf_gpio_pin_clear(27);
           
        }
         
         if(ctrl_data[3] == 0x01) //开
        {
           //curtain_on();
            nrf_gpio_pin_clear(26);
            nrf_gpio_pin_set(27);
        }
        else if( ctrl_data[3] == 0x00)  //关
        {
           //curtain_off();
            nrf_gpio_pin_set(26);
            nrf_gpio_pin_clear(27);
        }
    
    }
    if(ctrl_data[10] == 0x10)
    {
         if(ctrl_data[4] == 0x01)
        {
            #if 1
            nrf_gpio_pin_set(14);  //开   车库门

            nrf_gpio_pin_clear(15);
            #endif 
        }
        else if( ctrl_data[4] == 0x00)
        {
            #if 1
            nrf_gpio_pin_clear(14);  //关 车库门
            nrf_gpio_pin_set(15);
            #endif
        }
    
    }
    else if(ctrl_data[10] == 0x40)
    {
        if(ctrl_data[6] == 0x01)
        {
            clothes_shores_on();
        }
        else if( ctrl_data[6] == 0x00)
        {
           
            clothes_shores_off();
        }
    
    }
    
    else if(ctrl_data[10] == 0x80)
    {
        if(ctrl_data[7] == 0x01)
        {
            hourseholdlight_on();
        }
        else if( ctrl_data[7] == 0x00)
        {
           
            hourseholdlight_off();
        }
    
    }
   
    else if(ctrl_data[11] == 0x01)
    {
        if(ctrl_data[8] == 0x01)
        {
            #if 1
            nrf_gpio_pin_clear(16);  //开 筒灯
            nrf_gpio_pin_set(17);

            #endif
           
        }
        else if( ctrl_data[8] == 0x00)
        {
           
            #if 1
            nrf_gpio_pin_set(16);      //关  筒灯
            nrf_gpio_pin_clear(17);
            #endif
        }
    
    }
    else if(ctrl_data[11] == 0x02)
    {
        if(ctrl_data[9] == 0x01)
        {
           studyroom_on();
        }
        else if( ctrl_data[9] == 0x00)
        {
           studyroom_off();
        }
    }
}


/**@brief Clife_GetHisData     
 *
 *	Function for dealing with the process of getting history data command.
 *
 * @param[in]   cmd   clife command word 
 * @param[in]   data  clife command word data
 * @param[in]   len   data length
 *
 * @return      void
 */
void Clife_GetHisData(uint16_t cmd, uint8_t* data, uint16_t len)
{
	
	
}


/**@brief Clife_GenerateHisData     
 *
 *	Function for Generating history data to write to the flash.
 *
 * @param[in]   void
 *
 * @return      void
 */
void Clife_GenerateHisData(void)
{



}



//设备连接上后主动发起绑定请求认证

void AuthInfo_Request(void)
{
    
  
    
}




