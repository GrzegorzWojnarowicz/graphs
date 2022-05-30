#pragma once

#include <limits>
#include "graphList.hpp"
#include "graphMatrix.hpp"

struct BFVertices
{
    int id;
    int value;
    BFVertices* parent;
};

template <size_t vSize, size_t eSize>
BFVertices* bellmanFord(graphList<vSize, eSize>& graph, Vertex start)
{
    BFVertices* ret = new BFVertices[vSize];
    const Vertex* v = graph.getVertices();
    const Edge* e = graph.getEdges();
    for (int i = 0; i < vSize; ++i)
    {
        ret[i].id = v[i];
        ret[i].value = 100000000;
        ret[i].parent = nullptr;

        if (ret[i].id == start)
        {
            ret[i].value = 0;
            ret[i].parent = &ret[i];
        }
    }

    for (int i = 0; i < vSize - 1; ++i)
    {
        for (int j = 0; j < eSize; ++j)
        {
            int first = *(e[j].firstVertex);
            int second = *(e[j].secondVertex);
            int value = e[j].value;
            BFVertices* f = nullptr;
            BFVertices* s = nullptr;
            for (int k = 0; k < vSize; ++k)
            {
                if (ret[k].id == first)
                    f = &ret[k];
                else if (ret[k].id == second)
                    s = &ret[k];

                if (f != nullptr && s != nullptr)
                    break;
            }

            assert(f != nullptr && s != nullptr);

            if (s->value > f->value + value)
            {
                s->value = f->value + value;
                s->parent = f;
            }
        }
    }

    for (int j = 0; j < eSize; ++j)
    {
        int first = *(e[j].firstVertex);
        int second = *(e[j].secondVertex);
        int value = e[j].value;
        BFVertices* f = nullptr;
        BFVertices* s = nullptr;
        for (int k = 0; k < vSize; ++k)
        {
            if (ret[k].id == first)
                f = &ret[k];
            else if (ret[k].id == second)
                s = &ret[k];

            if (f != nullptr && s != nullptr)
                break;
        }

        assert(f != nullptr && s != nullptr);

        if (s->value > f->value + value)
        {
            assert(false);  // Graf ujemny
        }
    }

    return ret;
}

template <size_t vSize, size_t eSize>
BFVertices* bellmanFord(graphMatrix<vSize, eSize>& graph, Vertex start)
{
    BFVertices* ret = new BFVertices[vSize];
    const Vertex* v = graph.getVertices();
    const MatrixEdge* e = graph.getEdges();
    for (int i = 0; i < vSize; ++i)
    {
        ret[i].id = v[i];
        ret[i].value = 100000000;
        ret[i].parent = nullptr;

        if (ret[i].id == start)
        {
            ret[i].value = 0;
            ret[i].parent = &ret[i];
        }
    }

    for (int i = 0; i < vSize - 1; ++i)
    {
        for (int j = 0; j < vSize; ++j)
        {
            for (int k = 0; k < vSize; ++k)
            {
                if (graph.getPtrEdge(j, k) != nullptr)
                {
                    if (ret[k].value > ret[j].value + *graph.getPtrEdge(j, k))
                    {
                        ret[k].value = ret[j].value + *graph.getPtrEdge(j, k);
                        ret[k].parent = &ret[j];
                    }
                }
            }
        }
    }

    for (int j = 0; j < vSize; ++j)
    {
        for (int k = 0; k < vSize; ++k)
        {
            if (graph.getPtrEdge(j, k) != nullptr)
            {
                if (ret[k].value > ret[j].value + *graph.getPtrEdge(j, k))
                {
                    assert(false);  //Graf ujemny
                }
            }
        }
    }
    
    return ret;
}