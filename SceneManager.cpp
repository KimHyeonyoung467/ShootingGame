#include "pch.h"
#include "SceneManager.h"

namespace Scenes
{


	SceneManager::SceneManager()
		: m_sceneName("empty"), m_curentScene()
	{
	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::CreateScene(const string& name, unique_ptr<Scenes::Scene> scene)
	{
		addScene(name, std::move(scene));
	}

	void SceneManager::ChangeScene(const string& name)
	{
		Scenes::Scene* nextScene = getScene(name);

		// type �� ���� �̸� ���� 
		if (nextScene)
		{
			m_curentScene = nextScene;
			m_sceneName = name;
		}
	}

	void SceneManager::update()
	{
		// �׻� üũ�ؼ� ���� ��ȯ 
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "[DEBUG] curent Scene  : " << m_sceneName << endl;
		vaildate(m_curentScene);

		m_curentScene->update(); // m_curScene �� ���� �ƴ� �� �׻� ȣ���ϰ� �ϱ�. 

		if (m_curentScene->getScore() == 10)
			ChangeScene("End"); 

	}
	void SceneManager::addScene(const string& name, unique_ptr<Scenes::Scene> scene)
	{
		m_Scenemap[name] = std::move(scene);
	}

	Scenes::Scene* SceneManager::getScene(const string& name)
	{
		auto findScene = m_Scenemap.find(name);

		// ã�Ƴ� Scene �� �����ϴ� ��� 
		if (findScene != m_Scenemap.end())
		{
			cout << "[Debug] " << name << " ���� ã�Ƴ½��ϴ�!" << endl;
			auto& scene = findScene->second;

			return scene.get();
		}
		return nullptr;
	}

	void SceneManager::Render()
	{
		if (!m_curentScene) return;

		vaildate(m_curentScene);

		m_curentScene->Render();

	}
}