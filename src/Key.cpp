/**
  ******************************************************************************
  * @file    Key.cpp
  * @author  Trasterlabs
  * @brief   Where the FSM of the key behaviour takes place.
  ******************************************************************************
  * @attention
  *
  * License Creative Commons CC BY-NC-SA 3.0
  *
  ******************************************************************************
  */

#include "Key.h"

/**
  * @brief  Constructor de la "tecla": utiliza un estado de partida.
  * @param  [in] state El estado de entrada definido por las clases derivadas de KeyState. Por defecto, se introduce el estado NULL
  * @see KeyState
  */
Key::Key (KeyState  *state) : state_(nullptr)
{
  this->TransitionTo(state);
}
Key::~Key ( void )
{
  delete state_;
}

/**
  * @brief  "La transición a" o "transicionar al" es la método que permite saltar de un estado al estado siguiente
  * @param  [in] state El estado de entrada definido por las clases derivadas de KeyState. Por defecto, se introduce el estado NULL
  * @see KeyState
  */
void Key::TransitionTo (KeyState *state)
{
  if (this->state_ != nullptr)
  {
    delete this->state_;
  }
  this->state_ = state;
  this->state_->set_Key(this);
}

void Key::Open ( void )
{
  this->state_->Open();
}
void Key::Closed ( void )
{
  this->state_->Closed();
}
