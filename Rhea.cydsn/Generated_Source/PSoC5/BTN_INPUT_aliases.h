/*******************************************************************************
* File Name: BTN_INPUT.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BTN_INPUT_ALIASES_H) /* Pins BTN_INPUT_ALIASES_H */
#define CY_PINS_BTN_INPUT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define BTN_INPUT_0			(BTN_INPUT__0__PC)
#define BTN_INPUT_0_INTR	((uint16)((uint16)0x0001u << BTN_INPUT__0__SHIFT))

#define BTN_INPUT_1			(BTN_INPUT__1__PC)
#define BTN_INPUT_1_INTR	((uint16)((uint16)0x0001u << BTN_INPUT__1__SHIFT))

#define BTN_INPUT_2			(BTN_INPUT__2__PC)
#define BTN_INPUT_2_INTR	((uint16)((uint16)0x0001u << BTN_INPUT__2__SHIFT))

#define BTN_INPUT_INTR_ALL	 ((uint16)(BTN_INPUT_0_INTR| BTN_INPUT_1_INTR| BTN_INPUT_2_INTR))

#endif /* End Pins BTN_INPUT_ALIASES_H */


/* [] END OF FILE */
