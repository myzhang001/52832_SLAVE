#include "Protocol_Analysis.h"
#include "Somputon_BLE_DataHandle.h"




appRecvHandler_Cb  receive_data_from_app;   //数据接收回调



void regRevAppDataCb(appRecvHandler_Cb cb)
{
		receive_data_from_app = cb;
}



/**@brief Somputon_Init
 * Register a Somputon command word callback function for application
 
 * @param[in] cb Function will be called when data have been received complete from BLE.
 */
void Somputon_Init(appRecvHandler_Cb cb)
{
	regRevAppDataCb(cb);	
}



uint8_t bond_ack =0;




/**@brief     Function for handling clife command word in the application
 *
 * @param[in] command 			clife command word
 *         	  src_data    	    source data
 *         	  len 			    data length
 *
 * @return    void
 */
void App_RecvHandler(uint16_t command, uint8_t* pdata,uint16_t len)
{
		switch(command)
		{			
			case ENCRYPTION_REQ_REPLY:
					control_device_cmd(NULL);			      												
					break;
			case CLEAR_HISTORY_DATA_COMMAND:
					 clear_history_data_cmd();                //清除历史数据
					 break;			
			
			case GET_REAL_TIME_DATA_COMMAND:					 
					 get_real_time_data_cmd();	              //获取实时时间
					 break;		
			
			case BOND_COMMAND:
				
					//bond_ack = 1;
					bond_cmd();                                //发送绑定指令
                    
					//printf("------------bond_cmd------------");	
          
					 break;		
												
			case GET_HISTORY_DATA_TOTAL_PACKETS:
			case GET_HISTORY_DATA_COMMAND:
			case HISTORY_DATA_REPLY_FROM_APP:	
					 //Clife_GetHisData(command,data,len);
					 break;
			
			case SET_DEVICE_TIME_COMMAND:			
					 //set_device_time_cmd(data);				//  先同步APP的时间					 
					 break;		
			
			case GET_DEVICE_TIME_COMMAND:						 
					  get_device_time_cmd(1);			    //  上传时间
					 break;
			

			case CONTROL_DATA_COMMAND:
					 //control_device_cmd(data);				//处理控制数据	   	
					break;			
															
			default:				
					break;
		}		
			
}





