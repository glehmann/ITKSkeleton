#ifndef itkSkeletonizationImageFilter_txx
#define itkSkeletonizationImageFilter_txx

#include <functional>

#include <itkImageRegionConstIteratorWithIndex.h>
#include <itkNumericTraits.h>

#include "hierarchical_queue.h"

#include "itkLineTerminalityImageFunction.h"
#include "itkSimplicityByTopologicalNumbersImageFunction.h"

namespace itk
{

template<typename TImage, typename TForegroundConnectivity>
SkeletonizeImageFilter<TImage, TForegroundConnectivity>
::SkeletonizeImageFilter()
: m_OrderingImage(0),
  m_SimplicityCriterion(0),
  m_TerminalityCriterion(0)
{
}


template<typename TImage, typename TForegroundConnectivity>
void 
SkeletonizeImageFilter<TImage, TForegroundConnectivity>
::PrintSelf(std::ostream& os, Indent indent) const
{
    Superclass::PrintSelf(os,indent);
    os << indent << "Cell dimension used for foreground connectivity: " <<  ForegroundConnectivity::CellDimension << std::endl;
}


template<typename TImage, typename TForegroundConnectivity>
void 
SkeletonizeImageFilter<TImage, TForegroundConnectivity>
::GenerateData()
{
    this->AllocateOutputs();
    
    if(m_OrderingImage.IsNull())
    {
        itkExceptionMacro("No distance map available, cannot skeletonize image");
    }
    
    if(m_SimplicityCriterion.IsNull())
    {
        m_SimplicityCriterion = SimplicityByTopologicalNumbersImageFunction<OutputImageType, TForegroundConnectivity>::New();
        m_SimplicityCriterion->SetInputImage(this->GetInput());
    }
    
    if(m_TerminalityCriterion.IsNull())
    {
        m_TerminalityCriterion = LineTerminalityImageFunction<OutputImageType, TForegroundConnectivity>::New();
        m_TerminalityCriterion->SetInputImage(this->GetInput());
    }
    
    typename OutputImageType::Pointer outputImage = this->GetOutput(0);
    
    // Initialize hierarchical queue
    hierarchical_queue<typename OrderingImageType::PixelType, 
                       typename InputImageType::IndexType, 
                       std::less<typename OrderingImageType::PixelType> > q;
    
    bool* inQueue = new bool[ outputImage->GetRequestedRegion().GetNumberOfPixels() ];
    
    for(ImageRegionConstIteratorWithIndex<OrderingImageType> it(m_OrderingImage, m_OrderingImage->GetRequestedRegion());
        !it.IsAtEnd(); 
        ++it)
    {
        if(it.Get() != NumericTraits<typename OrderingImageType::PixelType>::Zero )
        {
            q.push(it.Get(), it.GetIndex());
            inQueue[ outputImage->ComputeOffset(it.GetIndex()) ] = true;
        }
        else
        {
            inQueue[ outputImage->ComputeOffset(it.GetIndex()) ] = false;
        }
    }
    
    ForegroundConnectivity const & connectivity = ForegroundConnectivity::GetInstance();
    
    while(!q.empty())
    {
        typename InputImageType::IndexType const current = q.front();
        q.pop();
        inQueue[outputImage->ComputeOffset(current)] = false;
        
        bool const terminal = m_TerminalityCriterion->EvaluateAtIndex(current);
        bool const simple = m_SimplicityCriterion->EvaluateAtIndex(current);
        
        if( simple && !terminal )
        {
            outputImage->SetPixel(current, NumericTraits<typename OutputImageType::PixelType>::Zero);
            
            // Add neighbors that are not already in the queue
            for(unsigned int i = 0; i < connectivity.GetNumberOfNeighbors(); ++i)
            {
                typename InputImageType::IndexType currentNeighbor;
                for(unsigned int j = 0; j < ForegroundConnectivity::Dimension; ++j)
                {
                    currentNeighbor[j] = current[j] + connectivity.GetNeighborsPoints()[i][j];
                }
                
                if( /*outputImage->GetRequestedRegion().IsInside(currentNeighbor) &&*/
                    outputImage->GetPixel(currentNeighbor) != NumericTraits<typename OutputImageType::PixelType>::Zero && /* currentNeighbor is in image */
                    !inQueue[outputImage->ComputeOffset(currentNeighbor)]  /* and not in queue */ &&  
                    m_OrderingImage->GetPixel(currentNeighbor) != NumericTraits<typename OrderingImageType::PixelType>::Zero /*and has not 0 priority*/)
                {
                    q.push(m_OrderingImage->GetPixel(currentNeighbor), currentNeighbor);
                    inQueue[outputImage->ComputeOffset(currentNeighbor)] = true;
                }
            }
        }
    }
    
    delete[] inQueue;
}

} // namespace itk

#endif // itkSkeletonizationImageFilter_txx
