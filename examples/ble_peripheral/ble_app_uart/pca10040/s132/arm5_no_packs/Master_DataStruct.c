#include "Master_DataStruct.h"



_datastruct_08F   System_08F;        //08F  系统变量



	

//清零数据   device_index 0 - 7

void Master_ResetBuffer_08F_RealStatus(uint8_t device_index)
{
	//memset(&Device_08F_Array[device_index],0,sizeof(_real_staus_08F));
}


//清零所有数据   all
void Master_ResetBuffer_08F_RealStatus_All(void)
{
	//memset(&Device_08F_Array,0,sizeof(_real_staus_08F)*8);
}



//检查mac 地址合法性

uint8_t  Check_Mac(uint8_t mac_addr[6])
{
	
	uint8_t ret;
	
	
	if(mac_addr[0]==0 &&mac_addr[1]==0 &&
		mac_addr[2]==0 &&mac_addr[3]==0 &&
		mac_addr[4]==0 &&mac_addr[5]==0 )
	{
		ret =  0;
	
	}
	else
	{
		ret = 1;
	}
	
	
	if(mac_addr[0]==0xff &&mac_addr[1]==0xff &&
		mac_addr[2]==0xff &&mac_addr[3]==0xff &&
		mac_addr[4]==0xff &&mac_addr[5]==0xff )
	{
		ret =  0;
	
	}
	else
	{
		ret = 1;
	}
	return ret;
}

//ret: 0  非法输入的地址


uint8_t Mac_Compare(uint8_t src_mac[6],uint8_t dst_mac[6])
{
	
	uint8_t i = 0;
	
	
	if(Check_Mac(src_mac) == 0)
	{
		return 0;
	}
	if(Check_Mac(dst_mac) == 0)
	{
		return 0;
	}
	
	for(i = 0; i < 8;i++)
	{
		if(src_mac[i]!=dst_mac[i])
		{
			break;
		}
	}
	
	//if(  )
	return 0;

}




//检查数据是否可用
uint8_t Empty_Mac_List(_mac_index_fix addr_mac)
{
	uint8_t  ret;
	
	if( addr_mac.index == 0 &&  addr_mac.mac_addr[0]== 0x00 &&
		addr_mac.mac_addr[1]== 0x00 &&addr_mac.mac_addr[2]== 0x00 &&
		addr_mac.mac_addr[3]== 0x00 &&addr_mac.mac_addr[4]== 0x00 &&
		addr_mac.mac_addr[5]== 0x00 )
	{
	
		ret =1 ;
	
	}
	else
	{
		ret = 0;
	}

	return ret;
}



void BubbleSort1(uint8_t *arr,int sz){
    int i = 0;
    int j = 0;
   
    for(i=0;i<sz-1;i++){
        for(j=0;j<sz-i-1;j++){
            if(arr[j]>arr[j+1]){
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}



void  Index_Sort_Push(_mac_index_data *device_list, uint8_t index)
{
	
	if(device_list == NULL)
	{
		return;
	}

	
	device_list->index_sort[device_list->device_num] =  index;   //添加
	
	//添加后排序
	
	BubbleSort1(device_list->index_sort,device_list->device_num);
	
	device_list->max_index_decice = device_list->index_sort[device_list->device_num];
	
}




void Index_Sort_POP(_mac_index_data *device_list ,uint8_t index)
{
	
	uint8_t i = 0;
	
	
	if( device_list == NULL)
	{
		return ;
	}
	
	for(i = 0; i < device_list->device_num;i++)
	{
		if(device_list->index_sort[i]== index )
        {
            break;
        }
	}
	
	if(i < device_list->device_num)
    {
        device_list->index_sort[i] = device_list->device_num;
    }

    //删除后排序
	
	BubbleSort1(device_list->index_sort,device_list->device_num);
    
}






//往列表里面增加设备

uint8_t Add_Device_List(_mac_index_data *device_list,uint8_t mac_addr[6])
{
	
	
	uint8_t ret;
	uint8_t i;
	
	if(device_list == NULL)
	{
		return ret = 0;
	}

	_mac_index_data *s_device_list = device_list;
	
	
	if(s_device_list->device_num == 0)   //设备列表为空
	{
		s_device_list->mac_list_array[0].index  = 0;
		memcpy(&s_device_list->mac_list_array[0].mac_addr,&mac_addr[0],6);         //拷贝mac地址和索引
	}
	else
	{
		//设备列表不为空,检查mac 地址是否相同，相同返回错误，不同继续添加
		
		for(i = 0; i< s_device_list->max_index_decice + 2;i++)
		{
			if(memcmp(&s_device_list->mac_list_array[i].mac_addr,&mac_addr[0],6) == 0)  //设备已经添加
			{
				ret = 0;
			}
			else                                              							//设备未添加
			{
				if(s_device_list->device_num >= 8 )return 0;
				
				
				if(Empty_Mac_List(s_device_list->mac_list_array[i]) == 1)               	//给数据结构为可用
				{
					s_device_list->device_num += 1;											//索引加1
					
					s_device_list->mac_list_array[s_device_list->device_num].index  = i;                           
					
					memcpy(&s_device_list->mac_list_array[i].mac_addr,&mac_addr[0],6);
					
																							//更新最大索引
					if(  i > s_device_list->max_index_decice)
					{
						s_device_list->max_index_decice = i;
					}

                    Index_Sort_Push(s_device_list,i);                                       //更新所以列表   
                    
                    
				}
			}
			
		}
	}
	return 0;
}


//删除设备
uint8_t Del_Device_List(_mac_index_data *device_list,uint8_t mac_addr[6])
{
	uint8_t ret;
	uint8_t i;
	
	
	
	if(device_list == NULL)
	{
		return ret = 0;
	}
	
	_mac_index_data *s_device_list = device_list;
	
	if(s_device_list->device_num == 0)   //设备列表为空
	{
		return 0;
	}
	else
	{
		for(i = 0;  i < s_device_list->max_index_decice + 1 ;i++)
		{
			if(memcmp(&s_device_list->mac_list_array[i].mac_addr,&mac_addr[0],6) != 0)
			{
				return 0;
			}
			else																	//找到相同的设备
			{
				memset(&s_device_list->mac_list_array[i],0,sizeof(_mac_index_fix)); //清除设备
				
				break;
			
			}
		}
        
        Index_Sort_POP(s_device_list,i);                                            //更新索引列表
        
        
	}
	return 0;
}





