#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "train_system.h"
#include "utility_fxn.h"

void intialize_train_list()
{
    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        train_list[i].id = i;
        train_list[i].num = 0;
        train_list[i].date_head = NULL;
    }
    // this can also be done manullay from console
    // but let assume train database already present
    strcpy(train_list[0].Name, "jaipur_exp");
    strcpy(train_list[1].Name, "bikaner");
    strcpy(train_list[2].Name, "rajdani");
    strcpy(train_list[3].Name, "flying_rani");
    printf("-----intialised---\n");
}

sortTravel_Node *get_sortTravelNode(int tr_date[], char destination_st[])
{
    sortTravel_Node *new_node = (sortTravel_Node *)malloc(sizeof(sortTravel_Node));

    new_node->date[0] = tr_date[0];
    new_node->date[1] = tr_date[1];
    new_node->date[2] = tr_date[2];

    strcpy(new_node->destination, destination_st);

    new_node->next = NULL;

    return new_node;
}

Train_sort_Node *get_trainSort_node(int trn_id, int ct, int date[])
{
    Train_sort_Node *new_node = (Train_sort_Node *)malloc(sizeof(Train_sort_Node));

    new_node->train_id = trn_id;
    new_node->cnt = ct;
    new_node->travel_date[0] = date[0];
    new_node->travel_date[1] = date[1];
    new_node->travel_date[2] = date[2];

    new_node->next = NULL;
    return new_node;
}

Passenger *get_new_passenger(Passenger *pngr_data)
{
    Passenger *new_pngr = (Passenger *)malloc(sizeof(Passenger));
    new_pngr->next = NULL;

    new_pngr->PNR = pngr_data->PNR;
    strcpy(new_pngr->firstName, pngr_data->firstName);
    strcpy(new_pngr->lastName, pngr_data->lastName);
    new_pngr->age = pngr_data->age;
    new_pngr->train_id = pngr_data->train_id;
    strcpy(new_pngr->boarding_train, train_list[pngr_data->train_id].Name);
    strcpy(new_pngr->boarding_station, pngr_data->boarding_station);
    strcpy(new_pngr->destination_station, pngr_data->destination_station);
    new_pngr->traveling_class = pngr_data->traveling_class;

    new_pngr->travel_date[0] = pngr_data->travel_date[0];
    new_pngr->travel_date[1] = pngr_data->travel_date[1];
    new_pngr->travel_date[2] = pngr_data->travel_date[2];
    new_pngr->hasToPromote = pngr_data->hasToPromote;

    return new_pngr;
}

Travel_Date *get_travel_date(int Date[])
{
    Travel_Date *new_node = (Travel_Date *)malloc(sizeof(Travel_Date));

    new_node->next = NULL;

    new_node->cnt = 0;
    new_node->booking_number = 0;

    new_node->date[0] = Date[0];
    new_node->date[1] = Date[1];
    new_node->date[2] = Date[2];

    // intialise book upto;
    // -----------------------------------
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
            new_node->book_upto[i][j] = -1;
    }
    // -----------------------------------
    /* int sleeper_class[6][72]; // sleeper class
    int AC_class1[2][22];     // 1 AC
    int AC_class2[3][46];     // 2 AC
    int AC_class3[4][62];     // 3 AC*/
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 72; j++)
        {
            new_node->sleeper_class[i][j] = -1;
        }
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 22; j++)
        {
            new_node->AC_class1[i][j] = -1;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 46; j++)
        {
            new_node->AC_class2[i][j] = -1;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 62; j++)
        {
            new_node->AC_class3[i][j] = -1;
        }
    }
    // -----------------------------------

    new_node->head_pngr = NULL;
    return new_node;
}

void insert(Passenger *pngr_node)
{
    Travel_Date *lptr = train_list[pngr_node->train_id].date_head;

    Travel_Date *temp_nptr = search_travel_date(lptr, pngr_node->travel_date);

    int status;

    status = insert_at_travel_date(temp_nptr, pngr_node);

    if (status == 0)
    {
        printf("Reservation unsuccesseful!! ..\n");
        free(pngr_node);
    }
    else
    {
        printf("Reservation successful..!\n");
    }
}

Travel_Date *search_travel_date(Travel_Date *lptr, int *date)
{
    Travel_Date *temp = lptr;
    Travel_Date *ret_node = NULL;

    int flag = 1;
    while (temp != NULL && flag)
    {
        if (campare_date(temp->date, date) == 0)
        {
            ret_node = temp;
            flag = 0;
        }
        temp = temp->next;
    }

    return ret_node;
}

