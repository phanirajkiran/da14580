/**
 ****************************************************************************************
 *
 * @file em_map_ble.h
 *
 * @brief Mapping of the different descriptors in the exchange memory
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 ****************************************************************************************
 */

#ifndef EM_MAP_BLE_H_
#define EM_MAP_BLE_H_

/**
 ****************************************************************************************
 * @addtogroup EM EM
 * @ingroup CONTROLLER
 * @brief Mapping of the different descriptors in the exchange memory
 *
 * @{
 ****************************************************************************************
 */
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"                // stack configuration
#include "em_map_ble_user.h"

#if (BT_DUAL_MODE)
#include "em_map_bt.h"
#else //BT_DUAL_MODE
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "co_bt.h"
#include "co_buf.h"
#include "_reg_ble_em_tx.h"
#include "_reg_ble_em_txe.h"
#include "_reg_ble_em_rx.h"
#include "_reg_ble_em_wpb.h"
#include "_reg_ble_em_wpv.h"
#include "_reg_ble_em_et.h"
#include "_reg_ble_em_cs.h"

/*
 * DEFINES
 ****************************************************************************************
 */
/// number of entries for the exchange table
#define EM_BLE_EXCH_TABLE_LEN      16

/// number of frequencies / Depends on RF target
#if defined(CFG_RF_ATLAS)
  /// IcyTRx requires 40 x 32-bit words for Frequency table + 40 byte for VCO sub-band table
  #define EM_BLE_FREQ_TABLE_LEN  160
  #define EM_BLE_VCO_TABLE_LEN 40
#else
  /// Ripple/ExtRC requires 40 x 8-bit words for Frequency table / No VCO sub-band table
#define EM_BLE_FREQ_TABLE_LEN  40
  #define EM_BLE_VCO_TABLE_LEN 0
#endif

/// Size of the encryption area
#define EM_BLE_ENC_LEN         16

/// number of control structure entries for the exchange table
#define EM_BLE_CS_COUNT        (BLE_CONNECTION_MAX + 1)

/// number of control structure entries for the exchange table
#define EM_BLE_TXE_COUNT       (BLE_CONNECTION_MAX)

/// Status of the control structure in the exchange table
enum
{
    EM_BLE_ET_READY,
    EM_BLE_ET_PROCESSED,
    EM_BLE_ET_RESERVED,
    EM_BLE_ET_BYPASSED
};

#if 0
	/*
	 * Mapping of the different elements in EM
	 ****************************************************************************************
	 */
	/// Offset of the exchange table
	#define EM_BLE_ET_OFFSET         0
	/// Offset of the frequency table
	#define EM_BLE_FT_OFFSET         (EM_BLE_ET_OFFSET + EM_BLE_EXCH_TABLE_LEN * REG_BLE_EM_ET_SIZE)
	/// Offset of the plain data area (used for SW initiated encryption)
	#define EM_BLE_ENC_PLAIN_OFFSET  (EM_BLE_FT_OFFSET + (EM_BLE_VCO_TABLE_LEN + EM_BLE_FREQ_TABLE_LEN) * sizeof(uint8_t))
	/// Offset of the ciphered data area (used for SW initiated encryption)
	#define EM_BLE_ENC_CIPHER_OFFSET (EM_BLE_ENC_PLAIN_OFFSET + EM_BLE_ENC_LEN * sizeof(uint8_t))
	/// Offset of the control structure area
	#define EM_BLE_CS_OFFSET         (EM_BLE_ENC_CIPHER_OFFSET + EM_BLE_ENC_LEN * sizeof(uint8_t))



	/// Offset of the public white list area
	#define EM_BLE_WPB_OFFSET        (EM_BLE_CS_OFFSET + EM_BLE_CS_COUNT * REG_BLE_EM_CS_SIZE)
	/// Offset of the private white list area
	#define EM_BLE_WPV_OFFSET        (EM_BLE_WPB_OFFSET + BLE_WHITELIST_MAX * REG_BLE_EM_WPB_SIZE)
	/// Offset of the Connection Address
	#define EM_BLE_CNXADD_OFFSET     (EM_BLE_WPV_OFFSET + BLE_WHITELIST_MAX * REG_BLE_EM_WPV_SIZE)
	/// Offset of the empty TX buffer area
	#define EM_BLE_TXE_OFFSET        (EM_BLE_CNXADD_OFFSET + BD_ADDR_LEN) 
	/// End of EM ret.part
	#define DUMMY_SIZE              (EM_BLE_TXE_OFFSET + EM_BLE_TXE_COUNT * REG_BLE_EM_TXE_SIZE) //(EM_BLE_RF_SPI_OFFSET) 



	// IN CASE OF EXCHANGE MEM. PAGES MAPPING CASE 15
	#define CASE_15_OFFSET (0x2000)
	/// Offset of the TX buffer area
	#define EM_BLE_TX_OFFSET         (CASE_15_OFFSET)
	/// Offset of the RX buffer area
	#define EM_BLE_RX_OFFSET         (EM_BLE_TX_OFFSET + BLE_TX_BUFFER_CNT * REG_BLE_EM_TX_SIZE)
