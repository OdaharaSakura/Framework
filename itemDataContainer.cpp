#include "main.h"
#include "itemDataContainer.h"
#include <fstream>
#include <iostream>
#include <sstream>


std::vector<ItemData> ItemDataContainer::m_ItemData{};

void ItemDataContainer::Load()
{
    std::string filename= "csv/item.csv";
    std::ifstream file(filename); // ファイルを開く
    std::string line;
    while (std::getline(file, line)) { // ファイルから行を読み込む

        std::stringstream lineStream(line); // 行データをストリームとして扱う

        std::vector<std::string> cells; // セルを一時的に保持するベクター
        std::string cell;
        while (std::getline(lineStream, cell, ',')) { // カンマで区切られた値を読み込む

            cells.push_back(cell); // 値をベクターに追加
        }
        // 最初の行（ヘッダー）をスキップ
        if (cells[0] == "Type") continue;

        if (cells[0] == "そうび")
        {
            m_EquipmentData.push_back({ 
                cells[0],//Type
                cells[1],//Key
                cells[2],//TexturePass
                cells[3],//Name
                cells[4],//Description
                std::stoi(cells[5]),//BuyingPrice
                std::stoi(cells[6]),//SellingPrice
                cells[7] == "1",//IsEat
                cells[8],//ModelPass
                });
            continue;
        }
    //    if (cells[0] == "さくもつ")
    //    {
    //        m_CropData.push_back({
				//cells[0],//Type
				//cells[1],//Key
				//cells[2],//TexturePass
				//cells[3],//Name
				//cells[4],//Description
				//std::stoi(cells[5]),//BuyingPrice
				//std::stoi(cells[6]),//SellingPrice
    //            cells[7] == "1",//IsEat
				//std::stoi(cells[8]),//GrowthTime
				//std::stoi(cells[9]),//HarvestCount
				//std::stoi(cells[10]),//HarvestPrice
				//});
    //    }

        // ItemDataオブジェクトにデータを格納し、リストに追加
        m_ItemData.push_back({ cells[0], cells[1], cells[2], cells[3], cells[4], std::stoi(cells[5]), std::stoi(cells[6]) });
    }
}

ItemData ItemDataContainer::GetItemData_Key(std::string key)
{
    // std::find_ifを使用して特定のm_Keyを持つItemDataを検索
    auto it = std::find_if(m_ItemData.begin(), m_ItemData.end(), [&key](const ItemData& item) {
        return item.m_Key == key;
        });

    // 検索結果のチェックと表示
    if (it != m_ItemData.end()) {
        return *it;
    }
    else {
        return ItemData();
    }
}
