#include "pch.h"
#include "Application.h"

void ConsolePrint()
{
	AllocConsole();

	// C ��Ÿ�� stdout/stderr �����̷�Ʈ
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);

	// C++ ��Ʈ���� ����ȭ
	std::ios::sync_with_stdio(true);

	// �׽�Ʈ
	std::cout << "�ְܼ� Direct2D �����츦 ���ÿ� ����մϴ�.\0\n";
}

Application::Application() : m_appResource(Resource::AppResourceManager::Get()),
m_d2DResource(Resource::D2DResourceManager::Get())
{
}

Application::~Application()
{
	std::cout.unsetf(std::ios::boolalpha);
}

void Application::Initialize()
{
	// bool Ÿ�� ������ true / false �� �ܼ�â�� ���� 
	std::cout.setf(std::ios::boolalpha);

	m_appResource->WindowInitialize();
	m_d2DResource->initialize();
	ConsolePrint();

	Time::InitTime();


}

void Application::Run()
{
	MSG msg = {};
	bool isquit = true;

	while (isquit == true)
	{
		while (msg.message != WM_QUIT && PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// ���� ȣ��  
		update();
		Render();
	}
}

void Application::update()
{
	Time::updateTime();

}

void Application::Render()
{
	beginDraw(D2D1::ColorF::Black);

}
void Application::beginDraw(const D2D1::ColorF& color)
{
	m_d2DResource->getContext()->BeginDraw();
	m_d2DResource->getContext()->Clear(color);
}

void Application::endDraw()
{
	m_d2DResource->getContext()->EndDraw();
	m_d2DResource->getSwapChain()->Present(1, 0);
}
