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

int initializationCoffeeMachine(serviceData &variableValues);
void outputGreeting();
void printCountBalansAndCups(serviceData &variableValues);
void printMenu(serviceData &variableValues);

int putBalanceMoney(serviceData &variableValues);

void printMenuCoffee(serviceData &variableValues);
bool isCupsExist(serviceData &variableValues);
void selectCoffee(serviceData &variableValues);
int cookCoffee(serviceData &variableValues, string nameCoffee, double price);
int checkConditionsMakingCoffee(serviceData &variableValues, double price);
bool isEnoughMoney(serviceData &variableValues, double price);
bool isEnoughCups(serviceData &variableValues);
void showProcessCookCoffee(string nameCoffee);

int selectServiceMenu(serviceData &variableValues);
void printServiceMenu(serviceData &variableValues);
void showСurrentBalance(serviceData &variableValues);
void showNumberCupsRemaining(serviceData &variableValues);
void takeMoney(serviceData &variableValues);

void clearDisplay();
int autentification(serviceData &variableValues);
void setColorConsole(int colorText, int background);
void showErrorMessage(string message);
void showSuccessfulMessage(string message);

void changeColour(int colour);
void printTitle();
void printFooter();
int inputUserIntNumber(int value);
int checkIntInputUserNumber(int data, int start, int end);
double inputUserDoubleNumber(double value);
double checkDoubleInputUserNumber(double data, double startLimit, double endLimit);
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

