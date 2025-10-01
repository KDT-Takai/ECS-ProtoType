#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

#include "EntityManager.h"  // EntityManager.h

inline bool operator==(const EntityID& lhs, const EntityID& rhs) {
    return lhs.index == rhs.index && lhs.generation == rhs.generation;
}

// unordered_map用
namespace std {
    template<>
    struct hash<EntityID> {
        size_t operator()(const EntityID& e) const {
            return (size_t(e.index) << 32) | e.generation;
        }
    };
}

// ComponentManager データ管理
// 目的 各コンポーネント型ごとにエンティティへのデータを保存・管理
// コンポーネントの追加/削除/検索/反復を効率的に行う
class ComponentManager
{
private:

public:
	// コンポーネントの追加
	void AddComponent() {}
	void RemoveComponent() {}
	void GetComponent() {}
	void IterateComponents() {}
};