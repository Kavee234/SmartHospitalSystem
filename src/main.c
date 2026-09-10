#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define NUM_SPECIALTIES 4
#define NUM_WARDS 4

char patientNames[MAX_PATIENTS][50];
int patientAges[MAX_PATIENTS];
int patientUrgency[MAX_PATIENTS];
int patientSpecialty[MAX_PATIENTS];
int patientWard[MAX_PATIENTS];
int patientDays[MAX_PATIENTS];
int patientCount = 0;

const char *specialtyNames[NUM_SPECIALTIES] = {"General Practice (OPD)","Paediatrics","Cardiology","Neurology"};

const char *wardNames[NUM_WARDS] = {"General Ward","Paediatric Ward","Surgical Ward","ICU"};

void showSpecialties() {
    printf("\n--------------------------\n");
    printf("--- Doctor Specialties ---\n");
    printf("--------------------------\n");
    for (int i = 0; i < NUM_SPECIALTIES; i++) {
        printf("ID %d: %s\n", i+1, specialtyNames[i]);
    }
}

void showWards() {
    printf("\n--------------------------\n");
    printf("---- Hospital Wards ----\n");
    printf("--------------------------\n");
    for (int i = 0; i < NUM_WARDS; i++) {
        printf("ID %d: %s\n", i+1, wardNames[i]);
    }
}

void registerPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient limit reached!\n");
        return;
    }

    printf("\n----------------------------------\n");
    printf("------ Register New Patient ------\n");
    printf("----------------------------------\n");
    printf("Enter Patient's Name: ");
    scanf(" %[^\n]", patientNames[patientCount]);

    printf("Enter Age: ");
    scanf("%d", &patientAges[patientCount]);

    printf("\n---------------------\n--- Urgency Level ---\n---------------------\n \n1 = Normal \n2 = Urgent \n3 = Critical \nEnter Urgency Level: ");
    scanf("%d", &patientUrgency[patientCount]);

    showSpecialties();
    printf("Enter Specialty ID (1-4): ");
    scanf("%d", &patientSpecialty[patientCount]);

    printf("Admitted to Ward? (1 = Yes, 0 = No): ");
    int admitted;
    scanf("%d", &admitted);

    if (admitted == 1) {
        showWards();
        printf("Enter Ward ID (1-4): ");
        scanf("%d", &patientWard[patientCount]);
        printf("Enter Days Admitted: ");
        scanf("%d", &patientDays[patientCount]);
    } else {
        patientWard[patientCount] = 0;
        patientDays[patientCount] = 0;
    }

    patientCount++;
    printf("Patient registered successfully!\n");
}

int main() {
    int choice;
    do {
        printf("-----------------------------\n");
        printf("### Smart Hospital System ###\n");
        printf("-----------------------------\n");
        printf("1. Register Patient\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: registerPatient(); break;
            case 2: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while(choice != 2);

    return 0;
}
