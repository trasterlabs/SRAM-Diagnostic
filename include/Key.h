/**
  ******************************************************************************
  * @file    key.h
  * @author  Trasterlabs
  * @brief   Header file of the button state pattern.
  ******************************************************************************
  *
  * @attention
  *
  * License Creative Commons CC BY-NC-SA 3.0
  *
  ******************************************************************************
  */

#ifndef KEY_H
#define KEY_H

#include "state.h"


/**
 * Each key must be defined with a state pattern with 4 subclasses which are determined state.
 */
class Key
{
 private:
  KeyState *state_;

 public:
  Key(KeyState *state);
  ~Key();
  
  void TransitionTo(KeyState *state);
  
  // When the key is opened
  void Open();
  // when the key is closed
  void Closed();
};

#endif // KEY_H
