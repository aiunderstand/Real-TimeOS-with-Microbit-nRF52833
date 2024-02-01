#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "matrix.h"

int main(void)
{
	int ret;
	ret = matrix_begin();
	if (ret < 0)
	{
		printk("\nError initializing LED matrix.  Error code = %d\n",ret);	
		while(1);
	}

	while(1)
	{       
		matrix_put_pattern(4, 27);	
	    printk("LED 3,3 is ON!\n\r");		
		k_msleep(500);
		matrix_all_off();
		printk("LED 3,3 is OFF!\n\r");		
		k_msleep(500);
	}
}

//some useful patterns that don't need a 5 cycle framebuffer

//for column a 0 is mask for enable and 1 is disable
//for row a 1 is a mask for enable and 0 is disable

//matrix_put_pattern(4, 27);	//center led

//matrix_put_pattern(31, 0);	//all led on
//matrix_put_pattern(0, 31);	//all led off

//matrix_put_pattern(7, 27);	//first three center column pixels 
//matrix_put_pattern(31, 27);	//all center column pixels
//matrix_put_pattern(31, 4);	//inverse of all center column pixels

//matrix_put_pattern(7, 0);		//first three rows pixels
//matrix_put_pattern(4, 0);		//all center row pixels
//matrix_put_pattern(27, 0);	//inverse of center row pixels
		
//matrix_put_pattern(27, 4);	//inverse of center plus