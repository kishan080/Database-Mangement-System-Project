#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utility_fxn.h"

void print_class(int x)
{
    if (x == 0)
        printf("sleeper\n");
    else if (x == 1)
        printf("AC1\n");
    else if (x == 2)
        printf("AC2\n");
    else if (x == 3)
        printf("AC3\n");
}

int campare_date(int date1[], int date2[])
{
    int ret_val;

    ret_val = date1[2] - date2[2]; // check year

    if (ret_val == 0)
        ret_val = date1[1] - date2[1]; // check month

    if (ret_val == 0)
        ret_val = date1[0] - date2[0]; // check date..

    return ret_val;
}

void Display_pngr(Passenger *pngr_data)
{
    printf("==================================================\n");
    printf("PNR: %d", pngr_data->PNR);
    printf("first Name: %s\n", pngr_data->firstName);
    printf("last Name: %s\n", pngr_data->lastName);
    printf("age: %d\n", pngr_data->age);
    printf("train id: %d\n", pngr_data->train_id);
    printf("boarding train: %s\n", pngr_data->boarding_train);
    printf("boarding station: %s\n", pngr_data->boarding_station);
    printf("destination station: %s\n", pngr_data->destination_station);
    printf("traveling class: ");
    print_class(pngr_data->traveling_class);

    printf("Traveling date: %d/%d/%d \n", pngr_data->travel_date[0], pngr_data->travel_date[1], pngr_data->travel_date[2]);

    printf("coach no: %d\n", pngr_data->coach_no);
    printf("seat no: %d\n", pngr_data->seat_no);
    printf("want to promote(1=yes,0=no): %d\n", pngr_data->hasToPromote);

    printf("==================================================\n");
}

void display_pngr_list(Passenger *lptr)
{
    if (lptr == NULL)
    {
        printf("Empty passenger list!!\n");
    }
    else
    {
        while (lptr != NULL)
        {
            Display_pngr(lptr);
            lptr = lptr->next;
        }
    }
}

void Display_all()
{
    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        printf("==============================================\n");
        printf("---TRAIN ID: %d---NAME: %s\n", i, train_list[i].Name);
        printf("==============================================\n");

        Travel_Date *lptr_date = train_list[i].date_head;

        if (lptr_date == NULL)
        {
            printf("Empty _ train!!\n");
        }
        else
        {
            while (lptr_date != NULL)
            {
                printf("---Travel date: %d/%d/%d ---\n", lptr_date->date[0], lptr_date->date[1], lptr_date->date[2]);

                printf("----------------------------------------------\n");
                printf("---Reservation list---: \n");
                display_pngr_list(lptr_date->head_pngr);
                printf("----------------------------------------------\n");

                lptr_date = lptr_date->next;
            }
        }
        printf("==============================================\n");
    }
}

//======================================================================================//
//======================================================================================//
//======================================================================================//
Passenger *findMid_des(Passenger *lptr)
{
    Passenger *nptr = NULL;
    if (lptr != NULL && lptr->next != NULL)
    {
        Passenger *slow = lptr;
        Passenger *fast = lptr->next;
        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        nptr = slow->next;
        slow->next = NULL;
    }
    return nptr;
}

Passenger *Merge_dest(Passenger *lptr, Passenger *nptr)
{
    Passenger *result, *ptr1, *ptr2, *tail;
    ptr1 = lptr;
    ptr2 = nptr;
    if (strcmp(ptr1->destination_station, ptr2->destination_station) == -1)
    {
        result = ptr1;
        ptr1 = ptr1->next;
    }
    else
    {
        result = ptr2;
        ptr2 = ptr2->next;
    }
    tail = result;

    while (ptr1 != NULL && ptr2 != NULL)
    {
        int flag = strcmp(ptr1->destination_station, ptr2->destination_station);
        if (flag == 0 || flag == -1)
        {
            tail->next = ptr1;
            tail = ptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            tail->next = ptr2;
            tail = ptr2;
            ptr2 = ptr2->next;
        }
    }
    if (ptr1 == NULL)
    {
        tail->next = ptr2;
    }
    else
    {
        tail->next = ptr1;
    }
    return result;
}

Passenger *MergeSort_dest(Passenger *lptr)
{
    Passenger *nptr;
    if (lptr != NULL && lptr->next != NULL)
    {
        nptr = findMid_des(lptr);
        lptr = MergeSort_dest(lptr);
        nptr = MergeSort_dest(nptr);
        lptr = Merge_dest(lptr, nptr);
    }
    return lptr;
}

Passenger *sort_acc_to_dest(Passenger *lptr)
{
    return MergeSort_dest(lptr);
}
//======================================================================================//
//======================================================================================//
Train_sort_Node *findMid_trainSort(Train_sort_Node *lptr)
{
    Train_sort_Node *nptr = NULL;
    if (lptr != NULL && lptr->next != NULL)
    {
        Train_sort_Node *slow = lptr;
        Train_sort_Node *fast = lptr->next;
        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        nptr = slow->next;
        slow->next = NULL;
    }
    return nptr;
}

