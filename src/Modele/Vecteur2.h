#pragma once
#include <tuple>
#include <string>
#include <SFML/System/Vector2.hpp>

typedef unsigned short ushort;

template<class T>
struct Vecteur2
{
	Vecteur2(const T& x, const T& y): x(x), y(y) {}
	
	Vecteur2(const sf::Vector2<T>& sfVecteur): x(sfVecteur.x), y(sfVecteur.y){}
	Vecteur2<T>& operator= (const sf::Vector2<T>& sfVecteur) { return Vecteur2<T>(sfVecteur.x,sfVecteur.y); }
	operator sf::Vector2<T>() { return sf::Vector2<T>(x,y); }

	Vecteur2() : x(T(0)), y(T(0)) {}

	Vecteur2& operator+=(const Vecteur2& v) { x += v.x; y += v.y; return *this; }
	Vecteur2& operator-=(const Vecteur2& v) { x -= v.x; y -= v.y; return *this; }

	friend bool operator==(const Vecteur2& v1, const Vecteur2& v2) { return std::tie(v1.x, v1.y) == std::tie(v2.x, v2.y); }
	friend bool operator!=(const Vecteur2& v1, const Vecteur2& v2) { return !(v1 == v2); }
	friend bool operator<(const Vecteur2& v1, const Vecteur2& v2) { return v1.x*v1.y + v1.x < v2.x*v2.y + v2.x; }
	Vecteur2 operator-() const { return Vecteur2(-x, -y); }

	Vecteur2& operator*=(const T& s) { x *= s; y *= s; return *this; }
	Vecteur2& operator/=(const T& s) { if (s == 0) throw std::logic_error("division by 0");  x /= s; y /= s; return *this; }
	
	T x = 0;
	T y = 0;
	
	static const Vecteur2<T> NORD;
	static const Vecteur2<T> EST;
	static const Vecteur2<T> SUD;
	static const Vecteur2<T> OUEST;
};

template<class T> Vecteur2<T> const Vecteur2<T>::NORD = Vecteur2<T>(0, 1);
template<class T> Vecteur2<T> const Vecteur2<T>::EST = Vecteur2<T>(1, 0);
template<class T> Vecteur2<T> const Vecteur2<T>::SUD = Vecteur2<T>(0, -1);
template<class T> Vecteur2<T> const Vecteur2<T>::OUEST = Vecteur2<T>(-1, 0);

template<class T> Vecteur2<T> operator+(const Vecteur2<T>& v1, const Vecteur2<T>& v2) { return Vecteur2<T>(v1) += v2; };
template<class T> Vecteur2<T> operator-(const Vecteur2<T>& v1, const Vecteur2<T>& v2) { return Vecteur2<T>(v1) -= v2; };
template<class T> Vecteur2<T> operator*(const Vecteur2<T>& v, const T& s) { return Vecteur2<T>(v) *= s; };
template<class T> Vecteur2<T> operator/(const Vecteur2<T>& v, const T& s) { return Vecteur2<T>(v) /= s; };

namespace std 
{
	template<class T> std::string to_string(Vecteur2<T> c) { return "["+to_string(c.x)+","+to_string(c.y)+"]"; }
}

enum Direction 
{
	NORD,
	EST,
	SUD,
	OUEST
};