#ifndef __Geometry_H__
#define __Geometry_H__

#include <math.h>
#include <iostream>

using namespace std;

#define PI 3.14159265
#define Radians(angle) (angle*PI)/180.00

class Vector3D
{
public:

    Vector3D(): X(0), Y(0), Z(0) {}
    Vector3D(float x, float y) : X(x), Y(y), Z(0) {}
    Vector3D(float x, float y, float z) : X(x), Y(y), Z(z) {}
    ~Vector3D() {}
    
    float getX() { return X; }
    float getY() { return Y; }
    float getZ() { return Z; }

    void setX(float x) { X = x; }
    void setY(float y) { Y = y; }
    void setZ(float z) { Z = z; }

    float length() { return sqrt(X * X + Y * Y + Z * Z); }

    Vector3D polar(float radius, float angle) // Plano 2D
    {        
        if (angle < 0)   angle += 180;
        if (angle > 360) angle = int(angle) % 360 + angle - int(angle);
        if (radius < 0)  radius = 0; 

        return Vector3D(
            X + radius * cos(Radians(angle)),
            Y + radius * sin(Radians(angle)),
            Z
        );
    }

    Vector3D negative() { return Vector3D(-X, -Y, -Z); }

    Vector3D& operator=(const Vector3D& v2)
    {
        X = v2.X;
        Y = v2.Y;
        Z = v2.Z;
        
        return *this;
    }

    Vector3D operator+(const Vector3D& v2) const
    {
        return Vector3D(X + v2.X, Y + v2.Y, Z + v2.Z);
    }
    
    Vector3D& operator+=(const Vector3D& v2)
    {
        X += v2.X;
        Y += v2.Y;
        Z += v2.Z;
        
        return *this;
    }
    
    Vector3D operator-(const Vector3D& v2) const
    {
        return Vector3D(X - v2.X, Y - v2.Y, Z - v2.Z);
    }
    
    Vector3D& operator-=(const Vector3D& v2)
    {
        X -= v2.X;
        Y -= v2.Y;
        Z -= v2.Z;
        
        return *this;
    }

    Vector3D operator*(float scalar)
    {
        return Vector3D(X * scalar, Y * scalar, Z * scalar);
    }

    Vector3D& operator*=(float scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        
        return *this;
    }

    Vector3D operator/(float scalar)
    {
        return Vector3D(X / scalar, Y / scalar, Z / scalar);
    }

    Vector3D& operator/=(float scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        
        return *this;
    }
    
    void normalize()
    {
        float l = length();
        if(l > 0)
        {
            (*this) *= 1 / l;
        }
    }

    string str()
    {
        return "(" + csv() + ")";
    }

    string csv()
    {
        return to_string(X) + "," + to_string(Y) + "," + to_string(Z);
    }

    void show()
    {
        cout << str() << endl;
    }

private:

    float X;
    float Y;
    float Z;
};

#endif // __Geometry_H__