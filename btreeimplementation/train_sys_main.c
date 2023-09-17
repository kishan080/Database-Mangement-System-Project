#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_and_struct.h"

//-------------------------------------------------------------//
// no of train in database currently.
//-----------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------//

void INSERT(Train *TRAIN, int train_size, Passenger *pngr_data)
{
    tNode *trvl_root = TRAIN[(pngr_data->train_id) - 1].date_root;

    int pos;
    tNode *found = Search_travel(trvl_root, pngr_data->travel_date, &pos);

    if (found == NULL)
    {
        // create new travel date on which pngr want to travel
        Travel_Date *new_trvl = get_travel_date(pngr_data->travel_date);

        // allocate seat on that travel date
        int flag = allocate_seat(new_trvl, pngr_data);

        // insert that travel date in trvl date root of train
        trvl_root = insert_travel(trvl_root, new_trvl);

        // insert pngr in created trvel node
        new_trvl->pngr_root = insert_pngr(new_trvl->pngr_root, pngr_data);

        printf("Reservation Done successfully!!\n");

        TRAIN[(pngr_data->train_id) - 1].num++; // one more trvel date added
        new_trvl->cnt++;                        // passenger+1
    }
    else
    {
        Travel_Date *node = found->key[pos];

        pNode *found = Search_pngr(node->pngr_root, pngr_data->PNR, &pos);

        if (found == NULL) // if key is not duplicate
        {
            int flag = allocate_seat(node, pngr_data);
            int pos;

            if (flag)
            {
                node->pngr_root = insert_pngr(node->pngr_root, pngr_data);
                printf("Reservation Done successfully!!\n");
            }
            else
            {
                printf("\nReserversation unsuccessful !!!\n");
            }

            node->cnt++; // no of passenger incresed by 1
        }
        else
        {
            printf("\nERROR: passenger id exist on given date!!\n");
        }
    }

    TRAIN[(pngr_data->train_id) - 1].date_root = trvl_root;
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

            ret_val = allocate_seat_util(pngr_data, SL_COACH, SL_SEAT, nptr->sleeper_class, &coach_no_bkd, &seat_no_bkd);

            nptr->book_upto[0][0] = coach_no_bkd;
            nptr->book_upto[0][1] = seat_no_bkd;
        }

        break;

    case 1:
    {
        int coach_no_bkd = nptr->book_upto[1][0];
        int seat_no_bkd = nptr->book_upto[1][1];

        ret_val = allocate_seat_util(pngr_data, AC1_COACH, AC1_SEAT, nptr->AC_class1, &coach_no_bkd, &seat_no_bkd);

        nptr->book_upto[1][0] = coach_no_bkd;
        nptr->book_upto[1][1] = seat_no_bkd;
    }
    break;
    case 2:
    {
        int coach_no_bkd = nptr->book_upto[2][0];
        int seat_no_bkd = nptr->book_upto[1][1];

        ret_val = allocate_seat_util(pngr_data, AC2_COACH, AC2_SEAT, nptr->AC_class2, &coach_no_bkd, &seat_no_bkd);

        nptr->book_upto[2][0] = coach_no_bkd;
        nptr->book_upto[2][1] = seat_no_bkd;
    }
    break;
    case 3:
    {
        int coach_no_bkd = nptr->book_upto[3][0];
        int seat_no_bkd = nptr->book_upto[3][1];

        ret_val = allocate_seat_util(pngr_data, AC3_COACH, AC3_SEAT, nptr->AC_class2, &coach_no_bkd, &seat_no_bkd);

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

void DELETE(Train *TRAIN, int train_size)
{
    int pnr;
    int trn_id;
    int trvl_date[3];

    printf("Enter PNR,train_id,and travel_date to cancel reservation: \n");
    printf(" Enter PNR: ");
    scanf("%d", &pnr);

    printf("---------------------------------------\n");
    for (int i = 0; i < train_size; i++)
    {
        printf("Train id: %d Name: %s\n", i + 1, TRAIN[i].Name);
    }
    printf("---------------------------------------\n");

    do
    {
        printf("Enter train_id(see above list):");
        scanf("%d", &trn_id);
    } while (trn_id < 1 && trn_id > train_size);

    printf("Enter travel date(format: dd<space >mm<space>yyyy): ");
    scanf("%d", &trvl_date[0]);
    scanf("%d", &trvl_date[1]);
    scanf("%d", &trvl_date[2]);

    tNode *date_root = TRAIN[trn_id - 1].date_root;

    int pos;
    tNode *found_trvl = Search_travel(date_root, trvl_date, &pos);

    if (found_trvl == NULL)
    {
        printf("No data for given travel date!!!\n");
    }
    else
    {
        int k;
        Travel_Date *trv_temp = found_trvl->key[pos];
        pNode *found_pngr = Search_pngr(trv_temp->pngr_root, pnr, &k);

        if (found_pngr == NULL)
        {
            printf("passenger not found on given travel date!!\n");
        }
        else
        {
            Passenger *temp = found_pngr->key[k];

            // free up seat
            switch (temp->traveling_class)
            {
            case 0:
            {
                trv_temp->sleeper_class[temp->coach_no][temp->seat_no] = -1;
            }
            break;
            case 1:
            {
                trv_temp->AC_class1[temp->coach_no][temp->seat_no] = -1;
            }
            break;
            case 2:
            {
                trv_temp->AC_class2[temp->coach_no][temp->seat_no] = -1;
            }
            break;
            case 3:
            {
                trv_temp->AC_class3[temp->coach_no][temp->seat_no] = -1;
            }
            }

            trv_temp->pngr_root = Delete_pngr(trv_temp->pngr_root, pnr);

            if (trv_temp->pngr_root == NULL) // if train became empty delte trvel node also
            {
                TRAIN[trn_id - 1].date_root = Delete_travel(date_root, trvl_date);
            }

            printf("\n---Reservation canceled successfully!!---\n");
        }
    }
}

//-----------------------===============================================---------------------------//
//-----------------------===============================================---------------------------//
//-----------------------===============================================---------------------------//
//-------------------------------------------------------------------------------------------//
void Traverse_date_tree(tNode *root, Train_sort_Node **head, int t_id)
{
    if (root != NULL)
    {
        for (int i = 1; i <= root->count; i++)
        {
            Traverse_date_tree(root->branch[i - 1], head, t_id);

            Train_sort_Node *temp = get_trainSort_node(t_id, root->key[i]->cnt, root->key[i]->date);
            // insert at head;
            temp->next = (*head);
            (*head) = temp;
        }

        Traverse_date_tree(root->branch[root->count], head, t_id);
    }
}
//-------------------------------------------------------------------------------------------//

void SortTrain(Train *TRAIN, int train_size)
{
    Train_sort_Node *head = NULL;

    for (int i = 0; i < train_size; i++)
    {
        tNode *trv_root = TRAIN[i].date_root;

        if (trv_root != NULL)
        {
            Traverse_date_tree(trv_root, &head, i + 1);
        }
    }

    // sort
    head = MergeSort_trainSort(head);
    // display
    printf("\n---------------------sort by Passenger on Train--------------------------\n");
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
//-----------------------===============================================---------------------------//

//-----------------------===============================================---------------------------//
void Traverse_pngr(pNode *root, int pnr, sortTravel_Node **head)
{
    if (root != NULL)
    {
        for (int i = 1; i <= root->count; i++)
        {
            Traverse_pngr(root->branch[i - 1], pnr, head);

            if (root->key[i]->PNR == pnr)
            {
                sortTravel_Node *nptr = get_sortTravelNode(root->key[i]->travel_date, root->key[i]->destination_station);
                // insert at head;
                nptr->next = *head;
                *head = nptr;
            }
        }

        Traverse_pngr(root->branch[root->count], pnr, head);
    }
}
//-----------------------===============================================---------------------------//
void Traverse_travelSort(tNode *root, int pnr, sortTravel_Node **head)
{
    if (root != NULL)
    {

        for (int i = 1; i <= root->count; i++)
        {
            Traverse_travelSort(root->branch[i - 1], pnr, head);
            Traverse_pngr(root->key[i]->pngr_root, pnr, head);
        }
        Traverse_travelSort(root->branch[root->count], pnr, head);
    }
}
//-----------------------===============================================---------------------------//
void Sort_Travel_date(Train *TRAIN, int train_size)
{
    int pnr;
    printf("Enter pnr: ");
    scanf("%d", &pnr);

    sortTravel_Node *head = NULL;

    for (int i = 0; i < train_size; i++)
    {
        tNode *trv_root = TRAIN[i].date_root;

        if (trv_root != NULL)
        {
            Traverse_travelSort(trv_root, pnr, &head);
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
void Traverse_getList_pngr(pNode *root, get_list_des **head)
{
    if (root != NULL)
    {
        for (int i = 1; i <= root->count; i++)
        {
            Traverse_getList_pngr(root->branch[i - 1], head);

            get_list_des *temp = get_list_des_node(root->key[i]->PNR, root->key[i]->destination_station);

            temp->next = *head;
            *head = temp;
        }
        Traverse_getList_pngr(root->branch[root->count], head);
    }
}
//-----------------------===============================================---------------------------//
void Traverse_getList(tNode *root)
{
    if (root != NULL)
    {
        for (int i = 1; i <= root->count; i++)
        {
            Traverse_getList(root->branch[i - 1]);

            Travel_Date *temp = root->key[i];
            printf("\n---------------------------------------------------------------------\n");
            printf("______________________TRAVEL DATE : %d/%d/%d ______________________\n", temp->date[0], temp->date[1], temp->date[2]);

            get_list_des *head = NULL;

            Traverse_getList_pngr(root->key[i]->pngr_root, &head);

            head = MergeSort_dest(head);
            get_list_des *temp2 = head;

            while (temp2 != NULL)
            {
                printf("PNR: %d\t Destination station: %s\n", temp2->pnr, temp2->destination);
                temp2 = temp2->next;
            }
            // free list
            temp2 = head;
            while (head != NULL)
            {
                head = head->next;
                free(temp2);
                temp2 = head;
            }
        }

        Traverse_getList(root->branch[root->count]);
    }
}
//-----------------------===============================================---------------------------//
void get_listDestination(Train *TRAIN, int train_size)
{
    int trn_id;
    for (int i = 0; i < train_size; i++)
    {
        printf("Train id: %d Name: %s\n", i + 1, TRAIN[i].Name);
    }
    printf("---------------------------------------\n");

    do
    {
        printf("Enter train_id(see above list):");
        scanf("%d", &trn_id);
    } while (trn_id < 1 && trn_id > train_size);

    tNode *trv_root = TRAIN[trn_id - 1].date_root;

    printf("\n---------------------------------------------------------------------\n");
    printf("List of passenger with train id: %d and same destination station \n", trn_id);
    printf("---------------------------------------------------------------------\n");

    if (trv_root != NULL)
    {
        Traverse_getList(trv_root);
    }
}

//-----------------------===============================================---------------------------//

//-----------------------===============================================---------------------------//

void Range_search(tNode *root, int low[], int high[])
{
    if (root != NULL)
    {
        for (int i = 1; i <= root->count; i++)
        {
            int low_flag = campare_date(root->key[i]->date, low);
            int high_flag = campare_date(root->key[i]->date, high);

            if (low_flag == 1)
            {
                Range_search(root->branch[i - 1], low, high);
            }

            if ((low_flag == 0 || low_flag == 1) && (high_flag == 0 || high_flag == -1))
            {
                Travel_Date *tmp = root->key[i];
                printf("Travel Date: %d/%d/%d \t", tmp->date[0], tmp->date[1], tmp->date[2]);
                printf("No of passenger: %d\n", tmp->cnt);
            }

            if (high_flag == 1)
                break;
        }

        if (campare_date(root->key[root->count]->date, high) == -1)
            Range_search(root->branch[root->count], low, high);
    }
}
//-----------------------===============================================---------------------------//
void RangeSearch_travelDate(Train *TRAIN, int train_size)
{
    int trn_id;
    int From[3];
    int To[3];

    printf("---------------------------------------\n");
    for (int i = 0; i < train_size; i++)
    {
        printf("Train id: %d Name: %s\n", i + 1, TRAIN[i].Name);
    }
    printf("---------------------------------------\n");

    do
    {
        printf("Enter train_id on which u have to perform Range search(see above list):");
        scanf("%d", &trn_id);
    } while (trn_id < 1 && trn_id > train_size);

    printf("Enter FROM date(format: dd<space >mm<space>yyyy): ");
    scanf("%d", &From[0]);
    scanf("%d", &From[1]);
    scanf("%d", &From[2]);

    do
    {
        printf("Enter TO date(format: dd<space >mm<space>yyyy)(must be >= FROM date): ");
        scanf("%d", &To[0]);
        scanf("%d", &To[1]);
        scanf("%d", &To[2]);
    } while (campare_date(From, To) == 1);

    printf("\n----------------------------------------------------------\n");
    Range_search(TRAIN[trn_id - 1].date_root, From, To);
    printf("\n----------------------------------------------------------\n");
}
//-----------------------===============================================---------------------------//

/*
//-----------------------===============================================---------------------------//
Passenger *get_fast(int pnr, char *name, int date[], int tid, char des[])
{
    Passenger *temp = get_new_passenger();

    temp->PNR = pnr;
    strcpy(temp->firstName, name);
    strcpy(temp->lastName, "verma");
    temp->age = 20;
    temp->train_id = tid;
    strcpy(temp->boarding_train, "jaipur_exp");
    strcpy(temp->boarding_station, "palghar");
    strcpy(temp->destination_station, des);
    temp->traveling_class = 0;

    temp->travel_date[0] = date[0];
    temp->travel_date[1] = date[1];
    temp->travel_date[2] = date[2];

    return temp;
}
//-----------------------===============================================---------------------------//
int main()
{
    int max_size = 0;
    int train_size = 0;
    Train *TRAIN;
    // TRAIN = READ_TRAIN_CONSOLE();
    TRAIN = intialize_train(&train_size, &max_size);
    Display_all(TRAIN, train_size);

    int date[3] = {1, 2, 2022};

    Passenger *temp = get_fast(1, "kishan", date, 1, "Mumbai");
    INSERT(TRAIN, train_size, temp);

    date[0] = 1;
    temp = get_fast(2, "kishan2", date, 1, "Akola");
    INSERT(TRAIN, train_size, temp);
    date[0] = 1;
    temp = get_fast(3, "kishan3", date, 1, "Mumbai");
    INSERT(TRAIN, train_size, temp);
    date[0] = 2;
    temp = get_fast(4, "kishan4", date, 1, "Ajmer");
    INSERT(TRAIN, train_size, temp);
    date[0] = 2;
    temp = get_fast(5, "kishan5", date, 1, "Palghar");
    INSERT(TRAIN, train_size, temp);
    date[0] = 3;
    temp = get_fast(6, "kishan6", date, 1, "Palghar");
    INSERT(TRAIN, train_size, temp);
    date[0] = 3;
    temp = get_fast(7, "kishan7", date, 1, "jaipur");
    INSERT(TRAIN, train_size, temp);
    date[0] = 4;
    temp = get_fast(8, "kishan8", date, 1, "jaipur");
    INSERT(TRAIN, train_size, temp);
    //    INSERT(TRAIN, train_size, temp);
    //    INSERT(TRAIN, train_size, temp2);
    //    Display_all(TRAIN, train_size);

    // DELETE(TRAIN, train_size);

    Display_all(TRAIN, train_size);

    // SortTrain(TRAIN, train_size);
    // Sort_Travel_date(TRAIN, train_size);
    // get_listDestination(TRAIN, train_size);
    RangeSearch_travelDate(TRAIN, train_size);

    return 0;
}

*/