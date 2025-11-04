#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_APPOINTMENTS 200

typedef struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    struct Patient *next;
} Patient;

typedef struct Doctor {
    int id;
    char name[50];
    char specialization[50];
    struct Doctor *next;
} Doctor;

typedef struct {
    int patientID;
    int doctorID;
    char date[15];
} Appointment;

typedef struct Bill {
    int billID;
    int patientID;
    float amount;
    struct Bill *left, *right;
} Bill;

// functions
Patient* addPatient(Patient *head);
void displayPatients(Patient *head);
Doctor* addDoctor(Doctor *head);
void displayDoctors(Doctor *head);
void addAppointment(Appointment *appointments, int *count);
void displayAppointments(Appointment *appointments, int count);
Bill* insertBill(Bill *root, int billID, int patientID, float amount);
void inorderBills(Bill *root);
void freeBills(Bill *root);

// file handling
void savePatients(Patient *head);
Patient* loadPatients();
void saveDoctors(Doctor *head);
Doctor* loadDoctors();
void saveAppointments(Appointment *appointments, int count);
int loadAppointments(Appointment *appointments);
void saveBills(Bill *root);
Bill* loadBills();

// patient
Patient* addPatient(Patient *head) {
    Patient *newNode = (Patient*)malloc(sizeof(Patient));
    printf("\nEnter Patient ID: ");
    scanf("%d", &newNode->id);
    printf("\nEnter Name: ");
    scanf("%s", newNode->name);
    printf("\nEnter Age: ");
    scanf("%d", &newNode->age);
    printf("\nEnter Gender: ");
    scanf("%s", newNode->gender);
    printf("\nEnter Disease: ");
    scanf("%s", newNode->disease);
    newNode->next = head;
    printf("\nPatient added successfully!\n");
    return newNode;
}

void displayPatients(Patient *head) {
    if (!head) {
        printf("No patients found.\n");
        return;
    }
    printf("\nPatient List\n");
    while (head) {
        printf("ID: %d | Name: %s | Age: %d | Gender: %s | Disease: %s\n",
             head->id, head->name, head->age, head->gender, head->disease);
        head = head->next;
    }
}

void savePatients(Patient *head) {
    FILE *fp = fopen("patients.dat", "wb");
    if (!fp) return;
    while (head) {
        fwrite(head, sizeof(Patient) - sizeof(Patient*), 1, fp);
        head = head->next;
    }
    fclose(fp);
}

Patient* loadPatients() {
    FILE *fp = fopen("patients.dat", "rb");
    if (!fp) return NULL;
    Patient temp, *head = NULL;
    while (fread(&temp, sizeof(Patient) - sizeof(Patient*), 1, fp)) {
        Patient *newNode = (Patient*)malloc(sizeof(Patient));
        *newNode = temp;
        newNode->next = head;
        head = newNode;
    }
    fclose(fp);
    return head;
}

// doctor
Doctor* addDoctor(Doctor *head) {
    Doctor *newNode = (Doctor*)malloc(sizeof(Doctor));
    printf("\nEnter Doctor ID: ");
    scanf("%d", &newNode->id);
    printf("\nEnter Name: ");
    scanf("%s", newNode->name);
    printf("\nEnter Specialization: ");
    scanf("%s", newNode->specialization);
    newNode->next = head;
    printf("\nDoctor added successfully\n");
    return newNode;
}

void displayDoctors(Doctor *head) {
    if (!head) {
        printf("No doctors found.\n");
        return;
    }
    printf("\nDoctor List \n");
    while (head) {
        printf("ID: %d | Name: %s | Specialization: %s\n",
               head->id, head->name, head->specialization);
        head = head->next;
    }
}

void saveDoctors(Doctor *head) {
    FILE *fp = fopen("doctors.dat", "wb");
    if (!fp) return;
    while (head) {
        fwrite(head, sizeof(Doctor) - sizeof(Doctor*), 1, fp);
        head = head->next;
    }
    fclose(fp);
}

Doctor* loadDoctors() {
    FILE *fp = fopen("doctors.dat", "rb");
    if (!fp) return NULL;
    Doctor temp, *head = NULL;
    while (fread(&temp, sizeof(Doctor) - sizeof(Doctor*), 1, fp)) {
        Doctor *newNode = (Doctor*)malloc(sizeof(Doctor));
        *newNode = temp;
        newNode->next = head;
        head = newNode;
    }
    fclose(fp);
    return head;
}

