#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    struct Contact* next;
};

struct Contact* createContact(char name[], char phone[]) {
    struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = NULL;
    return newContact;
}

void addContact(struct Contact** head, char name[], char phone[]) {
    struct Contact* newContact = createContact(name, phone);

    // If the list is empty or the new contact comes before the head
    if (*head == NULL || strcmp(newContact->name, (*head)->name) < 0) {
        newContact->next = *head;
        *head = newContact;
    } else {
        // Traverse the list to find the correct position
        struct Contact* current = *head;
        while (current->next != NULL && strcmp(newContact->name, current->next->name) > 0) {
            current = current->next;
        }

        // Insert the new contact at the correct position
        newContact->next = current->next;
        current->next = newContact;
    }

    printf("Contact added successfully!\n");
}

void displayContacts(struct Contact* head) {
    if (head == NULL) {
        printf("Contact manager is empty.\n");
        return;
    }

    printf("Contacts:\n");
    while (head != NULL) {
        printf("Name: %s, Phone: %s\n", head->name, head->phone);
        head = head->next;
    }
}

void searchContact(struct Contact* head, char name[]) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            printf("Contact found!\n");
            printf("Name: %s, Phone: %s\n", head->name, head->phone);
            return;
        }
        head = head->next;
    }

    printf("Contact not found.\n");
}

void deleteContact(struct Contact** head, char name[]) {
    struct Contact* current = *head;
    struct Contact* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            printf("Contact deleted successfully!\n");
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Contact not found.\n");
}

void freeContacts(struct Contact* head) {
    struct Contact* current = head;
    struct Contact* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct Contact* contactManager = NULL;
    int choice;
    char name[50];
    char phone[15];

    do {
        printf("\nContact Manager Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter phone: ");
                scanf("%s", phone);
                addContact(&contactManager, name, phone);
                break;
            case 2:
                displayContacts(contactManager);
                break;
            case 3:
                printf("Enter name to search: ");
                scanf("%s", name);
                searchContact(contactManager, name);
                break;
            case 4:
                printf("Enter name to delete: ");
                scanf("%s", name);
                deleteContact(&contactManager, name);
                break;
            case 5:
                freeContacts(contactManager);
                printf("Exiting Contact Manager. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}
