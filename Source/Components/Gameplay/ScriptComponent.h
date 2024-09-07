#pragma once
#include "Core/Component.h"

namespace Hydro
{
    struct Contact3D;
    struct Contact2D;

    class ScriptComponent : public Component
    {
    public:
        ScriptComponent(Entity* Owner, std::string Name) : Component(Owner, std::move(Name)) {}
    protected:
        void OnInit() override;
        void OnDestroy() override;

        virtual void OnContactBegin2D(const Contact2D& Contact) {}
        virtual void OnContactStay2D(const Contact2D& Contact) {}
        virtual void OnContactEnd2D(const Contact2D& Contact) {}

        virtual void OnContactBegin3D(const Contact3D& Contact) {}
        virtual void OnContactStay3D(const Contact3D& Contact) {}
        virtual void OnContactEnd3D(const Contact3D& Contact) {}
    };
}
