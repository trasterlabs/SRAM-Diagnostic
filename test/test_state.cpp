#include <iostream>

#include "gtest/gtest.h"

#include "context.h"
#include "ConcreteStateA.h"

TEST(Methods_random, Basic_functionality)
{
  Context *context = new Context(new ConcreteStateA);
  context->Request1();
  context->Request1();
  context->Request2();
  context->Request2();
  context->Request1();
  delete context;
}
