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
  unsigned int next_available = the_pool.nextAvailablePositionIncludingFrom( 0 );
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
  unsigned int next_available = the_pool.nextAvailablePositionIncludingFrom( 0 );
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
    unsigned int next_available = the_pool.nextAvailablePositionIncludingFrom( i );
    unsigned int objective = i;
    //Assert
    EXPECT_EQ( next_available, objective );
  }
}

TEST_F(MemPoolTestingFixture, SiguienteOcupado01)
{
  //Arrange
  pool_elements_used[2] = 1;
  pool_elements_used[3] = 1;
  pool_elements_used[4] = 1;
  //Act
  unsigned int next_occupied = the_pool.nextOccupiedPositionIncludingFrom( 2 );
  unsigned int objective = 2;
  //Assert
  EXPECT_EQ( next_occupied, objective );
}

TEST_F(MemPoolTestingFixture, SiguienteOcupado02)
{
  //Arrange
  pool_elements_used[2] = 1;
  pool_elements_used[3] = 1;
  pool_elements_used[4] = 1;
  //Act
  unsigned int next_occupied = the_pool.nextOccupiedPositionIncludingFrom( 4 );
  unsigned int objective = 4;
  //Assert
  EXPECT_EQ( next_occupied, objective );
}

TEST_F(MemPoolTestingFixture, SiguienteOcupado03)
{
  //Arrange
  pool_elements_used[2] = 1;
  pool_elements_used[3] = 1;
  pool_elements_used[4] = 1;
  //Act
  unsigned int next_occupied = the_pool.nextOccupiedPositionIncludingFrom( 5 );
  unsigned int objective = NELMS + 1;
  //Assert
  EXPECT_EQ( next_occupied, objective );
}

TEST_F(MemPoolTestingFixture, SiguienteOcupado_TodosOcupados_recorrido)
{
  //Arrange
  for ( int i = 0; i < NELMS; i++ )
  {
    pool_elements_used[i] = 1;
  }
  for ( int i = 0; i < NELMS; i++ )
  {
    //Act
    unsigned int next_occupied = the_pool.nextOccupiedPositionIncludingFrom( i );
    unsigned int objective = i;
    //Assert
    EXPECT_EQ( next_occupied, objective );
  }
}

TEST_F(MemPoolTestingFixture, SiguienteOcupado_TodosLibres_Recorrido)
{
  //Arrange
  for ( int i = 0; i < NELMS; i++ )
  {
    //Act
    unsigned int next_occupied = the_pool.nextOccupiedPositionIncludingFrom( i );
    unsigned int objective = NELMS + 1;
    //Assert
    EXPECT_EQ( next_occupied, objective );
  }
}

TEST_F(MemPoolTestingFixture, MarcarDisponibles01)
{
  //Arrange
  //Act
  the_pool.markTheElementsToBeAllocated( 2, 4 );
  unsigned int objective[] = { 0, 0, 4, 4, 4, 4, 0, 0, 0, 0 };
  //Assert
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_EQ( pool_elements_used[i], objective[i] );
  }
}

TEST_F(MemPoolTestingFixture, MarcarDisponibles02)
{
  //Arrange
  //Act
  the_pool.markTheElementsToBeAllocated( 2, 4 );
  the_pool.markTheElementsToBeAllocated( 7, 2 );
  unsigned int objective[] = { 0, 0, 4, 4, 4, 4, 0, 2, 2, 0 };
  //Assert
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_EQ( pool_elements_used[i], objective[i] );
  }
}

TEST_F(MemPoolTestingFixture, MarcarDisponibles_CasoMarginal01)
{
  //Arrange
  //Act
  the_pool.markTheElementsToBeAllocated( 0, 15 );
  unsigned int objective[] = { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 };
  //Assert
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_EQ( pool_elements_used[i], objective[i] );
  }
}

TEST_F(MemPoolTestingFixture, MarcarDisponibles_CasoMarginal02)
{
  //Arrange
  //Act
  the_pool.markTheElementsToBeAllocated( 10, 15 );
  unsigned int objective[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  //Assert
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_EQ( pool_elements_used[i], objective[i] );
  }
}


