#ifndef __LINE2_H__
#define __LINE2_H__

#pragma once

#include "Vector2.h"

//����Ϊ��άֱ�ߵ�ģ���࣬һ��ֱ����������ά������ʾ��
//һ��ԭ�㣬��һ��Ϊֱ�ߵķ�����������һ��Ϊ��λ������
//@param LineScalarType:ģ�����������ָ����ʾ�����scalar type

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
	
	//����pͶӰ��ֱ����,���ر���t
	inline ScalarType Projection(const PointType& p)const {
		return static_cast<ScalarType>((p - ori_).Dot(dir_) / dir_.SquaredNorm());
	}

	//����ֱ���ϲ���t��Ӧ�ĵ�
	inline PointType P(const ScalarType t)const {
		return ori_ + dir_ * t;
	}

	inline LineType& Normalize() {
		dir_.Normalize();
		return *this;
	}
	
	//����ֱ���Ͼ����p����ĵ�
	inline PointType ClosestPoint(const PointType& p)const {
		return P(Projection(p));
	}

	//��תֱ�ߵķ���
	inline void Flip() {
		dir_ = -dir;
	}


protected:
	PointType ori_;	//ֱ��ԭ��
	PointType dir_;	//ֱ�߷�����������һ��Ϊ��λ����
};
#endif // __Line2_H__


//************************************************************************
// ����: �����point��ֱ��line�ϵ�ͶӰ��
// ����: const Line2<T> & line
// ����: const Vector2<T> & point
// ����: 
// ���ڣ�2016/12/28 
//************************************************************************
template<typename T>
Vector2<T> ClosestPoint(const Line2<T>& line, const Vector2<T>& point) {
	return line.P(line.Projection(point));
}


//************************************************************************
// ����: �����point��ֱ��line�ľ���
// ����: const Line2<T> & line
// ����: const Vector2<T> & point
// ����: boost::T
// ���ڣ�2016/12/28 
//************************************************************************
template<typename T>
T Distance(const Line2<T>& line, const Vector2<T>& point) {
	Vector2<T> neareast = line.ClosestPoint(point);
	return (neareast - point).Norm();
}


//************************************************************************
// ����: �����point����ֱ��line�ľ����
// ����: const Line2<T> & line
// ����: const Vector2<T> & point
// ����: 
// ���ڣ�2016/12/28 
//************************************************************************
template<typename T>
Vector2<T> Mirror(const Line2<T>& line, const Vector2<T>& point) {
	Vector2<T> nearest = ClosestPoint(line, point);
	Vector2<T> direction = nearest - point;
	nearest += direction;
	return nearest;
}


//�����άֱ�ߵ�ʵ����
typedef Line2<short> Line2s;
typedef Line2<int> Line2i;
typedef Line2<float> Line2f;
typedef Line2<double> Line2d;