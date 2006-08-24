#ifndef itkSkeletonizationImageFilter_h
#define itkSkeletonizationImageFilter_h

#include <itkImage.h>
#include "itkBinaryImageFunction.h"
#include <itkInPlaceImageFilter.h>

namespace itk
{


/**
 * @brief Computes the skeleton of an image using homotopic thinning.
 *
 * @param FGC the connectivity used in the foreground
 *
 * This algorithm needs the following inputs :
 * - An image to be skeletonized
 * - An image to order the removal
 * - A simplicity criterion
 * - A terminality criterion
 *
 * @pre The object in the image must not touch the border.
 *
 * If no simplicity criterion is provided, the default is to compute the 
 * topological numbers and to qualify a point as simple iff both numbers are 
 * equal to 1.
 * @sa itk::SimplicityByTopologicalNumbersImageFunction
 *
 * If no terminality criterion is provided, the default is to keep the line 
 * terminal points, i.e. points having only one neighbor in the object.
 * @sa itk::LineTerminalityImageFunction
 */
template<typename TImage, typename TForegroundConnectivity>
class SkeletonizeImageFilter : public InPlaceImageFilter<TImage>
{
public :
    /**
     * @name Standard ITK boilerplate
     */
    //@{
    typedef SkeletonizeImageFilter Self;
    typedef InPlaceImageFilter<TImage> Superclass;
    typedef SmartPointer<Self> Pointer;
    typedef SmartPointer<Self const> ConstPointer;

    itkNewMacro(Self);
    itkTypeMacro(SkeletonizeImageFilter, InPlaceImageFilter);
    
    //@}
    
    /**
     * @name Standard filter typedefs.
     */
    //@{
    typedef TImage InputImageType;
    typedef TImage OutputImageType;
    //@}
    
    /**
     * @name Define the type of the ordering image.
     */
    //@{
    typedef unsigned int OrderingVoxelType;
    typedef Image<OrderingVoxelType, InputImageType::ImageDimension> OrderingImageType;
    //@}
    
    /**
     * @brief Type of the simplicity and terminality functors.
     */
    typedef BinaryImageFunction<OutputImageType, bool> Criterion;
    
    /** Declaration of pixel type. */
    typedef typename InputImageType::PixelType InputPixelType ;

    /** Set/Get the foreground value. Defaults to max */
    itkSetMacro(ForegroundValue, InputPixelType);
    itkGetMacro(ForegroundValue, InputPixelType);

    /** Set/Get the foreground value. Defaults to zero */
    itkSetMacro(BackgroundValue, InputPixelType);
    itkGetMacro(BackgroundValue, InputPixelType);

    /**
     * @name Accessors for the ordering image.
     */
    //@{
    void SetOrderingImage(OrderingImageType *input)
      {
      // Process object is not const-correct so the const casting is required.
      this->SetNthInput( 1, const_cast<OrderingImageType *>(input) );
      }
  
    OrderingImageType * GetOrderingImage()
      {
      return static_cast<OrderingImageType*>(const_cast<DataObject *>(this->ProcessObject::GetInput(1)));
      }
    //@}
    
    /**
     * @name Accessors for the simplicity criterion.
     */
    //@{
    itkGetConstObjectMacro(SimplicityCriterion, Criterion);
    itkSetObjectMacro(SimplicityCriterion, Criterion);
    //@}
    
    /**
     * @name Accessors for the terminality criterion.
     */
    //@{
    itkGetConstObjectMacro(TerminalityCriterion, Criterion);
    itkSetObjectMacro(TerminalityCriterion, Criterion);
    //@}
    
    /**
     * @brief Connectivity used in the foreground of the image.
     */
    typedef TForegroundConnectivity ForegroundConnectivity;
    
    SkeletonizeImageFilter();
    
protected :
    void PrintSelf(std::ostream& os, Indent indent) const;
    
    void GenerateData();
    
    void GenerateInputRequestedRegion();

    typename Criterion::Pointer m_SimplicityCriterion;
    typename Criterion::Pointer m_TerminalityCriterion;

    InputPixelType m_ForegroundValue;
    InputPixelType m_BackgroundValue;
    
};

} // namespace itk

#include "itkSkeletonizeImageFilter.txx"

#endif
