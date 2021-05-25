#include "StaticMemoryPool.hpp"
#include "KeyStateHOLD.h"
#include "KeyStateRELEASED.h"
#include "Key.h"

#ifdef PC_OUTPUT
#include <iostream>
#endif

typedef MemoryPool<KeyStateHOLD,3> KeyStateHOLDPool;

void* KeyStateHOLD::operator new(size_t sz)
{
  KeyStateHOLDPool & memorypool = KeyStateHOLDPool::GetInstance();
  return memorypool.new_();
}

void* KeyStateHOLD::operator new[](size_t sz)
{
  KeyStateHOLDPool & memorypool = KeyStateHOLDPool::GetInstance();
  return memorypool.new_( sz / sizeof ( KeyStateHOLD ) );
}

void KeyStateHOLD::operator delete(void* ptr)
{
  KeyStateHOLDPool & memorypool = KeyStateHOLDPool::GetInstance();
  return memorypool.delete_( static_cast <KeyStateHOLD *> (ptr) );
}

void KeyStateHOLD::operator delete[](void* ptr)
{
  KeyStateHOLDPool & memorypool = KeyStateHOLDPool::GetInstance();
  return memorypool.delete_( static_cast <KeyStateHOLD *> (ptr) );
}

void KeyStateHOLD::Open()
{
#ifdef PC_OUTPUT
  std::cout << "KeyStateHOLD: opened key.\n";
  std::cout << "KeyStateHOLD: trying to change the state of the context.\n";
#endif

  this->Key_->TransitionTo(new KeyStateRELEASED);
}

void KeyStateHOLD::Closed()
{
#ifdef PC_OUTPUT
  std::cout << "KeyStateHOLD: closed key.\n";
  std::cout << "KeyStateHOLD: trying to change the state of the context.\n";
#endif

  this->Key_->TransitionTo(new KeyStateHOLD);
}
