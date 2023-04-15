#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <iterator>>
#include <windows.h>

using namespace std;
string fileUsers = "users.txt";
string fileBus = "bus.txt";
const string PROGR_INFO = "author Evgeny Sochinsky";
int const countOfUsers = 10;
int const countOfBus = 10;

struct Bus {
    string number;
    vector<std::string> route;
    int numberoOfVacancies;
    int time;
};

struct User {
    string login;
    string password;
};

int main();

void admMenuStart();

int authorization();

void admMenuBus();

void admMenuUsers();

void userMenuStart();

bool fileExists(const string& filename);

bool isLoginExists(const string& filename, const string& login);

void registrUser(string& fileUsers);

bool loginUser(const string& fileUsers, const string& login, const string& password);

void authorizationMainMenu();

void readUsers(User* users, int& numberOfUsers);

void showUsers(User* users, int numberOfUsers);

void addUserInArray(User* users, int& numberOfUsers);

void editUser(User* users, int numberOfUsers);

void dellUser();

void writeEndFileUsers(User newUser);

void writeFileUsers(User* users, int numberOfUsers);

void sortUsers(User* users, int& numberOfUsers);

int getCountOfStucturesInFile(string filePath);

bool removeLine(string filePath, size_t index);

void readBus(Bus* bus, int& numberOfBus);

void showBus(Bus* bus, int numberOfBus);

void addBusInArray(Bus* bus, int& numberOfBus);

void editBus(Bus* bus, int numberOfBus);

void writeFileBus(Bus* bus, int numberOfBus);

void showAllBuses();

void writeEndFileBus(const Bus& newBus, Bus* buses, int numberOfBus);

void dellBus();

void sortBus(Bus* bus, int& numberOfBus);

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

bool isLoginExists(const string& fileUsers, const string& login) {
    ifstream file(fileUsers);
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string fileLogin = line.substr(0, pos);
            if (login == fileLogin) {
                return true;
            }
        }
    }
    return false;
}

void registerUser(string& filename) {
    string login, password;

    do {
        cout << "Enter a login: ";
        cin >> login;
        if (isLoginExists(fileUsers, login)) {
            cout << "This login already exists. Try another one." << endl;
        }
    } while (isLoginExists(fileUsers, login));

    cout << "Enter a password: ";
    cin >> password;
    ofstream file(fileUsers, ios::app);
    file << login << ':' << password << endl;
    file.close();
    cout << "Successfully registered." << endl;
};

bool loginUser(const string& fileUsers, const string& login, const string& password) {
    ifstream file(fileUsers);
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string fileLogin = line.substr(0, pos);
            string filePassword = line.substr(pos + 1);
            if (login == fileLogin && password == filePassword) {
                return true;
            }
        }
    }
    return false;
}

void authorizationMainMenu() {

    if (!fileExists(fileUsers)) {
        ofstream file(fileUsers);
        file.close();
    }


    int choice;
    string login, password;
    do {
        cout << "1. Register\n2. Login\n3. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            registerUser(fileUsers);
            break;
        case 2:
            cout << "Enter your login: ";
            cin >> login;
            cout << "Enter your password: ";
            cin >> password;
            if (loginUser(fileUsers, login, password)) {
                choice = 3;
                if (login == "admin") {
                    system("cls");
                    admMenuStart();
                }
                else {
                    system("cls");
                    userMenuStart();
                }
                cout << "Successfully logged in." << endl;
            }
            else {
                cout << "Incorrect login or password." << endl;
            }
            break;
        case 3:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
    } while (choice != 3);
};

