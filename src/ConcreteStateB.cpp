#include "StaticMemoryPool.hpp"
#include "ConcreteStateB.h"
#include "ConcreteStateA.h"
#include "context.h"

#ifdef PC_OUTPUT
#include <iostream>
#endif

typedef MemoryPool<ConcreteStateB,3> concreteStateBPool;


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
#ifdef PC_OUTPUT
  std::cout << "ConcreteStateB: request1.\n";
#endif
}
void ConcreteStateB::Handle2()
{
#ifdef PC_OUTPUT
  std::cout << "ConcreteStateB: request2.\n";
  std::cout << "ConcreteStateB: trying to change the state of the context.\n";
#endif
  this->context_->TransitionTo(new ConcreteStateA);
}
const char * ConcreteStateB::Show()
{
  return "=========\n NO OK   \n=========\n";
}
