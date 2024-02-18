#include "main.h"
#include "itemDataContainer.h"
#include <fstream>
#include <iostream>
#include <sstream>


std::vector<ItemData> ItemDataContainer::m_ItemData{};
std::vector<EquipmentData> ItemDataContainer::m_EquipmentData{};
std::vector<CropData> ItemDataContainer::m_CropData{};
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
                cells[1],//Key
                cells[2],//TexturePass
                cells[7],//ModelPass
                std::stoi(cells[8])//LostHP
                });

            m_ItemData.push_back({ cells[0], cells[1], cells[2], cells[3], cells[4], std::stoi(cells[5]), std::stoi(cells[6]), false, 0});
            continue;
        }
        if (cells[0] == "��������")
        {
            m_CropData.push_back({
				cells[1],//Key
				cells[2],//TexturePass
				std::stoi(cells[9]),//GrowthTime
				std::stoi(cells[10]),//GrowthFirstState
				std::stoi(cells[11]),//GrowthHarvestState
                cells[12],//FirstStateModelPass
                cells[13],//HarvestModelPass
				});
                //ItemData�I�u�W�F�N�g�Ƀf�[�^���i�[���A���X�g�ɒǉ�
                m_ItemData.push_back({ cells[0], cells[1], cells[2], cells[3], cells[4], std::stoi(cells[5]), std::stoi(cells[6]) , true , std::stoi(cells[8])});
                 continue;
        }

        // ItemData�I�u�W�F�N�g�Ƀf�[�^���i�[���A���X�g�ɒǉ�
        m_ItemData.push_back({ cells[0], cells[1], cells[2], cells[3], cells[4], std::stoi(cells[5]), std::stoi(cells[6]) , cells[7] == "1", std::stoi(cells[8]) });
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

EquipmentData ItemDataContainer::GetEquipmentData_Key(std::string key)
{
    // std::find_if���g�p���ē����m_Key������EquipmentData������
    auto it = std::find_if(m_EquipmentData.begin(), m_EquipmentData.end(), [&key](const EquipmentData& equipment) {
		return equipment.m_Key == key;
		});


    // �������ʂ̃`�F�b�N�ƕ\��
    if (it != m_EquipmentData.end()) {
        return *it;
    }
    else {
        return EquipmentData();
    }
}

CropData ItemDataContainer::GetCropData_Key(std::string key)
{
	// std::find_if���g�p���ē����m_Key������CropData������
    auto it = std::find_if(m_CropData.begin(), m_CropData.end(), [&key](const CropData& crop) {
		return crop.m_Key == key;
		});

	// �������ʂ̃`�F�b�N�ƕ\��
    if (it != m_CropData.end()) {
		return *it;
	}
    else {
		return CropData();
	}
}
