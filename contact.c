#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

// phone number validation
int validate_phone(AddressBook *addressBook, char *phone_number)
{
    int length = strlen(phone_number); // check length for validation

    if (length != 10)
    {
        return 0;
    }

    for (int i = 0; i < length; i++) // this loop use for the phone number only have numeric caracter
    {
        if (phone_number[i] < '0' || phone_number[i] > '9')
        {
            return 0;
        }
    }

    for (int i = 0; i < addressBook->contactCount; i++) // this loop comparing with save contacts if the phone number match then invalid number
    {
        if (strcmp(phone_number, addressBook->contacts[i].phone) == 0)
        {
            return 2;
        }
    }

    return 1;
}

// Email validation
int validate_email(AddressBook *addressBook, char *email_id)
{
    int length = strlen(email_id);

    if (length == 0)
    {
        return 0;
    }

    // Convert uppercase to lowercase
    for (int i = 0; i < length; i++)
    {
        if (email_id[i] >= 'A' && email_id[i] <= 'Z')
        {
            email_id[i] = email_id[i] + 32;
        }
    }

    int atcount = 0;
    int atindex = 0;
    int dotcount = 0;
    int dotindex = 0;

    for (int i = 0; i < length; i++)
    {
        if (email_id[i] == ' ') // check for space
        {
            return 0;
        }

        if (email_id[i] == '@') // check for @ index and count
        {
            atcount++;
            atindex = i;
        }

        if (email_id[i] == '.') // check for . index and count
        {
            dotcount++;
            dotindex = i;

            // Safe dot checks
            if (i == 0) // check first position
                return 0;

            if (i + 1 < length && email_id[i + 1] == '@') // checks dot before @
            {
                return 0;
            }

            if (i - 1 >= 0 && email_id[i - 1] == '@') // checks dot after @
            {
                return 0;
            }

            if (i > 0 && email_id[i - 1] == '.') // its check consecutive dots (dot after dot)
            {
                return 0;
            }
        }

        if (!((email_id[i] >= 'a' && email_id[i] <= 'z') || (email_id[i] >= '0' && email_id[i] <= '9') || email_id[i] == '@' || email_id[i] == '.')) // this checks if it is not that character in email then invalid
        {
            return 0;
        }
    }

    if (!((email_id[0] >= 'a' && email_id[0] <= 'z') || (email_id[0] >= '0' && email_id[0] <= '9'))) // this checks starting character of email
    {
        return 0;
    }

    if (atcount != 1 || dotcount < 1) // this check @ count and . Count
    {
        return 0;
    }

    if (atindex <= 0 || atindex == length - 1 || dotindex == length - 1 || dotindex <= atindex) // this checks positions last first and .
    {
        return 0;
    }

    // Duplicate check
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email_id) == 0) // this comparing for duplicates
        {
            return 2;
        }
    }

    return 1;
}

// list contact function
void listContacts(AddressBook *addressBook, int sortChoice)
{
    // Sort contacts based on the chosen criteria

    printf("\nSort list Menu:\n");
    printf("1. Sort by Name\n");
    printf("2. Sort by Phone Number\n");
    printf("3. Sort by Email\n");
    printf("\nEnter your sortChoice: ");
    scanf("%d", &sortChoice);

    for (int i = 0; i < addressBook->contactCount - 1; i++) // outer loop for sort
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) // inner loop for sort
        {
            if (sortChoice == 1)
            {
                if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) // bubble sort for name
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
            else if (sortChoice == 2)
            {
                if (strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone) > 0) // bubble sort for phone
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
            else if (sortChoice == 3)
            {
                if (strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0) // bubble sort for email
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-15s | %-25s |\n", "Index", "Name", "Phone", "Email"); // - for left alignment 5 is width s string
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-5d | %-20s | %-15s | %-25s |\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email); // - for left alignment 5 is width d integer
    }
    printf("-------------------------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

// create contact Function
void createContact(AddressBook *addressBook)
{
    char user[100];
    char mobile[20];
    char email_id[100];

    int valid;
    int mobile_ret;
    int email_ret;
    do
    {
        valid = 1;
        printf("Enter the Contact name : ");
        scanf(" %[^\n]", user);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, user) == 0) // compare for duplicate name
            {
                printf("Error: Name already exists\n");
                valid = 0;
                break;
            }
        }

    } while (valid != 1);
    do
    {
        printf("Enter phone number : ");
        scanf("%s", mobile);

        mobile_ret = validate_phone(addressBook, mobile); // calls mobile validation function for number validate

        if (mobile_ret == 0)
        {
            printf("Error: Enter a valid number\n");
        }
        else if (mobile_ret == 2)
        {
            printf("Error: Phone number already exists\n");
        }

    } while (mobile_ret != 1);
    do
    {
        printf("Enter Email Id : ");
        scanf("%s", email_id);

        email_ret = validate_email(addressBook, email_id); // call email validation function for email validate

        if (email_ret == 0)
        {
            printf("Error: Invalid email format\n");
        }
        else if (email_ret == 2)
        {
            printf("Error: Email already exists\n");
        }

    } while (email_ret != 1);

    // Save contact
    strcpy(addressBook->contacts[addressBook->contactCount].name, user); // this is for copy from variable to contact
    strcpy(addressBook->contacts[addressBook->contactCount].phone, mobile);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email_id);
    addressBook->contactCount++; // this contact count

    printf("Contact created successfully !!\n");
}

