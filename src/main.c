#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATIENTS 100
#define NUM_SPECIALTIES 4
#define NUM_WARDS 4

void sortPatientsByUrgency();
void listPatients();
void showSpecialties();
void showWards();
void registerPatient();
void generateBill(int i);
double calcWaitingTime(int specialtyID);
double calcEmergencySurcharge(int urgency, double baseFee);
double calcWardCost(int wardID, int days);
double calcAgeDiscount(int age, double grossTotal);
void viewRegisteredPatients();
void admissionsReport();
void wardOccupancyReport();

char patientNames[MAX_PATIENTS][50];
int patientAges[MAX_PATIENTS];
int patientUrgency[MAX_PATIENTS];
int patientSpecialty[MAX_PATIENTS];
int patientWard[MAX_PATIENTS];
int patientDays[MAX_PATIENTS];
int patientCount = 0;

const char *specialtyNames[NUM_SPECIALTIES] = {"General Practice (OPD)","Paediatrics","Cardiology","Neurology"};
const double specialtyFees[NUM_SPECIALTIES] = {1500.0, 2500.0, 4500.0, 5000.0};
const int specialtyTimes[NUM_SPECIALTIES] = {15, 20, 30, 30};
int specialtyQueue[NUM_SPECIALTIES] = {0};

const char *wardNames[NUM_WARDS] = {"General Ward","Paediatric Ward","Surgical Ward","ICU"};
const double wardRates[NUM_WARDS] = {3000.0, 6000.0, 12000.0, 25000.0};

