#ifndef itkSkeletonizationImageFilter_txx
#define itkSkeletonizationImageFilter_txx

#include <functional>

#include <itkImageRegionConstIteratorWithIndex.h>
#include <itkImageRegionConstIterator.h>
#include <itkImageRegionIterator.h>
#include <itkNumericTraits.h>

#include "itkPriorityQueue.h"

#include "itkLineTerminalityImageFunction.h"
#include "itkSimplicityByTopologicalNumbersImageFunction.h"
#include "itkProgressReporter.h"

namespace itk
{

template<typename TImage, typename TForegroundConnectivity>
SkeletonizeImageFilter<TImage, TForegroundConnectivity>
::SkeletonizeImageFilter()
{
  this->SetNumberOfRequiredInputs(2);
  m_ForegroundValue = NumericTraits<InputPixelType>::max();
  m_BackgroundValue = NumericTraits<InputPixelType>::Zero;
}


template<typename TImage, typename TForegroundConnectivity>
void 
SkeletonizeImageFilter<TImage, TForegroundConnectivity>
::PrintSelf(std::ostream& os, Indent indent) const
{
    Superclass::PrintSelf(os,indent);
    os << indent << "Cell dimension used for foreground connectivity: " <<  ForegroundConnectivity::CellDimension << std::endl;
    os << indent << "ForegroundValue: " << static_cast<typename NumericTraits<InputPixelType>::PrintType>(m_ForegroundValue) << std::endl;
    os << indent << "BackgroundValue: " << static_cast<typename NumericTraits<InputPixelType>::PrintType>(m_BackgroundValue) << std::endl;
}


template<typename TImage, typename TForegroundConnectivity>
void 
SkeletonizeImageFilter<TImage, TForegroundConnectivity>
::GenerateData()
{
    this->AllocateOutputs();
    typename OrderingImageType::Pointer orderingImage = this->GetOrderingImage();
    
    if(m_SimplicityCriterion.IsNull())
    {
        m_SimplicityCriterion = SimplicityByTopologicalNumbersImageFunction<OutputImageType, TForegroundConnectivity>::New();
    }
    m_SimplicityCriterion->SetInputImage(this->GetInput());
    m_SimplicityCriterion->SetForegroundValue( m_ForegroundValue );
    
    if(m_TerminalityCriterion.IsNull())
    {
        m_TerminalityCriterion = LineTerminalityImageFunction<OutputImageType, TForegroundConnectivity>::New();
    }
    m_TerminalityCriterion->SetInputImage(this->GetInput());
    m_TerminalityCriterion->SetForegroundValue( m_ForegroundValue );
    
    typename OutputImageType::Pointer outputImage = this->GetOutput(0);
    
    // Initialize hierarchical queue
    PriorityQueue<typename OrderingImageType::PixelType, 
                       typename InputImageType::IndexType, 
                       std::less<typename OrderingImageType::PixelType> > q;
    
    bool* inQueue = new bool[ outputImage->GetRequestedRegion().GetNumberOfPixels() ];
    
    // set up progress reporter. There is 2 steps, but we can't know how many pixels will be
    // in the second one, so use the maximum
    ProgressReporter progress(this, 0, outputImage->GetRequestedRegion().GetNumberOfPixels()*2);

    ImageRegionConstIteratorWithIndex<OrderingImageType> ordIt(orderingImage, orderingImage->GetRequestedRegion());
    ImageRegionConstIterator<InputImageType> iIt(this->GetInput(), orderingImage->GetRequestedRegion());
    ImageRegionIterator<OutputImageType> oIt(outputImage, orderingImage->GetRequestedRegion());

    for(ordIt.Begin(), iIt.Begin(), oIt.Begin();
        !ordIt.IsAtEnd(); 
        ++ordIt, ++iIt, ++oIt)
    {
        if(ordIt.Get() != NumericTraits<typename OrderingImageType::PixelType>::Zero )
        {
            q.Push(ordIt.Get(), ordIt.GetIndex());
            inQueue[ outputImage->ComputeOffset(ordIt.GetIndex()) ] = true;
        }
        else
        {
            inQueue[ outputImage->ComputeOffset(ordIt.GetIndex()) ] = false;
        }
        oIt.Set( iIt.Get() );
        progress.CompletedPixel();
    }
    
    ForegroundConnectivity const & connectivity = ForegroundConnectivity::GetInstance();
    
    while(!q.Empty())
    {
        typename InputImageType::IndexType const current = q.FrontValue();
        q.Pop();
        inQueue[outputImage->ComputeOffset(current)] = false;
        
        bool const terminal = m_TerminalityCriterion->EvaluateAtIndex(current);
        bool const simple = m_SimplicityCriterion->EvaluateAtIndex(current);
        
        if( simple && !terminal )
        {
            outputImage->SetPixel(current, m_BackgroundValue);
            
            // Add neighbors that are not already in the queue
            for(unsigned int i = 0; i < connectivity.GetNumberOfNeighbors(); ++i)
            {
                typename InputImageType::IndexType currentNeighbor;
                for(unsigned int j = 0; j < ForegroundConnectivity::Dimension; ++j)
                {
                    currentNeighbor[j] = current[j] + connectivity.GetNeighborsPoints()[i][j];
                }
                
                if( /*outputImage->GetRequestedRegion().IsInside(currentNeighbor) &&*/
                    outputImage->GetPixel(currentNeighbor) == m_ForegroundValue && /* currentNeighbor is in image */
                    !inQueue[outputImage->ComputeOffset(currentNeighbor)]  /* and not in queue */ &&  
                    orderingImage->GetPixel(currentNeighbor) != NumericTraits<typename OrderingImageType::PixelType>::Zero /*and has not 0 priority*/)
                {
                    q.Push(orderingImage->GetPixel(currentNeighbor), currentNeighbor);
                    inQueue[outputImage->ComputeOffset(currentNeighbor)] = true;
                }
            }
        }
        progress.CompletedPixel();
    }
    
    delete[] inQueue;
}


template<typename TImage, typename TForegroundConnectivity>
void 
SkeletonizeImageFilter<TImage, TForegroundConnectivity>
::GenerateInputRequestedRegion()
{
  // call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();

  // get pointers to the inputs
  typename OrderingImageType::Pointer  orderingPtr = this->GetOrderingImage();

  typename TImage::Pointer  inputPtr =
    const_cast< TImage * >( this->GetInput() );

  if ( !orderingPtr || !inputPtr )
    { return; }

  // We need to
  // configure the inputs such that all the data is available.
  //
  orderingPtr->SetRequestedRegion(orderingPtr->GetLargestPossibleRegion());
  inputPtr->SetRequestedRegion(inputPtr->GetLargestPossibleRegion());
}


} // namespace itk

#endif // itkSkeletonizationImageFilter_txx
