
#include <map>
#include <functional>
#include <string>
class Equipment;
class ItemDataContainer;

class EquipmentFactory
{
private:
    std::map<std::string, std::function<Equipment* ()>> equipmentMap;

public:
    EquipmentFactory();

    template<typename T>
    void RegisterEquipment(const std::string& key) {
        equipmentMap[key] = [key]() -> Equipment* {
            auto equipmentData = ItemDataContainer::GetEquipmentData_Key(key);
            return new T(
                equipmentData.m_Key,
                equipmentData.m_TexturePass,
                equipmentData.m_ModelPass,
                equipmentData.m_LostHP 
            );
            };
    }

    Equipment* CreateEquipment(std::string key)
    {
        auto it = equipmentMap.find(key);
        if (it != equipmentMap.end()) {
            return it->second(); // Œ©‚Â‚©‚Á‚½ê‡‚ÍŠÖ”‚ğÀs
        }
        return nullptr; // Œ©‚Â‚©‚ç‚È‚©‚Á‚½ê‡‚Ìˆ—
    }
};
