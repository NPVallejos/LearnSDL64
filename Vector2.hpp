#pragma once
// Read: https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
// Use method 3 from the article for templates only^
namespace Nick
{
	template <class T>
	class Vector2
	{
	public:
		T x;
		T y;
	public:
		Vector2(T x, T y);
		void Clear();
	};

	template <class T>
	Vector2<T>::Vector2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	template <class T>
	void Vector2<T>::Clear()
	{
		this->x = 0;
		this->y = 0;
	}
} // namespace