#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_STUDENTS 100
#define MAX_TITLE_LENGTH 15
#define MAX_AUTHOR_LENGTH 20
#define MAX_CATEGORY_LENGTH 100
#define MAX_YEAR_LENGTH 15
#define MAX_ID_LENGTH 10
#define MAX_NAME_LENGTH 50
#define MAX_LAST_NAME_LENGTH 50
#define MAX_FACULTY_LENGTH 50

typedef struct {
    char ISBN[14];
    char category[MAX_CATEGORY_LENGTH];
    char title[MAX_TITLE_LENGTH];
    char year[MAX_YEAR_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int readings;
} Book;

typedef struct {
    char ID[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char lastName[MAX_LAST_NAME_LENGTH];
    char faculty[MAX_FACULTY_LENGTH];
    int readings;
} Student;

typedef struct {
    char studentID[MAX_ID_LENGTH];
    char ISBN[14];
    char takeDate[11];
    char returnDate[11];
    int status;
} Transaction;

Book library[MAX_BOOKS];
int numBooks = 0;

Student students[MAX_STUDENTS];
int numStudents = 0;

Transaction transactions[MAX_BOOKS];
int numTransactions = 0;

void saveBooksToFile() {
    FILE *file = fopen("book.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%d\n", library[i].ISBN, library[i].category, library[i].title,
                library[i].year, library[i].author, library[i].readings);
    }

    fclose(file);
}

void saveStudentsToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%s,%s,%s,%s\n", students[i].ID, students[i].name, students[i].lastName,
                students[i].faculty);
    }

    fclose(file);
}

void saveTransactionsToFile() {
    FILE *file = fopen("take_book.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numTransactions; i++) {
        fprintf(file, "%s,%s,%s,%s,%d\n", transactions[i].studentID, transactions[i].ISBN,
                transactions[i].takeDate, transactions[i].returnDate, transactions[i].status);
    }

    fclose(file);
}

void loadBooksFromFile() {
    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        strcpy(library[numBooks].ISBN, token);

        token = strtok(NULL, ",");
        strcpy(library[numBooks].category, token);

        token = strtok(NULL, ",");
        strcpy(library[numBooks].title, token);

        token = strtok(NULL, ",");
        strcpy(library[numBooks].year, token);

        token = strtok(NULL, ",");
        strcpy(library[numBooks].author, token);

        token = strtok(NULL, ",");
        library[numBooks].readings = atoi(token);

        numBooks++;
    }

    fclose(file);
}

void loadStudentsFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        strcpy(students[numStudents].ID, token);

        token = strtok(NULL, ",");
        strcpy(students[numStudents].name, token);

        token = strtok(NULL, ",");
        strcpy(students[numStudents].lastName, token);

        token = strtok(NULL, ",");
        strcpy(students[numStudents].faculty, token);

        numStudents++;
    }

    fclose(file);
}
void printStudent(Student student) {
    printf("Student ID: %s\n", student.ID);
    printf("Name: %s\n", student.name);
    printf("Last Name: %s\n", student.lastName);
    printf("Faculty: %s\n", student.faculty);
    printf("Number of Readings: %d\n", student.readings);
    printf("\n");
}
void loadTransactionsFromFile() {
    FILE *file = fopen("take_book.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        strcpy(transactions[numTransactions].studentID, token);

        token = strtok(NULL, ",");
        strcpy(transactions[numTransactions].ISBN, token);

        token = strtok(NULL, ",");
        strcpy(transactions[numTransactions].takeDate, token);

        token = strtok(NULL, ",");
        strcpy(transactions[numTransactions].returnDate, token);

        token = strtok(NULL, ",");
        transactions[numTransactions].status = atoi(token);

        numTransactions++;
    }

    fclose(file);
}

