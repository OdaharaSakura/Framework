#pragma once

class TownFactory
{
public:
	TownFactory() {};
	~TownFactory() {};

	void SetSphereCollider(class StaticObject* gameObject);
	void SetBoxCollider(class StaticObject* gameObject);

	void CreateTown();
};
