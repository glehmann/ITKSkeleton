#ifndef TopologicalNumberFunction_txx
#define TopologicalNumberFunction_txx

#include <itkNumericTraits.h>

namespace itk
{

template<typename TImage, typename TFGConnectivity, typename TBGConnectivity >
TopologicalNumberImageFunction<TImage, TFGConnectivity, TBGConnectivity>
::TopologicalNumberImageFunction()
: m_ComputeForegroundTN(true), m_ComputeBackgroundTN(true)
{
}

template<typename TImage, typename TFGConnectivity, typename TBGConnectivity >
std::pair<unsigned int, unsigned int> 
TopologicalNumberImageFunction<TImage, TFGConnectivity, TBGConnectivity>
::Evaluate(PointType const & point) const
{
    typename TImage::IndexType index;
    ConvertPointToNearestIndex(point, index);
    return EvaluateAtIndex(index);
}


template<typename TImage, typename TFGConnectivity, typename TBGConnectivity >
std::pair<unsigned int, unsigned int> 
TopologicalNumberImageFunction<TImage, TFGConnectivity, TBGConnectivity>
::EvaluateAtIndex(IndexType const & index) const
{
    char subImage[TFGConnectivity::GetInstance().GetNeighborhoodSize()];
    
    // Get the sub-image
    for(unsigned int i=0; i<TFGConnectivity::GetInstance().GetNeighborhoodSize(); ++i)
    {
        int remainder = i;
        itk::Offset<TFGConnectivity::Dimension> offset;

        // Get current offset
        for(unsigned int j=0; j<TFGConnectivity::Dimension; ++j)
        {
            offset[j] = remainder % 3;
            remainder -= offset[j];
            remainder /= 3;
            --offset[j];
        }
        
        subImage[i] = (this->GetInputImage()->GetPixel(index+offset)!=itk::NumericTraits<typename TImage::PixelType>::Zero)?255:0;
    }
    subImage[13] = 0;
    
    // Topological number in the foreground
    m_ForegroundUnitCubeCCCounter.SetImage(subImage, subImage+TFGConnectivity::GetInstance().GetNeighborhoodSize());
    unsigned int const ccNumber = m_ComputeForegroundTN ? m_ForegroundUnitCubeCCCounter() : 0;
    
    // Invert the sub-image
    for(int bit = 0; bit<13; ++bit)
    {
        subImage[bit] = 255 - subImage[bit];
    }
    for(int bit=13; bit<26; ++bit)
    {
        subImage[bit+1] = 255 - subImage[bit+1];
    }
    
    // Topological number in the background
    m_BackgroundUnitCubeCCCounter.SetImage(subImage, subImage+TBGConnectivity::GetInstance().GetNeighborhoodSize());
    assert(TFGConnectivity::GetInstance().GetNeighborsPoints());
    
    unsigned int const backgroundCcNumber = m_ComputeBackgroundTN ? m_BackgroundUnitCubeCCCounter() : 0;
    
    return std::pair<unsigned int, unsigned int>(ccNumber, backgroundCcNumber);
}


template<typename TImage, typename TFGConnectivity, typename TBGConnectivity >
std::pair<unsigned int, unsigned int> 
TopologicalNumberImageFunction<TImage, TFGConnectivity, TBGConnectivity>
::EvaluateAtContinuousIndex(ContinuousIndexType const & contIndex) const
{
    typename TImage::IndexType index;
    ConvertContinuousIndexToNearestIndex(contIndex, index);
    return EvaluateAtIndex(index);
}


template<typename TImage, typename TFGConnectivity, typename TBGConnectivity >
UnitCubeCCCounter< TFGConnectivity > 
TopologicalNumberImageFunction<TImage, TFGConnectivity, TBGConnectivity>
::m_ForegroundUnitCubeCCCounter = UnitCubeCCCounter< TFGConnectivity >();


template<typename TImage, typename TFGConnectivity, typename TBGConnectivity >
UnitCubeCCCounter< TBGConnectivity > 
TopologicalNumberImageFunction<TImage, TFGConnectivity, TBGConnectivity>
::m_BackgroundUnitCubeCCCounter = UnitCubeCCCounter< TBGConnectivity >();

}

#endif // TopologicalNumberFunction_txx
