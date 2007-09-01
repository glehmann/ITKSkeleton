#ifndef itkSimplicityByTopologicalNumbersImageFunction_h
#define itkSimplicityByTopologicalNumbersImageFunction_h

#include "itkBinaryImageFunction.h"

#include "itkBackgroundConnectivity.h"
#include "itkTopologicalNumberImageFunction.h"

namespace itk
{

template<typename TImage, 
         typename TForegroundConnectivity, 
         typename TBackgroundConnectivity = 

            typename BackgroundConnectivity<TForegroundConnectivity>::Type >
class ITK_EXPORT SimplicityByTopologicalNumbersImageFunction : 

  public itk::BinaryImageFunction<TImage, bool >
  {
  public :
    /**
     * @name Standard ITK declarations
     */
    //@{
    typedef SimplicityByTopologicalNumbersImageFunction Self;
    typedef itk::BinaryImageFunction<TImage, bool > Superclass;
    typedef itk::SmartPointer<Self> Pointer;
    typedef itk::SmartPointer<Self const> ConstPointer;

    itkNewMacro(Self);
    itkTypeMacro(SimplicityByTopologicalNumbersImageFunction, BinaryImageFunction);
    
    typedef typename Superclass::PointType PointType;
    typedef typename Superclass::ContinuousIndexType ContinuousIndexType;
    typedef typename Superclass::IndexType IndexType;
    
    typedef typename Superclass::InputImageType InputImageType;
    typedef typename Superclass::InputPixelType InputPixelType;
    //@}
    
    /**
     * @brief Initialize the functor so that the topological numbers are 
     * computed for both the foreground and the background.
     */
    SimplicityByTopologicalNumbersImageFunction();
    
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
    
    void SetInputImage(InputImageType const * ptr)
      {
      Superclass::SetInputImage(ptr);
      m_TnCounter->SetInputImage(ptr);
      }
      
    virtual void SetForegroundValue(const InputPixelType &);

  private :
    SimplicityByTopologicalNumbersImageFunction(Self const &); //not implemented
    Self & operator=(Self const &); // not implemented
    typename TopologicalNumberImageFunction<TImage, 

      TForegroundConnectivity>::Pointer m_TnCounter;
  };

}


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkSimplicityByTopologicalNumbersImageFunction.txx"

#endif

#endif // itkSimplicityByTopologicalNumbersImageFunction_h
