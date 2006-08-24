/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkBinaryImageFunction.h,v $
  Language:  C++
  Date:      $Date: 2006/08/22 22:25:36 $
  Version:   $Revision: 1.41 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkBinaryImageFunction_h
#define __itkBinaryImageFunction_h

#include "itkImageFunction.h"
#include "itkPoint.h"
#include "itkIndex.h"
#include "itkContinuousIndex.h"
#include "itkImageBase.h"

namespace itk
{


/** \class BinaryImageFunction
 * \brief Evaluates a function of an image at specified position.
 *
 * BinaryImageFunction is a baseclass for all objects that evaluates
 * a function of an image at index, continuous index or point.
 * This class is templated over the input image type, the type 
 * of the function output and the coordinate representation type
 * (e.g. float or double).
 *
 * The input image is set via method SetInputImage().
 * Methods Evaluate, EvaluateAtIndex and EvaluateAtContinuousIndex
 * respectively evaluates the function at an geometric point,
 * image index and continuous image index.
 *
 * \warning Image BufferedRegion information is cached during
 * in SetInputImage( image ). If the image BufferedRegion has changed
 * one must call SetInputImage( image ) again to update the cache 
 * to the current values.
 *
 * \sa Point
 * \sa Index
 * \sa ContinuousIndex
 *
 * \ingroup BinaryImageFunctions
 */
template <
class TInputImage, 
class TOutput,
class TCoordRep = float 
>
class ITK_EXPORT BinaryImageFunction : 
    public ImageFunction< TInputImage, TOutput, TCoordRep > 
{
public:
  /** Dimension underlying input image. */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  /** Standard class typedefs. */
  typedef BinaryImageFunction Self;
  typedef ImageFunction< TInputImage, TOutput, TCoordRep > Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  
  /** Run-time type information (and related methods). */
  itkTypeMacro(BinaryImageFunction, ImageFunction);

  /** InputImageType typedef support. */
  typedef TInputImage InputImageType;

  /** InputPixel typedef support */
  typedef typename InputImageType::PixelType InputPixelType;

  /** InputImagePointer typedef support */ 
  typedef typename InputImageType::ConstPointer InputImageConstPointer;

  /** OutputType typedef support. */
  typedef TOutput OutputType;

  /** CoordRepType typedef support. */
  typedef TCoordRep CoordRepType;

  /** Index Type. */
  typedef typename InputImageType::IndexType IndexType;

  /** ContinuousIndex Type. */
  typedef ContinuousIndex<TCoordRep,itkGetStaticConstMacro(ImageDimension)>
          ContinuousIndexType;

  /** Point Type. */
  typedef Point<TCoordRep,itkGetStaticConstMacro(ImageDimension)> PointType;

  /** Set/Get the foreground value. Defaults to max */
  itkGetMacro(ForegroundValue, InputPixelType);
  virtual void SetForegroundValue(const InputPixelType &);

protected:
  BinaryImageFunction();
  ~BinaryImageFunction() {}
  void PrintSelf(std::ostream& os, Indent indent) const;

  InputPixelType m_ForegroundValue;
  
private:
  BinaryImageFunction(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkBinaryImageFunction.txx"
#endif

#endif
