#ifndef NeighborhoodConnectivity_h
#define NeighborhoodConnectivity_h

#include "Connectivity.h"

namespace itk
{

/**
 * @brief Helper to determine the neighborhood connectivity to use when computing topological numbers.
 * @param Connectivity : the image connectivity
 */
template<typename TConnectivity>
struct NeighborhoodConnectivity
{
    typedef TConnectivity Type;
};


template<>
struct NeighborhoodConnectivity< Connectivity<2,1> >
{
    typedef Connectivity<2,0> Type;
};


template<>
struct NeighborhoodConnectivity< Connectivity<3,2> >
{
    typedef Connectivity<3,1> Type;
};

}

#endif // NeighborhoodConnectivity_h
