#include "Chunk.h"
#include <iostream>
namespace game
{
    Chunk::Chunk(game::BlockManager* manager)
    {
        vertexBufferVector = nullptr;
        indexBufferVector = nullptr;
        vertexBuffer = nullptr;
        indexBuffer = nullptr;
        vao = nullptr;

        this->manager = manager;
        GenerateChunk();
        GenerateVao();
    }


    void Chunk::GenerateChunk()
    {
        for(int x = 0; x < 16; x++)
        {
            for(int y = 0; y < 256; y++)
            {
                for(int z = 0; z < 16; z++)
                {
                    if(y < 250)
                    {
                        blocks[x][y][z] = 2u;
                    }
                    else
                    {
                        blocks[x][y][z] = 1u;
                    }
                }
            }
        }
    }

    void Chunk::GenerateVao()
    {
        if(vertexBufferVector != nullptr) { delete vertexBufferVector; }
        if(indexBufferVector != nullptr) { delete indexBufferVector; }
        vertexBufferVector = new std::vector<float>;
        indexBufferVector = new std::vector<unsigned int>;

        unsigned int offset = 0;
        for(int x = 0; x < 16; x++)
        {
            for(int y = 0; y < 256; y++)
            {
                for(int z = 0; z < 16; z++)
                {

                    std::vector<float>* insertionVertexVector = manager->GetBlockVertexBuffer(blocks[x][y][z],
                                                                                              GetBlockFacesAtChunkCoordinate(x,y,z).topFace,
                                                                                              GetBlockFacesAtChunkCoordinate(x,y,z).bottomFace,
                                                                                              GetBlockFacesAtChunkCoordinate(x,y,z).backFace,
                                                                                              GetBlockFacesAtChunkCoordinate(x,y,z).frontFace,
                                                                                              GetBlockFacesAtChunkCoordinate(x,y,z).leftFace,
                                                                                              GetBlockFacesAtChunkCoordinate(x,y,z).rightFace
                    );

                    // No Block at this chunk coord

                    if(insertionVertexVector == nullptr) { continue;}
                    for(int i = 0; i < insertionVertexVector->size(); i+=8)
                    {
                        vertexBufferVector->push_back(insertionVertexVector->at(i) + x);        //Vert X
                        vertexBufferVector->push_back(insertionVertexVector->at(i + 1) + y);    //Vert Y
                        vertexBufferVector->push_back(insertionVertexVector->at(i + 2) + z);    //Vert Z
                        vertexBufferVector->push_back(insertionVertexVector->at(i + 3));        //Norm X
                        vertexBufferVector->push_back(insertionVertexVector->at(i + 4));        //Norm Y
                        vertexBufferVector->push_back(insertionVertexVector->at(i + 5));        //Norm Z
                        vertexBufferVector->push_back(insertionVertexVector->at(i + 6));        //Tex X
                        vertexBufferVector->push_back(insertionVertexVector->at(i + 7));        //Tex Y
                    }

                    std::vector<unsigned int>* insertionIndexBuffer = manager->GetBlockIndexBuffer(blocks[x][y][z],
                                                                                          GetBlockFacesAtChunkCoordinate(x,y,z).topFace,
                                                                                          GetBlockFacesAtChunkCoordinate(x,y,z).bottomFace,
                                                                                          GetBlockFacesAtChunkCoordinate(x,y,z).backFace,
                                                                                          GetBlockFacesAtChunkCoordinate(x,y,z).frontFace,
                                                                                          GetBlockFacesAtChunkCoordinate(x,y,z).leftFace,
                                                                                          GetBlockFacesAtChunkCoordinate(x,y,z).rightFace
                                                                                          );

                    for(unsigned int i : *insertionIndexBuffer)
                    {
                        indexBufferVector->push_back(i+offset);
                    }
                    offset = indexBufferVector->at(indexBufferVector->size()-1)+1;
                }
            }
        }

        if(vertexBuffer != nullptr) { delete vertexBuffer; }
        if(indexBuffer != nullptr) { delete indexBuffer; }
        vertexBuffer = new engine::VertexBuffer(vertexBufferVector->data(), vertexBufferVector->size() * sizeof(float), GL_STATIC_DRAW);
        indexBuffer  = new engine::IndexBuffer (indexBufferVector->data(),  indexBufferVector->size() *  sizeof(unsigned int), GL_STATIC_DRAW);

        if(vao != nullptr) { delete vao; }
        vao = new engine::VertexArrayObject();
        vao->AddIndexBuffer(*indexBuffer);
        vao->SetVertexAttribPointer(*vertexBuffer, 0, 3, GL_FLOAT, false, 8*sizeof(float), nullptr);
        vao->SetVertexAttribPointer(*vertexBuffer, 1, 3, GL_FLOAT, false, 8*sizeof(float), (void*) (3 * sizeof(float)));
        vao->SetVertexAttribPointer(*vertexBuffer, 2, 2, GL_FLOAT, false, 8*sizeof(float), (void*) (6 * sizeof(float)));
        vao->EnableVertexAttribPointer(0);
        vao->EnableVertexAttribPointer(1);
        vao->EnableVertexAttribPointer(2);
        vao->SetVertexCount(indexBufferVector->size());
    }

    uint8_t Chunk::GetBlockTypeAtChunkCoordinate(uint8_t x, uint8_t y, uint8_t z)
    {
        return blocks[x][z][y];
    }

    Faces Chunk::GetBlockFacesAtChunkCoordinate(uint8_t x, uint8_t y, uint8_t z)
    {
        bool hasTop    = y == 255 || blocks[x][y + 1][z] == 0;
        bool hasBottom = y == 0   || blocks[x][y - 1][z] == 0;

        bool hasFront = z == 15 || blocks[x][y][z+1] == 0;
        bool hasBack = z == 0 || blocks[x][y][z-1] == 0;

        bool hasRight = x == 15 || blocks[x+1][y][z] == 0;
        bool hasLeft = x == 0 || blocks[x-1][y][z] == 0;

        return {hasTop, hasBottom, hasFront, hasBack, hasLeft, hasRight};

    }

    engine::VertexArrayObject* Chunk::GetVao()
    {
        return vao;
    }

}