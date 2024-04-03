#ifndef CC1120_SPI_H_
#define CC1120_SPI_H_

#include "stm32f4xx_hal.h"

// CC1120 Register Addresses
#define CC1120_REG_IOCFG2 0x00
#define CC1120_REG_IOCFG1 0x01
#define CC1120_REG_IOCFG0 0x02
#define CC1120_REG_SYNC3 0x03
#define CC1120_REG_SYNC2 0x04
#define CC1120_REG_SYNC1 0x05
#define CC1120_REG_SYNC0 0x06
#define CC1120_REG_SYNC_CFG1 0x07
#define CC1120_REG_SYNC_CFG0 0x08
#define CC1120_REG_DEVIATION_M 0x09
#define CC1120_REG_MODCFG_DEV 0x0A
#define CC1120_REG_DCFILT_CFG 0x0B
#define CC1120_REG_PREAMBLE_CFG1 0x0C
#define CC1120_REG_PREAMBLE_CFG0 0x0D
#define CC1120_REG_IQIC 0x0E
#define CC1120_REG_CHAN_BW 0x0F
#define CC1120_REG_MDMCFG1 0x10
#define CC1120_REG_MDMCFG0 0x11
#define CC1120_REG_SYMBOL_RATE2 0x12
#define CC1120_REG_SYMBOL_RATE1 0x13
#define CC1120_REG_SYMBOL_RATE0 0x14
#define CC1120_REG_AGC_REF 0x15
#define CC1120_REG_AGC_CS_THR 0x16
#define CC1120_REG_AGC_GAIN_ADJUST 0x17
#define CC1120_REG_AGC_CFG3 0x18
#define CC1120_REG_AGC_CFG2 0x19
#define CC1120_REG_AGC_CFG1 0x1A
#define CC1120_REG_AGC_CFG0 0x1B
#define CC1120_REG_FIFO_CFG 0x1C
#define CC1120_REG_DEV_ADDR 0x1D
#define CC1120_REG_SETTLING_CFG 0x1E
#define CC1120_REG_FS_CFG 0x1F
#define CC1120_REG_WOR_CFG1 0x20
#define CC1120_REG_WOR_CFG0 0x21
#define CC1120_REG_WOR_EVENT0_MSB 0x22
#define CC1120_REG_WOR_EVENT0_LSB 0x23
#define CC1120_REG_RXDCM_TIME 0x24
#define CC1120_REG_PKT_CFG2 0x25
#define CC1120_REG_PKT_CFG1 0x26
#define CC1120_REG_PKT_CFG0 0x27
#define CC1120_REG_RFEND_CFG1 0x29
#define CC1120_REG_RFEND_CFG0 0x2A
#define CC1120_REG_PA_CFG2 0x2B
#define CC1120_REG_PA_CFG1 0x2C
#define CC1120_REG_PA_CFG0 0x2D
#define CC1120_REG_PKT_LEN 0x2E
#define CC1120_REG_IF_MIX_CFG 0x2F
#define CC1120_REG_FREQOFF_CFG 0x30
#define CC1120_REG_TOC_CFG 0x31
#define CC1120_REG_MARC_SPARE 0x32
#define CC1120_REG_ECG_CFG 0x33
#define CC1120_REG_CFM_DATA_CFG 0x34
#define CC1120_REG_EXT_CTRL 0x35
#define CC1120_REG_RCCAL_CFG 0x36

// Set SPI Handler
void SPI_Init(void);

// CC1120 SPI Functions
void CC1120_Init(void);
void CC1120_Reset(void);

void CC1120_SetFrequency(uint32_t freq);
void CC1120_SetOutputPower(int8_t power);
void CC1120_SetSyncWord(uint32_t syncWord);
void CC1120_SetDataRate(uint32_t dataRate);
void CC1120_SetDeviation(uint32_t deviation);
void CC1120_SetupDataPacket(uint8_t packetLength, uint8_t preambleLength, uint8_t syncWordLength, uint8_t crcConfig);

// CC1120 SPI Read/Write Functions
void CC1120_WriteRegister(uint8_t regAddr, uint8_t data);
uint8_t CC1120_ReadRegister(uint8_t regAddr);

#endif /* CC1120_SPI_H_ */
