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

 /*Black = 0, Blue = 1,
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

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <stdlib.h>
#include <locale>

using namespace std;

#define PIN 1234
#define MAXBALANCE 5000
#define PRICEEXPRESSO 2.0
#define PRICECAPUTHINO 2.5
#define PRICELATTE 3.0

struct serviceData {
    double balance;
    int cups;
    int auAttempts;
};

int initializationCoffeeMachine(serviceData &balanceAndCups);
void outputGreeting();
void printCountBalansAndCups(serviceData &balanceAndCups);
void printMenu(serviceData &balanceAndCups);

int putBalanceMoney(serviceData &balanceAndCups);

void printMenuCoffee(serviceData &balanceAndCups);
bool isCupsExist(serviceData &balanceAndCups);
void selectCoffee(serviceData &balanceAndCups);
int cookCoffee(serviceData &balanceAndCups, string nameCoffee, double price);
int checkConditionsMakingCoffee(serviceData &balanceAndCups, double price);
bool isEnoughMoney(serviceData &balanceAndCups, double price);
bool isEnoughCups(serviceData &balanceAndCups);
void showProcessCookCoffee(string nameCoffee);

int selectServiceMenu(serviceData &balanceAndCups);
void printServiceMenu(serviceData &balanceAndCups);
void showСurrentBalance(serviceData &balanceAndCups);
void showNumberCupsRemaining(serviceData &balanceAndCups);
void takeMoney(serviceData &balanceAndCups);

void clearDisplay();
int autentification(serviceData &balanceAndCups);
void setColorConsole(int colorText, int background);
void showErrorMessage(string message);
void showSuccessfulMessage(string message);

void changeColour(int colour);
void printTitle();
void printFooter();
int checkIntInputUserNumber(int data, int start, int end);
double checkDoubleInputUserNumber(double data, double startLimit, double endLimit);
int inputUserIntNumber(int value);
double inputUserDoubleNumber(double value);
void blockCoffeeMachine();


int main()
{
    // Это зачем?
    const int LightCyan = 11;
    const int GREEN = 2;
    const int RED = 4;
    const int YELLOW = 14;
    const int WHITE = 15;
    const int BRIGHTBLUE = 94;

    cout.precision(2);
    cout.setf(ios::fixed);

    // The first number - balance
    // The second number - count cups
    // The 3  number - authentication attempts
    serviceData variableValues = { 6.0, 7, 0 };
    int userChoice = 0;

    if (int result = initializationCoffeeMachine(variableValues) != 0) // Checking cups and overflow balance
        return result;

    //outputGreeting(); // пока убрал для заголовка

    while (true) {
        printMenu(variableValues);

        userChoice = inputUserIntNumber(userChoice);
        if (checkIntInputUserNumber(userChoice, 1, 3) != 0) {
            continue;
        }

        if (userChoice == 1)
            putBalanceMoney(variableValues);
        else if (userChoice == 2)
            selectCoffee(variableValues);
        else if (userChoice == 3)
            selectServiceMenu(variableValues);
    }
    return 0;
}

int initializationCoffeeMachine(serviceData &balanceAndCups) {
    if (balanceAndCups.balance >= MAXBALANCE) {                     
        showErrorMessage("Error! The coffee machine cannot accept money.");
        return 1;
    }
    else if (balanceAndCups.cups == 0) {
        showErrorMessage("Error! The coffee machine has run out of cups.");
        return 2;
    }
    return 0;
}


// УБИРАЕМ?
void outputGreeting() {
    changeColour(14);
    cout << endl << "[ * * * ESPRESSO BIANCCI  * * * ]" <<
        endl << "Wonderful palette of coffee aromas" << 
        endl << "[ * * * Enjoy your coffee! * * * ]" << endl;
    changeColour(15);
}

void printMenu(serviceData &balanceAndCups) {
    printTitle();
    printCountBalansAndCups(balanceAndCups);

    changeColour(2); cout << endl << "[ ==> USER'S GUIDE: <== ]"; 
    changeColour(15); cout << endl << "To get our great coffee, select "; changeColour(2); cout << "[ 1 ]"; changeColour(15); cout << " and deposit the required amount.";
    
    // Это я добавил, оформи это красиво)
    cout << endl << "Maximum amount 100 BYN!";
    changeColour(12); cout << endl << "PLEASE NOTE that the device DOES NOT RETURN CHANGE!";
    changeColour(15); cout << endl << "Then press "; changeColour(2); cout << "[ 2 ]"; changeColour(15); cout << " to select the type of coffee.";
    changeColour(15); cout << endl << "For service, press "; changeColour(2); cout << "[ 3 ]" << endl; 
    changeColour(2); cout << endl << "[ 1 ]"; changeColour(15); cout << " Put money." << endl;
    changeColour(2); cout << "[ 2 ]"; changeColour(15); cout << " Select coffee." << endl;
    changeColour(2); cout << "[ 3 ]"; changeColour(15); cout << " Service menu" << endl;
    cout << "Your choice? " << endl;
}

void printTitle() {
    changeColour(14);
    cout << "[= = = = = = = = = = = = = = = =]" << endl;
    cout << "[ * * * ESPRESSO BIANCCI  * * * ]" << endl;
    cout << "[  * TASTE * AROMA * PLEASURE * ]" << endl;
    cout << "[= = = = = = = = = = = = = = = =]" << endl;
    changeColour(15);
}

void printFooter() {  // пока что не используется
    changeColour(11); cout << endl << "UI developed by the team N.Gusak & R.Kaznouski. All rights reserved."; changeColour(15);
}

void printCountBalansAndCups(serviceData &balanceAndCups) {
    changeColour(11);
    cout << "Cups: " << balanceAndCups.cups;
    if (balanceAndCups.balance < 10) {
        cout << "         ";
    }
    else if (balanceAndCups.balance > 10 and balanceAndCups.balance < 100) {
        cout << "        ";
    }
    else if (balanceAndCups.balance > 100) {
        cout << "       ";
    }
    cout << "Balance: " << balanceAndCups.balance << " BYN" << endl;
    changeColour(15);
}

int putBalanceMoney(serviceData &balanceAndCups) {
    clearDisplay();    

    if (isCupsExist(balanceAndCups) == false) {
        return 1;
    }
    
    cout << "Put money: ";
    double changeBalanc = 0;
    changeBalanc = inputUserDoubleNumber(changeBalanc);

    if (checkDoubleInputUserNumber(changeBalanc, 0.01, 100.0) != 0) {
        //showErrorMessage("Error! You have entered incorrect data. The coffee machine accepts notes no more than 100 BYN");
        return 2;
    }
    else {
        balanceAndCups.balance += changeBalanc;
        clearDisplay();
        
        changeColour(10);
        cout << changeBalanc << " BYN has been successfully credited to your account." << endl;
        changeColour(15);
        return 0;
    }

  /*  cin >> changeBalanc;
    if (changeBalanc <= 100.0) {
        
    }
    else {
        showErrorMessage("Error! The coffee machine accepts notes no more than 100 BYN.");
        return 2;
    }*/
}

