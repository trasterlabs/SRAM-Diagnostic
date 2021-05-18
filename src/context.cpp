#include "context.h"
#include <iostream>
#include <typeinfo>

Context::Context (State *state) : state_(nullptr)
{
  this->TransitionTo(state);
}
Context::~Context ( void )
{
  delete state_;
}

void Context::TransitionTo (State *state)
{
  std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
  if (this->state_ != nullptr)
  {
    delete this->state_;
  }
  this->state_ = state;
  this->state_->set_context(this);
}
void Context::Request1 ( void )
{
  this->state_->Handle1();
}
void Context::Request2 ( void )
{
  this->state_->Handle2();
}

const char * ShowScreen()
{
    this->state_->Show();
}
