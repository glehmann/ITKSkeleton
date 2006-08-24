/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkBinaryImageFunction.txx,v $
  Language:  C++
  Date:      $Date: 2006/08/22 22:25:36 $
  Version:   $Revision: 1.16 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkBinaryImageFunction_txx
#define __itkBinaryImageFunction_txx

#include "itkBinaryImageFunction.h"

namespace itk
{

/**
 * Constructor
 */
template <class TInputImage, class TOutput, class TCoordRep>
BinaryImageFunction<TInputImage, TOutput, TCoordRep>
::BinaryImageFunction()
{
  m_ForegroundValue = NumericTraits<InputPixelType>::max();
}


/**
 * Standard "PrintSelf" method
 */
template <class TInputImage, class TOutput, class TCoordRep>
void
BinaryImageFunction<TInputImage, TOutput, TCoordRep>
::PrintSelf(
  std::ostream& os, 
  Indent indent) const
{
  Superclass::PrintSelf( os, indent );
    os << indent << "ForegroundValue: " << static_cast<typename NumericTraits<InputPixelType>::PrintType>(m_ForegroundValue) << std::endl;
}


template <class TInputImage, class TOutput, class TCoordRep>
void
BinaryImageFunction<TInputImage, TOutput, TCoordRep>
::SetForegroundValue( const InputPixelType & v )
{
  this->m_ForegroundValue = v;
  this->Modified();
}



} // end namespace itk

#endif

