//Vinícius Meng - 0250583

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "biblioteca.h"

#define PEOPLE_ARRAY_MAX_SIZE 20

typedef enum typeOfOperation {
    defaultOperation = 0,
    nameSorted = 1,
    surnameSorted = 2,
    ageSorted = 3,
    heightSorted = 4,
    arithmeticMean = 5,
    geometricMean = 6
} typeOfOperation;

void help() {
    printf("\nUtilizacao:\n");
    printf("Exemplo:> trabalhoFinal.exe NewDataPeople.dat NewDataPeopleSorted.dat\n");
    printf("\nArgumentos de entrada:\n");
    printf("    -ns     Ordenar por nome. Exemplo:> trabalhoFinal.exe -ns NewDataPeople.dat NewDataPeopleSorted.dat\n");
    printf("    -ss     Ordenar por sobrenome. Exemplo:> trabalhoFinal.exe -ss NewDataPeople.dat NewDataPeopleSorted.dat\n");
    printf("    -as     Ordenar por idade. Exemplo:> trabalhoFinal.exe -as NewDataPeople.dat NewDataPeopleSorted.dat\n");
    printf("    -hs     Ordenar por altura. Exemplo:> trabalhoFinal.exe -hs NewDataPeople.dat NewDataPeopleSorted.dat\n");
    printf("    -am     Media aritmetica da idade e da altura. Exemplo:> trabalhoFinal.exe -am NewDataPeople.dat NewDataPeopleSorted.dat\n");
    printf("    -gm     Media geometrica da idade e da altura. Exemplo:> trabalhoFinal.exe -gm NewDataPeople.dat NewDataPeopleSorted.dat\n");
    printf("    -all    Realiza todas as operacoes acima de modo verboso. Exemplo:> trabalhoFinal.exe -all NewDataPeople.dat NewDataPeopleSorted.dat\n");
    printf("    -r      Ler um arquivo. Exemplo:> trabalhoFinal.exe -r NewDataPeople.dat\n\n");
}

int printPeopleFile(const char *fileName) {
    FILE *file;
    person personData;

    if (!(file = fopen(fileName, "r"))) {
        printf("\nNao foi possivel ler este arquivo: %s\n", fileName);
        help();
        return -2;
    }

    printf("\n=====================================================\n");

    while (fread(&personData, sizeof(person), 1, file)) {
        printf("id: %d, name: %s, surname: %s, age: %d, height: %d\n", personData.id, personData.name, personData.surname, personData.age, personData.height);
    }

    printf("=====================================================\n\n");

    fclose(file);
    return 0;
}

int writeSortedPeopleFile(const person *arr, const int arraySize, char *prefix, const char *fileName) {
    FILE *file;
    char newFileName[100];

    strcpy(newFileName, prefix);
    strcat(newFileName, fileName);

    if (!(file = fopen(newFileName, "w"))) {
        printf("\nNao foi possivel escrever este arquivo: %s\n", newFileName);
        help();
        return false;
    }

    for (int counter = 0; counter < arraySize; counter++) {
        fwrite(&arr[counter], sizeof(person), 1, file);
    }

    fclose(file);
    return true;
}

void printPeopleInMemory(const person *arr, const int arraySize, const char *title) {
    printf("\n=====================================================\n");
    printf("%s\n\n", title);
    for (int counter = 0; counter < arraySize; counter++) {
        printf("id: %d, name: %s, surname: %s, age: %d, height: %d\n", arr[counter].id, arr[counter].name, arr[counter].surname, arr[counter].age, arr[counter].height);
    }
    printf("=====================================================\n");
}

