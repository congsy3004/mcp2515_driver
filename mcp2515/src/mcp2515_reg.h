/**
 * @file  mcp2515_regs.h
 * @brief MCP2515 register addresses and bit-field definitions.
 *
 * Derived from Microchip DS20001801J.
 * All address constants, SPI instruction codes, and bit-mask macros are
 * defined here.  No driver logic lives in this file ? it is pure data.
 *
 * Naming convention
 * -----------------
 *   MCP_REG_<NAME>        Register address (uint8_t)
 *   MCP_BIT_<REG>_<FIELD> Single-bit mask  (uint8_t)
 *   MCP_MSK_<REG>_<FIELD> Multi-bit mask   (uint8_t)
 *   MCP_SPI_<CMD>         SPI instruction byte
 */

#ifndef MCP2515_REGS_H
#define MCP2515_REGS_H

#include <stdint.h>

/* =========================================================================
 * SPI instruction set  (Table 12-1)
 * ========================================================================= */

#define MCP_SPI_RESET           ((uint8_t)0xC0)
#define MCP_SPI_READ            ((uint8_t)0x03)
#define MCP_SPI_WRITE           ((uint8_t)0x02)
#define MCP_SPI_BIT_MODIFY      ((uint8_t)0x05)
#define MCP_SPI_READ_STATUS     ((uint8_t)0xA0)
#define MCP_SPI_RX_STATUS       ((uint8_t)0xB0)

/* READ RX BUFFER ? bits [nm] select start address (Figure 12-3)
 *   n=0,m=0 Å® RXB0SIDH (0x61)
 *   n=0,m=1 Å® RXB0D0   (0x66)
 *   n=1,m=0 Å® RXB1SIDH (0x71)
 *   n=1,m=1 Å® RXB1D0   (0x76)  */
#define MCP_SPI_READ_RX_BUF(n, m) ((uint8_t)(0x90 | (((n) & 0x01) << 2) | (((m) & 0x01) << 1)))

/* LOAD TX BUFFER ? bits [abc] select start address (Figure 12-5)
 *   000 Å® TXB0SIDH (0x31)   001 Å® TXB0D0 (0x36)
 *   010 Å® TXB1SIDH (0x41)   011 Å® TXB1D0 (0x46)
 *   100 Å® TXB2SIDH (0x51)   101 Å® TXB2D0 (0x56)  */
#define MCP_SPI_LOAD_TX_BUF(a, b, c) \
    ((uint8_t)(0x40 | (((a) & 0x01) << 2) | (((b) & 0x01) << 1) | ((c) & 0x01)))

/* RTS ? bits [2:0] map to TXB2, TXB1, TXB0 (Figure 12-6) */
#define MCP_SPI_RTS(txb2, txb1, txb0) \
    ((uint8_t)(0x80 | (((txb2) & 0x01) << 2) | (((txb1) & 0x01) << 1) | ((txb0) & 0x01)))

/* =========================================================================
 * Filter registers  (Section 4.5, Table 11-1)
 * RXF0?RXF2: page 0x0x; RXF3?RXF5: page 0x1x
 * ========================================================================= */

#define MCP_REG_RXF0SIDH        ((uint8_t)0x00)
#define MCP_REG_RXF0SIDL        ((uint8_t)0x01)
#define MCP_REG_RXF0EID8        ((uint8_t)0x02)
#define MCP_REG_RXF0EID0        ((uint8_t)0x03)

#define MCP_REG_RXF1SIDH        ((uint8_t)0x04)
#define MCP_REG_RXF1SIDL        ((uint8_t)0x05)
#define MCP_REG_RXF1EID8        ((uint8_t)0x06)
#define MCP_REG_RXF1EID0        ((uint8_t)0x07)

#define MCP_REG_RXF2SIDH        ((uint8_t)0x08)
#define MCP_REG_RXF2SIDL        ((uint8_t)0x09)
#define MCP_REG_RXF2EID8        ((uint8_t)0x0A)
#define MCP_REG_RXF2EID0        ((uint8_t)0x0B)

#define MCP_REG_RXF3SIDH        ((uint8_t)0x10)
#define MCP_REG_RXF3SIDL        ((uint8_t)0x11)
#define MCP_REG_RXF3EID8        ((uint8_t)0x12)
#define MCP_REG_RXF3EID0        ((uint8_t)0x13)

