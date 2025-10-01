#pragma once
#include <vector>
#include <queue>

// EntityID 世代付きID
struct EntityID {
	uint32_t index;			    // 配列の位置 Entity が vector の格納位置
	uint32_t generation;	    // 同じ index が再利用されても別物として扱うためのバージョン番号 何回目に使われているか
};

// EntityManager ゲーム上のオブジェクトID管理
// 目的 エンティティを一意に発行・破棄・照会 同じIDが再利用されていないかを保障
class EntityManager
{
private:

    std::vector<uint32_t> generations;   // 各インデックスの世代
	std::vector<uint32_t> freeIndices;    // 空きインデックス queue→vector
	uint32_t nextIndex = 0;              // まだ使ってない新規インデックス

public:

    // Entityを作成
    EntityID CreateEntity() {
        uint32_t index;
        if (!freeIndices.empty()) {             // 再利用できるindexがある場合
            index = freeIndices.back();         // 再利用対象を取り出し
            freeIndices.pop_back();             // リストから削除
        } else {                                // 再利用できるindexが無い場合
            index = nextIndex++;                // 新しいインデックスを発行
            generations.push_back(0);           // そのインデックス用の世代カウンタを0で初期化
        }
        // 世代付きIDを返す（index + 世代）
        return { index, generations[index] };
    }

    // Entityを削除
    void DeleteEntity(EntityID id) {
        if (IsAlive(id)) {                      // 渡されたIDがまだ有効なら
            generations[id.index]++;            // 世代を進める（古いIDを無効化）
            freeIndices.push_back(id.index);         // indexを再利用候補に追加
        }
    }

    // Entityの生存判定
    bool IsAlive(EntityID id) const {
        // index範囲内かつ、世代が一致していれば生存
        return id.index < generations.size() &&
            generations[id.index] == id.generation;
    }

    // リサイズコスト
    void Reserve(size_t n) { generations.reserve(n); }

    // 削除されたインデックスを整理し、世代やインデックスを圧縮
    // ゲームリセットやロード後に freeIndices を整理
    void Compact() {
        // freeIndicesを空にして、次のインデックスをリセットする
        freeIndices.clear();            // 空にする
        nextIndex = generations.size(); // 新規発行は generations.size()
    }

};