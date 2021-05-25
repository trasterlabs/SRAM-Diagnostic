#ifndef KEYSTATERELEASED_H
#define KEYSTATERELEASED_H

#include "KeyState.h"

#include <stddef.h>


class KeyStateRELEASED : public KeyState
{
 public:
  void* operator new(size_t sz);
  void* operator new[](size_t sz);
  void operator delete(void* ptr);
  void operator delete[](void* ptr);

  void Open() override;

  void Closed() override;
  
};

#endif // KEYSTATERELEASED_H
