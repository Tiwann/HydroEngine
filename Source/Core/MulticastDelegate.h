#pragma once
#include "Assertion.h"
#include "Core/Containers/DynamicArray.h"
#include <functional>

#define HYDRO_BIND_EVENT(Event, Func) (Event).BindMember(this, (Func))
#define HYDRO_BIND_EVENT_AS(Event, As, Func) (Event).BindMember<As>(this, (Func))

namespace Hydro
{
	template<typename Signature>
	class MulticastDelegate
	{
	public:
		using DelegateType = std::function<Signature>;
		MulticastDelegate() = default;

		bool IsBound() const { return !m_Subscribers.IsEmpty(); }
		
		void Bind(DelegateType Subscriber)
		{
			m_Subscribers.Add(Subscriber);
		}

		template<typename Class, typename... Args>
		void BindMember(Class* Instance, void (Class::*MemberFunc)(Args...))
		{
			Bind([Instance, MemberFunc](Args... args)
			{
				(Instance->*MemberFunc)(std::forward<Args>(args)...);
			});
		}

		void operator+=(DelegateType Subscriber)
		{
			Bind(Subscriber);
		}

		void Unbind(DelegateType Subscriber)
		{
			m_Subscribers.RemoveAll(Subscriber);
		}
		
		void operator-=(DelegateType Subscriber)
		{
			Unbind(Subscriber);
		}

		void ClearAll()
		{
			m_Subscribers.Clear();
		}

		template<typename... Params>
		void Broadcast(Params... Parameters)
		{
			for (const auto& Delegate : m_Subscribers)
			{
				Delegate(std::forward<Params>(Parameters)...);
			}
		}

		template<typename... Params>
		void BroadcastChecked(Params... Parameters)
		{
			for(const auto& Delegate : m_Subscribers)
			{
				HYDRO_ASSERT(Delegate, "Tried to broacast event but found a invalid subscriber");
			}
			
			for (const auto& Delegate : m_Subscribers)
			{
				Delegate(std::forward<Params>(Parameters)...);
			}
		}

	private:
		Array<DelegateType> m_Subscribers;
	};
}