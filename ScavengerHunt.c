#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 


struct Node {
    char data[100];
    struct Node* next;
};


struct Node* head = NULL;
struct Node* tail = NULL;


struct Node* createNode(char* hint) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->data, hint);
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(char* hint) {
    struct Node* newNode = createNode(hint);

    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void display() {
    struct Node* temp = head;

    if (temp == NULL) {
        printf("Hunt failed. No clues were found.\n");
        return;
    }

    printf("\nBeginning the HUNT...\n");

    while (temp != NULL) {
        sleep(2); 
        printf("\nHunting...");
        sleep(1); 
        printf("\n FOUND!! : %s\nMoving to the next clue...\n", temp->data);
        temp = temp->next;
    }

    printf("\nHUNT SUCCESSFUL! All clues discovered!\n");
}

// Main function
int main() {
    int tot;
    char hint[100];

    printf("Enter number of clues: ");
    scanf("%d", &tot);
    getchar();

    for (int i = 0; i < tot; i++) {
        printf("Enter clue %d: ", i + 1);
        fgets(hint, sizeof(hint), stdin);
        hint[strcspn(hint, "\n")] = '\0';
        insertAtEnd(hint);
    }

    display();

    return 0;
}
