#pragma once
#include "Assertion.h"
#include "Core/Containers/DynamicArray.h"
#include "Core/Containers/Function.h"

#define HYDRO_BIND_EVENT(Event, Func) (Event).BindMember(this, (Func))
#define HYDRO_BIND_EVENT_AS(Event, As, Func) (Event).BindMember<As>(this, (Func))

namespace Hydro
{
	template<typename Signature>
	class MulticastDelegate
	{
	public:
		using DelegateType = Function<Signature>;
		using PointerType = typename DelegateType::PointerType;
		template<class Class> using MemberPointerType = typename DelegateType::template MemberPointerType<Class>;
		using DelegateArray = Array<DelegateType>;
		
		MulticastDelegate() = default;

		bool IsBound() const { return !m_Subscribers.IsEmpty(); }
		
		void Bind(DelegateType Subscriber)
		{
			m_Subscribers.Add(Subscriber);
		}

		template<typename Class>
		void BindMember(Class* Instance, MemberPointerType<Class> MemberFunc)
		{
			DelegateType Subscriber;
			Subscriber.BindMember(Instance, MemberFunc);
			m_Subscribers.Add(Subscriber);
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
			for (const DelegateType& Delegate : m_Subscribers)
			{
				Delegate.Call(std::forward<Params>(Parameters)...);
			}
		}

		template<typename... Params>
		void BroadcastChecked(Params... Parameters)
		{
			for(const auto& Delegate : m_Subscribers)
			{
				HYDRO_ASSERT(Delegate, "Tried to broadcast event but found a invalid subscriber");
			}
			
			for (const auto& Delegate : m_Subscribers)
			{
				Delegate.Call(std::forward<Params>(Parameters)...);
			}
		}

	private:
		DelegateArray m_Subscribers;
	};
}