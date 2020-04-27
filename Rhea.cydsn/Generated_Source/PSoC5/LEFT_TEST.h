/*******************************************************************************
* File Name: LEFT_TEST.h  
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

#if !defined(CY_PINS_LEFT_TEST_H) /* Pins LEFT_TEST_H */
#define CY_PINS_LEFT_TEST_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEFT_TEST_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEFT_TEST__PORT == 15 && ((LEFT_TEST__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LEFT_TEST_Write(uint8 value);
void    LEFT_TEST_SetDriveMode(uint8 mode);
uint8   LEFT_TEST_ReadDataReg(void);
uint8   LEFT_TEST_Read(void);
void    LEFT_TEST_SetInterruptMode(uint16 position, uint16 mode);
uint8   LEFT_TEST_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LEFT_TEST_SetDriveMode() function.
     *  @{
     */
        #define LEFT_TEST_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LEFT_TEST_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LEFT_TEST_DM_RES_UP          PIN_DM_RES_UP
        #define LEFT_TEST_DM_RES_DWN         PIN_DM_RES_DWN
        #define LEFT_TEST_DM_OD_LO           PIN_DM_OD_LO
        #define LEFT_TEST_DM_OD_HI           PIN_DM_OD_HI
        #define LEFT_TEST_DM_STRONG          PIN_DM_STRONG
        #define LEFT_TEST_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LEFT_TEST_MASK               LEFT_TEST__MASK
#define LEFT_TEST_SHIFT              LEFT_TEST__SHIFT
#define LEFT_TEST_WIDTH              1u

/* Interrupt constants */
#if defined(LEFT_TEST__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LEFT_TEST_SetInterruptMode() function.
     *  @{
     */
        #define LEFT_TEST_INTR_NONE      (uint16)(0x0000u)
        #define LEFT_TEST_INTR_RISING    (uint16)(0x0001u)
        #define LEFT_TEST_INTR_FALLING   (uint16)(0x0002u)
        #define LEFT_TEST_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LEFT_TEST_INTR_MASK      (0x01u) 
#endif /* (LEFT_TEST__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEFT_TEST_PS                     (* (reg8 *) LEFT_TEST__PS)
/* Data Register */
#define LEFT_TEST_DR                     (* (reg8 *) LEFT_TEST__DR)
/* Port Number */
#define LEFT_TEST_PRT_NUM                (* (reg8 *) LEFT_TEST__PRT) 
/* Connect to Analog Globals */                                                  
#define LEFT_TEST_AG                     (* (reg8 *) LEFT_TEST__AG)                       
/* Analog MUX bux enable */
#define LEFT_TEST_AMUX                   (* (reg8 *) LEFT_TEST__AMUX) 
/* Bidirectional Enable */                                                        
#define LEFT_TEST_BIE                    (* (reg8 *) LEFT_TEST__BIE)
/* Bit-mask for Aliased Register Access */
#define LEFT_TEST_BIT_MASK               (* (reg8 *) LEFT_TEST__BIT_MASK)
/* Bypass Enable */
#define LEFT_TEST_BYP                    (* (reg8 *) LEFT_TEST__BYP)
/* Port wide control signals */                                                   
#define LEFT_TEST_CTL                    (* (reg8 *) LEFT_TEST__CTL)
/* Drive Modes */
#define LEFT_TEST_DM0                    (* (reg8 *) LEFT_TEST__DM0) 
#define LEFT_TEST_DM1                    (* (reg8 *) LEFT_TEST__DM1)
#define LEFT_TEST_DM2                    (* (reg8 *) LEFT_TEST__DM2) 
/* Input Buffer Disable Override */
#define LEFT_TEST_INP_DIS                (* (reg8 *) LEFT_TEST__INP_DIS)
/* LCD Common or Segment Drive */
#define LEFT_TEST_LCD_COM_SEG            (* (reg8 *) LEFT_TEST__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEFT_TEST_LCD_EN                 (* (reg8 *) LEFT_TEST__LCD_EN)
/* Slew Rate Control */
#define LEFT_TEST_SLW                    (* (reg8 *) LEFT_TEST__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEFT_TEST_PRTDSI__CAPS_SEL       (* (reg8 *) LEFT_TEST__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEFT_TEST_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEFT_TEST__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEFT_TEST_PRTDSI__OE_SEL0        (* (reg8 *) LEFT_TEST__PRTDSI__OE_SEL0) 
#define LEFT_TEST_PRTDSI__OE_SEL1        (* (reg8 *) LEFT_TEST__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEFT_TEST_PRTDSI__OUT_SEL0       (* (reg8 *) LEFT_TEST__PRTDSI__OUT_SEL0) 
#define LEFT_TEST_PRTDSI__OUT_SEL1       (* (reg8 *) LEFT_TEST__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEFT_TEST_PRTDSI__SYNC_OUT       (* (reg8 *) LEFT_TEST__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LEFT_TEST__SIO_CFG)
    #define LEFT_TEST_SIO_HYST_EN        (* (reg8 *) LEFT_TEST__SIO_HYST_EN)
    #define LEFT_TEST_SIO_REG_HIFREQ     (* (reg8 *) LEFT_TEST__SIO_REG_HIFREQ)
    #define LEFT_TEST_SIO_CFG            (* (reg8 *) LEFT_TEST__SIO_CFG)
    #define LEFT_TEST_SIO_DIFF           (* (reg8 *) LEFT_TEST__SIO_DIFF)
#endif /* (LEFT_TEST__SIO_CFG) */

/* Interrupt Registers */
#if defined(LEFT_TEST__INTSTAT)
    #define LEFT_TEST_INTSTAT            (* (reg8 *) LEFT_TEST__INTSTAT)
    #define LEFT_TEST_SNAP               (* (reg8 *) LEFT_TEST__SNAP)
    
	#define LEFT_TEST_0_INTTYPE_REG 		(* (reg8 *) LEFT_TEST__0__INTTYPE)
#endif /* (LEFT_TEST__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEFT_TEST_H */


/* [] END OF FILE */