void admMenuStart() {
    char myChoice;
    cout << "********** Главное меню для администратра **********" << endl;
    cout << "1: Работа с пользователями" << endl;
    cout << "2: Работа с данными об автобусе" << endl;
    cout << "9: Назад к авторизации" << endl;
    cout << "0: Выход из программы" << endl;
    cout << "?: Информация о программе" << endl;
tryAgain_am1:
    cout << "\nВыберите пукт меню: ";
    cin >> myChoice;
    switch (myChoice)
    {
    case '1':
        admMenuUsers();
        break;
    case '2':
        admMenuBus();
        break;
    case '9':
        main();
        break;
    case '0':
        exit(0);
    case '?':
        cout << PROGR_INFO << endl;
        break;
    default:
        cout << "Такого пункта меню нет! Попробуйте снова." << endl;
        break;
    }
    goto tryAgain_am1;
}

void admMenuUsers() {

    char myChoice;
    User users[countOfUsers];
    int numberOfUsers = 0;
    cout << "********** Работа с пользователями **********" << endl;
    cout << "1: Показать данные всех пользователей" << endl;
    cout << "2: Добвить пользователя" << endl;
    cout << "3: Изменить пользователя" << endl;
    cout << "4: Удалить пользователей" << endl;
    cout << "5: Упорядочить пользователя" << endl;
    cout << "9: Назад главному меню" << endl;
    cout << "0: Выход из программы" << endl;
    cout << "?: Информация о программе" << endl;
tryAgain_adm2:
    cout << "\nВыберите пукт меню: ";
    cin >> myChoice;
    switch (myChoice)
    {
    case '1':
        readUsers(users, numberOfUsers);
        showUsers(users, numberOfUsers);;
        break;
    case '2':
        registerUser(fileUsers);
        break;
    case '3':
        editUser(users, numberOfUsers);
        break;
    case '4':
        dellUser();
        break;
    case '5':
        sortUsers(users, numberOfUsers);
        break;
    case '9':
        admMenuStart();
        break;
    case '0':
        exit(0);
    case '?':
        cout << PROGR_INFO << endl;
        break;
    default:
        cout << "Такого пункта меню нет! Попробуйте снова." << endl;
        break;
    }
    goto tryAgain_adm2;
}


void admMenuBus()
{
    char myChoice;
    Bus bus[countOfBus];
    int numberOfBus = 0;
    cout << "*** Работа с данными автобуса ***" << endl;
    cout << "1: Показать информацию об автобусе" << endl;
    cout << "2: Добвить запись о автобусе" << endl;
    cout << "3: Показать информацию обо всех автобусах" << endl;
    cout << "4: Изменить запись о автобусе" << endl;
    cout << "5: Удалить запись о автобусе" << endl;
    cout << "6: Сортировка записей" << endl;
    cout << "7: Вывод информации о записях по условию ИЗ" << endl;
    cout << "9: Назад главному меню" << endl;
    cout << "0: Выход из программы" << endl;
    cout << "?: Информация о программе" << endl;
tryAgain_am2:
    cout << "\nВыберите пукт меню: ";
    cin >> myChoice;
    switch (myChoice)
    {
    case '1':
        //readBus(bus, numberOfBus);
        showBus(bus, numberOfBus);
        break;
    case '2':
        addBusInArray(bus, numberOfBus);
        break;
    case '3':
        showAllBuses();
        break;
    case '4':
        editBus(bus, numberOfBus);
        break;
    case '5':
        dellBus();
        break;
    case '6':
        sortBus(bus, numberOfBus);
        break;
    case '9':
        admMenuStart();
        break;
    case '0':
        exit(0);
    case '?':
        cout << PROGR_INFO << endl;
        break;
    default:
        cout << "Такого пункта меню нет! Попробуйте снова. " << endl;
        break;
    }
    goto tryAgain_am2;
}

