#pragma once

#include <cassert>

typedef int MatrixEdge;
typedef int Vertex;

template <size_t vSize, size_t eSize>
class graphMatrix
{
    public:
        graphMatrix();
        void addVertex(int id);
        void addEdge(int edgeValue, int firstVertex, int secondVertex);

        const Vertex* getVertices() const { return vertexTab; }
        const MatrixEdge* getEdges() const { return edgeTab; }
        const MatrixEdge* getPtrEdge(int i, int j) const { return matrix[i][j]; }
    private:
        MatrixEdge* matrix[vSize][vSize];
        Vertex vertexTab[vSize];
        int vCapacity;
        MatrixEdge edgeTab[eSize];
        int eCapacity;
};

template<size_t vSize, size_t eSize>
graphMatrix<vSize, eSize>::graphMatrix()
{
    vCapacity = 0;
    eCapacity = 0;

    for (int i = 0; i < vSize; ++i)
        vertexTab[i] = -1;
    for (int i = 0; i < eSize; ++i)
        edgeTab[i] = -1;

    for (int i = 0; i < vSize; ++i)
        for (int j = 0; j < vSize; ++j)
            matrix[i][j] = nullptr;
}

template<size_t vSize, size_t eSize>
void graphMatrix<vSize, eSize>::addVertex(int id)
{
    assert(vCapacity < vSize);
    vertexTab[vCapacity] = id;
    vCapacity++;
}

template<size_t vSize, size_t eSize>
void graphMatrix<vSize, eSize>::addEdge(int edgeValue, int firstVertex, int secondVertex)
{
    assert(eCapacity < eSize);

    int index_first = -1;
    int index_second = -1;

    for (int i = 0; i < vCapacity; ++i)
    {
        if (vertexTab[i] == firstVertex)
            index_first = i;
        else if (vertexTab[i] == secondVertex)
            index_second = i;

        if (index_first != -1 && index_second != -1)
            break;
    }

    assert(index_first != -1 && index_second != -1);

    edgeTab[eCapacity] = edgeValue;
    matrix[index_first][index_second] =  &edgeTab[eCapacity];

    eCapacity++;
}
