#include <iostream>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkImage.h>

#include "itkSkeletonizeImageFilter.h"

#include "itkChamferDistanceTransformImageFilter.h"

int main(int argc, char** argv)
{
    typedef itk::Image<char, 3> Image;
    
    itk::ImageFileReader<Image>::Pointer reader = itk::ImageFileReader<Image>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    
    Image::Pointer image = reader->GetOutput();
    
    typedef itk::SkeletonizeImageFilter<Image, itk::Connectivity<3, 0> > Skeletonizer;
    
    typedef itk::ChamferDistanceTransformImageFilter<Image, Skeletonizer::OrderingImageType> DistanceMapFilterType;
    DistanceMapFilterType::Pointer distanceMapFilter = DistanceMapFilterType::New();
    unsigned int weights[] = { 16, 21, 27 };
    distanceMapFilter->distanceFromObject = false;
    distanceMapFilter->SetWeights(weights, weights+3);
    distanceMapFilter->SetInput(image);
    distanceMapFilter->Update();
    
    Skeletonizer::Pointer skeletonizer = Skeletonizer::New();
    skeletonizer->SetInput(image);
    skeletonizer->SetOrderingImage(distanceMapFilter->GetOutput());
    skeletonizer->Update();
    Image::Pointer skeleton = skeletonizer->GetOutput();
    
    itk::ImageFileWriter<Image>::Pointer writer = itk::ImageFileWriter<Image>::New();
    writer->SetFileName(argv[2]);
    writer->SetInput(skeleton);
    writer->Update();
    
    return EXIT_SUCCESS;
}