void userMenuStart()
{
    char myChoice;
    Bus bus[countOfBus];
    int numberOfBus = 0;
    cout << "********** Работа с данными **********" << endl;
    cout << "1: Показать информацию обо всех автобусов" << endl;
    cout << "2: Сортировка автобусы" << endl;
    cout << "9: Назад" << endl;
    cout << "0: Выход из программы" << endl;
    cout << "?: Информация о программе" << endl;
tryAgain_um1:
    cout << "\nВыберите пукт меню: ";
    cin >> myChoice;
    switch (myChoice)
    {
    case '1':
        //readBus(bus, numberOfBus);
        showBus(bus, numberOfBus);
        break;
    case '2':
        sortBus(bus, numberOfBus);
        break;
    case '9':
        main();
        break;
    case '0':
        exit(0);
    case '?':
        cout << PROGR_INFO << endl;
        break;
    default:
        cout << "Такого пункта меню нет! Попробуйте снова." << endl;
        break;
    }
    goto tryAgain_um1;
}

void readUsers(User* users, int& numberOfUsers)
{
    ifstream fin(fileUsers.c_str(), ios::in); // Открыли файл для чтения
    if (!fin.is_open()) cout << "Указанный файл не существует!" << endl;
    else
    {
        int i = 0;
        while (!fin.eof())
        {
            if (i < countOfUsers)
            {
                fin >> users[i].login
                    >> users[i].password;
                i++;
            }
            else
            {
                cout << "Недостаточно памяти для чтения всех данных!" << endl;
                break;
            }
        }
        numberOfUsers = i - 1;
    }
    fin.close();
}

void showUsers(User* users, int numberOfUsers) {
    std::ifstream infile("users.txt");
    std::string line;
    while (std::getline(infile, line)) {
        size_t pos = line.find(':');
        std::string login = line.substr(0, pos);
        std::string password = line.substr(pos + 1);

        std::cout << "Login: " << login << ", Password: " << password << "\n";
    }
}


void addUserInArray(User* users, int& numberOfUsers) {
    cout << "*******************" << " Добавление пользователя "
        << "*******************" << endl;
    //добавление пользователя, если не происходит выход за пределы массива
    if (numberOfUsers + 1 <= countOfUsers)
    {
        numberOfUsers++;
        cout << "Добавление нового пользователя " << endl;
        cout << "Введите имя пользователя: ";
        cin >> users[numberOfUsers - 1].login;
        cout << "Введите пароль: ";
        cin >> users[numberOfUsers - 1].password;
        writeEndFileUsers(users[numberOfUsers - 1]);
        cout << "Пользователь " << users[numberOfUsers - 1].login << "добавлен" << endl;
    }
    else cout << "Недостаточно памяти для добавления нового элемента!" << endl;
}

void editUser(User* users, int numberOfUsers) {
    cout << "*******************"
        << " Редактирование пользователя "
        << "*******************" << endl;
    int id = 100;
    readUsers(users, numberOfUsers);
    cout << "Изменение пользователя" << endl;
    cout << "Введите id пользователя, для изменения ";
    cin >> id;
    id = id - 1;
    if (id > numberOfUsers - 1)
    {
        cout << "Такого пользователя не существует."
            << endl << "Проверьте вводимые данные!" << endl;
    }
    else
    {
        cout << "Имя: ";
        cin >> users[id].login;
        cout << "Пароль: ";
        cin >> users[id].password;
        cout << "Данные пользователя #" << id + 1 << " " << users[id].login
            << " изменены" << endl;
        writeFileUsers(users, numberOfUsers);
    }
}

void dellUser() {
    cout << "*******************"
        << " Удаление пользователя "
        << "*******************" << endl;
    string id;
    cout << "Удаление пользователя" << endl;
    cout << "Введите login пользователя для удаления ";
    cin >> id;
    std::ifstream infile("users.txt");
    std::string line;
    int counter = 0;
    while (std::getline(infile, line)) {
        size_t pos = line.find(':');
        if (id == line.substr(0, pos)) {
            break;
        }
        else {
            counter++;
        }
    }
    removeLine(fileUsers, counter);
}

