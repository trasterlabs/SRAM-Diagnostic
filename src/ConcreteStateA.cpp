#include "StaticMemoryPool.hpp"
#include "ConcreteStateA.h"
#include "ConcreteStateB.h"
#include "context.h"

#ifdef PC_OUTPUT
#include <iostream>
#endif

typedef MemoryPool<ConcreteStateA,3> concreteStateAPool;

void* ConcreteStateA::operator new(size_t sz)
{
  concreteStateAPool & memorypool = concreteStateAPool::GetInstance();
  return memorypool.new_();
}

void* ConcreteStateA::operator new[](size_t sz)
{
  concreteStateAPool & memorypool = concreteStateAPool::GetInstance();
  return memorypool.new_( sz / sizeof ( ConcreteStateA ) );
}

void ConcreteStateA::operator delete(void* ptr)
{
  concreteStateAPool & memorypool = concreteStateAPool::GetInstance();
  return memorypool.delete_( static_cast <ConcreteStateA *> (ptr) );
}

void ConcreteStateA::operator delete[](void* ptr)
{
  concreteStateAPool & memorypool = concreteStateAPool::GetInstance();
  return memorypool.delete_( static_cast <ConcreteStateA *> (ptr) );
}

void ConcreteStateA::Handle1()
{
#ifdef PC_OUTPUT
  std::cout << "ConcreteStateA: request1.\n";
  std::cout << "ConcreteStateA: trying to change the state of the context.\n";
#endif

  this->context_->TransitionTo(new ConcreteStateB);
}
void ConcreteStateA::Handle2()
{
#ifdef PC_OUTPUT
  std::cout << "ConcreteStateA: request2.\n";
#endif
}

const char * ConcreteStateA::Show()
{
  return "=========\n Todo OK \n=========\n";
}
