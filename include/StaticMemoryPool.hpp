/**
  ******************************************************************************
  * @file    StaticMemoryPool.hpp
  * @author  Trasterlabs
  * @brief   Memory Pool using static memory to surpass the new funcitonalty.
  ******************************************************************************
  * @attention
  *
  * License Creative Commons CC BY-NC-SA 3.0
  *
  ******************************************************************************
  */


class MemoryPool
{
protected:
  /**
   * El constructor de MemoryPool debería ser siempre privado para
   * prevenir que nadie pueda hacer un new
   */
  MemoryPool(){}
public:
  /**
   * Como MemoryPool es un singleton, los singletons, en general, no deberían ser clonables
   */
  MemoryPool (MemoryPool &loquesea) = delete;
  /**
   * Como MemoryPool es un singleton, los singletons, en general, no deberían ser asignables
   */
  void operator = (const MemoryPool &) = delete;
  
  /**
   * The big mother of lamb: el método estático que controla el acceso a la "instancia" del singleton.
   * La instancia es el objeto a representar. La primera vez que se ejecute,
   * se "crea" un objeto que será el que se devuelva SIEMPRE.
   * En las consecutivas llamadas, se devolverá el mismo objeto que se creó la primera vez,
   * de modo que siempre se devueva de forma estática.
   */
  static MemoryPool & GetInstance();
  
  /**
   * LA LÓGICA DE NEGOCIO
   */
};
