#include "Quaternion.h"
#include <math.h>


Quaternion::Quaternion(){
	q0 = q1 = q2 = q3 = 0;
}


Quaternion::Quaternion(const double v0, const double v1, const double v2, const double v3):
	q0(v0),q1(v1),q2(v2),q3(v3){

}

Quaternion::Quaternion(const Quaternion& p):
	q0(p.q0),q1(p.q1),q2(p.q2),q3(p.q3){

}

Quaternion::Quaternion(const double phi, const Pointf3& a) {
	FromAxis(phi, a);
}

Quaternion Quaternion::operator*(const double s) const {
	return Quaternion(q0 *s, q1* s, q2*s, q3*s);
}

Quaternion& Quaternion::operator*=(const double s) {
	q0 *= s;
	q1 *= s;
	q2 *= s;
	q3 *= s;
}

Quaternion Quaternion::operator*(const Quaternion& p) const {

}

Quaternion& Quaternion::operator*=(const Quaternion& p) {

}

void Quaternion::Invert() {

}

Quaternion Quaternion::Inverse() const {

}

void Quaternion::SetIdentity() {

}

//************************************************************************
// 日期：2016/12/26 
// 参数: const double phi
// 参数: const Pointf3 & a,对称轴
// 返回: void
// 功能: 根据对称轴计算quatenion
//************************************************************************

void Quaternion::FromAxis(const double phi, const Pointf3& a) {
	Pointf3 b = a;
	b.Normalize();
	double s = std::sin(phi / (2.0));

	q0 = std::cos(phi / (2.0));
	q1 = b.x * s;
	q2 = b.y * s;
	q3 = b.z * s;
}

void Quaternion::ToAxis(double &phi, Pointf3& a) const {

}

Pointf3 Quaternion::Rotate(const Pointf3& point) const {

}

Quaternion::~Quaternion()
{
}
