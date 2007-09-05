#include <iostream>

#include "itkConnectivity.h"

int main(int argc, char** argv)
{

  const unsigned int Dimension = 3;
  typedef itk::Connectivity< Dimension > ConnectivityType;

  ConnectivityType::Pointer connectivity = ConnectivityType::New();
  connectivity->Print( std::cout );
  std::cout << std::endl;

  connectivity->SetFullyConnected( true );
  connectivity->Print( std::cout );
  std::cout << std::endl;

  connectivity->SetFullyConnected( false );
  connectivity->Print( std::cout );
  std::cout << std::endl;

  ConnectivityType::SetGlobalDefaultFullyConnected( true );
  connectivity = ConnectivityType::New();
  connectivity->Print( std::cout );
  std::cout << std::endl;
  
  connectivity->SetCellDimension( 3 );
  connectivity->Print( std::cout );
  std::cout << std::endl;
  
  ConnectivityType::SetGlobalDefaultNumberOfNeighbors( 18 );
  connectivity = ConnectivityType::New();
  connectivity->Print( std::cout );
  std::cout << std::endl;
  
  return EXIT_SUCCESS;
}
