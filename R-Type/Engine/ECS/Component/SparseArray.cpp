#include "Engine/ECS/Component/SparseArray.hpp"

using namespace eng;

SparseArray::SparseArray()
{
}

void SparseArray::addData(std::size_t id, std::any data)
{
    if (id >= this->_data.size())
        this->_data.resize(id + 1);
    this->_data[id] = data;
}

void SparseArray::emplaceData(std::size_t id, std::any data)
{
    if (id > this->_data.size())
        throw std::runtime_error("Incorrect ID");
    this->_data[id] = data;
}

void SparseArray::destroyData(std::size_t id)
{
    if (id > this->_data.size())
        throw std::runtime_error("Incorrect ID");
    this->_data[id].reset();
}

std::size_t SparseArray::getSize()
{
    return this->_data.size();
}

std::optional<std::any> &SparseArray::getField(std::size_t id)
{
    if (id > this->_data.size())
        throw std::runtime_error("Incorrect ID");
    return this->_data[id];
}

void SparseArray::clear()
{
    this->_data.clear();
}
