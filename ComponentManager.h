#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <string>

#include "EntityManager.h"  // EntityManager.h

// ComponentManager.h�̎g���� ��
//ComponentManager cm;
//EntityID e{ 0, 1 };
// �R���|�[�l���g�ǉ�
//cm.AddComponent(e, Position{ 10.f, 20.f });
//cm.AddHealth(e, Health{ 100, 100 });
// �擾
//if (auto pos = cm.GetComponent(e)) {
//	pos->x += 5;
//}
// �C�e���[�V����
//cm.IteratePositions([](EntityID id, Position& p) {
//	printf("Entity %u Pos=(%f,%f)\n", id.index, p.x, p.y);
//	});
//cm.IterateHealths([](EntityID id, Health& h) {
//	printf("Entity %u HP=%d/%d\n", id.index, h.hp, h.maxHp);
//	});

// EntityID ��r���Z�q
inline bool operator==(const EntityID& lhs, const EntityID& rhs) {
	// index �� generation �̗����������Ȃ瓙����
	return lhs.index == rhs.index && lhs.generation == rhs.generation;
}

// unordered_map�p�n�b�V���֐�
namespace std {
	template<>
	struct hash<EntityID> {                                 // EntityID �p�̃n�b�V���֐�
		size_t operator()(const EntityID& e) const {        // index �� generation ��g�ݍ��킹�ăn�b�V���l�𐶐�
			return (size_t(e.index) << 32) | e.generation;  // ���32�r�b�g�� index�A����32�r�b�g�� generation ��z�u
		}
	};
}

// �R���|�[�l���g��`
// Position �R���|�[�l���g
struct Position {
	float x, y;	// DxLib �ł� float �^����������Ă���̂� float
};
// Velocity �R���|�[�l���g
struct Velocity {
	float vx; // x�����̑��x
	float vy; // y�����̑��x
};
// Health �R���|�[�l���g
struct Health {
	int hp;
	int maxHp;
};

// ComponentStorage �R���|�[�l���g�f�[�^�Ǘ�
template<typename Component>
class ComponentStorage {
private:

	// EntityID ���L�[�AComponent ��l�Ƃ���n�b�V���}�b�v
	std::unordered_map<EntityID, Component> data;

public:
	// Add �R���|�[�l���g�ǉ�
	void Add(EntityID e, const Component& comp) {
		data[e] = comp;                         // e �ɑΉ�����R���|�[�l���g��ǉ��܂��͍X�V
	}
	// Remove �R���|�[�l���g�폜
	void Remove(EntityID e) {
		data.erase(e);                          // e �ɑΉ�����R���|�[�l���g���폜
	}
	// Get �R���|�[�l���g�擾
	Component* Get(EntityID e) {
		auto it = data.find(e);                 // e �ɑΉ�����R���|�[�l���g������
		if (it == data.end()) return nullptr;	// ������Ȃ���� nullptr ��Ԃ�
		return &it->second;			            // ������΃R���|�[�l���g�ւ̃|�C���^��Ԃ�
	}
	// Has �R���|�[�l���g���݊m�F
	bool Has(EntityID e) const {
		return data.find(e) != data.end();      // e �ɑΉ�����R���|�[�l���g�����݂��邩
	}
	// Iterate �S�R���|�[�l���g�𔽕�����
	template<typename Func>
	void Iterate(Func&& func) {                 // func �� (EntityID, Component&) �������Ɏ��֐��I�u�W�F�N�g
		for (auto& [id, comp] : data) {         // C++17 �̍\���������� id �� comp �ɕ���
			func(id, comp);                     // func ���Ăяo��
		}
	}
};


// ComponentManager �f�[�^�Ǘ�
// �ړI �e�R���|�[�l���g�^���ƂɃG���e�B�e�B�ւ̃f�[�^��ۑ��E�Ǘ�
// �R���|�[�l���g�̒ǉ�/�폜/����/�����������I�ɍs��
class ComponentManager {
private:
	// Position�R���|�[�l���g�Ǘ�
	ComponentStorage<Position> positionStorage;
	// Health�R���|�[�l���g�Ǘ�
	ComponentStorage<Health> healthStorage;

public:
	// �R���|�[�l���g�̒ǉ��A�폜�A�擾�A���݊m�F
	// Position�R���|�[�l���g�Ǘ�
	void AddComponent(EntityID e, const Position& p) { positionStorage.Add(e, p); }		// �ǉ�
	void RemoveComponent(EntityID e) { positionStorage.Remove(e); }						// �폜
	Position* GetComponent(EntityID e) { return positionStorage.Get(e); }				// �擾
	bool HasComponent(EntityID e) { return positionStorage.Has(e); }					// ���݊m�F

	// IteratePositions �SPosition�R���|�[�l���g�𔽕�����
	template<typename Func>
	void IteratePositions(Func&& func) { positionStorage.Iterate(func); }

	// Health�R���|�[�l���g�Ǘ�
	void AddHealth(EntityID e, const Health& h) { healthStorage.Add(e, h); }    // �ǉ�
	Health* GetHealth(EntityID e) { return healthStorage.Get(e); }				// �擾
	void RemoveHealth(EntityID e) { healthStorage.Remove(e); }					// �폜
	bool HasHealth(EntityID e) { return healthStorage.Has(e); }					// ���݊m�F

	// IterateHealths �SHealth�R���|�[�l���g�𔽕�����
	template<typename Func>
	void IterateHealths(Func&& func) { healthStorage.Iterate(func); }
};