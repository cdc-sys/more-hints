#include "includes.h"
#include <matdash/console.hpp>
#include <matdash/boilerplate.hpp>

bool faded = true;
bool got_position = true;

class NodeTools {
public:
    void onFinishAnim(cocos2d::CCObject* sender) {
        std::cout << "2" << std::endl;
        auto node = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(sender);
        node->removeFromParent();
    }
};

bool PlayLayer_init(gd::PlayLayer* self) {
    faded = true;
    got_position = false;
    return matdash::orig<&PlayLayer_init>(self);
}
void PlayLayer_showHint(gd::PlayLayer* self) {
    if (!faded) {
        return;
    }
    faded = false;
    auto director = CCDirector::sharedDirector();
    auto winsize = director->getWinSize();
    auto levelID = self->m_level->m_nLevelID;
    const char* hint = "";
    float scale = 0.7f;
    float delay = 3.0f;
    switch (levelID) {
    default:
        hint = "";
        break;
    case 1:
        // Stereo Madness
        hint = "Click / Space to jump over the spikes";
        break;
    case 2:
        // Back on track
        hint = "Touching a Jump Pad will launch you in the air";
        scale = 0.6f;
        delay = 4.0f;
        break;
    case 3:
        // Polargeist
        hint = "Click while touching a ring to jump mid air";
        break;
    case 4:
        // Dry Out
        hint = "Touching a yellow portal will flip your gravity upside down";
        scale = 0.52f;
        delay = 4.5f;
        break;
    case 5:
        // Base after Base
        hint = "Click / Space to jump over the spikes";
        break;
    case 6:
        // Can't let go
        hint = "Click / Space to jump on the block";
        break;
    case 7:
        // Jumper
        hint = "Click / Space to jump on the block";
        break;
    case 8:
        // Time machine
        hint = "Hold Left Click / Space to make progress in the level";
        scale = 0.55f;
        delay = 4.0f;
        break;
    case 9:
        // cycles
        hint = "Click / Space to switch gravity in the Ball gamemode";
        scale = 0.55f;
        delay = 4.0f;
        break;
    case 10:
        // xstep
        hint = "Click / Space to switch gravity in the Ball Gamemode";
        scale = 0.55f;
        delay = 4.0f;
        break;
    case 11:
        // clutterfunk
        hint = "Touching a Mini Portal will make your icon smaller";
        scale = 0.6f;
        delay = 4.0f;
        break;
    case 12:
        // theory of everything
        hint = "Touching a Mini Portal will make your icon smaller";
        scale = 0.6f;
        delay = 4.0f;
        break;
    case 13:
        // electroman adventures
        hint = "Touching a Breakable Block will make it disappear";
        scale = 0.6f;
        delay = 4.0f;
        break;
    case 14:
        // clubstep
        hint = "";
        break;
    case 15:
        // electrodynamix
        hint = "Your speed changes when you touch a Speed Portal";
        scale = 0.5f;
        delay = 4.0f;
        break;
    case 16:
        // hexagon force
        hint = "You split into two when touching a Dual Portal";
        scale = 0.6f;
        delay = 4.0f;
        break;
    case 17:
        // blast processing
        hint = "The wave goes up while you're holding";
        break;
    case 18:
        // theory of everything 2
        hint = "";
        break;
    case 19:
        // geometrical dominator
        hint = "Click / Space to jump over the monster";
        break;
    case 20:
        // deadlocked
        hint = "";
        break;
    case 21:
        // fingerdash
        hint = "Hold to dash!";
        break;
    case 22:
        // dash lmfao
        hint = "2.2 when?";
        break;
    }
    auto text = CCLabelBMFont::create(hint, "bigFont.fnt");
    text->setPosition({ winsize.width * 0.5f,winsize.height * 0.5f + 60.f });
    text->setScale(scale);
    text->setOpacity(0);
    text->runAction(
        CCSequence::create(
        CCFadeIn::create(0.5),
        CCDelayTime::create(delay),
        CCFadeOut::create(0.5),
        CCCallFuncO::create(text,callfuncO_selector(NodeTools::onFinishAnim),text),
        nullptr
        )
    );
    text->setZOrder(999);
    self->addChild(text);
}

void mod_main(HMODULE) {
    // this creates a console window whenever the mod is injected
    // which is very useful for debugging, but make sure to remove
    // on release builds! :D
    matdash::create_console();


    matdash::add_hook<&PlayLayer_showHint>(gd::base + 0x20A910);
    matdash::add_hook<&PlayLayer_init>(gd::base + 0x1FB780);
}