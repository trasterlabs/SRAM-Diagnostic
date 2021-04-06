#include "ConcreteStateA.h"
#include "ConcreteStateB.h"
#include "Context.h"

void ConcreteStateA::Handle1()
{
  std::cout << "ConcreteStateA: request1.\n";
  std::cout << "ConcreteStateA: trying to change the state of the context.\n";

  this->context_->TransitionTo(new ConcreteStateB);
}
void ConcreteStateA::Handle2()
{
  std::cout << "ConcreteStateA: request2.\n";
}
