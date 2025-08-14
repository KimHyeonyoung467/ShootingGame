#pragma once
#include "pch.h" 
#include "GameObject.h" 
#include "Timer.h" 
#include <functional>
#include "DrawText.h" 

enum SceneType
{
	MENU,
	PLAY,
	END,
	SCENE_COUNT // �� ���� 
};

namespace Scenes
{
	class Scene
	{
	public:
		Scene();
		virtual void Initialize();
		virtual void update();
		virtual void Render();

		// GameObject �߰� 
		void addGameObject(GameObject* obj);
		void addpendingObject(GameObject* obj);

		void removeGameObject(ObjectType type);
		void removeBulletCount();
		void removeContainer(); 
		
		GameObject* getGameObject(ObjectType type);
		GameObject* getGameObject(ObjectType type, ObjectType ownerType);
		vector<GameObject*> getGameObjects(); 

		// setType ������ type �� �����Ͽ� �� ��ȯ ����. 
		void setType(SceneType type) { m_type = type; }
		const SceneType getType() const { return m_type; }
		
		void SetEnemyCreator(std::function<GameObject* ()> creator);
		
		void EnemyRespawn(); 

		const bool const IsRespawning() { return isRespawning; }

		const int getScore() const { return scoreCount; }
	private:
		SceneType m_type;

		// string Ÿ���� �̸��� ���ؼ� ��ġ�� Scene �� ������ �� �ְ� �Ѵ�. 
		vector<GameObject*> m_objects;
		// �߰��� ��ü���� �����ϴ� �ӽ� ���
		std::vector<GameObject*> m_pendingObjects; 

		// test code 
		Time::Timer<> m_RespawnTimer;

		bool isRespawning; 
		const float ENEMY_RESPAWN_DELAY = 3.0f;
		int scoreCount = 0; 

		TextDraw* m_text; 

		// function  
		std::function<GameObject* ()> m_enemyCreator; 

	};

}


