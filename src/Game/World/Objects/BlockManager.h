
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
        std::map<uint32_t, engine::VertexArrayObject*> vaos;
        std::map<uint32_t, unsigned int> vertexCount;
        std::vector<engine::VertexBuffer*> vbs;
        std::vector<engine::IndexBuffer*> ibs;
        game::world::object::BlockAtlas blockAtlas;
    private:
        uint32_t getBlockCode(uint8_t blockID, bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight);
        template<typename T>
        void addDataFromArrayIntoVector(std::vector<T>* vector, T* array, int start, int number);
        void addSide(std::vector<float>* vector, int start, glm::vec2 texPos);
        void addIndicesforSide(std::vector<unsigned int>* vector, int offset);
    public:
        BlockManager() = default;
        //TODO Deconstuctor deleting als vb, ib and vao
        engine::VertexArrayObject* getBlockVao(uint8_t blockID, bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight);
        unsigned int getVertexCount(bool hasTop, bool hasBottom, bool hasBack, bool hasFront, bool hasLeft, bool hasRight);
    };

} // game

#endif //BLOCKBUILDINGGAME_BLOCKMANAGER_H
