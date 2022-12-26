#include "includes.h"
#include <matdash/console.hpp>
#include <matdash/boilerplate.hpp>

bool hintAnimationFinished = true;

class NodeTools {
public:
    void onFinishAnim(cocos2d::CCObject* sender) {
        std::cout << "2" << std::endl;
        auto node = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(sender);
        node->removeFromParent();
    }
};

bool PlayLayer_init(gd::PlayLayer* self) {
    hintAnimationFinished = true;
    return matdash::orig<&PlayLayer_init>(self);
}
void PlayLayer_showHint(gd::PlayLayer* self) {
    std::cout << self->m_level->m_nLevelID << std::endl;
    //std::cout << self->m_level->m_sLevelName;
    if (!hintAnimationFinished) {
        return;
    }
    hintAnimationFinished = false;
    auto director = CCDirector::sharedDirector();
    auto winsize = director->getWinSize();
    auto levelID = self->m_level->m_nLevelID;
    const char* hint = "";
    float scale = 0.7f;
    float delay = 3.0f;
    struct HintData {
        const char* hint = "";
        float scale = 0.7f;
        float delay = 4.0f;
    };

    std::unordered_map<int, HintData> hints = {
        {1, {"Click / Space to jump over the spikes"}},
        {2, {"Touching a Jump Pad will launch you in the air", 0.6f,4.0f}},
        {3, {"Click while touching a ring to jump mid air"}},
        {4,{"Touching a yellow portal will flip your gravity upside down",0.52f,4.0f}},
        {5,{"Click / Space to jump over the spikes"}},
        {6,{"Click / Space to jump on the block"}},
        {7,{"Click / Space to jump on the block"}},
        {8,{"Hold Left Click / Space to make progress in the level",0.55f,4.0f}},
        {9,{"Click / Space to switch gravity in the Ball gamemode",0.55f,4.0f}},
        {10,{"Click / Space to switch gravity in the Ball Gamemode",0.55f,4.0f}},
        {11,{"Touching a Mini Portal will make your icon smaller",0.6f,4.0f}},
        {12,{"Touching a Mini Portal will make your icon smaller",0.6f,4.0f}},
        {13,{"Touching a Breakable Block will make it disappear",0.6f,4.0f}},
        {14,{""}},
        {15,{"Your speed changes when you touch a Speed Portal",0.5f,4.0f}},
        {16,{"You split into two when touching a Dual Portal",0.6f,4.0f}},
        {17,{"The wave goes up while you're holding"}},
        {18,{""}},
        {19,{"Click / Space to jump over the monster"}},
        {20,{""}},
        {21,{"Hold to dash!"}},
        {22,{"2.2 when?"}},
        {3001,{"This level is absolutely filled with bugs"}}
    };
    //std::cout << "hint: " << hints[levelID].hint << " scale: " << hints[levelID].scale << " delay: " << hints[levelID].delay << std::endl;
    auto text = CCLabelBMFont::create(hints[levelID].hint, "bigFont.fnt");
    text->setPosition({ winsize.width * 0.5f,winsize.height * 0.5f + 60.f });
    text->setScale(hints[levelID].scale);
    text->setOpacity(0);
    text->runAction(
        CCSequence::create(
        CCFadeIn::create(0.5),
        CCDelayTime::create(hints[levelID].delay),
        CCFadeOut::create(0.5),
        CCCallFuncO::create(text,callfuncO_selector(NodeTools::onFinishAnim),text),
        nullptr
        )
    );
    text->setZOrder(999);
    self->addChild(text);
}
void PlayLayer_destroyPlayer(gd::PlayLayer* self, PlayerObject* player, GameObject* object) {
    matdash::orig<&PlayLayer_destroyPlayer>(self, player, object);
    if (self->m_currentAttempt == 2 && self->m_jumpCount == 0 && player->getPositionX() > 16.9) {
        if (hintAnimationFinished) {
            PlayLayer_showHint(self);
        }
    }
}
void mod_main(HMODULE) {
    // this creates a console window whenever the mod is injected
    // which is very useful for debugging, but make sure to remove
    // on release builds! :D
    matdash::create_console();

    //0x20A1A0
    matdash::add_hook<&PlayLayer_destroyPlayer>(gd::base + 0x20A1A0);
    matdash::add_hook<&PlayLayer_showHint>(gd::base + 0x20A910);
    matdash::add_hook<&PlayLayer_init>(gd::base + 0x1FB780);
}