#ifndef CONCRETESTATEB_H
#define CONCRETESTATEB_H

#include "state.h"

#include <stddef.h>

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */

class ConcreteStateB : public State
{
 public:
  void* operator new(size_t sz);
  void* operator new[](size_t sz);
  void operator delete(void* ptr);
  void operator delete[](void* ptr);
 
  void Handle1() override;
  void Handle2() override;
  const char * Show() override;
};

#endif // CONCRETESTATEB_H
