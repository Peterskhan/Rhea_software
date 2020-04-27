/*******************************************************************************
* File Name: BTN_ENTER.h  
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

#if !defined(CY_PINS_BTN_ENTER_ALIASES_H) /* Pins BTN_ENTER_ALIASES_H */
#define CY_PINS_BTN_ENTER_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define BTN_ENTER_0			(BTN_ENTER__0__PC)
#define BTN_ENTER_0_INTR	((uint16)((uint16)0x0001u << BTN_ENTER__0__SHIFT))

#define BTN_ENTER_INTR_ALL	 ((uint16)(BTN_ENTER_0_INTR))

#endif /* End Pins BTN_ENTER_ALIASES_H */


/* [] END OF FILE */
