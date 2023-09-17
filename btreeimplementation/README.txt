NAME:VERMA KISHAN RAKESH
ROLL: BT20CSE120

---------------------------------DSPD-2 ASSIGNMENT-------------------------------------
Data Structure Used: B Tree

---------------------------------------------------------------------------------------
typedef struct train
{
    int id;           // train id
    char Name[50];    // train name
    int num;          // num of travel date so far
    tNode *date_root; // head to travel_date
                      // which will contain all data on particular date
} Train; 
first we have "TRAIN" which is array of Train Database Which stores data Train id ,Name
of Train ,num = no of travel date for which booking is done so far and date_root which 
is root if BTree which Travel dates of Train as a key in tree .......................
-Assumption:-
    -TRAIN Database are stored as array becuz Train are usually fixed in railways
     system is not so often that we add new train to system or remove it from system
     so considering this fact for faster access i have created perfect hash fxn in which 
      index=train_id -1 and Array size intially kept greater then Train available in system
      so we can add new train if required and in worst case train_size==max_size so program 
      will create new array twice the previous size one and copy data in new one and delete
      the previous (dynamic array-);
---------------------------------------------------------------------------------------
In Traveldate Node of Tree is contain all info about given train on particular travel date such
no of passenger seat allocation data and also root of passenger data of given travel date
 there is seperate Tree base for Every Travel date of Train of passenger---------------
-Assumption:-
    i have assume that a particular run every day (i.e Travel time <= 1 day) without break for easy of implemntaion.
- getListDestion -> This Fxn Print Destination station in sorted order for evry travel date for particular 
                    Train id becuz it make more sense to have lsit for evry Travel date instead of combined data and just simply printed destiation in sorted order so eventually all passenger will be together with same destiation.
---------------------------------------------------------------------------------------
Range Search: for range search instead of Train no i have implemented it on travel date for particular train_id becuz the way i have structured the data it will be super easy for train id therefore to implement 
range search on b tree i have done it on Travel date which is a BTree
 
 use: command to compile in command prompt
   gcc -Wall main.c train_sys_main.c travel_tree.c passenger_tree.c utility.c -o out
