/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#ifndef __DRVUART_H__
#define __DRVUART_H__

#include "NUC1xx.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/*---------------------------------------------------------------------------------------------------------*/
/*  Define Version number								                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define DRVUART_MAJOR_NUM	1
#define DRVUART_MINOR_NUM	00
#define DRVUART_BUILD_NUM	1

/*---------------------------------------------------------------------------------------------------------*/
/*  Version define with SysInfra				                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define DRVUART_VERSION_NUM     _SYSINFRA_VERSION(DRVUART_MAJOR_NUM, DRVUART_MINOR_NUM, DRVUART_BUILD_NUM)
							   
/*---------------------------------------------------------------------------------------------------------*/
/*  Define Error Code									                                                   */
/*---------------------------------------------------------------------------------------------------------*/
// E_DRVUART_ERR_TIMEOUT  				Time out
// E_DRVUART_ERR_PORT_INVALID		 	Wrong port
// E_DRVUART_ERR_PARITY_INVALID			Wrong party setting
// E_DRVUART_ERR_DATA_BITS_INVALID		Wrong Data bit setting
// E_DRVUART_ERR_STOP_BITS_INVALID		Wrong Stop bit setting
// E_DRVUART_ERR_TRIGGERLEVEL_INVALID	Wrong trigger level setting
// E_DRVUART_ARGUMENT                	Wrong Argument (Wrong UART Port)
#define E_DRVUART_ERR_TIMEOUT   			_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 1)
#define E_DRVUART_ERR_PORT_INVALID		   	_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 2)
#define E_DRVUART_ERR_PARITY_INVALID   		_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 3)
#define E_DRVUART_ERR_DATA_BITS_INVALID 	_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 4)
#define E_DRVUART_ERR_STOP_BITS_INVALID   	_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 5)
#define E_DRVUART_ERR_TRIGGERLEVEL_INVALID  _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 6)
#define E_DRVUART_ARGUMENT                  _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVUART, 7)


typedef void (PFN_DRVUART_CALLBACK)(uint32_t userData);

/*---------------------------------------------------------------------------------------------------------*/
/* Port Number                                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define DRVUART_PORT0		0x000
#define DRVUART_PORT1		0x100000


/*---------------------------------------------------------------------------------------------------------*/
/* define UART line status control			                                                         	   */
/*---------------------------------------------------------------------------------------------------------*/
#define DRVUART_LININT		LINIE
#define DRVUART_WAKEUPINT	WAKEIE
#define DRVUART_BUFERRINT	BUFERRIE
#define DRVUART_TOUTINT		RTOIE 
#define DRVUART_MOSINT		MSIE
#define DRVUART_RLSNT		RLSIE
#define DRVUART_THREINT		THREIE
#define DRVUART_RDAINT		RDAIE

/*---------------------------------------------------------------------------------------------------------*/
/* DATA BIT                                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define DRVUART_DATABITS_5		0x0
#define DRVUART_DATABITS_6		0x1
#define DRVUART_DATABITS_7		0x2
#define DRVUART_DATABITS_8		0x3

/*---------------------------------------------------------------------------------------------------------*/
/* PARITY Setting                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define DRVUART_PARITY_EVEN		0x18
#define DRVUART_PARITY_ODD		0x08
#define DRVUART_PARITY_NONE		0x00
#define DRVUART_PARITY_MARK		0x28
#define DRVUART_PARITY_SPACE	0x38

/*---------------------------------------------------------------------------------------------------------*/
/* STOP BIT                                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define DRVUART_STOPBITS_1		0x0
#define DRVUART_STOPBITS_1_5	0x4
#define DRVUART_STOPBITS_2		0x4

/*---------------------------------------------------------------------------------------------------------*/
/* FIFO Select                                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define DRVUART_FIFO_1BYTES		0x00
#define DRVUART_FIFO_4BYTES		0x10
#define DRVUART_FIFO_8BYTES		0x20
#define DRVUART_FIFO_14BYTES	0x30
#define DRVUART_FIFO_30BYTES	0x40
#define DRVUART_FIFO_46BYTES	0x50
#define DRVUART_FIFO_62BYTES	0x60

/*---------------------------------------------------------------------------------------------------------*/
/* Clock Source                                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define DRVUART_CLKSRC_EXT			0x00	
#define DRVUART_CLKSRC_PLL			0x40
#define DRVUART_CLKSRC_PLL_DIV2		0x80


/*---------------------------------------------------------------------------------------------------------*/
/* Define UART Macro		                                                                         	   */
/*---------------------------------------------------------------------------------------------------------*/
#define LINIE           BIT8			/* LIN RX Break Field Detected Interrupt Enable */
#define WAKEIE          BIT6			/* Wake up interrupt enable */
#define BUFERRIE        BIT5			/* Buffer Error Interrupt Enable  */
#define RTOIE           BIT4			/* RX Time out Interrupt Enable	*/
#define MSIE            BIT3			/* MODEM Status Interrupt (Irpt_MOS) Enable	 */
#define RLSIE           BIT2			/* Receive Line Status Interrupt (Irpt_RLS) Enable */
#define THREIE          BIT1			/* Transmit Holding Register Empty Interrupt (Irpt_THRE) Enable */
#define RDAIE           BIT0			/* Receive Data Available Interrupt (Irpt_RDA) Enable and */
										/* Time-out Interrupt (Irpt_TOUT) Enable */

