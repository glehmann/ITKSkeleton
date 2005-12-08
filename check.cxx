#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCommand.h"
#include "itkSimpleFilterWatcher.h"

#include "itkImageFilter.h"


int main(int, char * argv[])
{
  const int dim = 2;
  
  typedef unsigned char PType;
  typedef itk::Image< PType, dim > IType;

  typedef itk::ImageFileReader< IType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  typedef itk::ImageFilter< IType, IType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  // test the filter without input or parameters
  try
    {
    filter->Update();
    // comment this line if the filter don't have to send an exception
    return EXIT_FAILURE;
    }
  catch (itk::ExceptionObject & e)
    {}
  // set the input
  filter->SetInput( reader->GetOutput() );

  itk::SimpleFilterWatcher watcher(filter, "filter");

  typedef itk::ImageFileWriter< IType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( argv[2] );
  writer->UpdateLargestPossibleRegion();

  return 0;
}

