/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

#define BEEP_DURATION  K_MSEC(60)
#define PERIOD_MIN     PWM_USEC(50)
#define PERIOD_MAX     PWM_USEC(3900)

static const struct pwm_dt_spec speaker = PWM_DT_SPEC_GET(DT_PATH(zephyr_user));
int period;

static void beep(int p)
{
	/* The "period / 2" pulse duration gives 50% duty cycle, which
	 * should result in the maximum sound volume.
	 */
	pwm_set_dt(&speaker, p, p / 2U);
	k_sleep(BEEP_DURATION);

	/* Disable the PWM */
	pwm_set_pulse_dt(&speaker, 0);

	/* Ensure there's a clear silent period between two tones */
	k_sleep(K_MSEC(50));
}


int main(void)
{
	period = speaker.period;
	while(1)
	{       
		//note that sound is timing sensitive and should thus not be preempted when playing and have a high priority.
		beep(period);

		//increase frequency by increasing the period (check if within bounds)
		if 	(period < PERIOD_MAX)
			period += PWM_USEC(50);
		else
			period = PERIOD_MIN;

		k_msleep(500);
	}
	return 0;
}