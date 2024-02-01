#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

//add a hardware timer, we could also use a zephyr timer that is based on the kernel timer facilities.
//NOTE add the timer configuration to prj.conf, now only timer0 and timer1 are added!
//NOTE2: all 5 timers can be used, the zephyr kernel uses RTC1 (https://github.com/zephyrproject-rtos/zephyr/blob/main/drivers/timer/Kconfig.nrf_rtc)
#include <nrfx_timer.h>

//Two timers are configured in prj.conf with TIMER_INST_IDX 0 and 1. 
//In this code only one timer is used, but a second timer can easily be added

/** @brief Symbol specifying timer instance to be used. */
#define TIMER_INST_IDX 1

/** @brief Symbol specifying time in milliseconds to wait for handler execution. */
#define TIME_TO_WAIT_MS 1000UL

/**
 * @brief Function for handling TIMER driver events.
 *
 * @param[in] event_type Timer event.
 * @param[in] p_context  General purpose parameter set during initialization of
 *                       the timer. This parameter can be used to pass
 *                       additional information to the handler function, for
 *                       example, the timer ID.
 */
static void timer_handler(nrf_timer_event_t event_type, void * p_context)
{
    if(event_type == NRF_TIMER_EVENT_COMPARE0)
    {
        char * p_msg = p_context;
        printk("Timer interrupt!\n");        
    }
}

void main(void)
{
	int ret;

	printk("Hello Timer with Interrupts! %s\n", CONFIG_BOARD);
	
    //timer setup
	#if defined(__ZEPHYR__)
    	IRQ_CONNECT(NRFX_IRQ_NUMBER_GET(NRF_TIMER_INST_GET(TIMER_INST_IDX)), IRQ_PRIO_LOWEST,
                NRFX_TIMER_INST_HANDLER_GET(TIMER_INST_IDX), 0, 0);
	#endif
	
	nrfx_timer_t timer_inst = NRFX_TIMER_INSTANCE(TIMER_INST_IDX);
 	uint32_t base_frequency = NRF_TIMER_BASE_FREQUENCY_GET(timer_inst.p_reg);
    nrfx_timer_config_t config = NRFX_TIMER_DEFAULT_CONFIG(base_frequency);
    config.bit_width = NRF_TIMER_BIT_WIDTH_32;
    config.p_context = "My context";

    nrfx_err_t status = nrfx_timer_init(&timer_inst, &config, timer_handler);
    NRFX_ASSERT(status == NRFX_SUCCESS);

    nrfx_timer_clear(&timer_inst);

    /* Creating variable desired_ticks to store the output of nrfx_timer_ms_to_ticks function */
    uint32_t desired_ticks = nrfx_timer_ms_to_ticks(&timer_inst, TIME_TO_WAIT_MS);
    
    /*
     * Setting the timer channel NRF_TIMER_CC_CHANNEL0 in the extended compare mode to stop the timer and
     * trigger an interrupt if internal counter register is equal to desired_ticks.
     */
    nrfx_timer_extended_compare(&timer_inst, NRF_TIMER_CC_CHANNEL0, desired_ticks,
                                NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

    nrfx_timer_enable(&timer_inst);

	while(1)
	{

	}
}