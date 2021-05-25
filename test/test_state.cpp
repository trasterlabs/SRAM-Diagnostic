#include <iostream>

#include "gtest/gtest.h"

#include "context.h"
#include "ConcreteStateA.h"
#include "ConcreteStateB.h"

#if 0
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
#endif

TEST(Screen_functionality, Screen01_test)
{
  //Arrange
  Context *context = new Context(new ConcreteStateA);
  //Act
  const char * prueba = context->ShowScreen();
  //Assert
  EXPECT_STREQ( prueba, "=========\n Todo OK \n=========\n" );
}

TEST(Screen_functionality, Screen02_test)
{
  //Arrange
  Context *context = new Context(new ConcreteStateB);
  //Act
  const char * prueba = context->ShowScreen();
  //Assert
  EXPECT_STREQ( prueba, "=========\n NO OK   \n=========\n" );
}

