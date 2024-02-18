#include "main.h"
#include "cropFactory.h"
#include "itemDataContainer.h"



Crop* CropFactory::CreateCrop(std::string key)
{
    auto cropData = ItemDataContainer::GetCropData_Key(key);
    Crop* crop = 
        new Crop(cropData.m_Key, cropData.m_TexturePass, cropData.m_GrowthTime, cropData.m_GrowthTimeToFirstState,
			cropData.m_GrowthTimeToHarvest, cropData.m_FirstStateModelPass, cropData.m_HarvestModelPass);
	return crop;
}
