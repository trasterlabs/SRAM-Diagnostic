#include "state.h"

typedef MemoryPool<State,3> StatePool;

void* State::operator new(size_t sz)
{
  StatePool & memorypool = StatePool::GetInstance();
  return memorypool.new_();
}

void* State::operator new[](size_t sz)
{
  StatePool & memorypool = StatePool::GetInstance();
  return memorypool.new_( sz / sizeof ( State ) );
}

void State::operator delete(void* ptr)
{
  StatePool & memorypool = StatePool::GetInstance();
  return memorypool.delete_( static_cast <State *> (ptr) );
}

void State::operator delete[](void* ptr)
{
  StatePool & memorypool = StatePool::GetInstance();
  return memorypool.delete_( static_cast <State *> (ptr) );
}

void State::set_context(Context *context)
{
  this->context_ = context;
}
