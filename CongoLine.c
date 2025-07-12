#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    char *data;
    struct Node* pre;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;

// Enqueue
void queuePush(char* person) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = malloc(strlen(person) + 1);
    strcpy(newNode->data, person);
    newNode->pre = tail;
    newNode->next = NULL;

    if (tail == NULL)
        head = newNode;
    else
        tail->next = newNode;
    
    tail = newNode;
}

// Dequeue specific node
void queuePop(struct Node* temp) {
    if (temp == head && temp == tail) {
        free(temp->data);
        free(temp);
        head = tail = NULL;
    }
    else if (temp == head) {
        head = temp->next;
        head->pre = NULL;
        free(temp->data);
        free(temp);
    }
    else if (temp == tail) {
        tail = temp->pre;
        tail->next = NULL;
        free(temp->data);
        free(temp);
    }
    else {
        temp->next->pre = temp->pre;
        temp->pre->next = temp->next;
        free(temp->data);
        free(temp);
    }
}

// Search & remove
int search(char* rem_person) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data, rem_person) == 0) {
            queuePop(temp);
            printf("%s removed from the Congo line.\n", rem_person);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// Display queue
void display() {
    struct Node* temp = head;
    if (temp == NULL) {
        printf("Congo line is empty.\n");
        return;
    }

    printf("Congo Line: ");
    while (temp != NULL) {
        printf("%s -> ", temp->data);
        temp = temp->next;
    }
    printf("End\n");
}

int main() {
    char person[50], rem_person[50];
    int choice;

    printf("🎉 LET'S START CONGO LINE DANCING 🎉\n");

    // Print menu only once
    printf("\n--- MENU ---\n");
    printf("1. Add person to Congo line\n");
    printf("2. Show Congo line\n");
    printf("3. Remove person from Congo line\n");
    printf("4. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                printf("Enter name of person joining: ");
                fgets(person, sizeof(person), stdin);
                person[strcspn(person, "\n")] = '\0'; // remove newline
                queuePush(person);
                break;

            case 2:
                display();
                break;

            case 3:
                printf("Enter name of person to remove: ");
                fgets(rem_person, sizeof(rem_person), stdin);
                rem_person[strcspn(rem_person, "\n")] = '\0';
                if (!search(rem_person))
                    printf("Person not found in Congo line.\n");
                break;

            case 4:
                printf("Congo line dancing ended. Bye!\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
