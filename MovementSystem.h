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
		// 仮の処理：全エンティティを見て Position と Velocity を参照
		// 実際には SystemManager や ComponentManager から対象を抽出
		std::cout << "Update positions based on velocities\n";
    }

    std::vector<std::type_index> GetComponentSignature() const override
    {
        return { typeid(Position), typeid(Velocity) };
    }
};