Train_sort_Node *Merge_trainSort(Train_sort_Node *lptr, Train_sort_Node *nptr)
{
    Train_sort_Node *result, *ptr1, *ptr2, *tail;
    ptr1 = lptr;
    ptr2 = nptr;
    if (ptr1->cnt < ptr2->cnt)
    {
        result = ptr1;
        ptr1 = ptr1->next;
    }
    else
    {
        result = ptr2;
        ptr2 = ptr2->next;
    }
    tail = result;

    while (ptr1 != NULL && ptr2 != NULL)
    {

        if (ptr1->cnt <= ptr2->cnt)
        {
            tail->next = ptr1;
            tail = ptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            tail->next = ptr2;
            tail = ptr2;
            ptr2 = ptr2->next;
        }
    }
    if (ptr1 == NULL)
    {
        tail->next = ptr2;
    }
    else
    {
        tail->next = ptr1;
    }
    return result;
}

Train_sort_Node *MergeSort_trainSort(Train_sort_Node *lptr)
{
    Train_sort_Node *nptr;
    if (lptr != NULL && lptr->next != NULL)
    {
        nptr = findMid_trainSort(lptr);
        lptr = MergeSort_trainSort(lptr);
        nptr = MergeSort_trainSort(nptr);
        lptr = Merge_trainSort(lptr, nptr);
    }
    return lptr;
}
//======================================================================================//
//======================================================================================//
sortTravel_Node *findMid_sortTravel(sortTravel_Node *lptr)
{
    sortTravel_Node *nptr = NULL;
    if (lptr != NULL && lptr->next != NULL)
    {
        sortTravel_Node *slow = lptr;
        sortTravel_Node *fast = lptr->next;
        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        nptr = slow->next;
        slow->next = NULL;
    }
    return nptr;
}

sortTravel_Node *Merge_sortTravel(sortTravel_Node *lptr, sortTravel_Node *nptr)
{
    sortTravel_Node *result, *ptr1, *ptr2, *tail;
    ptr1 = lptr;
    ptr2 = nptr;
    if (campare_date(ptr1->date, ptr2->date) == -1)
    {
        result = ptr1;
        ptr1 = ptr1->next;
    }
    else
    {
        result = ptr2;
        ptr2 = ptr2->next;
    }
    tail = result;

    while (ptr1 != NULL && ptr2 != NULL)
    {
        int flag = campare_date(ptr1->date, ptr2->date);
        if (flag == 0 || flag == -1)
        {
            tail->next = ptr1;
            tail = ptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            tail->next = ptr2;
            tail = ptr2;
            ptr2 = ptr2->next;
        }
    }
    if (ptr1 == NULL)
    {
        tail->next = ptr2;
    }
    else
    {
        tail->next = ptr1;
    }
    return result;
}

sortTravel_Node *MergeSort_sortTravel(sortTravel_Node *lptr)
{
    sortTravel_Node *nptr;
    if (lptr != NULL && lptr->next != NULL)
    {
        nptr = findMid_sortTravel(lptr);
        lptr = MergeSort_sortTravel(lptr);
        nptr = MergeSort_sortTravel(nptr);
        lptr = Merge_sortTravel(lptr, nptr);
    }
    return lptr;
}
//======================================================================================//
//======================================================================================//
//======================================================================================//

int mycmp(Passenger *ptr1, Passenger *ptr2)
{
    int ret_val;

    int class1 = 3 - ptr1->traveling_class;
    int class2 = 3 - ptr2->traveling_class;

    if (class1 < class2)
        ret_val = -1;
    else if (class1 > class2)
        ret_val = 1;
    else if (class1 == class2)
    {
        if (ptr1->booked_num < ptr2->booked_num)
            ret_val = -1;
        else if (ptr1->booked_num > ptr2->booked_num)
            ret_val = 1;
        else
            ret_val = 0;
    }
    return ret_val;
}

Passenger *findMid_promote(Passenger *lptr)
{
    Passenger *nptr = NULL;
    if (lptr != NULL && lptr->next != NULL)
    {
        Passenger *slow = lptr;
        Passenger *fast = lptr->next;
        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        nptr = slow->next;
        slow->next = NULL;
    }
    return nptr;
}