int insert_at_travel_date(Travel_Date *nptr, Passenger *pngr_data)
{
    int ret_val;

    if (nptr == NULL)
    {
        Travel_Date *new_node = get_travel_date(pngr_data->travel_date);

        train_list[pngr_data->train_id].date_head = insert_new_travelDate(train_list[pngr_data->train_id].date_head, new_node);
        train_list[pngr_data->train_id].num++;
        ret_val = insert_at_travel_date(new_node, pngr_data);
    }
    else
    {
        ret_val = allocate_seat(nptr, pngr_data);

        if (ret_val == 1)
        {
            nptr->head_pngr = insert_passenger(nptr->head_pngr, pngr_data);
            pngr_data->booked_num = nptr->booking_number++;
            nptr->cnt++; // ek passenger added
        }
    }

    return ret_val;
}

Travel_Date *insert_new_travelDate(Travel_Date *lptr, Travel_Date *new_node)
{
    if (lptr == NULL)
    {
        lptr = new_node;
    }
    else
    {

        Travel_Date *temp = lptr;
        Travel_Date *prev = NULL;
        while (temp != NULL && campare_date(temp->date, new_node->date) < 0)
        {
            prev = temp;
            temp = temp->next;
        }

        if (prev == NULL)
        {
            new_node->next = lptr;
            lptr = new_node;
        }
        else
        {
            new_node->next = temp;
            prev->next = new_node;
        }
    }

    return lptr;
}

int allocate_seat_util(Passenger *pngr_data, int max_coach, int max_seat, int Coach_class[max_coach][max_seat], int *coach_bkd, int *seat_bkd)
{
    int ret_val = 0;

    if (*coach_bkd == -1 && *seat_bkd == -1) // empty train
    {                                        // first booking
        (*coach_bkd)++;
        (*seat_bkd)++;
        Coach_class[*coach_bkd][*seat_bkd] = pngr_data->PNR;
        pngr_data->coach_no = *coach_bkd;
        pngr_data->seat_no = *seat_bkd;
        ret_val = 1;
    }
    else if (*seat_bkd < max_seat - 1) // check in current coaches if there any seat
    {
        (*seat_bkd)++;
        Coach_class[*coach_bkd][*seat_bkd] = pngr_data->PNR;
        pngr_data->coach_no = *coach_bkd;
        pngr_data->seat_no = *seat_bkd;
        ret_val = 1;
    } // check  for next coaches if there is available
    else if (*coach_bkd < max_coach - 1)
    {
        (*coach_bkd)++;
        (*seat_bkd)++;
        Coach_class[*coach_bkd][*seat_bkd] = pngr_data->PNR;
        pngr_data->coach_no = *coach_bkd;
        pngr_data->seat_no = *seat_bkd;
        ret_val = 1; // success
    }

    if (ret_val == 0) // check missing gap that were created while deletion
    {
        for (int i = 0; i < max_coach; i++)
        {
            for (int j = 0; j < max_seat; j++)
            {
                if (Coach_class[i][j] == -1)
                {
                    Coach_class[i][j] = pngr_data->PNR;
                    pngr_data->coach_no = i;
                    pngr_data->seat_no = j;
                    ret_val = 1; // success
                }
            }
        }
    }

    return ret_val;
}

int allocate_seat(Travel_Date *nptr, Passenger *pngr_data)
{
    int ret_val = 0;

    switch (pngr_data->traveling_class)
    {
    case 0:
        // coach no and seat upto which reservation is done
        {
            int coach_no_bkd = nptr->book_upto[0][0];
            int seat_no_bkd = nptr->book_upto[0][1];

            ret_val = allocate_seat_util(pngr_data, 6, 72, nptr->sleeper_class, &coach_no_bkd, &seat_no_bkd);

            nptr->book_upto[0][0] = coach_no_bkd;
            nptr->book_upto[0][1] = seat_no_bkd;
        }

        break;

    case 1:
    {
        int coach_no_bkd = nptr->book_upto[1][0];
        int seat_no_bkd = nptr->book_upto[1][1];

        ret_val = allocate_seat_util(pngr_data, 2, 22, nptr->AC_class1, &coach_no_bkd, &seat_no_bkd);

        nptr->book_upto[1][0] = coach_no_bkd;
        nptr->book_upto[1][1] = seat_no_bkd;
    }
    break;
    case 2:
    {
        int coach_no_bkd = nptr->book_upto[2][0];
        int seat_no_bkd = nptr->book_upto[1][1];

        ret_val = allocate_seat_util(pngr_data, 3, 46, nptr->AC_class2, &coach_no_bkd, &seat_no_bkd);

        nptr->book_upto[2][0] = coach_no_bkd;
        nptr->book_upto[2][1] = seat_no_bkd;
    }
    break;
    case 3:
    {
        int coach_no_bkd = nptr->book_upto[3][0];
        int seat_no_bkd = nptr->book_upto[3][1];

        ret_val = allocate_seat_util(pngr_data, 4, 62, nptr->AC_class2, &coach_no_bkd, &seat_no_bkd);

        nptr->book_upto[3][0] = coach_no_bkd;
        nptr->book_upto[3][1] = seat_no_bkd;
    }
    break;
    default:
        printf("Error in allocation !!\n");
        break;
    }

    return ret_val;
}

