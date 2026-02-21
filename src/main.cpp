#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    struct Fields {
        int m_resetCount = 0;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;
        m_fields->m_resetCount = 0;
        return true;
    }

    void resetLevel() {

        PlayLayer::resetLevel();

        if (m_player1 && m_player1->m_position.x <= 1.0f) {
            m_fields->m_resetCount = 0;
        }
        if (m_isPracticeMode) {
            m_fields->m_resetCount++;
        }
    }

    void levelComplete() {
        if (this->m_isPracticeMode && m_fields->m_resetCount <= 1) {
            this->m_isPracticeMode = false;
            
            if (Mod::get()->getSettingValue<bool>("ShowPopup")) {
                Notification::create("Practice run converted to Normal", NotificationIcon::Success)->show();
            }
        }
        PlayLayer::levelComplete();
    }
};
