/*******************************************************************************
* File Name: BTN_INPUT.h  
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

#if !defined(CY_PINS_BTN_INPUT_H) /* Pins BTN_INPUT_H */
#define CY_PINS_BTN_INPUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BTN_INPUT_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BTN_INPUT__PORT == 15 && ((BTN_INPUT__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BTN_INPUT_Write(uint8 value);
void    BTN_INPUT_SetDriveMode(uint8 mode);
uint8   BTN_INPUT_ReadDataReg(void);
uint8   BTN_INPUT_Read(void);
void    BTN_INPUT_SetInterruptMode(uint16 position, uint16 mode);
uint8   BTN_INPUT_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BTN_INPUT_SetDriveMode() function.
     *  @{
     */
        #define BTN_INPUT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BTN_INPUT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BTN_INPUT_DM_RES_UP          PIN_DM_RES_UP
        #define BTN_INPUT_DM_RES_DWN         PIN_DM_RES_DWN
        #define BTN_INPUT_DM_OD_LO           PIN_DM_OD_LO
        #define BTN_INPUT_DM_OD_HI           PIN_DM_OD_HI
        #define BTN_INPUT_DM_STRONG          PIN_DM_STRONG
        #define BTN_INPUT_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BTN_INPUT_MASK               BTN_INPUT__MASK
#define BTN_INPUT_SHIFT              BTN_INPUT__SHIFT
#define BTN_INPUT_WIDTH              3u

/* Interrupt constants */
#if defined(BTN_INPUT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BTN_INPUT_SetInterruptMode() function.
     *  @{
     */
        #define BTN_INPUT_INTR_NONE      (uint16)(0x0000u)
        #define BTN_INPUT_INTR_RISING    (uint16)(0x0001u)
        #define BTN_INPUT_INTR_FALLING   (uint16)(0x0002u)
        #define BTN_INPUT_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BTN_INPUT_INTR_MASK      (0x01u) 
#endif /* (BTN_INPUT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BTN_INPUT_PS                     (* (reg8 *) BTN_INPUT__PS)
/* Data Register */
#define BTN_INPUT_DR                     (* (reg8 *) BTN_INPUT__DR)
/* Port Number */
#define BTN_INPUT_PRT_NUM                (* (reg8 *) BTN_INPUT__PRT) 
/* Connect to Analog Globals */                                                  
#define BTN_INPUT_AG                     (* (reg8 *) BTN_INPUT__AG)                       
/* Analog MUX bux enable */
#define BTN_INPUT_AMUX                   (* (reg8 *) BTN_INPUT__AMUX) 
/* Bidirectional Enable */                                                        
#define BTN_INPUT_BIE                    (* (reg8 *) BTN_INPUT__BIE)
/* Bit-mask for Aliased Register Access */
#define BTN_INPUT_BIT_MASK               (* (reg8 *) BTN_INPUT__BIT_MASK)
/* Bypass Enable */
#define BTN_INPUT_BYP                    (* (reg8 *) BTN_INPUT__BYP)
/* Port wide control signals */                                                   
#define BTN_INPUT_CTL                    (* (reg8 *) BTN_INPUT__CTL)
/* Drive Modes */
#define BTN_INPUT_DM0                    (* (reg8 *) BTN_INPUT__DM0) 
#define BTN_INPUT_DM1                    (* (reg8 *) BTN_INPUT__DM1)
#define BTN_INPUT_DM2                    (* (reg8 *) BTN_INPUT__DM2) 
/* Input Buffer Disable Override */
#define BTN_INPUT_INP_DIS                (* (reg8 *) BTN_INPUT__INP_DIS)
/* LCD Common or Segment Drive */
#define BTN_INPUT_LCD_COM_SEG            (* (reg8 *) BTN_INPUT__LCD_COM_SEG)
/* Enable Segment LCD */
#define BTN_INPUT_LCD_EN                 (* (reg8 *) BTN_INPUT__LCD_EN)
/* Slew Rate Control */
#define BTN_INPUT_SLW                    (* (reg8 *) BTN_INPUT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BTN_INPUT_PRTDSI__CAPS_SEL       (* (reg8 *) BTN_INPUT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BTN_INPUT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BTN_INPUT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BTN_INPUT_PRTDSI__OE_SEL0        (* (reg8 *) BTN_INPUT__PRTDSI__OE_SEL0) 
#define BTN_INPUT_PRTDSI__OE_SEL1        (* (reg8 *) BTN_INPUT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BTN_INPUT_PRTDSI__OUT_SEL0       (* (reg8 *) BTN_INPUT__PRTDSI__OUT_SEL0) 
#define BTN_INPUT_PRTDSI__OUT_SEL1       (* (reg8 *) BTN_INPUT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BTN_INPUT_PRTDSI__SYNC_OUT       (* (reg8 *) BTN_INPUT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BTN_INPUT__SIO_CFG)
    #define BTN_INPUT_SIO_HYST_EN        (* (reg8 *) BTN_INPUT__SIO_HYST_EN)
    #define BTN_INPUT_SIO_REG_HIFREQ     (* (reg8 *) BTN_INPUT__SIO_REG_HIFREQ)
    #define BTN_INPUT_SIO_CFG            (* (reg8 *) BTN_INPUT__SIO_CFG)
    #define BTN_INPUT_SIO_DIFF           (* (reg8 *) BTN_INPUT__SIO_DIFF)
#endif /* (BTN_INPUT__SIO_CFG) */

/* Interrupt Registers */
#if defined(BTN_INPUT__INTSTAT)
    #define BTN_INPUT_INTSTAT            (* (reg8 *) BTN_INPUT__INTSTAT)
    #define BTN_INPUT_SNAP               (* (reg8 *) BTN_INPUT__SNAP)
    
	#define BTN_INPUT_0_INTTYPE_REG 		(* (reg8 *) BTN_INPUT__0__INTTYPE)
	#define BTN_INPUT_1_INTTYPE_REG 		(* (reg8 *) BTN_INPUT__1__INTTYPE)
	#define BTN_INPUT_2_INTTYPE_REG 		(* (reg8 *) BTN_INPUT__2__INTTYPE)
#endif /* (BTN_INPUT__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BTN_INPUT_H */


/* [] END OF FILE */