#define MCP_REG_RXF4SIDH        ((uint8_t)0x14)
#define MCP_REG_RXF4SIDL        ((uint8_t)0x15)
#define MCP_REG_RXF4EID8        ((uint8_t)0x16)
#define MCP_REG_RXF4EID0        ((uint8_t)0x17)

#define MCP_REG_RXF5SIDH        ((uint8_t)0x18)
#define MCP_REG_RXF5SIDL        ((uint8_t)0x19)
#define MCP_REG_RXF5EID8        ((uint8_t)0x1A)
#define MCP_REG_RXF5EID0        ((uint8_t)0x1B)

/* RXFnSIDL ? bit 3 (EXIDE): 1 = filter applies to extended frames only */
#define MCP_BIT_RXFnSIDL_EXIDE  ((uint8_t)(1u << 3))

/* =========================================================================
 * Mask registers  (Section 4.5, Table 11-1)
 * ========================================================================= */

#define MCP_REG_RXM0SIDH        ((uint8_t)0x20)
#define MCP_REG_RXM0SIDL        ((uint8_t)0x21)
#define MCP_REG_RXM0EID8        ((uint8_t)0x22)
#define MCP_REG_RXM0EID0        ((uint8_t)0x23)

#define MCP_REG_RXM1SIDH        ((uint8_t)0x24)
#define MCP_REG_RXM1SIDL        ((uint8_t)0x25)
#define MCP_REG_RXM1EID8        ((uint8_t)0x26)
#define MCP_REG_RXM1EID0        ((uint8_t)0x27)

/* =========================================================================
 * Bit timing configuration  (Section 5.7)
 * ========================================================================= */

#define MCP_REG_CNF3            ((uint8_t)0x28)
#define MCP_REG_CNF2            ((uint8_t)0x29)
#define MCP_REG_CNF1            ((uint8_t)0x2A)

/* CNF1 (Register 5-1) */
#define MCP_MSK_CNF1_SJW        ((uint8_t)(0x03u << 6))   /**< [7:6] SJW[1:0]  */
#define MCP_MSK_CNF1_BRP        ((uint8_t)(0x3Fu << 0))   /**< [5:0] BRP[5:0]  */

/* CNF2 (Register 5-2) */
#define MCP_BIT_CNF2_BTLMODE    ((uint8_t)(1u << 7))      /**< PS2 length source  */
#define MCP_BIT_CNF2_SAM        ((uint8_t)(1u << 6))      /**< Triple sample      */
#define MCP_MSK_CNF2_PHSEG1     ((uint8_t)(0x07u << 3))   /**< [5:3] PHSEG1[2:0] */
#define MCP_MSK_CNF2_PRSEG      ((uint8_t)(0x07u << 0))   /**< [2:0] PRSEG[2:0]  */

/* CNF3 (Register 5-3) */
#define MCP_BIT_CNF3_SOF        ((uint8_t)(1u << 7))      /**< SOF signal on CLKOUT */
#define MCP_BIT_CNF3_WAKFIL     ((uint8_t)(1u << 6))      /**< Wake-up filter       */
#define MCP_MSK_CNF3_PHSEG2     ((uint8_t)(0x07u << 0))   /**< [2:0] PHSEG2[2:0]   */

/* =========================================================================
 * Interrupt enable / flag registers  (Section 7)
 * ========================================================================= */

#define MCP_REG_CANINTE         ((uint8_t)0x2B)
#define MCP_REG_CANINTF         ((uint8_t)0x2C)

/* Shared bit positions for both CANINTE and CANINTF */
#define MCP_BIT_INT_MERR        ((uint8_t)(1u << 7))  /**< Message error          */
#define MCP_BIT_INT_WAK         ((uint8_t)(1u << 6))  /**< Wake-up                */
#define MCP_BIT_INT_ERR         ((uint8_t)(1u << 5))  /**< Error (EFLG change)    */
#define MCP_BIT_INT_TX2         ((uint8_t)(1u << 4))  /**< TXB2 empty             */
#define MCP_BIT_INT_TX1         ((uint8_t)(1u << 3))  /**< TXB1 empty             */
#define MCP_BIT_INT_TX0         ((uint8_t)(1u << 2))  /**< TXB0 empty             */
#define MCP_BIT_INT_RX1         ((uint8_t)(1u << 1))  /**< RXB1 full              */
#define MCP_BIT_INT_RX0         ((uint8_t)(1u << 0))  /**< RXB0 full              */

/* =========================================================================
 * Error flag register  (Section 6.7, Register 6-3)
 * ========================================================================= */

#define MCP_REG_EFLG            ((uint8_t)0x2D)

