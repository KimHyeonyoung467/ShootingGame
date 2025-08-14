#pragma once
#include "IRectAngle.h"
#include "D2DResourceManager.h"

class RectAngle : public IRectAngle 
{
public: 
	RectAngle(); 

	D2D1_RECT_F getRectAngle(); 
	// �����ϴ� �Լ� 
	D2D1_RECT_F createRectAngle(const Vector2& pos, const Vector2& scale) override;
	
	// ���� ����ִ� ���� �׸��� 
	void drawRectAngle(const D2D1_RECT_F& rect) override; 
	void drawRectAngle(const D2D1_RECT_F& rect, ID2D1SolidColorBrush* brush, float strokWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr);
	void drawsRectAngle(const D2D1_RECT_F& rect, ID2D1SolidColorBrush* brush, float strokWidth = 2.0f, ID2D1StrokeStyle* strokeStyle = nullptr) override;
	
	// ���� ���� ���� ä��� �׸��� 
	void drawFillRectAngle(const D2D1_RECT_F& rect) override;
	void drawFillRectAngle(const D2D1_RECT_F& rect, const D2D1::Matrix3x2F& matrix) override;

	void removeRectAngle(const D2D1_RECT_F& rect, ID2D1SolidColorBrush* brush) override;

	// ������ ��ġ�� ���� �ϴ� �Լ� 
	void rectAngleTransform(const Vector2& pos, const Vector2& scale) override; 

private: 
	D2D1_RECT_F m_rect; 
	shared_ptr<Resource::D2DResourceManager> m_d2DResource; 	

};

