#include "Dani.h"
#include <iostream>
#include <limits>

using namespace std;

void inputStage(Stage& stage) {
    cout << "Введіть номер етапу: ";
    cin.getline(stage.stageNumber, 5);
    cout << "Введіть назву етапу: ";
    cin.getline(stage.stageName, 40);
    cout << "Введіть заплановану дату виконання (ДД.ММ.РРРР): ";
    cin.getline(stage.plannedDate, 10);
    cout << "Введіть статус етапу: ";
    cin.getline(stage.status, 40);
}

int main() {
    setlocale(LC_ALL, ""); // Установим локаль по умолчанию для вашей системы
    const char* filename = "stages.dat";
    int choice;

    do {
        cout << "|---------------------------------------------|\n";
        cout << "| ПРОГРАМА ДЛЯ ЛОГІСТИКИ ТЕХНОЛОГІЧНИХ ЕТАПІВ  |\n";
        cout << "|---------------------------------------------|\n";
        cout << "1. Додати новий проект\n";
        cout << "2. Видалити етап та додати новий етап\n";
        cout << "3. Вивести інформацію про проект\n";
        cout << "4. Вивести інформацію про всі проекти\n";
        cout << "5. Вийти\n";
        cout << "Виберіть опцію: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Project project;
            project.stageCount = 0;
            cout << "Введіть назву проекту: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.getline(project.projectName, 40);

            char more;
            do {
                Stage stage;
                inputStage(stage);
                project.stages[project.stageCount++] = stage;

                cout << "Додати ще один етап? (y/n): ";
                cin >> more;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } while (more == 'y');

            addProject(filename, project);
            break;
        }
        case 2: {
            char projectName[40];
            int stageNumber;
            Stage newStage;

            cout << "Введіть назву проекту: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.getline(projectName, 40);
            cout << "Введіть номер етапу для видалення: ";
            cin >> stageNumber;
            cout << "Введіть нову інформацію для етапу:\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            inputStage(newStage);

            deleteStage(filename, projectName, stageNumber);
            addStage(filename, projectName, newStage);
            break;
        }
        case 3: {
            int projectNumber;
            cout << "Введіть номер проекту: ";
            cin >> projectNumber;
            printProjectInfo(filename, projectNumber);
            break;
        }
        case 4: {
            printAllProjects(filename);
            break;
        }
        case 5:
            cout << "Вихід з програми.\n";
            break;
        default:
            cerr << "Неправильний вибір! Спробуйте ще раз.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}