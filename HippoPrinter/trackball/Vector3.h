#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#pragma once
#include <math.h>



template<typename ScalarType>
class Vector3
{

public:
	inline Vector3() {}
	inline Vector3(const ScalarType x, const ScalarType y, const ScalarType z):
		_v[0](x),_v[1](y),_v[2](z){
// 		_v[0] = x;
// 		_v[1] = y;
// 		_v[2] = z;
	}
	inline Vector3(const Vector3& v):
		_v[0](v[0]), _v[1](v[1]), _v[2](v[2]){
// 		_v[0] = v._v[0];
// 		_v[1] = v._v[1];
// 		_v[2] = v._v[2];
	}
	inline Vector3(const ScalarType nv[3]):
		_v[0](nv[0]), _v[1](nv[1]), _v[2](nv[2]){
// 		_v[0] = nv[0];
// 		_v[1] = nv[1];
// 		_v[2] = nv[2];
	}

	template<typename Q>
	static inline Vector3 Construct(const Vector3<Q>& b) {
		return Vector3(static_cast<ScalarType>(b[0]), static_cast<ScalarType>(b[1]), static_cast<ScalarType>(b[2]);
	}

	template<typename Q>
	static inline Vector3 Construct(const Q& q0, const Q& q1, const Q& q2) {
		return Vector3(static_cast<ScalarType>(q0), static_cast<ScalarType>(q1), static_cast<ScalarType>(q2));
	}

	static inline Construct(const Vector3<ScalarType>& b) {
		return b;
	}

	inline Vector3& operator=(const Vector3& vec) {
		_v[0] = vec._v[0];
		_v[1] = vec._v[1];
		_v[2] = vec._v[2];
		return *this;
	}
	inline void SetZero() {
		_v[0] = 0;
		_v[1] = 0;
		_v[2] = 0;
	}

	inline ScalarType& operator[](const int i) {
		assert(i >= 0 && i < 3);
		return _v[i];
	}

	const ScalarType& operator[](const int i) const {
		assert(i >= 0 && i < 3);
		return _v[i];
	}

	inline ScalarType& X() const { return _v[0]; }
	inline ScalarType& Y() const { return _v[1]; }
	inline ScalarType& Z() const { return _v[2]; }
	inline const ScalarType& X() const { return _v[0]; }
	inline const ScalarType& Y() const { return _v[1]; }
	inline const ScalarType& Z() const { return _v[2]; }

	inline ScalarType* V() {return _v;}

	inline const ScalarType* V() const {return _v;}

	inline ScalarType& V(const int i) {
		assert(i >= 0 && i < 3);
		return _v[i];
	}

	inline const ScalarType& V(const int i)const {
		assert(i >= 0 && i < 3);
		return _v[i];
	}

	inline Vector3 operator+(const Vector3& vec) const {
		return Vector3<ScalarType>(_v[0] + vec._v[0], _v[1] + vec._v[1], _v + vec._v[2]);
	}
	inline Vector3 operator-(const Vector3& vec) const {
		return Vector3<ScalarType>(_v[0] - vec._v[0], _v[1] - vec._v[1], _v - vec._v[2]);
	}
	inline Vector3 operator*(const ScalarType s)const {
		return Vector3<ScalarType>(_v[0] * s, _v[1] * s, _v[2] * s);
	}
	inline Vector3 operator/(const ScalarType s)const {
		return Vector3<ScalarType>(_v[0] / s, _v[1] / s, _v[2] / s);
	}

	inline ScalarType operator*(const Vector3& vec)const {
		return static_cast<ScalarType>(_v[0] * vec._v[0], _v[1] * vec._v[1], _v[2] * vec._v[2]);
	}

	inline ScalarType Dot(const Vector3& vec)const {
		return (*this)*p;
	}

	inline Vector3 operator^(const Vector3& vec)const {
		return Vector3<ScalarType>{
			_v[1]*vec._v[2] - _v[2]*vec._v[1],
			_v[2]*vec._v[0] - _v[0]*vec._v[2],
			_v[0]*vec._v[1] - _v[1]*vec._v[0]
		}
	}

	inline Vector3& operator+=(const Vector3& vec) {
		_v[0] += vec._v[0];
		_v[1] += vec._v[1];
		_v[2] += vec._v[2];
		return *this;
	}
	inline Vector3& operator-=(const Vector3& vec) {
		_v[0] -= vec._v[0];
		_v[1] -= vec._v[1];
		_v[2] -= vec._v[2];
		return *this;
	}
	inline Vector3& operator*=(const ScalarType& s) {
		_v[0] *= s;
		_v[1] *= s;
		_v[2] *= s;
		return *this;
	}
	inline Vector3& operator/=(const ScalarType& s) {
		_v[0] /= s;
		_v[1] /= s;
		_v[2] /= s;
		return *this;
	}
	
	//************************************************************************
	// 功能: 判断两个向量是否相同
	// 参数: const Vector3 & vec
	// 返回: bool
	// 日期：2016/12/28 
	//************************************************************************
	inline bool operator ==(const Vector3& vec)const {
		return _v[0] == vec._v[0] && _v[1] == vec._v[1] && _v[2] == vec._v[2];
	}
	
	//************************************************************************
	// 功能: 判断两个向量值是否相同
	// 参数: const Vector3 & vec
	// 返回: bool
	// 日期：2016/12/28 
	//************************************************************************
	inline bool operator!=(const Vector3& vec)const {
		return _v[0] != vec._v[0] || _v[1] != vec._v[1] || _v[2] != vec._v[2];
	}

	
	//************************************************************************
	// 功能: 比较两个向量的值
	// 参数: const Vector3 & vec
	// 返回: bool
	// 日期：2016/12/28 
	//************************************************************************
	inline bool operator<(const Vector3& vec) const {
		return	(_v[2] != vec._v[2]) ? (_v[2] < vec._v[2]) :
			(_v[1] != vec._v[1]) ? (_v[1] < vec._v[1]) :
			(_v[0] < vec._v[0]);
	}
	
	//************************************************************************
	// 功能: 比较两个向量的值
	// 参数: const Vector3 & vec
	// 返回: bool
	// 日期：2016/12/28 
	//************************************************************************
	inline bool operator >(const Vector3& vec)const {
		return	(_v[2] != vec._v[2]) ? (_v[2] > vec._v[2]) :
			(_v[1] != vec._v[1]) ? (_v[1] > vec._v[1]) :
			(_v[0] > vec._v[0]);
	}
	
	//************************************************************************
	// 功能: 比较两个向量的值
	// 参数: const Vector3 & vec
	// 返回: bool
	// 日期：2016/12/28 
	//************************************************************************
	inline bool operator<=(const Vector3& vec)const {
		return	(_v[2] != vec._v[2]) ? (_v[2] < vec._v[2]) :
			(_v[1] != vec._v[1]) ? (_v[1] < vec._v[1]) :
			(_v[0] <= vec._v[0]);
	}
	
	//************************************************************************
	// 功能: 对两个向量进行比较
	// 参数: const Vector3 & vec
	// 返回: bool
	// 日期：2016/12/28 
	//************************************************************************
	inline bool operator>=(const Vector3& vec) const {
		return	(_v[2] != vec._v[2]) ? (_v[2] > vec._v[2]) :
			(_v[1] != vec._v[1]) ? (_v[1] > vec._v[1]) :
			(_v[0] >= vec._v[0]);
	}
	
	//************************************************************************
	// 功能: 对向量求负
	// 返回: Vector3
	// 日期：2016/12/28 
	//************************************************************************
	inline Vector3 operator -()const {
		return Vector3<ScalarType>(-_v[0], -_v[1], -_v[2]);
	}

	//************************************************************************
	// 功能: 计算向量的长度值
	// 返回: ScalarType
	// 日期：2016/12/28 
	//************************************************************************
	inline ScalarType Norm() const {
		return sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]);
	}

	//************************************************************************
	// 功能: 计算向量的长度平方值
	// 返回: ScalarType
	// 日期：2016/12/28 
	//************************************************************************
	inline ScalarType SquaredNorm() const {
		return (_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]);
	}
	
	//************************************************************************
	// 功能: 对向量进行缩放
	// 参数: const ScalarType & sx
	// 参数: const ScalarType & sy
	// 参数: const ScalarType sz
	// 返回: Vector3&
	// 日期：2016/12/28 
	//************************************************************************
	inline Vector3& Scale(const ScalarType& sx, const ScalarType& sy, const ScalarType sz) {
		_v[0] *= sx;
		_v[1] *= sy;
		_v[2] *= sz;
		return *this;
	}
	
	//************************************************************************
	// 功能: 对向量进行缩放
	// 参数: const Vector3 & vec
	// 返回: Vector3&
	// 日期：2016/12/28 
	//************************************************************************
	inline Vector3& Scale(const Vector3& vec) {
		_v[0] *= vec._v[0];
		_v[1] *= vec._v[1];
		_v[2] *= vec._v[2];
		return *this;
	}
	
	//************************************************************************
	// 功能: 对向量进行单位化
	// 返回: Vector3&
	// 日期：2016/12/28 
	//************************************************************************
	inline Vector3& Normalize() {
		ScalarType factor = static_cast<ScalarType>(sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]));
		if (factor > static_cast<ScalarType>(0)) {
			_v[0] /= factor;
			_v[1] /= factor;
			_v[2] /= factor;
		}
		return *this;
	}

	//************************************************************************
	// 功能: 对向量进行单位化
	// 返回: Vector3&
	// 日期：2016/12/28 
	//************************************************************************
	inline Vector3& Normalized() {
		return Normalize();
	}

	inline ScalarType Distance(const Vector3& vec)const {
		return (*this - vec).Norm();
	}

	inline ScalarType SquaredDistance(const Vector3& vec) const {
		return (*this - vec).SquaredDistance();
	}

	//************************************************************************
	// 日期：2016/12/28 
	// 参数: ScalarType & rotation，
	// 参数: ScalarType & theta:方位角(azimuth angle),范围为[0,2PI]
	// 参数: ScalarType & phi:仰角(elevation angle),范围为[-PI/2,PI/2]
	// 返回: void
	// 功能: 将Cartesian 坐标转换为polar坐标
	// 备注： 没有转换为经典的极坐标，而是转换为标准的球坐标系
	//************************************************************************
	inline void ToPolarRad(ScalarType& rotation, ScalarType& theta, ScalarType& phi)const {
		rotation = Norm();
		theta = static_cast<ScalarType>(atan2(_v[2], _v[0]));
		phi = static_cast<ScalarType>(asin(_v[1] / rotation));
	}


	
	//************************************************************************
	// 功能: 将极坐标转换为Cartesian坐标
	// 参数: const ScalarType & rotation
	// 参数: const ScalarType & theta
	// 参数: const ScalarType & phi
	// 返回: void
	// 备注: 没有使用经典极坐标系，而是使用了球面坐标系
	// 日期：2016/12/28 
	//************************************************************************
	inline void FromPolarRad(const ScalarType& rotation, const ScalarType& theta, const ScalarType& phi) {
		_v[0] = rotation*cos(theta)*cos(phi);
		_v[1] = rotation*sin(phi);
		_v[2] = rotation*sin(theta)*cos(phi);
	}
	

