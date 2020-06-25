// Vinícius Meng - 0250583

#ifndef __BIBLIOTECA_H
#define __BIBLIOTECA_H

typedef struct person {
    int id;
    char name[20];
    char surname[20];
    int age;
    int height;
} person;

int compareName(const void *personDataA, const void *personDataB);
int compareSurname(const void *personDataA, const void *personDataB);
int compareAge(const void *personDataA, const void *personDataB);
int compareHeight(const void *personDataA, const void *personDataB);
float arithmeticMeanAge(const person *peopleData, const int arraySize);
float geometricMeanAge(const person *peopleData, const int arraySize);
float arithmeticMeanHeight(const person *peopleData, const int arraySize);
float geometricMeanHeight(const person *peopleData, const int arraySize);

#endif