int main(const int argc, const char *argv[]) {
    FILE *file;
    person personData;
    person peopleData[PEOPLE_ARRAY_MAX_SIZE];
    int counter = 0;
    typeOfOperation typeOfOp = defaultOperation;
    int moveArgument = 0;

    if (argc < 3) {
        help();
        return -1;
    }

    if (strcmp(argv[1], "-r") == 0) {
        return printPeopleFile(argv[2]);
    } else if (strcmp(argv[1], "-ns") == 0) {
        typeOfOp = nameSorted;
        moveArgument++;
    } else if (strcmp(argv[1], "-ss") == 0) {
        typeOfOp = surnameSorted;
        moveArgument++;
    } else if (strcmp(argv[1], "-as") == 0) {
        typeOfOp = ageSorted;
        moveArgument++;
    } else if (strcmp(argv[1], "-hs") == 0) {
        typeOfOp = heightSorted;
        moveArgument++;
    } else if (strcmp(argv[1], "-am") == 0) {
        typeOfOp = arithmeticMean;
        moveArgument++;
    } else if (strcmp(argv[1], "-gm") == 0) {
        typeOfOp = geometricMean;
        moveArgument++;
    } else if (strcmp(argv[1], "-all") == 0) {
        typeOfOp = defaultOperation;
        moveArgument++;
    }

    if (!(file = fopen(argv[1 + moveArgument], "r"))) {
        printf("\nNao foi possivel ler este arquivo: %s\n", argv[1 + moveArgument]);
        help();
        return -2;
    }

    while (fread(&personData, sizeof(person), 1, file)) {
        peopleData[counter] = personData;
        counter++;
    }

    fclose(file);

    const int arraySize = sizeof(peopleData) / sizeof(person);

    if (typeOfOp == defaultOperation) {
        printPeopleInMemory(peopleData, arraySize, "Dados desordenados:");
    }

    if (typeOfOp == defaultOperation || typeOfOp == nameSorted) {
        qsort(peopleData, arraySize, sizeof(person), compareName);

        if (typeOfOp == defaultOperation) {
            printPeopleInMemory(peopleData, arraySize, "Dados ordenados por nome:");
        }

        if (!writeSortedPeopleFile(peopleData, arraySize, "Name", argv[2 + moveArgument])) {
            return -3;
        }
    }

    if (typeOfOp == defaultOperation || typeOfOp == surnameSorted) {
        qsort(peopleData, arraySize, sizeof(person), compareSurname);

        if (typeOfOp == defaultOperation) {
            printPeopleInMemory(peopleData, arraySize, "Dados ordenados por sobrenome:");
        }

        if (!writeSortedPeopleFile(peopleData, arraySize, "Surname", argv[2 + moveArgument])) {
            return -3;
        }
    }

    if (typeOfOp == defaultOperation || typeOfOp == ageSorted) {
        qsort(peopleData, arraySize, sizeof(person), compareAge);

        if (typeOfOp == defaultOperation) {
            printPeopleInMemory(peopleData, arraySize, "Dados ordenados por idade:");
        }

        if (!writeSortedPeopleFile(peopleData, arraySize, "Age", argv[2 + moveArgument])) {
            return -3;
        }
    }

    if (typeOfOp == defaultOperation || typeOfOp == heightSorted) {
        qsort(peopleData, arraySize, sizeof(person), compareHeight);

        if (typeOfOp == defaultOperation) {
            printPeopleInMemory(peopleData, arraySize, "Dados ordenados por altura:");
        }

        if (!writeSortedPeopleFile(peopleData, arraySize, "Height", argv[2 + moveArgument])) {
            return -3;
        }
    }

    if (typeOfOp == defaultOperation || typeOfOp == arithmeticMean || typeOfOp == geometricMean) {
        printf("\n=====================================================");

        if (typeOfOp == defaultOperation || typeOfOp == arithmeticMean) {
            const float ageArithmeticMean = arithmeticMeanAge(peopleData, arraySize);
            const float heightArithmeticMean = arithmeticMeanHeight(peopleData, arraySize);
            printf("\nMedia aritmetica das idades: %.2f\n", ageArithmeticMean);
            printf("Media aritmetica das alturas: %.2f", heightArithmeticMean);
        }

        if (typeOfOp == defaultOperation || typeOfOp == geometricMean) {
            const float ageGeometricMean = geometricMeanAge(peopleData, arraySize);
            const float heightGeometricMean = geometricMeanHeight(peopleData, arraySize);
            printf("\nMedia geometrica das idades: %.2f\n", ageGeometricMean);
            printf("Media geometrica das alturas: %.2f", heightGeometricMean);
        }

        printf("\n=====================================================\n");
    }

    return 0;
}