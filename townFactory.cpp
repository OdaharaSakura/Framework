#include "main.h"
#include "townFactory.h"
#include "scene.h"
#include "manager.h"
#include "staticObject.h"

void TownFactory::CreateTown()
{
	Scene* scene = Manager::GetScene();

	StaticObject* desk = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	desk->SetModel_Key("Desk");
	desk->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 10.0f));
	desk->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	desk->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* house1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house1->SetModel_Key("House1");
	house1->SetPosition(D3DXVECTOR3(40.0f, 0.0f, 80.0f));
	house1->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	house1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* house2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house2->SetModel_Key("House2");
	house2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 80.0f));
	house2->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	house2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* shop1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop1->SetModel_Key("Shop1");
	shop1->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 150.0f));
	shop1->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	shop1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	/*StaticObject* shop2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop2->SetModel_Key("Shop2");
	shop2->SetPosition(D3DXVECTOR3(80.0f, 0.0f, 40.0f));
	shop2->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	shop2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* shop3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop3->SetModel_Key("Shop3");
	shop3->SetPosition(D3DXVECTOR3(70.0f, 0.0f, 100.0f));
	shop3->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	shop3->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* fence = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence->SetModel_Key("Fence");
	fence->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 20.0f));
	fence->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	fence->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* fencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fencewood->SetModel_Key("FenceWood");
	fencewood->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 30.0f));
	fencewood->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	fencewood->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* treemiddle = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	treemiddle->SetModel_Key("MiddleTree");
	treemiddle->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 170.0f));
	treemiddle->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	treemiddle->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* symboltree = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	symboltree->SetModel_Key("SymbolTree");
	symboltree->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 170.0f));
	symboltree->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	symboltree->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	/*StaticObject* windmill = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	windmill->SetModel_Key("WindMill");
	windmill->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 30.0f));
	windmill->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	windmill->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* gate1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	gate1->SetModel_Key("Gate");
	gate1->SetPosition(D3DXVECTOR3(150.0f, 0.0f, 150.0f));
	gate1->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	gate1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* gate2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	gate2->SetModel_Key("Gate2");
	gate2->SetPosition(D3DXVECTOR3(120.0f, 0.0f, 120.0f));
	gate2->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	gate2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* bridge = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	bridge->SetModel_Key("Bridge");
	bridge->SetPosition(D3DXVECTOR3(110.0f, 0.0f, 70.0f));
	bridge->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	bridge->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* pool = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	pool->SetModel_Key("Pool");
	pool->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -10.0f));
	pool->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	pool->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	/*StaticObject* wateringcan = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	wateringcan->SetModel_Key("WateringCan");
	wateringcan->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	wateringcan->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	wateringcan->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* wateringcan2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	wateringcan2->SetModel_Key("WateringCan2");
	wateringcan2->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 10.0f));
	wateringcan2->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	wateringcan2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* carriage = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	carriage->SetModel_Key("Carriage");
	carriage->SetPosition(D3DXVECTOR3(70.0f, 0.0f, 80.0f));
	carriage->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	carriage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* carriage = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	carriage->SetModel_Key("Barrel");
	carriage->SetPosition(D3DXVECTOR3(45.0f, 0.0f, 80.0f));
	carriage->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	carriage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));*/
}
