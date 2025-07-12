#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* pre;
};

struct Node* head = NULL;
struct Node* tail = NULL;

// Make the list circular
void makeCircular() {
    if (head != NULL && tail != NULL) {
        tail->next = head;
        head->pre = tail;
    }
}

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->pre = NULL;
    return newNode;
}

// Insert node at the end
void insertAtEnd(int data) {
    struct Node* newNode = createNode(data);
    if (tail == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->pre = tail;
        tail = newNode;
    }
}

// Delete a node and return its data
int deleteNode(struct Node* cur) {
    int player = cur->data;

    if (cur == head && cur == tail) {
        head = tail = NULL;
    } else if (cur == head) {
        cur->next->pre = tail;
        head = cur->next;
        tail->next = head;
    } else if (cur == tail) {
        cur->pre->next = head;
        tail = cur->pre;
        head->pre = tail;
    } else {
        cur->next->pre = cur->pre;
        cur->pre->next = cur->next;
    }

    free(cur);
    return player;
}

// Eliminate function returns the last remaining player
int eliminate(int key) {
    int player = -1;
    int k = key;
    struct Node* temp;
    struct Node* cur = head;

    while (cur->next != cur) {
        key = k;
        while (key - 1 > 0) {
            cur = cur->next;
            key--;
        }
        temp = cur->next;
        player = deleteNode(cur);
        cur = temp;
    }

    player = deleteNode(cur);  // Delete the last remaining node
    return player;
}

int main() {
    int tot, key;
    printf("Enter total number of players: ");
    scanf("%d", &tot);

    for (int i = 1; i <= tot; i++) {
        insertAtEnd(i);
    }

    makeCircular();

    printf("Enter key: ");
    scanf("%d", &key);

    int winner = eliminate(key);
    printf("Last remaining player: %d\n", winner);

    return 0;
}
