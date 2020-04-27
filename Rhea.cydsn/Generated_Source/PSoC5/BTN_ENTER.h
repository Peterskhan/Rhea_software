/*******************************************************************************
* File Name: BTN_ENTER.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BTN_ENTER_H) /* Pins BTN_ENTER_H */
#define CY_PINS_BTN_ENTER_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BTN_ENTER_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BTN_ENTER__PORT == 15 && ((BTN_ENTER__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BTN_ENTER_Write(uint8 value);
void    BTN_ENTER_SetDriveMode(uint8 mode);
uint8   BTN_ENTER_ReadDataReg(void);
uint8   BTN_ENTER_Read(void);
void    BTN_ENTER_SetInterruptMode(uint16 position, uint16 mode);
uint8   BTN_ENTER_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BTN_ENTER_SetDriveMode() function.
     *  @{
     */
        #define BTN_ENTER_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BTN_ENTER_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BTN_ENTER_DM_RES_UP          PIN_DM_RES_UP
        #define BTN_ENTER_DM_RES_DWN         PIN_DM_RES_DWN
        #define BTN_ENTER_DM_OD_LO           PIN_DM_OD_LO
        #define BTN_ENTER_DM_OD_HI           PIN_DM_OD_HI
        #define BTN_ENTER_DM_STRONG          PIN_DM_STRONG
        #define BTN_ENTER_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BTN_ENTER_MASK               BTN_ENTER__MASK
#define BTN_ENTER_SHIFT              BTN_ENTER__SHIFT
#define BTN_ENTER_WIDTH              1u

/* Interrupt constants */
#if defined(BTN_ENTER__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BTN_ENTER_SetInterruptMode() function.
     *  @{
     */
        #define BTN_ENTER_INTR_NONE      (uint16)(0x0000u)
        #define BTN_ENTER_INTR_RISING    (uint16)(0x0001u)
        #define BTN_ENTER_INTR_FALLING   (uint16)(0x0002u)
        #define BTN_ENTER_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BTN_ENTER_INTR_MASK      (0x01u) 
#endif /* (BTN_ENTER__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BTN_ENTER_PS                     (* (reg8 *) BTN_ENTER__PS)
/* Data Register */
#define BTN_ENTER_DR                     (* (reg8 *) BTN_ENTER__DR)
/* Port Number */
#define BTN_ENTER_PRT_NUM                (* (reg8 *) BTN_ENTER__PRT) 
/* Connect to Analog Globals */                                                  
#define BTN_ENTER_AG                     (* (reg8 *) BTN_ENTER__AG)                       
/* Analog MUX bux enable */
#define BTN_ENTER_AMUX                   (* (reg8 *) BTN_ENTER__AMUX) 
/* Bidirectional Enable */                                                        
#define BTN_ENTER_BIE                    (* (reg8 *) BTN_ENTER__BIE)
/* Bit-mask for Aliased Register Access */
#define BTN_ENTER_BIT_MASK               (* (reg8 *) BTN_ENTER__BIT_MASK)
/* Bypass Enable */
#define BTN_ENTER_BYP                    (* (reg8 *) BTN_ENTER__BYP)
/* Port wide control signals */                                                   
#define BTN_ENTER_CTL                    (* (reg8 *) BTN_ENTER__CTL)
/* Drive Modes */
#define BTN_ENTER_DM0                    (* (reg8 *) BTN_ENTER__DM0) 
#define BTN_ENTER_DM1                    (* (reg8 *) BTN_ENTER__DM1)
#define BTN_ENTER_DM2                    (* (reg8 *) BTN_ENTER__DM2) 
/* Input Buffer Disable Override */
#define BTN_ENTER_INP_DIS                (* (reg8 *) BTN_ENTER__INP_DIS)
/* LCD Common or Segment Drive */
#define BTN_ENTER_LCD_COM_SEG            (* (reg8 *) BTN_ENTER__LCD_COM_SEG)
/* Enable Segment LCD */
#define BTN_ENTER_LCD_EN                 (* (reg8 *) BTN_ENTER__LCD_EN)
/* Slew Rate Control */
#define BTN_ENTER_SLW                    (* (reg8 *) BTN_ENTER__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BTN_ENTER_PRTDSI__CAPS_SEL       (* (reg8 *) BTN_ENTER__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BTN_ENTER_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BTN_ENTER__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BTN_ENTER_PRTDSI__OE_SEL0        (* (reg8 *) BTN_ENTER__PRTDSI__OE_SEL0) 
#define BTN_ENTER_PRTDSI__OE_SEL1        (* (reg8 *) BTN_ENTER__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BTN_ENTER_PRTDSI__OUT_SEL0       (* (reg8 *) BTN_ENTER__PRTDSI__OUT_SEL0) 
#define BTN_ENTER_PRTDSI__OUT_SEL1       (* (reg8 *) BTN_ENTER__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BTN_ENTER_PRTDSI__SYNC_OUT       (* (reg8 *) BTN_ENTER__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BTN_ENTER__SIO_CFG)
    #define BTN_ENTER_SIO_HYST_EN        (* (reg8 *) BTN_ENTER__SIO_HYST_EN)
    #define BTN_ENTER_SIO_REG_HIFREQ     (* (reg8 *) BTN_ENTER__SIO_REG_HIFREQ)
    #define BTN_ENTER_SIO_CFG            (* (reg8 *) BTN_ENTER__SIO_CFG)
    #define BTN_ENTER_SIO_DIFF           (* (reg8 *) BTN_ENTER__SIO_DIFF)
#endif /* (BTN_ENTER__SIO_CFG) */

/* Interrupt Registers */
#if defined(BTN_ENTER__INTSTAT)
    #define BTN_ENTER_INTSTAT            (* (reg8 *) BTN_ENTER__INTSTAT)
    #define BTN_ENTER_SNAP               (* (reg8 *) BTN_ENTER__SNAP)
    
	#define BTN_ENTER_0_INTTYPE_REG 		(* (reg8 *) BTN_ENTER__0__INTTYPE)
#endif /* (BTN_ENTER__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BTN_ENTER_H */


/* [] END OF FILE */
