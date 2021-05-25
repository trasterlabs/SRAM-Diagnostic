#include "StaticMemoryPool.hpp"
#include "KeyStatePRESSED.h"
#include "KeyStateIDLE.h"
#include "KeyStateRELEASED.h"
#include "Key.h"

#ifdef PC_OUTPUT
#include <iostream>
#endif

typedef MemoryPool<KeyStateRELEASED,3> KeyStateRELEASEDPool;

void* KeyStateRELEASED::operator new(size_t sz)
{
  KeyStateRELEASEDPool & memorypool = KeyStateRELEASEDPool::GetInstance();
  return memorypool.new_();
}

void* KeyStateRELEASED::operator new[](size_t sz)
{
  KeyStateRELEASEDPool & memorypool = KeyStateRELEASEDPool::GetInstance();
  return memorypool.new_( sz / sizeof ( KeyStateRELEASED ) );
}

void KeyStateRELEASED::operator delete(void* ptr)
{
  KeyStateRELEASEDPool & memorypool = KeyStateRELEASEDPool::GetInstance();
  return memorypool.delete_( static_cast <KeyStateRELEASED *> (ptr) );
}

void KeyStateRELEASED::operator delete[](void* ptr)
{
  KeyStateRELEASEDPool & memorypool = KeyStateRELEASEDPool::GetInstance();
  return memorypool.delete_( static_cast <KeyStateRELEASED *> (ptr) );
}

void KeyStateRELEASED::Open()
{
#ifdef PC_OUTPUT
  std::cout << "KeyStateRELEASED: opened key.\n";
  std::cout << "KeyStateRELEASED: trying to change the state of the context.\n";
#endif

  this->Key_->TransitionTo(new KeyStateIDLE);
}

void KeyStateRELEASED::Closed()
{
#ifdef PC_OUTPUT
  std::cout << "KeyStateRELEASED: closed key.\n";
  std::cout << "KeyStateRELEASED: trying to change the state of the context.\n";
#endif

  this->Key_->TransitionTo(new KeyStatePRESSED);
}
