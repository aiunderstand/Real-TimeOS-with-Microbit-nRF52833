/*
 * SPDX-License-Identifier: Apache-2.0
*/

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>	
#include "lsm303_ll.h"

int main(void)
{
	int ret;
	ret = lsm303_ll_begin();        
	if (ret < 0)
	{
		printk("\nError initializing lsm303.  Error code = %d\n",ret);	
		while(1);
	}
	while(1)
	{    
         struct All_Axes_Data data = lsm303_ll_readAccel();
         printk("Accel X (x100) = %d\n", data.X);   
         printk("Accel Y (x100) = %d\n", data.Y);        
         printk("Accel Z (x100) = %d\n", data.Z);    
         printk("\n");    
         k_msleep(500);

	}
}