#define MCP_BIT_EFLG_RX1OVR     ((uint8_t)(1u << 7))  /**< RXB1 overflow (MCU clears) */
#define MCP_BIT_EFLG_RX0OVR     ((uint8_t)(1u << 6))  /**< RXB0 overflow (MCU clears) */
#define MCP_BIT_EFLG_TXBO       ((uint8_t)(1u << 5))  /**< Bus-off (TEC ? 255)        */
#define MCP_BIT_EFLG_TXEP       ((uint8_t)(1u << 4))  /**< TX error-passive (TEC?128) */
#define MCP_BIT_EFLG_RXEP       ((uint8_t)(1u << 3))  /**< RX error-passive (REC?128) */
#define MCP_BIT_EFLG_TXWAR      ((uint8_t)(1u << 2))  /**< TX warning (TEC ? 96)      */
#define MCP_BIT_EFLG_RXWAR      ((uint8_t)(1u << 1))  /**< RX warning (REC ? 96)      */
#define MCP_BIT_EFLG_EWARN      ((uint8_t)(1u << 0))  /**< Either counter ? 96        */

/* =========================================================================
 * Error counters  (Section 6.7)
 * ========================================================================= */

#define MCP_REG_TEC             ((uint8_t)0x1C)  /**< Transmit Error Counter (R)  */
#define MCP_REG_REC             ((uint8_t)0x1D)  /**< Receive Error Counter  (R)  */

/* Error counter thresholds */
#define MCP_ERR_WARNING_LIMIT   ((uint8_t)96u)
#define MCP_ERR_PASSIVE_LIMIT   ((uint8_t)128u)
#define MCP_ERR_BUSOFF_LIMIT    ((uint8_t)255u)

/* =========================================================================
 * CAN control / status  (Section 10)
 * CANCTRL is mirrored at 0x0F, 0x1F, 0x2F, 0x3F, 0x4F, 0x5F, 0x6F, 0x7F
 * CANSTAT is mirrored at 0x0E, 0x1E, 0x2E, 0x3E, 0x4E, 0x5E, 0x6E, 0x7E
 * ========================================================================= */

#define MCP_REG_CANCTRL         ((uint8_t)0x0F)
#define MCP_REG_CANSTAT         ((uint8_t)0x0E)

/* CANCTRL (Register 10-1) */
#define MCP_MSK_CANCTRL_REQOP   ((uint8_t)(0x07u << 5))  /**< [7:5] Request op mode */
#define MCP_BIT_CANCTRL_ABAT    ((uint8_t)(1u << 4))     /**< Abort all TX          */
#define MCP_BIT_CANCTRL_OSM     ((uint8_t)(1u << 3))     /**< One-shot mode         */
#define MCP_BIT_CANCTRL_CLKEN   ((uint8_t)(1u << 2))     /**< CLKOUT enable         */
#define MCP_MSK_CANCTRL_CLKPRE  ((uint8_t)(0x03u << 0))  /**< [1:0] CLKOUT prescaler*/

/* REQOP[2:0] values Å® write to CANCTRL[7:5] */
#define MCP_REQOP_NORMAL        ((uint8_t)(0x00u << 5))
#define MCP_REQOP_SLEEP         ((uint8_t)(0x01u << 5))
#define MCP_REQOP_LOOPBACK      ((uint8_t)(0x02u << 5))
#define MCP_REQOP_LISTENONLY    ((uint8_t)(0x03u << 5))
#define MCP_REQOP_CONFIG        ((uint8_t)(0x04u << 5))

/* CLKPRE[1:0] values */
#define MCP_CLKPRE_DIV1         ((uint8_t)0x00u)
#define MCP_CLKPRE_DIV2         ((uint8_t)0x01u)
#define MCP_CLKPRE_DIV4         ((uint8_t)0x02u)
#define MCP_CLKPRE_DIV8         ((uint8_t)0x03u)

/* CANSTAT (Register 10-2) */
#define MCP_MSK_CANSTAT_OPMOD   ((uint8_t)(0x07u << 5))  /**< [7:5] Current op mode */
#define MCP_MSK_CANSTAT_ICOD    ((uint8_t)(0x07u << 1))  /**< [3:1] Interrupt code  */

