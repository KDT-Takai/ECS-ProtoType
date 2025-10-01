#pragma once
#include <string>
#include <vector>
#include <typeindex>

// System 処理
// 特定のコンポーネント群を処理するクラス/関数
// 目的 特定のコンポーネント群に基づく処理を行う
class System
{
public:
    virtual ~System() = default;

    // システム名（デバッグ用）
    virtual std::string GetName() const = 0;

    // 毎フレーム呼ばれる更新処理
    virtual void Update(float deltaTime) = 0;

    // 対象とするコンポーネント群（シグネチャ）
    // → SystemManager が参照して「どのエンティティが対象か」を決定できる
    virtual std::vector<std::type_index> GetComponentSignature() const = 0;
};