#endif //0
/*
 * Mapping of the different elements in EM
 ****************************************************************************************
 */
/// Offset of the exchange table
#define EM_BLE_ET_OFFSET         0
/// Offset of the frequency table
#define EM_BLE_FT_OFFSET         (EM_BLE_ET_OFFSET + EM_BLE_EXCH_TABLE_LEN * REG_BLE_EM_ET_SIZE)
/// Offset of the plain data area (used for SW initiated encryption)
#define EM_BLE_ENC_PLAIN_OFFSET  (EM_BLE_FT_OFFSET + (EM_BLE_VCO_TABLE_LEN + EM_BLE_FREQ_TABLE_LEN) * sizeof(uint8_t))
/// Offset of the ciphered data area (used for SW initiated encryption)
#define EM_BLE_ENC_CIPHER_OFFSET (EM_BLE_ENC_PLAIN_OFFSET + EM_BLE_ENC_LEN * sizeof(uint8_t))
/// Offset of the control structure area
#define EM_BLE_CS_OFFSET         (EM_BLE_ENC_CIPHER_OFFSET + EM_BLE_ENC_LEN * sizeof(uint8_t))



/// Offset of the public white list area
#define EM_BLE_WPB_OFFSET        (EM_BLE_CS_OFFSET + EM_BLE_CS_COUNT_USER * REG_BLE_EM_CS_SIZE)
/// Offset of the private white list area
#define EM_BLE_WPV_OFFSET        (EM_BLE_WPB_OFFSET + BLE_WHITELIST_MAX_USER * REG_BLE_EM_WPB_SIZE)  
/// Offset of the Connection Address
#define EM_BLE_CNXADD_OFFSET     (EM_BLE_WPV_OFFSET + BLE_WHITELIST_MAX_USER * REG_BLE_EM_WPV_SIZE)
/// Offset of the empty TX buffer area
#define EM_BLE_TXE_OFFSET        (EM_BLE_CNXADD_OFFSET + BD_ADDR_LEN) 
/// End of EM ret.part
#define DUMMY_SIZE               (EM_BLE_TXE_OFFSET + EM_BLE_TXE_COUNT_USER * REG_BLE_EM_TXE_SIZE) //(EM_BLE_RF_SPI_OFFSET) 




// WE DEFINE 6 LINKS AND SELECT EXCHANGE MEM. PAGES MAPPING CASE 23
#define OFFSET_BUFFERS (0x1300) //(0x2000)  //BEGINNING OF BUFFERS IS 0x82000, START OF SYSRAM AFTER EMI


/// Offset of the TX buffer area
#define EM_BLE_TX_OFFSET         (OFFSET_BUFFERS)
/// Offset of the RX buffer area
//#define EM_BLE_RX_OFFSET         (EM_BLE_TX_OFFSET + BLE_TX_BUFFER_CNT_USER * REG_BLE_EM_TX_SIZE)
#define EM_BLE_RX_OFFSET         (EM_BLE_TX_OFFSET + BLE_TX_BUFFER_CNT * REG_BLE_EM_TX_SIZE)

#define EM_SYSMEM_START			 (0x80000+EM_BLE_TX_OFFSET) //ABSOLUTE ADDRESS OF EM IN SYSRAM

#define EM_SYSMEM_END			 (EM_BLE_RX_OFFSET + BLE_RX_BUFFER_CNT * REG_BLE_EM_RX_SIZE) //RELATIVE END ADDRESS OF EM IN SYSRAM

#define EM_SYSMEM_SIZE           (EM_SYSMEM_END-OFFSET_BUFFERS) //SIZE OF EM IN SYSRAM

#endif //BT_DUAL_MODE
/// @} LLDEXMEM

#endif // EM_MAP_BLE_H_
