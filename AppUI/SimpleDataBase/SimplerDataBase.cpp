/**
*********************************************************************
*********
* @project_name :lvgl
* @file : SimpleDataBase.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/10/8 
*********************************************************************
*********
*/


#include "SimpleDataBase.hpp"

namespace DataBase
{
    bool SimpleDataBase::Exist(const std::string& key)
    {
        if (_value_map.find(key) != _value_map.end())
        {
            return true;
        }
        return false;
    }

    size_t SimpleDataBase::MemoryUsage()
    {
        size_t ret = 0;
        for (auto& kv : _value_map)
        {
            ret += kv.second.size;
        }
        return ret;
    }

    bool SimpleDataBase::Add(const std::string& key, void* value, size_t size)
    {
        if (Exist(key) || (size == 0))
        {
            return false;
        }

        /* Create */
        ValueInfo_t new_item;
        new_item.size = size;

        /* Create buffer  */
        new_item.addr = _malloc(size);
        /* Copy data */
        _memcpy(new_item.addr, value, size);

        /* Create link */
        _value_map[key] = new_item;

        return true;
    }

    bool SimpleDataBase::Put(const std::string& key, void* value)
    {
        /* Get iterater */
        auto iter = _value_map.find(key);

        /* If exist */
        if (iter != _value_map.end())
        {
            /* Copy new data */
            _memcpy(iter->second.addr, value, iter->second.size);

            return true;
        }

        return false;
    }

    ValueInfo_t* SimpleDataBase::Get(const std::string& key)
    {
        /* Get iterater */
        auto iter = _value_map.find(key);

        /* If exist */
        if (iter != _value_map.end())
        {
            /* Copy value info */
            _memcpy((void*)&_ret_buffer, (void*)&iter->second, sizeof(ValueInfo_t));
        }
        else
        {
            _ret_buffer.size = 0;
            _ret_buffer.addr = nullptr;
        }

        return &_ret_buffer;
    }

    bool SimpleDataBase::Delete(const std::string& key)
    {
        /* Get iterater */
        auto iter = _value_map.find(key);

        /* If exist */
        if (iter != _value_map.end())
        {
            /* Free memory */
            _free(iter->second.addr);

            /* Remove elemant */
            _value_map.erase(iter);

            return true;
        }

        return false;
    }

    void SimpleDataBase::DeleteAll()
    {
        /* Free memory */
        for (auto& kv : _value_map)
        {
            _free(kv.second.addr);
        }

        /* Remove all element */
        _value_map.erase(_value_map.begin(), _value_map.end());
    }
} // namespace DataBase