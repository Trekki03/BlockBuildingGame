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

    BlockManager::~BlockManager()
    {
        for(auto& [key, value] : vbs)
        {
            delete value;
        }

        for(auto& [key, value] : ibs)
        {
            delete value;
        }
    }

    std::vector<float>* BlockManager::GetBlockVertexBuffer(uint8_t blockID, bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight)
    {
        // If no block
        if((blockID == 0) || (!hasTop && !hasBottom && !hasBack && !hasFront && !hasLeft && !hasRight))
        {
            return nullptr;
        }

        uint32_t blockCode = GetBlockCode(blockID, hasTop, hasBottom, hasBack, hasFront, hasLeft, hasRight);

        //if already created
        if(vbs.contains(blockCode))
        {
            return vbs.at(blockCode);
        }

        //if new
        auto* vertices = new std::vector<float>;
        if(hasFront)
        {
            AddVerticesForSide(vertices, VERT_FRONT_START, blockAtlas.getSideTexPos(blockID));
        }
        if(hasRight)
        {
            AddVerticesForSide(vertices, VERT_RIGHT_START, blockAtlas.getSideTexPos(blockID));
        }
        if(hasBack)
        {
            AddVerticesForSide(vertices, VERT_BACK_START, blockAtlas.getSideTexPos(blockID));
        }
        if(hasLeft)
        {
            AddVerticesForSide(vertices, VERT_LEFT_START, blockAtlas.getSideTexPos(blockID));
        }
        if(hasBottom)
        {
            AddVerticesForSide(vertices, VERT_BOTTOM_START, blockAtlas.getBottomTexPos(blockID));
        }
        if(hasTop)
        {
            AddVerticesForSide(vertices, VERT_TOP_START, blockAtlas.getTopTexPos(blockID));
        }
        vbs.insert({blockCode, vertices});
        return vertices;
    }

    std::vector<unsigned >* BlockManager::GetBlockIndexBuffer(uint8_t blockID, bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight)
    {
        // If no block
        if((blockID == 0) || (!hasTop && !hasBottom && !hasBack && !hasFront && !hasLeft && !hasRight))
        {
            return nullptr;
        }

        uint32_t blockCode = GetBlockCode(blockID, hasTop, hasBottom, hasBack, hasFront, hasLeft, hasRight);

        //if already created
        if(ibs.contains(blockCode))
        {
            return ibs.at(blockCode);
        }

        //if new
        auto* indices = new std::vector<unsigned int>;
        int offset = 0;
        if(hasFront)
        {
            AddIndicesForSide(indices, offset);
            offset+=4;
        }
        if(hasRight)
        {
            AddIndicesForSide(indices, offset);
            offset+=4;
        }

        if(hasBack)
        {
            AddIndicesForSide(indices, offset);
            offset+=4;
        }
        if(hasLeft)
        {
            AddIndicesForSide(indices, offset);
            offset+=4;
        }
        if(hasBottom)
        {
            AddIndicesForSide(indices, offset);
            offset+=4;
        }
        if(hasTop)
        {
            AddIndicesForSide(indices, offset);
        }
        ibs.insert({blockCode, indices});
        return indices;
    }

    unsigned int BlockManager::GetVertexCount(bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight)
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

    void BlockManager::AddIndicesForSide(std::vector<unsigned int> *vector, int offset)
    {
        vector->push_back(offset);
        vector->push_back(offset+1);
        vector->push_back(offset+3);
        vector->push_back(offset+1);
        vector->push_back(offset+2);
        vector->push_back(offset+3);
    }

    void BlockManager::AddVerticesForSide(std::vector<float>* vector, int start, glm::vec2 texPos)
    {
        AddDataFromArrayIntoVector(vector, engine::primitives::cubeVertices,
                                   start, VALUES_PER_VERT);
        vector->push_back(texPos.x*ATLAS_FACTOR);
        vector->push_back(texPos.y*ATLAS_FACTOR);

        AddDataFromArrayIntoVector(vector, engine::primitives::cubeVertices,
                                   start + VALUES_PER_VERT, VALUES_PER_VERT);
        vector->push_back(texPos.x*ATLAS_FACTOR+ATLAS_FACTOR);
        vector->push_back(texPos.y*ATLAS_FACTOR);

        AddDataFromArrayIntoVector(vector, engine::primitives::cubeVertices,
                                   start + 2 * VALUES_PER_VERT, VALUES_PER_VERT);
        vector->push_back(texPos.x*ATLAS_FACTOR+ATLAS_FACTOR);// + ATLAS_FACTOR);
        vector->push_back(texPos.y*ATLAS_FACTOR+ATLAS_FACTOR);// + ATLAS_FACTOR);

        AddDataFromArrayIntoVector(vector, engine::primitives::cubeVertices,
                                   start + 3 * VALUES_PER_VERT, VALUES_PER_VERT);
        vector->push_back(texPos.x*ATLAS_FACTOR);
        vector->push_back(texPos.y*ATLAS_FACTOR+ATLAS_FACTOR);// + ATLAS_FACTOR);
    }

    template<typename T>
    void BlockManager::AddDataFromArrayIntoVector(std::vector<T>* vector, T* array, int start, int number)
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
    uint32_t BlockManager::GetBlockCode(uint8_t blockID, bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight)
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

        //Add hasBack
        output <<= 1;
        output |= hasFront;

        //Add hasBottom
        output <<= 1;
        output |= hasBottom;

        //Add hasTop
        output <<= 1;
        output |= hasTop;

        return output;
    }
}