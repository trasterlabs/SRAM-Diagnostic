/**
  ******************************************************************************
  * @file    key.h
  * @author  Trasterlabs
  * @brief   Header file of the key state pattern.
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

#include "KeyState.h"


/**
 * @brief La clase key forma parte del patrón estado. Es donde se almacena el estado actual de la máquina de estado y permite la transición a nuevos estados.
 * @warning La clase key no ejecuta el contenido de ningún estado. Sólo almacena el estado actual de la FSM
 */
class Key
{
 private:
  KeyState *state_; /*!< El estado que tiene guardado para ejecutar */

 public:
  /**
   * @brief Constructor chachi que permite empezar la máquina de estados @p Key en un estado @p KeyState definido
   * @see KeyState
   */
  Key(KeyState *state);
  ~Key();
  
  /**
   * @brief "transiciona a" o "hace una transición a"; es el método que permite realizar una transición al siguiente estado en la máquina de estados @p Key
   * @param [in] state El nuevo @p KeyState que va a almacenarse en la FSM
   */
  void TransitionTo(KeyState *state);
  
  /** @defgroup KEY_BUSINESS_LAYER 
  * @brief Business layer of a key.
  * @{
  */
  // When the key is opened
  void Open();
  // when the key is closed
  void Closed();
  
  /**
    * @}
    */
};

#endif // KEY_H
