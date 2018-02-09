#pragma once
#include <tuple>
#include "yaml-cpp/yaml.h"

typedef unsigned short ushort;

template<class T>
struct Point2D
{
	Point2D(const T& x, const T& y): x(x), y(y) {}
	Point2D() : x(T(0)), y(T(0)) {}

	Point2D& operator+=(const Point2D& v) { x += v.x; y += v.y; return *this; }
	Point2D& operator-=(const Point2D& v) { x -= v.x; y -= v.y; return *this; }

	friend bool operator==(const Point2D& v1, const Point2D& v2) { return std::tie(v1.x, v1.y) == std::tie(v2.x, v2.y); }
	friend bool operator!=(const Point2D& v1, const Point2D& v2) { return !(v1 == v2); }
	friend bool operator<(const Point2D& v1, const Point2D& v2) { return v1.x*v1.y + v1.x < v2.x*v2.y + v2.x; }
	Point2D operator-() const { return Point2D(-x, -y); }

	Point2D& operator*=(const T& s) { x *= s; y *= s; return *this; }
	Point2D& operator/=(const T& s) { if (s == 0) throw std::logic_error("division by 0");  x /= s; y /= s; return *this; }
	T x = 0;
	T y = 0;
	
	static const Point2D<T> NORTH;
	static const Point2D<T> EAST;
	static const Point2D<T> SOUTH;
	static const Point2D<T> WEST;
};

template<class T> Point2D<T> const Point2D<T>::NORTH = Point2D<T>(0, 1);
template<class T> Point2D<T> const Point2D<T>::EAST = Point2D<T>(1, 0);
template<class T> Point2D<T> const Point2D<T>::SOUTH = Point2D<T>(0, -1);
template<class T> Point2D<T> const Point2D<T>::WEST = Point2D<T>(-1, 0);

template<class T> Point2D<T> operator+(const Point2D<T>& v1, const Point2D<T>& v2) { return Point2D<T>(v1) += v2; };
template<class T> Point2D<T> operator-(const Point2D<T>& v1, const Point2D<T>& v2) { return Point2D<T>(v1) -= v2; };
template<class T> Point2D<T> operator*(const Point2D<T>& v, const T& s) { return Point2D<T>(v) *= s; };
template<class T> Point2D<T> operator/(const Point2D<T>& v, const T& s) { return Point2D<T>(v) /= s; };

namespace std 
{
	template<class T> std::string to_string(Point2D<T> c) { return "["+to_string(c.x)+","+to_string(c.y)+"]"; }
}

enum Direction 
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

namespace YAML {
	template<class T>
	struct convert<Point2D<T>> {
		static Node encode(const Point2D<T> rhs) {
			Node node;
			node.SetStyle(YAML::EmitterStyle::Flow);
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, Point2D<T>& rhs) {
			if (!node.IsSequence() || node.size() != 2) {
				return false;
			}
			rhs.x = node[0].as<T>();
			rhs.y = node[1].as<T>();
			return true;
		}
	};
}