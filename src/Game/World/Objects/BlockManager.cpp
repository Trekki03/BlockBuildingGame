#include "BlockManager.h"
#include <vector>
#include "Engine/Render/Objects/Primitives.h"


#define VALUES_PER_VERT 6
#define VERT_PER_SIDE 4
#define INDICES_PER_SIDE 6

#define VERT_TOP_START 120
#define VERT_BOTTOM_START 96
#define VERT_RIGHT_START 24
#define VERT_LEFT_START 72
#define VERT_BACK_START 48
#define VERT_FRONT_START 0

#include <iostream>

namespace game
{
    //engine::VertexArrayObject*
    engine::VertexArrayObject* BlockManager::getBlockVao(uint8_t blockID, bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight)
    {
        //if block has no sides to show, return a nullptr
        if(!hasTop && !hasBottom && !hasBack && !hasFront && !hasLeft && !hasRight)
        {
            return nullptr;
        }

        //if vao for block already exists, return it.
        uint32_t blockCode = getBlockCode(blockID, hasTop, hasBottom, hasBack, hasFront, hasLeft, hasRight);
        if(vaos.contains(blockCode))
        {
            return vaos.at(blockCode);
        }

        //if vao doesn't already exist, create it.
        engine::VertexArrayObject* vao = new engine::VertexArrayObject;

        //Create Vertexbuffer
        std::vector<float> vertices;
        if(hasFront)
        {
            addSide(&vertices, VERT_FRONT_START, blockAtlas.getSideTexPos(blockID));
        }
        if(hasRight)
        {
            addSide(&vertices, VERT_RIGHT_START, blockAtlas.getSideTexPos(blockID));
        }
        if(hasBack)
        {
            addSide(&vertices, VERT_BACK_START, blockAtlas.getSideTexPos(blockID));
        }
        if(hasLeft)
        {
            addSide(&vertices, VERT_LEFT_START, blockAtlas.getSideTexPos(blockID));
        }
        if(hasBottom)
        {
            addSide(&vertices, VERT_BOTTOM_START, blockAtlas.getBottomTexPos(blockID));
        }
        if(hasTop)
        {
            addSide(&vertices, VERT_TOP_START, blockAtlas.getTopTexPos(blockID));
        }
        engine::VertexBuffer* vb = new engine::VertexBuffer(vertices.data(), vertices.size() * sizeof(float), GL_STATIC_DRAW);
        vbs.push_back(vb);

        //Create Indexbuffer
        std::vector<unsigned int> indices;
        int offset = 0;
        if(hasFront)
        {
            addIndicesforSide(&indices, offset);
            offset+=4;
        }
        if(hasRight)
        {
            addIndicesforSide(&indices, offset);
            offset+=4;
        }

        if(hasBack)
        {
            addIndicesforSide(&indices, offset);
            offset+=4;
        }
        if(hasLeft)
        {
            addIndicesforSide(&indices, offset);
            offset+=4;
        }
        if(hasBottom)
        {
            addIndicesforSide(&indices, offset);
            offset+=4;
        }
        if(hasTop)
        {
            addIndicesforSide(&indices, offset);
            offset+=4;
        }
        engine::IndexBuffer* ib = new engine::IndexBuffer(indices.data(), indices.size()*sizeof(unsigned int), GL_STATIC_DRAW);
        ibs.push_back(ib);

        vao->AddIndexBuffer(*ib);
        vao->SetVertexAttribPointer(*vb, 0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);
        vao->SetVertexAttribPointer(*vb, 1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*) (3 * sizeof(float)));
        vao->SetVertexAttribPointer(*vb, 2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*) (6 * sizeof(float)));
        vao->EnableVertexAttribPointer(0);
        vao->EnableVertexAttribPointer(1);
        vao->EnableVertexAttribPointer(2);
        return vao;
    }

    unsigned int BlockManager::getVertexCount(bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight)
    {
        unsigned int count = 0;
        if(hasFront)
        {
            count+=6;
        }
        if(hasRight)
        {
            count+=6;
        }

        if(hasBack)
        {
            count+=6;
        }
        if(hasLeft)
        {
            count+=6;
        }
        if(hasBottom)
        {
            count+=6;
        }
        if(hasTop)
        {
            count+=6;
        }
        return count;
    }

    void BlockManager::addIndicesforSide(std::vector<unsigned int>* vector, int offset)
    {
        vector->push_back(offset);
        vector->push_back(offset+1);
        vector->push_back(offset+3);
        vector->push_back(offset+1);
        vector->push_back(offset+2);
        vector->push_back(offset+3);
    }

    void BlockManager::addSide(std::vector<float>* vector, int start, glm::vec2 texPos)
    {
        addDataFromArrayIntoVector(vector, engine::primitives::cubeVertices,
                                   start, VALUES_PER_VERT);
        vector->push_back(texPos.x*ATLAS_FACTOR);
        vector->push_back(texPos.y*ATLAS_FACTOR);

        addDataFromArrayIntoVector(vector, engine::primitives::cubeVertices,
                                    start + VALUES_PER_VERT, VALUES_PER_VERT);
        vector->push_back(texPos.x*ATLAS_FACTOR+ATLAS_FACTOR);
        vector->push_back(texPos.y*ATLAS_FACTOR);

        addDataFromArrayIntoVector(vector, engine::primitives::cubeVertices,
                                   start + 2 * VALUES_PER_VERT, VALUES_PER_VERT);
        vector->push_back(texPos.x*ATLAS_FACTOR+ATLAS_FACTOR);// + ATLAS_FACTOR);
        vector->push_back(texPos.y*ATLAS_FACTOR+ATLAS_FACTOR);// + ATLAS_FACTOR);

        addDataFromArrayIntoVector(vector, engine::primitives::cubeVertices,
                                   start + 3 * VALUES_PER_VERT, VALUES_PER_VERT);
        vector->push_back(texPos.x*ATLAS_FACTOR);
        vector->push_back(texPos.y*ATLAS_FACTOR+ATLAS_FACTOR);// + ATLAS_FACTOR);
    }

    template<typename T>
    void BlockManager::addDataFromArrayIntoVector(std::vector<T>* vector, T* array, int start, int number)
    {
        for(int i = start; i < start+number; i++)
        {
            vector->push_back(array[i]);
        }
    }

    /*
     * BlockCode:
     * 0    - hasTop
     * 1    - hasBottom
     * 2    - hasBack
     * 3    - hasFront
     * 4    - hasRight
     * 5    - hasLeft
     * 6-13 - Block ID
     * Rest - not used
     */
    uint32_t BlockManager::getBlockCode(uint8_t blockID, bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight)
    {
        uint32_t output = 0;

        //Add BlockID
        output |= blockID;

        //Add hasLeft
        output <<= 1;
        output |= hasLeft;

        //Add hasRight
        output <<= 1;
        output |= hasRight;

        //Add hasBack
        output <<= 1;
        output |= hasBack;

        //Add hasBottom
        output <<= 1;
        output |= hasBottom;

        //Add hasTop
        output <<= 1;
        output |= hasTop;

        return output;
    }
}