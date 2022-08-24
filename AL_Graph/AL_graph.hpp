#ifndef __AL_Graph_H__
#define __AL_Graph_H__

#include "../AL_Direct_Graph/AL_Direct_graph.hpp"
#include "../AL_Direct_Graph/AL_Direct_graph.cpp"

template<typename TV, typename TE>
class AL_Graph : public AL_Direct_Graph<TV,TE>
{
public:
    void insertEdge(const typename AL_Direct_Graph<TV,TE>::Vertex &u, const TE &wgt, const typename AL_Direct_Graph<TV,TE>::Vertex &v);
    void eraseEdge(const typename AL_Direct_Graph<TV,TE>::Edge &e);
};

#endif