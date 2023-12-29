#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mariadb/mysql.h>

int studentSubjects = 8;
char studentSubjectsNames[8][50] = {"Fundamentals of Programming", "Introduction to Computing", "Information Management", "Mathematics in the Modern World", "Purposive Communication", "Understanding the Self", "Physical Education", "National Service Training Program"};

struct INFORMATION {
    int studNumbers;
    char firstName[26];
    char lastName[26];
    char birthDate[26];
    char email[51];
    char cpNum[12];
};

struct INFORMATION student;

MYSQL *conn;

void connectDatabase() {
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "root", NULL, "group1", 0, NULL, 0) == NULL) {
    fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(conn));
    exit(1);
    }
}

int addStud() {
    char createTableQuery[] = "CREATE TABLE IF NOT EXISTS Students ("
                                   "studNumbers INT PRIMARY KEY,"
                                   "firstName CHAR(25),"
                                   "lastName CHAR(25),"
                                   "birthDate VARCHAR(25),"
                                   "email VARCHAR(50),"
                                   "cpNum CHAR(11)"
                                   ");";
        if (mysql_query(conn, createTableQuery) != 0) {
                fprintf(stderr, "Failed to create Students table: Error: %s\n", mysql_error(conn));
                mysql_close(conn);
                exit(1);
        }

        printf("-------------------------------\n");
        printf("| \tStudent Details       |\n");       
        printf("-------------------------------\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        int validstudNum = 0;
        char buffer[10];
        getchar();
        while (!validstudNum) {
            printf("Student Number: ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] == '\n') {
                printf("\nInvalid input. Student Number must not be empty (PRIMARY KEY). \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            } else if (sscanf(buffer, "%d", &student.studNumbers) != 1) {
                printf("\nInvalid input. Please enter a valid student number. \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            } else {
                validstudNum = 1;
            }
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        int validFirstName = 0;
        while (!validFirstName) {
            printf("First name: ");
            scanf("%[^\n]", &student.firstName);
            getchar();
            if (strlen(student.firstName) == 0) {
                printf("\nInvalid input. First name must not be empty (NOT NULL). \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            } else {
                validFirstName = 1;
            }
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        int validLastName = 0;
        while (!validLastName) {
            printf("Last name: ");
            scanf("%[^\n]", &student.lastName);
            getchar();
            if (strlen(student.lastName) == 0) {
                printf("\nInvalid input. Last name must not be empty (NOT NULL). \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            } else {
                validLastName = 1;
            }
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        int validDoB = 0;
        int month, day, year;
        while (!validDoB) {
            printf("Date of Birth (mm/dd/yyyy): ");
            scanf("%[^\n]", &student.birthDate);
            getchar();
            if (strlen(student.birthDate) == 0) {
                printf("\nInvalid input. Date of Birth must not be empty (NOT NULL). \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            } else if (sscanf(student.birthDate, "%2d/%2d/%4d", &month, &day, &year) != 3) {
                printf("\nInvalid input. Date of Birth must be in valid format. \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
            } else {
                validDoB = 1;
            }
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        int validEmail = 0;
        while (!validEmail) {
            printf("Email Address: ");
            scanf("%[^\n]", &student.email);
            getchar();
            if (strlen(student.email) == 0) {
                printf("\nInvalid input. Email must not be empty (NOT NULL). \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            } else if (strstr(student.email, "@") == NULL || strstr(student.email, ".") == NULL) {
                printf("\nInvalid input. Email must be in valid format. \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            } else {
                validEmail = 1;
            }
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        int validCpNum = 0;
        while (!validCpNum) {
            printf("Cellphone Number (09*********): ");
            scanf("%[^\n]", &student.cpNum);
            getchar();
            if (strlen(student.cpNum) == 0 ) {
                printf("\nInvalid input. Cellphone Number must not be empty (NOT NULL). \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            } else if (strlen(student.cpNum) != 11) {
                printf("\nInvalid input. Cellphone Number should be exactly 11 digits.\n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            } else {
                validCpNum = 1;
            }
        }
        
        char confirmation;
        printf("\nDo you confirm to add this student on the database? (y/n): ");
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'Y') {
            char insertDataQuery[200];  
            sprintf(insertDataQuery, "INSERT INTO Students (studNumbers, firstName, lastName, birthDate, email, cpNum) VALUES (%d, '%s', '%s', '%s', '%s', '%s')",
                    student.studNumbers, student.firstName,
                    student.lastName, student.birthDate,
                    student.email, student.cpNum);
                if (mysql_query(conn, insertDataQuery) != 0) {
                    fprintf(stderr, "Failed to insert data: Error: %s\n", mysql_error(conn));
                    mysql_close(conn);
                    return 1;
                }

            printf("\n| THE STUDENT IS ADDED SUCCESSFULLY | \n");  
            return 1;  
        } else {
            printf("Student not added. \n");
            return 0;
        }
}

int updateStud() {
    printf("------------------------------------------\n");
    printf("| \t  Update Student Details         |\n");
    printf("------------------------------------------\n");
    
    int studNum;
    printf("Enter the Student Number to update: ");
    if (scanf("%d", &studNum) != 1) {
            printf("Invalid option. Enter the Student Number properly. \n");
            scanf("%*[^\n]"); 
            scanf("%*c");      
            return 0;
        }

    char selectQuery[200];
    sprintf(selectQuery, "SELECT * FROM Students WHERE studNumbers = %d", studNum);
        if (mysql_query(conn, selectQuery) != 0) {
            fprintf(stderr, "There is an error finding the student: %s\n", mysql_error(conn));
            return 0;
        }

    MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "There is an error storing the result: %s\n", mysql_error(conn));
            return 0;
        }

    int numRows = mysql_num_rows(result);

    if (numRows > 0) {
        int choice;
        printf("\nWhat Student detail do you want to update? \n");
        printf("1. First name\n");
        printf("2. Last name\n");
        printf("3. Date of Birth\n");
        printf("4. Email Address\n");
        printf("5. Cellphone Number\n\n");
        printf("Enter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid option. Please choose from 1 to 5 only. \n");
            scanf("%*[^\n]"); 
            scanf("%*c");      
            return 0;
        }
        
        char updateDataQuery[200];

        switch (choice) {
            case 1: {
                int validFirstName = 0;
                while (!validFirstName) {
                    getchar();
                    printf("New First name: ");
                    scanf("%[^\n]", &student.firstName);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    if (strlen(student.firstName) == 0) {
                        printf("\nInvalid input. First name must not be empty (NOT NULL). \n");
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    } else {
                        validFirstName = 1;
                    }
                }
            }
                sprintf(updateDataQuery, "UPDATE Students SET firstName = '%s' WHERE studNumbers = %d", student.firstName, studNum);
                break;
            case 2: {
                int validLastName = 0;
                while (!validLastName) {
                    getchar();
                    printf("New Last name: ");
                    scanf("%[^\n]", &student.lastName);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    if (strlen(student.lastName) == 0) {
                        printf("\nInvalid input. Last name must not be empty (NOT NULL). \n");
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    } else {
                        validLastName = 1;
                    }
                }
            }
                sprintf(updateDataQuery, "UPDATE Students SET lastName = '%s' WHERE studNumbers = %d", student.lastName, studNum);
                break;
            case 3: {
                int validDoB = 0;
                int month, day, year;
                while (!validDoB) {
                    getchar();
                    printf("New Date of Birth (mm/dd/yyyy): ");
                    scanf("%[^\n]", &student.birthDate);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    if (strlen(student.birthDate) == 0) {
                        printf("\nInvalid input. Date of Birth must not be empty (NOT NULL). \n");
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    } else if (sscanf(student.birthDate, "%2d/%2d/%4d", &month, &day, &year) != 3) {
                        printf("\nInvalid input. Date of Birth must be in valid format. \n");
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
                    } else {
                        validDoB = 1;
                    }
                }
            }
                sprintf(updateDataQuery, "UPDATE Students SET birthDate = '%s' WHERE studNumbers = %d", student.birthDate, studNum);
                break;
            case 4: {
                int validEmail = 0;
                while (!validEmail) {
                    getchar();
                    printf("New Email Address: ");
                    scanf("%[^\n]", &student.email);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    if (strlen(student.email) == 0) {
                        printf("\nInvalid input. Email must not be empty (NOT NULL). \n");
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    } else if (strstr(student.email, "@") == NULL || strstr(student.email, ".") == NULL) {
                        printf("\nInvalid input. Email must be in valid format. \n");
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    } else {
                        validEmail = 1;
                    }
                }
            }
                sprintf(updateDataQuery, "UPDATE Students SET email = '%s' WHERE studNumbers = %d", student.email, studNum);
                break;
            case 5: {
                int validCpNum = 0;
                while (!validCpNum) {
                    getchar();
                    printf("New Cellphone Number (09*********): ");
                    scanf("%[^\n]", &student.cpNum);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    if (strlen(student.cpNum) == 0 ) {
                        printf("\nInvalid input. Cellphone Number must not be empty (NOT NULL). \n");
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    } else if (strlen(student.cpNum) != 11) {
                        printf("\nInvalid input. Cellphone Number should be exactly 11 digits.\n");
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    } else {
                        validCpNum = 1;
                    }
                }
                sprintf(updateDataQuery, "UPDATE Students SET cpNum = '%s' WHERE studNumbers = %d", student.cpNum, studNum);
                break;
            }
            default:
                printf("Invalid option. Please choose from 1 to 5 only. \n");
                return 0;
        }
        
        if (mysql_query(conn, updateDataQuery) != 0) {
            fprintf(stderr, "There is an error updating the student: %s\n", mysql_error(conn));
            mysql_free_result(result);
            return 0; 
        }
        
            printf("\n| STUDENT %d UPDATED SUCCESSFULLY |\n", studNum);
            mysql_free_result(result);
            return 1;
    } else {
        printf("Student %d not found in the database.\n", studNum);
        return 0;
    }
}

int deleteStud() {
    printf("----------------------------------\n");
    printf("| \tDelete a Student         |\n");
    printf("----------------------------------\n");

    int studNum;
    printf("Enter Student ID to delete: ");
    if (scanf("%d", &studNum) != 1) {
            printf("Invalid option. Enter the Student Number properly. \n");
            scanf("%*[^\n]"); 
            scanf("%*c");      
            return 0;
        }

    char selectQuery[200];
    sprintf(selectQuery, "SELECT * FROM Students WHERE studNumbers = %d", studNum);
        if (mysql_query(conn, selectQuery) != 0) {
            fprintf(stderr, "There is an error finding the student: %s\n", mysql_error(conn));
            return 0;
        } 

    MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "There is an error storing the result: %s\n", mysql_error(conn));
            return 0;
        }

    int numRows = mysql_num_rows(result);

    if (numRows == 0) {
        printf("Student %d not found in the database. \n", studNum);
        mysql_free_result(result);
        return 0;
    }

    char decision;
    printf("Are you sure you want to delete this student? (y/n): ");
    scanf(" %c", &decision);

    if (decision == 'y' || decision == 'Y'){ 
        char deleteGradesQuery[200];
        sprintf(deleteGradesQuery, "DELETE FROM Grades WHERE studNumbers = %d", studNum);
            if (mysql_query(conn, deleteGradesQuery) != 0) {
                fprintf(stderr, "There is an error deleting the grades: %s\n", mysql_error(conn));
                mysql_free_result(result);
                return 0;
            }

        char deleteDataQuery[200];
        sprintf(deleteDataQuery, "DELETE FROM Students WHERE studNumbers = %d", studNum);
            if (mysql_query(conn, deleteDataQuery) != 0) {
                fprintf(stderr, "There is an error deleting the student: %s\n", mysql_error(conn));
                mysql_free_result(result);
                return 0;
            }

            printf("\n| STUDENT %d DELETED SUCCESSFULLY |\n", studNum);
            mysql_free_result(result);
            return 1;
    } else {
        printf("Student %d not deleted. \n", studNum);
        mysql_free_result(result);
        return 0;
    }
} 

void displayStud() {
    if (mysql_query(conn, "SELECT * FROM Students") != 0) {
        fprintf(stderr, "There is an error finding the students: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "There is an error storing the result: %s\n", mysql_error(conn));
            return;
        }

    int numRows = mysql_num_rows(result);

    if (numRows == 0) {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("No students available.\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    } else {
        printf("----------------------------\n");
        printf("\tStudent List\n");
        printf("----------------------------\n");

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            int studentNumber = atoi(row[0]);
            printf("Student Number: %d\n", studentNumber);
            printf("Student: %s %s\n", row[1], row[2]);
            printf("Date of Birth: %s\n", row[3]);
            printf("Email: %s\n", row[4]);
            printf("Contact Number: %s\n\n", row[5]);
        }
    }

    mysql_free_result(result);
}

int inputGrades() {
    char createTableQuery[] = "CREATE TABLE IF NOT EXISTS Grades ("
                               "gradeID INT AUTO_INCREMENT PRIMARY KEY,"
                               "studNumbers INT,"
                               "subjectName VARCHAR(50),"
                               "grade INT,"
                               "FOREIGN KEY (studNumbers) REFERENCES Students(studNumbers)"
                               ");";
        if (mysql_query(conn, createTableQuery) != 0) {
            fprintf(stderr, "Failed to create Grades table: Error: %s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }

    int studNum;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Enter Student Number to input grades: ");
    if (scanf("%d", &studNum) != 1) {
            printf("Invalid option. Enter the Student Number properly. \n");
            scanf("%*[^\n]"); 
            scanf("%*c");      
            return 0;
        }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    char selectQuery[100];
    sprintf(selectQuery, "SELECT * FROM Students WHERE studNumbers = %d", studNum);
        if (mysql_query(conn, selectQuery) != 0) {
            fprintf(stderr, "There is an error finding the student: %s\n", mysql_error(conn));
            return 0;
        }

    MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "There is an error storing the result: %s\n", mysql_error(conn));
            return 0;
        }

    MYSQL_ROW row = mysql_fetch_row(result);
        if (row == NULL) {
            printf("Student %d not found in the database. \n", studNum);
            mysql_free_result(result);
            return 0;
        }

    char checkGradesQuery[100];
    sprintf(checkGradesQuery, "SELECT * FROM Grades WHERE studNumbers = %d", studNum);
        if (mysql_query(conn, checkGradesQuery) != 0) {
            fprintf(stderr, "There is an error checking for existing grades: %s\n", mysql_error(conn));
            mysql_free_result(result);
            return 0;
        }

    MYSQL_RES *existingGradesResult = mysql_store_result(conn);
        if (existingGradesResult == NULL) {
            fprintf(stderr, "There is an error storing existing grades result: %s\n", mysql_error(conn));
            mysql_free_result(result);
            return 0;
        }

    MYSQL_ROW existingGradesRow = mysql_fetch_row(existingGradesResult);
        if (existingGradesRow != NULL) {
            printf("Grades already exist for student %d. You cannot insert new grades.\n", studNum);
            mysql_free_result(existingGradesResult);
            mysql_free_result(result);
            return 0;
        }

    char insertDataQuery[100];
    for (int i = 0; i < studentSubjects; i++) {
        printf("%s Grade: ", studentSubjectsNames[i]);
        int grade;
        if (scanf("%d", &grade) != 1 || grade <= 50 || grade > 100) {
            printf("Invalid Input. The grade must be a number and not less than 50 or greater than 100. \n");
            scanf("%*[^\n]");  
            scanf("%*c");   
            i--;
            continue;
    } 
        char confirmation;
        printf("Do you confirm this grade? (y/n): ");
        scanf(" %c", &confirmation);
        if (confirmation == 'y' || confirmation == 'Y') {
            sprintf(insertDataQuery, "INSERT INTO Grades (studNumbers, subjectName, grade) VALUES (%d, '%s', %d)", studNum, studentSubjectsNames[i], grade);
                if (mysql_query(conn, insertDataQuery) != 0) {
                    fprintf(stderr, "There is an error inserting grades: %s\n", mysql_error(conn));
                    mysql_free_result(result);
                    return 0;
                }
        } else {
            printf("Try again. Enter the grades correctly. \n");
            i--;
        }    
    }

        printf("\n| STUDENT %d GRADES ENTERED SUCCESSFULLY |\n", studNum);
        mysql_free_result(result);
        return 1;
}

int searchStudents() {
    printf("----------------------------------\n");
    printf("| \tSearch a Student         |\n");
    printf("----------------------------------\n");
    int choice;
    int studNum;
    char studName[26];
    char selectQuery[200];
    printf("1. Search by Student Number\n");
    printf("2. Search by Student Name\n\n");
    printf("Enter your choice (1-2): ");
    if (scanf("%d", &choice) != 1) {
            printf("Invalid option. Please choose from 1 and 2 only. \n");
            scanf("%*[^\n]"); 
            scanf("%*c");      
            return 0;
        }

    switch (choice) {
        case 1:
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("Enter Student Number to search: ");
            if (scanf("%d", &studNum) != 1) {
                printf("Invalid option. Enter the Student Number properly. \n");
                scanf("%*[^\n]"); 
                scanf("%*c");      
                return 0;
            }
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            sprintf(selectQuery, "SELECT * FROM Students WHERE studNumbers = %d", studNum);
                if (mysql_query(conn, selectQuery) != 0) {
                    fprintf(stderr, "There is an error searching for a student: %s\n", mysql_error(conn));
                    return 0;
                }
            break;
        case 2:
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            getchar();
            printf("Enter Student Name to search: ");
            scanf("%[^\n]", &studName);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            sprintf(selectQuery, "SELECT * FROM Students WHERE firstName = '%s' OR lastName = '%s'", studName, studName);
                if (mysql_query(conn, selectQuery) != 0) {
                    fprintf(stderr, "There is an error searching for a student: %s\n", mysql_error(conn));
                    return 0;
                }
            break;
        default:
            printf("Invalid option. Please choose from 1 and 2 only. \n");
            return 0;
            break;
    }

    MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "There is an error storing the result: %s\n", mysql_error(conn));
            return 0;
        }

    int numRows = mysql_num_rows(result);

    if (numRows > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);
        printf("Student %d is found.\n\n", atoi(row[0]));

        printf("Student: %s %s\n", row[1], row[2]);
        printf("Date of Birth: %s\n", row[3]);
        printf("Email: %s\n", row[4]);
        printf("Contact Number: %s\n", row[5]);
        mysql_free_result(result);
        return 1;
    } else {
        printf("Student %d not found in the database. \n", studNum);
        mysql_free_result(result);
        return 0;
    }
}

float getAverage(int studNum) {
    char selectQuery[200];
    sprintf(selectQuery, "SELECT grade FROM Grades WHERE studNumbers = %d", studNum);
        if (mysql_query(conn, selectQuery) != 0) {
            fprintf(stderr, "There is an error finding the grades: %s\n", mysql_error(conn));
            return 0; 
        }
    
    MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "There is an error storing the result: %s\n", mysql_error(conn));
            return 0;
        }

    int numRows = mysql_num_rows(result);
        if (numRows == 0) {
            printf("There is currently no grades found for Student %d in the database. \n", studNum);
            mysql_free_result(result);
            return 0; 
        }

    int total = 0;

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != NULL) {
        total += atoi(row[0]); 
    }

    mysql_free_result(result);
    return (float)total / numRows;
}

int viewGrades() {
    int studNum;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Enter the Student Number to view grades: ");
    if (scanf("%d", &studNum) != 1) {
            printf("Invalid option. Enter the Student Number properly. \n");
            scanf("%*[^\n]"); 
            scanf("%*c");      
            return 0;
        }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    char selectQuery[200];
    sprintf(selectQuery, "SELECT g.subjectName, g.grade, s.firstName, s.lastName "
                        "FROM Grades AS g "
                        "INNER JOIN Students AS s ON g.studNumbers = s.studNumbers "
                        "WHERE g.studNumbers = %d", studNum);
        if (mysql_query(conn, selectQuery) != 0) {
            fprintf(stderr, "There is an error finding the grades: %s\n", mysql_error(conn));
            return 0;
        }

    MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "There is an error storing the result: %s\n", mysql_error(conn));
            return 0;
        }

    int numRows = mysql_num_rows(result);

    if (numRows > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);

        printf("Student Number: %d\n", studNum);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Student: %s %s\n", row[2], row[3]);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        do {
            if (row[0] != NULL && row[1] != NULL) {
                printf("%s: %s\n", row[0], row[1]);
            } 
        } while ((row = mysql_fetch_row(result)) != NULL);
        
            float average = getAverage(studNum);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("Average Grade: %.2f\n", average);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            if (average >= 75) {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("Result: Passed!\n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            } else {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("Result: Failed!\n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        }
            mysql_free_result(result);
            return 1;
    } else {
        printf("There are currently no grades found for Student %d in the database. \n", studNum);
        mysql_free_result(result);
        return 0;
    }
}

void aboutUs() {
    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|\t\t\t\t\t\t                ABOUT US               \t\t\t\t\t\t   | \n");
    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|\t Welcome to CCA-BSCS1: Student Management System! Student Management System (S.I.S) keeps track of student's grades,     |\n");
    printf("|  records, and personal data for easy access. The system can manage and organize student information stored in a database.        |\n|");
    printf("                                                                                                                                  |\n");
    printf("|\t This system was developed by Bachelor of Science in Computer Science first-year students at City College of Angeles.      |\n|");
    printf("                                                                                                                                  |\n");
    printf("|  Panlaqui Brendon  |  Manalo Warren  |  David Nikko  |  Naguit Sean Warren  |  Wiyangco Edcel Carlos  |  Zamora Kristine Angela  |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
}


int welcome() {
    printf("-----------------------------------------------------\n");
    printf("|\tWelcome to Student Management System        | \n");
    printf("-----------------------------------------------------\n\n");

    printf("1. Add Student\n2. Update Student\n3. Delete Student\n4. Search Student\n5. Display Students\n6. Input Grades\n7. View Grades\n8. About Us\n9. Exit\n\n");
    int option;
    printf("Choose an option (1-9): ");
    if (scanf("%d", &option) != 1) {
        printf("Invalid option. Please choose from 1 to 9 only. \n");
        scanf("%*[^\n]"); 
        scanf("%*c");      
        return 0;
    }

    switch (option) {
        case 1:
            addStud();
            break;
        case 2:
            updateStud();
            break;
        case 3:
            deleteStud();
            break;
        case 4:
            searchStudents();
            break;
        case 5:
            displayStud();
            break;
        case 6:
            inputGrades();
            break;
        case 7:
            viewGrades();
            break;
        case 8:
            aboutUs();
            break;
        case 9:
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("THANK YOU FOR USING OUR FINAL PROJECT:)) \n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            mysql_close(conn);
            exit(1);
        default:
            printf("Invalid Option. Please enter a valid one.\n");
            return 0;
    }
}

int main () {
    char admin[15], passw[15];

    while (1) {
        printf("-----------------------------------------------------\n");
        printf("|\t     Student Management System             | \n");
        printf("-----------------------------------------------------\n\n");
        
        printf("Username: ");
        scanf("%s", &admin);
        printf("Password: ");
        scanf("%s", &passw);
        
        if (strcmp(admin, "admin") == 0 && strcmp(passw, "group1") == 0) {
            printf("\nLogin successfully!\n\n");
            break;
        } else {
            printf("Invalid username or password. Try again.\n\n");
        }
    }

    connectDatabase();
    char repeat;
    do {
        welcome();
            printf("\nWould you like to choose another option? (y/n): ");
            scanf("%s", &repeat);
            if (repeat == 'n' || repeat == 'N') {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("THANK YOU FOR USING OUR FINAL PROJECT:)) \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                mysql_close(conn);
            }
    } while (repeat != 'n' && repeat != 'N');
    
    return 0;
}