#include "AL_graph.hpp"

template<typename TV, typename TE>
void AL_Graph<TV,TE>::insertEdge(const typename AL_Direct_Graph<TV,TE>::Vertex &u, const TE &wgt, const typename AL_Direct_Graph<TV,TE>::Vertex &v)
{
    AL_Direct_Graph<TV,TE>::insertEdge(u, wgt, v);
    AL_Direct_Graph<TV,TE>::insertEdge(v, wgt, u);
}