#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <string>
#include <ostream>

class Vector3
{
public:
	float x, y, z;
public:
	Vector3();
	Vector3(float _x, float _y);
	Vector3(float _x, float _y, float _z);
	~Vector3();

	// Static Properties
	Vector3 Up();
	Vector3 Down();
	Vector3 Left();
	Vector3 Right();
	Vector3 Zero();

	// Public methods
	bool Equals(Vector3 v1, Vector3 v2);
	std::string VecToString();

	// Operator Overloads
	Vector3 operator+(Vector3& rhs);
	Vector3& operator+=(Vector3& rhs);

	Vector3 operator-(Vector3& rhs); 
	Vector3& operator-=(Vector3& rhs);

	Vector3 operator/(Vector3& rhs);
	Vector3& operator/=(Vector3& rhs);

	Vector3 operator-(); 

	Vector3 operator*(float scalar); 
	Vector3& operator*=(float scalar);

	bool operator==(Vector3& rhs);
	bool operator!=(Vector3& rhs);

	Vector3& operator=(Vector3& rhs); 

	float Magnitude();
	float sqrMagnitude() ;

	float Dot(Vector3& rhs); 
	Vector3 Cross(Vector3& rhs) ;

	////Return a copy of this vector, normalized
	////Throw a divide by zero exception if normalizing a zero vector
	Vector3 Normalized() ; // throw(DivideByZero);

	//Normalize this vector and return a reference to it
	//Throw a divide by zero exception if normalizing a zero vector
	Vector3& Normalize(); // throw(DivideByZero);

	friend std::ostream& operator<<(std::ostream& os, Vector3& rhs); //print to ostream

	// friend Vector3 operator*(float scalar, const Vector3& rhs); //what is this for?

	// Getters/setters
	void SetZero();
	bool IsZero();

	Vector3 Get();
	float GetX();
	float GetY();
	float GetZ();

	void Set(float x, float y, float z);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
};

#endif
