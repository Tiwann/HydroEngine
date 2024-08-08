#pragma once
#include "imgui/imgui.h"

namespace Hydro::UI
{
    enum class StyleVar
    {
        Alpha,                    // float     Alpha
        DisabledAlpha,            // float     DisabledAlpha
        WindowPadding,            // ImVec2    WindowPadding
        WindowRounding,           // float     WindowRounding
        WindowBorderSize,         // float     WindowBorderSize
        WindowMinSize,            // ImVec2    WindowMinSize
        WindowTitleAlign,         // ImVec2    WindowTitleAlign
        ChildRounding,            // float     ChildRounding
        ChildBorderSize,          // float     ChildBorderSize
        PopupRounding,            // float     PopupRounding
        PopupBorderSize,          // float     PopupBorderSize
        FramePadding,             // ImVec2    FramePadding
        FrameRounding,            // float     FrameRounding
        FrameBorderSize,          // float     FrameBorderSize
        ItemSpacing,              // ImVec2    ItemSpacing
        ItemInnerSpacing,         // ImVec2    ItemInnerSpacing
        IndentSpacing,            // float     IndentSpacing
        CellPadding,              // ImVec2    CellPadding
        ScrollbarSize,            // float     ScrollbarSize
        ScrollbarRounding,        // float     ScrollbarRounding
        GrabMinSize,              // float     GrabMinSize
        GrabRounding,             // float     GrabRounding
        TabRounding,              // float     TabRounding
        TabBorderSize,            // float     TabBorderSize
        TabBarBorderSize,         // float     TabBarBorderSize
        TabBarOverlineSize,       // float     TabBarOverlineSize
        TableAngledHeadersAngle,  // float     TableAngledHeadersAngle
        TableAngledHeadersTextAlign,// ImVec2  TableAngledHeadersTextAlign
        ButtonTextAlign,          // ImVec2    ButtonTextAlign
        SelectableTextAlign,      // ImVec2    SelectableTextAlign
        SeparatorTextBorderSize,  // float     SeparatorTextBorderSize
        SeparatorTextAlign,       // ImVec2    SeparatorTextAlign
        SeparatorTextPadding,     // ImVec2    SeparatorTextPadding
        DockingSeparatorSize,     // float     DockingSeparatorSize
    };

    template<typename T>
    class ScopedStyleVarPusher
    {
    public:
        ScopedStyleVarPusher(StyleVar Var, T Value) : m_Variable(std::move(Var))
        {
            ImGui::PushStyleVar((ImGuiStyleVar)Var, Value);
        }

        ~ScopedStyleVarPusher()
        {
            ImGui::PopStyleVar();
        }
    private:
        StyleVar m_Variable;
    };
}
