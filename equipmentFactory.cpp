#include "main.h"
#include "equipmentFactory.h"
#include "itemDataContainer.h"
#include "equipment.h"

EquipmentFactory::EquipmentFactory()
{
    equipmentMap["Hoe"] = []() { return new Hoe(); };
    equipmentMap["Axe"] = []() { return new Axe(); };
    equipmentMap["Pickaxe"] = []() { return new Pickaxe(); };
    equipmentMap["WateringCan"] = []() { return new WateringCan(); };
}
