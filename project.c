#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD "codingage"
#define FILENAME "diary.txt"
#define TEMPFILE "temp.txt"

struct Diary {
    char date[20];
    char title[50];
    char content[500];
};

void checkPassword();
void menu();
void addEntry();
void viewEntries();
void editEntry();
void deleteEntry();

int main() {
    checkPassword();
    menu();
    return 0;
}

void checkPassword() {
    char pass[20];
    printf("Enter Password: ");
    scanf("%s", pass);
    if (strcmp(pass, PASSWORD) != 0) {
        printf("wrong password!\n");
        exit(0);
    }
    printf("Access Granted!\n\n");
}

void menu() {
    int choice;
    do {
        printf("\n--- Digital Diary System ---\n");
        printf("1. Add Entry\n");
        printf("2. View Entries\n");
        printf("3. Edit Entry\n");
        printf("4. Delete Entry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // clear newline

        switch (choice) {
            case 1: addEntry(); 
            break;
            case 2: viewEntries(); 
            break;
            case 3: editEntry(); 
            break;
            case 4: deleteEntry(); 
            break;
            case 5: printf("Exit...\n"); 
            break;
            default: printf("please choose valid option!\n");
        }
    } while (choice != 5);
}

void addEntry() {
    FILE *fp = fopen(FILENAME, "a");
    struct Diary d;
    printf("Enter date (dd-mm-yyyy): ");
    fgets(d.date, sizeof(d.date), stdin);
    strtok(d.date, "\n"); // remove newline

    printf("Enter title: ");
    fgets(d.title, sizeof(d.title), stdin);
    strtok(d.title, "\n");

    printf("Enter content: ");
    fgets(d.content, sizeof(d.content), stdin);
    strtok(d.content, "\n");

    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
    printf("Entry added successfully!\n");
}

void viewEntries() {
    FILE *fp = fopen(FILENAME, "r");
    struct Diary d;
    int count = 0;

    while (fread(&d, sizeof(d), 1, fp)) {
        printf("\nEntry %d\n", ++count);
        printf("Date: %s\nTitle: %s\nContent: %s\n", d.date, d.title, d.content);
    }

    if (count == 0)
        printf("No entries found.\n");

    fclose(fp);
}

void editEntry() {
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen(TEMPFILE, "w");
    struct Diary d;
    char title[50];
    int found = 0;

    printf("Enter title of entry to edit: ");
    fgets(title, sizeof(title), stdin);
    strtok(title, "\n");

    while (fread(&d, sizeof(d), 1, fp)) {
        if (strcmp(d.title, title) == 0) {
            found = 1;
            printf("Enter new date: ");
            fgets(d.date, sizeof(d.date), stdin);
            strtok(d.date, "\n");

            printf("Enter new title: ");
            fgets(d.title, sizeof(d.title), stdin);
            strtok(d.title, "\n");

            printf("Enter new content: ");
            fgets(d.content, sizeof(d.content), stdin);
            strtok(d.content, "\n");
        }
        fwrite(&d, sizeof(d), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove(FILENAME);
    rename(TEMPFILE, FILENAME);

    if (found)
        printf("Entry updated successfully.\n");
    else
        printf("Entry not found.\n");
}

void deleteEntry() {
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen(TEMPFILE, "w");
    struct Diary d;
    char title[50];
    int found = 0;

    printf("Enter title of entry to delete: ");
    fgets(title, sizeof(title), stdin);
    strtok(title, "\n");

    while (fread(&d, sizeof(d), 1, fp)) {
        if (strcmp(d.title, title) != 0) {
            fwrite(&d, sizeof(d), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove(FILENAME);
    rename(TEMPFILE, FILENAME);

    if (found)
        printf("Entry deleted successfully.\n");
    else
        printf("Entry not found.\n");
}

