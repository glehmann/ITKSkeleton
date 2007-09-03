#include <iostream>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkImage.h>

#include "itkSkeletonizeImageFilter.h"

#include "itkChamferDistanceTransformImageFilter.h"
#include "itkSimpleFilterWatcher.h"

int main(int argc, char** argv)
{

  if( argc != 5 )
    {
    std::cerr << "usage: " << argv[0] << " input output fg bg" << std::endl;
    // std::cerr << "  : " << std::endl;
    exit(1);
    }

    const int dim = 2;
    typedef itk::Image<unsigned char, dim> Image;
    
    itk::ImageFileReader<Image>::Pointer reader = itk::ImageFileReader<Image>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    
    Image::Pointer image = reader->GetOutput();
    
    typedef itk::SkeletonizeImageFilter<Image, itk::Connectivity<dim, 0> > Skeletonizer;
    
    typedef itk::ChamferDistanceTransformImageFilter<Image, Skeletonizer::OrderingImageType> DistanceMapFilterType;
    DistanceMapFilterType::Pointer distanceMapFilter = DistanceMapFilterType::New();
    unsigned int weights[] = { 16, 21 };
    distanceMapFilter->SetDistanceFromObject( false );
    distanceMapFilter->SetWeights(weights, weights+2);
    distanceMapFilter->SetInput(image);
    distanceMapFilter->SetForegroundValue( atoi(argv[3]) );
//     itk::SimpleFilterWatcher watcher(distanceMapFilter, "distanceMapFilter");
    distanceMapFilter->Update();
    
    Skeletonizer::Pointer skeletonizer = Skeletonizer::New();
    skeletonizer->SetInput(image);
    skeletonizer->SetOrderingImage(distanceMapFilter->GetOutput());
    skeletonizer->SetForegroundValue( atoi(argv[3]) );
    skeletonizer->SetBackgroundValue( atoi(argv[4]) );
    itk::SimpleFilterWatcher watcher2(skeletonizer, "skeletonizer");
    
    itk::ImageFileWriter<Image>::Pointer writer = itk::ImageFileWriter<Image>::New();
    writer->SetFileName(argv[2]);
    writer->SetInput(skeletonizer->GetOutput());
    writer->Update();
    
    return EXIT_SUCCESS;
}
