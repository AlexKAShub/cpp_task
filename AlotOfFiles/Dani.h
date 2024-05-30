#pragma once

struct Stage {
    char stageNumber[5];   // ����� �����
    char stageName[40];    // ����� �����
    char plannedDate[10];  // ����������� ���� ��������� �����
    char status[40];       // ������ �����
};

struct Project {
    char projectName[40];   // ����� �������
    char startDate[10];     // ���� ������� �������
    char endDate[10];       // ���� ���� �������
    Stage stages[100];      // ����� �������
    int stageCount;         // ʳ������ �����
};

void addProject(const char* filename, Project& project);
void addStage(const char* filename, const char* projectName, const Stage& stage);
void deleteStage(const char* filename, const char* projectName, int stageNumber);
void printProjectInfo(const char* filename, int projectNumber);
void loadProjects(const char* filename, Project* projects, int& count);
void saveProjects(const char* filename, const Project* projects, int count);
void printAllProjects(const char* filename);