/* OPMOD[2:0] values Å® read from CANSTAT[7:5] */
#define MCP_OPMOD_NORMAL        ((uint8_t)(0x00u << 5))
#define MCP_OPMOD_SLEEP         ((uint8_t)(0x01u << 5))
#define MCP_OPMOD_LOOPBACK      ((uint8_t)(0x02u << 5))
#define MCP_OPMOD_LISTENONLY    ((uint8_t)(0x03u << 5))
#define MCP_OPMOD_CONFIG        ((uint8_t)(0x04u << 5))

/* ICOD[2:0] values (Table 7-1) Å® read from CANSTAT[3:1] */
#define MCP_ICOD_NONE           ((uint8_t)(0x00u << 1))
#define MCP_ICOD_ERR            ((uint8_t)(0x01u << 1))
#define MCP_ICOD_WAK            ((uint8_t)(0x02u << 1))
#define MCP_ICOD_TX0            ((uint8_t)(0x03u << 1))
#define MCP_ICOD_TX1            ((uint8_t)(0x04u << 1))
#define MCP_ICOD_TX2            ((uint8_t)(0x05u << 1))
#define MCP_ICOD_RX0            ((uint8_t)(0x06u << 1))
#define MCP_ICOD_RX1            ((uint8_t)(0x07u << 1))

/* =========================================================================
 * RXnBF pin control  (Section 4.4, Register 4-3)
 * ========================================================================= */

#define MCP_REG_BFPCTRL         ((uint8_t)0x0C)

#define MCP_BIT_BFPCTRL_B1BFS   ((uint8_t)(1u << 5))  /**< RX1BF pin state (dig out) */
#define MCP_BIT_BFPCTRL_B0BFS   ((uint8_t)(1u << 4))  /**< RX0BF pin state (dig out) */
#define MCP_BIT_BFPCTRL_B1BFE   ((uint8_t)(1u << 3))  /**< RX1BF function enable     */
#define MCP_BIT_BFPCTRL_B0BFE   ((uint8_t)(1u << 2))  /**< RX0BF function enable     */
#define MCP_BIT_BFPCTRL_B1BFM   ((uint8_t)(1u << 1))  /**< RX1BF mode: 1=INT, 0=OUT  */
#define MCP_BIT_BFPCTRL_B0BFM   ((uint8_t)(1u << 0))  /**< RX0BF mode: 1=INT, 0=OUT  */

/* =========================================================================
 * TXnRTS pin control  (Section 3.5, Register 3-2)
 * ========================================================================= */

#define MCP_REG_TXRTSCTRL       ((uint8_t)0x0D)

#define MCP_BIT_TXRTSCTRL_B2RTS  ((uint8_t)(1u << 5))  /**< TX2RTS pin state (R)     */
#define MCP_BIT_TXRTSCTRL_B1RTS  ((uint8_t)(1u << 4))  /**< TX1RTS pin state (R)     */
#define MCP_BIT_TXRTSCTRL_B0RTS  ((uint8_t)(1u << 3))  /**< TX0RTS pin state (R)     */
#define MCP_BIT_TXRTSCTRL_B2RTSM ((uint8_t)(1u << 2))  /**< TX2RTS: 1=RTS, 0=dig in  */
#define MCP_BIT_TXRTSCTRL_B1RTSM ((uint8_t)(1u << 1))  /**< TX1RTS: 1=RTS, 0=dig in  */
#define MCP_BIT_TXRTSCTRL_B0RTSM ((uint8_t)(1u << 0))  /**< TX0RTS: 1=RTS, 0=dig in  */

/* =========================================================================
 * Transmit buffer registers  (Section 3, Registers 3-1 to 3-8)
 *
 * TXBn base addresses:  TXB0=0x30, TXB1=0x40, TXB2=0x50
 * Offsets from base:    CTRL=0, SIDH=1, SIDL=2, EID8=3, EID0=4, DLC=5, D0?D7=6?13
 * ========================================================================= */

#define MCP_REG_TXB0CTRL        ((uint8_t)0x30)
#define MCP_REG_TXB0SIDH        ((uint8_t)0x31)
#define MCP_REG_TXB0SIDL        ((uint8_t)0x32)
#define MCP_REG_TXB0EID8        ((uint8_t)0x33)
#define MCP_REG_TXB0EID0        ((uint8_t)0x34)
#define MCP_REG_TXB0DLC         ((uint8_t)0x35)
#define MCP_REG_TXB0D0          ((uint8_t)0x36)

