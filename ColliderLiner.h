#pragma once
#include "pch.h" 
#include "Transform.h" 
#include "D2DResourceManager.h"
#include "RendererManager.h"
#include "IRectAngle.h" 

class ColliderLiner
{
public:
	// �������̽� �Ǽ��� ���� ���� ���丮 �Լ� 
	static ColliderLiner* drawLiner(Transform* tr)
	{
		return new ColliderLiner(tr); 
	}

	// GameObject �� Rect �� �޾Ƽ� Rect �� ũ�� ��ŭ�� ColliderLiner ������ ���, 
	// RendererManager �� m_rect �� ����� �׸���. 

	void Initialize();
	void update();
	void Render();

	void setTransform(Transform* tr) { m_transform = tr; }
	const Transform* getTransform() const {	return m_transform; } 

	const RendererManager* getRender() const { return m_render; }

	const IRectAngle* getRectAngle() const { return m_rect; }

	void setColor(const D2D1::ColorF& color) { m_color = color; }
	const D2D1::ColorF& getColor() const { return m_color; }
private:
	ColliderLiner(Transform* obj);
	Transform* m_transform; 

	Vector2 m_position;
	Vector2 m_scale;

	RendererManager* m_render; // Collider �浹 ���� �׸� ���ڸ� ���� RendererManager 
									// RendererManager ���� ���� ���� ���� 
	D2D1::ColorF m_color; 

	IRectAngle* m_rect; 
	D2D1_RECT_F rect; 

	shared_ptr<Resource::D2DResourceManager> m_d2DResource;
};

