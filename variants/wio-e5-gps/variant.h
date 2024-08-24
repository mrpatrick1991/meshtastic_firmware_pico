/*
Wio-E5 mini (formerly LoRa-E5 mini)
https://www.seeedstudio.com/LoRa-E5-mini-STM32WLE5JC-p-4869.html
https://www.seeedstudio.com/LoRa-E5-Wireless-Module-p-4745.html
*/

/*
This variant is a work in progress.
Do not expect a working Meshtastic device with this target.
This variant has GPS enabled and expects PA2 / PA3 as the GPS serial pins.
*/

#ifndef _VARIANT_WIOE5_
#define _VARIANT_WIOE5_

#define USE_STM32WLx
#define MAX_NUM_NODES 10

#define LED_PIN PB5
#define LED_STATE_ON 1

#define HAS_GPS 1
#define GPS_RX_PIN PA3
#define GPS_TX_PIN PA2

#endif
