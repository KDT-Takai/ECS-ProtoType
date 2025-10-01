#pragma once
#include "System.h"
#include <iostream>
#include "ComponentManager.h"

class MovementSystem : public System
{
public:
    std::string GetName() const override { return "MovementSystem"; }

    void Update(float deltaTime) override
    {
	//	pos.x += vel.vx * deltaTime;
	//	pos.y += vel.vy * deltaTime;
		// ���̏����F�S�G���e�B�e�B������ Position �� Velocity ���Q��
		// ���ۂɂ� SystemManager �� ComponentManager ����Ώۂ𒊏o
		std::cout << "Update positions based on velocities\n";
    }

    std::vector<std::type_index> GetComponentSignature() const override
    {
        return { typeid(Position), typeid(Velocity) };
    }
};
