#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include<ctype.h>

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *file = fopen("address_book.txt", "r");
    if (file == NULL) 
    {
        return;
    }

    addressBook->contactCount = 0;
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) != EOF) 
    {
        addressBook->contactCount++;
    }
    fclose(file);
}

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *file = fopen("address_book.txt", "w");
    if (file == NULL)
    {
        printf("Error: Contact has not been saved\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
    fclose(file);
}


void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts found\n");
        return;
    }

    // Print header with proper alignment
    printf("%-30s %-20s %-30s\n", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------------------------\n");

    // Print each contact with proper alignment
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-30s %-20s %-30s\n", 
               addressBook->contacts[i].name, 
               addressBook->contacts[i].phone, 
               addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}


void createContact(AddressBook *addressBook)
 {
    char name1[50];
    char phone1[20];
    char email1[50];

    // Get the name and check for duplicates
    printf("Enter the name: ");
    getchar();
    // fgets(name1, sizeof(name1), stdin);
    // name1[strcspn(name1, "\n")] = '\0'; // Remove newline character from fgets
    scanf("%[^\n]",name1);


    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(name1, addressBook->contacts[i].name) == 0) 
        {
            printf("Error: Name already exists.\n");
            return; 
        }
    }

    // Get the phone number and validate its length (10 digits)
    printf("Enter Mobile Number: ");
    getchar();
    // fgets(phone1, sizeof(phone1), stdin);
    // phone1[strcspn(phone1, "\n")] = '\0'; // Remove newline character from fgets/
    scanf("%[^\n]",phone1);

    if (strlen(phone1) != 10 ) 
    {
        printf("Error: Mobile number must be 10 digits.\n");
        return;
    }

    // Check if the phone number already exists
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(phone1, addressBook->contacts[i].phone) == 0) 
        {
            printf("Error: Mobile number already exists.\n");
            return; 
        }
    }

    // Get the email and validate the format (must contain '@' and '.')
    printf("Enter the email: ");
    //fgets(email1, sizeof(email1), stdin);
   // email1[strcspn(email1, "\n")] = '\0'; // Remove newline character from fgets
   getchar();
    scanf("%[^\n]",email1);
    if (strchr(email1, '@') == NULL || strchr(email1, '.') == NULL) 
    {
        printf("Error: Invalid email address.\n");
        return;
    }

    // Check if the email already exists
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(email1, addressBook->contacts[i].email) == 0) 
        {
            printf("Error: Email already exists.\n");
            return; 
        }
    }

    // Add the new contact to the address book
    int count = addressBook->contactCount;
    strcpy(addressBook->contacts[count].name, name1);
    strcpy(addressBook->contacts[count].phone, phone1);
    strcpy(addressBook->contacts[count].email, email1);

    // Increase the contact count
    addressBook->contactCount++;

    // Success message
    printf("Contact created successfully!\n");
}

void searchContact(AddressBook *addressBook) 
{
    printf("Enter which contact you want based on 1.Name, 2.Phone, 3.Email ID: ");
    int option;
    scanf("%d", &option);
    int flag = 0;

    switch(option)
    {
        case 1:
        {
            char str1name[50];
            printf("Enter the name : ");
            scanf(" %[^\n]", str1name);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].name,str1name))
                {
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    flag = 1;
                    
                }
            }
            break;
        }
        case 2:
        {
            char str1phone[20];
            printf("Enter the phone: ");
            getchar();
            scanf("%[0-9]", str1phone);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].phone,str1phone)) 
                {
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    flag = 1;
                   
                }
            }
            break;
        }
        case 3:
        {
            char str1email[50];
            printf("Enter the email id: ");
            getchar();
            scanf(" %[^\n]", str1email);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].email,str1email))
                {
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    flag = 1;
                    
                }
            }
            break;
        }
        default:
            printf("Invalid option selected\n");
            break;
    }

    if(flag == 0)
    {
        printf("Contact not found\n");
    }
}

