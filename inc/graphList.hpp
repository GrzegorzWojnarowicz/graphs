#pragma once

#include <cassert>

typedef int Vertex;

struct Edge
{
    int value;
    Vertex* firstVertex;
    Vertex* secondVertex;
};

template <size_t vSize, size_t eSize>
class graphList 
{
    public:
        graphList();
        void addVertex(int id);
        void addEdge(int edgeValue, int firstVertex, int secondVertex);

        const Vertex* getVertices() const;
        const Edge* getEdges() const;
    private:
        Vertex vertexList[vSize];
        int vCapacity;
        Edge edgeList[eSize];
        int eCapacity;
};

template <size_t vSize, size_t eSize>
graphList<vSize, eSize>::graphList()
{
    vCapacity = 0;
    eCapacity = 0;

    for (int i = 0; i < vSize; ++i)
        vertexList[i] = -1;
    for (int i = 0; i < eSize; ++i)
    {
        edgeList[i].value = -1;
        edgeList[i].firstVertex = nullptr;
        edgeList[i].secondVertex = nullptr;
    }
}

template<size_t vSize, size_t eSize>
void graphList<vSize, eSize>::addVertex(int id)
{
    assert(vCapacity < vSize);
    vertexList[vCapacity] = id;
    vCapacity++;
}

template<size_t vSize, size_t eSize>
void graphList<vSize, eSize>::addEdge(int edgeValue, int firstVertex, int secondVertex)
{
    assert(eCapacity < eSize);

    Vertex* first = nullptr;
    Vertex* second = nullptr;

    for (int i = 0; i < vCapacity; ++i)
    {
        if (vertexList[i] == firstVertex)
            first = &vertexList[i];
        else if (vertexList[i] == secondVertex)
            second = &vertexList[i];

        if (first != nullptr && second != nullptr)
            break;
    }

    assert(first != nullptr && second != nullptr);

    edgeList[eCapacity].value = edgeValue;
    edgeList[eCapacity].firstVertex = first;
    edgeList[eCapacity].secondVertex = second;

    eCapacity++;
}

template<size_t vSize, size_t eSize>
const Vertex* graphList<vSize, eSize>::getVertices() const
{
    assert(vCapacity == vSize);
    return vertexList;
}

template<size_t vSize, size_t eSize>
const Edge* graphList<vSize, eSize>::getEdges() const
{
    assert(eCapacity == eSize);
    return edgeList;
}
