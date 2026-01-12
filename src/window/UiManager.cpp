#include "UiManager.hpp"
#include "../scene/World.hpp"
#include <stb_image.h>
#include <iostream>

void UiManager::setupUI() {
    goldIcon = loadIconTexture("../assets/gold_icon.png");
    gameOverIcon = loadIconTexture("../assets/gameOver.png");
}

void UiManager::showGoldDisplay() {
    const ImGuiIO& io = ImGui::GetIO();
    constexpr auto window_size = ImVec2(200, 60);
    const auto window_pos = ImVec2(io.DisplaySize.x - window_size.x - 10, 10);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

    ImGui::Begin("Gold", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoCollapse |
                 ImGuiWindowFlags_NoScrollbar |
                 ImGuiWindowFlags_NoBackground);

    ImGui::SetWindowFontScale(3.0f);

    const ImVec2 cursor = ImGui::GetCursorScreenPos();
    constexpr ImVec2 iconSize(48.0f, 48.0f);

    // gold amount
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%d", World::gold);
    const ImVec2 textSize = ImGui::CalcTextSize(buffer, nullptr, false, 0);

    // right edge
    const ImVec2 windowPos = ImGui::GetWindowPos();
    const ImVec2 windowSize = ImGui::GetWindowSize();
    const float rightEdgeX = windowPos.x + windowSize.x - 10.0f;

    // icon position right
    const ImVec2 iconPos(rightEdgeX - iconSize.x, cursor.y);

    // text position left of icon
    constexpr float spacing = 6.0f;
    const ImVec2 textPos(iconPos.x - spacing - textSize.x, cursor.y + (iconSize.y - textSize.y)/2.0f);

    // Icon
    constexpr ImU32 outlineColor = IM_COL32(0, 0, 0, 255);
    if (goldIcon) {
        constexpr float outlineThickness = 1.5f;
        ImageOutlinedAtPosition(goldIcon, iconPos, iconSize, outlineColor, outlineThickness);
    }
    else {
        TextOutlinedAtPosition("N/A", iconPos, IM_COL32(255, 0, 0, 255), outlineColor);
    }

    // Text
    TextOutlinedAtPosition(buffer, textPos, IM_COL32(255, 215, 0, 255), outlineColor);

    ImGui::Dummy(ImVec2(window_size.x, window_size.y));
    ImGui::SetWindowFontScale(1.0f);
    ImGui::End();
}

void UiManager::showGameOverScreen() {
    showDimmer(0.6f);

    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    // remove padding
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

    if (!ImGui::Begin(
            "GameOverScreen",
            nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNav))
    {
        ImGui::End();
        ImGui::PopStyleVar(3);
        return;
    }
    ImDrawList* draw = ImGui::GetForegroundDrawList();

    // use entire viewport
    const ImVec2 pos = viewport->Pos;
    const ImVec2 size = viewport->Size;

    draw->AddImage(
        gameOverIcon,
        pos,
        ImVec2(pos.x + size.x, pos.y + size.y),
        ImVec2(0.0f, 0.0f),
        ImVec2(1.0f, 1.0f)
    );

    ImGui::End();
    ImGui::PopStyleVar(3);
}

void UiManager::showDimmer(float alpha) {
    const ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw = ImGui::GetForegroundDrawList();

    draw->AddRectFilled(
        ImVec2(0, 0),
        io.DisplaySize,
        IM_COL32(0, 0, 0, static_cast<int>(255 * alpha))
    );
}

void UiManager::ImageOutlinedAtPosition(const unsigned int texture, const ImVec2& pos, const ImVec2& size, ImU32 outlineColor, float thickness)
{
    ImDrawList* draw = ImGui::GetWindowDrawList();

    // outline
    draw->AddImage(texture, ImVec2(pos.x - thickness, pos.y), ImVec2(pos.x - thickness + size.x, pos.y + size.y), ImVec2(0,0), ImVec2(1,1), outlineColor);
    draw->AddImage(texture, ImVec2(pos.x + thickness, pos.y), ImVec2(pos.x + thickness + size.x, pos.y + size.y), ImVec2(0,0), ImVec2(1,1), outlineColor);
    draw->AddImage(texture, ImVec2(pos.x, pos.y - thickness), ImVec2(pos.x + size.x, pos.y - thickness + size.y), ImVec2(0,0), ImVec2(1,1), outlineColor);
    draw->AddImage(texture, ImVec2(pos.x, pos.y + thickness), ImVec2(pos.x + size.x, pos.y + thickness + size.y), ImVec2(0,0), ImVec2(1,1), outlineColor);

    // icon
    draw->AddImage(texture, pos, ImVec2(pos.x + size.x, pos.y + size.y));
}

void UiManager::TextOutlinedAtPosition(const char* text, const ImVec2& pos, ImU32 textColor, ImU32 outlineColor)
{
    ImDrawList* draw = ImGui::GetWindowDrawList();
    const float offset = 1.0f;

    // outline
    draw->AddText(ImVec2(pos.x - offset, pos.y), outlineColor, text);
    draw->AddText(ImVec2(pos.x + offset, pos.y), outlineColor, text);
    draw->AddText(ImVec2(pos.x, pos.y - offset), outlineColor, text);
    draw->AddText(ImVec2(pos.x, pos.y + offset), outlineColor, text);

    // text
    draw->AddText(pos, textColor, text);
}


unsigned int UiManager::loadIconTexture(const char* path) {
    int w, h, channels;
    unsigned char* data = stbi_load(path, &w, &h, &channels, 4);
    if (!data) {
        std::cerr << "Failed to setup UI | Could not load icon texture: " << path << std::endl;
        return 0;
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        w, h,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );

    stbi_image_free(data);
    return tex;
}