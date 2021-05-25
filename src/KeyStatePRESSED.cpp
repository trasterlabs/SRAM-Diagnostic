#include "StaticMemoryPool.hpp"
#include "KeyStatePRESSED.h"
#include "KeyStateHOLD.h"
#include "KeyStateRELEASED.h"
#include "Key.h"

#ifdef PC_OUTPUT
#include <iostream>
#endif

typedef MemoryPool<KeyStatePRESSED,3> KeyStatePRESSEDPool;

void* KeyStatePRESSED::operator new(size_t sz)
{
  KeyStatePRESSEDPool & memorypool = KeyStatePRESSEDPool::GetInstance();
  return memorypool.new_();
}

void* KeyStatePRESSED::operator new[](size_t sz)
{
  KeyStatePRESSEDPool & memorypool = KeyStatePRESSEDPool::GetInstance();
  return memorypool.new_( sz / sizeof ( KeyStatePRESSED ) );
}

void KeyStatePRESSED::operator delete(void* ptr)
{
  KeyStatePRESSEDPool & memorypool = KeyStatePRESSEDPool::GetInstance();
  return memorypool.delete_( static_cast <KeyStatePRESSED *> (ptr) );
}

void KeyStatePRESSED::operator delete[](void* ptr)
{
  KeyStatePRESSEDPool & memorypool = KeyStatePRESSEDPool::GetInstance();
  return memorypool.delete_( static_cast <KeyStatePRESSED *> (ptr) );
}

void KeyStatePRESSED::Open()
{
#ifdef PC_OUTPUT
  std::cout << "KeyStatePRESSED: opened key.\n";
  std::cout << "KeyStatePRESSED: trying to change the state of the context.\n";
#endif

  this->Key_->TransitionTo(new KeyStateRELEASED);
}

void KeyStatePRESSED::Closed()
{
#ifdef PC_OUTPUT
  std::cout << "KeyStatePRESSED: closed key.\n";
  std::cout << "KeyStatePRESSED: trying to change the state of the context.\n";
#endif

  this->Key_->TransitionTo(new KeyStateHOLD);
}
