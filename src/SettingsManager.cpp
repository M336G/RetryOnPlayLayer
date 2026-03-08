#include "SettingsManager.h"

using namespace geode::prelude;

SettingsManager::DisplaySettings SettingsManager::Display = {
    Mod::get()->getSettingValue<int>("button-width"),
    Mod::get()->getSettingValue<int>("button-height"),
    Mod::get()->getSettingValue<float>("button-size"),
    round(Mod::get()->getSettingValue<int>("button-opacity") / 100.f * 255)
};

SettingsManager::OtherSettings SettingsManager::Other = {
    Mod::get()->getSettingValue<bool>("only-retry-if-doubleclicked"),
    Mod::get()->getSettingValue<int>("only-retry-if-doubleclicked-delay")
};

$execute {
    listenForSettingChanges<int>("button-width", [](int width) {
        SettingsManager::Display.width = width;
    });
    listenForSettingChanges<int>("button-height", [](int height) {
        SettingsManager::Display.height = height;
    });
    listenForSettingChanges<float>("button-size", [](float size) {
        SettingsManager::Display.size = size;
    });
    listenForSettingChanges<int>("button-opacity", [](int opacity) {
        SettingsManager::Display.opacity = round(opacity / 100.f * 255);
    });

    listenForSettingChanges<bool>("only-retry-if-doubleclicked", [](bool enabled) {
        SettingsManager::Other.onlyRetryIfDoubleclicked = enabled;
    });
    listenForSettingChanges<int>("only-retry-if-doubleclicked-delay", [](int delay) {
        SettingsManager::Other.onlyRetryIfDoubleclickedDelay = delay;
    });
};