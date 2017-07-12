#pragma once
//* a lot of bugs to be fixed!
//1.public swap member function
//2.non-member swap function
//3.for class, specialize std::swap 

#ifndef SWAP_SOME_SOME_H
#define SWAP_SOME_SOME_H

#include <vector>

namespace shizu_function {
	/******pimpl******/
	template<typename T>
	class WidgetImpl
	{
	public:
		/*some public fun and data*/
		WidgetImpl() = default;
		WidgetImpl(T n1,std::vector<T> v1) : a(n1),b(n1),c(n1),v(v1) {}
	private:
		/*probabely private data*/
		T a, b, c;
		std::vector<T> v;
	};

	template<typename T>
	class Widget
	{
	public:
		Widget() = default;
		Widget(WidgetImpl pImpl1) : pImpl(pimp1) { }

		void swap(Widget<T>& other)
		{
			using std::swap;
			swap(pImpl, other.pImpl);
		}
		
	private:
		WidgetImpl *pImpl;
	};

	template<typename T>
	void swap(Widget<T>& a, Widget<T>& b)
	{
		a.swap(b);
	}

}
#endif // !SWAP_SOME_SOME_H
