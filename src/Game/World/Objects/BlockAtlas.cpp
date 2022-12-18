
#include "BlockAtlas.h"

namespace game::world::object
{
    BlockAtlas::BlockAtlas() :
            blockAtlasTexture("res/textures/TextureAtlas.jpg", GL_RGB, GL_RGB, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, false)
    {
        addBlocks();
    }

    void BlockAtlas::addBlocks()
    {
        blockAtlas.insert({1u,{1u,glm::vec2(0.0f,0.0f),glm::vec2( 1.0f,0.0f),glm::vec2( 2.0f,0.0f)}});
    }

    glm::vec2 BlockAtlas::getSideTexPos(uint8_t blockID)
    {
        return blockAtlas.at(blockID).TexSidePos;
    }

    glm::vec2 BlockAtlas::getTopTexPos(uint8_t blockID)
    {
        return blockAtlas.at(blockID).TexTopPos;
    }

    glm::vec2 BlockAtlas::getBottomTexPos(uint8_t blockID)
    {
        return blockAtlas.at(blockID).TexBottomPos;
    }
}

