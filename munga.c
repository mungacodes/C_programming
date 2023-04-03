#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// To limit the number of entries
#define MAX_USERS 100
#define MAX_NAME_LEN 50
#define MAX_ID_LEN 50
#define MAX_CONTACT_LEN 50
#define MAX_EMAIL_LEN 50
#define MAX_LOCATION_LEN 50
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

// User struct
typedef struct {
    char name[MAX_NAME_LEN];
    char id[MAX_ID_LEN];
    char contact[MAX_CONTACT_LEN];
    char email[MAX_EMAIL_LEN];
    char location[MAX_LOCATION_LEN];
    float balance;
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

// transactional functions
void register_user(User *users, int *num_users);
int login(User *users, int num_users);
void deposit(User *user);
void withdraw(User *user);
void check_balance(User *user);

int main() {
    User users[MAX_USERS];
    int num_users = 0;
    int choice;

    while (1) {
        printf("Welcome to MungaBanking service. Please select an option to proceed:\n");
        printf("1. To Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user(users, &num_users);
                break;
            case 2: {
                int user_index = login(users, num_users);
                // check if the user exists
                if (user_index != -1) {
                    while (1) {
                        printf("What do you want to do?\n");
                        printf("1. Deposit\n");
                        printf("2. Withdraw\n");
                        printf("3. Check balance\n");
                        printf("4. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1:
                                deposit(&users[user_index]);
                                break;
                            case 2:
                                withdraw(&users[user_index]);
                                break;
                            case 3:
                                check_balance(&users[user_index]);
                                break;
                            case 4:
                                printf("Logout successful! THANK YOU FOR BANKING WITH US\n");
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }

                        if (choice == 4) {
                            break;
                        }
                    }
                }
                break;
            }
            case 3:
                printf("Thank you for transacting with us!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Register a new user
void register_user(User *users, int *num_users) {
    if (*num_users == MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    User new_user;
    printf("Thank you for choosing Munga Services please proceed to register\n");
    // Get user information
    printf("Fullname: ");
    scanf("%s", new_user.name);

    printf("National ID number/ Passport Number: ");
    scanf("%s", new_user.id);

    printf("Contact: ");
    scanf("%s", new_user.contact);

    printf("Email address: ");
    scanf("%s", new_user.email);

    printf("Location: ");
    scanf("%s", new_user.location);

    printf("Please fill in the details to be used for Log in: \n");
    printf("Preffered Username: ");
    scanf("%s", new_user.username);

    printf("Preffered Password: ");
    scanf("%s", new_user.password);

    // initiates the users balance
    new_user.balance = 0.0;

    // Add new user to array
    users[*num_users] = new_user;
    (*num_users)++;

    printf("User registered successfully!\n");
}

// Log in a user
int login(User *users, int num_users) {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    // checking for user in the set of users
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful!\n");
            return i; // Return index of logged in user
        }
    }

    printf("Invalid username or password. Kindly check and try again\n");
    return -1; // Return -1 if login failed
}
// Deposit money into a user's account
void deposit(User *user) {
    float amount;

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }
    // Update the users amount 
    user->balance += amount;

    printf("Deposit successful! New balance: %.2f\n", user->balance);
}

// Withdraw money from a user's account
void withdraw(User *user) {
    float amount;

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0 || amount > user->balance) {
        printf("Invalid amount. Your balance is: %.2f\n", user->balance);
        return;
    }

    user->balance -= amount;

    printf("Withdrawal successful! New balance: %.2f\n", user->balance);
}

// Check the balance of a user's account
void check_balance(User *user) {
    printf("Your account balance is: %.2f\n", user->balance);
}

// Write user information to file called data.txt
void write_user_data(User *users, int num_users) {
    FILE *fp;
    fp = fopen("data.txt", "w");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < num_users; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%.2f,%s,%s\n", users[i].name, users[i].id, users[i].contact,
                users[i].email, users[i].location, users[i].balance, users[i].username, users[i].password);
    }

    fclose(fp);
}