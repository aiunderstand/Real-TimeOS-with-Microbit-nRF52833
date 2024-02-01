A FreeRTOS example for the chipset (nRF52833) of the micro:bit v2 can be found in the old SDK of Nordic. Since Nordic has switched focus from MBED (and FreeRTOS) to ZephyrRTOS these examples are becoming lost to awareness.

The following example shows how to set up the FreeRTOS with the chipset but has no specific drivers for the various devices. Since most drivers are written in C, adding these for FreeRTOS should be relatively straightforward.

Link to nRF5_SDK (version I used for testing was nRF5_SDK_17.1.0_ddde560) 
https://www.nordicsemi.com/Products/Development-software/nrf5-sdk

The example can be found in the folder Examples\peripheral\blinky_rtc_freertos. Several other examples can also be found in the folder. The manual mentioning the FreeRTOS example and explaining the code can be found here:

https://infocenter.nordicsemi.com/topic/sdk_nrf5_v17.1.0/nrf_rtc_freertos_example.html and 
https://infocenter.nordicsemi.com/topic/sdk_nrf5_v17.1.0/nrf_freertos_example.html