public:
	enum {
		Dimension = 3
	};
protected:
	ScalarType _v[3];

};

#endif // __Vector3_H__


//************************************************************************
// 功能: 计算两个向量之间的夹角
// 参数: const Vector3<ScalarType> & vec1
// 参数: const Vector3<ScalarType> & vec2
// 返回: ScalarType
// 日期：2016/12/28 
//************************************************************************
template<typename ScalarType>
inline ScalarType Angle(const Vector3<ScalarType>& vec1, const Vector3<ScalarType>& vec2) {
	ScalarType w = vec1.Norm() * vec2.Norm();
	if (w == 0) {
		return -1;
	}
	ScalarType ScalarType = (vec1 * vec2) / w;
	if (ScalarType > 1) {
		ScalarType = 1;
	}else if (ScalarType < -1) {
		ScalarType = -1;
	}
	return static_cast<ScalarType>(acos(ScalarType));
}

//************************************************************************
// 功能: 计算两个单位向量之间的夹角
// 参数: const Vector3<ScalarType> & vec1
// 参数: const Vector3<ScalarType> & vec2
// 返回: ScalarType
// 日期：2016/12/28 
//************************************************************************
template<typename ScalarType>
inline ScalarType AngleN(const Vector3<ScalarType>& vec1, const Vector3<ScalarType>& vec2) {
	ScalarType w = vec1 * vec2;
	if (w > 1) {
		w = 1;
	}else if (w < -1) {
		w = -1;
	}
	return static_cast<ScalarType>(acos(w));

}

