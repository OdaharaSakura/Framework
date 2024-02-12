#pragma once

#include <map>

class Equipment;

class EquipmentFactory
{
private:
	std::map<std::string, std::function<const Equipment* ()>> equipmentMap;

public:
    EquipmentFactory();

    const Equipment* CreateEquipment(const std::string& key) {
        auto it = equipmentMap.find(key);
        if (it != equipmentMap.end()) {
            return it->second(); // ���������ꍇ�͊֐������s
        }
        return nullptr; // ������Ȃ������ꍇ�̏���
    }
};