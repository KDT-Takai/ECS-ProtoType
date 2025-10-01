#pragma once
#include <vector>
#include <queue>

// EntityID ����t��ID
struct EntityID {
	uint32_t index;			    // �z��̈ʒu Entity �� vector �̊i�[�ʒu
	uint32_t generation;	    // ���� index ���ė��p����Ă��ʕ��Ƃ��Ĉ������߂̃o�[�W�����ԍ� ����ڂɎg���Ă��邩
};

// EntityManager �Q�[����̃I�u�W�F�N�gID�Ǘ�
// �ړI �G���e�B�e�B����ӂɔ��s�E�j���E�Ɖ� ����ID���ė��p����Ă��Ȃ�����ۏ�
class EntityManager
{
private:

    std::vector<uint32_t> generations;   // �e�C���f�b�N�X�̐���
	std::vector<uint32_t> freeIndices;    // �󂫃C���f�b�N�X queue��vector
	uint32_t nextIndex = 0;              // �܂��g���ĂȂ��V�K�C���f�b�N�X

public:

    // Entity���쐬
    EntityID CreateEntity() {
        uint32_t index;
        if (!freeIndices.empty()) {             // �ė��p�ł���index������ꍇ
            index = freeIndices.back();         // �ė��p�Ώۂ����o��
            freeIndices.pop_back();             // ���X�g����폜
        } else {                                // �ė��p�ł���index�������ꍇ
            index = nextIndex++;                // �V�����C���f�b�N�X�𔭍s
            generations.push_back(0);           // ���̃C���f�b�N�X�p�̐���J�E���^��0�ŏ�����
        }
        // ����t��ID��Ԃ��iindex + ����j
        return { index, generations[index] };
    }

    // Entity���폜
    void DeleteEntity(EntityID id) {
        if (IsAlive(id)) {                      // �n���ꂽID���܂��L���Ȃ�
            generations[id.index]++;            // �����i�߂�i�Â�ID�𖳌����j
            freeIndices.push_back(id.index);         // index���ė��p���ɒǉ�
        }
    }

    // Entity�̐�������
    bool IsAlive(EntityID id) const {
        // index�͈͓����A���オ��v���Ă���ΐ���
        return id.index < generations.size() &&
            generations[id.index] == id.generation;
    }

    // ���T�C�Y�R�X�g
    void Reserve(size_t n) { generations.reserve(n); }

    // �폜���ꂽ�C���f�b�N�X�𐮗����A�����C���f�b�N�X�����k
    // �Q�[�����Z�b�g�⃍�[�h��� freeIndices �𐮗�
    void Compact() {
        // freeIndices����ɂ��āA���̃C���f�b�N�X�����Z�b�g����
        freeIndices.clear();            // ��ɂ���
        nextIndex = generations.size(); // �V�K���s�� generations.size()
    }

};