void editContact(AddressBook *addressBook) 
{
    int opt;
    printf("Enter the option\n1. Name\n2. Email\n");
    scanf("%d", &opt);

    switch (opt) 
    {
        case 1: 
        {
            char e_name[50];
            printf("Enter the name: ");
            getchar();  // To consume newline
            scanf("%[^\n]", e_name);

            int arr[15], count = 0;
            printf("All possible contacts:\n");
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].name, e_name))
                 {
                    arr[count] = i;
                    count++;
                    printf("%d. %s\t%s\t%s\n", count, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                }
            }

            if (count > 0) 
            {
                int choice;
                printf("Enter the choice for editing the contact: ");
                scanf("%d", &choice);

                if (choice > 0 && choice <= count) 
                {
                    int idx = arr[choice - 1];
                    int option1;
                    printf("Enter the option for editing the contact:\n1. Name\n2. Phone No\n3. Email\n");
                    scanf("%d", &option1);

                    switch (option1) 
                    {
                        case 1: {
                            char new_name[50];
                            int flag1 = 0;
                            do {
                                printf("Enter the new name: ");
                                getchar();
                                scanf("%[^\n]", new_name);
                                
                                flag1 = 0;
                                for (int j = 0; j < addressBook->contactCount; j++)
                                 {
                                    if (strcmp(addressBook->contacts[j].name, new_name) == 0) 
                                    {
                                        flag1 = 1;
                                        printf("Name already exists, please try again!\n");
                                        break;
                                    }
                                }

                                if (!flag1) {
                                    strcpy(addressBook->contacts[idx].name, new_name);
                                    printf("Name updated successfully!\n");
                                }
                            } 
                            while (flag1);
                            break;
                        }
                        case 2:
                         {
                            char new_phone[20];
                            int flag = 0;
                            do {
                                printf("Enter the new phone number: ");
                                getchar();
                                scanf("%[^\n]", new_phone);

                                if (strlen(new_phone) != 10 || !isdigit(new_phone[0])) 
                                {
                                    printf("Invalid phone number, please try again!\n");
                                    flag = 1;
                                } 
                                else 
                                {
                                    flag = 0;
                                    for (int j = 0; j < addressBook->contactCount; j++) 
                                    {
                                        if (strcmp(addressBook->contacts[j].phone, new_phone) == 0) 
                                        {
                                            flag = 1;
                                            printf("Phone number already exists, please try again!\n");
                                            break;
                                        }
                                    }
                                    if (!flag) 
                                    {
                                        strcpy(addressBook->contacts[idx].phone, new_phone);
                                        printf("Phone number updated successfully!\n");
                                    }
                                }
                            }
                             while (flag);
                            break;
                        }
                        case 3:
                         {
                            char new_email[50];
                            int flag3 = 0;
                            do {
                                printf("Enter the new email: ");
                                getchar();
                                scanf("%[^\n]", new_email);

                                flag3 = 0;
                                for (int j = 0; j < addressBook->contactCount; j++) 
                                {
                                    if (strcmp(addressBook->contacts[j].email, new_email) == 0) 
                                    {
                                        flag3 = 1;
                                        printf("Email already exists, please try again!\n");
                                        break;
                                    }
                                }
                                if (flag3 == 0 && (strchr(new_email, '@') == NULL || strchr(new_email, '.') == NULL))
                                 {
                                    printf("Invalid email format, please try again!\n");
                                    flag3 = 1;
                                }
                                if (!flag3) 
                                {
                                    strcpy(addressBook->contacts[idx].email, new_email);
                                    printf("Email updated successfully!\n");
                                }
                            }
                             while (flag3);
                            break;
                        }
                        default:
                            printf("Invalid selection for editing!\n");
                    }
                } 
                else 
                {
                    printf("Invalid choice!\n");
                }
            } 
            else 
            {
                printf("No contacts found matching the name!\n");
            }
            break;
        }
        case 2: 
        {
            char e_email[50];
            printf("Enter the email: ");
            getchar();
            scanf("%[^\n]", e_email);

            int arr[15], count = 0;
            printf("All possible contacts:\n");
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].email, e_email)) 
                {
                    arr[count] = i;
                    count++;
                    printf("%d. %s\t%s\t%s\n", count, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                }
            }

            if (count > 0)
             {
                int choice;
                printf("Enter the choice for editing the contact: ");
                scanf("%d", &choice);

                if (choice > 0 && choice <= count)
                 {
                    int idx = arr[choice - 1];
                    int option2;
                    printf("Enter the option for editing the contact:\n1. Name\n2. Phone No\n3. Email\n");
                    scanf("%d", &option2);

                    switch (option2) {
                        case 1: {
                            char new_name[50];
                            int flag2 = 0;
                            do {
                                printf("Enter the new name: ");
                                getchar();
                                scanf("%[^\n]", new_name);

                                flag2 = 0;
                                for (int j = 0; j < addressBook->contactCount; j++) {
                                    if (strcmp(addressBook->contacts[j].name, new_name) == 0) 
                                    {
                                        flag2 = 1;
                                        printf("Name already exists, please try again!\n");
                                        break;
                                    }
                                }

                                if (!flag2) {
                                    strcpy(addressBook->contacts[idx].name, new_name);
                                    printf("Name updated successfully!\n");
                                }
                            } while (flag2);
                            break;
                        }
                        case 2: {
                            char new_phone[20];
                            int flag = 0;
                            do {
                                printf("Enter the new phone number: ");
                                getchar();
                                scanf("%[^\n]", new_phone);

                                if (strlen(new_phone) != 10 || !isdigit(new_phone[0]))
                                 {
                                    printf("Invalid phone number, please try again!\n");
                                    flag = 1;
                                } else
                                 {
                                    flag = 0;
                                    for (int j = 0; j < addressBook->contactCount; j++)
                                     {
                                        if (strcmp(addressBook->contacts[j].phone, new_phone) == 0) 
                                        {
                                            flag = 1;
                                            printf("Phone number already exists, please try again!\n");
                                            break;
                                        }
                                    }
                                    if (!flag) 
                                    {
                                        strcpy(addressBook->contacts[idx].phone, new_phone);
                                        printf("Phone number updated successfully!\n");
                                    }
                                }
                            }
                             while (flag);
                            break;
                        }
                        case 3:
                         {
                            char new_email[50];
                            int flag3 = 0;
                            do {
                                printf("Enter the new email: ");
                                getchar();
                                scanf("%[^\n]", new_email);

                                flag3 = 0;
                                for (int j = 0; j < addressBook->contactCount; j++) 
                                {
                                    if (strcmp(addressBook->contacts[j].email, new_email) == 0) 
                                    {
                                        flag3 = 1;
                                        printf("Email already exists, please try again!\n");
                                        break;
                                    }
                                }
                                if (flag3 == 0 && (strchr(new_email, '@') == NULL || strchr(new_email, '.') == NULL))
                                 {
                                    printf("Invalid email format, please try again!\n");
                                    flag3 = 1;
                                }
                                if (!flag3) 
                                {
                                    strcpy(addressBook->contacts[idx].email, new_email);
                                    printf("Email updated successfully!\n");
                                }
                            } 
                            while (flag3);
                            break;
                        }
                        default:
                            printf("Invalid selection for editing!\n");
                    }
                } 
                else
                {
                    printf("Invalid choice!\n");
                }
            } 
            else 
            {
                printf("No contacts found matching the email!\n");
            }
            break;
        }
        default:
            printf("Invalid option!\n");
    }
}

