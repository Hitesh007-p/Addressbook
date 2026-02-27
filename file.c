#include <stdio.h>
#include "file.h"
#include <stdlib.h>

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp; // File Pointer to poiniting file starting character

    fp = fopen("contact.csv", "w"); // open file

    if (fp == NULL) // validation for file itd NULL or not if it is NULL terminate the program
    {
        printf("Error: to find file");
        return;
    }
    printf("File opened!!\n");

    fprintf(fp, "%d\n", addressBook->contactCount); // This is for contact count

    for (int i = 0; i < addressBook->contactCount; i++) // This loop for save conatct to contact.csv file
    {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fp); // close file

    exit(0);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp; // File Pointer to poiniting file starting character

    fp = fopen("contact.csv", "r");

    if (fp == NULL) // validation for file itd NULL or not if it is NULL terminate the program
    {
        printf("Error: to find file");
        return;
    }
    printf("File opened!!\n");

    fscanf(fp, "%d\n", &addressBook->contactCount); // This is for contact count

    for (int i = 0; i < addressBook->contactCount; i++) // This loop for load conatct to contact.csv file
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fp);
}
