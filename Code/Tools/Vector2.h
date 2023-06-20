#pragma once

// struct Vector2 is just a container for any two numbers. It's like an
// std::pair, but two fields are named x and y.
template <typename T>
struct Vector2
{
	T x;
	T y;
};

template <typename T>
inline bool operator==(const Vector2<T>& left, const Vector2<T>& right)
{
	return left.x == right.x && left.y == right.y;
}

template <typename T>
inline bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
{
	return !(left == right);
}

using Vector2u = Vector2<unsigned>;