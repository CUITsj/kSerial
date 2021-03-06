/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    kSerial.h
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __KSERIAL_H
#define __KSERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include <stdint.h>
#include "kStatus.h"
#ifndef KSERIAL_RECONFIG
#include "kSerial_Conf.h"
#else
#include "kSerial_ReConf.h"
#endif

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/

typedef struct
{
    uint8_t param[2];
    uint32_t type;
    uint32_t lens;
    uint32_t nbyte;
    void *data;

} kserial_packet_t;

typedef struct
{
    uint32_t size;
    uint32_t count;
    uint8_t *buffer;

    uint32_t pkcnt;
    kserial_packet_t *packet;

} kserial_t;

typedef struct
{
    uint32_t type;
    uint32_t nbyte;
    uint8_t param[2];
    uint8_t data[8];

} kserial_ack_t;

typedef enum
{
    KSCMD_R0_NULL               = 0x00,
    KSCMD_R0_DEVICE_ID          = 0xD0,
    KSCMD_R0_DEVICE_BAUDRATE    = 0xD1,
    KSCMD_R0_DEVICE_RATE        = 0xD2,
    KSCMD_R0_DEVICE_MDOE        = 0xD3,
    KSCMD_R0_DEVICE_GET         = 0xE3

} kserial_r0_command_t;

typedef enum
{
    KSCMD_R2_TWI_SCAN_DEVICE    = 0xA1,
    KSCMD_R2_TWI_SCAN_REGISTER  = 0xA2

} kserial_r2_command_t;

typedef void (*pKserialCallback)( kserial_packet_t *pk, uint8_t *data, uint32_t count, uint32_t total );

/* Extern ----------------------------------------------------------------------------------*/

extern const uint32_t KS_TYPE_SIZE[KSERIAL_TYPE_LENS];
extern const char KS_TYPE_STRING[KSERIAL_TYPE_LENS][4];
extern const char KS_TYPE_FORMATE[KSERIAL_TYPE_LENS][8];

/* Functions -------------------------------------------------------------------------------*/

uint32_t    kSerial_GetTypeSize( uint32_t type );

uint32_t    kSerial_CheckHeader( const uint8_t *packet, void *param, uint32_t *type, uint32_t *nbyte );
uint32_t    kSerial_CheckEnd( const uint8_t *packet, uint32_t nbyte );
uint32_t    kSerial_Check( const uint8_t *packet, void *param, uint32_t *type, uint32_t *nbyte );
void        kSerial_GetBytesData( const uint8_t *packet, void *pdata, uint32_t nbyte );

uint32_t    kSerial_Pack( uint8_t *packet, const void *param, uint32_t type, uint32_t lens, const void *pdata );
uint32_t    kSerial_Unpack( const uint8_t *packet, void *param, uint32_t *type, uint32_t *nbyte, void *pdata );
uint32_t    kSerial_UnpackBuffer( const uint8_t *buffer, uint32_t buffersize, kserial_packet_t *ksp, uint32_t *count );

uint32_t    kSerial_SendPacket( void *param, void *pdata, uint32_t lens, uint32_t type );
uint32_t    kSerial_RecvPacket( uint8_t input, void *param, void *pdata, uint32_t *lens, uint32_t *type );

uint32_t    kSerial_Read( kserial_t *ks );
void        kSerial_ReadFlush( kserial_t *ks );
void        kSerial_GetPacketData( kserial_packet_t *ksp, void *pdata, uint32_t index );
uint32_t    kSerial_ContinuousRead( kserial_packet_t *ksp, uint32_t *index, uint32_t *count, uint32_t *total );

uint32_t    kSerial_SendCommand( uint32_t type, uint32_t p1, uint32_t p2, kserial_ack_t *ack );
uint32_t    kSerial_DeviceCheck( uint32_t *id );

uint32_t    kSerial_TwiReadRegs( uint8_t slaveAddr, uint8_t regAddr, uint8_t *regData, uint8_t lens );
uint32_t    kSerial_TwiWriteRegs( uint8_t slaveAddr, uint8_t regAddr, uint8_t *regData, uint8_t lens );
uint32_t    kSerial_TwiScanDevice( uint8_t *slaveAddr );
uint32_t    kSerial_TwiScanRegister( uint8_t slaveAddr, uint8_t reg[256] );

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
