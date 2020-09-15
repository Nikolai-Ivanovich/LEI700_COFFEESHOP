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
#include <cstdlib>
#include <Windows.h>
#include <string>

using namespace std;

#define PIN 1234
#define MAXBALANCE 5000
#define PRICEEXPRESSO 2.0
#define PRICECAPUTHINO 2.5
#define PRICELATTE 3.0

int initializationCoffeeMachine(double balanceAndCups[]);
void outputGreeting();
void printCountBalansAndCups(double balanceAndCups[]);
void printMenu(double balanceAndCups[]);

int putBalanceMoney(double balanceAndCups[]);

void printMenuCoffee(double balanceAndCups[]);
bool isCupsExist(double balanceAndCups[]);
void selectCoffee(double balanceAndCups[]);
int cookCoffee(double balanceAndCups[], string nameCoffee, double price);
int checkСonditionsMakingCoffee(double balanceAndCups[], double price);
bool isEnoughMoney(double balanceAndCups[], double price);
bool isEnoughCups(double balanceAndCups[]);
void showProcesCookCoffee(string nameCoffee);

int selectServiceMenu(double balanceAndCups[]);
void printServiceMenu(double balanceAndCups[]);
void showСurrentBalance(double balanceAndCups[]);
void showNumberCupsRemaining(double balanceAndCups[]);
void takeMoney(double balanceAndCups[]);

void clearDisplay();
bool autentification(double balanceAndCups[]);
void setColorConsole(int colorText, int background);
void showErrorMessage(string message);
void showSuccessfulMessage(string message);

int main()
{   
    // The first number - balance
    // The second number - count cups
    // The 3  number number - authentication attempts
    double balanceAndCups[] = { 6.0, 7.0 , 0.0};
    int userChoice = 0;

    // Checking all ingredients are present and overflow balance
    if (int result = initializationCoffeeMachine(balanceAndCups) != 0)
        return result;
    
    outputGreeting();

    while (true) {
        printMenu(balanceAndCups);
        cin >> userChoice;
        if (userChoice == 1)
            putBalanceMoney(balanceAndCups);
        else if (userChoice == 2)
            selectCoffee(balanceAndCups);
        else if (userChoice == 3)
            selectServiceMenu(balanceAndCups);
    }
    return 0;
}

int selectServiceMenu(double balanceAndCups[]) {
    if (autentification(balanceAndCups) == false) {
        return 1;
    }
    else
        clearDisplay();


    
    int userChoice = 0;
    while (true) {
        printServiceMenu(balanceAndCups);
        cin >> userChoice;
        if (userChoice == 1) {
            clearDisplay();
            showСurrentBalance(balanceAndCups);
        }
        else if (userChoice == 2) {
            clearDisplay();
            showNumberCupsRemaining(balanceAndCups);
        }
        else if (userChoice == 3) {
            clearDisplay();
            takeMoney(balanceAndCups);
        }
        else if (userChoice == 4) {
            clearDisplay();
            exit(0);
        }
        else if (userChoice == 5) {
            clearDisplay();
            break;
        }
    }
    return 0;

}

void showСurrentBalance(double balanceAndCups[]) {
    cout << endl << "Balance: "<< balanceAndCups[0] << endl;
}

void showNumberCupsRemaining(double balanceAndCups[]) {
    cout << endl << "Cups remaining: " << balanceAndCups[1] << endl;
}

void takeMoney(double balanceAndCups[]) {
    cout << endl << "Take money in the amount of: " << balanceAndCups[0] << " BYN." << endl;
    balanceAndCups[0] = 0;
}

void printServiceMenu(double balanceAndCups[]) {
    //Нужно изменить!!!!
    cout << endl << "INSTRUCTIONS: To select coffee, first press 1 and deposit money," <<
        "then press 2 to select the type of coffee. For service, press 3." << endl;

    cout << endl << "1. Show balance." << endl;
    cout << "2. View the number of cups remaining" << endl;
    cout << "3. Pick up the proceeds." << endl;
    cout << "4. Shutdown." << endl;
    cout << "5. Back." << endl;
    cout << "Your choice? ";
}

bool isCupsExist(double balanceAndCups[]) {
    if (balanceAndCups[1] > 0)
        return true;
    else
        showErrorMessage("Error! Sorry, we cannot accept money and fulfill your order because the cups have run out.");
    return false;
}

void clearDisplay() {
    system("cls");
}
    
int putBalanceMoney(double balanceAndCups[]) {
    clearDisplay();

    if (isCupsExist(balanceAndCups) == false) {
        return 1;
    }

    double changeBalanc = 0;
    cout << "Put money: " ;
    cin >> changeBalanc;
    if (changeBalanc <= 100.0) {
        balanceAndCups[0] += changeBalanc;
        clearDisplay();
        showSuccessfulMessage(to_string(changeBalanc) + " BYN has been successfully credited to your account.");
        return 0;
    }
    else {
        showErrorMessage("The coffee machine accepts notes no more than 100 BYN.");
        return 2;
    }

}


        /*Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGray = 7,
        & nbsp;DarkGray = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        Yellow = 14,
        White = 15*/