// appointment
void addAppointment(Appointment *appointments, int *count) {
    if (*count >= MAX_APPOINTMENTS) {
        printf("Appointment list full!\n");
        return;
    }
    printf("\nEnter Patient ID: ");
    scanf("%d", &appointments[*count].patientID);
    printf("Enter Doctor ID: ");
    scanf("%d", &appointments[*count].doctorID);
    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%s", appointments[*count].date);
    (*count)++;
    printf("Appointment added successfully!\n");
}

void displayAppointments(Appointment *appointments, int count) {
    if (count == 0) {
        printf("No appointments found.\n");
        return;
    }
    printf("\n--- Appointments ---\n");
    for (int i = 0; i < count; i++) {
        printf("Patient ID: %d | Doctor ID: %d | Date: %s\n",
               appointments[i].patientID, appointments[i].doctorID, appointments[i].date);
    }
}

void saveAppointments(Appointment *appointments, int count) {
    FILE *fp = fopen("appointments.dat", "wb");
    if (!fp) return;
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(appointments, sizeof(Appointment), count, fp);
    fclose(fp);
}

int loadAppointments(Appointment *appointments) {
    FILE *fp = fopen("appointments.dat", "rb");
    if (!fp) return 0;
    int count = 0;
    fread(&count, sizeof(int), 1, fp);
    fread(appointments, sizeof(Appointment), count, fp);
    fclose(fp);
    return count;
}

// bill 
Bill* insertBill(Bill *root, int billID, int patientID, float amount) {
    if (!root) {
        Bill *newNode = (Bill*)malloc(sizeof(Bill));
        newNode->billID = billID;
        newNode->patientID = patientID;
        newNode->amount = amount;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (billID < root->billID)
        root->left = insertBill(root->left, billID, patientID, amount);
    else
        root->right = insertBill(root->right, billID, patientID, amount);
    return root;
}

void inorderBills(Bill *root) {
    if (root) {
        inorderBills(root->left);
        printf("Bill ID: %d | Patient ID: %d | Amount: %.2f\n",
               root->billID, root->patientID, root->amount);
        inorderBills(root->right);
    }
}

void freeBills(Bill *root) {
    if (!root) return;
    freeBills(root->left);
    freeBills(root->right);
    free(root);
}


void write_node(Bill *n, FILE *fp) {
    if (!n) return;
    fwrite(&n->billID, sizeof(int), 1, fp);
    fwrite(&n->patientID, sizeof(int), 1, fp);
    fwrite(&n->amount, sizeof(float), 1, fp);
    write_node(n->left, fp);
    write_node(n->right, fp);
}

void saveBills(Bill *root) {
    FILE *fp = fopen("bills.dat", "wb");
    if (!fp) return;
    write_node(root, fp);
    fclose(fp);
}



Bill* loadBills() {
    FILE *fp = fopen("bills.dat", "rb");
    if (!fp) return NULL;
    Bill *root = NULL;
    int billID, patientID;
    float amount;
    while (fread(&billID, sizeof(int), 1, fp) == 1) {
        if (fread(&patientID, sizeof(int), 1, fp) != 1) break;
        if (fread(&amount, sizeof(float), 1, fp) != 1) break;
        root = insertBill(root, billID, patientID, amount);
    }
    fclose(fp);
    return root;
}



int main() {
    Patient *patients = loadPatients();
    Doctor *doctors = loadDoctors();
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount = loadAppointments(appointments);
    Bill *bills = NULL;

    int choice;
    while (1) {
        printf("\n---HOSPITAL MANAGEMENT SYSTEM---\n");
        printf("1. Add Patient\n2. View Patients\n3. Add Doctor\n4. View Doctors\n");
        printf("5. Add Appointment\n6. View Appointments\n7. Add Bill\n8. View Bills\n9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: patients = addPatient(patients); break;
            case 2: displayPatients(patients); break;
            case 3: doctors = addDoctor(doctors); break;
            case 4: displayDoctors(doctors); break;
            case 5: addAppointment(appointments, &appointmentCount); break;
            case 6: displayAppointments(appointments, appointmentCount); break;
            case 7: {
                int billID, patientID;
                float amount;
                printf("Enter Bill ID: ");
                scanf("%d", &billID);
                printf("Enter Patient ID: ");
                scanf("%d", &patientID);
                printf("Enter Amount: ");
                scanf("%f", &amount);
                bills = insertBill(bills, billID, patientID, amount);
                printf("Bill added successfully!\n");
                break;
            }
            case 8: inorderBills(bills); break;
            case 9:
                printf("Saving data & exiting...\n");
                savePatients(patients);
                saveDoctors(doctors);
                saveAppointments(appointments, appointmentCount);
                printf(" All data saved.\n");
                freeBills(bills);
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
