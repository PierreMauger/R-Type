#include "System/ModelIdSystem.hpp"

using namespace ECS;

ModelIdSystem::ModelIdSystem()
{
    this->id = 0;
}

void ModelIdSystem::update(ComponentManager &componentManager)
{
    std::vector<std::optional<std::any>> &modelId = componentManager.getComponent(typeid(ModelID));

    for (std::size_t i = 0; i < modelId.size(); i++) {
        if (modelId[i].has_value())
            std::any_cast<ModelID &>(modelId[i].value()).id = this->id;
    }
}