template<typename T>
inline Vector3<T> operator-(const Vector3<T>& vec) {
	return Vector3<T>(-vec.X(), -vec.Y(), -vec.Z());
}

template<typename T>
inline Vector3<T> operator*(const T s, const Vector3<T>& vec) {
	return Vector3<T>(vec[0] * s, vec[1] * s, vec[2] * s);
}

//************************************************************************
// 功能: 计算Vector的长度值
// 参数: const Vector3<ScalarType> & vec
// 返回: ScalarType
// 日期：2016/12/28 
//************************************************************************
template<typename ScalarType>
inline ScalarType Norm(const Vector3<ScalarType>& vec) {
	return vec.Norm();
}



//************************************************************************
// 功能: 计算Vector的长度平方值
// 参数: const Vector3<ScalarType> & vec
// 返回: ScalarType
// 日期：2016/12/28 
//************************************************************************
template<typename ScalarType>
inline ScalarType SquaredNorm(const Vector3<ScalarType>& vec) {
	return vec.SquaredNorm();
}

//************************************************************************
// 功能: 对Vector进行单位化
// 参数: Vector3<ScalarType> & vec
// 返回: &
// 日期：2016/12/28 
//************************************************************************
template<typename ScalarType>
inline Vector3<ScalarType>& Normalize(Vector3<ScalarType>& vec) {
	vec.Normalize();
	return vec;
}