void clearDisplay() {
    system("cls");
}

bool isCupsExist(serviceData &balanceAndCups) {
    if (balanceAndCups.cups > 0)
        return true;
    else
        showErrorMessage("Error! Sorry, we cannot accept money and fulfill your order because the cups have run out.");
    return false;
}

void showSuccessfulMessage(string message) {
    setColorConsole(10, 0);
    cout << message << endl;
    setColorConsole(15, 0);
}

void showErrorMessage(string message) {
    setColorConsole(12, 0);
    cout << message << endl;
    setColorConsole(15, 0);
}

void selectCoffee(serviceData &balanceAndCups) {
    clearDisplay();
    printTitle();
    int userChoice = 0;
    while (true) {
        printMenuCoffee(balanceAndCups); 

        userChoice = inputUserIntNumber(userChoice);
        if (checkIntInputUserNumber(userChoice, 1, 4) != 0) {
            continue;
        }

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


void printMenuCoffee(serviceData &balanceAndCups) {
    printCountBalansAndCups(balanceAndCups);
    
    cout << endl << "What do you prefer?";
    changeColour(2); cout << endl << "[ 1 ]"; changeColour(15); cout << " If you have a momentary need for caffeine, try our espresso." <<
        endl << "It is a coffee drink characterized by a small volume," <<
        endl << "strong and made from finely ground beans under high water pressure." << endl;
    changeColour(2); cout << endl << "[ 2 ]"; changeColour(15); cout << " If you would like to enjoy a great tasting coffee, choose our cappuccino." <<
        endl << "Espresso coffee with heated frothed milk. A thick layer of thick, creamy foam," <<
        endl << "accompanied by a sweetish warming milk and a rich taste of well-brewed espresso." << endl;
    changeColour(2); cout << endl << "[ 3 ]"; changeColour(15); cout << " If you want a light coffee and creamy taste, try our latte." <<
        endl << "The largest and mildest espresso-based coffee drink." << 
        endl << "Suitable for those who do not like the bright taste of coffee." << endl;
    
    changeColour(2); cout << endl << "[ 1 ]"; changeColour(15); cout << " Expresso - "; changeColour(11); cout << PRICEEXPRESSO << " BYN" << endl;
    changeColour(2); cout << "[ 2 ]"; changeColour(15); cout << " Cappuccino - "; changeColour(11); cout << PRICECAPUTHINO << " BYN" << endl;
    changeColour(2); cout << "[ 3 ]"; changeColour(15); cout << " Latte - "; changeColour(11); cout << PRICELATTE << " BYN" << endl;
    changeColour(2); cout << "[ 4 ]"; changeColour(15); cout << " Back to main menu." << endl;
    changeColour(15);
    cout << "Your choice? " << endl;
}

int cookCoffee(serviceData &balanceAndCups, string nameCoffee, double price) {
    //showProcessCookCoffee(nameCoffee);

    if (int result = checkConditionsMakingCoffee(balanceAndCups, price) != 0)
        return result;

    showProcessCookCoffee(nameCoffee);

    showSuccessfulMessage(nameCoffee + " is ready.");
    balanceAndCups.balance = balanceAndCups.balance - price;
    balanceAndCups.cups = balanceAndCups.cups - 1;
    return 0;
}

void showProcessCookCoffee(string nameCoffee) {
    int i = 0;
    string strProgress = "";
    while (i < 51)
    {
        Sleep(10);  
        clearDisplay();
        cout << "--------------------------------------------------" << std::endl;
        cout << "          Expect your coffee to prepare          " << std::endl;
        cout << "                        " << i*2 <<" %                         " << std::endl;
        cout << strProgress << std::endl;
        cout << "                                                  " << std::endl;
        cout << "                                                  " << std::endl;
        cout << "--------------------------------------------------" << std::endl;
        strProgress = strProgress + "*";
        i++;
    }
    Sleep(1000);
    clearDisplay();
}

int checkConditionsMakingCoffee(serviceData &balanceAndCups, double price) {
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

bool isEnoughMoney(serviceData &balanceAndCups, double price) {
    if (balanceAndCups.balance < price)
        return false;
    return true;
}

bool isEnoughCups(serviceData &balanceAndCups) {
    if (balanceAndCups.cups == 0)
        return false;
    return true;
}

int selectServiceMenu(serviceData &balanceAndCups) {
    int resultAu = autentification(balanceAndCups);
    if (resultAu != 0) {
        return resultAu;
    }
    else
        clearDisplay();

    int userChoice = 0;
    while (true) {
        printServiceMenu(balanceAndCups);

        userChoice = inputUserIntNumber(userChoice);
        if (checkIntInputUserNumber(userChoice, 1, 5) != 0) {
            continue;
        }

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

int autentification(serviceData &balanceAndCups) {
    clearDisplay();

    int userPin = 0;
    cout << "Please, enter your PIN: ";
    cin >> userPin;

    if (userPin == PIN)
        return 0;
    else {
        balanceAndCups.auAttempts++;
        if (balanceAndCups.auAttempts == 3) {
            blockCoffeeMachine();
        }
        clearDisplay();
        showErrorMessage("Error! Your PIN is not valid.");
    }
    return 1;
}

void printServiceMenu(serviceData &balanceAndCups) {
    cout << endl << "To check funds in the bill acceptor, click [ 1 ] " <<
        endl << "To check the number of cups, click [ 2 ] " <<
        endl << "For withdrawing funds from the bill acceptor, click [ 3 ] " <<
        endl << "To switch off the coffee machine, click [ 4 ]" <<
        endl << "To exit the service menu, click [ 5 ]" << endl;

    cout << endl << "[ 1 ] Check funds." << endl;
    cout << "[ 2 ] Check the number of cups." << endl;
    cout << "[ 3 ] Withdrawal of proceeds." << endl;
    cout << "[ 4 ] Switch of coffee machine." << endl;
    cout << "[ 5 ] Exit." << endl;
    cout << "Your choice? ";
}

void showСurrentBalance(serviceData &balanceAndCups) {
    cout << endl << "Balance: " << balanceAndCups.balance << endl;
}

void showNumberCupsRemaining(serviceData &balanceAndCups) {
    cout << endl << "Cups remaining: " << balanceAndCups.cups << endl;
}

void takeMoney(serviceData &balanceAndCups) {
    cout << endl << "Take money in the amount of: " << balanceAndCups.balance << " BYN." << endl;
    balanceAndCups.balance = 0;
}

void changeColour(int colour) {
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, colour);
}

void setColorConsole(int colorText, int background) {
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleHandle, colorText | background);
}

int checkIntInputUserNumber(int data, int startLimit, int endLimit) {
    // If user input incorrect value if cin function
    if (!cin)
    {
        cin.clear(); // Check error input int
        cin.ignore(10000, '\n'); // Clea buffer
    }
    // Check input limit
    if (data >= startLimit and data <= endLimit) {
         return 0;            
    }
    clearDisplay();
    showErrorMessage("Error! You have entered incorrect data. Read the instructions carefully.");
    return 1;
}

int inputUserIntNumber(int value) {
    cin >> value;
    return value;
}

double checkDoubleInputUserNumber(double data, double startLimit, double endLimit) {
    // If user input incorrect value if cin function
    if (!cin)
    {
        cin.clear(); // Check error input int
        cin.ignore(10000, '\n'); // Clea buffer
    }
    // Check input limit
    if (data >= startLimit and data <= endLimit) {
        return 0;
    }
    clearDisplay();
    showErrorMessage("Error! You have entered incorrect data. Read the instructions carefully.");
    return 1;
}

double inputUserDoubleNumber(double value) {
    cin >> value;
    return value;
}

// Нужно офрмить блокировку
void blockCoffeeMachine()
{
    clearDisplay();
    cout << "blockCoffeeMachine";
    while (true) { };
}