#define MCP_REG_TXB1CTRL        ((uint8_t)0x40)
#define MCP_REG_TXB1SIDH        ((uint8_t)0x41)
#define MCP_REG_TXB1SIDL        ((uint8_t)0x42)
#define MCP_REG_TXB1EID8        ((uint8_t)0x43)
#define MCP_REG_TXB1EID0        ((uint8_t)0x44)
#define MCP_REG_TXB1DLC         ((uint8_t)0x45)
#define MCP_REG_TXB1D0          ((uint8_t)0x46)

#define MCP_REG_TXB2CTRL        ((uint8_t)0x50)
#define MCP_REG_TXB2SIDH        ((uint8_t)0x51)
#define MCP_REG_TXB2SIDL        ((uint8_t)0x52)
#define MCP_REG_TXB2EID8        ((uint8_t)0x53)
#define MCP_REG_TXB2EID0        ((uint8_t)0x54)
#define MCP_REG_TXB2DLC         ((uint8_t)0x55)
#define MCP_REG_TXB2D0          ((uint8_t)0x56)

/* TXBnCTRL (Register 3-1) ? same bit layout for all three buffers */
#define MCP_BIT_TXBnCTRL_ABTF   ((uint8_t)(1u << 6))  /**< Message aborted (R)       */
#define MCP_BIT_TXBnCTRL_MLOA   ((uint8_t)(1u << 5))  /**< Lost arbitration (R)      */
#define MCP_BIT_TXBnCTRL_TXERR  ((uint8_t)(1u << 4))  /**< Bus error during TX (R)   */
#define MCP_BIT_TXBnCTRL_TXREQ  ((uint8_t)(1u << 3))  /**< Request TX / pending (RW) */
#define MCP_MSK_TXBnCTRL_TXP    ((uint8_t)(0x03u << 0)) /**< [1:0] TX priority        */

/* TXP[1:0] priority values */
#define MCP_TXP_HIGHEST         ((uint8_t)0x03u)
#define MCP_TXP_HIGH            ((uint8_t)0x02u)
#define MCP_TXP_LOW             ((uint8_t)0x01u)
#define MCP_TXP_LOWEST          ((uint8_t)0x00u)

/* TXBnSIDL (Register 3-4) */
#define MCP_BIT_TXBnSIDL_EXIDE  ((uint8_t)(1u << 3))  /**< Extended ID enable        */

/* TXBnDLC (Register 3-7) */
#define MCP_BIT_TXBnDLC_RTR     ((uint8_t)(1u << 6))  /**< Remote TX request frame   */
#define MCP_MSK_TXBnDLC_DLC     ((uint8_t)(0x0Fu << 0)) /**< [3:0] Data length 0?8   */

/* Utility: base address and D0 offset for each TX buffer */
#define MCP_TXB_CTRL_BASE(n)    ((uint8_t)(0x30u + ((n) * 0x10u)))
#define MCP_TXB_SIDH_BASE(n)    ((uint8_t)(0x31u + ((n) * 0x10u)))
#define MCP_TXB_D0_BASE(n)      ((uint8_t)(0x36u + ((n) * 0x10u)))

/* =========================================================================
 * Receive buffer registers  (Section 4, Registers 4-1 to 4-9)
 *
 * RXBn base addresses:  RXB0=0x60, RXB1=0x70
 * Offsets from base:    CTRL=0, SIDH=1, SIDL=2, EID8=3, EID0=4, DLC=5, D0?D7=6?13
 * ========================================================================= */

#define MCP_REG_RXB0CTRL        ((uint8_t)0x60)
#define MCP_REG_RXB0SIDH        ((uint8_t)0x61)
#define MCP_REG_RXB0SIDL        ((uint8_t)0x62)
#define MCP_REG_RXB0EID8        ((uint8_t)0x63)
#define MCP_REG_RXB0EID0        ((uint8_t)0x64)
#define MCP_REG_RXB0DLC         ((uint8_t)0x65)
#define MCP_REG_RXB0D0          ((uint8_t)0x66)

#define MCP_REG_RXB1CTRL        ((uint8_t)0x70)
#define MCP_REG_RXB1SIDH        ((uint8_t)0x71)
#define MCP_REG_RXB1SIDL        ((uint8_t)0x72)
#define MCP_REG_RXB1EID8        ((uint8_t)0x73)
#define MCP_REG_RXB1EID0        ((uint8_t)0x74)
#define MCP_REG_RXB1DLC         ((uint8_t)0x75)
#define MCP_REG_RXB1D0          ((uint8_t)0x76)