//************************************************************************
// 功能: 计算两个Vector之间的距离
// 参数: const Vector3<ScalarType> & vec1
// 参数: const Vector3<ScalarType> & vec2
// 返回: ScalarType
// 日期：2016/12/28 
//************************************************************************
template<typename ScalarType>
inline ScalarType Distance(const Vector3<ScalarType>& vec1, const Vector3<ScalarType>& vec2) {
	return (vec1 - vec2).Norm();
}

//************************************************************************
// 功能: 计算两个Vector之间的距离平方值
// 参数: const Vector3<ScalarType> & vec1
// 参数: const Vector3<ScalarType> & vec2
// 返回: ScalarType
// 日期：2016/12/28 
//************************************************************************
template<typename ScalarType>
inline ScalarType SquaredDistance(const Vector3<ScalarType>& vec1, const Vector3<ScalarType>& vec2) {
	return (vec1 - vec2).SquaredNorm();
}

//************************************************************************
// 功能: 计算两个向量之间的点乘值，使用了稳定点乘的方法，可以减少double类型误差
// 参数: const Vector3<ScalarType> & vec1
// 参数: const Vector3<ScalarType> & vec2
// 返回: 
// 日期：2016/12/28 
//************************************************************************
template<typename ScalarType>
inline Stable_dot(const Vector3<ScalarType>& vec1, const Vector3<ScalarType>& vec2) {
	ScalarType k0 = vec1._v[0] * vec2._v[0];
	ScalarType k1 = vec1._v[1] * vec2._v[1];
	ScalarType k2 = vec1._v[2] * vec2._v[2];

	int exp0, exp1, exp2;
	frexp(static_cast<double>(k0), exp0);
	frexp(static_cast<double>(k1), exp1);
	frexp(static_cast<double>(k2), exp2);

	if (exp0 < exp1) {
		if (exp0 < exp2) {
			return (k1 + k2) + k0;
		}else{
			return (k0 + k1) + k2;
		}
	}else {
		if (exp1 < exp2)
			return(k0 + k2) + k1;
		else
			return (k0 + k1) + k2;
	}
}

//************************************************************************
// 功能: 计算点p到边(v1,v2)上的投影位置q,并返回点p到其投影点的距离，即点到边的距离
// 参数: const Vector3<ScalarType> & p
// 参数: const Vector3<ScalarType> & v1
// 参数: const Vector3<ScalarType> & v2
// 参数: Vector3<ScalarType> & q,投影点的坐标
// 返回: 点到边的距离
// 日期：2016/12/28 
//************************************************************************

template<typename ScalarType >
ScalarType PointEdgeDist(const Vector3<ScalarType>& p, const Vector3<ScalarType>& v1, const Vector3<ScalarType>& v2, Vector3<ScalarType>& q) {
	Vector3<ScalarType> e(v2 - v1);
	ScalarType t = ((p - v1)*e) / e.SquaredNorm();
	if(t < 0){
		t = 0;
	}
	else if (t > 1) {
		t = 1;
	}
	q = v1 + e * t;
	return Distance(p, q);
}

//************************************************************************
// 功能: 计算点p到边edge的投影点坐标q,并返回点到边的长度
// 参数: const Vector3<ScalarType> & point
// 参数: const Vector3<ScalarType> & edge
// 参数: Vector3<ScalarType> & q,投影点的坐标
// 返回: 点到边的长度
// 日期：2016/12/28 
//************************************************************************
template<typename ScalarType>
ScalarType PointEdgeDist(const Vector3<ScalarType>& point, const Vector3<ScalarType>& edge, Vector3<ScalarType>& q) {
	ScalarType ScalarType = ((p - v1)*edge) / edge.SquaredNorm();
	if (ScalarType < 0) {
		ScalarType = 0;
	}
	else if (ScalarType > 1) {
		ScalarType = 1;
	}
	q = v1 + edge * ScalarType;
	return Distance(p, q);
}



//************************************************************************
// 功能: 计算向量的绝对值坐标，即对其坐标值分别求绝对值
// 参数: const Vector3<ScalarType> & vec
// 返回: 
// 日期：2016/12/28 
//************************************************************************
template<typename ScalarType>
inline Vector3<ScalarType> Abs(const Vector3<ScalarType>& vec) {
	return Vector3<ScalarType>(math::abs(vec[0]), math::abs(vec[1]), math::abs(vec[2]));
}


typedef Vector3<short>  Vector3s;
typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

typedef Vector3<short>  Point3s;
typedef Vector3<int> Point3i;
typedef Vector3<float> Point3f;
typedef Vector3<double> Point3d;