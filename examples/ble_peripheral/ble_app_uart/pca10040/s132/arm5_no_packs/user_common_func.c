
#include "sdk_config.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "user_common_func.h"



//修改发射功率,协议栈初始化后调用
void User_Change_Tx_Power(e_power_level tx)
{
	uint32_t err_code;
	
	err_code = sd_ble_gap_tx_power_set(tx);
	
    APP_ERROR_CHECK(err_code);
}


//获取主机mac 地址







