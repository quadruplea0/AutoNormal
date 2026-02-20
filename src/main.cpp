#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    struct Fields {
        bool m_hasResetInPractice = false;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;
        m_fields->m_hasResetInPractice = false;
        return true;
    }

    void resetLevel() {
        if (m_isPracticeMode && m_player1 && m_player1->m_isDead) {
            m_fields->m_hasResetInPractice = true;
        }
        PlayLayer::resetLevel();
    }

    void levelComplete() {
        if (this->m_isPracticeMode && !m_fields->m_hasResetInPractice) {
            this->m_isPracticeMode = false;
            if (Mod::get()->getSettingValue<bool>("ShowPopup")) {
                Notification::create("Practice run converted to Normal", NotificationIcon::Success)->show();
            }
        }
        PlayLayer::levelComplete();
    }
};