void deleteContact(AddressBook *addressBook)
 {
    int choice;
    printf("Choose option to delete:\n1. Name\n2. Phone Number\n3. Email ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();  // To consume newline

    switch (choice)
     {
        case 1: 
        {
            char d_name[50];
            printf("Enter the name to delete: ");
            scanf("%[^\n]", d_name);

            int found = 0;
            printf("All possible contacts:\n");
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].name, d_name)) 
                {
                    printf("%d. %s\t%s\t%s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    found = 1;
                    // Shift elements to remove the contact
                    for (int j = i; j < addressBook->contactCount - 1; j++) 
                    {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                    break;
                }
            }
            if (!found) 
            {
                printf("No contacts found!\n");
            }
            break;
        }
        case 2: 
        {
            char d_phone[20];
            printf("Enter the phone number to delete: ");
            scanf("%[^\n]", d_phone);

            int found = 0;
            printf("All possible contacts:\n");
            for (int i = 0; i < addressBook->contactCount; i++)
             {
                if (strstr(addressBook->contacts[i].phone, d_phone))
                 {
                    printf("%d. %s\t%s\t%s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    found = 1;
                    // Shift elements to remove the contact
                    for (int j = i; j < addressBook->contactCount - 1; j++) 
                    {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                    break;
                }
            }
            if (!found) 
            {
                printf("No contacts found!\n");
            }
            break;
        }
        case 3:
         {
            char d_email[50];
            printf("Enter the email ID to delete: ");
            scanf("%[^\n]", d_email);

            int found = 0;
            printf("All possible contacts:\n");
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].email, d_email))
                 {
                    printf("%d. %s\t%s\t%s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    found = 1;
                    // Shift elements to remove the contact
                    for (int j = i; j < addressBook->contactCount - 1; j++) 
                    {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                    break;
                }
            }
            if (!found) 
            {
                printf("No contacts found!\n");
            }
            break;
        }
        default:
            printf("Invalid choice!\n");
    }
}