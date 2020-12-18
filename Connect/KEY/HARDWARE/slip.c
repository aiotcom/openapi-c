#include "slip.h"
#include "stm32f1xx_hal.h"
uint8_t slipdata[64];
_SLIP *pslip;
void ProtocolSort(uint8_t *sd,uint8_t len);
uint8_t slip_init(_SLIP *slip)
{
    slip->data = slipdata;
    pslip = slip;
}
uint8_t _xor(uint8_t *in,uint8_t len)
{
	uint8_t i = len,x=0;
	while(i--)
	{
		x = x ^ (*in);
		in++;		
	}
	return x;
}
void slip_pack(uint8_t *in,uint8_t inlen,uint8_t *out,uint8_t *outlen)
{
	uint8_t b,i = 0;
	out[i++] = 0xC0;
	while(inlen--)
	{
		b = *in;
		switch(b)
		{
			case 0xC0:
				out[i++] = 0xDB;
				out[i++] = 0xDC;
				break;
			case 0xDB:
				out[i++] = 0xDB;
				out[i++] = 0xDD;				
				break;
			default:
				out[i++] = b;
				break;						
		}
        in++;
	}
	
//取CRC检验度度转换	
	b = _xor(&out[1],i);
	switch(b)
	{
		case 0xC0:
			out[i++] = 0xDB;
			out[i++] = 0xDC;
			break;
		case 0xDB:
			out[i++] = 0xDB;
			out[i++] = 0xDD;				
			break;
		default:
			out[i++] = b;
			break;						
	}
//取CRC检验度度转换		
	out[i++] = 0xC0;
	*outlen = i;	
}

void slip_unpack(uint8_t *in,uint8_t inlen,uint8_t *out,uint8_t *outlen)
{
	uint8_t b = 0,nb = 0,i=0;

	while(inlen--)
	{
		b = *in;
        if(b==0xDB)
        {
            nb = *(++in);
            if((b==0xDB)&&(nb==0xDC))
            {
                out[i++] = 0xC0;
            }
            else if((b==0xDB)&&(nb==0xDD))
            {
                out[i++] = 0xDB;			
            }
        }
		else if(b != 0xC0)
		{
			out[i++] = *in;
		}
        in++;
	}
	*outlen = i;		
}

uint8_t sliprecv_buf[128],recvcount=0;
uint8_t sliprecv_state = 0;
uint8_t sliprecv_flg = 0;
void sliprecv(uint8_t b)
{
    switch(sliprecv_state)
    {
        case 0:
            if(b==0xC0)
            {
                recvcount = 0;
                sliprecv_buf[recvcount++] = b;
                sliprecv_state = 1;
            }
            break;
        case 1:
            if(b==0xC0)
            {
                sliprecv_buf[recvcount++] = b;
                sliprecv_flg = 0;
                sliprecv_state = 0;
                ProtocolSort(sliprecv_buf,recvcount);               
                OSSemPost(&SemRecvSync);
                pslip->flg = 1;
            }
            else
            {
                sliprecv_buf[recvcount++] = b;
            }            
            break;
        default:
            break;
    }
}

uint8_t slip_unpack_buf[64];
void ProtocolSort(uint8_t *sd,uint8_t len)
{
    uint8_t datalen;
    slip_unpack(sd,len,slip_unpack_buf,&datalen);   
    memcpy((void*)pslip,(const void*)slip_unpack_buf,5); 
    if(pslip->dl)
    {
        memcpy((void*)pslip->data,(const void*)&slip_unpack_buf[5],pslip->dl); 
    }        
}
