// search contact function
int searchContact(AddressBook *addressBook, int options)
{
    /* Define the logic for search */

    printf("\nSearch Contact Menu:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email\n");
    printf("\nEnter your searchChoice: ");
    scanf("%d", &options);

    char search[50];
    if (options == 1)
    {
        printf("Enter the search Name : ");
    }
    else if (options == 2)
    {
        printf("Enter the search Phone Number : ");
    }
    else if (options == 3)
    {
        printf("Enter the search Email : ");
    }
    scanf(" %[^\n]", search);

    int flag = 0;

    for (int i = 0; i < addressBook->contactCount; i++) // this loop for comparing contact for serching
    {
        if (options == 1)
        {
            if (strcmp(search, addressBook->contacts[i].name) == 0) // compare condition
            {
                printf("Index = %d, name = %s, phone = %s, email = %s", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                flag = 1;
                break;
            }
        }
        else if (options == 2)
        {
            if (strcmp(search, addressBook->contacts[i].phone) == 0) // compare condition
            {
                printf("Index = %d, name = %s, phone = %s, email = %s", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                flag = 1;
                break;
            }
        }
        else if (options == 3)
        {
            if (strcmp(search, addressBook->contacts[i].email) == 0) // compare condition
            {
                printf("Index = %d, name = %s, phone = %s, email = %s", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                flag = 1;
                break;
            }
        }
    }

    if (flag == 0)
    {
        printf("Not Found the Contact Enter the Valid name, phone or contact\n");
    }

    return flag;
}

// edit contact function
void editContact(AddressBook *addressBook, int options)
{
    int search = searchContact(addressBook, options); // calling search contact fuction for edit

    if (search != 1) // check call are work or not
    {
        printf("Error : Cannot able to edit contact\n");
        return;
    }

    int index;
    printf("\nEnter the index of contact to Edit : ");
    scanf("%d", &index);

    index = index - 1;

    if (index < 0 || index >= addressBook->contactCount) // this for check enter index less than 0 or index greater than contactcount
    {
        printf("Error: Invalid index\n");
        return;
    }

    printf("\nEdit Contact Menu:\n");
    printf("1. Edit Name\n");
    printf("2. Edit Phone Number\n");
    printf("3. Edit Email\n");
    printf("\nEnter your Edit Choice: ");

    int choice;
    scanf("%d", &choice);

    char edit[100];
    int status;

    if (choice == 1)
    {
        do
        {
            printf("Enter new Name: ");
            scanf(" %[^\n]", edit);

            status = 1;

            for (int i = 0; i < addressBook->contactCount; i++) // this loop for comparing
            {
                if (strcmp(addressBook->contacts[i].name, edit) == 0) // comparing condition
                {
                    printf("Error: Name already exists\n");
                    status = 0;
                    break;
                }
            }

        } while (status != 1);

        strcpy(addressBook->contacts[index].name, edit); // this is for copy to contacts
        printf("Name edited successfully !!\n");
    }
    else if (choice == 2)
    {
        do
        {
            printf("Enter new phone number: ");
            scanf("%s", edit);

            status = validate_phone(addressBook, edit); // call validate phone function for validation

            if (status == 0)
            {
                printf("Error: Phone number must be 10 digits only\n");
            }
            else if (status == 2)
            {
                printf("Error: Phone number already exists\n");
            }

        } while (status != 1);

        strcpy(addressBook->contacts[index].phone, edit);
        printf("Phone number edited successfully !!\n");
    }
    else if (choice == 3)
    {
        do
        {
            printf("Enter new Email ID: ");
            scanf("%s", edit);

            status = validate_email(addressBook, edit); // call validate email for validation

            if (status == 0)
            {
                printf("Error: Invalid email format\n");
            }
            else if (status == 2)
            {
                printf("Error: Email already exists\n");
            }

        } while (status != 1);

        strcpy(addressBook->contacts[index].email, edit);
        printf("Email address edited successfully !!\n");
    }

    else
    {
        printf("Invalid edit choice\n");
    }
}

// delete contact function
void deleteContact(AddressBook *addressBook, int options)
{
    /* Define the logic for deletecontact */
    int ret = searchContact(addressBook, options); // call search contact function for serching which contact we need to delete

    if (ret == 1)
    {
        int index;
        printf("\nEnter the index of contact to delete : ");
        scanf("%d", &index);

        index = index - 1;

        for (int i = index; i < addressBook->contactCount; i++) // this loop for delete contact
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--; // after delete decrement count value

        printf("Contact Deleted Succesfully !!\n");
    }
    else
    {
        printf("Error : Cannot able to delete contact\n");
    }

    return;
}
