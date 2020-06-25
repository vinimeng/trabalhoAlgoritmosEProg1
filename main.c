//Vinícius Meng - 0250583

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "biblioteca.h"

void help() {
    printf("\nEste programa necessita de um arquivo binario como primeiro argumento de entrada,\n");
    printf("e um nome para o um arquivo binario de saida como segundo argumento de entrada!\n");
    printf("Exemplo:> trabalhoFinal.exe NewDataPeople.dat NewDataPeopleSorted.dat\n");
    printf("\nCaso queira ler um arquivo utilize -r como primeiro argumento de entrada!\n");
    printf("Exemplo:> trabalhoFinal.exe -r NameNewDataPeopleSorted.dat\n\n");
}

int printPeopleFile(const char *fileName) {
    FILE *file;
    person personData;

    if (!(file = fopen(fileName, "r"))) {
        printf("\nNao foi possivel ler este arquivo: %s\n", fileName);
        help();
        return -3;
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
    person peopleData[20];
    int counter = 0;

    if (argc < 3) {
        help();
        return -1;
    }

    if (strcmp(argv[1], "-r") == 0) { // -r = read
        return printPeopleFile(argv[2]);
    }

    if (!(file = fopen(argv[1], "r"))) {
        printf("\nNao foi possivel ler este arquivo: %s\n", argv[1]);
        help();
        return -2;
    }

    while (fread(&personData, sizeof(person), 1, file)) {
        peopleData[counter] = personData;
        counter++;
    }

    fclose(file);

    const int arraySize = sizeof(peopleData) / sizeof(person);

    printPeopleInMemory(peopleData, arraySize, "Dados desordenados:");

    qsort(peopleData, arraySize, sizeof(person), compareName);
    printPeopleInMemory(peopleData, arraySize, "Dados ordenados por nome:");
    if (!writeSortedPeopleFile(peopleData, arraySize, "Name", argv[2])) {
        return -3;
    }

    qsort(peopleData, arraySize, sizeof(person), compareSurname);
    printPeopleInMemory(peopleData, arraySize, "Dados ordenados por sobrenome:");
    if (!writeSortedPeopleFile(peopleData, arraySize, "Surname", argv[2])) {
        return -3;
    }

    qsort(peopleData, arraySize, sizeof(person), compareAge);
    printPeopleInMemory(peopleData, arraySize, "Dados ordenados por idade:");
    if (!writeSortedPeopleFile(peopleData, arraySize, "Age", argv[2])) {
        return -3;
    }

    qsort(peopleData, arraySize, sizeof(person), compareHeight);
    printPeopleInMemory(peopleData, arraySize, "Dados ordenados por altura:");
    if (!writeSortedPeopleFile(peopleData, arraySize, "Height", argv[2])) {
        return -3;
    }

    const float ageArithmeticMean = arithmeticMeanAge(peopleData, arraySize);
    const float ageGeometricMean = geometricMeanAge(peopleData, arraySize);
    const float heightArithmeticMean = arithmeticMeanHeight(peopleData, arraySize);
    const float heightGeometricMean = geometricMeanHeight(peopleData, arraySize);

    printf("\n=====================================================\n");
    printf("Media aritmetica das idades: %.2f\n", ageArithmeticMean);
    printf("Media geometrica das idades: %.2f\n", ageGeometricMean);
    printf("Media aritmetica das alturas: %.2f\n", heightArithmeticMean);
    printf("Media geometrica das alturas: %.2f", heightGeometricMean);
    printf("\n=====================================================\n");

    return 0;
}