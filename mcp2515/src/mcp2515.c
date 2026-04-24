/******************************************************************************
 * @file           : mcp2515.c
 * @brief          : Brief description
 * 
 * Detailed description of the file's purpose and functionality.
 *
 * @author         : Your Name
 * @date           : 20-Apr-2026
 ******************************************************************************/

/* -------------------------------------------------------------------------
 *                           << Include Files >>                                   
 * -------------------------------------------------------------------------*/
#include "mcp2515.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
/* -------------------------------------------------------------------------
 *                           << Private Types >>                                   
 * -------------------------------------------------------------------------*/
struct st_mcp2515_ctx
{
	bool isInited;
	st_mcp2515_spi_t st_mcp2515_spi;
};
/* -------------------------------------------------------------------------
 *                           << Private Variables >>                                   
 * -------------------------------------------------------------------------*/
static struct st_mcp2515_ctx st_mcp2515_ctx;
/* -------------------------------------------------------------------------
 *                           << Private Constants >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Macros >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Functions Declarations >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Public Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/
pst_mcp2515_t mcp2515_Init(st_mcp2515_spi_t* pst_spi)
{
	if(pst_spi == NULL) return false;
	if(pst_spi->receive_byte == NULL) return false;
	if(pst_spi->send_byte == NULL) return false;
	if(pst_spi->start_com == NULL) return false;
	if(pst_spi->end_com == NULL) return false;
	st_mcp2515_ctx.st_mcp2515_spi.cs_pin = pst_spi->cs_pin;
	st_mcp2515_ctx.st_mcp2515_spi.send_byte = pst_spi->send_byte;
	st_mcp2515_ctx.st_mcp2515_spi.receive_byte = pst_spi->receive_byte;
	st_mcp2515_ctx.st_mcp2515_spi.start_com = pst_spi->start_com;
	st_mcp2515_ctx.st_mcp2515_spi.end_com = pst_spi->end_com;
	st_mcp2515_ctx.isInited = true;
	return &st_mcp2515_ctx;
}

bool mcp2515_isInited(pst_mcp2515_t pst_mcp2515)
{
	return pst_mcp2515->isInited;
}
bool mcp2515_SendCommand(pst_mcp2515_t pst_mcp2515, uint8_t* p_cmd)
{
	bool sent_result = false;
	if(!pst_mcp2515->isInited){
		return false;
	}
	sent_result = pst_mcp2515->st_mcp2515_spi.send_byte(p_cmd);
	if(!sent_result) return false;
	return true;
}
/******************************** END OF FILE ********************************/