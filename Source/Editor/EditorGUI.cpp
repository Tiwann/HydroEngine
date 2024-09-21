#include "EditorGUI.h"
#include "StyleVar.h"
#include "Core/Sprite.h"
#include "Core/Containers/StringFormat.h"
#include "Core/Application.h"
#include "Components/Camera.h"
#include "Components/Audio/SoundEmitter.h"
#include "Components/Audio/SoundListener.h"
#include "Components/Physics/Box2D.h"
#include "Components/Physics/Circle2D.h"
#include "Components/Rendering/SpriteRenderer.h"
#include "ResourceManager/TextureManager.h"

namespace Hydro::UI
{
    void NewWindow(const StringView Label, bool& Opened, WindowFlags Flags, const Function<void()>& Content)
    {
        if(!Opened) return;
        if(ImGui::Begin(Label, &Opened, Flags.As<ImGuiWindowFlags>()))
        {
            if(Content) Content();
        }
        ImGui::End();
    }
    

    void Text(const StringView Str)
    {
        ImGui::Text(Str);
    }
    
    bool Button(const StringView Label, Vector2 Size, bool Enabled)
    {
        ImGui::BeginDisabled(!Enabled);
        const bool Result = ImGui::Button(Label, { Size.x, Size.y });
        ImGui::EndDisabled();
        return Result;
    }

    static void MenuItemRecursive(const TreeNode<MenuItem>& Node)
    {
        for (const auto& ChildNode : Node)
        {
            const MenuItem& Item = ChildNode.GetValue();
            if(!Item.Selected)
            {
                if (ImGui::MenuItem(Item.Name.Data(), nullptr, false, Item.Enabled))
                {
                    if (Item.Callback)
                        Item.Callback();

                    for(const auto& SubChild : ChildNode)
                        MenuItemRecursive(SubChild);
                }
            } else
            {
                if (ImGui::MenuItem(Item.Name.Data(), nullptr, Item.Selected, Item.Enabled))
                {
                    if (Item.Callback)
                        Item.Callback();

                    for(const auto& SubChild : ChildNode)
                        MenuItemRecursive(SubChild);
                }
            }
                        
        }
    }
    
    void MainMenuMenuBar(const TreeNode<MenuItem>& RootNode)
    {
        if (ImGui::BeginMainMenuBar())
        {
            for(const auto& FirstDegreeChild : RootNode)
            {
                if (ImGui::BeginMenu(FirstDegreeChild.GetValue().Name.Data()))
                {
                    MenuItemRecursive(FirstDegreeChild);
                    ImGui::EndMenu();
                }
            }
            ImGui::EndMainMenuBar();
        }
    }

    void AddComponent(const Ref<Entity>& Entity)
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
                "Circle 2D"
            };

            ImGui::SeparatorText("Add Component");
            for(size_t i = 0; i < std::size(ComponentNames); i++)
            {
                if(ImGui::Selectable(ComponentNames[i]))
                {
                    switch (i)
                    {
                    case 0: Entity->AddComponent<Camera>(); break;
                    case 1: Entity->AddComponent<SoundEmitter>(); break;
                    case 2: Entity->AddComponent<SoundListener>(); break;
                    case 3: Entity->AddComponent<SpriteRenderer>(); break;
                    case 4: Entity->AddComponent<Box2D>(); break;
                    case 5: Entity->AddComponent<Circle2D>(); break;
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
                    ImVec2(0, 1), ImVec2(1, 0));
            }

            if(Button("Load Sprite"))
            {
                const Path Filepath = File::OpenFileDialog("Choose an image file", "", "Image Files (*.png)|*.png");
                TextureManager& Manager = g_Application->GetTextureManager();
                const std::string Name = Filepath.filename().string();
                const Ref<Texture2D> NewTexture = Manager.Load(Name.c_str(), Filepath);
                InOutSprite = NewTexture->CreateSprite();
            }
            ImGui::TreePop();
        }
    }
}

