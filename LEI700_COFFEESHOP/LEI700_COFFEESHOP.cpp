 /*
 COFFEESHOP. Компания EspressoBiancci заказывает разработку системы управления меню для своего кофейного аппарата LEI700. 
Аппарат готовит кофе трех видов: Espresso, Cappuccino, Latte
После ввода PIN:
* Просмотр баланса
* Просмотр кол-ва оставшихся пустых стаканчиков
* Изъятие выручки 
Примечания:
* Программно-аппаратный комплекс LEI700 поддерживает языки: Assembler, C, C++.     
* PIN - специальный код из 4 цифр, предоставляемый EspressoBiancci представителям сервиса под роспись.
 
+ 1. Разделитесь по парам
- 2. Договоритесь с напарником о времени митинга в скайпе  (1-2 раза в неделю) и явно запишите его
2. Работая в паре, обсудите проект. Помните, что хороший код - надежный, продумайте, какие исключительные ситуации могут возникнуть при заказе кофе и работе сотрудников сервиса
3. Критически важно на этом этапе задавать вопросы, иначе, по статистике, у вас есть 75% сделать работающий проект и услышать знаменитую фразу заказчика: "А я хотел не это"
4. Разработайте UI системы (точный вид меню)
5. Утвердите UI у заказчика
6. Договоритесь, кто какие функции пишет в проекте
7. Начинайте разработку. Используйте метод пошаговой разработки, начните с меню (пока функции, вызываемые из меню, будут заглушками), т.е. вы сделаете прототип системы
8. Утвердите прототип у своего ментора
9. Теперь постепенно наращивайте функциональность своего проекта, сопровождая этот процесс тестированием
10. Проведите crash-test системы, особенно чатей, написанных напарников (чужие ошибки ищутся лучше). Подготовьтесь к DEMO проекта.
 */

#include <iostream>
using namespace std;

#define PIN 1234
#define MAXBALANCE 5000

int initializationCoffeeMachine(double balance, int cups, int amountCoffee, int amountMilk, int amountWate, int amountSugar);
void outputGreeting();
void printMainMenu();
void cookEspresso();
void cookCappuccino();
void cookLatte();
void printServiceMenu();
void autentification();
int howMuchSugarUse();
int inputAmountSugar();

int main()
{
    int userChoice = 0;
    double balance = 100.0;
    int cups = 50;
    int amountCoffee = 1000;    // gramme
    int amountMilk = 1000;      // milliliters
    int amountWater = 10000;    // milliliters
    int amountSugar = 1000;     // gramme

    if (int result = initializationCoffeeMachine(balance, cups, amountCoffee, amountMilk, amountWater, amountSugar) != 0)
        return result;

    void outputGreeting();

    while (true) {
        printMainMenu();
        cin >> userChoice;
        if (userChoice == 1)
            cookEspresso();
        else if (userChoice == 2)
            cookCappuccino();
        else if (userChoice == 3)
            cookLatte();
        else if (userChoice == 4)
            autentification();
    }
    return 0;
}

int initializationCoffeeMachine(double balance, int cups, int amountCoffee, int amountMilk, int amountWate, int amountSugar) {
    if (balance >= MAXBALANCE)
        return 1;
    else if (cups == 0)
        return 2;
    else if (amountCoffee == 0)
        return 3;
    else if (amountMilk == 0)
        return 4;
    else if (amountWate == 0)
        return 5;
    else if (amountSugar == 0)
        return 6;
    else return 0;
}

void outputGreeting() {
    cout << "Welcome to the EspressoBiancci coffee machine." << endl;
}

void printMainMenu() {
    cout << endl << "1. Espresso" << endl;
    cout << "2. Cappuccino" << endl;
    cout << "3. Latte" << endl;
    cout << "4. Service" << endl;
    cout << "Your choice? ";
}

void cookEspresso() {
    cout << "Espresso is ready." << endl;
}

void cookCappuccino() {
    cout << "Cappuccino is ready" << endl;
}

void cookLatte() {
    cout << "Cappuccino is ready" << endl;
}

void printServiceMenu() {
    cout << endl << "Service menu LEI700" << endl;
    cout << "1. Cash transactions" << endl;
    cout << "2. View the amount of ingredients remaining" << endl;

    cout << "5. Software version" << endl;

    cout << "Your choice? ";
}

void autentification() {
    int pin = 0;
    cout << "Please, enter your PIN: ";
    cin >> pin;
    if (pin == PIN)
        printServiceMenu();
    else
        cout << "Your PIN is not valid." << endl;
}

int howMuchSugarUse() {
    int sugar = 0;
    cout << "Do you want to add sugar? ";
    cin >> sugar;
    if (sugar > 0)
        inputAmountSugar();
    return 0;
}

int inputAmountSugar() {
    int spoons = 0;
    cout << "How much spoons of sugar do you want? ";
    cin >> spoons;
    if (spoons == 1)
        cout << "One spoon of sugar.";
    else if (spoons == 2)
        cout << "Two spoons of sugar.";
    return 0;
}
