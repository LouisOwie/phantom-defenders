#ifndef PHANTOM_DEFENDERS_UIMANAGER_HPP
#define PHANTOM_DEFENDERS_UIMANAGER_HPP

#include <backends/imgui_impl_opengl3.h>

class UiManager {
public:
    static void setupUI();
    static void showGoldDisplay();

private:
    static inline unsigned int goldIcon = 0;

    static void ImageOutlinedAtPosition(ImTextureID texture, const ImVec2& pos, const ImVec2& size, ImU32 outlineColor, float thickness);
    static void TextOutlinedAtPosition(const char* text, const ImVec2& pos, ImU32 textColor, ImU32 outlineColor);

    static unsigned int loadIconTexture(const char* path);
};
#endif //PHANTOM_DEFENDERS_UIMANAGER_HPP