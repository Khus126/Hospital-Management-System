#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_appointments 200

typedef struct patient
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[10];
    struct patient *next;
}patient;

typedef struct doctor
{
    int id;
    char name[50];
    char specialization[50];
    struct doctor *next;
}doctor;

typedef struct 
{
    int patientID;
    int doctorID;
    char date[15];    
}appointent;

typedef struct bill
{
    int billID;
    int patientID;
    float amount;
    struct Bill *left,*right;
}Bill;




int main()
{
    int choice;
    while(1)
    {
        printf("--- HOSPTAL MANAGEMENT SYSTEM--- \n");
        printf("1.Add Patients \n 2.View Patients \n 3.Add Doctor \n 4.View Doctors\n");
        printf("5.Add Appointment \n 6.View appointments \n 7. Add Bill\n 8. View Bills");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1: 
                patients = addPatients(patients);
                break;
            case 2:
                displayPatients(patients);
                break;
            case 3:
                doctors = adddoctor(doctors);
        
        }
    }
}
Patient* addPatient(Patient *head)
{
    Patient *newnode = (Patient*)malloc(sizeof(Patient));
    printf("\nEnter Patient ID:");
    
}