TEST_F(MemPoolTestingFixture, ComprobarPosicion)
{
  //Arrange
  //Act
  //Assert
  EXPECT_TRUE( the_pool.isPositionInsideMemoryPool( 2 ) );
  EXPECT_FALSE( the_pool.isPositionInsideMemoryPool( 11 ) );
  
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_TRUE( the_pool.isPositionInsideMemoryPool( i ) );
  }
  for ( int i = NELMS; i < 50000; i++ )
  {
    EXPECT_FALSE( the_pool.isPositionInsideMemoryPool( i ) );
  }
}

TEST_F(MemPoolTestingFixture, BufferDisponible01)
{
  //Arrange
  pool_elements_used[0] = 1;
  pool_elements_used[1] = 1;
  pool_elements_used[4] = 1;
  pool_elements_used[5] = 1;
  //Act
  unsigned int place_available = the_pool.firstAvailableBuffer( 3 );
  unsigned int objective = 6;
  //Assert
  EXPECT_EQ( place_available, objective );
}

TEST_F(MemPoolTestingFixture, BufferDisponible02)
{
  //Arrange
  pool_elements_used[0] = 1;
  pool_elements_used[1] = 1;
  pool_elements_used[4] = 1;
  pool_elements_used[5] = 1;
  //Act
  unsigned int place_available = the_pool.firstAvailableBuffer( 2 );
  unsigned int objective = 2;
  //Assert
  EXPECT_EQ( place_available, objective );
}

TEST_F(MemPoolTestingFixture, BufferDisponible03)
{
  //Arrange
  for ( int i = 0; i < NELMS; i++ )
  {
    //Act
    unsigned int place_available = the_pool.firstAvailableBuffer( i );
    unsigned int objective = 0;
    //Assert
    EXPECT_EQ( place_available, objective );
  }
}

TEST_F(MemPoolTestingFixture, New_Test01)
{
  //Arrange
  pool_elements_used[0] = 1;
  pool_elements_used[1] = 1;
  //Act
  int * object_created = the_pool.new_( 3 );
  int * objective = &( pool_elements[2] );
  unsigned int objective_positions[] = { 1, 1, 3, 3, 3, 0, 0, 0, 0, 0 };
  //Assert
  EXPECT_EQ( object_created, objective );
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_EQ( pool_elements_used[i], objective_positions[i] );
  }
}

TEST_F(MemPoolTestingFixture, New_Test02)
{
  //Arrange
  //Act
  int * object_created = the_pool.new_( 3 );
  int * objective = &( pool_elements[0] );
  unsigned int objective_positions[] = { 3, 3, 3, 0, 0, 0, 0, 0, 0, 0 };
  //Assert
  EXPECT_EQ( object_created, objective );
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_EQ( pool_elements_used[i], objective_positions[i] );
  }
}
TEST_F(MemPoolTestingFixture, New_Test03 )
{
  //Arrange
  //Act
  int * object_created = the_pool.new_();
  int * objective = &( pool_elements[0] );
  unsigned int objective_positions[] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  //Assert
  EXPECT_EQ( object_created, objective );
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_EQ( pool_elements_used[i], objective_positions[i] );
  }
}

TEST_F(MemPoolTestingFixture, freeing_the_01)
{
  //Arrange
  int * object_created = the_pool.new_(3);
  int * object_created_2 = the_pool.new_(2);
  unsigned int objective_positions[] = { 0, 0, 0, 2, 2, 0, 0, 0, 0, 0 };
  //Act
  the_pool.freeing_the( object_created, 0, 3 );
  //Assert
  EXPECT_EQ( NULL, object_created );
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_EQ( pool_elements_used[i], objective_positions[i] );
  }
}

TEST_F(MemPoolTestingFixture, freeing_the_02)
{
  //Arrange
  int * object_created = the_pool.new_(3);
  int * object_created_2 = the_pool.new_(2);
  unsigned int objective_positions[] = { 0, 0, 0, 2, 2, 0, 0, 0, 0, 0 };
  //Act
  the_pool.freeing_the( object_created, 0, 3 );
  //Assert
  EXPECT_EQ( NULL, object_created );
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_EQ( pool_elements_used[i], objective_positions[i] );
  }
  //Act
  the_pool.freeing_the( object_created_2, 2, 2 );
  unsigned int objective_positions_2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  //Assert
  EXPECT_EQ( NULL, object_created_2 );
  for ( int i = 0; i < NELMS; i++ )
  {
    EXPECT_EQ( pool_elements_used[i], objective_positions_2[i] );
  }
}
