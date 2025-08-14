#pragma once
#include "pch.h" 
#include "Scene.h" 
#include "GameObject.h"
class ObjectBattle
{
public:
	ObjectBattle();
	// ����� Status �� �޾Ƽ� �ڽ��� HealthPoint Status �� ����  
	void TakeDamage(GameObject* Attacker, GameObject* defancer);

	// ����� Attack Status �� �޾Ƽ� �ڽ��� DefancePoint Status �� ���� 
	void TakeDefance(GameObject* Attacker, GameObject* defancer);

	// DefancePoint�� 0�� �Ǹ� TakeDamage �� ���ؼ� HealthPoint �� ����
	void Battle(GameObject* Attacker, GameObject* defancer);

	// Player �� healthPoint �� 0�� �Ǿ��� �� ȣ���ؼ� Scene �� m_objects �ȿ� �ִ� GameObject �� ���� �� End Scene ���� ��ȯ. 
	// Enemy �� healthPoint �� 0�� �Ǿ��� ������ Scene �� m_objects �ȿ� �ִ� Enemy GameObject �� ���� ��, Enemy �� �ٽ� ������ �� �ֵ��� �ϱ�. 
	void GameOver(GameObject* obj);

private:
	shared_ptr<Scenes::Scene> m_scene;
};

