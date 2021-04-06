#include <iostream>
#include "Context.h"
#include "ConcreteStateA.h"

/**
 * The client code.
 */
void ClientCode()
{
  Context *context = new Context(new ConcreteStateA);
  context->Request1();
  context->Request2();
  delete context;
}

int main ( void )
{
  ClientCode();
  return 0;
}
