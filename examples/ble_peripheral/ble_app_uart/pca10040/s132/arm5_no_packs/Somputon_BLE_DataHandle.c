#include "Somputon_BLE_DataHandle.h"
#include "System_Variable.h"

#include "NUS_Master_DataHandle.h"
#include "ble_nus.h"





uint8_t SendBuffer[256];





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
	
}


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
	//dev_info.ble_dev[conn_handle - 1].device_datastruct_index
	
	
	
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
void control_device_cmd(uint8_t *ctrl_data)
{




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
    
    SendBuffer[0] = START_FLAG;                                //数据头
    SendBuffer[1] = 0x00;                                      //数据长度
    SendBuffer[2] = 10;
    SendBuffer[3] = PROTOCOL_VERSION;                          //协议版本号
    
    memcpy(&SendBuffer[4],&system_work.device_mac_addr,6);     //获取mac 地址
    
    
    SendBuffer[8] =  (uint8_t)(BOND_COMMAND_REPLY>>8);         //命令控制字
    SendBuffer[9] =  (uint8_t)BOND_COMMAND_REPLY;              //命令控制字
    
    SendBuffer[10] = Crc8(&SendBuffer[1],10 - 1);               //crc 校验
 
     //ble_nus_string_send(&m_nus, SendBuffer, 10);
    
}




