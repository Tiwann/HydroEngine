#pragma once
#include <cstdint>

namespace Hydro
{
    class PhysicsWorld;
    
    
    
    class PhysicsBody
    {
    public:
        explicit PhysicsBody(const uintptr_t Handle, PhysicsWorld& World) : m_Handle(Handle), m_World(&World){ }
        virtual ~PhysicsBody() = default;
        PhysicsBody(const PhysicsBody&) = delete;
        PhysicsBody(PhysicsBody&&) noexcept = delete;
        PhysicsBody& operator=(const PhysicsBody&) = delete;
        PhysicsBody& operator=(PhysicsBody&&) noexcept = delete;

        
        virtual void SetUserPointer(void* User) = 0;
        virtual void* GetUserPointer() const = 0;
        
        PhysicsWorld& GetPhysicsWorld() { return *m_World; }
        
        template<typename T>
        T* GetHandleAs() { return reinterpret_cast<T*>(m_Handle); }

        template<typename T>
        const T* GetHandleAs() const { return reinterpret_cast<T*>(m_Handle); }
    protected:
        uintptr_t m_Handle = 0;
        PhysicsWorld* m_World = nullptr;
    };
}