void writeEndFileUsers(User newUser)
{
    ofstream fadd(fileUsers.c_str(), ios::app); // Открыли файл для дозаписи
    fadd << newUser.login << ":" << newUser.password;
    fadd.close();
}

void writeFileUsers(User* users, int numberOfUsers)
{
    ofstream fout(fileUsers, ios::out);
    for (int i = 0; i < numberOfUsers; i++)
    {
        fout << users[i].login << "\t"
            << users[i].password << endl;
        if (i < numberOfUsers - 1) {
            fout << endl;
        }
    }
    fout << endl;
    fout.close();
}

void sortUsers(User* users, int& numberOfUsers)
{
    vector<string> user;
    ifstream file(fileUsers);
    string line;

    // Чтение данных из файла и сохранение в векторе
    while (getline(file, line)) {
        user.push_back(line);
    }

    // Сортировка по логину в алфавитном порядке
    sort(user.begin(), user.end());

    // Запись отсортированных пользователей в файл
    ofstream out(fileUsers);
    for (const auto& user : user) {
        out << user << endl;
    }
    showUsers(users, numberOfUsers);
}

int getCountOfStucturesInFile(string filePath)
{
    ifstream file(filePath.c_str(), ios::in);
    int numberOfStrings = 0;
    if (file.is_open())
    {
        string buffer;
        while (getline(file, buffer))
            numberOfStrings++;
    }
    file.close();
    return numberOfStrings;
}


bool removeLine(string filePath, size_t index)
{
    vector<string> vec;
    ifstream file(filePath);
    if (file.is_open())
    {
        string str;
        while (getline(file, str))
            vec.push_back(str);
        file.close();
        if (vec.size() < index - 1)
            return false;
        vec.erase(vec.begin() + index - 1);
        ofstream outfile(filePath);
        if (outfile.is_open())
        {
            copy(vec.begin(), vec.end(),
                ostream_iterator<string>(outfile, "\n"));
            outfile.close();
            return true;
        }
        return false;
    }

    return false;
}

void showAllBuses() {
    ifstream infile(fileBus);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
    }
    else {
        cout << "Error opening file " << fileBus << " for reading" << endl;
    }

}

void showBus(Bus* bus, int numberOfBus) {
    fstream infile(fileBus, ios::in);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            if (line.find("Number: " + to_string(numberOfBus)) != string::npos) {
                cout << line << endl;
                getline(infile, line); // read and print the next line
                cout << line << endl;
                getline(infile, line); // read and print the next line
                cout << line << endl;
                cout << "Route:" << endl;
                while (getline(infile, line) && line.find("-") != string::npos) {
                    cout << line << endl;
                }
                break;
            }
        }
        infile.close();
    }
    else {
        cout << "Error opening file " << fileBus << " for reading" << endl;
    }
}

void addBusInArray(Bus* buses, int& numberOfBus)
{
    cout << "***********************************************"
        << " Добавление автобуса в массив "
        << "***********************************************" << endl;
    if (numberOfBus + 1 <= countOfBus)
    {
        numberOfBus++;
        cout << "Добавление нового автобуса " << endl;
        Bus newBus;
        cout << "Номер автобуса: ";
        cin >> newBus.number;
        cout << "Количество мест: ";
        cin >> newBus.numberoOfVacancies;
        cout << "время поездки: ";
        cin >> newBus.time;
        cin.ignore();
        string stop;
        while (true) {
            cout << "Enter a stop on the route (or type 'done' to finish): ";
            getline(cin, stop);
            if (stop == "done") {
                break;
            }
            newBus.route.push_back(stop);
        }

        buses[numberOfBus - 1] = newBus;

        // Передаем информацию о новом автобусе в функцию writeEndFileBus
        writeEndFileBus(newBus, buses, numberOfBus);
        showBus(buses, numberOfBus - 1);
    }
    else cout << "Недостаточно памяти для добавления нового элемента!" << endl;
}


