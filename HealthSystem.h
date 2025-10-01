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
        // ���̏����F�S�G���e�B�e�B������ Health ���Q��
        // ���ۂɂ� SystemManager �� ComponentManager ����Ώۂ𒊏o
        std::cout << "Check health and apply regeneration/damage\n";
    }

    std::vector<std::type_index> GetComponentSignature() const override
    {
     //   return { typeid(Health) }; // Health �����G���e�B�e�B��Ώۂɂ���
    }
};