int main() {
    int choice;
    do {
        printf("\n=============================================\n");
        printf("--------    Smart Hospital System    --------\n");
        printf("=============================================\n");
        printf("1. Register Patient\n");
        printf("2. Sort Patients by Urgency\n");
        printf("3. List Patients\n");
        printf("4. View Already Registered Patient's Details\n");
        printf("5. Admissions Report\n");
        printf("6. Ward Occupancy Report\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: registerPatient(); break;
            case 2: sortPatientsByUrgency(); break;
            case 3: listPatients(); break;
            case 4: viewRegisteredPatients(); break;
            case 5: admissionsReport(); break;
            case 6: wardOccupancyReport(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while(choice != 7);

    return 0;
}

void showSpecialties() {
    printf("\n================================\n");
    printf("------ Doctor Specialties ------\n");
    printf("================================\n");
    for (int i = 0; i < NUM_SPECIALTIES; i++) {
        printf("ID %d: %s\n", i+1, specialtyNames[i]);
    }
}

void showWards() {
    printf("\n==========================\n");
    printf("----- Hospital Wards -----\n");
    printf("==========================\n");
    for (int i = 0; i < NUM_WARDS; i++) {
        printf("ID %d: %s\n", i+1, wardNames[i]);
    }
}

void registerPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient limit reached!\n");
        return;
    }

    printf("\n======================================\n");
    printf("-------- Register New Patient --------\n");
    printf("======================================\n");
    printf("Enter Patient's Name: ");
    scanf(" %[^\n]", patientNames[patientCount]);

    printf("Enter Age: ");
    scanf("%d", &patientAges[patientCount]);

    printf("\n=====================\n");
    printf("--- Urgency Level ---\n");
    printf("=====================\n");
    printf("1 = Normal\n2 = Urgent\n3 = Critical\n");
    printf("Enter Urgancy Level: ");
    scanf("%d", &patientUrgency[patientCount]);

    showSpecialties();
    printf("\nEnter Specialty ID (1-4): ");
    scanf("%d", &patientSpecialty[patientCount]);
    specialtyQueue[patientSpecialty[patientCount]-1]++;

    printf("\nAdmitted to Ward?\n Yes = 1 , No = 0\n Enter your choice: ");
    int admitted;
    scanf("%d", &admitted);

    if (admitted == 1) {
        showWards();
        printf("\nEnter Ward ID (1-4): ");
        scanf("%d", &patientWard[patientCount]);
        printf("\nEnter Days Admitted: ");
        scanf("%d", &patientDays[patientCount]);
    } else {
        patientWard[patientCount] = 0;
        patientDays[patientCount] = 0;
    }

    generateBill(patientCount);
    patientCount++;
}

void generateBill(int i) {
    double baseFee = specialtyFees[patientSpecialty[i]-1];
    double surcharge = calcEmergencySurcharge(patientUrgency[i], baseFee);
    double wardCost = calcWardCost(patientWard[i], patientDays[i]);
    double grossTotal = baseFee + surcharge + wardCost;
    double discount = calcAgeDiscount(patientAges[i], grossTotal);
    double finalAmount = grossTotal - discount;
    double waitTime = calcWaitingTime(patientSpecialty[i]);
    double surchargePercent = 0.0;
        if (patientUrgency[i] == 2) surchargePercent = 20.0;
        else if (patientUrgency[i] == 3) surchargePercent = 50.0;
    double discountPercent = (patientAges[i] < 5 || patientAges[i] > 65) ? 15.0 : 0.0;

    printf("\n===============================================================\n");
    printf("                SMART HOSPITAL ADMISSION & BILL                \n");
    printf("---------------------------------------------------------------\n");
    printf("Patient ID                  : PAT-%04d\n", 1000+i+1);
    printf("Patient Name                : %s\n", patientNames[i]);
    printf("Age                         : %d Years%s\n", patientAges[i],
           (patientAges[i]<5 || patientAges[i]>65) ? " (15% Subsidy Eligible)" : "");
    printf("Specialty                   : %s\n", specialtyNames[patientSpecialty[i]-1]);
    if (patientWard[i] != 0)
        printf("Assigned Ward               : %s (Bed #%02d)\n", wardNames[patientWard[i]-1], i+1);
    else
        printf("Assigned Ward               : Outpatient\n");
    printf("Urgency Level               : Level %d\n", patientUrgency[i]);
    printf("---------------------------------------------------------------\n");
    printf("Base Consultation Fee       : LKR %8.2f\n", baseFee);
    printf("Emergency Surcharge         : LKR %8.2f (%.0f%%)\n", surcharge, surchargePercent);
    printf("Ward Stay Cost (%d Days)     : LKR %8.2f\n", patientDays[i], wardCost);
    printf("---------------------------------------------------------------\n");
    printf("Gross Total Bill            : LKR %8.2f\n", grossTotal);
    printf("Age Subsidy Discount        : LKR -%8.2f (%.0f%%)\n", discount, discountPercent);
    printf("---------------------------------------------------------------\n");
    printf("Final Payable Amount        : LKR %8.2f\n", finalAmount);
    printf("Estimated Waiting Time      : %.2f mins\n", waitTime);
    printf("===============================================================\n");

    printf("\nPress Enter to continue...");
    getchar(); getchar();

    system("cls");
}

double calcWaitingTime(int specialtyID) {
    return specialtyQueue[specialtyID-1] * specialtyTimes[specialtyID-1];
}

double calcEmergencySurcharge(int urgency, double baseFee) {
    if (urgency == 2) return baseFee * 0.20;
    if (urgency == 3) return baseFee * 0.50;
    return 0.0;
}

double calcWardCost(int wardID, int days) {
    if (wardID == 0) return 0.0;
    return wardRates[wardID-1] * days;
}

double calcAgeDiscount(int age, double grossTotal) {
    if (age < 5 || age > 65) return grossTotal * 0.15;
    return 0.0;
}

void sortPatientsByUrgency() {
    if (patientCount == 0) {
        printf("\nNo patients registered yet. Please register patients first.\n");
        return;
    }

    for (int i = 0; i < patientCount-1; i++) {
        for (int j = i+1; j < patientCount; j++) {
            if (patientUrgency[i] < patientUrgency[j]) {
                char tempName[50];
                strcpy(tempName, patientNames[i]);
                strcpy(patientNames[i], patientNames[j]);
                strcpy(patientNames[j], tempName);

                int tempAge = patientAges[i];
                patientAges[i] = patientAges[j];
                patientAges[j] = tempAge;

                int tempUrg = patientUrgency[i];
                patientUrgency[i] = patientUrgency[j];
                patientUrgency[j] = tempUrg;

                int tempSpec = patientSpecialty[i];
                patientSpecialty[i] = patientSpecialty[j];
                patientSpecialty[j] = tempSpec;

                int tempWard = patientWard[i];
                patientWard[i] = patientWard[j];
                patientWard[j] = tempWard;

                int tempDays = patientDays[i];
                patientDays[i] = patientDays[j];
                patientDays[j] = tempDays;
            }
        }
    }
    printf("\nPatients sorted by urgency successfully.\n");
}

void listPatients() {
    if (patientCount == 0) {
        printf("\nNo patients registered yet. Please register patients first.\n");
        return;
    }

    printf("\n==============================================================================\n");
    printf("---------------        Patient List (Sorted by Urgency)        ---------------\n");
    printf("==============================================================================\n");
    for (int i = 0; i < patientCount; i++) {
        printf("ID %d | Name: %s | Age: %d | Urgency: %d | Specialty: %s\n",
               i+1, patientNames[i], patientAges[i], patientUrgency[i],
               specialtyNames[patientSpecialty[i]-1]);
    }
}

void viewRegisteredPatients() {
    if (patientCount == 0) {
        printf("\nNo patients registered yet. Please register patients first.\n");
        return;
    }

    printf("\n===========================================================\n");
    printf("-------  Already Registered Patients & Their Bills  -------\n");
    printf("===========================================================\n");
    for (int i = 0; i < patientCount; i++) {
        generateBill(i);
    }
}

void admissionsReport() {
    if (patientCount == 0) {
        printf("\nNo patients registered yet. Please register patients first.\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        system("cls");
        return;
    }

    printf("\n=======================================\n");
    printf("------     Admissions Report     ------\n");
    printf("=======================================\n");
    printf("Total Patients Registered: %d\n", patientCount);

    printf("\nPress Enter to continue...");
    getchar(); getchar();
    system("cls");
}

void wardOccupancyReport() {
    if (patientCount == 0) {
        printf("\nNo patients registered yet. Please register patients first.\n");
        printf("\nPress Enter to continue...");
        getchar(); getchar();
        system("cls");
        return;
    }

    int wardCounts[NUM_WARDS] = {0};
    for (int i = 0; i < patientCount; i++) {
        if (patientWard[i] != 0) {
            wardCounts[patientWard[i]-1]++;
        }
    }

    printf("\n=======================================\n");
    printf("-----    Ward Occupancy Report    -----\n");
    printf("=======================================\n");
    for (int w = 0; w < NUM_WARDS; w++) {
        printf("%-16s: %d patients\n", wardNames[w], wardCounts[w]);
    }

    printf("\nPress Enter to continue...");
    getchar(); getchar();
    system("cls");
}