void editBus(Bus* bus, int numberOfBus) {
    std::vector<Bus> buses;
    fstream file(fileBus, ios::in | ios::out);


    if (file.is_open()) {
        string line;
        int count = 0;
        bool busFound = false;
        while (getline(file, line)) {
            if (line == "Number: ") {
                if (count == numberOfBus) {
                    busFound = true;
                    string number = "";
                    int free_seats = 0;
                    int travel_time = 0;
                    vector<string> route;
                    getline(file, line); // Считываем номер автобуса
                    number = line.substr(8);
                    getline(file, line); // Считываем количество свободных мест
                    free_seats = stoi(line.substr(13));
                    getline(file, line); // Считываем время поездки
                    travel_time = stoi(line.substr(14));
                    getline(file, line); // Считываем пустую строку
                    getline(file, line); // Считываем маршрут
                    while (getline(file, line)) {
                        if (line == "") {
                            break;
                        }
                        else {
                            route.push_back(line.substr(2));
                        }
                    }

                    // Вывод текущих данных об автобусе
                    cout << "Текущие данные об автобусе:" << endl;
                    cout << "Номер: " << number << endl;
                    cout << "Количество свободных мест: " << free_seats << endl;
                    cout << "Время поездки: " << travel_time << endl;
                    cout << "Маршрут: ";
                    for (string stop : route) {
                        cout << stop << " ";
                    }
                    cout << endl;

                    // Ввод новых данных об автобусе
                    cout << "Введите новые данные об автобусе:" << endl;
                    cout << "Номер: ";
                    getline(cin, number);
                    cout << "Количество свободных мест: ";
                    cin >> free_seats;
                    cout << "Время поездки: ";
                    cin >> travel_time;
                    cin.ignore();
                    route.clear();
                    string stop;
                    while (true) {
                        cout << "Маршрут (для завершения введите пустую строку): ";
                        getline(cin, stop);
                        if (stop.empty()) {
                            break;
                        }
                        route.push_back(stop);
                    }


                    // Обновление данных об автобусе в файле
                    file.seekp(0, ios::beg);
                    count = 0;
                    while (getline(file, line)) {
                        if (line == "Number: ") {
                            if (count == numberOfBus) {
                                file << "Number: " << number << endl;
                                file << "Free seats: " << free_seats << endl;
                                file << "Travel time: " << travel_time << endl;
                                file << "Route: " << endl;
                                for (string stop : route) {
                                    file << "- " << stop << endl;
                                }
                                break;
                            }
                            else {
                                count++;
                            }
                        }
                    }
                    cout << "Данные об автобусе успешно изменены." << endl;
                    break;
                }
                else {
                    count++;
                }
            }
        }
        if (!busFound) {
            cout << "Bus with number " << bus->number << " not found." << endl;
        }
        else {
            // Редактирование найденного автобуса
            cout << "Enter new number of free seats: ";
            int newVacancies;
            cin >> newVacancies;
            bus->numberoOfVacancies = newVacancies;

            cout << "Enter new travel time: ";
            int newTime;
            cin >> newTime;
            bus->time = newTime;

            cout << "Enter new route (end with empty line):" << endl;
            vector<string> newRoute;
            string stop;
            while (getline(cin, stop) && !stop.empty()) {
                newRoute.push_back(stop);
            }
            bus->route = newRoute;

            // Запись изменений в файл
            ofstream outfile(fileBus);
            if (outfile.is_open()) {
                for (Bus& b : buses) {
                    outfile << "Number: " << b.number << endl;
                    outfile << "Free seats: " << b.numberoOfVacancies << endl;
                    outfile << "Travel time: " << b.time << endl;
                    outfile << "Route: " << endl;
                    for (string stop : b.route) {
                        outfile << "- " << stop << endl;
                    }
                }
                outfile.close();
                cout << "Bus with number " << bus->number << " successfully updated." << endl;
            }
            else {
                cout << "Error opening file " << fileBus << endl;
            }
        }
    }
}

