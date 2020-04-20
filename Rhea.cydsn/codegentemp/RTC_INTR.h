/*******************************************************************************
* File Name: RTC_INTR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_RTC_INTR_H)
#define CY_ISR_RTC_INTR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void RTC_INTR_Start(void);
void RTC_INTR_StartEx(cyisraddress address);
void RTC_INTR_Stop(void);

CY_ISR_PROTO(RTC_INTR_Interrupt);

void RTC_INTR_SetVector(cyisraddress address);
cyisraddress RTC_INTR_GetVector(void);

void RTC_INTR_SetPriority(uint8 priority);
uint8 RTC_INTR_GetPriority(void);

void RTC_INTR_Enable(void);
uint8 RTC_INTR_GetState(void);
void RTC_INTR_Disable(void);

void RTC_INTR_SetPending(void);
void RTC_INTR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the RTC_INTR ISR. */
#define RTC_INTR_INTC_VECTOR            ((reg32 *) RTC_INTR__INTC_VECT)

/* Address of the RTC_INTR ISR priority. */
#define RTC_INTR_INTC_PRIOR             ((reg8 *) RTC_INTR__INTC_PRIOR_REG)

/* Priority of the RTC_INTR interrupt. */
#define RTC_INTR_INTC_PRIOR_NUMBER      RTC_INTR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable RTC_INTR interrupt. */
#define RTC_INTR_INTC_SET_EN            ((reg32 *) RTC_INTR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the RTC_INTR interrupt. */
#define RTC_INTR_INTC_CLR_EN            ((reg32 *) RTC_INTR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the RTC_INTR interrupt state to pending. */
#define RTC_INTR_INTC_SET_PD            ((reg32 *) RTC_INTR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the RTC_INTR interrupt. */
#define RTC_INTR_INTC_CLR_PD            ((reg32 *) RTC_INTR__INTC_CLR_PD_REG)


#endif /* CY_ISR_RTC_INTR_H */


/* [] END OF FILE */
