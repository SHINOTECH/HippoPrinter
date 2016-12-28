#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#pragma once

#include <src/libslic3r/Point.hpp>
using Slic3r::Pointf3;
using Slic3r::Vectorf3;

class Quaternion
{
public:
	Quaternion();
	Quaternion(const double v0, const double v1, const double v2, const double v3);
	Quaternion(const Quaternion& p);
	Quaternion(const double phi, const Pointf3& a);
	Quaternion operator*(const double s) const;
	Quaternion& operator*=(const double s);

	Quaternion operator*(const Quaternion& p) const;
	Quaternion& operator*=(const Quaternion& p);
	
	void Invert();

	Quaternion Inverse() const;

	void SetIdentity();

	void FromAxis(const double phi, const Pointf3& a);
	void ToAxis(double &phi, Pointf3& a) const;

	Pointf3 Rotate(const Pointf3& point) const;
	//TODO:Matrix44
	~Quaternion();

public:
	double q0, q1, q2, q3;

};

#endif // __Quaternion_H__