Passenger *insert_passenger(Passenger *lptr, Passenger *pngr_data)
{
    pngr_data->next = lptr;
    lptr = pngr_data;

    return lptr;
}

void Delete()
{
    int pnr;
    int trn_id;
    int trvl_date[3];

    printf("Enter PNR,train_id,and travel_date to cancel reservation: \n");
    printf(" Enter PNR: ");
    scanf("%d", &pnr);

    printf("---------------------------------------\n");
    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        printf("Train id: %d Name: %s\n", i, train_list[i].Name);
    }
    printf("---------------------------------------\n");

    do
    {
        printf("Enter train_id(see above list):");
        scanf("%d", &trn_id);
    } while (trn_id < 0 && trn_id >= TRAIN_SIZE);

    printf(" Enter travel date(format: dd<space >mm<space>yyyy): ");
    scanf("%d", &trvl_date[0]);
    scanf("%d", &trvl_date[1]);
    scanf("%d", &trvl_date[2]);

    Travel_Date *lptr = train_list[trn_id].date_head;
    Travel_Date *prev_date = NULL;
    while (lptr != NULL && campare_date(lptr->date, trvl_date) != 0)
    {
        prev_date = lptr;
        lptr = lptr->next;
    }

    if (lptr == NULL)
    {
        printf("Error! not valid data to be cancel reservation!!\n");
        return;
    }
    else
    {

        lptr->head_pngr = delete_pngr(lptr->head_pngr, pnr, lptr);
        lptr->cnt--;
    }

    printf("Your reservation is cancel successfully!!\n");

    if (lptr->head_pngr == NULL)
    {
        if (prev_date == NULL)
        {
            train_list[trn_id].date_head = train_list[trn_id].date_head->next;
        }
        else
        {
            prev_date->next = lptr->next;
        }

        free(lptr);
    }
}

Passenger *delete_pngr(Passenger *lptr, int pnr, Travel_Date *lptr_date)
{
    Passenger *temp = lptr;
    Passenger *prev = NULL;

    while (temp != NULL && temp->PNR != pnr)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("No such passenger data \n");
        return lptr;
    }

    if (prev == NULL)
    {
        lptr = lptr->next;
    }
    else
    {
        prev->next = temp->next;
    }

    // deallocate seat..

    switch (temp->traveling_class)
    {
    case 0:
    {
        lptr_date->sleeper_class[temp->coach_no][temp->seat_no] = -1;
    }
    break;
    case 1:
    {
        lptr_date->AC_class1[temp->coach_no][temp->seat_no] = -1;
    }
    break;
    case 2:
    {
        lptr_date->AC_class2[temp->coach_no][temp->seat_no] = -1;
    }
    break;
    case 3:
    {
        lptr_date->AC_class3[temp->coach_no][temp->seat_no] = -1;
    }
    break;

    default:
        break;
    }

    free(temp);

    return lptr;
}

void get_listDestination()
{
    int trn_id;
    printf("Enter train_id: ");
    scanf("%d", &trn_id);

    Travel_Date *lptr = train_list[trn_id].date_head;

    printf("---------------------------------------------------------------------\n");
    printf(":list of passenger with same train id and same destination station:");
    printf("---------------------------------------------------------------------\n");

    while (lptr != NULL)
    {
        printf("TRAIN ID: %d\t", trn_id);
        printf(" Travel Date: %d/%d/%d\n", lptr->date[0], lptr->date[1], lptr->date[2]);
        lptr->head_pngr = sort_acc_to_dest(lptr->head_pngr);
        Passenger *temp = lptr->head_pngr;

        while (temp != NULL)
        {

            printf("PNR: %d\t Name: %s %s\t Destination station: %s\n", temp->PNR, temp->firstName, temp->lastName, temp->destination_station);

            temp = temp->next;
        }

        printf("---------------------------------------------------------------------\n");
        lptr = lptr->next;
    }
}

