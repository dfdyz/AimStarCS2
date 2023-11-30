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
	float fCosHRoll = cos(Roll * .5f);
	float fSinHRoll = sin(Roll * .5f);
	float fCosHPitch = cos(Pitch * .5f);
	float fSinHPitch = sin(Pitch * .5f);
	float fCosHYaw = cos(Yaw * .5f);
	float fSinHYaw = sin(Yaw * .5f);

	w = fCosHRoll * fCosHPitch * fCosHYaw + fSinHRoll * fSinHPitch * fSinHYaw;
	x = fCosHRoll * fSinHPitch * fCosHYaw + fSinHRoll * fCosHPitch * fSinHYaw;
	y = fCosHRoll * fCosHPitch * fSinHYaw - fSinHRoll * fSinHPitch * fCosHYaw;
	z = fSinHRoll * fCosHPitch * fCosHYaw - fCosHRoll * fSinHPitch * fSinHYaw;
}

void Quaternion::GetEulerAngle(float &r, float &p, float y) const
{

	r  = atan2(2 * (w * z + x * y) , 1 - 2 * (z * z + x * x));
	p = asin(CLAMP(2 * (w * x - y * z) , -1.0f , 1.0f));
	y   = atan2(2 * (w * y + z * x) , 1 - 2 * (x * x + y * y));
}