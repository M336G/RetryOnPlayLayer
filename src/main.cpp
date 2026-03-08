#include <Geode/modify/PlayLayer.hpp>
#include "SettingsManager.h"

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
	struct Fields {
		long long m_lastButtonClick = 0;
	};

	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects))
			return false;

        if (SettingsManager::Display.isVisible()) {
            auto* retryButtonSprite = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
            retryButtonSprite->setScale(SettingsManager::Display.size);

            auto* retryButton = CCMenuItemSpriteExtra::create(
                retryButtonSprite,
                this,
                menu_selector(MyPlayLayer::onRetryButton)
            );
            retryButton->setID("retry-button"_spr);
            retryButton->setOpacity(SettingsManager::Display.opacity);

            auto* retryButtonMenu = CCMenu::create();
            retryButtonMenu->setID("retry-button-menu"_spr);
            retryButtonMenu->setPosition(SettingsManager::Display.getPosition());

            retryButtonMenu->addChild(retryButton);
            m_uiLayer->addChild(retryButtonMenu);
        }

		return true;
	};

	void onRetryButton(CCObject*) {
		if (SettingsManager::Other.onlyRetryIfDoubleclicked) {
			auto currentTimestamp = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

			if (m_fields->m_lastButtonClick + SettingsManager::Other.onlyRetryIfDoubleclickedDelay > currentTimestamp) {
				resetLevel();
				m_fields->m_lastButtonClick = 0;
			} else {
				m_fields->m_lastButtonClick = currentTimestamp;
			}
		} else {
			resetLevel();
		}
	};
};