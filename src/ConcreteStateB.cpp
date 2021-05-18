#include "ConcreteStateA.h"
#include "ConcreteStateB.h"
#include "context.h"
#include <iostream>


void* ConcreteStateB::operator new(size_t sz)
{
  concreteStateBPool & memorypool = concreteStateBPool::GetInstance();
  return memorypool.new_();
}

void* ConcreteStateB::operator new[](size_t sz)
{
  concreteStateBPool & memorypool = concreteStateBPool::GetInstance();
  return memorypool.new_( sz / sizeof ( ConcreteStateB ) );
}

void ConcreteStateB::operator delete(void* ptr)
{
  concreteStateBPool & memorypool = concreteStateBPool::GetInstance();
  return memorypool.delete_( static_cast <ConcreteStateB *> (ptr) );
}

void ConcreteStateB::operator delete[](void* ptr)
{
  concreteStateBPool & memorypool = concreteStateBPool::GetInstance();
  return memorypool.delete_( static_cast <ConcreteStateB *> (ptr) );
}

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
  return "=========\n NO OK   \n=========\n";
}
