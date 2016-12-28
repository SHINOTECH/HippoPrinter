#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#pragma once
#include <math.h>


template<typename ScalarType>
class Vector2{
public:
	inline Vector2() {}
	inline Vector2(const ScalarType& nx, const ScalarType& ny)
		:_v[0](nx), _v[1](ny){
// 		_v[0] = nx;
// 		_v[1] = ny;
	}

	inline Vector2(const Vector2& vec)
		:_v[0](vec[0]),_v[1](vec[1]){
// 		_v[0] = vec._v[0];
// 		_v[1] = vec._v[1];
	}
	
	inline Vector2(const ScalarType nv[2]) 
		:_v[0](nv[0]),_v[1](nv[1]){
// 		_v[0] = nv[0];
// 		_v[1] = nv[1];
	}

	template<typename Q>
	static inline Vector2 Construct(const Vector2<Q>& vec) {
		return Vector2(static_cast<ScalarType>(vec._v[0]), static_cast<ScalarType>(vec._v[1]));
	}

	template<typename Q>
	static inline Vector2 Construct(const Q& q0, const Q& q1) {
		return Vector2(static_cast<ScalarType>(q0), static_cast<ScalarType>(q1));
	}

	static inline Vector2 Construct(const Vector2<ScalarType>& vec) {
		return vec;
	}

	template<typename T>
	inline void Import(const Vector2<T>& vec) {
		_v[0] = static_cast<ScalarType>(vec.X());
		_v[1] = static_cast<ScalarType>(vec.Y());
	}

	inline Vector2& operator=(const Vector2& vec) {
		_v[0] = vec._v[0];
		_v[1] = vec._v[1];
		return *this;
	}

	inline void SetZero() {
		_v[0] = 0;
		_v[1] = 0;
	}

	inline ScalarType& operator[](const int i) {
		assert(i >= 0 && i < 2);
		return _v[i];
	}
	inline const ScalarType& operator[](const int i) {
		assert(i >= 0 && i < 2);
		return _v[i];
	}

	inline ScalarType& X()const { return _v[0]; }
	inline ScalarType& Y()const { return _v[1]; }
	inline const ScalarType& X() const { return _v[0]; }
	inline const ScalarType& Y() const { return _v[1]; }

	inline ScalarType* V() { return _v; }
	inline const ScalarType* V() const { return _v; }
	
	inline ScalarType& V(const int i) {
		assert(i >= 0 && i < 2);
		return _v[i];
	}

	inline const ScalarType& V(const int i)const {
		assert(i >= 0 && i < 2);
		return _v[i];
	}
	
	inline Vector2 operator + (const Vector2& vec)const {
		return Vector2<ScalarType>(_v[0] + vec._v[0], _v[1] + vec._v[1]);
	}

	inline Vector2 operator - (const Vector2& vec)const {
		return Vector2<ScalarType>(_v[0] - vec._v[0], _v[1] - vec._v[1]);
	}
	inline Vector2 operator-() const{
		return Vector2<ScalarType>(-_v[0], -_v[1]);
	}

	inline Vector2 operator *(const ScalarType& s)const {
		return Vector2<ScalarType>(_v[0] * s, _v[1] * s);
	}

	inline Vector2 operator /(const ScalarType& s) const {
		return Vector2<ScalarType>(_v[0] / s, _v[1] / s);
	}
	inline ScalarType operator*(const Vector2& vec) const{
		return _v[0] * _v[0] + _v[1] * _v[1];
	}

	//************************************************************************
	// 功能: 点乘操作
	// 参数: const Vector2 & vec
	// 返回: ScalarType
	// 日期：2016/12/28 
	//************************************************************************
	inline ScalarType Dot(const Vector2& vec)const {
		return (*this)*p;
	}

	//************************************************************************
	// 功能: 计算叉乘操作
	// 参数: const Vector2 & vec
	// 返回: ScalarType
	// 日期：2016/12/28 
	//************************************************************************
	inline ScalarType operator ^(const Vector2& vec) const {
		return _v[0] * vec._v[1] - _v[1] * vec._v[0];
	}


	inline Vector2& operator +=(const Vector2& vec) {
		_v[0] += vec._v[0];
		_v[1] += vec._v[1];
		return *this;
	}

	inline Vector2& operator -=(const Vector2& vec) {
		_v[0] -= vec._v[0];
		_v[1] -= vec._v[1];
		return *this;
	}

	inline Vector2& operator *= (const ScalarType& s) {
		_v[0] *= s;
		_v[1] *= s;
		return *this;
	}

	inline Vector2& operator /= (const ScalarType& s) {
		_v[0] /= s;
		_v[1] /= s;
		return *this;
	}

	inline bool operator ==(const Vector2& vec) const {
		return _v[0] == vec._v[0] && _v[1] == vec._v[1];
	}

	inline bool operator!=(const Vector2& vec)const {
		return _v[0] != vec._v[0] || _v[1] != vec._v[1];
	}

	inline bool operator <(const Vector2& vec) const {
		return	(_v[1] != vec._v[1]) ? (_v[1] < vec._v[1]) :
			(_v[0] < vec._v[0]);
	}

