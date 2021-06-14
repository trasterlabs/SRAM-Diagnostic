/**
  ******************************************************************************
  * @file    stm32f4xx_hal.c
  * @author  Trasterlabs
  * @brief   The state when the key is being pressed between readings
  *
  ******************************************************************************
  * @attention
  *
  * License Creative Commons CC BY-NC-SA 3.0
  *
  ******************************************************************************
  */

// Para fingir las llamadas a new y delete utilizando la memoria estática en vez de la dinámica
#include "StaticMemoryPool.hpp"

// Para hacer la transición a los estados que correspondan, hará falta que se incluyan como elementos externos.
// Los estados son elementos externos a la máquina de estados, ya que la máquina de estados es la que transiciona, no posee estados
#include "KeyStateHOLD.h"
#include "KeyStateRELEASED.h"

// Para albergar la máquina de estados que se va a utilizar con KeyStateHOLD.
#include "Key.h"

// Si tuviéramos opciones para mostrar en PC
#ifdef PC_OUTPUT
#include <iostream>
#endif

/**
  * @brief El lugar donde se almacena el singleton que permite la gestión estática de memoria dinámica.
  * Se utiliza una plantilla (template) para generar de forma estática un array de 3 elementos que guardará el new cuando se realice un new
  */
typedef MemoryPool<KeyStateHOLD,3> KeyStateHOLDPool;

/** @defgroup NEW_PACKAGE 
  * @brief Conjunto de llamadas a fingir el new, pero usando memoria estática.
  * @{
  */

/**
  * @brief Emulador del new de un único elemento
  */
void* KeyStateHOLD::operator new(size_t sz)
{
  KeyStateHOLDPool & memorypool = KeyStateHOLDPool::GetInstance();
  return memorypool.new_();
}

/**
  * @brief Emulador del new de un array de elementos
  */
void* KeyStateHOLD::operator new[](size_t sz)
{
  KeyStateHOLDPool & memorypool = KeyStateHOLDPool::GetInstance();
  return memorypool.new_( sz / sizeof ( KeyStateHOLD ) );
}

/**
  * @brief Emulador del delete de un único elemento
  */
void KeyStateHOLD::operator delete(void* ptr)
{
  KeyStateHOLDPool & memorypool = KeyStateHOLDPool::GetInstance();
  return memorypool.delete_( static_cast <KeyStateHOLD *> (ptr) );
}

/**
  * @brief Emulador del delete de un array de elementos
  */
void KeyStateHOLD::operator delete[](void* ptr)
{
  KeyStateHOLDPool & memorypool = KeyStateHOLDPool::GetInstance();
  return memorypool.delete_( static_cast <KeyStateHOLD *> (ptr) );
}

/**
  * @}
  */

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
