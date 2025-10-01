#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

#include "EntityManager.h"  // EntityManager.h

inline bool operator==(const EntityID& lhs, const EntityID& rhs) {
    return lhs.index == rhs.index && lhs.generation == rhs.generation;
}

// unordered_map�p
namespace std {
    template<>
    struct hash<EntityID> {
        size_t operator()(const EntityID& e) const {
            return (size_t(e.index) << 32) | e.generation;
        }
    };
}

// ComponentManager �f�[�^�Ǘ�
// �ړI �e�R���|�[�l���g�^���ƂɃG���e�B�e�B�ւ̃f�[�^��ۑ��E�Ǘ�
// �R���|�[�l���g�̒ǉ�/�폜/����/�����������I�ɍs��
class ComponentManager
{
private:

public:
	// �R���|�[�l���g�̒ǉ�
	void AddComponent() {}
	void RemoveComponent() {}
	void GetComponent() {}
	void IterateComponents() {}
};