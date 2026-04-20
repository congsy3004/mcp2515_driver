/******************************************************************************
 * @file           : mcp2515.h
 * @brief          : Brief description
 * @author         : Your Name
 * @date           : 20-Apr-2026
 ******************************************************************************/

#ifndef MCP2515_H
#define MCP2515_H

#ifdef __cplusplus
extern "C" {
#endif
/** Driver requirements:
1. Hard reset
2. Start communication with SPI by pulling CS low
3. Send a 8-bit command to the MCP2515.
4. Send a byte of data to the MCP2515
5. 
*/

/* -------------------------------------------------------------------------
 *                           << Include Files >>                                   
 * -------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
/* -------------------------------------------------------------------------
 *                           << Exported Types >>                                   
 * -------------------------------------------------------------------------*/
typedef struct st_mcp2515_ctx* pst_mcp2515_t;
typedef struct
{
	uint32_t cs_pin; // chip select pin
	bool (*send_byte)(uint8_t* p_data);
	bool (*receive_byte)(uint8_t* buffer);
	bool (*start_com)(uint32_t);
	bool (*end_com)(uint32_t);
}st_mcp2515_spi_t;



/* -------------------------------------------------------------------------
 *                           << Exported Constants >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Exported Macros >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Exported Functions >>                                   
 * -------------------------------------------------------------------------*/
pst_mcp2515_t mcp2515_Init(st_mcp2515_spi_t*);
bool mcp2515_isInited(pst_mcp2515_t);
bool mcp2515_SendCommand(pst_mcp2515_t, uint8_t*);
#ifdef __cplusplus
}
#endif

#endif /* MCP2515_H */

/******************************** END OF FILE ********************************/