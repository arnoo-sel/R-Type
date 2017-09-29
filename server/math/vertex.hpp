#ifndef VERTEX
# define VERTEX

#include <iostream>
#include "sockets/iSocket.hpp"

using namespace std;

extern const int blockSize;

// Vertex : this class define a simple maths vertex (2 coordinates)
// and their operations

template<typename T = int>
class Vertex
{
public:
    Vertex(T initX = 0, T initY = 0) : x(initX), y(initY) {}
    template<typename F>
    Vertex(const Vertex<F>& other) : x(other.x), y(other.y) {}
    Vertex(string s)
    {
        x = Formater::unpack<T>(s);
        y = Formater::unpack<T>(s);
    }
    string  serialize() const
    {
        string  t;

        t = Formater::pack<T>(t, x);
        t = Formater::pack<T>(t, y);
        return (t);
    }
    template<typename F>
    const Vertex&   operator=(const Vertex<F>& other)
    {
        x = other.x;
        y = other.y;
        return (*this);
    }
    template<typename F>
    const Vertex    operator+(const Vertex<F>& other) const
    {
        Vertex<T>   res(x + other.x, y + other.y);
        return res;
    }
    template<typename F>
    const Vertex    operator-(const Vertex<F>& other) const
    {
        Vertex<T>   res(x - other.x, y - other.y);
        return res;
    }
    template<typename F>
    const Vertex    operator*(const Vertex<F>& other) const
    {
        Vertex<T>   res(x * other.x, y * other.y);
        return res;
    }
    template<typename F>
    const Vertex    operator/(const Vertex<F>& other) const
    {
        Vertex<T>   res(x / other.x, y / other.y);
        return res;
    }
    template<typename F>
    const Vertex&   operator+=(const Vertex<F>& other)
    {
        x += other.x;
        y += other.y;
        return (*this);
    }
    template<typename F>
    const Vertex&   operator-=(const Vertex<F>& other)
    {
        x -= other.x;
        y -= other.y;
        return (*this);
    }
    template<typename F>
    const Vertex&   operator*=(const F& other)
    {
        x *= other;
        y *= other;
        return (*this);
    }
    template<typename F>
    const Vertex&   operator/=(const F& other)
    {
        x /= other;
        y /= other;
        return (*this);
    }
    template<typename F>
    bool      operator==(const F& other)
    {
        return ((x == other.x) && (y == other.y));
    }
    template<typename F>
    const Vertex   operator*(const F& other)
    {
        Vertex<T>   res(x * other, y * other);
        return res;
    }
    // Convert the pixel coordinate into blocks
    Vertex<T>  toBlock()
    {
        return (Vertex<int>((int)x / blockSize, (int)y / blockSize));
    }
    double	len() const
    {
        return (sqrt(x*x + y*y));
    }
	Vertex<T>	normalized() const
	{
        Vertex<T>   res(*this);
        if (len() > 0.01)
            res /= len();
        return res;
	}

    // Get block position in pixels
    Vertex<T>  toPix()
    {
        return (Vertex<int>((int)x * blockSize, (int)y * blockSize));
    }

    T   x;
    T   y;
};

template<typename T>
ostream&    operator<<(ostream& os, const Vertex<T>& vertex)
{
    os << "(" << vertex.x << ", " << vertex.y << ")";
    return (os);
}

#endif //VERTEX
