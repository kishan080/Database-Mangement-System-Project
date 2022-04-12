#ifndef TRAIN_SYSTEM
#define TRAIN_SYSTEM

#define TRAIN_SIZE 4

#include "passenger.h"
#include "train.h"
// all fxn defination
Train train_list[TRAIN_SIZE];

void intialize_train_list();
void insert(Passenger *pngr_node);
Travel_Date *search_travel_date(Travel_Date *lptr, int *date);
int insert_at_travel_date(Travel_Date *nptr, Passenger *pngr_data);

int campare_date(int date1[], int date2[]);
Travel_Date *insert_new_travelDate(Travel_Date *lptr, Travel_Date *new_node);

int allocate_seat_util(Passenger *pngr_data, int max_coach, int max_seat, int Coach_class[max_coach][max_seat], int *coach_bkd, int *seat_bkd);
int allocate_seat(Travel_Date *nptr, Passenger *pngr_data);

Passenger *insert_passenger(Passenger *lptr, Passenger *pngr_data);

void Delete();                                                            // Delete fxn..for removeing passenger from data
Passenger *delete_pngr(Passenger *lptr, int pnr, Travel_Date *lptr_date); // delete from
// passseger list

void get_listDestination(); // get list passenger with same train id and destionation station
void Sort_Travel_date();    // Q4
void SortTrain();           // Q5
void PromotePassenger();    // Q6
#endif