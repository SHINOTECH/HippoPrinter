#ifndef __LINE2_H__
#define __LINE2_H__

#pragma once

#include "Vector2.h"

//该类为二维直线的模板类，一条直线由两个二维向量表示：
//一个原点，另一个为直线的方向向量（不一定为单位向量）
//@param LineScalarType:模板参数，用于指定表示坐标的scalar type

template<typename LineScalarType>
class Line2 {
public:
	//The scalar type
	typedef LineScalarType ScalarType;

	//The point type
	typedef Vector2<LineScalarType> PointType;

	//The scalar type
	typedef Line2<LineScalarType> LineType;

public:
	inline Line2() {}
	inline Line2(const PointType& origin, const PointType& direction)
		:ori_(origin),dir_(direction) {
	}
	inline Line2(const LineType& line)
		: ori_(line.Origin()), dir_(line.Direction()) {
	}

	template<typename Q>
	inline void Import(const Line2<Q>& b) {
		ori_.Import(b.ori_);
		dir_.Import(b.dir_);
	}

	template<typename Q>
	static inline LineType Construct(const Line2<Q>& b) {
		LineType line;
		line.Import(b);
		return line;
	}


	inline void SetOrigin(const PointType& origin) {ori_ = origin;}
	inline void SetDirection(const PointType& direction) {dir_ = direction;}
	inline const PointType& Origin() const { return ori_; }
	inline const PointType& Direction() const { return dir_; }
	inline PointType& Origin() { return ori_; }
	inline PointType& Direction(){return dir_;}

	inline LineType& operator=(const LineType& line) {
		Import(line);
	}
	inline LineType operator+(const LineType& line)const {
		return LineType(ori_ + line.Origin(), dir_ + line.Direction());
	}
	inline LineType operator-(const LineType& line)const {
		return LineType(ori_ - line.Origin(), dir_ - line.Direction());
	}
	inline LineType operator*(const ScalarType s)const {
		return LineType(ori_* s, dir_* s);
	}
	inline LineType operator /(const ScalarType s)const {
		return LineType(ori_ / s, dir_ / s);
	}

	inline bool operator == (const LineType& line)const {
		return ori_ == line.ori_ && dir_ == line.dir_;
	}

	inline bool operator !=(const LineType& line)const {
		return ori_ != line.ori_ || dir_ != line.dir_;
	}
	
	//将点p投影到直线上,返回比例t
	inline ScalarType Projection(const PointType& p)const {
		return static_cast<ScalarType>((p - ori_).Dot(dir_) / dir_.SquaredNorm());
	}

	//计算直线上参数t对应的点
	inline PointType P(const ScalarType t)const {
		return ori_ + dir_ * t;
	}

	inline LineType& Normalize() {
		dir_.Normalize();
		return *this;
	}
	
	//计算直线上距离点p最近的点
	inline PointType ClosestPoint(const PointType& p)const {
		return P(Projection(p));
	}

	//反转直线的方向
	inline void Flip() {
		dir_ = -dir;
	}


protected:
	PointType ori_;	//直线原点
	PointType dir_;	//直线方向向量，不一定为单位向量
};
#endif // __Line2_H__


//************************************************************************
// 功能: 计算点point在直线line上的投影点
// 参数: const Line2<T> & line
// 参数: const Vector2<T> & point
// 返回: 
// 日期：2016/12/28 
//************************************************************************
template<typename T>
Vector2<T> ClosestPoint(const Line2<T>& line, const Vector2<T>& point) {
	return line.P(line.Projection(point));
}


//************************************************************************
// 功能: 计算点point到直线line的距离
// 参数: const Line2<T> & line
// 参数: const Vector2<T> & point
// 返回: boost::T
// 日期：2016/12/28 
//************************************************************************
template<typename T>
T Distance(const Line2<T>& line, const Vector2<T>& point) {
	Vector2<T> neareast = line.ClosestPoint(point);
	return (neareast - point).Norm();
}


//************************************************************************
// 功能: 计算点point关于直线line的镜像点
// 参数: const Line2<T> & line
// 参数: const Vector2<T> & point
// 返回: 
// 日期：2016/12/28 
//************************************************************************
template<typename T>
Vector2<T> Mirror(const Line2<T>& line, const Vector2<T>& point) {
	Vector2<T> nearest = ClosestPoint(line, point);
	Vector2<T> direction = nearest - point;
	nearest += direction;
	return nearest;
}


//定义二维直线的实例类
typedef Line2<short> Line2s;
typedef Line2<int> Line2i;
typedef Line2<float> Line2f;
typedef Line2<double> Line2d;