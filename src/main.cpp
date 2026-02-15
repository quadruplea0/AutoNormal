#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    struct Fields {
        int m_sessionStartAttempt = 0;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;
        
        m_fields->m_sessionStartAttempt = level->m_attempts;
        return true;
    }

    void levelComplete() {
        if (this->m_isPracticeMode && this->m_player1 && !this->m_player1->m_isDead) {
            if (this->m_level->m_attempts - m_fields->m_sessionStartAttempt <= 1) {
                this->m_isPracticeMode = false;
                Notification::create("Practice run counted as normal", NotificationIcon::Success)->show();
            }
        }

        PlayLayer::levelComplete();
    }
};
