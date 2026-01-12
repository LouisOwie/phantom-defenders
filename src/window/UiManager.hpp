#ifndef PHANTOM_DEFENDERS_UIMANAGER_HPP
#define PHANTOM_DEFENDERS_UIMANAGER_HPP

#include <imgui.h>

class UiManager {
public:
    static void setupUI();
    static void showGoldDisplay();
    static void showGameOverScreen();
private:
    static inline unsigned int goldIcon = 0;
    static inline unsigned int gameOverIcon = 0;

    static void showDimmer(float alpha);

    static void ImageOutlinedAtPosition(unsigned int texture, const ImVec2& pos, const ImVec2& size, ImU32 outlineColor, float thickness);
    static void TextOutlinedAtPosition(const char* text, const ImVec2& pos, ImU32 textColor, ImU32 outlineColor);

    static unsigned int loadIconTexture(const char* path);
};
#endif //PHANTOM_DEFENDERS_UIMANAGER_HPP