/* RXB0CTRL (Register 4-1) */
#define MCP_MSK_RXB0CTRL_RXM    ((uint8_t)(0x03u << 5))  /**< [6:5] Receive mode      */
#define MCP_BIT_RXB0CTRL_RXRTR  ((uint8_t)(1u << 3))     /**< Remote TX request rcvd  */
#define MCP_BIT_RXB0CTRL_BUKT   ((uint8_t)(1u << 2))     /**< Rollover to RXB1 enable */
#define MCP_BIT_RXB0CTRL_FILHIT0 ((uint8_t)(1u << 0))    /**< Filter hit (RXF0/RXF1)  */

/* RXB1CTRL (Register 4-2) */
#define MCP_MSK_RXB1CTRL_RXM    ((uint8_t)(0x03u << 5))  /**< [6:5] Receive mode      */
#define MCP_BIT_RXB1CTRL_RXRTR  ((uint8_t)(1u << 3))     /**< Remote TX request rcvd  */
#define MCP_MSK_RXB1CTRL_FILHIT ((uint8_t)(0x07u << 0))  /**< [2:0] Filter hit code   */

/* RXM[1:0] values (same position in both RXBnCTRL) */
#define MCP_RXM_FILTER          ((uint8_t)(0x00u << 5))  /**< Use filters (normal)    */
#define MCP_RXM_ANY             ((uint8_t)(0x03u << 5))  /**< Receive all messages    */

/* RXBnSIDL (Register 4-5) */
#define MCP_BIT_RXBnSIDL_SRR    ((uint8_t)(1u << 4))  /**< Standard remote TX req    */
#define MCP_BIT_RXBnSIDL_IDE    ((uint8_t)(1u << 3))  /**< Extended frame received   */

/* RXBnDLC (Register 4-8) */
#define MCP_BIT_RXBnDLC_RTR     ((uint8_t)(1u << 6))  /**< Extended remote TX req    */
#define MCP_MSK_RXBnDLC_DLC     ((uint8_t)(0x0Fu << 0)) /**< [3:0] Data length       */

/* Utility: base address for each RX buffer */
#define MCP_RXB_CTRL_BASE(n)    ((uint8_t)(0x60u + ((n) * 0x10u)))
#define MCP_RXB_SIDH_BASE(n)    ((uint8_t)(0x61u + ((n) * 0x10u)))
#define MCP_RXB_D0_BASE(n)      ((uint8_t)(0x66u + ((n) * 0x10u)))

/* =========================================================================
 * READ STATUS response bit positions  (Figure 12-8)
 * ========================================================================= */

#define MCP_STATUS_RX0IF        ((uint8_t)(1u << 0))
#define MCP_STATUS_RX1IF        ((uint8_t)(1u << 1))
#define MCP_STATUS_TX0REQ       ((uint8_t)(1u << 2))  /**< TXB0 pending TX           */
#define MCP_STATUS_TX0IF        ((uint8_t)(1u << 3))
#define MCP_STATUS_TX1REQ       ((uint8_t)(1u << 4))
#define MCP_STATUS_TX1IF        ((uint8_t)(1u << 5))
#define MCP_STATUS_TX2REQ       ((uint8_t)(1u << 6))
#define MCP_STATUS_TX2IF        ((uint8_t)(1u << 7))

/* =========================================================================
 * RX STATUS response bit positions  (Figure 12-9)
 * ========================================================================= */

#define MCP_RXSTATUS_MSG_IN_RXB0  ((uint8_t)(0x01u << 6))
#define MCP_RXSTATUS_MSG_IN_RXB1  ((uint8_t)(0x02u << 6))
#define MCP_RXSTATUS_MSG_IN_BOTH  ((uint8_t)(0x03u << 6))
#define MCP_MSK_RXSTATUS_MSGBUF   ((uint8_t)(0x03u << 6))

#define MCP_BIT_RXSTATUS_EXTID    ((uint8_t)(1u << 4))
#define MCP_BIT_RXSTATUS_RTR      ((uint8_t)(1u << 3))
#define MCP_MSK_RXSTATUS_FILTMATCH ((uint8_t)(0x07u << 0))

/* =========================================================================
 * Hardware limits
 * ========================================================================= */

#define MCP_N_TX_BUFFERS        (3u)
#define MCP_N_RX_BUFFERS        (2u)
#define MCP_N_FILTERS           (6u)
#define MCP_N_MASKS             (2u)
#define MCP_MAX_DATA_BYTES      (8u)
#define MCP_OST_CYCLES          (128u)  /**< Oscillator start-up time in OSC1 cycles */

#endif /* MCP2515_REGS_H */