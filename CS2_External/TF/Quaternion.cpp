#include "Quaternion.h"
#include <math.h>

#define CLAMP(x , min , max) ((x) > (max) ? (max) : ((x) < (min) ? (min) : x))

void Quaternion::Mul(float _x, float _y, float _z, float& ox, float& oy, float& oz) {
	ox = _x * (w * w + x * x - y * y - z * z) +
		_y * 2 * (x * y - w * z) +
		_z * 2 * (w * y + x * z);

	oy = _x * 2 * (w * z + x * y) +
		_y * (w * w - x * x + y * y - z * z) +
		_z * 2 * (y * z - w * x);

	oz = _x * 2 * (x * z - w * y) +
		_y * 2 * (w * x + y * z) +
		_z * (w * w - x * x - y * y + z * z);
}

void Quaternion::SetEulerAngle(float Yaw, float Pitch, float Roll)
{
	float cy = cos(Yaw * 0.5f);
	float sy = sin(Yaw * 0.5f);
	float cp = cos(Pitch * 0.5f);
	float sp = sin(Pitch * 0.5f);
	float cr = cos(Roll * 0.5f);
	float sr = sin(Roll * 0.5f);

	w = cy * cp * cr + sy * sp * sr;
	x = cy * cp * sr - sy * sp * cr;
	y = sy * cp * sr + cy * sp * cr;
	z = sy * cp * cr - cy * sp * sr;
}

void Quaternion::GetEulerAngle(float &r, float &p, float y) const
{

	r  = atan2(2 * (w * z + x * y) , 1 - 2 * (z * z + x * x));
	p = asin(CLAMP(2 * (w * x - y * z) , -1.0f , 1.0f));
	y   = atan2(2 * (w * y + z * x) , 1 - 2 * (x * x + y * y));
}