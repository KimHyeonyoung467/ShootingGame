#include "pch.h"
#include "Scene.h"
#include <cmath>

namespace Scenes
{

	Scene::Scene()
		: m_type(MENU), isRespawning(false), m_enemyCreator(nullptr),
		m_text(new TextDraw()), scoreCount(0)
	{
		m_text->Initialize();
		m_text->setText(L" Score : ");

	}

	// function �� ����ؼ� �ܺο��� ����� �Լ��� ����� �� �ְ� �ϴ� �Լ� ��
	void Scene::SetEnemyCreator(std::function<GameObject* ()> creator)
	{
		m_enemyCreator = creator;
	}

	void Scene::EnemyRespawn()
	{

		auto player = getGameObject(ObjectType::PLAYER);
		if (!player || player->IsDead() || player->getState()->getHealthPoint() == 0)
		{
			isRespawning = false;
			return;
		}

		if (!m_enemyCreator) return;

		bool enemyExists = false;
		// ���� ���� ���� �ִ��� Ȯ��
		for (const auto& obj : m_objects)
		{
			if (obj->getObjectType() == ObjectType::ENEMY && !obj->IsOutSide())
			{
				enemyExists = true;
				break;
			}

			if (obj->IsDead() && obj->IsOutSide())
			{
				isRespawning = false;
				break;
			}
		}
		if (!enemyExists && !isRespawning)
		{
			isRespawning = true;
			m_RespawnTimer.Reset();
		}

		if (isRespawning && m_RespawnTimer.isElapssed(ENEMY_RESPAWN_DELAY))
		{
			GameObject* newEnemy = m_enemyCreator();			// ���丮 �Լ��� �� ����
			newEnemy->Initialize();									// ������ �� �ʱ�ȭ
			addpendingObject(newEnemy);							// ���� �߰�
			isRespawning = false;									// ������ ���� �ʱ�ȭ
		}
	}


	void Scene::Initialize()
	{

	}

	void Scene::update()
	{
		m_text->getTextTransform()->setlocalPosition(-100.0f, 50.0f);
		m_text->update();

		EnemyRespawn();

		// ���� ���� ��ü���� ������Ʈ�մϴ�. �� ���� ���ȿ��� m_objects�� �ƹ��͵� �߰����� �ʽ��ϴ�.
		for (auto& obj : m_objects)
		{
			obj->update();
		}

		// ȭ�� ������ ���� BULLET ������ ����
		removeBulletCount();

		// ������Ʈ ��ȸ�� ���� ��, ���� ���� ��ü���� m_objects�� �ű�ϴ�.
		if (!m_pendingObjects.empty())
		{
			std::move(m_pendingObjects.begin(), m_pendingObjects.end(), std::back_inserter(m_objects));
			m_pendingObjects.clear();
		}
		
		removeContainer();
			
	}