Passenger *Merge_promote(Passenger *lptr, Passenger *nptr)
{
    Passenger *result, *ptr1, *ptr2, *tail;
    ptr1 = lptr;
    ptr2 = nptr;
    if (mycmp(ptr1, ptr2) == -1)
    {
        result = ptr1;
        ptr1 = ptr1->next;
    }
    else
    {
        result = ptr2;
        ptr2 = ptr2->next;
    }
    tail = result;

    while (ptr1 != NULL && ptr2 != NULL)
    {
        int flag = mycmp(ptr1, ptr2);
        if (flag == 0 || flag == -1)
        {
            tail->next = ptr1;
            tail = ptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            tail->next = ptr2;
            tail = ptr2;
            ptr2 = ptr2->next;
        }
    }
    if (ptr1 == NULL)
    {
        tail->next = ptr2;
    }
    else
    {
        tail->next = ptr1;
    }
    return result;
}

Passenger *MergeSort_promote(Passenger *lptr)
{
    Passenger *nptr;
    if (lptr != NULL && lptr->next != NULL)
    {
        nptr = findMid_promote(lptr);
        lptr = MergeSort_promote(lptr);
        nptr = MergeSort_promote(nptr);
        lptr = Merge_promote(lptr, nptr);
    }
    return lptr;
}
//======================================================================================//
//======================================================================================//
// FILE OPERATION FXN
void write_train_list()
{
    FILE *fptr = fopen("train.txt", "wb");

    if (fptr == NULL)
    {
        printf("ERROR!!\n");
        exit(1);
    }
    Train *temp = (Train *)malloc(sizeof(Train));

    for (int i = 0; i < TRAIN_SIZE; i++)
    {

        // temp->id = i;
        // printf("enter train id %d name: ", i);
        // scanf("%s", temp->Name);
        // temp->num = 0;
        // temp->date_head = NULL;
        // fwrite(temp, sizeof(Train), 1, fptr);
        fwrite(&train_list[i], sizeof(Train), 1, fptr);
    }
    free(temp);
    fclose(fptr);
}
void read_train_list()
{
    FILE *fptr = fopen("train.txt", "rb");

    if (fptr == NULL)
    {
        printf("ERROR!!\n");
        exit(1);
    }

    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        fread(&train_list[i], sizeof(Train), 1, fptr);
        train_list[i].date_head = NULL;
    }
    fclose(fptr);
}
void write_Travel_date()
{
    FILE *fptr = fopen("Travel_date.txt", "wb");
    if (fptr == NULL)
    {
        printf("ERROR!\n");
        exit(1);
    }

    // Travel_Date temp = (Travel_Date *)malloc(sizeof(Travel_Date));

    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        Travel_Date *lptr = train_list[i].date_head;

        while (lptr != NULL)
        {
            fwrite(lptr, sizeof(Travel_Date), 1, fptr);
            lptr = lptr->next;
        }
        train_list[i].date_head = NULL;
    }

    fclose(fptr);
}
void read_Travel_date()
{
    FILE *fptr = fopen("Travel_date.txt", "rb");
    if (fptr == NULL)
    {
        printf("ERROR!\n");
        exit(1);
    }

    int dummy_date[3] = {0, 0, 0};
    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        printf("%d ", train_list[i].num);
        for (int j = 0; j < train_list[i].num; j++)
        {
            Travel_Date *temp = get_travel_date(dummy_date);

            fread(temp, sizeof(Travel_Date), 1, fptr);

            train_list[i].date_head = insert_new_travelDate(train_list[i].date_head, temp);
            train_list[i].date_head->head_pngr = NULL;
        }
    }

    fclose(fptr);
}

void read_passenger()
{
    FILE *fptr = fopen("passenger.txt", "rb");
    if (fptr == NULL)
    {
        printf("ERROR!\n");
        exit(1);
    }

    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        Travel_Date *lptr = train_list[i].date_head;

        while (lptr != NULL)
        {
            for (int j = 0; j < (lptr->cnt); j++)
            {
                Passenger *temp = (Passenger *)malloc(sizeof(Passenger));
                temp->next = NULL;

                fread(temp, sizeof(Passenger), 1, fptr);
                lptr->head_pngr = insert_passenger(lptr->head_pngr, temp);
            }
            lptr = lptr->next;
        }
    }

    fclose(fptr);
}
void write_passenger()
{
    FILE *fptr = fopen("passenger.txt", "wb");
    if (fptr == NULL)
    {
        printf("ERROR!\n");
        exit(1);
    }

    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        Travel_Date *lptr = train_list[i].date_head;

        while (lptr != NULL)
        {
            Passenger *temp = lptr->head_pngr;

            while (temp != NULL)
            {
                fwrite(temp, sizeof(Passenger), 1, fptr);
                temp = temp->next;
            }
            lptr->head_pngr = NULL;
            lptr = lptr->next;
        }
    }

    fclose(fptr);
}

void READ()
{
    read_train_list();
    printf("Train\n");
    read_Travel_date();
    printf("Travel\n");
    read_passenger();
    printf("passenger\n");
}

void WRITE()
{
    write_passenger();
    write_Travel_date();
    write_train_list();
}