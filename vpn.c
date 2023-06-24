#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_MESSAGE_LEN 100

typedef struct {
    char username[20];
    char password[20];
    int isActive;
    char ipAddress[16];
} User;

typedef struct {
    User users[MAX_USERS];
    int numUsers;
} VPN;

typedef struct {
    char sender[20];
    char receiver[20];
    char message[MAX_MESSAGE_LEN];
} Message;

void addUser(VPN* vpn, const char* username, const char* password) {
    if (vpn->numUsers < MAX_USERS) {
        User newUser;
        strcpy(newUser.username, username);
        strcpy(newUser.password, password);
        newUser.isActive = 1;

        vpn->users[vpn->numUsers++] = newUser;
        printf("User '%s' added successfully.\n", username);
    } else {
        printf("Maximum number of users reached. User '%s' cannot be added.\n", username);
    }
}

User* findUserByUsername(VPN* vpn, const char* username) {
    for (int i = 0; i < vpn->numUsers; i++) {
        if (strcmp(vpn->users[i].username, username) == 0) {
            return &(vpn->users[i]);
        }
    }
    return NULL;
}

int authenticateUser(VPN* vpn, const char* username, const char* password) {
    User* user = findUserByUsername(vpn, username);
    if (user != NULL && strcmp(user->password, password) == 0 && user->isActive) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}

void encryptMessage(char* message) {
    for (int i = 0; i < strlen(message); i++) {
        message[i] += 3; // Shift each character by 3
    }
}

void decryptMessage(char* message) {
    for (int i = 0; i < strlen(message); i++) {
        message[i] -= 3; // Shift each character back by 3
    }
}

void updateIpAddress(User* user, const char* ipAddress) {
    strcpy(user->ipAddress, ipAddress);
    printf("IP Address updated for user '%s': %s\n", user->username, ipAddress);
}

void sendMessage(User* sender, User* receiver, const char* message) {
    printf("Sending message from '%s' to '%s': %s\n", sender->username, receiver->username, message);
}

void displayInbox(User* user, Message* inbox, int numMessages) {
    printf("Inbox for user '%s':\n", user->username);
    for (int i = 0; i < numMessages; i++) {
        printf("From: %s\n", inbox[i].sender);
        printf("Message: %s\n", inbox[i].message);
        printf("-----------------\n");
    }
}

int main() {
    VPN vpn;
    vpn.numUsers = 0;

    addUser(&vpn, "admin", "password");
    addUser(&vpn, "user1", "pass123");
    addUser(&vpn, "user2", "pass123");
    addUser(&vpn, "user3", "pass123");
    addUser(&vpn, "user4", "pass123");
    addUser(&vpn, "user5", "pass123");
    addUser(&vpn, "user6", "pass123");
    addUser(&vpn, "user7", "pass123");
    addUser(&vpn, "user8", "pass123");
    addUser(&vpn, "user9", "pass123");

    char username[20];
    char password[20];
    char message[MAX_MESSAGE_LEN];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    int isAuthenticated = authenticateUser(&vpn, username, password);

    if (isAuthenticated) {
        printf("\nVPN connection established!\n");

        User* currentUser = findUserByUsername(&vpn, username);

        printf("Enter a message to encrypt: ");
        scanf(" %[^\n]s", message);

        encryptMessage(message);
        printf("Encrypted message: %s\n", message);

        decryptMessage(message);
        printf("Decrypted message: %s\n", message);

        printf("\nWelcome, %s!\n", username);

        char ipAddress[16];
        printf("Enter your IP address: ");
        scanf("%s", ipAddress);
        updateIpAddress(currentUser, ipAddress);

        // Messaging feature
        int choice;
        int numMessages = 0;
        Message inbox[MAX_USERS];

        do {
            printf("\nMessaging Menu:\n");
            printf("1. Send Message\n");
            printf("2. View Inbox\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: {
                    char receiverName[20];
                    printf("Enter the receiver's username: ");
                    scanf("%s", receiverName);

                    User* receiver = findUserByUsername(&vpn, receiverName);
                    if (receiver != NULL) {
                        printf("Enter the message: ");
                        scanf(" %[^\n]s", message);

                        encryptMessage(message);
                        sendMessage(currentUser, receiver, message);
                        decryptMessage(message);

                        // Store the message in the receiver's inbox
                        Message newMessage;
                        strcpy(newMessage.sender, currentUser->username);
                        strcpy(newMessage.receiver, receiver->username);
                        strcpy(newMessage.message, message);
                        inbox[numMessages++] = newMessage;

                        printf("Message sent successfully!\n");
                    } else {
                        printf("Receiver not found. Message could not be sent.\n");
                    }
                    break;
                }
                case 2: {
                    displayInbox(currentUser, inbox, numMessages);
                    break;
                }
                case 3: {
                    printf("Exiting...\n");
                    break;
                }
                default: {
                    printf("Invalid choice. Please try again.\n");
                    break;
                }
            }
        } while (choice != 3);
    } else {
        printf("\nInvalid username or password. VPN connection failed.\n");
    }

    return 0;
}
