#pragma once
#include "pch.h" 
#include "D2DResourceManager.h"
#include "RectAngle.h" 

class IRectAngle;

class RendererManager
{
public: 
	RendererManager(Transform* tr);
	~RendererManager() = default; 

	void Initialize(); 
	void update(); 
	void Render(); 

	// Direct2D �ʱ�ȭ 
	// GameObject ���� RenderManager �� �׸��� 
	IRectAngle* getRectAngle() {  return m_rect; } // IRectAngle �ڽ��� RectAngle Ÿ�� 
	const D2D1_RECT_F& getRect() const { return rect; }

	void setColor(const D2D1::ColorF& color) { m_color = color;  }
	const D2D1::ColorF getColor() { return m_color; }
private: 
	// �簢�� �׸��� �Լ� ������ Ŭ���� 
	IRectAngle* m_rect;	
	D2D1_RECT_F rect; 
	D2D1::ColorF m_color; 

	Transform* m_transform;	
	shared_ptr<Resource::D2DResourceManager> m_d2DResource; 
};

