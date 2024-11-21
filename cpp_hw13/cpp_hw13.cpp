#include <iostream>
#include <queue>
#include <string>
#include <ctime>

using namespace std;

struct PrintJob {
    int priority;
    string user;  
    string documentName; 
    time_t requestTime; 

    bool operator<(const PrintJob& other) const {
        return priority < other.priority;
    }
};

struct PrintStatistics {
    string user;
    string documentName;
    time_t printTime;
};

priority_queue<PrintJob> printQueue;
queue<PrintStatistics> statisticsQueue;

void addPrintJob(string user, string documentName, int priority) {
    PrintJob job = { priority, user, documentName, time(nullptr) };
    printQueue.push(job);
    cout << "Задание добавлено: " << documentName << " от " << user << " с приоритетом " << priority << endl;
}

void processPrintJob() {
    if (printQueue.empty()) {
        cout << "Очередь печати пуста." << endl;
        return;
    }

    PrintJob job = printQueue.top();
    printQueue.pop();

    PrintStatistics stat = { job.user, job.documentName, time(nullptr) };
    statisticsQueue.push(stat);

    cout << "Печатается: " << job.documentName << " от " << job.user << endl;
}

void printStatistics() {
    if (statisticsQueue.empty()) {
        cout << "Статистика пуста." << endl;
        return;
    }

    while (!statisticsQueue.empty()) {
        PrintStatistics stat = statisticsQueue.front();
        statisticsQueue.pop();
        cout << "Документ: " << stat.documentName
            << ", Пользователь: " << stat.user
            << ", Время печати: " << ctime(&stat.printTime);
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n1. Добавить задание\n2. Печать задания\n3. Показать статистику\n4. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (choice == 1) {
            string user, documentName;
            int priority;
            cout << "Введите имя пользователя: ";
            cin >> user;
            cout << "Введите название документа: ";
            cin >> documentName;
            cout << "Введите приоритет (чем выше, тем важнее): ";
            cin >> priority;
            addPrintJob(user, documentName, priority);
        }
        else if (choice == 2) {
            processPrintJob();
        }
        else if (choice == 3) {
            printStatistics();
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Неверный выбор!" << endl;
        }
    }

    return 0;
}
