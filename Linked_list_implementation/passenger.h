#ifndef PASSEN_TRAIN
#define PASSEN_TRAIN
// BT20CSE120

typedef struct Passenger
{
    int PNR;
    char firstName[25];
    char lastName[25];
    int age;

    int train_id;
    char boarding_train[50]; // train name;
    char boarding_station[50];
    char destination_station[50];
    int travel_date[3];

    int traveling_class;
    int coach_no;
    int seat_no;

    int booked_num;   // booking order
    int hasToPromote; // want to promote to  higher coaches or not.

    struct Passenger *next;

} Passenger;

Passenger *get_new_passenger(Passenger *pngr_data);

#endif