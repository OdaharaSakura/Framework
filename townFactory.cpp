#include "main.h"
#include "townFactory.h"
#include "scene.h"
#include "manager.h"
#include "staticObject.h"
#include "road.h"
#include "house.h"

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

	StaticObject* desk = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	desk->SetModel_Key("Desk");
	desk->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 8.0f));
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
	shop1->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 130.0f));
	shop1->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	shop1->SetRotation(D3DXVECTOR3(0.0f, -90.0f, 0.0f));

	StaticObject* shop2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop2->SetModel_Key("Shop2");
	shop2->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 130.0f));
	shop2->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	shop2->SetRotation(D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	/*StaticObject* shop3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop3->SetModel_Key("Shop3");
	shop3->SetPosition(D3DXVECTOR3(70.0f, 0.0f, 100.0f));
	shop3->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	shop3->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));*/





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

	//StaticObject* fence11 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	//fence11->SetModel_Key("Fence");
	//fence11->SetPosition(D3DXVECTOR3(-7.0f, 0.0f, -13.0f));
	//fence11->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	//fence11->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));




	/*const int maxwfence = 15;

	for (int i = 0; i < maxwfence; i++)
	{
		StaticObject* fence12 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
		fence12->SetModel_Key("Fence");
		fence12->SetPosition(D3DXVECTOR3(-5.0f, 0.0f, 9.0f - (i * 1.0f)));
		fence12->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		fence12->SetRotation(D3DXVECTOR3(0.0f, 30.0f, 0.0f));

	}*/



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
	windmill->SetPosition(D3DXVECTOR3(-30.0f, 0.0f, 100.0f));
	windmill->SetScale(D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	windmill->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* gate1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	gate1->SetModel_Key("Gate");
	gate1->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 45.0f));
	gate1->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	gate1->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* gate2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	gate2->SetModel_Key("Gate2");
	gate2->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 80.0f));
	gate2->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	gate2->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* flower = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower->SetModel_Key("Flower");
	flower->SetPosition(D3DXVECTOR3(26.0f, 0.0f, 80.0f));
	flower->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* flower2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
    flower2->SetModel_Key("Flower2");
    flower2->SetPosition(D3DXVECTOR3(27.0f, 0.0f, 80.0f));
    flower2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
    flower2->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* flower3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower3->SetModel_Key("Flower3");
	flower3->SetPosition(D3DXVECTOR3(28.0f, 0.0f, 80.0f));
	flower3->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower3->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f)); 

	StaticObject* flower4 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower4->SetModel_Key("Flower4");
	flower4->SetPosition(D3DXVECTOR3(12.0f, 0.0f, 79.0f));
	flower4->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower4->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* flower5 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower5->SetModel_Key("Flower5");
	flower5->SetPosition(D3DXVECTOR3(13.0f, 0.0f, 79.0f));
	flower5->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower5->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));

	StaticObject* flower6 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	flower6->SetModel_Key("Flower6");
	flower6->SetPosition(D3DXVECTOR3(14.0f, 0.0f, 79.0f));
	flower6->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	flower6->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));


	/*StaticObject* bridge = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	bridge->SetModel_Key("Bridge");
	bridge->SetPosition(D3DXVECTOR3(110.0f, 0.0f, 70.0f));
	bridge->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	bridge->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));*/


	StaticObject* carriage = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	carriage->SetModel_Key("Carriage");
	carriage->SetPosition(D3DXVECTOR3(-20.0f, 0.0f, -25.0f));
	carriage->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	carriage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* mountain = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	mountain->SetModel_Key("Mountain");
	mountain->SetPosition(D3DXVECTOR3(60.0f, 9.0f, -80.0f));
	mountain->SetScale(D3DXVECTOR3(20.0f, 20.0f, 20.0f));
	mountain->SetRotation(D3DXVECTOR3(0.0f, 135.0f, 0.0f));



	//staticobject* dryfield = scene->addgameobject<staticobject>(layer_object_3d);
 //   dryfield->setmodel_key("dryfield");
 //   dryfield->setposition(d3dxvector3(-10.2f, 0.0f, -9.0f));
 //   dryfield->setscale(d3dxvector3(0.7f, 0.7f, 0.7f));
 //   dryfield->setrotation(d3dxvector3(0.0f, 0.0f, 0.0f));

	//staticobject* wetfield = scene->addgameobject<staticobject>(layer_object_3d);
	//wetfield->setmodel_key("wetfield");
	//wetfield->setposition(d3dxvector3(-8.5f, 0.0f, -9.0f));
	//wetfield->setscale(d3dxvector3(0.7f, 0.7f, 0.7f));
	//wetfield->setrotation(d3dxvector3(0.0f, 0.0f, 0.0f));

	//staticobject* seed = scene->addgameobject<staticobject>(layer_object_3d);
	//seed->setmodel_key("seed");
	//seed->setposition(d3dxvector3(-10.2f, 0.2f, -9.0f));
	//seed->setscale(d3dxvector3(0.7f, 0.7f, 0.7f));
	//seed->setrotation(d3dxvector3(0.0f, 0.0f, 0.0f));

	//staticobject* seed1 = scene->addgameobject<staticobject>(layer_object_3d);
	//seed1->setmodel_key("seed");
	//seed1->setposition(d3dxvector3(-8.5f, 0.2f, -9.0f));
	//seed1->setscale(d3dxvector3(0.7f, 0.7f, 0.7f));
	//seed1->setrotation(d3dxvector3(0.0f, 0.0f, 0.0f));

	/*StaticObject* dryfield1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	dryfield1->SetModel_Key("DryField");
	dryfield1->SetPosition(D3DXVECTOR3(-10.2f, 0.0f, -7.3f));
	dryfield1->SetScale(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	dryfield1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* wetfield1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	wetfield1->SetModel_Key("WetField");
	wetfield1->SetPosition(D3DXVECTOR3(-8.5f, 0.0f, -7.3f));
	wetfield1->SetScale(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	wetfield1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* carrot_seedling = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	carrot_seedling->SetModel_Key("Carrot_Seedling");
	carrot_seedling->SetPosition(D3DXVECTOR3(-10.2f, 0.2f, -7.3f));
	carrot_seedling->SetScale(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	carrot_seedling->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* carrot_seedling1 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	carrot_seedling1->SetModel_Key("Carrot_Seedling");
	carrot_seedling1->SetPosition(D3DXVECTOR3(-8.5f, 0.2f, -7.3f));
	carrot_seedling1->SetScale(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	carrot_seedling1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* dryfield2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	dryfield2->SetModel_Key("DryField");
	dryfield2->SetPosition(D3DXVECTOR3(-10.2f, 0.0f, -5.6f));
	dryfield2->SetScale(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	dryfield2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* wetfield2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	wetfield2->SetModel_Key("WetField");
	wetfield2->SetPosition(D3DXVECTOR3(-8.5f, 0.0f, -5.6f));
	wetfield2->SetScale(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	wetfield2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* carrot_seedling2 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	carrot_seedling2->SetModel_Key("Carrot_Seedling2");
	carrot_seedling2->SetPosition(D3DXVECTOR3(-10.2f, 0.2f, -5.6f));
	carrot_seedling2->SetScale(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	carrot_seedling2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* carrot_seedling3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	carrot_seedling3->SetModel_Key("Carrot_Seedling2");
	carrot_seedling3->SetPosition(D3DXVECTOR3(-8.5f, 0.2f, -5.6f));
	carrot_seedling3->SetScale(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	carrot_seedling3->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));*/

	
	const int maxfieldx = 8;
	const int maxfieldz = 11;

	for (int z = 0; z < maxfieldz; z++)
	{
		for (int x = 0; x < maxfieldx; x++)
		{
			StaticObject* dryfield3 = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
			dryfield3->SetModel_Key("DryField");
			dryfield3->SetPosition(D3DXVECTOR3(-9.0f - (x * 1.7f), 0.0f, -8.5f + (z *1.7f)));
			dryfield3->SetScale(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
			dryfield3->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	StaticObject* tile = scene->AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	tile->SetModel_Key("Tile");
	tile->SetPosition(D3DXVECTOR3(17.0f, -0.5f, 107.0f));
	tile->SetScale(D3DXVECTOR3(6.0f, 6.0f, 6.0f));
	tile->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f)); 



	

}
