#include "pch.h"
#include "Camera.h"

void Camera::createViewCamera(UINT width, UINT height)
{
	// ī�޶��� ũ�� 
	m_transform->setlocalPosition({ 0.0f, 0.0f });
	m_transform->setlocalscale(width, height);
	m_transform->setRotation(0.0f); 
	
	// ��� �ʱ� ��� (���ſ����ε� ���) 
	m_viewMatrix = m_transform->getMatrix();	
}

D2D1::Matrix3x2F& Camera::getviewMatrix()
{
	// ���ŵ��� ���� transform �� ����� �����´�. Initialize ���� �̹� ����� ����� �������� ������, �̰������� ����� ��ȯ���� �ʿ��ϴ�. 
	m_viewMatrix.Invert(); 

	return m_viewMatrix; 
}

Camera::Camera(UINT width, UINT height)
	: m_viewMatrix(D2D1::Matrix3x2F::Identity()), 
	m_viewWidth(width), m_viewHeight(height)
{

}
