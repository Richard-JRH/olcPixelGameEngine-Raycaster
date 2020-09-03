#include "Vector3.h"

Vector3::Vector3()	// Default constructor
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float _x, float _y)	// Overloaded constructor for 2D Vector
{
	this->x = _x;
	this->y = _y;
	this->z = 0;
}

Vector3::Vector3(float _x, float _y, float _z)	// Overloaded constructor for 3D Vector
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

Vector3::~Vector3()	
{
}

Vector3 Vector3::Up()
{
	return Vector3(0, 1, 0);
}

Vector3 Vector3::Down()
{
	return Vector3(0, -1, 0);
}

Vector3 Vector3::Left()
{
	return Vector3(-1, 0, 0);
}

Vector3 Vector3::Right()
{
	return Vector3(1, 0, 0);
}

Vector3 Vector3::Zero()
{
	return Vector3(0, 0, 0);
}

bool Vector3::Equals(Vector3 v1, Vector3 v2)
{
	return (v1 == v2);
}

std::string Vector3::VecToString()
{
	return std::string(std::to_string(this->x) + ", " + 
					   std::to_string(this->y) + ", " + 
					   std::to_string(this->z));
}

Vector3 Vector3::operator+(Vector3& rhs)	
{
	return Vector3(this->x + rhs.x, 
				   this->y + rhs.y, 
				   this->z + rhs.z);
}

Vector3& Vector3::operator+=(Vector3& rhs)	
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;

	return *this;
}

Vector3 Vector3::operator-(Vector3& rhs)	
{
	return Vector3(this->x - rhs.x, 
					this->y - rhs.y, 
					 this->z - rhs.z);
}

Vector3& Vector3::operator-=(Vector3& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;

	return *this;
}

Vector3 Vector3::operator/(Vector3& rhs)	
{
	return Vector3(this->x / rhs.x,
					this->y / rhs.y,
					 this->z / rhs.z);
}

Vector3& Vector3::operator/=(Vector3& rhs)	
{
	this->x /= rhs.x;
	this->y /= rhs.y;
	this->z /= rhs.z;

	return *this;
}

Vector3 Vector3::operator-()	
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float scalar)	
{
	return Vector3(this->x * scalar,
					this->y * scalar,
					 this->z * scalar);
}

Vector3& Vector3::operator*=(float scalar) 
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;

	return *this;
}

bool Vector3::operator==(Vector3& rhs)
{
	return (this->x == rhs.x &&
			this->y == rhs.y &&
			this->z == rhs.z);
}

bool Vector3::operator!=(Vector3& rhs)
{
	return (this->x != rhs.x ||
			this->y != rhs.y ||
			this->z != rhs.z);
}

Vector3& Vector3::operator=(Vector3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;

	return *this;
}

float Vector3::Magnitude()
{
	return sqrtf(this->x * this->x *
				 this->y * this->y *
				 this->z * this->z);
}

float Vector3::sqrMagnitude()
{
	return (this->x * this->x *
			this->y * this->y *
			this->z * this->z);
}

float Vector3::Dot(Vector3& rhs)
{
	return ((this->x * rhs.x) +
			(this->y * rhs.y) +
			(this->z * rhs.z));
}

Vector3 Vector3::Cross(Vector3& rhs) 
{
	return Vector3((this->y * rhs.z) - (this->z * rhs.y),
					(this->z * rhs.x) - (this->x * rhs.z),
					 (this->x * rhs.y) - (this->y * rhs.x));
}

Vector3 Vector3::Normalized() 
{
	if ( IsZero() )
	{
		throw std::invalid_argument("Zero vector, unable to normalize!");
	}

	float len = Magnitude();

	return Vector3( this->x / len, 
					this->y / len,
					this->z / len );
}

Vector3& Vector3::Normalize()
{
	if ( IsZero() )
	{
		throw std::invalid_argument("Zero vector, unable to normalize!");
	}

	float len = Magnitude();

	this->x /= len;
	this->y /= len;
	this->z /= len;

	return *this;
}

void Vector3::SetZero()	
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

bool Vector3::IsZero()	
{
	return (this->x == 0 && 
			this->y == 0 && 
			this->z == 0);
}

Vector3 Vector3::Get()
{
	return Vector3(this->x, this->y, this->z);
}

float Vector3::GetX()
{
	return this->x;
}

float Vector3::GetY()
{
	return this->y;
}

float Vector3::GetZ()
{
	return this->z;
}

void Vector3::Set(float _x, float _y, float _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

void Vector3::SetX(float _x)
{
	this->x = _x;
}

void Vector3::SetY(float _y)
{
	this->y = _y;
}

void Vector3::SetZ(float _z)
{
	this->z = _z;
}

std::ostream& operator<<(std::ostream& os, Vector3& rhs)
{
	os << rhs.x << ", " << rhs.y << ", " << rhs.z;

	return os;
}
