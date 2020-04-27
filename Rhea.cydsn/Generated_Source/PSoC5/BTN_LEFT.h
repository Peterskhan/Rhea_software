/*******************************************************************************
* File Name: BTN_LEFT.h  
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

#if !defined(CY_PINS_BTN_LEFT_H) /* Pins BTN_LEFT_H */
#define CY_PINS_BTN_LEFT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BTN_LEFT_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BTN_LEFT__PORT == 15 && ((BTN_LEFT__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BTN_LEFT_Write(uint8 value);
void    BTN_LEFT_SetDriveMode(uint8 mode);
uint8   BTN_LEFT_ReadDataReg(void);
uint8   BTN_LEFT_Read(void);
void    BTN_LEFT_SetInterruptMode(uint16 position, uint16 mode);
uint8   BTN_LEFT_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BTN_LEFT_SetDriveMode() function.
     *  @{
     */
        #define BTN_LEFT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BTN_LEFT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BTN_LEFT_DM_RES_UP          PIN_DM_RES_UP
        #define BTN_LEFT_DM_RES_DWN         PIN_DM_RES_DWN
        #define BTN_LEFT_DM_OD_LO           PIN_DM_OD_LO
        #define BTN_LEFT_DM_OD_HI           PIN_DM_OD_HI
        #define BTN_LEFT_DM_STRONG          PIN_DM_STRONG
        #define BTN_LEFT_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BTN_LEFT_MASK               BTN_LEFT__MASK
#define BTN_LEFT_SHIFT              BTN_LEFT__SHIFT
#define BTN_LEFT_WIDTH              1u

/* Interrupt constants */
#if defined(BTN_LEFT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BTN_LEFT_SetInterruptMode() function.
     *  @{
     */
        #define BTN_LEFT_INTR_NONE      (uint16)(0x0000u)
        #define BTN_LEFT_INTR_RISING    (uint16)(0x0001u)
        #define BTN_LEFT_INTR_FALLING   (uint16)(0x0002u)
        #define BTN_LEFT_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BTN_LEFT_INTR_MASK      (0x01u) 
#endif /* (BTN_LEFT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BTN_LEFT_PS                     (* (reg8 *) BTN_LEFT__PS)
/* Data Register */
#define BTN_LEFT_DR                     (* (reg8 *) BTN_LEFT__DR)
/* Port Number */
#define BTN_LEFT_PRT_NUM                (* (reg8 *) BTN_LEFT__PRT) 
/* Connect to Analog Globals */                                                  
#define BTN_LEFT_AG                     (* (reg8 *) BTN_LEFT__AG)                       
/* Analog MUX bux enable */
#define BTN_LEFT_AMUX                   (* (reg8 *) BTN_LEFT__AMUX) 
/* Bidirectional Enable */                                                        
#define BTN_LEFT_BIE                    (* (reg8 *) BTN_LEFT__BIE)
/* Bit-mask for Aliased Register Access */
#define BTN_LEFT_BIT_MASK               (* (reg8 *) BTN_LEFT__BIT_MASK)
/* Bypass Enable */
#define BTN_LEFT_BYP                    (* (reg8 *) BTN_LEFT__BYP)
/* Port wide control signals */                                                   
#define BTN_LEFT_CTL                    (* (reg8 *) BTN_LEFT__CTL)
/* Drive Modes */
#define BTN_LEFT_DM0                    (* (reg8 *) BTN_LEFT__DM0) 
#define BTN_LEFT_DM1                    (* (reg8 *) BTN_LEFT__DM1)
#define BTN_LEFT_DM2                    (* (reg8 *) BTN_LEFT__DM2) 
/* Input Buffer Disable Override */
#define BTN_LEFT_INP_DIS                (* (reg8 *) BTN_LEFT__INP_DIS)
/* LCD Common or Segment Drive */
#define BTN_LEFT_LCD_COM_SEG            (* (reg8 *) BTN_LEFT__LCD_COM_SEG)
/* Enable Segment LCD */
#define BTN_LEFT_LCD_EN                 (* (reg8 *) BTN_LEFT__LCD_EN)
/* Slew Rate Control */
#define BTN_LEFT_SLW                    (* (reg8 *) BTN_LEFT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BTN_LEFT_PRTDSI__CAPS_SEL       (* (reg8 *) BTN_LEFT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BTN_LEFT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BTN_LEFT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BTN_LEFT_PRTDSI__OE_SEL0        (* (reg8 *) BTN_LEFT__PRTDSI__OE_SEL0) 
#define BTN_LEFT_PRTDSI__OE_SEL1        (* (reg8 *) BTN_LEFT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BTN_LEFT_PRTDSI__OUT_SEL0       (* (reg8 *) BTN_LEFT__PRTDSI__OUT_SEL0) 
#define BTN_LEFT_PRTDSI__OUT_SEL1       (* (reg8 *) BTN_LEFT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BTN_LEFT_PRTDSI__SYNC_OUT       (* (reg8 *) BTN_LEFT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BTN_LEFT__SIO_CFG)
    #define BTN_LEFT_SIO_HYST_EN        (* (reg8 *) BTN_LEFT__SIO_HYST_EN)
    #define BTN_LEFT_SIO_REG_HIFREQ     (* (reg8 *) BTN_LEFT__SIO_REG_HIFREQ)
    #define BTN_LEFT_SIO_CFG            (* (reg8 *) BTN_LEFT__SIO_CFG)
    #define BTN_LEFT_SIO_DIFF           (* (reg8 *) BTN_LEFT__SIO_DIFF)
#endif /* (BTN_LEFT__SIO_CFG) */

/* Interrupt Registers */
#if defined(BTN_LEFT__INTSTAT)
    #define BTN_LEFT_INTSTAT            (* (reg8 *) BTN_LEFT__INTSTAT)
    #define BTN_LEFT_SNAP               (* (reg8 *) BTN_LEFT__SNAP)
    
	#define BTN_LEFT_0_INTTYPE_REG 		(* (reg8 *) BTN_LEFT__0__INTTYPE)
#endif /* (BTN_LEFT__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BTN_LEFT_H */


/* [] END OF FILE */
