#ifndef UTIL
#define UTIL

#include "train_system.h"

void print_class(int x);
int campare_date(int date1[], int date2[]);
void Display_pngr(Passenger *pngr_data);
void display_pngr_list(Passenger *lptr);
void Display_all();

//======================================================================================//
// sort list acc to destination station ..in lexographical order
Passenger *findMid_des(Passenger *lptr);
Passenger *Merge_dest(Passenger *lptr, Passenger *nptr);
Passenger *MergeSort_dest(Passenger *lptr);
Passenger *sort_acc_to_dest(Passenger *lptr);
//======================================================================================//
//======================================================================================//
// sort list of stuct Train_sort_Node which store info acc to no of passenger on train on given date
Train_sort_Node *findMid_trainSort(Train_sort_Node *lptr);
Train_sort_Node *Merge_trainSort(Train_sort_Node *lptr, Train_sort_Node *nptr);
Train_sort_Node *MergeSort_trainSort(Train_sort_Node *lptr);
//======================================================================================//
//======================================================================================//
//======================================================================================//
// sort list of struct sortTravel_Node which stor info of destination station with travel date.
sortTravel_Node *findMid_sortTravel(sortTravel_Node *lptr);
sortTravel_Node *Merge_sortTravel(sortTravel_Node *lptr, sortTravel_Node *nptr);
sortTravel_Node *MergeSort_sortTravel(sortTravel_Node *lptr);
//======================================================================================//
//======================================================================================//
//======================================================================================//
// campare two passenger based  traveling class sleeper<AC3<AC3<AC1 if two class same then acc to booking number
int mycmp(Passenger *ptr1, Passenger *ptr2);
// sort list according to above fxn
Passenger *findMid_promote(Passenger *lptr);
Passenger *Merge_promote(Passenger *lptr, Passenger *nptr);
Passenger *MergeSort_promote(Passenger *lptr);
//======================================================================================//
//======================================================================================//
// FILE OPERATION FXN
void write_train_list(); // write struct Train data to train.txt
void write_Travel_date();
void write_passenger();
void WRITE();

void read_train_list();
void read_Travel_date();
void read_passenger();
void READ();

#endif