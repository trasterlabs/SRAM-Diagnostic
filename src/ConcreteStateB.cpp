#include "ConcreteStateA.h"
#include "ConcreteStateB.h"
#include "context.h"
#include <iostream>


void ConcreteStateB::Handle1()
{
  std::cout << "ConcreteStateB: request1.\n";
}
void ConcreteStateB::Handle2()
{
  std::cout << "ConcreteStateB: request2.\n";
  std::cout << "ConcreteStateB: trying to change the state of the context.\n";
  this->context_->TransitionTo(new ConcreteStateA);
}
const char * ConcreteStateB::Show()
{
  return "esto no debería verse";
}
