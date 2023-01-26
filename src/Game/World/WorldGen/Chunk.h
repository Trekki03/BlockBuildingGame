#ifndef BLOCKBUILDINGGAME_CHUNK_H
#define BLOCKBUILDINGGAME_CHUNK_H

#include <cstdint>
#include "Engine/Render/VertexArrayObject.h"
#include "Game/World/Objects/BlockManager.h"

namespace game
{

    struct Faces
    {
        bool topFace;
        bool bottomFace;
        bool frontFace;
        bool backFace;
        bool leftFace;
        bool rightFace;
    };

    class Chunk
    {
    private:
        game::BlockManager* manager;
        uint8_t blocks[16][256][16] {};
        std::vector<float>* vertexBufferVector;
        std::vector<unsigned int>* indexBufferVector;
        engine::VertexBuffer* vertexBuffer;
        engine::IndexBuffer* indexBuffer;
        engine::VertexArrayObject* vao;

    private:
        void GenerateChunk();
        uint8_t GetBlockTypeAtChunkCoordinate(uint8_t x, uint8_t y, uint8_t z);
        Faces GetBlockFacesAtChunkCoordinate(uint8_t x, uint8_t y, uint8_t z);
        void GenerateVao();
    public:
        Chunk(game::BlockManager* manager);
        engine::VertexArrayObject *GetVao();
    };

} // game

#endif //BLOCKBUILDINGGAME_CHUNK_H
