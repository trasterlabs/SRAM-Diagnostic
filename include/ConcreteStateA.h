#ifndef CONCRETESTATEA_H
#define CONCRETESTATEA_H

#include "state.h"

#include <stddef.h>

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */

class ConcreteStateA : public State
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

#endif // CONCRETESTATEA_H
