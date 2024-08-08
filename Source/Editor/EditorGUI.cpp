#include "HydroPCH.h"
#include "EditorGUI.h"

#include "StyleVar.h"
#include "Core/Sprite.h"
#include "Components/Camera.h"
#include "Components/Audio/SoundEmitter.h"
#include "Components/Audio/SoundListener.h"
#include "Components/Physics/Box2D.h"
#include "Components/Rendering/SpriteRenderer.h"
#include "Core/Application.h"
#include "ResourceManager/TextureManager.h"

namespace Hydro::UI
{
    void NewWindow(std::string_view Label, bool& Opened, WindowFlags Flags, const std::function<void()>& Content)
    {
        if(ImGui::Begin(Label.data(), &Opened, Flags.As<ImGuiWindowFlags>()))
        {
            if(Content) Content();
        }
        ImGui::End();
    }
    

    void Text(std::string_view Str)
    {
        ImGui::Text(Str.data());
    }
    
    bool SliderVector2(std::string_view Label, Vector2& Vec, float Min, float Max, std::string_view Format,
                       SliderFlags Flags, bool Enabled)
    {
        ImGui::BeginDisabled(!Enabled);
        const bool Result = ImGui::SliderFloat2(Label.data(), (float*)&Vec, Min, Max, Format.data(), Flags.As<ImGuiSliderFlags>());
        ImGui::EndDisabled();
        return Result;
    }

    bool SliderVector3(std::string_view Label, Vector3& Vec, float Min, float Max, std::string_view Format,
        SliderFlags Flags, bool Enabled)
    {
        ImGui::BeginDisabled(!Enabled);
        const bool Result = ImGui::SliderFloat3(Label.data(), (float*)&Vec, Min, Max, Format.data(), Flags.As<ImGuiSliderFlags>());
        ImGui::EndDisabled();
        return Result;
    }
    bool SliderVector4(std::string_view Label, Vector4& Vec, float Min, float Max, std::string_view Format,
        SliderFlags Flags, bool Enabled)
    {
        ImGui::BeginDisabled(!Enabled);
        const bool Result = ImGui::SliderFloat4(Label.data(), (float*)&Vec, Min, Max, Format.data(), Flags.As<ImGuiSliderFlags>());
        ImGui::EndDisabled();
        return Result;
    }
    

    bool DragVector2(std::string_view Label, Vector2& Vec, float Speed, float Min, float Max, std::string_view Format,
                     SliderFlags Flags, bool Enabled)
    {
        ImGui::BeginDisabled(!Enabled);
        const bool Result = ImGui::DragFloat2(Label.data(), (float*)&Vec, Speed, Min, Max, Format.data(), Flags.As<ImGuiSliderFlags>());
        ImGui::EndDisabled();
        return Result;
    }

    bool DragVector3(std::string_view Label, Vector3& Vec, float Speed, float Min, float Max, std::string_view Format,
        SliderFlags Flags, bool Enabled)
    {
        ImGui::BeginDisabled(!Enabled);
        const bool Result = ImGui::DragFloat3(Label.data(), (float*)&Vec, Speed, Min, Max, Format.data(), Flags.As<ImGuiSliderFlags>());
        ImGui::EndDisabled();
        return Result;
    }

    bool DragVector4(std::string_view Label, Vector4& Vec, float Speed, float Min, float Max, std::string_view Format,
        SliderFlags Flags, bool Enabled)
    {
        ImGui::BeginDisabled(!Enabled);
        const bool Result = ImGui::DragFloat4(Label.data(), (float*)&Vec, Speed, Min, Max, Format.data(), Flags.As<ImGuiSliderFlags>());
        ImGui::EndDisabled();
        return Result;
    }

    bool Button(std::string_view Label, Vector2 Size, bool Enabled)
    {
        ImGui::BeginDisabled(!Enabled);
        const bool Result = ImGui::Button(Label.data(), { Size.x, Size.y });
        ImGui::EndDisabled();
        return Result;
    }
    
    void MenuBar(const TreeNode<MenuItem>& RootNode)
    {
        if (ImGui::BeginMainMenuBar())
        {
            for(const auto& FirstDegreeChild : RootNode)
            {
                if (ImGui::BeginMenu(FirstDegreeChild.GetValue().Name.c_str()))
                {
                    for (const auto& ItemNode : FirstDegreeChild)
                    {
                        const MenuItem& Item = ItemNode.GetValue();
                        if(!Item.Selected)
                        {
                            if (ImGui::MenuItem(Item.Name.c_str(), nullptr, false, Item.Enabled))
                            {
                                if (Item.Callback)
                                    Item.Callback();
                            }
                        } else
                        {
                            if (ImGui::MenuItem(Item.Name.c_str(), nullptr, Item.Selected, Item.Enabled))
                            {
                                if (Item.Callback)
                                    Item.Callback();
                            }
                        }
                        
                    }
                    ImGui::EndMenu();
                }
            }
            ImGui::EndMainMenuBar();
        }
    }

    void AddComponent(const Ref<GameObject>& Object)
    {
        static bool ShowListBox = false;
        
        if(Button("Add Component"))
        {
            ShowListBox = true;
            ImGui::OpenPopup("AddComponent");
        }

        if(ShowListBox && ImGui::BeginPopup("AddComponent"))
        {
            
            const char* ComponentNames[]
            {
                "Camera",
                "Sound Emitter",
                "Sound Listener",
                "Sprite Renderer",
                "Box 2D",
            };

            ImGui::SeparatorText("Add Component");
            for(size_t i = 0; i < std::size(ComponentNames); i++)
            {
                if(ImGui::Selectable(ComponentNames[i]))
                {
                    switch (i)
                    {
                    case 0: Object->AddComponent<Camera>(); break;
                    case 1: Object->AddComponent<SoundEmitter>(); break;
                    case 2: Object->AddComponent<SoundListener>(); break;
                    case 3: Object->AddComponent<SpriteRenderer>(); break;
                    case 4: Object->AddComponent<Box2D>(); break;
                    }
                    ShowListBox = false;
                }
            }
            
            ImGui::EndPopup();
        }
    }

    bool ItemClicked(MouseButton Button)
    {
        return ImGui::IsItemClicked((ImGuiMouseButton)Button);
    }


    void Sprite(Hydro::Sprite& InOutSprite)
    {
        if(ImGui::TreeNode("Sprite"))
        {
            if(InOutSprite.GetTexture())
            {
                ImGui::Image(InOutSprite.GetTexture()->As<ImTextureID>(),
                    InOutSprite.GetTexture()->GetSize(),
                    ImVec2(1, 1), ImVec2(0, 0));
            }

            if(Button("Load Sprite"))
            {
                const Path Filepath = File::OpenFileDialog("Choose an image file", "", "Image Files (*.png)|*.png");
                TextureManager& Manager = Application::GetCurrentApplication().GetTextureManager();
                const std::string Name = Filepath.filename().string();
                const Ref<Texture2D> NewTexture = Manager.Load(Name, Filepath);
                InOutSprite = NewTexture->CreateDefaultSprite();
            }
            ImGui::TreePop();
        }
    }
}

