#ifndef UnitCubeCCCounter_h
#define UnitCubeCCCounter_h

#include <vector>

#include "UnitCubeNeighbors.h"

namespace itk
{

/** 
 * @brief Functor counting the number of connected components restricted in a 
 * unit cube. This class is used for topological number computation, and 
 * should be mostly useless in any other cases.
 */
template< typename TConnectivity, typename TNeighborhoodConnectivity = typename NeighborhoodConnectivity<TConnectivity>::Type >
class UnitCubeCCCounter
{
public :
    UnitCubeCCCounter();
    ~UnitCubeCCCounter();
    
    unsigned int operator()() const;
    
    template<typename Iterator>
    void SetImage(Iterator imageBegin, Iterator imageEnd);
    
private :
    
    template<typename C>
    static std::vector<bool> CreateConnectivityTest();
    
    static std::vector<bool> const m_NeighborhoodConnectivityTest;
    static std::vector<bool> const m_ConnectivityTest;
    
    char* m_Image;
    
    static UnitCubeNeighbors<TConnectivity, TNeighborhoodConnectivity > const m_UnitCubeNeighbors;
};

}

#include "UnitCubeCCCounter.txx"

#endif // UnitCubeCCCounter_h
