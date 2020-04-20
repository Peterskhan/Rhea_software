/*******************************************************************************
* File Name: SENSOR_1MS.h
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
#if !defined(CY_ISR_SENSOR_1MS_H)
#define CY_ISR_SENSOR_1MS_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SENSOR_1MS_Start(void);
void SENSOR_1MS_StartEx(cyisraddress address);
void SENSOR_1MS_Stop(void);

CY_ISR_PROTO(SENSOR_1MS_Interrupt);

void SENSOR_1MS_SetVector(cyisraddress address);
cyisraddress SENSOR_1MS_GetVector(void);

void SENSOR_1MS_SetPriority(uint8 priority);
uint8 SENSOR_1MS_GetPriority(void);

void SENSOR_1MS_Enable(void);
uint8 SENSOR_1MS_GetState(void);
void SENSOR_1MS_Disable(void);

void SENSOR_1MS_SetPending(void);
void SENSOR_1MS_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SENSOR_1MS ISR. */
#define SENSOR_1MS_INTC_VECTOR            ((reg32 *) SENSOR_1MS__INTC_VECT)

/* Address of the SENSOR_1MS ISR priority. */
#define SENSOR_1MS_INTC_PRIOR             ((reg8 *) SENSOR_1MS__INTC_PRIOR_REG)

/* Priority of the SENSOR_1MS interrupt. */
#define SENSOR_1MS_INTC_PRIOR_NUMBER      SENSOR_1MS__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SENSOR_1MS interrupt. */
#define SENSOR_1MS_INTC_SET_EN            ((reg32 *) SENSOR_1MS__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SENSOR_1MS interrupt. */
#define SENSOR_1MS_INTC_CLR_EN            ((reg32 *) SENSOR_1MS__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SENSOR_1MS interrupt state to pending. */
#define SENSOR_1MS_INTC_SET_PD            ((reg32 *) SENSOR_1MS__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SENSOR_1MS interrupt. */
#define SENSOR_1MS_INTC_CLR_PD            ((reg32 *) SENSOR_1MS__INTC_CLR_PD_REG)


#endif /* CY_ISR_SENSOR_1MS_H */


/* [] END OF FILE */
