#define ARDUINO_ARCH_AVR

// Build with slow system clock enabled to reduce power consumption.

// Expecting the Waveshare Pico GPS hat
#undef MESHTASTIC_EXCLUDE_GPS
#define DEBUG 1
#define HAS_GPS 1
#define GPS_DEBUG 1
#define GPS_BAUDRATE 9600
#define GPS_EXTRAVERBOSE 1
#define GPS_RX_PIN 1
#define GPS_TX_PIN 0

#define LED_PIN PIN_LED

#undef USE_SX1262
#undef LORA_SCK
#undef LORA_MISO
#undef LORA_MOSI
#undef LORA_CS
#undef LORA_DIO0
#undef LORA_DIO1
#undef LORA_DIO2
#undef LORA_DIO3

#define USE_RF95

#define LORA_SCK 10
#define LORA_MISO 12
#define LORA_MOSI 11
#define LORA_CS 13

#define LORA_RESET 14
#define LORA_DIO1 15
#define LORA_DIO0 16
#define LORA_DIO2 RADIOLIB_NC
#define LORA_DIO3 RADIOLIB_NC