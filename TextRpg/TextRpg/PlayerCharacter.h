#pragma once

#include <string>
#include <vector>

using namespace std;

/**
 * 
 */
enum STATUS {
    HP = 0,
    MAXHP,
    ATTACK,
    GOLD,
    EXP
};


class  PlayerCharacter
{
public:
    PlayerCharacter(const string& name);

    static PlayerCharacter* GetInstance(const string& name = "");

    // ���� ��� => ���ݷ� / ü��
    void DisplayStatus() const;


    // ������ ��� => �κ��丮�� ����
    void UseItem(int index);
    //// �κ��丮�� ������ �߰�
    void AddItem(const Item& item);

    //// �κ��丮���� ������ ����
    void RemoveItem(int index);

    //���� ������ġ
    void IncreaseStat(STATUS stat, int amount);
    // ���� �� => ����ġ ������ �ڵ������� (����������)
    void LevelUp();


    // ��Ÿ Getter�Լ� (�ٸ��� ������)
    int GetLevel() const { return _level; }
    int GetHealth() const { return _health; }
    int GetMaxHealth() const { return _maxHealth; }
    int GetAttack() const { return _attack; }
    int GetGold() const { return _gold; }
    int GetExperience() const { return _experience; }



private:
    static PlayerCharacter* instance; // �̱��� �ν��Ͻ�

    string _name;
    int _level;
    int _health;
    int _maxHealth;
    int _attack;
    int _experience;
    int _gold;
    
    vector<Item> inventory;

};
