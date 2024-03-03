#include "main.h"
#include "equipmentFactory.h"
#include "itemDataContainer.h"
#include "equipment.h"

EquipmentFactory::EquipmentFactory()
{
    RegisterEquipment<Hoe>("Hoe");
    RegisterEquipment<Sickle>("Sickle");
    RegisterEquipment<WaterWand>("WaterWand");
    RegisterEquipment<TomatoSeed>("TomatoSeed");
    RegisterEquipment<CarrotSeed>("CarrotSeed");
    RegisterEquipment<Sword>("Sword");
}

