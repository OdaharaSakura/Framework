#include "main.h"
#include "savedataManager.h"
#include "manager.h"
#include "scene.h"
#include "farmTile.h"
#include "farmField.h"
#include "time.h"
#include "player.h"
#include "inventory.h"
#include "item.h"
#include "iEquipment.h"
#include <fstream>
#include "nlohmann/json.hpp"

#include <string>
#include <vector>

using json = nlohmann::json;

SaveData SaveDataManager::m_SaveData{};

void to_json(json& j, const FarmTileData& farmtileData) {
    j = json{
        {"cropKey", farmtileData.cropKey},
        {"cropStage", farmtileData.cropStage},
        {"tileStage", farmtileData.tileStage},
        {"growthMinute", farmtileData.growthMinute} };
}

void from_json(const json& j, FarmTileData& farmtileData) {
    j.at("cropKey").get_to(farmtileData.cropKey);       // get_to(T& arg) は arg = get<T>() と同じ
    j.at("cropStage").get_to(farmtileData.cropStage);
    j.at("tileStage").get_to(farmtileData.tileStage);
    j.at("growthMinute").get_to(farmtileData.growthMinute);
}

void to_json(json& j, const TimeData& t) {
    j = json{
        {"minute", t.minute},
        {"hour", t.hour},
        {"day", t.day},
        {"month", t.month}
    };
}

void from_json(const json& j, TimeData& t) {
    j.at("minute").get_to(t.minute);       // get_to(T& arg) は arg = get<T>() と同じ
    j.at("hour").get_to(t.hour);
    j.at("day").get_to(t.day);
    j.at("month").get_to(t.month);
}

void to_json(json& j, const PlayerData& p) {
    j = json{
        {"money", p.money},
        {"positionx", p.positionx},
        {"positiony", p.positiony},
        {"positionz", p.positionz},
        {"possessionItemKeys", p.possessionItemKeys},
        {"equipmentItemKey", p.equipmentItemKey}
    };
}

void from_json(const json& j, PlayerData& p) {
    j.at("money").get_to(p.money);       // get_to(T& arg) は arg = get<T>() と同じ
    j.at("positionx").get_to(p.positionx);
    j.at("positiony").get_to(p.positiony);
    j.at("positionz").get_to(p.positionz);
    j.at("possessionItemKeys").get<std::vector<std::string>>();
    j.at("equipmentItemKey").get<std::string>();
}

void SaveDataManager::Save()
{
    std::vector<FarmTileData> farmTilesData{};
    Scene* scene = Manager::GetScene();

    // シーンから全てのFarmTileを取得し、それぞれのデータを保存
    auto farmField = scene->GetGameObject<FarmField>();
    std::vector<FarmTile*> farmTiles = farmField->GetFarmTiles();
    for (auto tile : farmTiles) {
        FarmTileData data;
        // tileからデータを取得してdataにセット
        data.cropKey = tile->GetCropKey();
        data.cropStage = tile->GetCropState();
        data.tileStage = tile->GetFarmTileState();
        data.growthMinute = tile->GetCropGrowTime();
        farmTilesData.push_back(data);
    }

    auto time = scene->GetGameObject<Time>();
    TimeData timeData{};
    timeData.minute = time->GetMinutes();
    timeData.hour = time->GetHours();
    timeData.day = time->GetDay();
    timeData.month = time->GetMonth();

    auto player = scene->GetGameObject<Player>();
    auto inventory = scene->GetGameObject<Inventory>();
    auto equipment = scene->GetGameObject<IEquipment>();
    PlayerData playerData{};
    playerData.money = 0;//後で変える
    playerData.positionx = player->GetPosition().x;
    playerData.positiony = player->GetPosition().y;
    playerData.positionz = player->GetPosition().z;
    playerData.possessionItemKeys = inventory->GetPossessionItemKeys();
    playerData.equipmentItemKey = equipment->GetEquipmentKey();

    m_SaveData.farmTileData = farmTilesData;
    m_SaveData.timeData = timeData;
    m_SaveData.playerData = playerData;

    json j;

    // m_SaveDataから取得したデータをJSONオブジェクトに変換
    j["farmTilesData"] = m_SaveData.farmTileData;
    j["timeData"] = m_SaveData.timeData;
    j["playerData"] = m_SaveData.playerData;

    std::ofstream ofs("asset\\json\\savedata.json");
    if (ofs.is_open()) {
        ofs << std::setw(4) << j << std::endl; 
        ofs.close();
    }
}
void SaveDataManager::Load(FarmField* farmField, Inventory* inventory, IEquipment* iEquipment, Player* player, Time* time)
{
    std::ifstream i("asset\\json\\savedata.json");
    json j;
    i >> j;

    m_SaveData.farmTileData = j.at("farmTilesData").get<std::vector<FarmTileData>>();
    m_SaveData.timeData = j.at("timeData").get<TimeData>();
    m_SaveData.playerData = j.at("playerData").get<PlayerData>();

    farmField->LoadFarmTileData(m_SaveData.farmTileData);
    time->Load(m_SaveData.timeData);
    iEquipment->Load(m_SaveData.playerData);
    inventory->Load(m_SaveData.playerData);
    player->LoadPlayerData(m_SaveData.playerData);
}

void SaveDataManager::Delete()
{
	std::remove("asset\\json\\savedata.json");
}