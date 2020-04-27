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
 * @file    state.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.21
 * @brief   State-machine implementation.
 * @details
 * This file contains the Rhea state-machine utility implementation.
 */

// Project includes
#include "state.h"


rhea_state_stateID rhea_state_nextState(rhea_state_StateMachine *stateMachine, rhea_state_inputID input) {
    
    // Checking input validity
    if(input >= stateMachine->inputCount || stateMachine->currentState > stateMachine->stateCount ||
       !stateMachine->transitions) return stateMachine->currentState;
    
    // Querying current state
    rhea_state_stateID currentState = stateMachine->currentState;
    
    // Querying transition
    uint8_t index = (currentState * stateMachine->inputCount) + input;
    rhea_state_Transition nextTransition = stateMachine->transitions[index];
    
    // Querying next state
    rhea_state_stateID nextState = nextTransition.nextState;
    
    // Performing transition actions
    if(nextTransition.action) nextTransition.action();
    
    // Moving to next state
    stateMachine->currentState = nextState;
    
    return nextState;
}