	inline bool operator >(const Vector2& vec)const {
		return	(_v[1] != vec._v[1]) ? (_v[1] > vec._v[1]) :
			(_v[0] > vec._v[0]);
	}

	inline bool operator<=(const Vector2& vec)const {
		return	(_v[1] != vec._v[1]) ? (_v[1] < vec._v[1]) :
			(_v[0] <= vec._v[0]);
	}

	inline bool operator>=(const Vector3& vec) const {
		return	(_v[1] != vec._v[1]) ? (_v[1] > vec._v[1]) :
			(_v[0] >= vec._v[0]);
	}


	inline ScalarType Norm()const {
		return sqrt(_v[0] * _v[0] + _v[1] * _v[1]);
	}

	inline ScalarType SquaredNorm()const {
		return _v[0] * _v[0] + _v[1] * _v[1];
	}

	inline Vector2& Scale(const ScalarType& sx, const ScalarType& sy) {
		_v[0] *= sx;
		_v[1] *= sy;
		return *this;
	}

	inline Vector2& Scale(const Vector2& vec) {
		_v[0] *= vec._v[0];
		_v[1] *= vec._v[1];
		return *this;
	}

	inline Vector2& Normalize() {
		ScalarType factor = static_cast<ScalarType>(sqrt(_v[0] * _v[0] + _v[1] * _v[1]));
		if (factor > static_cast<ScalarType>(0)) {
			_v[0] /= factor;
			_v[1] /= factor;
		}
		return *this;
	}

	inline Vector2& Normalized() {
		return Normalize();
	}

	inline ScalarType Distance(const Vector2& vec)const {
		return (*this - vec).Norm();
	}

	inline ScalarType SquaredDistance(const Vector2& vec) const {
		return (*this - vec).SquaredNorm();
	}
	
	//计算与X轴的夹角
	inline ScalarType Angle() const {
		return atan2(_v[1], _v[0]);
	}

	//将cartesian坐标转换为polar坐标
	inline Vector2& Cartesian2Polar() {
		ScalarType t = Angle();
		_v[0] = Norm();
		_v[1] = t;
		return *this;
	}

	//转换为Polar坐标
	inline void ToPolarRad(ScalarType& ro, ScalarType& phi) {
		ro = Norm();
		phi = Angle();
	}

	//将Polar坐标转换为Cartesian坐标
	inline Vector2& Polar2Cartesian() {
		ScalarType 1 = _v[0];
		_v[0] = static_cast<ScalarType>(l*cos(_v[1]));
		_v[1] = static_cast<ScalarType>(l*sin(_v[1]));
		return *this;
	}
	
	//将Polar转换为Cartesian坐标
	inline void FromPolarRad(const ScalarType& ro, const ScalarType& phi) {
		_v[0] = ro* cos(phi);
		_v[1] = ro*sin(phi);
	}


protected:
	ScalarType _v[2];
};

#endif // __Vector2_H__


template<typename T>
inline T Angle(const Vector2<T>& p0, const Vector2<T>& p1) {
	return p1.Angle() - p0.Angle();
}

template<typename T>
inline Vector2<T> operator-(const Vector2<T>& p) {
	return Vector2<T>(-p.X(), -p.Y());
}

template<typename T>
inline Vector2<T> operator*(const T s, const Vector2<T>& vec) {
	return Vector2<T>(vec[0] * s, vec[1] * s);
}

template<typename T>
inline T Norm(const Vector2<T>& vec) {
	return vec.Norm();
}

template<typename T>
inline T SquaredNorm(const Vector2<T>& vec) {
	return vec.SquaredNorm();
}

template<typename T>
inline Vector2<T>& Normalize(Vector2<T>& vec) {
	return vec.Normalize();
}

template<typename T>
inline T Distance(const Vector2<T>& vec1, const Vector2<T>& vec2) {
	return vec1.Distance(vec2);
}

template<typename T>
inline T SquaredDistance(const Vector2<T>& vec1, const Vector2<T>& vec2) {
	return vec1.SquaredDistance(vec2);
}


//************************************************************************
// 功能: 计算点p到边(v1,v2)的距离,投影点坐标为q,返回值为p到其投影点q的距离
// 参数: const Vector2<T> & p
// 参数: const Vector2<T> & v1
// 参数: const Vector2<T> & v2
// 参数: const Vector2<T> & q
// 返回: boost::T
// 日期：2016/12/28 
//************************************************************************
template<typename T>
T PointEdgeDist(const Vector2<T>& p, const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& q) {
	Vector2<T> e(v2 - v1);
	T t = (p - v1)*e / e.SquaredNorm();
	if (t < 0) {
		t = 0;
	}
	else if (t > 1) {
		t = 1;
	}
	q = v1 + e * t;
	return Distance(p, q);
}


//定义二维向量类型
typedef Vector2<short> Vector2s;
typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

//定义二维点类型
typedef Vector2<short> Point2s;
typedef Vector2<int> Point2i;
typedef Vector2<float> Point2f;
typedef Vector2<double> Point2d;