void SortTrain()
{
    Train_sort_Node *head = NULL;

    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        Travel_Date *lptr = train_list[i].date_head;

        if (lptr != NULL)
        {
            while (lptr != NULL)
            {
                Train_sort_Node *temp = get_trainSort_node(i, lptr->cnt, lptr->date);
                // insert at head;
                temp->next = head;
                head = temp;

                lptr = lptr->next;
            }
        }
    }

    // sort
    head = MergeSort_trainSort(head);
    // display
    printf("---------------------sort by Passenger on Train--------------------------\n");
    Train_sort_Node *nptr = head;
    while (nptr != NULL)
    {
        printf("TRAIN ID: %d\tTravel Date: %d/%d/%d\tNo of passenger: %d\n", nptr->train_id, nptr->travel_date[0], nptr->travel_date[1], nptr->travel_date[2], nptr->cnt);
        nptr = nptr->next;
    }
    printf("-------------------------------------------------------------------------\n");
    // freelist

    Train_sort_Node *temp = head;

    while (head != NULL)
    {
        head = head->next;
        free(temp);
        temp = head;
    }
}

void Sort_Travel_date()
{
    int pnr;
    printf("Enter pnr: ");
    scanf("%d", &pnr);

    sortTravel_Node *head = NULL;

    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        Travel_Date *lptr = train_list[i].date_head;

        while (lptr != NULL)
        {
            Passenger *temp = lptr->head_pngr;

            int found = 0;
            while (temp != NULL && found == 0)
            {
                if (temp->PNR == pnr)
                {
                    sortTravel_Node *nptr = get_sortTravelNode(lptr->date, temp->destination_station);
                    // insert at head;
                    nptr->next = head;
                    head = nptr;
                    found = 1; // breaking this loop becuz one person can travel only once through
                    // particular train in one day.
                }

                temp = temp->next;
            }
            lptr = lptr->next;
        }
    }

    // sort
    if (head == NULL)
    {
        printf("passenger with PNR: %d not found!!\n", pnr);
        return;
    }

    head = MergeSort_sortTravel(head);

    // display
    printf("-------------------sort by Travel date -------------------------\n");
    printf("-: PNR : %d :-\n", pnr);

    sortTravel_Node *temp = head;

    while (temp != NULL)
    {
        printf("Travel Date: %d/%d/%d\t Destination_station: %s\n", temp->date[0], temp->date[1], temp->date[2], temp->destination);

        temp = temp->next;
    }
    printf("---------------------------------------------------------------\n");

    sortTravel_Node *nptr = head;

    while (head != NULL)
    {
        head = head->next;
        free(nptr);
        nptr = head;
    }
}
//======================================================================================//

void PromotePassenger()
{
    int trn_id;
    int trvl_date[3];

    printf("Enter Train_id: ");
    scanf("%d", &trn_id);
    printf("Enter travel_date: ");
    scanf("%d", &trvl_date[0]);
    scanf("%d", &trvl_date[1]);
    scanf("%d", &trvl_date[2]);

    Travel_Date *lptr = train_list[trn_id].date_head;

    while (lptr != NULL && campare_date(lptr->date, trvl_date) != 0)
    {
        lptr = lptr->next;
    }

    if (lptr == NULL)
    {
        printf("No passenger for given Travel date\n");
    }
    else
    {
        lptr->head_pngr = MergeSort_promote(lptr->head_pngr);

        Passenger *nptr = lptr->head_pngr;

        while (nptr != NULL)
        {
            if (nptr->hasToPromote == 1 && nptr->traveling_class != 1) // AC1 cannot promoted
            {
                int status, coach, seat;
                coach = nptr->coach_no;
                seat = nptr->seat_no;

                switch (nptr->traveling_class)
                {
                case 0:
                {
                    nptr->traveling_class = 3; // trying to allocate to AC3
                    status = allocate_seat(lptr, nptr);
                    if (status == 1)
                    {
                        printf("PNR: %d is promoted to AC3 from Sleeper\n", nptr->PNR);
                        lptr->sleeper_class[coach][seat] = -1;
                        nptr->hasToPromote = 0;
                    }
                    else
                    {
                        nptr->traveling_class = 0;
                    }
                }
                break;
                case 2:
                {
                    nptr->traveling_class = 1; // trying to allocate to AC1
                    status = allocate_seat(lptr, nptr);
                    if (status == 1)
                    {
                        printf("PNR: %d is promoted to AC1 from AC2\n", nptr->PNR);
                        lptr->sleeper_class[coach][seat] = -1;
                        nptr->hasToPromote = 0;
                    }
                    else
                    {
                        nptr->traveling_class = 2;
                    }
                }
                break;
                case 3:
                {
                    nptr->traveling_class = 2; // trying to allocate to AC2
                    status = allocate_seat(lptr, nptr);
                    if (status == 1)
                    {
                        printf("PNR: %d is promoted to AC2 from AC3\n", nptr->PNR);
                        lptr->sleeper_class[coach][seat] = -1;
                        nptr->hasToPromote = 0;
                    }
                    else
                    {
                        nptr->traveling_class = 3;
                    }
                }
                break;

                default:
                    break;
                }
            }
            nptr = nptr->next;
        }
    }
}
