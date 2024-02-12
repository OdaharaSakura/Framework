#include "main.h"
#include "itemDataContainer.h"
#include <fstream>
#include <iostream>
#include <sstream>


std::vector<ItemData> ItemDataContainer::m_ItemData{};

void ItemDataContainer::Load()
{
    std::string filename= "csv/item.csv";
    std::ifstream file(filename); // �t�@�C�����J��
    std::string line;
    while (std::getline(file, line)) { // �t�@�C������s��ǂݍ���

        std::stringstream lineStream(line); // �s�f�[�^���X�g���[���Ƃ��Ĉ���

        std::vector<std::string> cells; // �Z�����ꎞ�I�ɕێ�����x�N�^�[
        std::string cell;
        while (std::getline(lineStream, cell, ',')) { // �J���}�ŋ�؂�ꂽ�l��ǂݍ���

            cells.push_back(cell); // �l���x�N�^�[�ɒǉ�
        }
        // �ŏ��̍s�i�w�b�_�[�j���X�L�b�v
        if (cells[0] == "Type") continue;

        if (cells[0] == "������")
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
    //    if (cells[0] == "��������")
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

        // ItemData�I�u�W�F�N�g�Ƀf�[�^���i�[���A���X�g�ɒǉ�
        m_ItemData.push_back({ cells[0], cells[1], cells[2], cells[3], cells[4], std::stoi(cells[5]), std::stoi(cells[6]) });
    }
}

ItemData ItemDataContainer::GetItemData_Key(std::string key)
{
    // std::find_if���g�p���ē����m_Key������ItemData������
    auto it = std::find_if(m_ItemData.begin(), m_ItemData.end(), [&key](const ItemData& item) {
        return item.m_Key == key;
        });

    // �������ʂ̃`�F�b�N�ƕ\��
    if (it != m_ItemData.end()) {
        return *it;
    }
    else {
        return ItemData();
    }
}
