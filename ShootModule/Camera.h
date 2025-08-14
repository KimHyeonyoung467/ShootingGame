#pragma once
#include "pch.h" 
#include "Transform.h" 

class Camera
{
public: 
	static unique_ptr<Camera> createMainCamera(UINT width, UINT height)
	{
		vaildata(width, height);
		static unique_ptr<Camera> instance(new Camera(width, height)); 
		return std::move(instance);
	}
	
	float getSize() { return m_size; }
	void setSize(float value) { m_size = value; }

	void createViewCamera(UINT width, UINT height);

	D2D1::Matrix3x2F& getviewMatrix(); 

	const shared_ptr<Transform> getTransform() const { return m_transform; }
private: 
	Camera(UINT width, UINT height); 
	shared_ptr<Transform> m_transform; 
	
	mutable D2D1::Matrix3x2F m_viewMatrix; 

	float m_size; // ÁÜÀÎ, ÁÜ ¾Æ¿ô 

	UINT m_viewWidth;
	UINT m_viewHeight; 

	static void vaildata(UINT w, UINT h)
	{
		if (w <= 0 || h <= 0)
			throw invalid_argument("viewport ³ÐÀÌ 0 ÀÌÇÏ."); 
	}
};

