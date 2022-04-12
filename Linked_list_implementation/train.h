#ifndef TRAIN
#define TRAIN
// BT20CSE120

#include "passenger.h"

// keep record of all data from booking to passenger on particular date..

typedef struct travel_date_tag
{
    int date[3];
    // to keep record of which seat is already booked.
    // we will store passenger_id as value of this array..
    int cnt;            // no od passenger
    int booking_number; // genrate booking number

    int sleeper_class[6][72]; // sleeper class
    int AC_class1[2][22];     // 1 AC
    int AC_class2[3][46];     // 2 AC
    int AC_class3[4][62];     // 3 AC

    int book_upto[4][2];
    // keep record of upto which coach ,and seat no booking is done.
    // 1st dimension represent 4 type coach
    // [0][]=sleeper
    // [1][]=1 AC
    // [2][]=2 AC
    // [3][]=3 AC
    // 2nd dimension [][2] => [][0]==coach,[][1] seat no
    Passenger *head_pngr;

    struct travel_date_tag *next;
} Travel_Date;

// train data
typedef struct train
{
    int id;                 // train id
    char Name[50];          // train name
    int num;                // num of travel date
    Travel_Date *date_head; // head to travel_date
    // which will contain all data on particular date

} Train;

Travel_Date *get_travel_date(int Date[]);

typedef struct sortTrain_tag
{
    int train_id;
    int cnt;
    int travel_date[3];

    struct sortTrain_tag *next;
} Train_sort_Node;

Train_sort_Node *get_trainSort_node(int trn_id, int ct, int date[]);

typedef struct sortTravel_tag
{
    int date[3]; // travel_date;
    char destination[50];
    struct sortTravel_tag *next;
} sortTravel_Node;

sortTravel_Node *get_sortTravelNode(int tr_date[], char destination_st[]);

#endif