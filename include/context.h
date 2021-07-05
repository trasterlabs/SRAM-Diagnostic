#ifndef CONTEXT_H
#define CONTEXT_H

#include "state.h"

#include <stddef.h>


/**
 * The Context defines the interface of interest to clients. It also maintains a
 * reference to an instance of a State subclass, which represents the current
 * state of the Context.
 */
class Context {
  /**
   * @var State A reference to the current state of the Context.
   */
 private:
  State *state_;

 public:
  void* operator new(size_t sz);
  void* operator new[](size_t sz);
  void operator delete(void* ptr);
  void operator delete[](void* ptr);

  Context(State *state);
  ~Context();
  /**
   * The Context allows changing the State object at runtime.
   */
  void TransitionTo(State *state);
  /**
   * The Context delegates part of its behavior to the current State object.
   */
  void Request1();
  void Request2();
  const char * ShowScreen();
};

#endif // CONTEXT_H
