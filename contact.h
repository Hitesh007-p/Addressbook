#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct
{
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook, int options);
void editContact(AddressBook *addressBook, int options);
void deleteContact(AddressBook *addressBook, int options);
void listContacts(AddressBook *addressBook, int sortChoice);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int validate_phone(AddressBook *addressBook, char *mobile);
int validate_email(AddressBook *AddressBook, char *email_id);
#endif
