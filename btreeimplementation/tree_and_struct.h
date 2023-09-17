#ifndef TREE_AND_STRUCT_H
#define TREE_AND_STRUCT_H

#define MAX 4
#define MIN 2

typedef enum
{
    FALSE,
    TRUE
} Boolean;
//---------------------------------------------------------------------------------------//
//-------------------------------Passenger Struct----------------------------------------//
//---------------------------------------------------------------------------------------//
typedef struct Passenger_tag
{
    int PNR; // unique id for passenger
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
    int booked_num; // booking order

} Passenger;
//---------------------------------------------------------------------------------------//
//-----------------------------Passenger B Tree and Btree Fxn----------------------------//
//---------------------------------------------------------------------------------------//
typedef struct Passenger_Btree_Node
{
    int count;                                    // present no of key
    Passenger *key[MAX + 1];                      // no of key (1 to MAX) stores address to data  for
                                                  // for easy coying of data
    struct Passenger_Btree_Node *branch[MAX + 1]; // children (0 to MAX)
} pNode;

//---------------------------------------------------------------------------------------//
Passenger *get_new_passenger();

pNode *make_pNode();
pNode *Search_pngr(pNode *root, int target, int *pos);
Boolean Search_pNode(pNode *p, int target, int *pos);
pNode *insert_pngr(pNode *root, Passenger *new_key);
Boolean PushDown_pngr(pNode *root, Passenger *new_key, Passenger **x, pNode **xr);
void PushIn_pngr(Passenger *x, pNode *xr, pNode *p, int k);
void Split_pngr(Passenger *x, pNode *xr, pNode *root, int k, Passenger **y, pNode **yr);
void inorder_pngr(pNode *root);
void Display_pngr(Passenger *pngr_data);

// deletion
pNode *Delete_pngr(pNode *root, int PNR);
Boolean RecDelete_pngr(pNode *root, int PNR);

void Successor_pngr(pNode *p, int k); // replace p->key[k] with its successor
void Remove_pngr(pNode *p, int k);    // delete p->key[k];
void Restore_pngr(pNode *p, int k);   // restore devoid node in tree i.e (count <min)
void MoveLeft_pngr(pNode *p, int k);  // move a key to left
void MoveRight_pngr(pNode *p, int k); // move a key to right
void Combine_pngr(pNode *p, int k);   // merger parent key "k" with there children or combine sibling

//------------------------------------------------------------------------------------------------------//
//-----------------------------------Travel Date Struct ------------------------------------------------//
//-----------------Stored info about particular train id on partucular traveling date of train---------//
//------------------------------------------------------------------------------------------------------//
// max no of coaches for traveling class
#define SL_COACH 3
#define AC1_COACH 2
#define AC2_COACH 2
#define AC3_COACH 2
// max seat in each coaches
#define SL_SEAT 3
#define AC1_SEAT 2
#define AC2_SEAT 3
#define AC3_SEAT 3

typedef struct travel_date_tag
{
    int date[3];
    int cnt;            // no of passenger
    int booking_number; // genrate booking number

    // to keep record of which seat is already booked.
    // we will store passenger_id as value of this array..
    int sleeper_class[SL_COACH][SL_SEAT]; // sleeper class
    int AC_class1[AC1_COACH][AC1_SEAT];   // 1 AC
    int AC_class2[AC2_COACH][AC2_SEAT];   // 2 AC
    int AC_class3[AC3_COACH][AC3_SEAT];   // 3 AC

    int book_upto[4][2];
    // keep record of upto which coach ,and seat no booking is done.
    // 1st dimension represent 4 type coach
    // [0][]=sleeper
    // [1][]=1 AC
    // [2][]=2 AC
    // [3][]=3 AC
    // 2nd dimension [][2] => [][0]==coach,[][1] seat no
    pNode *pngr_root; // passenger tree root pointer

} Travel_Date;

//------------------------------------------------------------------------------------------------------//
//----------------------------------Travel Date Btree and there Btree Fxn-------------------------------//
//------------------------------------------------------------------------------------------------------//
typedef struct travel_Btree_Node
{
    int count;                                 // present no of key
    Travel_Date *key[MAX + 1];                 // no of key (1 to MAX) stores address to data  for
                                               // for easy coying of data
    struct travel_Btree_Node *branch[MAX + 1]; // children (0 to MAX)
} tNode;
//------------------------------------------------------------------------------------------------------//
Travel_Date *get_travel_date(int Date[]);

tNode *make_tNode();
tNode *Search_travel(tNode *root, int target[], int *pos);
Boolean Search_tNode(tNode *p, int target[], int *pos);
tNode *insert_travel(tNode *root, Travel_Date *new_key);
Boolean PushDown_travel(tNode *root, Travel_Date *new_key, Travel_Date **x, tNode **xr);
void PushIn_travel(Travel_Date *x, tNode *xr, tNode *p, int k);
void Split_travel(Travel_Date *x, tNode *xr, tNode *root, int k, Travel_Date **y, tNode **yr);
void inorder_travel(tNode *root);
void display_travel(Travel_Date *node);