void writeEndFileBus(const Bus& newBus, Bus* buses, int numberOfBus) {
    fstream outfile(fileBus, ios::app); // append mode
    if (outfile.is_open()) {
        outfile << "Number: " << newBus.number << endl;
        outfile << "Free seats: " << newBus.numberoOfVacancies << endl;
        outfile << "Travel time: " << newBus.time << endl;
        outfile << "Route: " << endl;
        for (string stop : newBus.route) {
            outfile << "- " << stop << endl;
        }
        outfile << endl; // add empty line after each bus
        outfile.close();
        cout << "Data is written to the file " << fileBus << endl;

        // Обновляем соответствующий элемент массива buses
        buses[numberOfBus - 1] = newBus;
    }
    else {
        cout << "Error opening file " << fileBus << " for writing" << endl;
    }
}


void dellBus()
{
    cout << "***********************************************"
        << " Удаление записи о автобусе "
        << "***********************************************" << endl;
    string id;
    int k = getCountOfStucturesInFile(fileBus);
    cout << "Введите номер автобуса для удаления: ";
    cin >> id;
    std::ifstream infile(fileBus);
    std::string line;
    int counter = 0;
    while (std::getline(infile, line)) {
        size_t pos = line.find(':');
        if (id == line.substr(0, pos)) {
            removeLine(fileBus, counter);
            break;
        }
        else {
            counter++;
        }
    }

    cout << "автобус #" << id << " удален" << endl;
}

void sortBus(Bus* bus, int& numberOfBus)
{
    char myChoice;
    Bus temp;
    cout << "********** Сортировка **********" << endl;
    cout << "1: Упорядочить записи по номеру автобуса " << endl;
    cout << "2: Упорядочить записи по количеству мест" << endl;
    cout << "3: Упорядочить записи по времени поездки" << endl;
    cout << "9: Назад " << endl;
    cout << "0: Выход из программы" << endl;
    cout << "?: Информация о программе" << endl;
tryAgain_sort:
    cout << "\nВыберите пукт меню: ";
    cin >> myChoice;
    switch (myChoice)
    {
    case '1':
        //readBus(bus, numberOfBus);
        for (int i = 0; i < numberOfBus - 1; i++)
        {
            for (int j = 0; j < numberOfBus - i - 1; j++)
            {
                if (bus[j].number > bus[j + 1].number)
                {
                    temp = bus[j];
                    bus[j] = bus[j + 1];
                    bus[j + 1] = temp;
                }
            }
        }
        showBus(bus, numberOfBus);
        break;
    case '2':
        //readBus(bus, numberOfBus);
        for (int i = 0; i < numberOfBus - 1; i++)
        {
            for (int j = 0; j < numberOfBus - i - 1; j++)
            {
                if (bus[j].numberoOfVacancies > bus[j + 1].numberoOfVacancies)
                {
                    temp = bus[j];
                    bus[j] = bus[j + 1];
                    bus[j + 1] = temp;
                }
            }
        }

        showBus(bus, numberOfBus);
        break;
    case '3':
        //readBus(bus, numberOfBus);
        for (int i = 0; i < numberOfBus - 1; i++)
        {
            for (int j = 0; j < numberOfBus - i - 1; j++)
            {
                if (bus[j].time > bus[j + 1].time)
                {
                    temp = bus[j];
                    bus[j] = bus[j + 1];
                    bus[j + 1] = temp;
                }
            }
        }
        showBus(bus, numberOfBus);
        break;
    case '9':
        main();
        break;
    case '0':
        exit(0);
    case '?':
        cout << PROGR_INFO << endl;
        break;
    default:
        cout << "Такого пункта меню нет! Попробуйте снова." << endl;
        break;
    }
    goto tryAgain_sort;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::map<std::string, Bus> buses;
    authorizationMainMenu();

    return 0;
}

