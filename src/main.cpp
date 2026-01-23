#include <Geode/modify/PlayLayer.hpp>

class $modify(MyPlayLayer, PlayLayer) {
	struct Fields {
		int64_t m_buttonWidth = geode::Mod::get()->getSettingValue<int64_t>("button-width");
		int64_t m_buttonHeight = geode::Mod::get()->getSettingValue<int64_t>("button-height");
		double m_buttonSize = geode::Mod::get()->getSettingValue<double>("button-size");
		int64_t m_buttonOpacity = geode::Mod::get()->getSettingValue<int64_t>("button-opacity");
		bool m_onlyRetryIfDoubleclicked = geode::Mod::get()->getSettingValue<bool>("only-retry-if-doubleclicked");

		cocos2d::CCSize m_winSize = cocos2d::CCDirector::get()->getWinSize();

		int64_t m_lastButtonClick = 0;
	};

	bool init(GJGameLevel *level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects))
			return false;

		cocos2d::CCSprite *retryButtonSprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
		retryButtonSprite->setScale(m_fields->m_buttonSize);

		CCMenuItemSpriteExtra *retryButton = CCMenuItemSpriteExtra::create(
			retryButtonSprite,
			this,
			menu_selector(MyPlayLayer::onRetryButton));

		cocos2d::CCNode *uiLayer = this->getChildByID("UILayer");

		retryButton->setID("retry-button"_spr);
		retryButton->setOpacity(static_cast<int64_t>(round(static_cast<double>(m_fields->m_buttonOpacity) / 100 * 255)));

		cocos2d::CCMenu *retryButtonMenu = cocos2d::CCMenu::create();

		retryButtonMenu->setID("retry-button-menu"_spr);
		retryButtonMenu->setPositionX(m_fields->m_winSize.width / 2 + m_fields->m_buttonWidth);
		retryButtonMenu->setPositionY(m_fields->m_winSize.height / 2 + m_fields->m_buttonHeight);

		retryButtonMenu->addChild(retryButton);
		uiLayer->addChild(retryButtonMenu);
		uiLayer->updateLayout();

		return true;
	};

	void onRetryButton(CCObject *) {
		if (m_fields->m_onlyRetryIfDoubleclicked) {
			auto currentTimestamp = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

			if (m_fields->m_lastButtonClick + 500 > currentTimestamp) {
				this->resetLevel();
				m_fields->m_lastButtonClick = 0;
			} else {
				m_fields->m_lastButtonClick = currentTimestamp;
			}
		} else {
			this->resetLevel();
		}
	};
};