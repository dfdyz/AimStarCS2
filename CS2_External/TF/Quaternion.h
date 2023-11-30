#pragma once

class Quaternion
{
public:
	float x , y , z , w;
public:
	Quaternion(void) : x(0.0f) , y(0.0f) , z(0.0f) , w(1.0f) {}
	~Quaternion(void) {}
	void Mul(float x, float y, float z, float& ox, float& oy, float &oz);
	void SetEulerAngle(float Yaw, float Pitch, float  Roll);
	void GetEulerAngle(float& r, float& p, float y) const;
};
