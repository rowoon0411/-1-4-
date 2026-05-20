#pragma once

#include <iostream> //입출력 기능 가져오기
#include <string> //문자열 기능 가져오기
#include <vector> //여러 개 데이터를 저장하는 기능

using namespace std;

// Monster 클래스를 나중에 만들 거라고 미리 알려주는 코드
class Monster;

// =====================
// 플레이어 클래스
// =====================

class Player
{
protected:
    string name;
    string job;

    int level;

    int hp;
    int mp;
    int power;
    int defence;

    int maxHP;
    int maxMP;

    // 경험치 시스템 추가
    int exp; //현재 경험치
    int maxExp; //레벨업에 필요한 경험치

public:
    Player(string name, string job,
        int hp, int mp,
        int power, int defence);

    virtual void attack(Monster* monster) = 0;

    void printPlayerStatus();

    string getName();
    string getJob();

    int getHP();
    int getMP();

    int getMaxHP();
    int getMaxMP();

    int getPower();
    int getDefence();

    void setHP(int newHP);
    void setMP(int newMP);

    // 경험치 함수 추가
    void gainExp(int amount);

    void levelUp();

    virtual ~Player() {}
};

// =====================
// 전사
// =====================

class Warrior : public Player
{
public:
    Warrior(string name,
        int hp,
        int mp,
        int power,
        int defence);

    void attack(Monster* monster) override;
};

// =====================
// 마법사
// =====================

class Magician : public Player
{
public:
    Magician(string name,
        int hp,
        int mp,
        int power,
        int defence);

    void attack(Monster* monster) override;
};

// =====================
// 도적
// =====================

class Thief : public Player
{
public:
    Thief(string name,
        int hp,
        int mp,
        int power,
        int defence);

    void attack(Monster* monster) override;
};

// =====================
// 궁수
// =====================

class Archer : public Player
{
public:
    Archer(string name,
        int hp,
        int mp,
        int power,
        int defence);

    void attack(Monster* monster) override;
};

// =====================
// 몬스터 클래스
// =====================

class Monster
{
private:
    string name;

    int hp;
    int power;
    int defence;

public:
    Monster(string name,
        int hp,
        int power,
        int defence);

    string getName();

    int getHP();
    int getPower();
    int getDefence();

    void setHP(int newHP);

    void Attack();
};

// =====================
// 아이템 구조체
// =====================

struct Item
{
    string name;
    int price;

    void PrintInfo() const;
};

// =====================
// 몬스터 드랍 아이템 생성 함수
// =====================

Item CreateDropItem(string monsterName);

// =====================
// 포션 재료
// =====================

struct PotionIngredient
{
    string name;
    int count;
};

// =====================
// 포션 레시피
// =====================

class PotionRecipe
{
private:
    string name;

    vector<PotionIngredient> ingredients;

public:
    PotionRecipe(
        string name,
        vector<PotionIngredient> ingredients
    );

    string getName();

    vector<PotionIngredient> getIngredients();

    void printRecipe();
};

// =====================
// 포션 제작소
// =====================

class AlchemyWorkshop
{
private:
    vector<PotionRecipe> recipes;

public:
    void AddRecipe(PotionRecipe recipe);

    void ShowAllRecipes();

    void SearchByName(string name);

    void SearchByIngredient(string ingredient);
};

// =====================
// 함수
// =====================

void printStatus(string name, int stat[]);
