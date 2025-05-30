#include "main.h"
#include "itemFactory.h"
#include "itemDataContainer.h"



Item* ItemFactory::CreateItem(std::string key)
{
    auto itemData = ItemDataContainer::GetItemData_Key(key);
    Item* item = new Item(itemData.m_Type, itemData.m_Key, itemData.m_TexturePass, itemData.m_Name,
        itemData.m_Description, itemData.m_BuyingPrice, itemData.m_SellingPrice, itemData.m_IsEat, itemData.m_Healing);
    return item;
}
