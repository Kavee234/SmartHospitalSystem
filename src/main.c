#include <stdio.h>

#define NUM_SPECIALTIES 4
#define NUM_WARDS 4
#define MAX_BEDS 20

const char *specialtyNames[NUM_SPECIALTIES] = {"General Practice (OPD)","Paediatrics","Cardiology","Neurology"};

const double specialtyFees[NUM_SPECIALTIES] = {1500.0, 2500.0, 4500.0, 5000.0};
const int specialtyTimes[NUM_SPECIALTIES] = {15, 20, 30, 30};
const int specialtyCaps[NUM_SPECIALTIES] = {30, 20, 12, 10};

const char *wardNames[NUM_WARDS] = {"General Ward","Paediatric Ward","Surgical Ward","ICU"};

const double wardRates[NUM_WARDS] = {3000.0, 6000.0, 12000.0, 25000.0};
const int wardCapacities[NUM_WARDS] = {20, 10, 10, 5};

int bedOccupancy[NUM_WARDS][MAX_BEDS] = {0};

int main() {
    printf("--- Doctor Specialties ---\n");
    for (int i = 0; i < NUM_SPECIALTIES; i++) {
        printf("ID %d: %-22s | Fee: LKR %.2f | Time: %d mins | Daily Patient Cap: %d\n",
               i+1, specialtyNames[i], specialtyFees[i], specialtyTimes[i], specialtyCaps[i]);
    }

    printf("\n--- Hospital Wards ---\n");
    for (int i = 0; i < NUM_WARDS; i++) {
        printf("ID %d: %-15s | Rate: LKR %.2f | Capacity: %d beds\n",
               i+1, wardNames[i], wardRates[i], wardCapacities[i]);
    }
    return 0;
}
