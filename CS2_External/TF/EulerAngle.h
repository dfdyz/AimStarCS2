#pragma once

class EulerAngle
{
public:
	float m_fYaw , m_fPitch, m_fRoll;
public:
	EulerAngle(void): m_fYaw(0.0f) , m_fPitch(0.0f) , m_fRoll(0.0f) {}
	EulerAngle(float y, float p, float r) {
		m_fYaw = y;
		m_fPitch = p;
		m_fRoll = r;
	}
	~EulerAngle(void) {}
};
