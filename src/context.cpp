#include "StaticMemoryPool.hpp"
#include "context.h"
#include <iostream>
#include <typeinfo>

typedef MemoryPool<Context,3> contextPool;

void* Context::operator new(size_t sz)
{
  contextPool & memorypool = contextPool::GetInstance();
  return memorypool.new_();
}

void* Context::operator new[](size_t sz)
{
  contextPool & memorypool = contextPool::GetInstance();
  return memorypool.new_( sz / sizeof ( Context ) );
}

void Context::operator delete(void* ptr)
{
  contextPool & memorypool = contextPool::GetInstance();
  return memorypool.delete_( static_cast <Context *> (ptr) );
}

void Context::operator delete[](void* ptr)
{
  contextPool & memorypool = contextPool::GetInstance();
  return memorypool.delete_( static_cast <Context *> (ptr) );
}

Context::Context (State *state) : state_(state)
{
  this->TransitionTo(state);
}
Context::~Context ( void )
{
  delete state_;
}

void Context::TransitionTo (State *state)
{
  if (this->state_ != nullptr)
  {
    std::cout << "Context: Transition to " << typeid(state[0]).name() << ".\n";
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

const char * Context::ShowScreen()
{
    return this->state_->Show();
}
