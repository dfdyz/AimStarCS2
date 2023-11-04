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


void Quaternion::SetEulerAngle(const EulerAngle &ea)
{
	float fCosHRoll = cos(ea.m_fRoll * .5f);
	float fSinHRoll = sin(ea.m_fRoll * .5f);
	float fCosHPitch = cos(ea.m_fPitch * .5f);
	float fSinHPitch = sin(ea.m_fPitch * .5f);
	float fCosHYaw = cos(ea.m_fYaw * .5f);
	float fSinHYaw = sin(ea.m_fYaw * .5f);

	/// Cartesian coordinate System
	//w = fCosHRoll * fCosHPitch * fCosHYaw + fSinHRoll * fSinHPitch * fSinHYaw;
	//x = fSinHRoll * fCosHPitch * fCosHYaw - fCosHRoll * fSinHPitch * fSinHYaw;
	//y = fCosHRoll * fSinHPitch * fCosHYaw + fSinHRoll * fCosHPitch * fSinHYaw;
	//z = fCosHRoll * fCosHPitch * fSinHYaw - fSinHRoll * fSinHPitch * fCosHYaw;

	w = fCosHRoll * fCosHPitch * fCosHYaw + fSinHRoll * fSinHPitch * fSinHYaw;
	x = fCosHRoll * fSinHPitch * fCosHYaw + fSinHRoll * fCosHPitch * fSinHYaw;
	y = fCosHRoll * fCosHPitch * fSinHYaw - fSinHRoll * fSinHPitch * fCosHYaw;
	z = fSinHRoll * fCosHPitch * fCosHYaw - fCosHRoll * fSinHPitch * fSinHYaw;
}

EulerAngle Quaternion::GetEulerAngle() const
{
	EulerAngle ea;

	/// Cartesian coordinate System 
	//ea.m_fRoll  = atan2(2 * (w * x + y * z) , 1 - 2 * (x * x + y * y));
	//ea.m_fPitch = asin(2 * (w * y - z * x));
	//ea.m_fYaw   = atan2(2 * (w * z + x * y) , 1 - 2 * (y * y + z * z));

	ea.m_fRoll  = atan2(2 * (w * z + x * y) , 1 - 2 * (z * z + x * x));
	ea.m_fPitch = asin(CLAMP(2 * (w * x - y * z) , -1.0f , 1.0f));
	ea.m_fYaw   = atan2(2 * (w * y + z * x) , 1 - 2 * (x * x + y * y));

	return ea;
}