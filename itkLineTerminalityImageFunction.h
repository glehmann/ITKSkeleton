#ifndef itkLineTerminalityImageFunction_h
#define itkLineTerminalityImageFunction_h

#include <itkImageFunction.h>

#include "BackgroundConnectivity.h"

namespace itk
{

template<typename TImage, 
         typename TForegroundConnectivity, 
         typename TBackgroundConnectivity = typename BackgroundConnectivity<TForegroundConnectivity>::Type  >
class LineTerminalityImageFunction : public itk::ImageFunction<TImage, bool >
{
public :
    /**
     * @name Standard ITK boilerplate
     */
    //@{
    typedef LineTerminalityImageFunction Self;
    typedef itk::ImageFunction<TImage, bool > Superclass;
    typedef itk::SmartPointer<Self> Pointer;
    typedef itk::SmartPointer<Self const> ConstPointer;

    itkNewMacro(Self);
    itkTypeMacro(LineTerminalityImageFunction, ImageFunction);
    
    typedef typename Superclass::PointType PointType;
    typedef typename Superclass::ContinuousIndexType ContinuousIndexType;
    typedef typename Superclass::IndexType IndexType;
    //@}
    
    /**
     * @brief Initialize the functor so that the topological numbers are 
     * computed for both the foreground and the background.
     */
    LineTerminalityImageFunction();
    
    /**
     * @name Evaluation functions
     * 
     * These functions evaluate the topological number at the index.
     */
    //@{
    bool Evaluate(PointType const & point) const;
    
    bool EvaluateAtIndex(IndexType const & index) const;
    
    bool EvaluateAtContinuousIndex(ContinuousIndexType const & contIndex) const;
    //@}

private :
    LineTerminalityImageFunction(Self const &); // not implemented
    Self & operator=(Self const &); // not implemented
};

}

#include "itkLineTerminalityImageFunction.txx"

#endif // itkLineTerminalityImageFunction_hxx
