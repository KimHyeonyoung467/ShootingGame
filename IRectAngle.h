#pragma once
#include "pch.h" 
#include "Transform.h" 

class IRectAngle
{
public: 
	virtual D2D1_RECT_F createRectAngle(const Vector2& pos, const Vector2& scale) = 0;

	// ���ڸ� �׸��� �Լ� 
	virtual void drawRectAngle(const D2D1_RECT_F& rect) = 0;

	// ���� �� �� ���ڸ� �׸��� �Լ� 
	virtual void drawFillRectAngle(const D2D1_RECT_F& rect) = 0; 
	virtual void drawFillRectAngle(const D2D1_RECT_F& rect, const D2D1::Matrix3x2F& matrix) = 0;
	virtual void drawsRectAngle(const D2D1_RECT_F& rect, ID2D1SolidColorBrush* brush, float strokWidth = 2.0f, ID2D1StrokeStyle* strokeStyle = nullptr) = 0; 

	// ���ڸ� ���� �ϴ� �Լ� 
	virtual void removeRectAngle(const D2D1_RECT_F& rect, ID2D1SolidColorBrush* brush) = 0;

	// ������ ��ġ�� ���� �ϴ� �Լ� 
	virtual void rectAngleTransform(const Vector2& pos, const Vector2& scale) = 0; 
	

};


