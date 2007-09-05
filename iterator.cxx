#include <iostream>

#include "itkConnectivity.h"
#include "itkImage.h"
#include "itkShapedNeighborhoodIterator.h"

int main(int argc, char** argv)
{

  const unsigned int Dimension = 3;
  typedef itk::Connectivity< Dimension > ConnectivityType;
  typedef unsigned char PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;
  typedef itk::ConstShapedNeighborhoodIterator< ImageType > ConstIteratorType;
  typedef itk::ShapedNeighborhoodIterator< ImageType > IteratorType;

  ConnectivityType::Pointer connectivity = ConnectivityType::New();
  connectivity->Print( std::cout );

  ImageType::Pointer img = ImageType::New();
  ImageType::SizeType size;
  size.Fill( 10 );
  img->SetRegions( size );
  img->Allocate();

  ImageType::ConstPointer constImg = img.GetPointer();

/*  ConstIteratorType constIt = connectivity->Iterator<ConstIteratorType>( img, img->GetLargestPossibleRegion() );
  IteratorType It = connectivity->Iterator<IteratorType>( img, img->GetLargestPossibleRegion() );*/
  
  ConstIteratorType constIt = connectivity->ConstIterator<ConstIteratorType>( constImg, constImg->GetLargestPossibleRegion() );
  IteratorType it = connectivity->Iterator<IteratorType>( img, constImg->GetLargestPossibleRegion() );
  
  constIt = connectivity->ConstLaterIterator<ConstIteratorType>( constImg, constImg->GetLargestPossibleRegion() );
  it = connectivity->LaterIterator<IteratorType>( img, constImg->GetLargestPossibleRegion() );
  
  
  return EXIT_SUCCESS;
}
