#define ARDUINO_ARCH_AVR

#define LED_PIN PIN_LED

#undef USE_SX1262
#define USE_RF95

#undef LORA_SCK
#undef LORA_MISO
#undef LORA_MOSI
#undef LORA_CS

#define LORA_SCK 10
#define LORA_MISO 12
#define LORA_MOSI 11
#define LORA_CS 3

#define LORA_DIO0 2
#define LORA_RESET 15
#define LORA_DIO1 20
#define LORA_DIO2 RADIOLIB_NC
#define LORA_DIO3 RADIOLIB_NC

#define HAS_GPS 1
#define GPS_RX_PIN 9
#define GPS_TX_PIN 8
#define PIN_GPS_EN 2
#define GPS_EN_ACTIVE LOW

#define GPS_EXTRAVERBOSE 1
#define GPS_DEBUG 1