	void Scene::Render()
	{
		// vector �� ������ GameObject ����� ������ ������ ��� ������Ʈ�� ���� ȣ��. 
		for (vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
		{
			(*it)->Render();

		}
		m_text->setTextColor(D2D1::ColorF::White);

		auto size = m_objects.size();

		m_text->drawText(scoreCount);
	}

	void Scene::addGameObject(GameObject* obj)
	{
		cout << endl;
		cout << endl;
		cout << endl;
		std::cout << "[Scene::addGameObject] push type=" << obj->enum_to_string(obj->getObjectType())
			<< " this=" << this << std::endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		m_objects.push_back(std::move(obj));
		std::cout << " size=" << m_objects.size() << std::endl;
	}


	void Scene::addpendingObject(GameObject* obj)
	{
		m_pendingObjects.push_back(std::move(obj));
	}

	void Scene::removeGameObject(ObjectType type)
	{
		for (auto it = m_objects.begin(); it != m_objects.end();)
		{
			if ((*it)->getObjectType() == type || (*it)->IsOutSide())
			{
				(*it)->IsShoot(false);

				// �÷��̾ ������ �� 
				if ((*it)->getObjectType() == ObjectType::PLAYER)
				{
					delete* it;
					m_objects.erase(it);
					setType(SceneType::END);
				}

				delete* it;
				m_objects.erase(it);
			}
			else ++it;
		}
	}

	void Scene::removeBulletCount()
	{
		int removedPlayerBulletCount = 0;
		int removedEnemyBulletCount = 0;

		// 2. ȭ�� ������ ���� �Ѿ�(BULLET)�� ã�Ƽ� �����ϰ�, �����ں��� ������ ���ϴ�.
		for (auto it = m_objects.begin(); it != m_objects.end();)
		{
			// ��ü�� 'BULLET' Ÿ���̰� ȭ�� �ۿ� �������� Ȯ���մϴ�.
			if ((*it)->getObjectType() == ObjectType::BULLET && (*it)->IsOutSide()) {

				// �Ѿ��� �����ڸ� Ȯ���ϰ� �ش� ī��Ʈ�� ������ŵ�ϴ�.
				if ((*it)->getOwnerType() == ObjectType::PLAYER) {
					++removedPlayerBulletCount;
				}
				else if ((*it)->getOwnerType() == ObjectType::ENEMY) {
					++removedEnemyBulletCount;
				}

				delete* it;
				it = m_objects.erase(it);
			}
			else {
				++it;
			}
		}


		//  ������ �Ѿ��� �ִٸ�, ��  �Ѿ� ���� ������Ʈ
		if (removedPlayerBulletCount > 0 || removedEnemyBulletCount > 0)
		{
			for (auto& obj : m_objects)
			{
				// �÷��̾ ã�� �÷��̾� �Ѿ� ���� ����
				if (obj->getObjectType() == PLAYER && removedPlayerBulletCount > 0)
				{
					auto curentCount = obj->getState()->getShootPoint();

					if (obj->getState()->getShootPoint() != 5)
					{
						obj->getState()->setShootPoint(curentCount + removedPlayerBulletCount);
					}
					// shootPoint �� 5���� �� ��, 
					else if (obj->getState()->getShootPoint() <= 5)
					{
						obj->IsShoot(false);
					}
					else if (obj->getState()->getShootPoint() == 0 && m_RespawnTimer.isElapssed(0.5f)) // �� �� �ִ� �߻� ī��Ʈ�� 0�̰�, 0.5f �� �� �ð��� ������ ��. 
					{
						auto shootPoint = obj->getState()->getShootPoint();
						++shootPoint;
						obj->getState()->setShootPoint(shootPoint);
					}
				}
				// ���� ã�� �� �Ѿ� ���� ����
				else if (obj->getObjectType() == ENEMY && removedEnemyBulletCount > 0)
				{
					auto curentCount = obj->getState()->getShootPoint();

					if (obj->getState()->getShootPoint() != 0)
					{
						obj->getState()->setShootPoint(curentCount + removedEnemyBulletCount);
					}
					else if (obj->getState()->getShootPoint() == 0 && m_RespawnTimer.isElapssed(0.5f)) // �� �� �ִ� �߻� ī��Ʈ�� 0�̰�, 0.5f �� �� �ð��� ������ ��. 
					{
						obj->IsShoot(false);

						auto shootPoint = obj->getState()->getShootPoint();
						++shootPoint;
						obj->getState()->setShootPoint(shootPoint);
						obj->IsShoot(true);
					}
				}

			}
		}
	}

	void Scene::removeContainer()
	{
		// ���� object �� ���� �����̳ʿ��� ���� 
		for (std::vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); /* no ++it here */)
		{
			if ((*it)->IsOutSide() && (*it)->getState()->getHealthPoint() != 0)
			{
				(*it)->IsShoot(false);
				delete* it;
				it = m_objects.erase(it);
			}
			else if ((*it)->IsDead() && ((*it)->getState()->getHealthPoint() == 0))
			{
				if ((*it)->getObjectType() == ObjectType::ENEMY)
				{
					++scoreCount;
				}

				delete* it;
				it = m_objects.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	GameObject* Scene::getGameObject(ObjectType type)
	{
		GameObject* findObject;
		for (vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
		{
			if ((*it)->getObjectType() == type)
			{
				return findObject = (*it);
			}
		}
		return nullptr;
	}

	GameObject* Scene::getGameObject(ObjectType type, ObjectType ownerType)
	{
		GameObject* findObject;
		for (vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
		{
			if ((*it)->getObjectType() == type && (*it)->getOwnerType() == ownerType)
			{
				return findObject = (*it);
			}
		}
		return nullptr;
	}

	vector<GameObject*> Scene::getGameObjects()
	{
		return m_objects;
	}

}

