#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Node {
    char* data;
    struct Node* next;
    struct Node* pre;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void insertAtBeg(char *song) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Not enough space. Delete some files.\n");
        return;
    }

    newNode->data = (char*)malloc(strlen(song) + 1);
    strcpy(newNode->data, song);
    newNode->next = head;
    newNode->pre = NULL;

    if (head == NULL)
        tail = newNode;
    else
        head->pre = newNode;

    head = newNode;
}

void displaySongs(char *p_name) {
    if (head == NULL) {
        printf("\n-Playlist is empty-\n");
        return;
    }

    printf("\nPlaylist: %s", p_name);
    struct Node* temp = head;
    int i = 1;
    while (temp != NULL) {
        printf("%d. %s", i++, temp->data);
        temp = temp->next;
    }
}

void deleteAtBeg() {
    if (head == NULL) return;
    struct Node* temp = head;

    if (head->next == NULL) {
        free(head->data);
        free(head);
        head = tail = NULL;
    } else {
        head = head->next;
        head->pre = NULL;
        free(temp->data);
        free(temp);
    }
}

void deleteAtEnd() {
    if (tail == NULL) return;
    struct Node* temp = tail;

    if (tail->pre == NULL) {
        free(tail->data);
        free(tail);
        head = tail = NULL;
    } else {
        tail = tail->pre;
        tail->next = NULL;
        free(temp->data);
        free(temp);
    }
}

void deleteSong(char *s_song) {
    struct Node* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->data, s_song) == 0) {
            if (temp == head) {
                deleteAtBeg();
            } else if (temp == tail) {
                deleteAtEnd();
            } else {
                temp->pre->next = temp->next;
                temp->next->pre = temp->pre;
                free(temp->data);
                free(temp);
            }
            printf("Deleted song: %s", s_song);
            return;
        }
        temp = temp->next;
    }
    printf("Song not found.\n");
}

void searchAndDelete() {
    char s_song[100];
    printf("Enter song name to search (case-sensitive): ");
    getchar(); // clear leftover newline
    fgets(s_song, 100, stdin);

    struct Node* temp = head;
    bool found = false;
    while (temp != NULL) {
        if (strcmp(temp->data, s_song) == 0) {
            printf("Song found: %s", temp->data);
            printf("Do you want to delete this song? (1/0): ");
            int ch;
            scanf("%d", &ch);
            if (ch == 1)
                deleteSong(s_song);
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found)
        printf("Song not in playlist.\n");
}

int main() {
    char p_name[100];
    printf("Enter playlist name: ");
    fgets(p_name, 100, stdin);

    int choice;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Add Song\n");
        printf("2. Display Songs\n");
        printf("3. Search and Delete Song\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at End\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1: {
                char song[100];
                printf("Enter song name: ");
                fgets(song, 100, stdin);
                insertAtBeg(song);
                break;
            }

            case 2:
                displaySongs(p_name);
                break;

            case 3:
                searchAndDelete();
                break;

            case 4:
                deleteAtBeg();
                printf("First song deleted.\n");
                break;

            case 5:
                deleteAtEnd();
                printf("Last song deleted.\n");
                break;

            case 6:
                printf("Exiting playlist manager.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
