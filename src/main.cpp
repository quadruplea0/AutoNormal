#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    struct Fields {
        int m_sessionAttemptCount = 0;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;
        m_fields->m_sessionAttemptCount = 0;
        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        m_fields->m_sessionAttemptCount++;
    }

    void levelComplete() {
        if (this->m_isPracticeMode && 
            m_fields->m_sessionAttemptCount <= 1 && 
            this->m_player1 && !this->m_player1->m_isDead) {
            
            this->m_isPracticeMode = false;
            Notification::create("Practice run counted as normal", NotificationIcon::Success)->show();
        }

        PlayLayer::levelComplete();
    }
};
