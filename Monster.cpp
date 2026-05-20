//Monster.cpp

#include "Monster.h"

// =====================
// 상태 출력 함수
// =====================

void printStatus(string name, int stat[])
{
    cout << "\n============================\n";
    cout << name << "의 현재 능력치\n";
    cout << "============================\n";
    cout << "HP: " << stat[0] << " MP: " << stat[1] << endl;
    cout << "공격력: " << stat[2] << " 방어력: " << stat[3] << endl;
    cout << "============================\n";
}

// =====================
// 플레이어
// =====================

Player::Player(
    string name,
    string job,
    int hp,
    int mp,
    int power,
    int defence
)
{
    this->name = name;
    this->job = job;

    level = 1;

    exp = 0;
    maxExp = 100;

    this->hp = hp;
    this->mp = mp;
    this->power = power;
    this->defence = defence;

    this->maxHP = hp;
    this->maxMP = mp;
}

void Player::printPlayerStatus()
{
    cout << "------------------------------------\n";

    cout << "닉네임: "
        << name
        << " | 직업: "
        << job
        << " | Lv."
        << level
        << endl;

    cout << "HP: "
        << hp
        << "/"
        << maxHP
        << " | MP: "
        << mp
        << "/"
        << maxMP
        << " | 공격력: "
        << power
        << " | 방어력: "
        << defence
        << endl;

    cout << "EXP: "
        << exp
        << "/"
        << maxExp
        << endl;

    cout << "------------------------------------\n";
}

string Player::getName()
{
    return name;
}

string Player::getJob()
{
    return job;
}

int Player::getHP()
{
    return hp;
}

int Player::getMP()
{
    return mp;
}

int Player::getMaxHP()
{
    return maxHP;
}

int Player::getMaxMP()
{
    return maxMP;
}

int Player::getPower()
{
    return power;
}

int Player::getDefence()
{
    return defence;
}

void Player::setHP(int newHP)
{
    hp = newHP;

    if (hp < 0)
    {
        hp = 0;
    }

    if (hp > maxHP)
    {
        hp = maxHP;
    }
}

void Player::setMP(int newMP)
{
    mp = newMP;

    if (mp < 0)
    {
        mp = 0;
    }

    if (mp > maxMP)
    {
        mp = maxMP;
    }
}

// =====================
// 레벨업
// =====================

void Player::gainExp(int amount)
{
    exp += amount;

    cout << "\n★ 전투 승리!\n";

    cout << "-> 경험치 +"
        << amount
        << " 획득! (현재 경험치: "
        << exp
        << "/"
        << maxExp
        << ")\n";

    if (exp >= maxExp)
    {
        levelUp();
    }
}

void Player::levelUp()
{
    cout << "\n... 레벨업 조건 충족\n";

    cout << "-> 레벨 업! Lv."
        << level
        << " -> Lv."
        << level + 1
        << endl;

    level++;

    hp += 10;
    mp += 5;
    power += 5;

    maxHP += 10;
    maxMP += 5;

    exp = 0;
    maxExp += 50;

    cout << "-> HP +10, MP +5, 공격력 +5 증가!\n";
}

// =====================
// 전사
// =====================

Warrior::Warrior(
    string name,
    int hp,
    int mp,
    int power,
    int defence
)
    : Player(
        name,
        "전사",
        hp,
        mp,
        power + 30,
        defence
    )
{
}

void Warrior::attack(Monster* monster)
{
    int damage = power - monster->getDefence();

    if (damage < 1)
    {
        damage = 1;
    }

    monster->setHP(monster->getHP() - damage);

    cout << "[전사] 장검을 휘두른다! -> "
        << monster->getName()
        << "에게 "
        << damage
        << " 데미지!\n";
}

// =====================
// 마법사
// =====================

Magician::Magician(
    string name,
    int hp,
    int mp,
    int power,
    int defence
)
    : Player(
        name,
        "마법사",
        hp,
        mp + 30,
        power,
        defence
    )
{
}

void Magician::attack(Monster* monster)
{
    int damage = power - monster->getDefence();

    if (damage < 1)
    {
        damage = 1;
    }

    monster->setHP(monster->getHP() - damage);

    cout << "[마법사] 파이어볼 발사! -> "
        << monster->getName()
        << "에게 "
        << damage
        << " 데미지!\n";
}

// =====================
// 도적
// =====================

Thief::Thief(
    string name,
    int hp,
    int mp,
    int power,
    int defence
)
    : Player(
        name,
        "도적",
        hp,
        mp,
        power + 30,
        defence
    )
{
}