void setColorConsole(int colorText, int background) {
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleHandle, colorText | background);
}

void showErrorMessage(string message) {
    setColorConsole(12, 0);
    cout << message << endl;
    setColorConsole(15, 0);
}

void showSuccessfulMessage(string message) {
    setColorConsole(10, 0);
    cout << message << endl;
    setColorConsole(15, 0);
}

void selectCoffee(double balanceAndCups[]) {
    clearDisplay();
    int userChoice = 0;
    while (true) {
        printMenuCoffee(balanceAndCups);
        cin >> userChoice;
        if (userChoice == 1) {
            clearDisplay();
            cookCoffee(balanceAndCups, "Expresso", PRICEEXPRESSO);
        }
        else if (userChoice == 2) {
            clearDisplay();
            cookCoffee(balanceAndCups, "Cappuccino", PRICECAPUTHINO);
        }
        else if (userChoice == 3) {
            clearDisplay();
            cookCoffee(balanceAndCups, "Latte", PRICELATTE);
        }
        else if (userChoice == 4) {
            clearDisplay();
            break;
        }
    }
    
}

void printMenuCoffee(double balanceAndCups[]) {
    printCountBalansAndCups(balanceAndCups);
    //Нужно изменить!!!!
    cout << endl << "INSTRUCTIONS: To select coffee, first press 1 and deposit money," <<   
        "then press 2 to select the type of coffee. For service, press 3." << endl;

    cout << endl << "1. Expresso - " << PRICEEXPRESSO << " BYN" << endl;
    cout << "2. Cappuccino - " << PRICECAPUTHINO << " BYN" << endl;
    cout << "3. Latte - " << PRICELATTE << " BYN" << endl;
    cout << "4. Back." << endl;
    cout << "Your choice? ";
}

int initializationCoffeeMachine(double balanceAndCups[]) {
    if (balanceAndCups[0] >= MAXBALANCE) {
        showErrorMessage("Error! The coffee machine cannot accept money.");
        return 1;
    }
    else if (balanceAndCups[1] == 0) {
        showErrorMessage("Error! The coffee machine cannot accept money.");
        return 2;
    }
    return 0;
}

void outputGreeting() {
    cout << "Welcome to the EspressoBiancci coffee machine." << endl;
}

void printMenu(double balanceAndCups[]) {
    printCountBalansAndCups(balanceAndCups);

    cout << endl << "INSTRUCTIONS: To select coffee, first press 1 and deposit money," <<
        "then press 2 to select the type of coffee. For service, press 3." << endl;
    
    cout << endl << "1. Put money." << endl;
    cout << "2. Select coffee." << endl;
    cout << "3. Service menu" << endl;
    cout << "Your choice? ";
}

void printCountBalansAndCups(double balanceAndCups[]) {
    cout << endl << "Balance: " << balanceAndCups[0] << endl;
    cout << "Cups: " << balanceAndCups[1] << endl;
}

int cookCoffee(double balanceAndCups[], string nameCoffee, double price) {
    showProcesCookCoffee(nameCoffee);

    if (int result = checkСonditionsMakingCoffee(balanceAndCups, price) != 0)
        return result;

    showProcesCookCoffee(nameCoffee);

    showSuccessfulMessage(nameCoffee + " is ready.");
    balanceAndCups[0] = balanceAndCups[0] - price;
    balanceAndCups[1] = balanceAndCups[1] - 1;
    return 0;
}

void showProcesCookCoffee(string nameCoffee) {
    
}

int checkСonditionsMakingCoffee(double balanceAndCups[], double price) {
    if (isEnoughMoney(balanceAndCups, price) == false) {
        showErrorMessage("Error! Not enough money to order.");
        return 1;
    }
    if (isEnoughCups(balanceAndCups) == false) {
        showErrorMessage("Error! We cannot fulfill your order because we ran out of cups.");
        return 2;
    } 
    return 0;
}

bool isEnoughMoney(double balanceAndCups[], double price) {
    if (balanceAndCups[0] < price)
        return false;
    return true;
}

bool isEnoughCups(double balanceAndCups[]) {
    if (balanceAndCups[1] == 0)
        return false;
    return true;
}



bool autentification(double balanceAndCups[]) {
    clearDisplay();
    if (balanceAndCups[2] >2) {
        showErrorMessage("The coffee machine is locked!");
        return false;
    }

    int pin = 0;
    cout << "Please, enter your PIN: ";
    cin >> pin;
    if (pin == PIN)
        return true;
    else {
        balanceAndCups[2]++;
        showErrorMessage("Error! Your PIN is not valid.");
    }
    return false;
}
