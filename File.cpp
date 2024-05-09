#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

void drawLine(int length) {
    cout << "+";
    for (int i = 0; i < length - 2; ++i) {
        cout << "-";
    }
    cout << "+" << endl;
}

void drawText(const string& text, int length) {
    int padding = (length - text.length()) / 2;
    cout << "|";
    for (int i = 0; i < padding; ++i) {
        cout << " ";
    }
    cout << text;
    for (int i = 0; i < length - padding - text.length() - 1; ++i) {
        cout << " ";
    }
    cout << "|" << endl;
}

void drawRow(const string& content, int length) {
    cout << ">" << content;
    for (int i = 0; i < length - content.length() - 1; ++i) {
        cout << " ";
    }
    cout << endl;
}

bool authenticate(const string& username, const string& password) {
    vector<pair<string, string>> users = { {"admin", "admin"}, {"moder2", "123"}, {"moder1", "321"}, {"moder3", "1111"} };

    for (const auto& user : users) {
        if (username == user.first && password == user.second) {
            return true;
        }
    }

    return false;
}

string getCurrentDate() {
    time_t rawtime;
    struct tm timeinfo;
    char buffer[11];

    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);

    strftime(buffer, sizeof(buffer), "%d.%m.%Y", &timeinfo);
    return string(buffer);
}

bool is_number(const string& s) {
    try {
        stod(s);
    }
    catch (...) {
        return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "Ukrainian");

    string username, password, filename, date, income, expenses, losses, profit, clients;

    drawLine(110);
    drawText("Програмний продукт \"Звiтнiсть вiддiлення\" мовою програмування С++", 110);
    drawText("розробив Скорик Андрiй.", 110);

    // drawText("розробив Скорик Андрiй,", 110);
    // drawText("керiвник Руденко Антонiна Петрiвна.", 110);
    drawLine(110);

    cout << "Логiн: ";
    cin >> username;
    cout << "Пароль: ";
    cin >> password;

    if (!authenticate(username, password)) {
        cout << "Неправильний логiн або пароль. Вихiд з програми." << endl;
        return 1;
    }

    do {
        drawLine(110);
        cout << ">" << "Введiть назву файлу для збереження (або нову назву): ";
        cin >> filename;
        drawLine(110);

        ifstream fileExists(filename + ".csv");
        bool exists = fileExists.good();
        fileExists.close();

        ofstream outFile(filename + ".csv", ios::app);
        if (!outFile.is_open()) {
            cerr << "Помилка вiдкриття файлу для запису." << endl;
            return 1;
        }

        if (!exists) {
            outFile << "Дата:," << "Звiти про доходи:," << "Витрати:," << "Збитки:," << "Прибуток:," << "Кiлькiсть обслужених клiєнтiв за робочий день:," << "Звiт оформив:" << endl;
        }

        date = getCurrentDate();
        drawLine(110);
        cout << ">" << "Введіть дату. Формат: (" << date << " або 'auto'): ";
        cin >> date;

        if (date == "auto")
            date = getCurrentDate();

        cout << ">" << "Введiть доходи(грн): ";
        cin >> income;
        while (!is_number(income)) {
            cout << ">" << "Будь ласка, введiть число: ";
            cin >> income;
        }

        cout << ">" << "Введiть витрати(грн): ";
        cin >> expenses;
        while (!is_number(expenses)) {
            cout << ">" << "Будь ласка, введiть число: ";
            cin >> expenses;
        }

        cout << ">" << "Введiть збитки(грн): ";
        cin >> losses;
        while (!is_number(losses)) {
            cout << ">" << "Будь ласка, введiть число: ";
            cin >> losses;
        }

        cout << ">" << "Введiть прибуток(грн): ";
        cin >> profit;
        while (!is_number(profit)) {
            cout << ">" << "Будь ласка, введiть число: ";
            cin >> profit;
        }

        cout << ">" << "Кiлькiсть обслужених клiєнтiв за робочий день: ";
        cin >> clients;
        while (!is_number(clients)) {
            cout << ">" << "Будь ласка, введiть число: ";
            cin >> clients;
        }
        outFile << date << "," << income << "грн" << "," << expenses << "грн" << "," << losses << "грн" << "," << profit << "грн" << "," << clients << "," << username << endl;
        outFile.close();

        drawLine(110);
        cout << ">" << "Звiт успiшно збережено у файлi '" << filename << ".csv'." << endl;

        char choice;
        cout << ">" << "Бажаєте створити новий звітi (Y/N): ";
        cin >> choice;
        if (choice != 'Y' && choice != 'y')
            break;
    } while (true);

    return 0;
}
