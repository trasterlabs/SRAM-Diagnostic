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

intPool & the_pool = intPool::GetInstance();

class MemPoolTestingFixture : public testing::Test
{
protected:
  void SetUp () override
  {
    pool_elements = the_pool.ReceiveThePool();
    pool_elements_used = the_pool.ReceiveElementsUsed();
    for ( int i = 0; i < NELMS; i++ )
    {
      pool_elements[i] = 0;
    }
    for ( int i = 0; i < NELMS; i++ )
    {
      pool_elements_used[i] = 0;
    }
  }
  
  
  int * pool_elements;
  uint8_t * pool_elements_used;
};

TEST_F(MemPoolTestingFixture, ConteoDeMaximos01)
{
  //Arrange
  pool_elements_used[3] = 1;
  pool_elements_used[7] = 1;
  //Act
  unsigned int max_consecutive = the_pool.countMaxFreeConsecutiveElements();
  unsigned int objective = 3;
  //Assert
  EXPECT_EQ( max_consecutive, objective );
}

TEST_F(MemPoolTestingFixture, ConteoDeMaximos02)
{
  //Arrange
  pool_elements_used[3] = 1;
  pool_elements_used[8] = 1;
  //Act
  unsigned int max_consecutive = the_pool.countMaxFreeConsecutiveElements();
  unsigned int objective = 4;
  //Assert
  EXPECT_EQ( max_consecutive, objective );
}

TEST_F(MemPoolTestingFixture, ConteoDeMaximos03)
{
  //Arrange
  pool_elements_used[3] = 1;
  pool_elements_used[4] = 1;
  pool_elements_used[5] = 1;
  pool_elements_used[8] = 1;
  //Act
  unsigned int max_consecutive = the_pool.countMaxFreeConsecutiveElements();
  unsigned int objective = 4;
  //Assert
  EXPECT_EQ( max_consecutive, objective );
}

TEST_F(MemPoolTestingFixture, ConteoDeMaximos_TodosLibres)
{
  //Arrange
  //Act
  unsigned int max_consecutive = the_pool.countMaxFreeConsecutiveElements();
  unsigned int objective = 10;
  //Assert
  EXPECT_EQ( max_consecutive, objective );
}

TEST_F(MemPoolTestingFixture, ConteoDeMaximos_TodosOcupados)
{
  //Arrange
  for ( int i = 0; i < NELMS; i++ )
  {
    pool_elements_used[i] = 1;
  }
  //Act
  unsigned int max_consecutive = the_pool.countMaxFreeConsecutiveElements();
  unsigned int objective = 0;
  //Assert
  EXPECT_EQ( max_consecutive, objective );
}

TEST_F(MemPoolTestingFixture, SiguienteDisponible01)
{
  //Arrange
  pool_elements_used[2] = 1;
  pool_elements_used[3] = 1;
  pool_elements_used[4] = 1;
  //Act
  unsigned int next_available = the_pool.nextAvailablePositionIncludingFrom(2);
  unsigned int objective = 5;
  //Assert
  EXPECT_EQ( next_available, objective );
}

TEST_F(MemPoolTestingFixture, SiguienteDisponible02)
{
  //Arrange
  for ( int i = 0; i < 6; i++ )
  {
    pool_elements_used[i] = 1;
  }
  //Act
  unsigned int next_available = the_pool.nextAvailablePositionIncludingFrom(0);
  unsigned int objective = 6;
  //Assert
  EXPECT_EQ( next_available, objective );
}

TEST_F(MemPoolTestingFixture, SiguienteDisponible_TodosOcupados)
{
  //Arrange
  for ( int i = 0; i < NELMS; i++ )
  {
    pool_elements_used[i] = 1;
  }
  //Act
  unsigned int next_available = the_pool.nextAvailablePositionIncludingFrom(0);
  unsigned int objective = NELMS + 1;
  //Assert
  EXPECT_EQ( next_available, objective );
}

TEST_F(MemPoolTestingFixture, SiguienteDisponible_TodosLibres_recorrido)
{
  //Arrange
  for ( int i = 0; i < NELMS; i++ )
  {
    //Act
    unsigned int next_available = the_pool.nextAvailablePositionIncludingFrom(i);
    unsigned int objective = i;
    //Assert
    EXPECT_EQ( next_available, objective );
  }
}
