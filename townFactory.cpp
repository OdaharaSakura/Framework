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
#include "sphereObject.h"
#include "boxObject.h"

//SphereColliderの置き方//位置を変える、大きさ変えるときはこの書き方
//	SphereObject* sphereroad = scene->AddGameObject<SphereObject>(LAYER_SPHERECOLLIDER);
//	sphereroad->SetPosition(D3DXVECTOR3(0.0f, 0.01f, 8.0f));
//	sphereroad->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));

void TownFactory::SetSphereCollider(StaticObject* gameObject)
{
	Scene* scene = Manager::GetScene();

	SphereObject* sphere = scene->AddGameObject<SphereObject>(LAYER_SPHERECOLLIDER);
	sphere->SetPosition(gameObject->GetPosition());
	sphere->SetScale(gameObject->GetScale());
}

void TownFactory::SetBoxCollider(StaticObject* gameObject)
{
	Scene* scene = Manager::GetScene();

	BoxObject* box = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	box->SetPosition(gameObject->GetPosition());
	box->SetScale(gameObject->GetScale());
	box->SetRotation(gameObject->GetRotation());

}

void TownFactory::CreateTown()
{
	Scene* scene = Manager::GetScene();
	BoxObject* boxColliderTown1 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	boxColliderTown1->SetPosition(D3DXVECTOR3(0.0f, 0.01f, -80.0f));
	boxColliderTown1->SetScale(D3DXVECTOR3(200.0f, 1.0f, 10.0f));

	BoxObject* boxColliderTown2 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	boxColliderTown2->SetPosition(D3DXVECTOR3(0.0f, 0.01f, 165.0f));
	boxColliderTown2->SetScale(D3DXVECTOR3(200.0f, 1.0f, 10.0f));

	BoxObject* boxColliderTown3 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	boxColliderTown3->SetPosition(D3DXVECTOR3(60.0f, 0.01f, 0.0f));
	boxColliderTown3->SetScale(D3DXVECTOR3(10.0f, 1.0f, 400.0f));

	BoxObject* boxColliderTown4 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	boxColliderTown4->SetPosition(D3DXVECTOR3(-38.0f, 0.01f, 0.0f));
	boxColliderTown4->SetScale(D3DXVECTOR3(10.0f, 1.0f, 400.0f));


	scene->AddGameObject<House>(LAYER_OBJECT_3D)->SetPosition(D3DXVECTOR3(12.0f, 3.0f, 6.0f));
	BoxObject* boxColliderHouse = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	boxColliderHouse->SetPosition(D3DXVECTOR3(11.0f,1.0f, 7.0f));
	boxColliderHouse->SetScale(D3DXVECTOR3(3.0f, 1.0f, 4.5f));


	Road* road = scene->AddGameObject<Road>(LAYER_OBJECT_3D);
	road->SetPosition(D3DXVECTOR3(0.0f, 0.01f, 8.0f));
	road->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));

	////==========================丸いコライダーの置き方
	//SphereObject* sphereroad = scene->AddGameObject<SphereObject>(LAYER_SPHERECOLLIDER);
	//sphereroad->SetPosition(D3DXVECTOR3(0.0f, 0.01f, 8.0f));
	//sphereroad->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));
	////==========================

	Road* road1 = scene->AddGameObject<Road>(LAYER_OBJECT_3D);
	road1->SetPosition(D3DXVECTOR3(0.0f, 0.01f, 24.0f));
	road1->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));

	////==========================四角いコライダーの置き方
	//BoxObject* sphereroad = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	//sphereroad->SetPosition(D3DXVECTOR3(0.0f, 0.01f, 8.0f));
	//sphereroad->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));
	////==========================

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


	StaticObject* house2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house2->SetModel_Key("House2");
	house2->SetPosition(D3DXVECTOR3(8.0f, 0.0f, 80.0f));
	house2->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	house2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	BoxObject* sphereroad = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad->SetPosition(D3DXVECTOR3(8.0f, 0.0f, 78.0f));
	sphereroad->SetScale(D3DXVECTOR3(5.0f, 3.0f, 3.5f));




	StaticObject* house3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house3->SetModel_Key("House3");
	house3->SetPosition(D3DXVECTOR3(32.0f, 0.0f, 80.0f));
	house3->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	house3->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	BoxObject* sphereroad1 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad1->SetPosition(D3DXVECTOR3(32.0f, 0.0f, 78.0f));
	sphereroad1->SetScale(D3DXVECTOR3(5.0f, 3.0f, 3.5f));

	StaticObject* flowerbed = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flowerbed->SetModel_Key("FlowerBed");
	flowerbed->SetPosition(D3DXVECTOR3(15.0f, 0.0f, 80.0f));
	flowerbed->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flowerbed->SetRotation(D3DXVECTOR3(0.0f, 3.14f/-2, 0.0f));
	BoxObject* sphereroad2 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad2->SetPosition(D3DXVECTOR3(15.0f, 0.0f, 79.8f));
	sphereroad2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.3f));
	sphereroad2->SetRotation(D3DXVECTOR3(0.0f, 3.14f / -2, 0.0f));

	StaticObject* flowerbed1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flowerbed1->SetModel_Key("FlowerBed");
	flowerbed1->SetPosition(D3DXVECTOR3(25.0f, 0.0f, 80.0f));
	flowerbed1->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flowerbed1->SetRotation(D3DXVECTOR3(0.0f, 3.14f/2, 0.0f));
	BoxObject* sphereroad3 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad3->SetPosition(D3DXVECTOR3(25.0f, 0.0f, 79.8f));
	sphereroad3->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.3f));
	sphereroad3->SetRotation(D3DXVECTOR3(0.0f, 3.14f / 2, 0.0f));

	StaticObject* house4 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house4->SetModel_Key("House4");
	house4->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 140.0f));
	house4->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	house4->SetRotation(D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	BoxObject* sphereroad4 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad4->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 139.9f));
	sphereroad4->SetScale(D3DXVECTOR3(5.0f, 3.0f, 4.5f));
	sphereroad4->SetRotation(D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	StaticObject* house5 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house5->SetModel_Key("House5");
	house5->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 140.0f));
	house5->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	house5->SetRotation(D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	BoxObject* sphereroad5 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad5->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 139.9f));
	sphereroad5->SetScale(D3DXVECTOR3(5.0f, 3.0f, 4.5f));
	sphereroad5->SetRotation(D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	StaticObject* shop1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop1->SetModel_Key("Shop1");
	shop1->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 90.0f));
	shop1->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	shop1->SetRotation(D3DXVECTOR3(0.0f, -3.14/2.0f, 0.0f));
	BoxObject* sphereroad6 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad6->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 90.0f));
	sphereroad6->SetScale(D3DXVECTOR3(5.0f, 3.0f, 4.5f));
	sphereroad6->SetRotation(D3DXVECTOR3(0.0f, -3.14 / 2.0f, 0.0f));

	StaticObject* shop2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop2->SetModel_Key("Shop2");
	shop2->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 113.0f));
	shop2->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	shop2->SetRotation(D3DXVECTOR3(0.0f, 3.14/2.0f, 0.0f));
	BoxObject* sphereroad7 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad7->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 113.0f));
	sphereroad7->SetScale(D3DXVECTOR3(5.0f, 3.0f, 4.5f));
	sphereroad7->SetRotation(D3DXVECTOR3(0.0f, 3.14 / 2.0f, 0.0f));

	StaticObject* shop3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop3->SetModel_Key("Shop3");
	shop3->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 90.0f));
	shop3->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	shop3->SetRotation(D3DXVECTOR3(0.0f, 3.14/2.0f, 0.0f)); 
	BoxObject* sphereroad8 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad8->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 90.0f));
	sphereroad8->SetScale(D3DXVECTOR3(5.0f, 3.0f, 4.5f));
	sphereroad8->SetRotation(D3DXVECTOR3(0.0f, 3.14 / 2.0f, 0.0f));

	StaticObject* shop4 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop4->SetModel_Key("Shop4");
	shop4->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 113.0f));
	shop4->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	shop4->SetRotation(D3DXVECTOR3(0.0f, -3.14 / 2.0f, 0.0f));
	BoxObject* sphereroad9 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad9->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 113.0f));
	sphereroad9->SetScale(D3DXVECTOR3(5.0f, 3.0f, 4.5f));
	sphereroad9->SetRotation(D3DXVECTOR3(0.0f, -3.14 / 2.0f, 0.0f));

	StaticObject* wooden = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	wooden->SetModel_Key("Wooden");
	wooden->SetPosition(D3DXVECTOR3(-6.0f, 0.0f, 83.0f));
	wooden->SetScale(D3DXVECTOR3(0.80f, 0.80f, 0.80f));
	wooden->SetRotation(D3DXVECTOR3(0.0f, 3.14 / 2.0f, 0.0f));
	BoxObject* sphereroad10 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad10->SetPosition(D3DXVECTOR3(-6.0f, 0.0f, 82.5f));
	sphereroad10->SetScale(D3DXVECTOR3(0.80f, 0.80f, 1.0f));
	sphereroad10->SetRotation(D3DXVECTOR3(0.0f, 3.14 / 2.0f, 0.0f));

	StaticObject* bench = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	bench->SetModel_Key("Bench");
	bench->SetPosition(D3DXVECTOR3(33.0f, 0.0f, 120.0f));
	bench->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	bench->SetRotation(D3DXVECTOR3(0.0f, -3.14/6*5.0f, 0.0f));
	BoxObject* sphereroad11 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad11->SetPosition(D3DXVECTOR3(33.0f, 0.0f, 120.0f));
	sphereroad11->SetScale(D3DXVECTOR3(1.2f, 1.0f, 1.0f));
	sphereroad11->SetRotation(D3DXVECTOR3(0.0f, -3.14 / 6 * 5.0f, 0.0f));

	StaticObject* bench2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	bench2->SetModel_Key("Bench");
	bench2->SetPosition(D3DXVECTOR3(13.0f, 0.0f, 120.0f));
	bench2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	bench2->SetRotation(D3DXVECTOR3(0.0f, 3.14 / 6 * 5.0f, 0.0f));
	BoxObject* sphereroad12 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad12->SetPosition(D3DXVECTOR3(13.0f, 0.0f, 120.0f));
	sphereroad12->SetScale(D3DXVECTOR3(1.2f, 1.0f, 1.0f));
	sphereroad12->SetRotation(D3DXVECTOR3(0.0f, 3.14 / 6 * 5.0f, 0.0f));





	const int maxwthfence = 5;

	for (int i = 0; i < maxwthfence; i++)
	{
		StaticObject* fence = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		fence->SetModel_Key("Fence");
		fence->SetPosition(D3DXVECTOR3(-21.0f+ (i * 3.0f), 0.0f, 10.0f));
		fence->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		fence->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		BoxObject* boxColliderFence = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
		boxColliderFence->SetPosition(D3DXVECTOR3(-21.0f + (i * 3.0f), 0.0f, 11.5f));
		boxColliderFence->SetScale(D3DXVECTOR3(2.0f, 2.0f, 0.5f));
	}

	const int maxfarmfence = 6;

	for (int i = 0; i < maxfarmfence; i++)
	{
		StaticObject* fence = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		fence->SetModel_Key("Fence");
		fence->SetPosition(D3DXVECTOR3(-22.0f, 0.0f, 10.0f - (4.0f * i)));
		fence->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		fence->SetRotation(D3DXVECTOR3(0.0f, -3.14f / 2, 0.0f));

		BoxObject* boxColliderFence = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
		boxColliderFence->SetPosition(D3DXVECTOR3(-23.5f , 0.0f, 10.0f - (4.0f * i)));
		boxColliderFence->SetScale(D3DXVECTOR3(0.5f, 2.0f, 2.0f));
	}

	const int maxfarmfence2 = 4;

	for (int i = 0; i < maxfarmfence2; i++)
	{
		StaticObject* fence = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		fence->SetModel_Key("Fence");
		fence->SetPosition(D3DXVECTOR3(-21.0f + (i * 4.0f), 0.0f, -13.0f));
		fence->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		fence->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		BoxObject* boxColliderFence = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
		boxColliderFence->SetPosition(D3DXVECTOR3(-21.0f + (i * 4.0f), 0.0f, -11.5f));
		boxColliderFence->SetScale(D3DXVECTOR3(2.0f, 2.0f, 0.5f));
	}



	const int maxforest_bes1 = 4;

	for (int i = 0; i < maxforest_bes1; i++)
	{
		StaticObject* forest_bes1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		forest_bes1->SetModel_Key("MiddleTree");
		forest_bes1->SetPosition(D3DXVECTOR3(-19.0f + (i * 5.0f), 0.0f, -18.0f));
		forest_bes1->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		forest_bes1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetSphereCollider(forest_bes1);
		

	}

	const int maxforest_bes2 = 4;

	for (int i = 0; i < maxforest_bes2; i++)
	{
		StaticObject* forest_bes2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		forest_bes2->SetModel_Key("MiddleTree");
		forest_bes2->SetPosition(D3DXVECTOR3(4.0f + (i * 5.0f), 0.0f, -18.0f));
		forest_bes2->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		forest_bes2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetSphereCollider(forest_bes2);

	}

	const int maxforest_bes3 = 10;

	for (int i = 0; i < maxforest_bes3; i++)
	{
		StaticObject* forest_bes3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		forest_bes3->SetModel_Key("MiddleTree");
		forest_bes3->SetPosition(D3DXVECTOR3(-14.0f + (i * 5.0f), 0.0f, -64.0f));
		forest_bes3->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		forest_bes3->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetSphereCollider(forest_bes3);
		

	}

	const int maxforest_ver1 = 10;

	for (int i = 0; i < maxforest_ver1; i++)
	{
		StaticObject* forest_ver1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		forest_ver1->SetModel_Key("MiddleTree");
		forest_ver1->SetPosition(D3DXVECTOR3(-18.0f, 0.0f, -20.0f - (i * 5.0f)));
		forest_ver1->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		forest_ver1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetSphereCollider(forest_ver1);

	}


	const int maxforest_ver2 = 10;

	for (int i = 0; i < maxforest_ver2; i++)
	{
		StaticObject* forest_ver2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		forest_ver2->SetModel_Key("MiddleTree");
		forest_ver2->SetPosition(D3DXVECTOR3(26.0f, 0.0f, -16.0f - (i * 5.0f)));
		forest_ver2->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		forest_ver2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetSphereCollider(forest_ver2);

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
		SetSphereCollider(staticObject);
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
		SetSphereCollider(staticObject);
	}



	StaticObject* fencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fencewood->SetModel_Key("FenceWood");
	fencewood->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, 170.0f));
	fencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fencewood->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));
	SetBoxCollider(fencewood);




	 const int maxfence = 19;
	
	for (int i = 0; i < maxfence; i++)
	{
		StaticObject* fencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		fencewood->SetModel_Key("FenceWood");
		fencewood->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, 170.0f - (i * 5.0f)));
		fencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		fencewood->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));
		SetBoxCollider(fencewood);
	}

	StaticObject* fencewood1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fencewood1->SetModel_Key("FenceWood");
	fencewood1->SetPosition(D3DXVECTOR3(18.0f, 0.0f, 26.0f));
	fencewood1->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	fencewood1->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));
	BoxObject* fenceboxcollider = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	fenceboxcollider->SetPosition(D3DXVECTOR3(16.5f, 0.0f, 26.0f));
	fenceboxcollider->SetScale(D3DXVECTOR3(0.5f, 2.0f, 2.0f));

	
	
	const int vermaxfence = 11;

	for (int i = 0; i < vermaxfence; i++)
	{
	StaticObject* verfencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	verfencewood->SetModel_Key("FenceWood");
	verfencewood->SetPosition(D3DXVECTOR3(18.0f, 0.0f, 19.0f - (i * 3.0f)));
	verfencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	verfencewood->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));

	BoxObject* fenceboxcollider = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	fenceboxcollider->SetPosition(D3DXVECTOR3(16.5f, 0.0f, 19.0f - (i * 3.0f)));
	fenceboxcollider->SetScale(D3DXVECTOR3(0.5f, 2.0f, 2.0f));
	}


	const int besmaxfence = 8;

	for (int i = 0; i < besmaxfence; i++)
	{
		StaticObject* besfencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		besfencewood->SetModel_Key("FenceWood");
		besfencewood->SetPosition(D3DXVECTOR3(18.0f + (i * 4.0f), 0.0f, -15.0f));
		besfencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		besfencewood->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetBoxCollider(besfencewood);
	}

	const int oppbesmaxfence = 8;

	for (int i = 0; i < oppbesmaxfence; i++)
	{
		StaticObject* oppbesfencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		oppbesfencewood->SetModel_Key("FenceWood");
		oppbesfencewood->SetPosition(D3DXVECTOR3(18.0f + (i * 4.0f), 0.0f, 26.0f));
		oppbesfencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		oppbesfencewood->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		BoxObject* fenceboxcollider = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
		fenceboxcollider->SetPosition(D3DXVECTOR3(18.0f + (i * 4.0f), 0.0f, 27.5f));
		fenceboxcollider->SetScale(D3DXVECTOR3(2.0f, 2.0f, 0.5f));
	}


	const int oppvermaxfence = 10;

	for (int i = 0; i < oppvermaxfence; i++)
	{
		StaticObject* oppverfencewood = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		oppverfencewood->SetModel_Key("FenceWood");
		oppverfencewood->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 25.0f - (i * 4.0f)));
		oppverfencewood->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		oppverfencewood->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));
		SetBoxCollider(oppverfencewood);
	}



	const int maxtree = 5;

	for (int i = 0; i < maxtree; i++)
	{
		StaticObject* treemiddle = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		treemiddle->SetModel_Key("MiddleTree");
		treemiddle->SetPosition(D3DXVECTOR3(70.0f, 0.0f, 60.0f + (i * 20.0f)));
		treemiddle->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
		treemiddle->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetSphereCollider(treemiddle);
	}




	StaticObject* treemiddle5 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	treemiddle5->SetModel_Key("MiddleTree");
	treemiddle5->SetPosition(D3DXVECTOR3(-40.0f, 0.0f, 180.0f));
	treemiddle5->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	treemiddle5->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSphereCollider(treemiddle5);

	StaticObject* TAIZYU = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	TAIZYU->SetModel_Key("SymbolTree");
	TAIZYU->SetPosition(D3DXVECTOR3(0.0f, -20.5f, 165.0f));
	TAIZYU->SetScale(D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	TAIZYU->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	BoxObject* sphereroad13 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad13->SetPosition(D3DXVECTOR3(19.0f, 0.0f, 145.0f));
	sphereroad13->SetScale(D3DXVECTOR3(12.0f, 12.0f, 12.0f));

	StaticObject* windmill = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	windmill->SetModel_Key("WindMill");
	windmill->SetPosition(D3DXVECTOR3(-25.0f, 0.0f, 101.0f));
	windmill->SetScale(D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	windmill->SetRotation(D3DXVECTOR3(0.0f, -80.0f, 0.0f));
	BoxObject* sphereroad14 = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	sphereroad14->SetPosition(D3DXVECTOR3(-25.0f, 0.0f, 101.0f));
	sphereroad14->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	sphereroad14->SetRotation(D3DXVECTOR3(0.0f, -80.0f, 0.0f));
	

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
	SetSphereCollider(flower);

	StaticObject* flower2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
    flower2->SetModel_Key("Flower2");
    flower2->SetPosition(D3DXVECTOR3(27.0f, 0.0f, 67.0f));
    flower2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
    flower2->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));
	SetSphereCollider(flower2);

	StaticObject* flower3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower3->SetModel_Key("Flower3");
	flower3->SetPosition(D3DXVECTOR3(28.0f, 0.0f, 67.0f));
	flower3->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower3->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));
	SetSphereCollider(flower3);

	StaticObject* flower4 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower4->SetModel_Key("Flower4");
	flower4->SetPosition(D3DXVECTOR3(12.0f, 0.0f, 67.0f));
	flower4->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower4->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));
	SetSphereCollider(flower4);

	StaticObject* flower5 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower5->SetModel_Key("Flower5");
	flower5->SetPosition(D3DXVECTOR3(13.0f, 0.0f, 67.0f));
	flower5->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower5->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));
	SetSphereCollider(flower5);

	StaticObject* flower6 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower6->SetModel_Key("Flower6");
	flower6->SetPosition(D3DXVECTOR3(14.0f, 0.0f, 67.0f));
	flower6->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower6->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));
	SetSphereCollider(flower6);


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
	
	BoxObject* spheremountain = scene->AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	spheremountain->SetPosition(D3DXVECTOR3(0.0f, 0.01f, 8.0f));
	spheremountain->SetScale(D3DXVECTOR3(3.0f, 1.0f, 8.0f));



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
	SetBoxCollider(well);

	StaticObject* hut = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	hut->SetModel_Key("Hut");
	hut->SetPosition(D3DXVECTOR3(43.0f, 0.0f, 20.0f));
	hut->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	hut->SetRotation(D3DXVECTOR3(0.0f, 55.0f, 0.0f));
	SetBoxCollider(hut);

	scene->AddGameObject<COW>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(35.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	scene->AddGameObject<COW>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(30.0f, 0.0f, 10.0f), D3DXVECTOR3(0.0f, 55.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	scene->AddGameObject<COW>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(26.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 128.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	StaticObject* board = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	board->SetModel_Key("Board");
	board->SetPosition(D3DXVECTOR3(43.0f, 0.0f, 91.0f));
	board->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	board->SetRotation(D3DXVECTOR3(0.0f, 3.14/2.0f, 0.0f));
	SetBoxCollider(board);

	StaticObject* board1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	board1->SetModel_Key("Board");
	board1->SetPosition(D3DXVECTOR3(43.0f, 0.0f, 114.0f));
	board1->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	board1->SetRotation(D3DXVECTOR3(0.0f, 3.14 / 2.0f, 0.0f));
	SetBoxCollider(board);


}
