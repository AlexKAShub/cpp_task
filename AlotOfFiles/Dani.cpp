#include "Dani.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

void addProject(const char* filename, Project& project) {
    // ������������ ���� ������� �� ���� ������� �� ����� ������� �����
    if (project.stageCount > 0) {
        strcpy(project.startDate, project.stages[0].plannedDate);
        strcpy(project.endDate, project.stages[0].plannedDate);
    }

    ofstream outFile(filename, ios::binary | ios::app);
    if (outFile) {
        outFile.write(reinterpret_cast<const char*>(&project), sizeof(Project));
        outFile.close();
    }
    else {
        cerr << "������� �������� ����� ��� ������!" << endl;
    }
}

void addStage(const char* filename, const char* projectName, const Stage& stage) {
    Project projects[100];
    int projectCount = 0;
    loadProjects(filename, projects, projectCount);

    for (int i = 0; i < projectCount; ++i) {
        if (strcmp(projects[i].projectName, projectName) == 0) {
            if (projects[i].stageCount < 100) {
                projects[i].stages[projects[i].stageCount++] = stage;

                // ��������� ���� ������� �� ���� �������
                if (strcmp(stage.plannedDate, projects[i].startDate) < 0) {
                    strcpy(projects[i].startDate, stage.plannedDate);
                }
                if (strcmp(stage.plannedDate, projects[i].endDate) > 0) {
                    strcpy(projects[i].endDate, stage.plannedDate);
                }

                saveProjects(filename, projects, projectCount);
                return;
            }
            else {
                cerr << "��������� ����������� ������� �����!" << endl;
                return;
            }
        }
    }

    cerr << "������ �� ��������!" << endl;
}

void deleteStage(const char* filename, const char* projectName, int stageNumber) {
    Project projects[100];
    int projectCount = 0;
    loadProjects(filename, projects, projectCount);

    for (int i = 0; i < projectCount; ++i) {
        if (strcmp(projects[i].projectName, projectName) == 0) {
            if (stageNumber < 0 || stageNumber >= projects[i].stageCount) {
                cerr << "�������� ����� �����!" << endl;
                return;
            }
            for (int j = stageNumber; j < projects[i].stageCount - 1; ++j) {
                projects[i].stages[j] = projects[i].stages[j + 1];
            }
            projects[i].stageCount--;

            // ��������� ���� ������� �� ���� ������� ���� ��������� �����
            if (projects[i].stageCount > 0) {
                strcpy(projects[i].startDate, projects[i].stages[0].plannedDate);
                strcpy(projects[i].endDate, projects[i].stages[0].plannedDate);
                for (int k = 1; k < projects[i].stageCount; ++k) {
                    if (strcmp(projects[i].stages[k].plannedDate, projects[i].startDate) < 0) {
                        strcpy(projects[i].startDate, projects[i].stages[k].plannedDate);
                    }
                    if (strcmp(projects[i].stages[k].plannedDate, projects[i].endDate) > 0) {
                        strcpy(projects[i].endDate, projects[i].stages[k].plannedDate);
                    }
                }
            }
            else {
                strcpy(projects[i].startDate, "");
                strcpy(projects[i].endDate, "");
            }

            saveProjects(filename, projects, projectCount);
            return;
        }
    }

    cerr << "������ �� ��������!" << endl;
}

void printProjectInfo(const char* filename, int projectNumber) {
    Project projects[100];
    int projectCount = 0;
    loadProjects(filename, projects, projectCount);

    if (projectNumber <= 0 || projectNumber > projectCount) {
        cerr << "�������� ����� �������!" << endl;
        return;
    }

    const Project& project = projects[projectNumber - 1];
    cout << "|--------------------------------------------------------------------------|\n";
    cout << "|                                  " << project.projectName << "                                  |\n";
    cout << "|--------------------------------------------------------------------------|\n";
    cout << "| ����� ����� | ����� �����                  | ����������� ���� | ������         |\n";
    cout << "|-------------|------------------------------|------------------|----------------|\n";

    for (int j = 0; j < project.stageCount; ++j) {
        cout << "|   " << project.stages[j].stageNumber
            << "         |   " << project.stages[j].stageName
            << "       |   " << project.stages[j].plannedDate
            << "    |   " << project.stages[j].status << "    |\n";
    }
    cout << "|--------------------------------------------------------------------------|\n";
}

void loadProjects(const char* filename, Project* projects, int& count) {
    ifstream inFile(filename, ios::binary);
    if (inFile) {
        count = 0;
        while (inFile.read(reinterpret_cast<char*>(&projects[count]), sizeof(Project))) {
            count++;
        }
        inFile.close();
    }
    else {
        cerr << "������� �������� ����� ��� �������!" << endl;
    }
}

void saveProjects(const char* filename, const Project* projects, int count) {
    ofstream outFile(filename, ios::binary | ios::trunc);
    if (outFile) {
        outFile.write(reinterpret_cast<const char*>(projects), sizeof(Project) * count);
        outFile.close();
    }
    else {
        cerr << "������� �������� ����� ��� ������!" << endl;
    }
}

void printAllProjects(const char* filename) {
    Project projects[100];
    int projectCount = 0;
    loadProjects(filename, projects, projectCount);

    if (projectCount == 0) {
        cerr << "���� ����� ��� �����������!" << endl;
        return;
    }

    cout << "|-----------------------------------------------------------------------------------------|\n";
    cout << "|                         ���������� ��� �� �������                                      |\n";
    cout << "|-----------------------------------------------------------------------------------------|\n";
    cout << "| ����� ������� | ����� �������            | ���� �������                                 |\n";
    cout << "|---------------|--------------------------|----------------------------------------------|\n";

    for (int i = 0; i < projectCount; ++i) {
        cout << "| " << i + 1 << "             | " << projects[i].projectName
            << "       | " << projects[i].startDate << " - " << projects[i].endDate << " |\n";
    }
    cout << "|-----------------------------------------------------------------------------------------|\n";
}