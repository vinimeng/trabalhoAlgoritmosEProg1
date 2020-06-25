// Vinícius Meng - 0250583

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "biblioteca.h"

int compareName(const void *personDataA, const void *personDataB) {
    const person *pDataA = personDataA;
    const person *pDataB = personDataB;

    int lengthNameA = strlen(pDataA->name);
    int lengthNameB = strlen(pDataB->name);

    if (lengthNameA == lengthNameB) {
        for (int i = 0; i < lengthNameA; i++) {
            if (pDataA->name[i] != pDataB->name[i]) {
                return pDataA->name[i] - pDataB->name[i];
            }
        }
        return 0;
    }

    return lengthNameA - lengthNameB;
}

int compareSurname(const void *personDataA, const void *personDataB) {
    const person *pDataA = personDataA;
    const person *pDataB = personDataB;

    int lengthSurnameA = strlen(pDataA->surname);
    int lengthSurnameB = strlen(pDataB->surname);

    if (lengthSurnameA == lengthSurnameB) {
        for (int i = 0; i < lengthSurnameA; i++) {
            if (pDataA->surname[i] != pDataB->surname[i]) {
                return pDataA->surname[i] - pDataB->surname[i];
            }
        }
        return 0;
    }

    return lengthSurnameA - lengthSurnameB;
}

int compareAge(const void *personDataA, const void *personDataB) {
    const person *pDataA = personDataA;
    const person *pDataB = personDataB;

    return pDataA->age - pDataB->age;
}

int compareHeight(const void *personDataA, const void *personDataB) {
    const person *pDataA = personDataA;
    const person *pDataB = personDataB;

    return pDataA->height - pDataB->height;
}

float arithmeticMeanAge(const person *peopleData, const int arraySize) {
    unsigned int accumulator = 0;

    for (int i = 0; i < arraySize; i++) {
        accumulator += peopleData[i].age;
    }

    return (float)accumulator / (float)arraySize;
}

float geometricMeanAge(const person *peopleData, const int arraySize) {
    double accumulator = 1;

    for (int i = 0; i < arraySize; i++) {
        accumulator *= peopleData[i].age;
    }

    return (float)pow(accumulator, (float)1/arraySize);
}

float arithmeticMeanHeight(const person *peopleData, const int arraySize) {
    unsigned int accumulator = 0;

    for (int i = 0; i < arraySize; i++) {
        accumulator += peopleData[i].height;
    }

    return (float)accumulator / (float)arraySize;
}

float geometricMeanHeight(const person *peopleData, const int arraySize) {
    double accumulator = 1;

    for (int i = 0; i < arraySize; i++) {
        accumulator *= peopleData[i].height;
    }

    return (float)pow(accumulator, (float)1/arraySize);
}