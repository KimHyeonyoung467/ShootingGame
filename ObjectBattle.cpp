#include "pch.h"
#include "ObjectBattle.h"

ObjectBattle::ObjectBattle()
{

}

void ObjectBattle::TakeDamage(GameObject* Attacker, GameObject* defancer)
{
	// HealthPoint 
	auto defancerHealth(defancer->getState()->getHealthPoint());
		
	// AttackPoint 
	auto AttackerAttack(Attacker->getState()->getAttackPoint());

	// Attacker �� defancer �� �����ϴ� ���� 
	int damage = AttackerAttack - defancerHealth;
	defancer->getState()->setHealthPoint(damage);

	cout << "[DEBUG] Battle : " << endl <<
		"[DEBUG] defancer Object Type : " << defancer->enum_to_string(defancer->getObjectType()) << endl
		<< "[DEBUG] defancer HelthPoint : " << defancer->getState()->getHealthPoint() << endl;

}

void ObjectBattle::TakeDefance(GameObject* Attacker, GameObject* defancer)
{
	// DefancePoint
	auto defancerDefance(defancer->getState()->getDefancePoint());

	// AttackPoint 
	auto attackerAttack(Attacker->getState()->getAttackPoint());

	// defancer �� DefancePoint ���� 
	int damage = defancerDefance - attackerAttack;
	defancer->getState()->setDefancePoint(damage);
}

void ObjectBattle::Battle(GameObject* Attacker, GameObject* defancer)
{
	if (Attacker->IsCollision())
		TakeDamage(Attacker, defancer);
}

void ObjectBattle::GameOver(GameObject* obj)
{
	if (obj->getState()->getHealthPoint() != 0) return;

	// obj �� Player ����, Enemy ���� 2�� üũ �ʿ��ϴٸ� �߰� 

}