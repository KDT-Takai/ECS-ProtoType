#pragma once
#include "System.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include <iostream>

class HealthSystem : public System
{
public:
    std::string GetName() const override { return "HealthSystem"; }

    void Update(float deltaTime) override
    {
        // 仮の処理：全エンティティを見て Health を参照
        // 実際には SystemManager や ComponentManager から対象を抽出
        std::cout << "Check health and apply regeneration/damage\n";
    }

    std::vector<std::type_index> GetComponentSignature() const override
    {
     //   return { typeid(Health) }; // Health を持つエンティティを対象にする
    }
};