void Thief::attack(Monster* monster)
{
    int damage = (power - monster->getDefence()) / 5;

    if (damage < 1)
    {
        damage = 1;
    }

    for (int i = 0; i < 5; i++)
    {
        monster->setHP(monster->getHP() - damage);
    }

    cout << "[도적] 단검을 찌른다! -> "
        << monster->getName()
        << "에게 "
        << damage
        << " 데미지! (x5)\n";
}

// =====================
// 궁수
// =====================

Archer::Archer(
    string name,
    int hp,
    int mp,
    int power,
    int defence
)
    : Player(
        name,
        "궁수",
        hp,
        mp,
        power + 30,
        defence
    )
{
}

void Archer::attack(Monster* monster)
{
    int damage = (power - monster->getDefence()) / 3;

    if (damage < 1)
    {
        damage = 1;
    }

    for (int i = 0; i < 3; i++)
    {
        monster->setHP(monster->getHP() - damage);
    }

    cout << "[궁수] 화살을 쏜다! -> "
        << monster->getName()
        << "에게 "
        << damage
        << " 데미지! (x3)\n";
}

// =====================
// 몬스터
// =====================

Monster::Monster(
    string name,
    int hp,
    int power,
    int defence
)
{
    this->name = name;
    this->hp = hp;
    this->power = power;
    this->defence = defence;
}

string Monster::getName()
{
    return name;
}

int Monster::getHP()
{
    return hp;
}

int Monster::getPower()
{
    return power;
}

int Monster::getDefence()
{
    return defence;
}

void Monster::setHP(int newHP)
{
    hp = newHP;

    if (hp < 0)
    {
        hp = 0;
    }
}

void Monster::Attack()
{
    cout << name
        << "이(가) 공격합니다! 공격력: "
        << power
        << endl;
}

// =====================
// 아이템
// =====================

void Item::PrintInfo() const
{
    cout << name
        << " ("
        << price
        << "G)"
        << endl;
}

// =====================
// 몬스터 드랍 아이템 생성 함수
// =====================

Item CreateDropItem(string monsterName)
{
    Item droppedItem;

    if (monsterName == "슬라임")
    {
        droppedItem = {
            "슬라임의 끈적한 젤리",
            30
        };
    }
    else if (monsterName == "고블린")
    {
        droppedItem = {
            "고블린의 단검",
            100
        };
    }
    else
    {
        droppedItem = {
            "알 수 없는 전리품",
            10
        };
    }

    return droppedItem;
}

// =====================
// 포션 레시피
// =====================

PotionRecipe::PotionRecipe(
    string name,
    vector<PotionIngredient> ingredients
)
{
    this->name = name;
    this->ingredients = ingredients;
}

string PotionRecipe::getName()
{
    return name;
}

vector<PotionIngredient> PotionRecipe::getIngredients()
{
    return ingredients;
}

void PotionRecipe::printRecipe()
{
    cout << "-> " << name << " (";

    for (int i = 0; i < ingredients.size(); i++)
    {
        cout << ingredients[i].name
            << " x"
            << ingredients[i].count;

        if (i < ingredients.size() - 1)
        {
            cout << ", ";
        }
    }

    cout << ")" << endl;
}

// =====================
// 포션 제작소
// =====================

void AlchemyWorkshop::AddRecipe(PotionRecipe recipe)
{
    recipes.push_back(recipe);
}

void AlchemyWorkshop::ShowAllRecipes()
{
    cout << "\n=== 전체 레시피 목록 ===\n";

    for (PotionRecipe recipe : recipes)
    {
        recipe.printRecipe();
    }
}

void AlchemyWorkshop::SearchByName(string name)
{
    bool found = false;

    cout << "\n검색한 포션 이름: "
        << name
        << endl;

    for (PotionRecipe recipe : recipes)
    {
        if (recipe.getName() == name)
        {
            recipe.printRecipe();
            found = true;
        }
    }

    if (!found)
    {
        cout << "일치하는 레시피가 없습니다.\n";
    }
}

void AlchemyWorkshop::SearchByIngredient(string ingredient)
{
    bool found = false;
    int count = 0;

    cout << "\n검색한 재료: "
        << ingredient
        << endl;

    for (PotionRecipe recipe : recipes)
    {
        vector<PotionIngredient> ingredients = recipe.getIngredients();

        for (PotionIngredient item : ingredients)
        {
            if (item.name == ingredient)
            {
                recipe.printRecipe();

                found = true;
                count++;

                break;
            }
        }
    }

    if (found)
    {
        cout << "총 "
            << count
            << "개의 레시피를 찾았습니다.\n";
    }
    else
    {
        cout << "해당 재료를 포함한 레시피가 없습니다.\n";
    }
}
