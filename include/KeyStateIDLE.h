#ifndef KEYSTATEIDLE_H
#define KEYSTATEIDLE_H

#include "KeyState.h"

#include <stddef.h>

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */

class KeyStateIDLE : public KeyState
{
 public:
  void* operator new(size_t sz);
  void* operator new[](size_t sz);
  void operator delete(void* ptr);
  void operator delete[](void* ptr);

  void Open() override;

  void Closed() override;
  
};

#endif // KEYSTATEIDLE_H
