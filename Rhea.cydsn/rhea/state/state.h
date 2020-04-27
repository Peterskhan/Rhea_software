#pragma once
#ifndef RHEA_STATE_H_INCLUDED
#define RHEA_STATE_H_INCLUDED

/*********************************************************************************
 * Copyright (c) 2020 Peter Gyulai
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
**********************************************************************************/

/**
 * @file    state.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.21
 * @brief   State-machine utilities.
 * @details
 * This file contains utility types and functions to represent state-machines.
 */
    
// Standard includes
#include <stdint.h>
    
    
/** @brief Defines an action performed on state transition. */
typedef void(*rhea_state_action)(void);

/** @brief Defines the identifier of a State. */
typedef uint8_t rhea_state_stateID;

/** @brief Defines the identifier of an Input. */
typedef uint8_t rhea_state_inputID;
   
/** @brief Defines a Transition between States. */
typedef struct rhea_state_Transition {
    rhea_state_stateID      nextState;  /**< The next State after the Transition.       */
    rhea_state_action       action;     /**< The action performed upon the Transition.  */
} rhea_state_Transition;
    
/** @brief Defines a complete StateMachine. */
typedef struct rhea_state_StateMachine {
    rhea_state_Transition*  transitions;    /**< 2D table of Transitions, rows are States, colums are Inputs.   */
    rhea_state_stateID      currentState;   /**< The identifier of the current State.                           */
    rhea_state_stateID      stateCount;     /**< The total number of States in the StateMachine.                */
    rhea_state_inputID      inputCount;     /**< The total number of Inputs for the Statemachine.               */
} rhea_state_StateMachine;

/**
 * @brief Advances the specified StateMachine to the next State,
 * according to the specified Input, and returns the next State.
 * @param [in] stateMachine Pointer to the StateMachine.
 * @param [in] input The input to the StateMachine.
 * @returns The identifier of the State the StateMachine transitioned into.
 */
rhea_state_stateID rhea_state_nextState(rhea_state_StateMachine *stateMachine, rhea_state_inputID input);

#endif // RHEA_STATE_H_INCLUDED
