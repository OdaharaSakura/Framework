#include "main.h"
#include "townFactory.h"
#include "scene.h"
#include "manager.h"
#include "staticObject.h"
#include "road.h"
#include "house.h"
#include "cow.h"
#include "tree_billboard.h"
#include "tree.h"

void TownFactory::CreateTown()
{
	Scene* scene = Manager::GetScene();

	scene->AddGameObject<House>(LAYER_OBJECT_3D)->SetPosition(D3DXVECTOR3(12.0f, 3.0f, 6.0f));

	Road* road = scene->AddGameObject<Road>(LAYER_OBJECT_3D);
	road->SetPosition(D3DXVECTOR3(0.0f, 0.01f, 8.0f));
	road->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));

	Road* road1 = scene->AddGameObject<Road>(LAYER_OBJECT_3D);
	road1->SetPosition(D3DXVECTOR3(0.0f, 0.01f, 24.0f));
	road1->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));

	Road* road2 = scene->AddGameObject<Road>(LAYER_OBJECT_3D);
	road2->SetPosition(D3DXVECTOR3(10.0f, 0.01f, 36.0f));
	road2->SetScale(D3DXVECTOR3(4.0f, 1.0f, 13.0f));
	road2->SetRotation(D3DXVECTOR3(0.0f, 3.14f / 2, 0.0f));

	Road* road3 = scene->AddGameObject<Road>(LAYER_OBJECT_3D);
	road3->SetPosition(D3DXVECTOR3(20.0f, 0.01f, 48.0f));
	road3->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));
	road3->SetRotation(D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	Road* road4 = scene->AddGameObject<Road>(LAYER_OBJECT_3D);
	road4->SetPosition(D3DXVECTOR3(20.0f, 0.01f, 64.0f));
	road4->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));
	road4->SetRotation(D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	Road* road5 = scene->AddGameObject<Road>(LAYER_OBJECT_3D);
	road5->SetPosition(D3DXVECTOR3(20.0f, 0.01f, 80.0f));
	road5->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));
	road5->SetRotation(D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	Road* road6 = scene->AddGameObject<Road>(LAYER_OBJECT_3D);
	road6->SetPosition(D3DXVECTOR3(0.0f, 0.01f, -8.0f));
	road6->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));



	StaticObject* desk = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	desk->SetModel_Key("Desk");
	desk->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 8.0f));
	desk->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	desk->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* house2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house2->SetModel_Key("House2");
	house2->SetPosition(D3DXVECTOR3(8.0f, 0.0f, 80.0f));
	house2->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	house2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* house3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house3->SetModel_Key("House3");
	house3->SetPosition(D3DXVECTOR3(32.0f, 0.0f, 80.0f));
	house3->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	house3->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* flowerbed = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flowerbed->SetModel_Key("FlowerBed");
	flowerbed->SetPosition(D3DXVECTOR3(15.0f, 0.0f, 80.0f));
	flowerbed->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flowerbed->SetRotation(D3DXVECTOR3(0.0f, 3.14f/-2, 0.0f));

	StaticObject* flowerbed1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flowerbed1->SetModel_Key("FlowerBed");
	flowerbed1->SetPosition(D3DXVECTOR3(25.0f, 0.0f, 80.0f));
	flowerbed1->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flowerbed1->SetRotation(D3DXVECTOR3(0.0f, 3.14f/2, 0.0f));

	StaticObject* house4 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house4->SetModel_Key("House4");
	house4->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 140.0f));
	house4->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	house4->SetRotation(D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	StaticObject* house5 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house5->SetModel_Key("House5");
	house5->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 140.0f));
	house5->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	house5->SetRotation(D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	StaticObject* shop1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop1->SetModel_Key("Shop1");
	shop1->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 90.0f));
	shop1->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	shop1->SetRotation(D3DXVECTOR3(0.0f, -3.14/2.0f, 0.0f));

	StaticObject* shop2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop2->SetModel_Key("Shop2");
	shop2->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 113.0f));
	shop2->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	shop2->SetRotation(D3DXVECTOR3(0.0f, 3.14/2.0f, 0.0f));

	StaticObject* shop3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop3->SetModel_Key("Shop3");
	shop3->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 90.0f));
	shop3->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	shop3->SetRotation(D3DXVECTOR3(0.0f, 3.14/2.0f, 0.0f));

	StaticObject* shop4 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop4->SetModel_Key("Shop4");
	shop4->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 113.0f));
	shop4->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	shop4->SetRotation(D3DXVECTOR3(0.0f, -3.14 / 2.0f, 0.0f));

	StaticObject* wooden = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	wooden->SetModel_Key("Wooden");
	wooden->SetPosition(D3DXVECTOR3(-6.0f, 0.0f, 83.0f));
	wooden->SetScale(D3DXVECTOR3(0.80f, 0.80f, 0.80f));
	wooden->SetRotation(D3DXVECTOR3(0.0f, 3.14 / 2.0f, 0.0f));

	StaticObject* bench = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	bench->SetModel_Key("Bench");
	bench->SetPosition(D3DXVECTOR3(33.0f, 0.0f, 120.0f));
	bench->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	bench->SetRotation(D3DXVECTOR3(0.0f, -3.14/6*5.0f, 0.0f));

	StaticObject* bench2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	bench2->SetModel_Key("Bench");
	bench2->SetPosition(D3DXVECTOR3(13.0f, 0.0f, 120.0f));
	bench2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	bench2->SetRotation(D3DXVECTOR3(0.0f, 3.14 / 6 * 5.0f, 0.0f));





	const int maxwthfence = 5;

	for (int i = 0; i < maxwthfence; i++)
	{
		StaticObject* fence = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		fence->SetModel_Key("Fence");
		fence->SetPosition(D3DXVECTOR3(-21.0f+ (i * 3.0f), 0.0f, 10.0f));
		fence->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		fence->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	}




	StaticObject* fence1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence1->SetModel_Key("Fence");
	fence1->SetPosition(D3DXVECTOR3(-22.0f, 0.0f, 10.0f));
	fence1->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fence1->SetRotation(D3DXVECTOR3(0.0f, -3.14f / 2, 0.0f));

	StaticObject* fence2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence2->SetModel_Key("Fence");
	fence2->SetPosition(D3DXVECTOR3(-22.0f, 0.0f, 6.0f));
	fence2->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fence2->SetRotation(D3DXVECTOR3(0.0f, -3.14f/2, 0.0f));

	StaticObject* fence3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence3->SetModel_Key("Fence");
	fence3->SetPosition(D3DXVECTOR3(-22.0f, 0.0f, 2.0f));
	fence3->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fence3->SetRotation(D3DXVECTOR3(0.0f, -3.14f / 2, 0.0f));

	StaticObject* fence4 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence4->SetModel_Key("Fence");
	fence4->SetPosition(D3DXVECTOR3(-22.0f, 0.0f, -2.0f));
	fence4->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fence4->SetRotation(D3DXVECTOR3(0.0f, -3.14f / 2, 0.0f));

	StaticObject* fence5 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence5->SetModel_Key("Fence");
	fence5->SetPosition(D3DXVECTOR3(-22.0f, 0.0f, -6.0f));
	fence5->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fence5->SetRotation(D3DXVECTOR3(0.0f, -3.14f / 2, 0.0f));

	StaticObject* fence6 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence6->SetModel_Key("Fence");
	fence6->SetPosition(D3DXVECTOR3(-22.0f, 0.0f, -10.0f));
	fence6->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fence6->SetRotation(D3DXVECTOR3(0.0f, -3.14f / 2, 0.0f));


	StaticObject* fence7 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence7->SetModel_Key("Fence");
	fence7->SetPosition(D3DXVECTOR3(-21.0f, 0.0f, -13.0f));
	fence7->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fence7->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* fence8 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence8->SetModel_Key("Fence");
	fence8->SetPosition(D3DXVECTOR3(-17.0f, 0.0f, -13.0f));
	fence8->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fence8->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* fence9 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence9->SetModel_Key("Fence");
	fence9->SetPosition(D3DXVECTOR3(-13.0f, 0.0f, -13.0f));
	fence9->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fence9->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* fence10 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence10->SetModel_Key("Fence");
	fence10->SetPosition(D3DXVECTOR3(-9.0f, 0.0f, -13.0f));
	fence10->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fence10->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));



	/*StaticObject* for1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	for1->SetModel_Key("MiddleTree");
	for1->SetPosition(D3DXVECTOR3(-15.0f, 0.0f, -16.0f));
	for1->SetScale(D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	for1->SetRotation(D3DXVECTOR3(0.0f, 3.14 / 2.0f, 0.0f));*/


	const int maxforest_bes1 = 4;

	for (int i = 0; i < maxforest_bes1; i++)
	{
		StaticObject* forest_bes1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		forest_bes1->SetModel_Key("MiddleTree");
		forest_bes1->SetPosition(D3DXVECTOR3(-19.0f + (i * 5.0f), 0.0f, -18.0f));
		forest_bes1->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		forest_bes1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	}

	const int maxforest_bes2 = 4;

	for (int i = 0; i < maxforest_bes2; i++)
	{
		StaticObject* forest_bes2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		forest_bes2->SetModel_Key("MiddleTree");
		forest_bes2->SetPosition(D3DXVECTOR3(4.0f + (i * 5.0f), 0.0f, -18.0f));
		forest_bes2->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		forest_bes2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	}

	const int maxforest_bes3 = 10;

	for (int i = 0; i < maxforest_bes3; i++)
	{
		StaticObject* forest_bes3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		forest_bes3->SetModel_Key("MiddleTree");
		forest_bes3->SetPosition(D3DXVECTOR3(-14.0f + (i * 5.0f), 0.0f, -64.0f));
		forest_bes3->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		forest_bes3->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	}

	const int maxforest_ver1 = 10;

	for (int i = 0; i < maxforest_ver1; i++)
	{
		StaticObject* forest_ver1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		forest_ver1->SetModel_Key("MiddleTree");
		forest_ver1->SetPosition(D3DXVECTOR3(-18.0f, 0.0f, -20.0f - (i * 5.0f)));
		forest_ver1->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		forest_ver1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	}


	const int maxforest_ver2 = 10;

	for (int i = 0; i < maxforest_ver2; i++)
	{
		StaticObject* forest_ver2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		forest_ver2->SetModel_Key("MiddleTree");
		forest_ver2->SetPosition(D3DXVECTOR3(26.0f, 0.0f, -16.0f - (i * 5.0f)));
		forest_ver2->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		forest_ver2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	}




	srand(0);

	for (int i = 0; i < 18; i++)
	{
		StaticObject* staticObject = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		staticObject->SetModel_Key("ForestTree");
		staticObject->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));

		D3DXVECTOR3 pos;
		pos.x = (float)rand() / RAND_MAX * 100.0f + 8.0f;
		pos.z = (float)rand() / RAND_MAX * 100.0f + 140.0f;
		pos.y = 0.0f;

		staticObject->SetPosition(pos);
	}


	for (int i = 0; i < 25; i++)
	{
		StaticObject* staticObject = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		staticObject->SetModel_Key("ForestTree");
		staticObject->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));

		D3DXVECTOR3 pos;
		pos.x = (float)rand() / RAND_MAX * 100.0f - 45.0f;
		pos.z = (float)rand() / RAND_MAX * 100.0f - 115.0f;
		pos.y = 0.0f;

		staticObject->SetPosition(pos);
	}



	StaticObject* fencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fencewood->SetModel_Key("FenceWood");
	fencewood->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, 170.0f));
	fencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fencewood->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));




	 const int maxfence = 19;
	
	for (int i = 0; i < maxfence; i++)
	{
		StaticObject* fencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		fencewood->SetModel_Key("FenceWood");
		fencewood->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, 170.0f - (i * 5.0f)));
		fencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		fencewood->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));
	}

	StaticObject* fencewood1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fencewood1->SetModel_Key("FenceWood");
	fencewood1->SetPosition(D3DXVECTOR3(18.0f, 0.0f, 26.0f));
	fencewood1->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fencewood1->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));

	
	
	const int vermaxfence = 11;

	for (int i = 0; i < vermaxfence; i++)
	{
	StaticObject* verfencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	verfencewood->SetModel_Key("FenceWood");
	verfencewood->SetPosition(D3DXVECTOR3(18.0f, 0.0f, 19.0f - (i * 3.0f)));
	verfencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	verfencewood->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));
	}


	const int besmaxfence = 8;

	for (int i = 0; i < besmaxfence; i++)
	{
		StaticObject* besfencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		besfencewood->SetModel_Key("FenceWood");
		besfencewood->SetPosition(D3DXVECTOR3(18.0f + (i * 4.0f), 0.0f, -15.0f));
		besfencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		besfencewood->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	const int oppbesmaxfence = 8;

	for (int i = 0; i < oppbesmaxfence; i++)
	{
		StaticObject* oppbesfencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		oppbesfencewood->SetModel_Key("FenceWood");
		oppbesfencewood->SetPosition(D3DXVECTOR3(18.0f + (i * 4.0f), 0.0f, 26.0f));
		oppbesfencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		oppbesfencewood->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}


	const int oppvermaxfence = 10;

	for (int i = 0; i < oppvermaxfence; i++)
	{
		StaticObject* oppverfencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		oppverfencewood->SetModel_Key("FenceWood");
		oppverfencewood->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 25.0f - (i * 4.0f)));
		oppverfencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		oppverfencewood->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));
	}



	const int maxtree = 5;

	for (int i = 0; i < maxtree; i++)
	{
		StaticObject* treemiddle = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		treemiddle->SetModel_Key("MiddleTree");
		treemiddle->SetPosition(D3DXVECTOR3(70.0f, 0.0f, 60.0f + (i * 20.0f)));
		treemiddle->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
		treemiddle->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}




	StaticObject* treemiddle5 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	treemiddle5->SetModel_Key("MiddleTree");
	treemiddle5->SetPosition(D3DXVECTOR3(-40.0f, 0.0f, 180.0f));
	treemiddle5->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	treemiddle5->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* TAIZYU = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	TAIZYU->SetModel_Key("SymbolTree");
	TAIZYU->SetPosition(D3DXVECTOR3(0.0f, -20.5f, 165.0f));
	TAIZYU->SetScale(D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	TAIZYU->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* windmill = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	windmill->SetModel_Key("WindMill");
	windmill->SetPosition(D3DXVECTOR3(-25.0f, 0.0f, 101.0f));
	windmill->SetScale(D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	windmill->SetRotation(D3DXVECTOR3(0.0f, -80.0f, 0.0f));

	StaticObject* gate1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	gate1->SetModel_Key("Gate");
	gate1->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 42.0f));
	gate1->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	gate1->SetRotation(D3DXVECTOR3(0.0f, -132.0f, 0.0f));

	StaticObject* gate2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	gate2->SetModel_Key("Gate2");
	gate2->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 67.0f));
	gate2->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	gate2->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* gate3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	gate3->SetModel_Key("Gate3");
	gate3->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	gate3->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	gate3->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* flower = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower->SetModel_Key("Flower");
	flower->SetPosition(D3DXVECTOR3(26.0f, 0.0f, 67.0f));
	flower->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* flower2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
    flower2->SetModel_Key("Flower2");
    flower2->SetPosition(D3DXVECTOR3(27.0f, 0.0f, 67.0f));
    flower2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
    flower2->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* flower3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower3->SetModel_Key("Flower3");
	flower3->SetPosition(D3DXVECTOR3(28.0f, 0.0f, 67.0f));
	flower3->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower3->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f)); 

	StaticObject* flower4 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower4->SetModel_Key("Flower4");
	flower4->SetPosition(D3DXVECTOR3(12.0f, 0.0f, 67.0f));
	flower4->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower4->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* flower5 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower5->SetModel_Key("Flower5");
	flower5->SetPosition(D3DXVECTOR3(13.0f, 0.0f, 67.0f));
	flower5->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower5->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* flower6 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower6->SetModel_Key("Flower6");
	flower6->SetPosition(D3DXVECTOR3(14.0f, 0.0f, 67.0f));
	flower6->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower6->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));


	/*StaticObject* bridge = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	bridge->SetModel_Key("Bridge");
	bridge->SetPosition(D3DXVECTOR3(110.0f, 0.0f, 70.0f));
	bridge->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	bridge->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));*/


	/*StaticObject* carriage = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	carriage->SetModel_Key("Carriage");
	carriage->SetPosition(D3DXVECTOR3(-20.0f, 0.0f, -25.0f));
	carriage->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	carriage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));*/

	StaticObject* mountain = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		mountain->SetModel_Key("Mountain");
		mountain->SetPosition(D3DXVECTOR3(60.0f, 9.0f, -80.0f));
	mountain->SetScale(D3DXVECTOR3(20.0f, 20.0f, 20.0f));
	mountain->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));



	StaticObject* tile = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	tile->SetModel_Key("Tile");
	tile->SetPosition(D3DXVECTOR3(20.0f, -0.99f, 104.0f));
	tile->SetScale(D3DXVECTOR3(8.0f, 10.0f, 8.0f));
	tile->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f)); 

	StaticObject* well = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	well->SetModel_Key("Well");
	well->SetPosition(D3DXVECTOR3(12.0f, 0.0f, 16.0f));
	well->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	well->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* hut = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	hut->SetModel_Key("Hut");
	hut->SetPosition(D3DXVECTOR3(43.0f, 0.0f, 20.0f));
	hut->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	hut->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));

	scene->AddGameObject<COW>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(35.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	scene->AddGameObject<COW>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(30.0f, 0.0f, 10.0f), D3DXVECTOR3(0.0f, 55.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	scene->AddGameObject<COW>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(26.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 128.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

}