void registerBook() {
    if (numBooks == MAX_BOOKS) {
        printf("The library is full. Cannot register more books.\n");
        return;
    }

    printf("Enter the ISBN: ");
    scanf("%s", library[numBooks].ISBN);
    getchar(); // consume the newline character

    // Check if the ISBN already exists
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(library[i].ISBN, library[numBooks].ISBN) == 0) {
            printf("Book with the same ISBN already exists.\n");
            return;
        }
    }

    printf("Enter the category: ");
    fgets(library[numBooks].category, sizeof(library[numBooks].category), stdin);
    library[numBooks].category[strcspn(library[numBooks].category, "\n")] = '\0'; // remove the trailing newline character

    printf("Enter the title: ");
    fgets(library[numBooks].title, sizeof(library[numBooks].title), stdin);
    library[numBooks].title[strcspn(library[numBooks].title, "\n")] = '\0'; // remove the trailing newline character
    printf("Enter the year of the book's production: ");
    fgets(library[numBooks].year, sizeof(library[numBooks].year), stdin);
    library[numBooks].year[strcspn(library[numBooks].year, "\n")] = '\0'; // remove the trailing newline character
    
    printf("Enter the author: ");
    fgets(library[numBooks].author, sizeof(library[numBooks].author), stdin);
    library[numBooks].author[strcspn(library[numBooks].author, "\n")] = '\0'; // remove the trailing newline character
    
    library[numBooks].readings = 0; // initialize readings to 0
    
    printf("Book registered successfully.\n");
    
    numBooks++;
    
    saveBooksToFile();
}

void registerStudent() {
    if (numStudents == MAX_STUDENTS) {
        printf("The student database is full. Cannot register more students.\n");
        return;
    }
    printf("Enter the student ID: ");
    scanf("%s", students[numStudents].ID);
    getchar(); // consume the newline character
    
    // Check if the ID already exists
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].ID, students[numStudents].ID) == 0) {
            printf("Student with the same ID already exists.\n");
            return;
        }
    }
    
    printf("Enter the student name: ");
    fgets(students[numStudents].name, sizeof(students[numStudents].name), stdin);
    students[numStudents].name[strcspn(students[numStudents].name, "\n")] = '\0'; // remove the trailing newline character
    
    printf("Enter the student last name: ");
    fgets(students[numStudents].lastName, sizeof(students[numStudents].lastName), stdin);
    students[numStudents].lastName[strcspn(students[numStudents].lastName, "\n")] = '\0'; // remove the trailing newline character
    
    printf("Enter the student faculty: ");
    fgets(students[numStudents].faculty, sizeof(students[numStudents].faculty), stdin);
    students[numStudents].faculty[strcspn(students[numStudents].faculty, "\n")] = '\0'; // remove the trailing newline character
    
    printf("Student registered successfully.\n");
    
    numStudents++;
    
    saveStudentsToFile();
}

void lendBook() {
    if (numBooks == 0) {
        printf("The library is empty. No books available for lending.\n");
    return;
    }
    if (numStudents == 0) {
    printf("No students registered. Cannot lend a book.\n");
    return;
    }
    
    char studentID[MAX_ID_LENGTH];
    char bookISBN[14];
    char takeDate[11];
    char returnDate[11];
    
    printf("Enter the student ID: ");
    scanf("%s", studentID);
    getchar(); // consume the newline character
    
    // Check if the student ID exists
    int studentIndex = -1;
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].ID, studentID) == 0) {
            studentIndex = i;
            break;
        }
    }
    
    if (studentIndex == -1) {
        printf("No student found with the given ID.\n");
        return;
    }
    
    printf("Enter the book ISBN: ");
    scanf("%s", bookISBN);
    getchar(); // consume the newline character
    
    // Check if the book ISBN exists
    int bookIndex = -1;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(library[i].ISBN, bookISBN) == 0) {
            bookIndex = i;
            break;
        }
    }
    
    if (bookIndex == -1) {
        printf("No book found with the given ISBN.\n");
        return;
    }
    
    // Check if the book is already borrowed
    for (int i = 0; i < numTransactions; i++) {
        if (strcmp(transactions[i].ISBN, bookISBN) == 0 && transactions[i].status == 0) {
            printf("The book is already borrowed.\n");
            return;
        }
    }
    
    printf("Enter the take date (YYYY-MM-DD): ");
    scanf("%s", takeDate);
    getchar(); // consume the newline character
    
    printf("Enter the return date (YYYY-MM-DD): ");
    scanf("%s", returnDate);
    getchar(); // consume the newline character
    
    // Add the transaction
    strcpy(transactions[numTransactions].studentID, studentID);
    strcpy(transactions[numTransactions].ISBN, bookISBN);
    strcpy(transactions[numTransactions].takeDate, takeDate);
    strcpy(transactions[numTransactions].returnDate, returnDate);
    transactions[numTransactions].status = 0;
    
    printf("Book lent successfully.\n");
    
    numTransactions++;
    
    saveTransactionsToFile();
}


