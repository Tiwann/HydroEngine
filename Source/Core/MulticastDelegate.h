#pragma once
#include <functional>
#include <vector>

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

		bool IsBound() const { return !m_Subscribers.empty(); }
		
		void Bind(DelegateType Subscriber)
		{
			m_Subscribers.push_back(Subscriber);
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
			size_t Position = std::find(m_Subscribers.begin(), m_Subscribers.end(), Subscriber);
			m_Subscribers.erase(Position);
		}

		void operator-=(DelegateType Subscriber)
		{
			Unbind(Subscriber);
		}

		void ClearAll()
		{
			m_Subscribers.clear();
		}

		template<typename... Params>
		void Broadcast(Params... Parameters)
		{
			for (const auto& Delegate : m_Subscribers)
			{
				Delegate(std::forward<Params>(Parameters)...);
			}
		}

	private:
		std::vector<DelegateType> m_Subscribers;
	};
}