#include "PlayerCharacter.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <random>


PlayerCharacter* PlayerCharacter::instance = nullptr;

PlayerCharacter* PlayerCharacter::GetInstance(const string& name) 
{
    if (!instance) 
    {
        instance = new PlayerCharacter(name);
    }
    return instance;
}

PlayerCharacter::PlayerCharacter(const string& name)
    : _name(name), _level(1), _health(200), _maxHealth(200), _attack(30), _experience(0), _gold(0) 
{
}




void PlayerCharacter::DisplayStatus() const 
{
    cout << "===== " << _name << "�� ���� =====" << endl;
    cout << "����: " << _level << ", ����ġ: " << _experience << "/100" << endl;
    cout << "ü��: " << _health << "/" << _maxHealth << ", ���ݷ�: " << _attack << endl;
    cout << "���: " << _gold << endl;
    cout << "======================" << endl;
}

void PlayerCharacter::IncreaseStat(STATUS stat, int amount) 
{
    switch (stat)
    {
        case HP:
        {
            _health += amount;
            if (_health > _maxHealth) _health = _maxHealth;
                cout << "ü���� " << amount << "��ŭ �����߽��ϴ�! ���� ü��: " << _health << "/" << _maxHealth << endl;
        }
    break;

    case MAXHP:
    {
        _maxHealth += amount;
        cout << "�ִ� ü���� " << amount << "��ŭ �����߽��ϴ�! ���� �ִ� ü��: " << _maxHealth << endl;
    }
    break;


    case ATTACK:
    {
        _attack += amount;
        cout << "���ݷ��� " << amount << "��ŭ �����߽��ϴ�! ���� ���ݷ�: " << _attack << endl;
    }
        break;

    case GOLD:
    {
        _gold += amount;
        cout << "��尡 " << amount << "��ŭ �����߽��ϴ�! ���� ���: " << _gold << endl;
    }
        break;

    case EXP:
    {
        _experience += amount;
        cout << "����ġ�� " << amount << "��ŭ �����߽��ϴ�! ���� ����ġ: " << _experience << "/100" << endl;

        // ���� �� Ȯ��
        while (_experience >= 100) 
        {
            LevelUp();
            _experience -= 100; // ���� ���� �ʿ��� ����ġ ����
        }
    }
        break;

    default:
        cout << "�� �� ���� Stat ���Դϴ�!" << endl;
        break;
    }

}

void PlayerCharacter::LevelUp()
{
    if (_level >= 10) 
    {
        cout << "�ִ� ������ �����߽��ϴ�!" << endl;
        return;
    }
    _level++;
    _maxHealth += (_level * 20);
    _attack += (_level * 5);
    _health = _maxHealth; // ü�� ���� ȸ��
    _experience = 0; // ����ġ �ʱ�ȭ
    cout << "������! ���� ����: " << _level << endl;
}

void PlayerCharacter::AddGold(int amount)
{
    _gold += amount;
    cout << amount << " ��带 ȹ���߽��ϴ�! ���� ���: " << _gold << endl;
}
void PlayerCharacter::AddExperience(int amount)
{
    _experience += amount;
    cout << amount << " ����ġ�� ȹ���߽��ϴ�! ���� ����ġ: " << _experience << "/100" << endl;

    // ������ Ȯ��
    if (_experience >= 100)
    {
        LevelUp();
    }
}
void PlayerCharacter::UseItem(int index) 
{
    if (index < 0 || index >= _inventory.size()) 
    {
        cout << "�߸��� �ε����Դϴ�!" << endl;
        return;
    }

    const Item& item = _inventory[index];

    item.Use(this);
    
    // ������ ��� �� ����
    RemoveItem(index);
}
void PlayerCharacter::AddItem(const Item& item) 
{
    _inventory.push_back(item);
    cout << item.GetName() << "��(��) ȹ���߽��ϴ�!" << endl;
}

void PlayerCharacter::RemoveItem(int index) 
{
    if (index < 0 || index >= _inventory.size()) 
    {
        throw out_of_range("�߸��� �ε����Դϴ�!");
    }
    _inventory.erase(_inventory.begin() + index);
}
