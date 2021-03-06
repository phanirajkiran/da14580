#ifndef _RF_580_H_
#define _RF_580_H_

#include "global_io.h"
#include "rwip.h"               // for RF API structure definition
#include "reg_blecore.h"        // ble core registers
#include "reg_ble_em_cs.h"      // control structure definitions

#define DCDC_CTRL_REG  (0x50000080)
#define DCDC_CTRL2_REG (0x50000082)
#define DCDC_CTRL3_REG (0x50000084) 

#define RC16_CAL_REF_CYCLES 0x400

#define RF_DIAG_IRQ_MODE_TXONLY       0
#define RF_DIAG_IRQ_MODE_RXTX         1

void rf_init(struct rwip_rf_api *api);

void rf_init_func(struct rwip_rf_api *api);

bool rf_calibration(void);

uint16_t get_rc16m_count(void);

void conditionally_run_radio_cals(void);

void enable_rf_diag_irq(uint8_t mode);

void set_gauss_modgain(uint16_t cn);


#endif // _RF_580_H_

