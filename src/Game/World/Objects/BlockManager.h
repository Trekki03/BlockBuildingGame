
#ifndef BLOCKBUILDINGGAME_BLOCKMANAGER_H
#define BLOCKBUILDINGGAME_BLOCKMANAGER_H

#include <map>
#include <cstdint>
#include <vector>
#include "Engine/Render/VertexArrayObject.h"
#include "Engine/Render/VertexBuffer.h"
#include "Engine/Render/IndexBuffer.h"
#include "BlockAtlas.h"

namespace game
{

    class BlockManager
    {
    private:
        game::world::object::BlockAtlas blockAtlas;
        std::map<uint32_t, std::vector<float>*> vbs;
        std::map<uint32_t, std::vector<unsigned >*> ibs;
        std::map<uint32_t, unsigned int> vertexCount;

    private:
        static uint32_t GetBlockCode(uint8_t blockID, bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight);

        template<typename T>
        void AddDataFromArrayIntoVector(std::vector<T>* vector, T* array, int start, int number);

        void AddVerticesForSide(std::vector<float>* vector, int start, glm::vec2 texPos);
        static void AddIndicesForSide(std::vector<unsigned int> *vector, int offset);
    public:
        BlockManager() = default;
        ~BlockManager();

        std::vector<float>* GetBlockVertexBuffer(uint8_t blockID, bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight);
        std::vector<unsigned >* GetBlockIndexBuffer(uint8_t blockID, bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight);

        static unsigned int GetVertexCount(bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight);
    };

} // game

#endif //BLOCKBUILDINGGAME_BLOCKMANAGER_H
