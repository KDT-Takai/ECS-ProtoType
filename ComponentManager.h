#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <string>

#include "EntityManager.h"  // EntityManager.h

// ComponentManager.hの使い方 例
//ComponentManager cm;
//EntityID e{ 0, 1 };
// コンポーネント追加
//cm.AddComponent(e, Position{ 10.f, 20.f });
//cm.AddHealth(e, Health{ 100, 100 });
// 取得
//if (auto pos = cm.GetComponent(e)) {
//	pos->x += 5;
//}
// イテレーション
//cm.IteratePositions([](EntityID id, Position& p) {
//	printf("Entity %u Pos=(%f,%f)\n", id.index, p.x, p.y);
//	});
//cm.IterateHealths([](EntityID id, Health& h) {
//	printf("Entity %u HP=%d/%d\n", id.index, h.hp, h.maxHp);
//	});

// EntityID 比較演算子
inline bool operator==(const EntityID& lhs, const EntityID& rhs) {
	// index と generation の両方が同じなら等しい
	return lhs.index == rhs.index && lhs.generation == rhs.generation;
}

// unordered_map用ハッシュ関数
namespace std {
	template<>
	struct hash<EntityID> {                                 // EntityID 用のハッシュ関数
		size_t operator()(const EntityID& e) const {        // index と generation を組み合わせてハッシュ値を生成
			return (size_t(e.index) << 32) | e.generation;  // 上位32ビットに index、下位32ビットに generation を配置
		}
	};
}

// コンポーネント定義
// Position コンポーネント
struct Position {
	float x, y;	// DxLib では float 型が推奨されているので float
};
// Velocity コンポーネント
struct Velocity {
	float vx; // x方向の速度
	float vy; // y方向の速度
};
// Health コンポーネント
struct Health {
	int hp;
	int maxHp;
};

// ComponentStorage コンポーネントデータ管理
template<typename Component>
class ComponentStorage {
private:

	// EntityID をキー、Component を値とするハッシュマップ
	std::unordered_map<EntityID, Component> data;

public:
	// Add コンポーネント追加
	void Add(EntityID e, const Component& comp) {
		data[e] = comp;                         // e に対応するコンポーネントを追加または更新
	}
	// Remove コンポーネント削除
	void Remove(EntityID e) {
		data.erase(e);                          // e に対応するコンポーネントを削除
	}
	// Get コンポーネント取得
	Component* Get(EntityID e) {
		auto it = data.find(e);                 // e に対応するコンポーネントを検索
		if (it == data.end()) return nullptr;	// 見つからなければ nullptr を返す
		return &it->second;			            // 見つかればコンポーネントへのポインタを返す
	}
	// Has コンポーネント存在確認
	bool Has(EntityID e) const {
		return data.find(e) != data.end();      // e に対応するコンポーネントが存在するか
	}
	// Iterate 全コンポーネントを反復処理
	template<typename Func>
	void Iterate(Func&& func) {                 // func は (EntityID, Component&) を引数に取る関数オブジェクト
		for (auto& [id, comp] : data) {         // C++17 の構造化束縛で id と comp に分解
			func(id, comp);                     // func を呼び出す
		}
	}
};


// ComponentManager データ管理
// 目的 各コンポーネント型ごとにエンティティへのデータを保存・管理
// コンポーネントの追加/削除/検索/反復を効率的に行う
class ComponentManager {
private:
	// Positionコンポーネント管理
	ComponentStorage<Position> positionStorage;
	// Healthコンポーネント管理
	ComponentStorage<Health> healthStorage;

public:
	// コンポーネントの追加、削除、取得、存在確認
	// Positionコンポーネント管理
	void AddComponent(EntityID e, const Position& p) { positionStorage.Add(e, p); }		// 追加
	void RemoveComponent(EntityID e) { positionStorage.Remove(e); }						// 削除
	Position* GetComponent(EntityID e) { return positionStorage.Get(e); }				// 取得
	bool HasComponent(EntityID e) { return positionStorage.Has(e); }					// 存在確認

	// IteratePositions 全Positionコンポーネントを反復処理
	template<typename Func>
	void IteratePositions(Func&& func) { positionStorage.Iterate(func); }

	// Healthコンポーネント管理
	void AddHealth(EntityID e, const Health& h) { healthStorage.Add(e, h); }    // 追加
	Health* GetHealth(EntityID e) { return healthStorage.Get(e); }				// 取得
	void RemoveHealth(EntityID e) { healthStorage.Remove(e); }					// 削除
	bool HasHealth(EntityID e) { return healthStorage.Has(e); }					// 存在確認

	// IterateHealths 全Healthコンポーネントを反復処理
	template<typename Func>
	void IterateHealths(Func&& func) { healthStorage.Iterate(func); }
};