void returnBook() {
    if (numBooks == 0) {
    printf("The library is empty. No books to return.\n");
    return;
    }
    if (numStudents == 0) {
        printf("No students registered. Cannot return a book.\n");
        return;
    }
    
    char bookISBN[14];
    
    printf("Enter the book ISBN: ");
    scanf("%s", bookISBN);
    getchar(); // consume the newline character
    
    // Check if the book ISBN exists
    int bookIndex = -1;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(library[i].ISBN, bookISBN) == 0) {
            bookIndex = i;
            break;
        }
    }
    
    if (bookIndex == -1) {
        printf("No book found with the given ISBN.\n");
        return;
    }
    
    // Check if the book is borrowed
    int transactionIndex = -1;
    for (int i = 0; i < numTransactions; i++) {
        if (strcmp(transactions[i].ISBN, bookISBN) == 0 && transactions[i].status == 0) {
            transactionIndex = i;
            break;
        }
    }
    
    if (transactionIndex == -1) {
        printf("The book is not borrowed.\n");
        return;
    }
    
    // Update the transaction status to returned
    transactions[transactionIndex].status = 1;
    
    printf("Book returned successfully.\n");
    
    saveTransactionsToFile();
}

void printBook(Book book) {
    printf("ISBN: %s\n", book.ISBN);
    printf("Category: %s\n", book.category);
    printf("Title: %s\n", book.title);
    printf("Year: %s\n", book.year);
    printf("Author: %s\n", book.author);
    printf("Number of Readings: %d\n", book.readings);
}

void listBooks() {
    if (numBooks == 0) {
    printf("The library is empty. No books to list.\n");
    return;
    }
    int option;
    printf("1. List books by ISBN\n");
    printf("2. List books by title\n");
    printf("Enter your option: ");
    scanf("%d", &option);
    getchar(); // consume the newline character
    
    switch (option) {
        case 1: {
            char bookISBN[14];
            printf("Enter the book ISBN: ");
            scanf("%s", bookISBN);
            getchar(); // consume the newline character
    
            int bookIndex = -1;
            for (int i = 0; i < numBooks; i++) {
                if (strcmp(library[i].ISBN, bookISBN) == 0) {
                    bookIndex = i;
                    break;
                }
            }
    
            if (bookIndex == -1) {
                printf("No book found with the given ISBN.\n");
                return;
            }
    
            printBook(library[bookIndex]);
    
            break;
        }
        case 2: {
            char bookTitle[16];
            printf("Enter the book title: ");
            fgets(bookTitle, sizeof(bookTitle), stdin);
            bookTitle[strcspn(bookTitle, "\n")] = '\0'; // remove the trailing newline character
    
            int bookIndex = -1;
            for (int i = 0; i < numBooks; i++) {
                if (strcmp(library[i].title, bookTitle) == 0) {
                    bookIndex = i;
                    break;
                }
            }
    
            if (bookIndex == -1) {
                printf("No book found with the given title.\n");
                return;
            }
    
            printBook(library[bookIndex]);
    
            break;
        }
        default:
            printf("Invalid option.\n");
            break;
    }
}

