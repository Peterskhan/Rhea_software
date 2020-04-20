/*******************************************************************************
* File Name: RTC_INTR_PIN.h  
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

#if !defined(CY_PINS_RTC_INTR_PIN_H) /* Pins RTC_INTR_PIN_H */
#define CY_PINS_RTC_INTR_PIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RTC_INTR_PIN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RTC_INTR_PIN__PORT == 15 && ((RTC_INTR_PIN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RTC_INTR_PIN_Write(uint8 value);
void    RTC_INTR_PIN_SetDriveMode(uint8 mode);
uint8   RTC_INTR_PIN_ReadDataReg(void);
uint8   RTC_INTR_PIN_Read(void);
void    RTC_INTR_PIN_SetInterruptMode(uint16 position, uint16 mode);
uint8   RTC_INTR_PIN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RTC_INTR_PIN_SetDriveMode() function.
     *  @{
     */
        #define RTC_INTR_PIN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RTC_INTR_PIN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RTC_INTR_PIN_DM_RES_UP          PIN_DM_RES_UP
        #define RTC_INTR_PIN_DM_RES_DWN         PIN_DM_RES_DWN
        #define RTC_INTR_PIN_DM_OD_LO           PIN_DM_OD_LO
        #define RTC_INTR_PIN_DM_OD_HI           PIN_DM_OD_HI
        #define RTC_INTR_PIN_DM_STRONG          PIN_DM_STRONG
        #define RTC_INTR_PIN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RTC_INTR_PIN_MASK               RTC_INTR_PIN__MASK
#define RTC_INTR_PIN_SHIFT              RTC_INTR_PIN__SHIFT
#define RTC_INTR_PIN_WIDTH              1u

/* Interrupt constants */
#if defined(RTC_INTR_PIN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RTC_INTR_PIN_SetInterruptMode() function.
     *  @{
     */
        #define RTC_INTR_PIN_INTR_NONE      (uint16)(0x0000u)
        #define RTC_INTR_PIN_INTR_RISING    (uint16)(0x0001u)
        #define RTC_INTR_PIN_INTR_FALLING   (uint16)(0x0002u)
        #define RTC_INTR_PIN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RTC_INTR_PIN_INTR_MASK      (0x01u) 
#endif /* (RTC_INTR_PIN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RTC_INTR_PIN_PS                     (* (reg8 *) RTC_INTR_PIN__PS)
/* Data Register */
#define RTC_INTR_PIN_DR                     (* (reg8 *) RTC_INTR_PIN__DR)
/* Port Number */
#define RTC_INTR_PIN_PRT_NUM                (* (reg8 *) RTC_INTR_PIN__PRT) 
/* Connect to Analog Globals */                                                  
#define RTC_INTR_PIN_AG                     (* (reg8 *) RTC_INTR_PIN__AG)                       
/* Analog MUX bux enable */
#define RTC_INTR_PIN_AMUX                   (* (reg8 *) RTC_INTR_PIN__AMUX) 
/* Bidirectional Enable */                                                        
#define RTC_INTR_PIN_BIE                    (* (reg8 *) RTC_INTR_PIN__BIE)
/* Bit-mask for Aliased Register Access */
#define RTC_INTR_PIN_BIT_MASK               (* (reg8 *) RTC_INTR_PIN__BIT_MASK)
/* Bypass Enable */
#define RTC_INTR_PIN_BYP                    (* (reg8 *) RTC_INTR_PIN__BYP)
/* Port wide control signals */                                                   
#define RTC_INTR_PIN_CTL                    (* (reg8 *) RTC_INTR_PIN__CTL)
/* Drive Modes */
#define RTC_INTR_PIN_DM0                    (* (reg8 *) RTC_INTR_PIN__DM0) 
#define RTC_INTR_PIN_DM1                    (* (reg8 *) RTC_INTR_PIN__DM1)
#define RTC_INTR_PIN_DM2                    (* (reg8 *) RTC_INTR_PIN__DM2) 
/* Input Buffer Disable Override */
#define RTC_INTR_PIN_INP_DIS                (* (reg8 *) RTC_INTR_PIN__INP_DIS)
/* LCD Common or Segment Drive */
#define RTC_INTR_PIN_LCD_COM_SEG            (* (reg8 *) RTC_INTR_PIN__LCD_COM_SEG)
/* Enable Segment LCD */
#define RTC_INTR_PIN_LCD_EN                 (* (reg8 *) RTC_INTR_PIN__LCD_EN)
/* Slew Rate Control */
#define RTC_INTR_PIN_SLW                    (* (reg8 *) RTC_INTR_PIN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RTC_INTR_PIN_PRTDSI__CAPS_SEL       (* (reg8 *) RTC_INTR_PIN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RTC_INTR_PIN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RTC_INTR_PIN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RTC_INTR_PIN_PRTDSI__OE_SEL0        (* (reg8 *) RTC_INTR_PIN__PRTDSI__OE_SEL0) 
#define RTC_INTR_PIN_PRTDSI__OE_SEL1        (* (reg8 *) RTC_INTR_PIN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RTC_INTR_PIN_PRTDSI__OUT_SEL0       (* (reg8 *) RTC_INTR_PIN__PRTDSI__OUT_SEL0) 
#define RTC_INTR_PIN_PRTDSI__OUT_SEL1       (* (reg8 *) RTC_INTR_PIN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RTC_INTR_PIN_PRTDSI__SYNC_OUT       (* (reg8 *) RTC_INTR_PIN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RTC_INTR_PIN__SIO_CFG)
    #define RTC_INTR_PIN_SIO_HYST_EN        (* (reg8 *) RTC_INTR_PIN__SIO_HYST_EN)
    #define RTC_INTR_PIN_SIO_REG_HIFREQ     (* (reg8 *) RTC_INTR_PIN__SIO_REG_HIFREQ)
    #define RTC_INTR_PIN_SIO_CFG            (* (reg8 *) RTC_INTR_PIN__SIO_CFG)
    #define RTC_INTR_PIN_SIO_DIFF           (* (reg8 *) RTC_INTR_PIN__SIO_DIFF)
#endif /* (RTC_INTR_PIN__SIO_CFG) */

/* Interrupt Registers */
#if defined(RTC_INTR_PIN__INTSTAT)
    #define RTC_INTR_PIN_INTSTAT            (* (reg8 *) RTC_INTR_PIN__INTSTAT)
    #define RTC_INTR_PIN_SNAP               (* (reg8 *) RTC_INTR_PIN__SNAP)
    
	#define RTC_INTR_PIN_0_INTTYPE_REG 		(* (reg8 *) RTC_INTR_PIN__0__INTTYPE)
#endif /* (RTC_INTR_PIN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RTC_INTR_PIN_H */


/* [] END OF FILE */
