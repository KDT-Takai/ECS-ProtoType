#pragma once
#include <string>
#include <vector>
#include <typeindex>

// System ����
// ����̃R���|�[�l���g�Q����������N���X/�֐�
// �ړI ����̃R���|�[�l���g�Q�Ɋ�Â��������s��
class System
{
public:
    virtual ~System() = default;

    // �V�X�e�����i�f�o�b�O�p�j
    virtual std::string GetName() const = 0;

    // ���t���[���Ă΂��X�V����
    virtual void Update(float deltaTime) = 0;

    // �ΏۂƂ���R���|�[�l���g�Q�i�V�O�l�`���j
    // �� SystemManager ���Q�Ƃ��āu�ǂ̃G���e�B�e�B���Ώۂ��v������ł���
    virtual std::vector<std::type_index> GetComponentSignature() const = 0;
};