// deletion---travel
tNode *Delete_travel(tNode *root, int date[]);
Boolean RecDelete_travel(tNode *root, int date[]);

void copy_travel(Travel_Date *d1, Travel_Date *d2);
void Successor_travel(tNode *p, int k); // replace p->key[k] with its successor
void Remove_travel(tNode *p, int k);    // delete p->key[k];
void Restore_travel(tNode *p, int k);   // restore devoid node in tree i.e (count <min)
void MoveLeft_travel(tNode *p, int k);  // move a key to left
void MoveRight_travel(tNode *p, int k); // move a key to right
void Combine_travel(tNode *p, int k);

//------------------------------------------------------------------------------------------------------//
//-------------------------------TRAIN Struct Stores Info of Particular train --------------------------//
//------------------------------------------------------------------------------------------------------//
typedef struct train
{
    int id;           // train id
    char Name[50];    // train name
    int num;          // num of travel date so far
    tNode *date_root; // head to travel_date
                      // which will contain all data on particular date
} Train;
//------------------------------------------------------------------------------------------------------//

void INSERT(Train *TRAIN, int train_size, Passenger *pngr_data);
int allocate_seat(Travel_Date *nptr, Passenger *pngr_data);
int allocate_seat_util(Passenger *pngr_data, int max_coach, int max_seat, int Coach_class[max_coach][max_seat], int *coach_bkd, int *seat_bkd);
void DELETE(Train *TRAIN, int train_size);

//-------------------------------------------------------------------------------------------//
//-----------Utilty Fxn and UTility struct---------------------------------------------------//
//-------------------------------------------------------------------------------------------//

typedef struct get_list_des_tag
{
    int pnr;
    char destination[50];
    struct get_list_des_tag *next;
} get_list_des;

typedef struct sortTrain_tag
{
    int train_id;
    int cnt;
    int travel_date[3];

    struct sortTrain_tag *next;
} Train_sort_Node;

typedef struct sortTravel_tag
{
    int date[3]; // travel_date;
    char destination[50];
    struct sortTravel_tag *next;
} sortTravel_Node;

//-------------------------------------------------------------------------------------------//
//-----------------------Operational Fxn ,eg SortTRain---utilit fxn required for them -------//
//-------------------------------------------------------------------------------------------//
get_list_des *get_list_des_node(int pnr, char destination[]);
Train_sort_Node *get_trainSort_node(int trn_id, int ct, int date[]);
sortTravel_Node *get_sortTravelNode(int tr_date[], char destination_st[]);

//---------------------------------------------------------
void Traverse_date_tree(tNode *root, Train_sort_Node **head, int t_id);
void SortTrain(Train *TRAIN, int train_size); // Sort Train Q5
//-----------------------===============================================--------------------//
void Traverse_pngr(pNode *root, int pnr, sortTravel_Node **head);
void Traverse_travelSort(tNode *root, int pnr, sortTravel_Node **head);
void Sort_Travel_date(Train *TRAIN, int train_size); // Sort by travel Q4
//-----------------------===============================================--------------------//
//==========================================================================================//
void Traverse_getList_pngr(pNode *root, get_list_des **head);
void Traverse_getList(tNode *root);
void get_listDestination(Train *TRAIN, int train_size); // get list Q3
//=========================================================================================//
void Range_search(tNode *root, int low[], int high[]);
void RangeSearch_travelDate(Train *TRAIN, int train_size);
//=========================================================================================//
//---------------Merge sort Fxn for Q3 to Q6-----------------------------------------------//
//============================get list util================================================//
get_list_des *findMid_des(get_list_des *lptr);
get_list_des *Merge_dest(get_list_des *lptr, get_list_des *nptr);
get_list_des *MergeSort_dest(get_list_des *lptr);
//========================================================================================//
//========================================================================================//
// sort list of stuct Train_sort_Node which store info acc to no of passenger on train on given date

Train_sort_Node *findMid_trainSort(Train_sort_Node *lptr);
Train_sort_Node *Merge_trainSort(Train_sort_Node *lptr, Train_sort_Node *nptr);
Train_sort_Node *MergeSort_trainSort(Train_sort_Node *lptr);

//=======================================================================================//
//=======================================================================================//
//=======================================================================================//
// sort list of struct sortTravel_Node which stor info of destination station with travel date.
sortTravel_Node *findMid_sortTravel(sortTravel_Node *lptr);
sortTravel_Node *Merge_sortTravel(sortTravel_Node *lptr, sortTravel_Node *nptr);
sortTravel_Node *MergeSort_sortTravel(sortTravel_Node *lptr);
//======================================================================================//
//===========================UTILTY FXN=================================================//

void print_class(int x);
int campare_date(int date1[], int date2[]);
//======================================================================================//
//======================================================================================//
// Read Train Database from Console write to file...
Train *READ_TRAIN_CONSOLE(int *train_size, int *max_size);
// read from File and intilaize Train Data
Train *intialize_train(int *train_Size, int *max_size);
void Display_all(Train *TRAIN, int Train_Size);                        // Diaplay all Data database
Train *Insert_new_Train(Train *TRAIN, int *Train_size, int *max_size); // Insert new data in Trainbase
//======================================================================================//
#endif