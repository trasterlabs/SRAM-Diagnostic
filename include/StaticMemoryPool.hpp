/**
  ******************************************************************************
  * @file    StaticMemoryPool.hpp
  * @author  Trasterlabs
  * @brief   Memory Pool using static memory to override the new funcitonalty.
  ******************************************************************************
  * @attention
  *
  * License Creative Commons CC BY-NC-SA 3.0
  *
  ******************************************************************************
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
   * This is the static method that controls the access to the singleton
   * instance. On the first run, it creates a singleton object and places it
   * into the static field. On subsequent runs, it returns the client existing
   * object stored in the static field.
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
  void delete_ (theType * array_to_be_deleted, bool is_an_array = true, unsigned int how_many_elements = 1);
  void freeing_the (theType * array_to_be_deleted, unsigned int the_position_to_delete, unsigned int how_many_elements);
  unsigned int find_the_position_in_the_pool (theType * the_array);
  void markTheElementsToBeAllocated (unsigned int position, unsigned int places);
  unsigned int countMaxFreeConsecutiveElements ()
  {
    unsigned int max_consecutive = 0;
    unsigned int total_free_elements = 0;
    for ( unsigned int i = 0; i < numberOfElements; i++ )
    {
      if ( ( this->element_used[i] != 0 ) && ( total_free_elements > max_consecutive ) )
      {
        max_consecutive = total_free_elements;
      }
      total_free_elements = ( this->element_used[i] != 0 )? 0 : total_free_elements + 1;
    }
    if ( total_free_elements > max_consecutive )
    {
        max_consecutive = total_free_elements;
    }
    return max_consecutive;
  }
  unsigned int nextAvailablePositionIncludingFrom (unsigned int position);
  unsigned int nextOccupiedPositionIncludingFrom (unsigned int position);
  bool isPositionInsideMemoryPool (unsigned int position);
  unsigned int firstAvailableBuffer (unsigned int size_of_the_desired_buffer);
  void showTheElementsUsed ();
  #ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
  theType * ReceiveThePool ()
  {
    return &(this->the_pool[0]);
  }
  uint8_t * ReceiveElementsUsed ()
  {
    return &(this->elements_used[0]);
  }
  #endif
};

/**
 * Static methods should be defined outside the class.
 */
template <typename T, unsigned int N>
MemoryPool < T, N > & MemoryPool < T, N >::GetInstance()
{
  static MemoryPool < T, N > instance;
  return instance;
}


