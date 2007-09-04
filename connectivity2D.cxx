#include <iostream>

#include "itkConnectivity.h"

int main(int argc, char** argv)
{

  const unsigned int Dimension = 2;
  typedef itk::Connectivity< Dimension > ConnectivityType;
  ConnectivityType::Pointer connectivity = ConnectivityType::New();
  
  std::cout << "global cell dimension: " << ConnectivityType::GetGlobalDefaultCellDimension() << std::endl;
  std::cout << "global fully connected: " << ConnectivityType::GetGlobalDefaultFullyConnected() << std::endl;

  std::cout << std::endl;

  std::cout << "cell dimension: " << connectivity->GetCellDimension() << std::endl;
  std::cout << "fully connected: " << connectivity->GetFullyConnected() << std::endl;
  std::cout << "number of neighbors: " << connectivity->GetNumberOfNeighbors() << std::endl;
  std::cout << "computed number of neighbors: " << connectivity->ComputeNumberOfNeighbors() << std::endl;
  std::cout << "neighbors: ";
  for( int i=0; i<connectivity->GetNumberOfNeighbors(); i++ )
    {
    std::cout << connectivity->GetNeighbors()[i] << " ";
    }
  std::cout << std::endl;

  std::cout << std::endl;

  connectivity->SetFullyConnected( true );
  std::cout << "cell dimension: " << connectivity->GetCellDimension() << std::endl;
  std::cout << "fully connected: " << connectivity->GetFullyConnected() << std::endl;
  std::cout << "number of neighbors: " << connectivity->GetNumberOfNeighbors() << std::endl;
  std::cout << "computed number of neighbors: " << connectivity->ComputeNumberOfNeighbors() << std::endl;
  std::cout << "neighbors: ";
  for( int i=0; i<connectivity->GetNumberOfNeighbors(); i++ )
    {
    std::cout << connectivity->GetNeighbors()[i] << " ";
    }
  std::cout << std::endl;
  
  std::cout << std::endl;

  connectivity->SetFullyConnected( false );
  std::cout << "cell dimension: " << connectivity->GetCellDimension() << std::endl;
  std::cout << "fully connected: " << connectivity->GetFullyConnected() << std::endl;
  std::cout << "number of neighbors: " << connectivity->GetNumberOfNeighbors() << std::endl;
  std::cout << "computed number of neighbors: " << connectivity->ComputeNumberOfNeighbors() << std::endl;
  std::cout << "neighbors: ";
  for( int i=0; i<connectivity->GetNumberOfNeighbors(); i++ )
    {
    std::cout << connectivity->GetNeighbors()[i] << " ";
    }
  std::cout << std::endl;

  std::cout << std::endl;

  ConnectivityType::SetGlobalDefaultFullyConnected( true );

  std::cout << "global cell dimension: " << ConnectivityType::GetGlobalDefaultCellDimension() << std::endl;
  std::cout << "global fully connected: " << ConnectivityType::GetGlobalDefaultFullyConnected() << std::endl;

  std::cout << std::endl;

  connectivity = ConnectivityType::New();
  
  std::cout << "cell dimension: " << connectivity->GetCellDimension() << std::endl;
  std::cout << "fully connected: " << connectivity->GetFullyConnected() << std::endl;
  std::cout << "number of neighbors: " << connectivity->GetNumberOfNeighbors() << std::endl;
  std::cout << "computed number of neighbors: " << connectivity->ComputeNumberOfNeighbors() << std::endl;
  std::cout << "neighbors: ";
  for( int i=0; i<connectivity->GetNumberOfNeighbors(); i++ )
    {
    std::cout << connectivity->GetNeighbors()[i] << " ";
    }
  std::cout << std::endl;    
  
  return EXIT_SUCCESS;
}
