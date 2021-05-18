#include "ConcreteStateA.h"
#include "ConcreteStateB.h"
#include "context.h"
#include <iostream>

#include "StaticMemoryPool.h"

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
  std::cout << "ConcreteStateA: request1.\n";
  std::cout << "ConcreteStateA: trying to change the state of the context.\n";

  this->context_->TransitionTo(new ConcreteStateB);
}
void ConcreteStateA::Handle2()
{
  std::cout << "ConcreteStateA: request2.\n";
}

const char * ConcreteStateA::Show()
{
  return "=========\n Todo OK \n=========\n";
}
