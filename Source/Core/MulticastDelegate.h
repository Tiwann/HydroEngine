#pragma once
#include "Function.h"

#include <vector>

namespace Hydro
{
	template<typename... Params>
	class MulticastDelegate
	{
	public:
		using DelegateType = Function<void, Params...>;
		MulticastDelegate() = default;

		bool IsBound() const { return !m_Subscribers.empty(); }
		
		void Bind(DelegateType Subscriber)
		{
			m_Subscribers.push_back(Subscriber);
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
		
		void Broadcast(Params... Parameters)
		{
			for (auto it = m_Subscribers.begin(); it != m_Subscribers.end(); ++it)
			{
				DelegateType* Delegate = &(*it);
				(void)Delegate->CallChecked(std::forward<Params>(Parameters)...);
			}
		}

	private:
		std::vector<DelegateType> m_Subscribers;
	};
}