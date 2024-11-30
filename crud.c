#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char name[50];
    int age;
} User;

int userIdCheck(int userId)
{
    FILE *file = fopen("users.txt", "r");
    if (!file){
        printf("Error opening file.\n");
        return -1;
    }
    User user;
    while (fscanf(file, "%d,%49[^,],%d", &user.id, user.name, &user.age) == 3){
        if (user.id == userId){
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void createUser(){
    User user;
    printf("Enter UserID: ");
    scanf("%d", &user.id);
    if (userIdCheck(user.id) == 1){
        printf("Error: UserID %d already exists\n", user.id);
        return;
    }
    printf("Enter UserName: ");
    scanf(" %s", user.name);
    printf("Enter User Age: ");
    scanf("%d", &user.age);
    FILE *file = fopen("users.txt", "a");
    if (!file){
        printf("Error opening file\n");
        return;
    }
    fprintf(file, "%d,%s,%d\n", user.id, user.name, user.age);
    fclose(file);
    printf("User added successfully\n");
}
void displayUsers(){
    User user;
    FILE *f = fopen("users.txt", "r");
    if (!f){
        printf("Error opening file\n");
        return;
    }
    printf("UserId  UserName  Age\n\n");
    while (fscanf(f, "%d,%49[^,],%d", &user.id, user.name, &user.age) == 3){
        printf("   %d    %s    %d\n", user.id, user.name, user.age);
    }
    fclose(f);
}
void updateUser() {
    int userId, flag = 0;
    User user;
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    User users[100];
    int n = 0;

    while (fscanf(file, "%d,%49[^,],%d", &user.id, user.name, &user.age) == 3) {
        users[n] = user;
        n++;
    }
    fclose(file);

    printf("Enter UserID to be updated: ");
    scanf("%d", &userId);
    for (int i = 0; i < n; i++) {
        if (users[i].id == userId) {
            flag = 1;
            printf("Enter new UserName: ");
            scanf(" %49s", users[i].name);
            printf("Enter new User Age: ");
            scanf("%d", &users[i].age);
            printf("\nSuccessfully modified to:\n");
            printf("UserID: %d, UserName: %s, Age: %d\n", users[i].id, users[i].name, users[i].age);
            break;
        }
    }
    if (!flag) {
        printf("Error: UserID %d not found\nn", userId);
        return;
    }
    file = fopen("users.txt", "w");
    if (!file) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d,%s,%d\n", users[i].id, users[i].name, users[i].age);
    }
    fclose(file);
}
void deleteUser() {
    int userId, flag = 0;
    User user;
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }
    User users[100];
    int n = 0;

    while (fscanf(file, "%d,%49[^,],%d", &user.id, user.name, &user.age) == 3) {
        users[n] = user;
        n++;
    }
    fclose(file);

    printf("Enter UserID to delete: ");
    scanf("%d", &userId);

    for (int i = 0; i < n; i++) {
        if (users[i].id == userId) {
            flag = 1;
            for (int j = i; j < n - 1; j++) {
                users[j] = users[j + 1];
            }
            n--; 
            break;
        }
    }

    if (!flag) {
        printf("Error: UserID %d not found\n", userId);
        return;
    }

    file = fopen("users.txt", "w");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d,%s,%d\n", users[i].id, users[i].name, users[i].age);
    }
    fclose(file);
    printf("User with UserID %d deleted successfully\n", userId);
}

int main()
{
    int ch;
    do
    {
        printf("\n--- CRUD Operations ---\n");
        printf("1. Create User\n");
        printf("2. Display Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            createUser();
            break;
        case 2:
            displayUsers();
            break;
        case 3:
            updateUser();
            break;
        case 4:
            deleteUser();
            break;
        case 5:
            printf("Exiting.....\n");
            break;
        default:
            printf("Invalid choice\n\n");
        }
    } while (ch != 5);
    return 0;
}