void searchBook() {
    if (numBooks == 0) {
        printf("The library is empty. No books to search.\n");
        return;
    }
    int option;
    printf("1. Search book by ISBN\n");
    printf("2. Search book by title\n");
    printf("Enter your option: ");
    scanf("%d", &option);
    getchar(); // consume the newline character
    
    switch (option) {
        case 1: {
            char bookISBN[14];
            printf("Enter the book ISBN: ");
            scanf("%s", bookISBN);
            getchar(); // consume the newline character
    
            int bookIndex = -1;
            for (int i = 0; i < numBooks; i++) {
                if (strcmp(library[i].ISBN, bookISBN) == 0) {
                    bookIndex = i;
                    break;
                }
            }
    
            if (bookIndex == -1) {
                printf("No book found with the given ISBN.\n");
                return;
            }
    
            printBook(library[bookIndex]);
    
            break;
        }
        case 2: {
            char bookTitle[16];
            printf("Enter the book title: ");
            fgets(bookTitle, sizeof(bookTitle), stdin);
            bookTitle[strcspn(bookTitle, "\n")] = '\0'; // remove the trailing newline character
    
            int bookIndex = -1;
            for (int i = 0; i < numBooks; i++) {
                if (strcmp(library[i].title, bookTitle) == 0) {
                    bookIndex = i;
                    break;
                }
            }
    
            if (bookIndex == -1) {
                printf("No book found with the given title.\n");
                return;
            }
    
            printBook(library[bookIndex]);
    
            break;
        }
        default:
            printf("Invalid option.\n");
            break;
    }
}

void printMostReadBooks() {
    if (numBooks == 0) {
        printf("The library is empty. No books to print.\n");
        return;
    }
    if (numBooks < 10) {
    printf("There are less than 10 books in the library.\n");
    }
    
    Book tempBooks[MAX_BOOKS];
    memcpy(tempBooks, library, sizeof(library)); // create a copy of the library
    
    // Sort books based on number of readings in descending order
    for (int i = 0; i < numBooks - 1; i++) {
        for (int j = 0; j < numBooks - i - 1; j++) {
            if (tempBooks[j].readings < tempBooks[j + 1].readings) {
                Book temp = tempBooks[j];
                tempBooks[j] = tempBooks[j + 1];
                tempBooks[j + 1] = temp;
            }
        }
    }
    
    printf("Top 10 most read books:\n");
    for (int i = 0; i < 10; i++) {
        printBook(tempBooks[i]);
    }
}

void printStudentsWithLeastReadings() {
    if (numStudents == 0) {
        printf("No students registered. Cannot print students with least readings.\n");
        return;
    }
    if (numStudents < 20) {
        printf("There are less than 20 students in the library.\n");
    }
    
    Student tempStudents[MAX_STUDENTS];
    memcpy(tempStudents, students, sizeof(students)); // create a copy of the students
    
    // Sort students based on number of readings in ascending order
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if(tempStudents[j].readings && tempStudents[j+1].readings){
                if (tempStudents[j].readings > tempStudents[j + 1].readings) {
                    Student temp = tempStudents[j];
                    tempStudents[j] = tempStudents[j + 1];
                    tempStudents[j + 1] = temp;
                }
            }
        }
    }
    
    printf("Top 20 students with least readings:\n");
    for (int i = 0; i < 20; i++) {
        printStudent(tempStudents[i]);
    }
}

int main() {
    loadBooksFromFile();
    loadStudentsFromFile();
    loadTransactionsFromFile();
    int choice;

    do {
        printf("************ Student Library Administration ************\n");
        printf("1. Register a book\n");
        printf("2. Register a student\n");
        printf("3. Lend a book\n");
        printf("4. Return a book\n");
        printf("5. List books\n");
        printf("6. Search book\n");
        printf("7. Print top 10 most read books\n");
        printf("8. Print top 20 students with least readings\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume the newline character
    
        switch (choice) {
            case 0:
                printf("Exiting the program.\n");
                break;
            case 1:
                registerBook();
                break;
            case 2:
                registerStudent();
                break;
            case 3:
                lendBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                listBooks();
                break;
            case 6:
                searchBook();
                break;
            case 7:
                printMostReadBooks();
                break;
            case 8:
                printStudentsWithLeastReadings();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    
        printf("\n");
    
    } while (choice != 0);
    
    return 0;
}
