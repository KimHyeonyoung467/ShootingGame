#pragma once
#include "Scene.h"
#include <unordered_map>

namespace Scenes {

	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		// ���� �����Ͽ�  Scene ������ unordared_map �� ����ȴ�. 
		void CreateScene(const string& name, unique_ptr<Scenes::Scene> scene);

		// ���� Ÿ�Կ� ����, ���� ���� Ÿ�Կ� �´� ������ �����Ѵ�. 
		void ChangeScene(const string& name);

		// ���� ���� ���� update �� Render �� ȣ�� 
		void update();
		void Render();

		// ������ ������ �ν��Ͻ� �ּҸ� vector m_vScenes �� ���� 
		void addScene(const string& name, unique_ptr<Scenes::Scene> scene);
		Scenes::Scene* getScene(const string& name);

		// ���� �� ���¿� ���� �̸� ���� 
		void setName(const string& nm) { m_sceneName = nm; }
		const string& getName() const { return m_sceneName; }

		// ���� ���� �����ϰ� ���� 
		void setcurentScene(Scenes::Scene* curScene) { m_curentScene = curScene; }
		Scenes::Scene* getcurentScene() { return m_curentScene; }

	private:
		// key 
		string m_sceneName;


		// ������ ������ �ּҸ� ������ �����̳� 
		unordered_map<string, unique_ptr<Scenes::Scene>> m_Scenemap; // ������ ������ �����̳�

		// �� ���� �� �ν��Ͻ� �ּҿ� ���� �����ϰ� �ϱ� 
		Scenes::Scene* m_curentScene;


		static void vaildate(const Scenes::Scene* scene)
		{
			if (scene == nullptr)
				throw invalid_argument("ScenManager :: m_curentScene is Nullptr!");
		}

	};
}
