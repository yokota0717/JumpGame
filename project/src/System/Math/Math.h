/**
* @file Math.h
* @brief ���w�֘A�̍\���̂��`����
* @author yokota0717
* @date 2018.10.29
* @param history
- 2018.11.9 yokota0717
-# Vec��Offset��ǉ�
- 2018.11.12 yokota0717
-# Rect��Offset,OffsetCopy��ǉ�
- 2018.11.15 yokota0717
-# Vec��x,y�̃e���v���[�g��������߂�
*/


#pragma once
#include <cmath>


namespace Math {
	struct Vec;
	struct Box2D;
	struct Circle;
	struct Triangle;
	struct Orval;

	//�~����
	static constexpr float PI = 3.141592653589793238462643383279502884197f;
	//�p�x�ϊ�
	float ToDegree(float radian);
	float ToRadian(float degree);
	//�d��
	float Gravity(int onemeter);

	//�x�N�g���\����
	struct Vec {
		float x, y, z;		//���W

		Vec();
		Vec(float x, float y, float z = 0.0f);
		~Vec();

		//���s�ړ�
		void Offset(const Math::Vec& v);
		void Offset(const float x, const float y);
		Math::Vec OffsetCopy(const Math::Vec& v);
		Math::Vec OffsetCopy(const float x, const float y);

		//�x�N�g���̃[���N���A
		void Zero();
		//�x�N�g���𐳋K��
		Vec Normalize();
		//�x�N�g����x���@�ŉ�]����
		Vec RotateVecDegree(float deg);
		//�x�N�g�����ʓx�@�ŉ�]����
		Vec RotateVecRadian(float rad);
		//�x�N�g����x���@�ŉ�]����A��]���S�w��
		void RotateVecDegree(Vec center, float deg);
		//�x�N�g�����ʓx�@�ŉ�]����A��]���S�w��
		void RotateVecRadian(Vec center, float rad);
		//2�̃x�N�g���̓��ς�Ԃ�
		static float GetDotVec(Vec v1, Vec v2) {
			return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
		}
		//2�̃x�N�g���̊O�ς�Ԃ�(2����)
		static float GetCrossVec2(Vec v1, Vec v2) {
			return (v1.x*v2.y) - (v1.y*v2.x);
		}
		//2�̃x�N�g���̊O�ς�Ԃ�(3����)
		Vec GetCrossVec3(Vec v1, Vec v2);
		//�x�N�g���̒����𓾂�
		static float GetVecLen(Vec v) {
			return std::powf(v.x*v.x + v.y*v.y + v.z*v.z, 0.5f);
		}
		float GetVecLen() const;
		//���K�����ꂽ�x�N�g���𓾂�
		Vec GetUnitVec(Vec v);
		//�x�N�g����n�{����
		Vec VecScale(Vec v, float n);
		//2�����x�N�g���̒P�ʖ@���x�N�g���𓾂� v1�~v2 �x�N�g���̍����̕� (��:���w�̍��W�n)
		Vec GetUnitNormVec2Left(Vec v);
		//2�����x�N�g���̒P�ʖ@���x�N�g���𓾂� v1�~v2 �x�N�g���̉E���̕� (��:���w�̍��W�n)
		Vec GetUnitNormVec2Right(Vec v);
		//3�������ʂ̒P�ʖ@���x�N�g���𓾂�(��:���w�̍��W�n) v1,v2�͕��ʏ�ɑ��݂���x�N�g��
		Vec GetUnitNormVec3(Vec v1, Vec v2);

		//�����蔻��
		bool Hit(Vec& v) const;
		bool Hit(Box2D& b) const;
		bool Hit(Circle& c) const;
		bool HitBox(Box2D& b) const;

		//�I�y���[�^��`
		Vec& operator = (const Vec& v);
		const Vec operator + (const Vec& v) const;
		const Vec operator - (const Vec& v) const;
		const Vec operator * (const float n) const;
		const Vec operator / (const float n) const;
		Vec& operator += (const Vec& v);
		Vec& operator -= (const Vec& v);
		Vec& operator *= (const float n);
		Vec& operator /= (const float n);
		bool operator == (const Vec& v) const;
	};




	struct Box2D {				//�l�p�`�\����
		float	x, y, w, h;		//����̍��W�A���A����

		Box2D();
		Box2D(float x, float y, float w, float h);
		~Box2D();
		void Offset(Vec v);
		void Offset(float vx, float vy);
		Box2D OffsetCopy(float vx, float vy) const;
		Box2D OffsetCopy(const Vec& v)const;
		bool Hit(const Box2D& b) const;
		bool Hit(const Vec& b) const;
	};

	struct Circle {
		Vec center;		//���S���W
		float r;			//���a

		Circle();
		Circle(float x, float y, float z, float r);
		~Circle();

		void Offset(Vec v);
		void Offset(float vx, float vy, float vz = 0.0f);
		Circle OffsetCopy(float vx, float vy, float vz = 0.0f) const;
		Circle OffsetCopy(const Vec& v)const;
		bool Hit(const Circle& c) const;
		bool Hit(const Vec& v) const;
		bool Hit(const Box2D& b) const;
	};

	struct Triangle {
		Vec v1, v2, v3;		//3���_

		Triangle(Vec v1, Vec v2, Vec v3);
	};

	struct Orval {
		float x, y;		//���S���W
		float lr, sr;	//�����A�Z��	 long radius,shot radius
		float angle;	//������x������̌X��

		Orval(float x, float y, float lr, float sr, float ang);
	};


	struct Rect {
		Vec tl, tr, bl, br;			//4���_
		Rect();
		Rect(Vec tl, Vec tr, Vec bl, Vec br);
		Rect(const Vec& topleft, const Vec& bottomright);
		void Rotate(float rad);
		void Rotate(float rad, Vec center);
		void Offset(const float x, const float y);
		void Offset(const Vec& v);
	};
}