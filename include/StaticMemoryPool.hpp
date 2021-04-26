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

/**
 * Guía de uso:
 * Si yo necesito crear un memoryPool de <INTS> y con 30 ELEMENTOS
 * MemoryPool <int, 30> Gregory;
 * Gregory.GetInstance().create(5);
 * MemoryPool <int, 30> & Martha = MemoryPool <int, 30>::GetInstance();
 * Martha.create(5);
 */


template <typename theType, unsigned int numberOfElements>
class MemoryPool
{
private:
  theType the_pool      [numberOfElements]; /*!< Where the <new> and <delete> will be */
  uint8_t elements_used [numberOfElements]; /*!< The elements used */
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
   * Finally, any singleton should define some business logic, which can be
   * executed on its instance.
   */
  /**
   * @brief static allocation for sustitution of the new operator
   * @param i the number of elements to be returned
   * @return the pointer to the static array location
   */
  theType * new_ (unsigned int size = 1);
  void delete_ (theType * array_to_be_deleted, bool is_an_array = true, unsigned int how_many_elements = 1);L
};

template <typename T, unsigned int N>
MemoryPool < T, N > & MemoryPool < T, N >::GetInstance()
{
  static MemoryPool < T, N > instance;
  return instance;
}


