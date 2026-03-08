#pragma once

class SettingsManager {
private:
    struct DisplaySettings {
        int width;
        int height;
        float size;
        float opacity;

        bool isVisible() const {
            return size > 0 && opacity > 0;
        };

        cocos2d::CCPoint getPosition() const {
            auto winSize = cocos2d::CCDirector::get()->getWinSize();

            return {
                winSize.width / 2 + width,
                winSize.height / 2 + height
            };
        };
    };

    struct OtherSettings {
        bool onlyRetryIfDoubleclicked;
        int onlyRetryIfDoubleclickedDelay;
    };

public:
    static DisplaySettings Display;
    static OtherSettings Other;
};