#include "main.h"
#include "itemFactory.h"
#include "itemDataContainer.h"



const Item* ItemFactory::CreateItem(std::string key)
{
    auto itemData = ItemDataContainer::GetItemData_Key(key);
    Item* item = new Item(itemData.m_Key, itemData.m_TexturePass, itemData.m_ModelPass, itemData.m_Name, itemData.m_Type,
        itemData.m_Description, itemData.m_buyingPrice, itemData.m_sellingPrice);
    return item;
}
