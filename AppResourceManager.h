#pragma once
namespace Resource
{
	class AppResourceManager
	{
	public: 
		static shared_ptr<AppResourceManager> Get() {
			static shared_ptr<AppResourceManager> instance(new AppResourceManager()); 
			return instance; 
		}
		void WindowInitialize(); 

		const HWND getHwnd() { return m_hwnd; }
		const int getWidth() { return m_width; }
		const int getHeight() { return m_height; }

	private: 
		AppResourceManager(); 

		HWND m_hwnd; 
		HINSTANCE m_hInstance; 
		HICON m_hIcon = nullptr;
		HCURSOR m_hCursor = nullptr;
		HICON m_hIconSmall = nullptr;

		// ��ũ�� ũ��. -> �� ���� ���� ������ �Ѿ��� ����! 
		UINT m_width; 
		UINT m_height; 

		wstring m_className; 
		wstring m_windowName; 		
		wstring m_modulePath;
		wstring m_workingPath;

		// default settings
		UINT m_classStyle;
		DWORD m_windowStyle;
		int m_x;
		int m_y;

	};
}


