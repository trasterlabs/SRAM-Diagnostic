/**
  ******************************************************************************
  * @file    keystate.h
  * @author  trasterlabs
  * @brief   Implementation of the state pattern of a key button.
  ******************************************************************************
  */

#ifndef KEYSTATE_H
#define KEYSTATE_H

class Key;

class KeyState
{
  /**
   * @var Context
   */
 protected:
  Key *Key_;

 public:
  virtual ~KeyState() {}

  void set_Key(Key *key);

  virtual void Open() = 0;
  virtual void Closed() = 0;
};

#endif // KEYSTATE_H
