#pragma once

struct Stage {
    char stageNumber[5];   // Номер етапу
    char stageName[40];    // Назва етапу
    char plannedDate[10];  // Запланована дата виконання етапу
    char status[40];       // Статус етапу
};

struct Project {
    char projectName[40];   // Назва проекту
    char startDate[10];     // Дата початку проекту
    char endDate[10];       // Дата кінця проекту
    Stage stages[100];      // Етапи проекту
    int stageCount;         // Кількість етапів
};

void addProject(const char* filename, Project& project);
void addStage(const char* filename, const char* projectName, const Stage& stage);
void deleteStage(const char* filename, const char* projectName, int stageNumber);
void printProjectInfo(const char* filename, int projectNumber);
void loadProjects(const char* filename, Project* projects, int& count);
void saveProjects(const char* filename, const Project* projects, int count);
void printAllProjects(const char* filename);