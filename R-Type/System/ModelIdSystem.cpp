#include "System/ModelIdSystem.hpp"

using namespace ECS;

ModelIdSystem::ModelIdSystem()
{
    this->id = 0;
}

void ModelIdSystem::update(ComponentManager &componentManager)
{
    Component &modelId = componentManager.getComponent(typeid(ModelID));

    for (std::size_t i = 0; i < modelId.getSize(); i++) {
        if (modelId.getField(i).has_value())
            std::any_cast<ModelID &>(modelId.getField(i).value()).id = this->id;
    }
}
