/**
 * listado de pruebas para asegurar el funcionamiento de un mempool
 * ¿Qué es un mempool? Es un bufer estático de memoria donde hay un tipo asignado y cada vez que alguien trate de borrar o crear un objeto, sustituya el comportamiento de new y delete para evitar usar memoria dinámica.
 */

/**
 * +---+---+---+---+---+---+---+---+---+----+
 * | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | <- Tipo de objeto que irá sustituyendo a new y delete
 * +===+===+===+===+===+===+===+===+===+====+
 * | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |  0 | <- Cuántos objetos hay seguidos
 * +---+---+---+---+---+---+---+---+---+----+
 */

#include "gtest/gtest.h"
#include "StaticMemoryPool.hpp"

#define NELMS 10

typedef MemoryPool<int, NELMS> intPool;

class MemPoolTestingFixture : public testing::Test
{
protected:
  void SetUp () override
  {
    pool_elements = intPool::ReceiveThePool();
    pool_elements_used = intPool::ReceiveElementsUsed();
    for ( int i = 0; i < NELMS; i++ )
    {
      pool_elements[i] = 0;
    }
    for ( int i = 0; i < NELMS; i++ )
    {
      pool_elements_used[i] = 0;
    }
  }
  
  intPool the_pool;
  int * pool_elements;
  uint8_t * pool_elements_used;
};

TEST_F(QueueTestSmpl3, ConteoDeMaximos01)
{
  //Arrange
  pool_elements_used[3] = 1;
  pool_elements_used[7] = 1;
  //Act

}
