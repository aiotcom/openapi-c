#ifndef _SLIP_H
#define _SLIP_H
#include "stm32f1xx_hal.h"
#include "includes.h"
typedef struct{
	uint8_t seq;
	uint8_t cid;	
	uint8_t tid;
	uint8_t rid;
	uint8_t dl;
	uint8_t *data;	
    uint8_t flg;
}_SLIP;
void slip_pack(uint8_t *in,uint8_t inlen,uint8_t *out,uint8_t *outlen);
void slip_unpack(uint8_t *in,uint8_t inlen,uint8_t *out,uint8_t *outlen);
void sliprecv(uint8_t b);
uint8_t slip_init(_SLIP *slip);

extern OS_EVENT  SemRecvSync;
extern uint8_t sliprecv_flg;
#endif