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
		//col 1 
		matrix_put_pattern(8, 30);
		k_msleep(1);
		
		//col 2
		matrix_put_pattern(19, 29);
		k_msleep(1);

		//col 3
		matrix_put_pattern(16, 27);	
		k_msleep(1);

		//col 4
		matrix_put_pattern(19, 23);
		k_msleep(1);

		//col 5
		matrix_put_pattern(8, 15);
		k_msleep(1);
	}
}