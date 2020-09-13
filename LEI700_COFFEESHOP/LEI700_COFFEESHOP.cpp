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
 
1. Разделитесь по парам
2. Договоритесь с напарником о времени митинга в скайпе  (1-2 раза в неделю) и явно запишите его
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

void printMenu();
void cookEspresso();
void cookCappuccino();
void cookLatte();
void openServiceMenu(); 
void autentification();
int amtSugar();
int numbOfSpoons();

int main()
{
    int choice = 0;
    double balance = 100.0;
    int cups = 50;
    int amountCoffee = 1000; //gramme
    int amountMilk = 1000;  //milliliters
    int amountWater = 10000;    //milliliters
    int amountSugar = 1000; //gramme

    cout << "Hello! Please select coffee." << endl;

    while (true) {
        printMenu();
        cin >> choice;
        if (choice == 1)
            cookEspresso();
        else if (choice == 2)
            cookCappuccino();
        else if (choice == 3)
            cookLatte();
        else if (choice == 4)
            autentification();
    }
    return 0;
}

void printMenu() {
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

void openServiceMenu() {
    cout << "Service is open." << endl;
}

void autentification() {
    int pin = 0;
    cout << "Please, enter your PIN: ";
    cin >> pin;
    if (pin == PIN)
        openServiceMenu();
    else
        cout << "Your PIN is not valid." << endl;
}

int amtSugar() {
    int sugar = 0;
    cout << "Do you want to add sugar? ";
    cin >> sugar;
    if (sugar > 0)
        numbOfSpoons();
    return 0;
}

int numbOfSpoons() {
    int spoons = 0;
    cout << "How much spoons of sugar do you want? ";
    cin >> spoons;
    if (spoons == 1)
        cout << "One spoon of sugar.";
    else if (spoons == 2)
        cout << "Two spoons of sugar.";
}
