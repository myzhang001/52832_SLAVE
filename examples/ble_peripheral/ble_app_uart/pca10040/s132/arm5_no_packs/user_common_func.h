#ifndef __USER_COMMON_FUNC_H
#define __USER_COMMON_FUNC_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nordic_common.h"
#include "ble_db_discovery.h"


typedef enum{

	E_TX_N40DB = -40,
	E_TX_N20DB = -20,
	E_TX_N16DB = -16,
	E_TX_N12DB = -12,
	E_TX_N8DB  = -8,
	E_TX_N4DB  = -4,
	E_TX_0DB   = 0,
	E_TX_3DB   = 3,
	E_TX_4DB   = 4
}e_power_level;









#endif


