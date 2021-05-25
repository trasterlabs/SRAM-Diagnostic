#ifndef KEYSTATEPRESSED_H
#define KEYSTATEPRESSED_H

#include "KeyState.h"

#include <stddef.h>

class KeyStatePRESSED : public KeyState
{
 public:
  void* operator new(size_t sz);
  void* operator new[](size_t sz);
  void operator delete(void* ptr);
  void operator delete[](void* ptr);

  void Open() override;

  void Closed() override;
  
};

#endif // KEYSTATEPRESSED_H
