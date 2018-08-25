/*
 *  Read value from xbox one controller
 *  Send wifi message only when value > 0
 *  Define value to 0 when loop start
 *
 *  程式代號: XBtransmitter.h
 *  程式名稱: Obstacle Avoiding Car transmitter
 *  程式功能: Transmitting wifi message via xbox controller
 *  2018.08.26
 */
#include <SPI.h>
#include <RF24.h>
#include <XBOXONE.h>

#define CE_PIN  A2
#define CSN_PIN A1
#define UHS_CSS 10

RF24 rf24(CE_PIN, CSN_PIN);
const uint64_t addr;
USB Usb;
XBOXONE Xbox(&Usb);

void setUHS();
void setWiFi();
int mapAnalogHat(int intVal);
void writeWiFiMsg(long msg);
void setup();
void loop();