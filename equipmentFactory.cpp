#include "main.h"
#include "equipmentFactory.h"
#include "itemDataContainer.h"
#include "equipment.h"

EquipmentFactory::EquipmentFactory()
{
    RegisterEquipment<Hoe>("Hoe");
    RegisterEquipment<Sickle>("Sickle");
}

