//main.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Monster.h"

using namespace std;

// 포션 개수 설정 함수
void setPotion(int count, int* p_HPPotion, int* p_MPPotion)
{
    *p_HPPotion = count;
    *p_MPPotion = count;
}

int main()
{
    srand((unsigned int)time(0));

    string name;

    const int SIZE = 4;
    int stat[SIZE] = { 0 };

    int choice;

    vector<Item> inventory;

    cout << "============================\n";
    cout << "[ 던전 탈출 텍스트 RPG ]\n";
    cout << "============================\n";

    cout << "용사의 이름을 입력해주세요: ";
    cin >> name;

    while (true)
    {
        cout << "HP와 MP를 입력해주세요: ";
        cin >> stat[0] >> stat[1];

        if (stat[0] >= 50 && stat[1] >= 50)
        {
            break;
        }

        cout << "HP나 MP의 값이 너무 낮습니다. 다시 입력해주세요.\n";
    }

    while (true)
    {
        cout << "공격력과 방어력을 입력해주세요: ";
        cin >> stat[2] >> stat[3];

        if (stat[2] > 0 && stat[3] > 0)
        {
            break;
        }

        cout << "공격력이나 방어력이 너무 작습니다. 다시 입력해주세요.\n";
    }

    printStatus(name, stat);

    int hppotion = 0;
    int mppotion = 0;

    setPotion(5, &hppotion, &mppotion);

    bool isGamestart = false;

    cout << "\n* HP 포션 5개, MP 포션 5개가 지급되었습니다.\n";

    while (!isGamestart)
    {
        cout << "\n< 캐릭터 강화 >\n";

        cout << "1. HP UP       2. MP UP        3. 공격력 2배\n";
        cout << "4. 방어력 2배   5. 현재 능력치  0. 게임시작\n";

        cout << "번호를 선택하세요: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (hppotion > 0)
            {
                stat[0] += 20;
                hppotion--;

                cout << "* HP 20 증가! (남은 HP 포션: "
                    << hppotion
                    << ")\n";
            }
            else
            {
                cout << "* HP 포션이 부족합니다!\n";
            }

            break;

        case 2:
            if (mppotion > 0)
            {
                stat[1] += 20;
                mppotion--;

                cout << "* MP 20 증가! (남은 MP 포션: "
                    << mppotion
                    << ")\n";
            }
            else
            {
                cout << "* MP 포션이 부족합니다!\n";
            }

            break;

        case 3:
            stat[2] *= 2;
            cout << "* 공격력이 2배 증가했습니다!\n";
            break;

        case 4:
            stat[3] *= 2;
            cout << "* 방어력이 2배 증가했습니다!\n";
            break;

        case 5:
            printStatus(name, stat);
            break;

        case 0:
            cout << "\n게임을 시작합니다!\n";
            isGamestart = true;
            break;

        default:
            cout << "잘못된 입력입니다.\n";
        }
    }

    cout << "\n최종 능력치입니다.";
    printStatus(name, stat);

    cout << "\n< 전직 시스템 >\n";
    cout << name << "님, 직업을 선택해주세요!\n";
    cout << "1. 전사  2. 마법사  3. 도적  4. 궁수\n";

    cout << "선택: ";
    cin >> choice;

    Player* player = nullptr;

    if (choice == 1)
    {
        cout << "* 전사로 전직하였습니다. (공격력 +30)\n";

        player = new Warrior(
            name,
            stat[0],
            stat[1],
            stat[2],
            stat[3]
        );
    }
    else if (choice == 2)
    {
        cout << "* 마법사로 전직하였습니다. (MP +30)\n";

        player = new Magician(
            name,
            stat[0],
            stat[1],
            stat[2],
            stat[3]
        );
    }
    else if (choice == 3)
    {
        cout << "* 도적으로 전직하였습니다. (공격력 +30)\n";

        player = new Thief(
            name,
            stat[0],
            stat[1],
            stat[2],
            stat[3]
        );
    }
    else if (choice == 4)
    {
        cout << "* 궁수로 전직하였습니다. (공격력 +30)\n";

        player = new Archer(
            name,
            stat[0],
            stat[1],
            stat[2],
            stat[3]
        );
    }
    else
    {
        cout << "잘못된 선택입니다.\n";
        return 0;
    }

    player->printPlayerStatus();

    // 전투 중 사용할 포션 지급
    inventory.push_back({ "HP포션", 50 });
    inventory.push_back({ "MP포션", 50 });

    AlchemyWorkshop workshop;

    workshop.AddRecipe(
        PotionRecipe(
            "HP포션",
            {
                {"허브", 1},
                {"맑은물", 1}
            }
        )
    );

    workshop.AddRecipe(
        PotionRecipe(
            "MP포션",
            {
                {"베리", 1},
                {"맑은물", 1}
            }
        )
    );

    workshop.AddRecipe(
        PotionRecipe(
            "스태미나포션",
            {
                {"허브", 1},
                {"베리", 1}
            }
        )
    );

    while (true)
    {
        cout << "\n--- 메인 메뉴 ---\n";

        cout << "1. 던전 입장\n";
        cout << "2. 인벤토리 확인\n";
        cout << "3. 포션 제작소\n";
        cout << "0. 게임 종료\n";

        cout << "\n선택: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\n던전에 입장했습니다!\n";

            Monster monster("", 0, 0, 0);

            int randomMonster = rand() % 2;

            if (randomMonster == 0)
            {
                monster = Monster(
                    "슬라임",
                    100,
                    20,
                    10
                );
            }
            else
            {
                monster = Monster(
                    "고블린",
                    150,
                    30,
                    15
                );
            }

            cout << "\n[전투 시작] "
                << player->getName()
                << "("
                << player->getJob()
                << ") vs "
                << monster.getName()
                << "\n";

            while (player->getHP() > 0 && monster.getHP() > 0)
            {
                cout << "\n--- 플레이어 턴 ---\n";
                cout << "1. 공격\n";
                cout << "2. 아이템 사용\n";

                cout << "선택: ";
                cin >> choice;

                if (choice == 1)
                {
                    player->attack(&monster);

                    cout << monster.getName()
                        << " 남은 HP: "
                        << monster.getHP()
                        << endl;
                }
                else if (choice == 2)
                {
                    cout << "\n[ 인벤토리 ]\n";

                    if (inventory.empty())
                    {
                        cout << "인벤토리가 비어 있습니다.\n";
                    }
                    else
                    {
                        for (int i = 0; i < inventory.size(); i++)
                        {
                            cout << i + 1 << ". ";
                            inventory[i].PrintInfo();
                        }

                        int itemChoice;

                        cout << "사용할 아이템 번호: ";
                        cin >> itemChoice;

                        itemChoice--;

                        if (itemChoice >= 0 && itemChoice < inventory.size())
                        {
                            Item selectedItem = inventory[itemChoice];

                            if (selectedItem.name == "HP포션")
                            {
                                int beforeHP = player->getHP();

                                player->setHP(
                                    player->getHP() + selectedItem.price
                                );

                                cout << "* HP포션 사용! HP "
                                    << beforeHP
                                    << " -> "
                                    << player->getHP()
                                    << endl;

                                inventory.erase(
                                    inventory.begin() + itemChoice
                                );
                            }
                            else if (selectedItem.name == "MP포션")
                            {
                                int beforeMP = player->getMP();

                                player->setMP(
                                    player->getMP() + selectedItem.price
                                );

                                cout << "* MP포션 사용! MP "
                                    << beforeMP
                                    << " -> "
                                    << player->getMP()
                                    << endl;

                                inventory.erase(
                                    inventory.begin() + itemChoice
                                );
                            }
                            else
                            {
                                cout << "사용할 수 없는 아이템입니다.\n";
                            }
                        }
                        else
                        {
                            cout << "잘못된 아이템 번호입니다.\n";
                        }
                    }
                }
                else
                {
                    cout << "잘못된 입력입니다.\n";
                    continue;
                }

                // =====================
                // 몬스터 처치 체크 + 아이템 획득
                // =====================

                if (monster.getHP() <= 0)
                {
                    cout << "\n"
                        << monster.getName()
                        << "을(를) 처치했습니다!\n";

                    player->gainExp(30);

                    Item droppedItem =
                        CreateDropItem(monster.getName());

                    inventory.push_back(droppedItem);

                    cout << "-> "
                        << droppedItem.name
                        << " 획득!\n";

                    cout << "-> 인벤토리에 저장되었습니다.\n";

                    player->printPlayerStatus();

                    break;
                }

                // =====================
                // 몬스터 턴
                // =====================

                cout << "\n--- 몬스터 턴 ---\n";

                int monsterDamage =
                    monster.getPower() - player->getDefence();

                if (monsterDamage < 1)
                {
                    monsterDamage = 1;
                }

                int beforePlayerHP = player->getHP();

                player->setHP(
                    player->getHP() - monsterDamage
                );

                cout << monster.getName()
                    << "의 공격!\n";

                cout << player->getName()
                    << "에게 "
                    << monsterDamage
                    << " 데미지!\n";

                cout << player->getName()
                    << " HP: "
                    << beforePlayerHP
                    << " -> "
                    << player->getHP()
                    << endl;

                if (player->getHP() <= 0)
                {
                    cout << "\n전투 패배...\n";
                    cout << "게임 오버!\n";
                    break;
                }
            }
        }
        else if (choice == 2)
        {
            cout << "\n[ 인벤토리 ("
                << inventory.size()
                << "/10) ]\n";

            if (inventory.empty())
            {
                cout << "인벤토리가 비어 있습니다.\n";
            }
            else
            {
                int index = 1;

                for (const Item& item : inventory)
                {
                    cout << index << ". ";

                    item.PrintInfo();

                    index++;
                }
            }
        }
        else if (choice == 3)
        {
            int potionChoice;

            while (true)
            {
                cout << "\n=== 포션 제작소 ===\n";
                cout << "1. 전체 레시피 보기\n";
                cout << "2. 포션 이름으로 검색\n";
                cout << "3. 재료로 검색\n";
                cout << "0. 돌아가기\n";

                cout << "\n선택: ";
                cin >> potionChoice;

                if (potionChoice == 1)
                {
                    workshop.ShowAllRecipes();
                }
                else if (potionChoice == 2)
                {
                    string potionName;

                    cout << "검색할 포션 이름: ";
                    cin >> potionName;

                    workshop.SearchByName(potionName);
                }
                else if (potionChoice == 3)
                {
                    string ingredient;

                    cout << "검색할 재료: ";
                    cin >> ingredient;

                    workshop.SearchByIngredient(ingredient);
                }
                else if (potionChoice == 0)
                {
                    break;
                }
                else
                {
                    cout << "잘못된 입력입니다.\n";
                }
            }
        }
        else if (choice == 0)
        {
            cout << "\n게임 종료!\n";
            break;
        }
        else
        {
            cout << "잘못된 입력입니다.\n";
        }
    }

    delete player;
// 포인터를 사용하지 않으면 매개변수만 넘기면
// 값이 복사되어서 전달된다
// 따라서 함수 내부에서 값을 변경해도
// 원본 변수는 바뀌지않고
// 포인터를 사용하면 변수의 주소를 전달되서
// 원본 값을 직접 수정할 수 있다.
    return 0;
}
