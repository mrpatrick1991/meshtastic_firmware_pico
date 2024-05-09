#define ARDUINO_ARCH_AVR

// Build with slow system clock enabled to reduce power consumption.
#define RP2040_SLOW_CLOCK

#ifdef RP2040_SLOW_CLOCK
// Redefine UART1 serial log output to avoid collision with UART0 for GPS.
#define SERIAL2_TX -1
#define SERIAL2_RX -1
// Reroute log output in SensorLib when USB is not available
#define log_e(...) Serial2.printf(__VA_ARGS__)
#define log_i(...) Serial2.printf(__VA_ARGS__)
#define log_d(...) Serial2.printf(__VA_ARGS__)
#endif

// Traquito board has a GPS
#define HAS_GPS 1

// Disable OLED Screen
#define HAS_SCREEN 0
#define USE_SH1106 0
#define RESET_OLED -1

// Redefine I2C0 pins to avoid collision with UART1/Serial2.
#define I2C_SDA -1
#define I2C_SCL -1

// Redefine Waveshare UPS-A/B I2C_1 pins:
#define I2C_SDA1 -1
#define I2C_SCL1 -1

// no INA219
#undef INA219_MULTIPLIER 

// Traquito ATGM 336H GPS 
#define GPS_RX_PIN 9
#define GPS_TX_PIN 8

// Wakeup from backup mode
// #define PIN_GPS_FORCE_ON 14
// No GPS reset available
#undef PIN_GPS_RESET
#undef PIN_GPS_PPS // no PPS

// Traquito GPS reset must be turned high impedence to enable GPS
#define PIN_GPS_STANDBY 6

#define LED_PIN PIN_LED

#undef USE_SX1262 // RFM98 module is SX127x

#undef LORA_SCK
#undef LORA_MISO
#undef LORA_MOSI
#undef LORA_CS

#define LORA_SCK 10
#define LORA_MISO 12
#define LORA_MOSI 11
#define LORA_CS 3

#define LORA_DIO0 RADIOLIB_NC
#define LORA_RESET 15
#define LORA_DIO1 20
#define LORA_DIO2 2
#define LORA_DIO3 RADIOLIB_NC

#ifdef USE_SX1262
#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY LORA_DIO2
#define SX126X_RESET LORA_RESET
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#endif