#ifndef BLOCKBUILDINGGAME_BLOCKATLAS_H
#define BLOCKBUILDINGGAME_BLOCKATLAS_H

#include <cstdint>
#include <glm/glm.hpp>
#include <map>
#include "Engine/Render/Texture2D.h"
#include <cstdint>
#define ATLAS_FACTOR (1.0f/192.0f)
#define ATLAS_WIDTH_HEIGHT 192.0f

namespace game::world::object
{
    struct block
    {
        uint8_t id;
        glm::vec2 TexTopPos;
        glm::vec2 TexBottomPos;
        glm::vec2 TexSidePos;
    };

    class BlockAtlas
    {
    private:
        engine::Texture2D blockAtlasTexture;
        std::map<uint8_t, block> blockAtlas;
        void addBlocks();
    public:
        BlockAtlas();
        glm::vec2 getSideTexPos(uint8_t blockID);
        glm::vec2 getTopTexPos(uint8_t blockID);
        glm::vec2 getBottomTexPos(uint8_t blockID);
    };
}






#endif //BLOCKBUILDINGGAME_BLOCKATLAS_H
