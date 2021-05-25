#include "key.h"
#include <iostream>

Key::Key (KeyState  *state) : state_(nullptr)
{
  this->TransitionTo(state);
}
Key::~Key ( void )
{
  delete state_;
}

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