int initializationCoffeeMachine(serviceData &variableValues) {
    if (variableValues.balance >= MAXBALANCE) {                     
        showErrorMessage("Error! The coffee machine cannot accept money.");
        return 1;
    }
    else if (variableValues.cups == 0) {
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

void printMenu(serviceData &variableValues) {
    printTitle();
    printCountBalansAndCups(variableValues);

    changeColour(2); cout << endl << "[ ==> USER'S GUIDE: <== ]"; 
    changeColour(15); cout << endl << "To get our great coffee, select "; changeColour(2); cout << "[ 1 ]"; changeColour(15); cout << " and deposit the required amount.";
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

// Нежалательно записывать такие несколько команд в одной строке, нужно разбивать с новой строки после каждой точки с запятой
// Мне кажется лучше оформить на примере функции showErrorMessage() во всей программе
// Так код будет симпатичнее
/*
    Вместо строки- changeColour(11); cout << endl << "UI developed by the team N.Gusak & R.Kaznouski. All rights reserved."; changeColour(15);

    Пишем и используем функцию:
    void showMessageGreanColor(string text) {
        changeColour(11);
        cout << endl << "UI developed by the team N.Gusak & R.Kaznouski. All rights reserved.";
        changeColour(15);
    }

    А в вызове:
    showMessageGreanColor("UI developed by the team N.Gusak & R.Kaznouski. All rights reserved.");
*/
void printFooter() {  // пока что не используется
    changeColour(11); cout << endl << "UI developed by the team N.Gusak & R.Kaznouski. All rights reserved."; changeColour(15);
}

void printCountBalansAndCups(serviceData &variableValues) {
    changeColour(11);
    cout << "Cups: " << variableValues.cups;
    if (variableValues.balance < 10) {
        cout << "         ";
    }
    else if (variableValues.balance > 10 and variableValues.balance < 100) {
        cout << "        ";
    }
    else if (variableValues.balance > 100) {
        cout << "       ";
    }
    cout << "Balance: " << variableValues.balance << " BYN" << endl;
    changeColour(15);
}

int putBalanceMoney(serviceData &variableValues) {
    clearDisplay();    

    if (isCupsExist(variableValues) == false) {
        return 1;
    }
    
    cout << "Put money: ";
    double changeBalanc = 0;
    changeBalanc = inputUserDoubleNumber(changeBalanc);

    if (checkDoubleInputUserNumber(changeBalanc, 0.01, 100.0) != 0) {
        showErrorMessage("The coffee machine accepts notes no more than 100 BYN");
        return 2;
    }
    else {
        variableValues.balance += changeBalanc;
        clearDisplay();
        
        changeColour(10);
        cout << changeBalanc << " BYN has been successfully credited to your account." << endl;
        changeColour(15);
        return 0;
    }
}

void clearDisplay() {
    system("cls");
}

bool isCupsExist(serviceData &variableValues) {
    if (variableValues.cups > 0)
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

void selectCoffee(serviceData &variableValues) {
    clearDisplay();
    printTitle();
    int userChoice = 0;

    while (true) {
        printMenuCoffee(variableValues); 

        userChoice = inputUserIntNumber(userChoice);
        if (checkIntInputUserNumber(userChoice, 1, 4) != 0) {
            continue;
        }

        if (userChoice == 1) 
            cookCoffee(variableValues, "Expresso", PRICEEXPRESSO);
        else if (userChoice == 2)
            cookCoffee(variableValues, "Cappuccino", PRICECAPUTHINO);
        else if (userChoice == 3)
            cookCoffee(variableValues, "Latte", PRICELATTE);
        else if (userChoice == 4) {
            break;
        }
    }
    clearDisplay();
}

void printMenuCoffee(serviceData &variableValues) {
    printCountBalansAndCups(variableValues);
    
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

int cookCoffee(serviceData &variableValues, string nameCoffee, double price) {
    clearDisplay();

    if (int result = checkConditionsMakingCoffee(variableValues, price) != 0)
        return result;

    showProcessCookCoffee(nameCoffee);

    // Здесь можно написать красивше, мол ваше кофе готово - возьмите его
    showSuccessfulMessage(nameCoffee + " is ready.");
    variableValues.balance = variableValues.balance - price;
    variableValues.cups = variableValues.cups - 1;
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

int checkConditionsMakingCoffee(serviceData &variableValues, double price) {
    if (isEnoughMoney(variableValues, price) == false) {
        showErrorMessage("Error! Not enough money to order.");
        return 1;
    }
    if (isEnoughCups(variableValues) == false) {
        showErrorMessage("Error! We cannot fulfill your order because we ran out of cups.");
        return 2;
    }
    return 0;
}

bool isEnoughMoney(serviceData &variableValues, double price) {
    if (variableValues.balance < price)
        return false;
    return true;
}

bool isEnoughCups(serviceData &variableValues) {
    if (variableValues.cups == 0)
        return false;
    return true;
}

int selectServiceMenu(serviceData &variableValues) {
    int resultAu = autentification(variableValues);
    if (resultAu != 0) {
        return resultAu;
    }
    else
        clearDisplay();

    int userChoice = 0;
    while (true) {
        printServiceMenu(variableValues);

        userChoice = inputUserIntNumber(userChoice);
        if (checkIntInputUserNumber(userChoice, 1, 5) != 0) {
            continue;
        }

        if (userChoice == 1)
            showСurrentBalance(variableValues);
        else if (userChoice == 2)
            showNumberCupsRemaining(variableValues);
        else if (userChoice == 3)
            takeMoney(variableValues);
        else if (userChoice == 4) {
            clearDisplay();
            exit(0);
        }
        else if (userChoice == 5)
            break;
    }
    clearDisplay();
    return 0;
}

int autentification(serviceData &variableValues) {
    clearDisplay();

    int userPin = 0;
    cout << "Please, enter your PIN: ";
    cin >> userPin;

    if (userPin == PIN)
        return 0;
    else {
        variableValues.auAttempts++;
        if (variableValues.auAttempts == 3) {
            blockCoffeeMachine();
        }
        clearDisplay();
        showErrorMessage("Error! Your PIN is not valid.");
    }
    return 1;
}

void printServiceMenu(serviceData &variableValues) {
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

void showСurrentBalance(serviceData &variableValues) {
    clearDisplay();
    cout << endl << "Balance: " << variableValues.balance << endl;
}

void showNumberCupsRemaining(serviceData &variableValues) {
    clearDisplay();
    cout << endl << "Cups remaining: " << variableValues.cups << endl;
}

void takeMoney(serviceData &balanceAndCups) {
    clearDisplay();
    cout << endl << "Take money in the amount of: " << balanceAndCups.balance << " BYN." << endl;
    balanceAndCups.balance = 0;
}

// Нужно оставить лишь одну функцию
void changeColour(int colour) {
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, colour);
}
// Нужно оставить лишь одну функцию
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