#define MODE_TX  0
#define MODE_RX  1
/*---------------------------------------------------------------------------------------------------------*/
/*  Define UART initialization data structure                                                              */
/*---------------------------------------------------------------------------------------------------------*/
typedef enum 
{
	MODE_UART =0, 
	MODE_IRCR =1, 
	MODE_LIN =2 
} MODE_SEL;


typedef struct DRVUART_STRUCT
{
    uint32_t        u32BaudRate;
    uint8_t	        u8cDataBits;
    uint8_t   	    u8cStopBits;
    uint8_t			u8cParity;
    uint8_t	        u8cRxTriggerLevel;
    uint8_t         u8TimeOut;
}STR_UART_T;


typedef struct IRCR_STRUCT
{
    uint8_t	        u8cRXSelect;
    uint8_t   	    u8cTXSelect;
    uint8_t			u8cInvTX;
    uint8_t	        u8cInvRX;
}STR_IRCR_T;

typedef enum 
{
	UART_PORT0 = DRVUART_PORT0, 
	UART_PORT1 = DRVUART_PORT1
} UART_PORT;

 
/*---------------------------------------------------------------------------------------------------------*/
/* Define UART functions prototype                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
void DrvUART_Close(UART_PORT Port);
void DrvUART_DisableInt(UART_PORT u16Port,uint32_t u32InterruptFlag);
void DrvUART_GetClcok(uint8_t *pu8ClcokSrc, uint8_t *pu8ClcokDiv);
void DrvUART_GetCTS(UART_PORT u16Port,uint8_t *pu8CTSValue,uint8_t *pu8CTSChangeState);
void DrvUART_SetClcok(uint8_t u8ClcokSrc, uint8_t u8ClcokDiv);
void DrvUART_SetFIFOTriggerLevel(UART_PORT u16Port,uint16_t u32TriggerLevel);
void DrvUART_SetRTS(UART_PORT u16Port,uint8_t	u8Value);
void DrvUART_SetRxTimeOut(UART_PORT u16Port,uint8_t u8TimeOut);
void DrvUART_OpenIRCR(UART_PORT u16Port,STR_IRCR_T str_IRCR );
void DrvUART_OpenLIN(UART_PORT u16Port,uint16_t DIRECTION,uint16_t BCNT);

int8_t DrvUART_GetIntStatus(UART_PORT u16Port,uint32_t u32InterruptFlag);
int32_t DrvUART_Read(UART_PORT u16Port,uint8_t *pu8RxBuf,uint32_t	u32ReadBytes);
int32_t DrvUART_Open(UART_PORT port, STR_UART_T *sParam);
int32_t DrvUART_Write(UART_PORT u16Port,uint8_t *pu8TxBuf,uint32_t u32WriteBytes);
int32_t DrvUART_EnableInt(UART_PORT port,uint32_t u32InterruptFlag,PFN_DRVUART_CALLBACK pfncallback);
int32_t DrvUART_GetVersion(void);
int32_t DrvUART_kbhit(void);
uint32_t DrvUART_IsIntEnabled(UART_PORT u16Port,uint32_t u32InterruptFlag);
uint32_t DrvUART_ClearInt(UART_PORT u16Port,uint32_t u32InterruptFlag);
void DrvUART_SetPDMA(UART_PORT u16Port,uint16_t IsEnable);


#ifdef  __cplusplus
}
#endif

#endif











