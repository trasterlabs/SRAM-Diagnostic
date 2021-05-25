#include "StaticMemoryPool.hpp"
#include "KeyStateIDLE.h"
#include "KeyStatePRESSED.h"
#include "Key.h"

#ifdef PC_OUTPUT
#include <iostream>
#endif

typedef MemoryPool<KeyStateIDLE,3> KeyStateIDLEPool;

void* KeyStateIDLE::operator new(size_t sz)
{
  KeyStateIDLEPool & memorypool = KeyStateIDLEPool::GetInstance();
  return memorypool.new_();
}

void* KeyStateIDLE::operator new[](size_t sz)
{
  KeyStateIDLEPool & memorypool = KeyStateIDLEPool::GetInstance();
  return memorypool.new_( sz / sizeof ( KeyStateIDLE ) );
}

void KeyStateIDLE::operator delete(void* ptr)
{
  KeyStateIDLEPool & memorypool = KeyStateIDLEPool::GetInstance();
  return memorypool.delete_( static_cast <KeyStateIDLE *> (ptr) );
}

void KeyStateIDLE::operator delete[](void* ptr)
{
  KeyStateIDLEPool & memorypool = KeyStateIDLEPool::GetInstance();
  return memorypool.delete_( static_cast <KeyStateIDLE *> (ptr) );
}

void KeyStateIDLE::Closed()
{
#ifdef PC_OUTPUT
  std::cout << "KeyStateIDLE: closed key.\n";
  std::cout << "KeyStateIDLE: trying to change the state of the context.\n";
#endif

  this->Key_->TransitionTo(new KeyStatePRESSED);
}
void KeyStateIDLE::Open()
{
#ifdef PC_OUTPUT
  std::cout << "KeyStateIDLE: opened key.\n";
#endif
}
