#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_and_struct.h"

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

    if (ret_val < 0)
        ret_val = -1;
    else if (ret_val > 0)
        ret_val = 1;

    return ret_val;
}

//-------------------------------------------------------------------------------------------//

get_list_des *get_list_des_node(int pnr, char destination[])
{
    get_list_des *temp = (get_list_des *)malloc(sizeof(get_list_des));
    temp->pnr = pnr;
    strcpy(temp->destination, destination);
    temp->next = NULL;

    return temp;
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

//-------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------//
//======================================================================================//
//======================================================================================//
//======================================================================================//
get_list_des *findMid_des(get_list_des *lptr)
{
    get_list_des *nptr = NULL;
    if (lptr != NULL && lptr->next != NULL)
    {
        get_list_des *slow = lptr;
        get_list_des *fast = lptr->next;
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

get_list_des *Merge_dest(get_list_des *lptr, get_list_des *nptr)
{
    get_list_des *result, *ptr1, *ptr2, *tail;
    ptr1 = lptr;
    ptr2 = nptr;
    if (strcmp(ptr1->destination, ptr2->destination) == -1)
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
        int flag = strcmp(ptr1->destination, ptr2->destination);
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

get_list_des *MergeSort_dest(get_list_des *lptr)
{
    get_list_des *nptr;
    if (lptr != NULL && lptr->next != NULL)
    {
        nptr = findMid_des(lptr);
        lptr = MergeSort_dest(lptr);
        nptr = MergeSort_dest(nptr);
        lptr = Merge_dest(lptr, nptr);
    }
    return lptr;
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
Train *READ_TRAIN_CONSOLE(int *train_size, int *max_size)
{
    FILE *fp = fopen("intialize_train.txt", "wb");
    Train *TRAIN;

    if (fp != NULL)
    {
        int n, m;
        printf("Enter max Train_size: ");
        scanf("%d", &m);
        *max_size = m;
        fwrite(&m, 1, sizeof(int), fp);

        do
        {
            printf("Enter Train_size(<=max_size): ");
            scanf("%d", &n);
        } while (n > m);

        *train_size = n;

        fwrite(&n, 1, sizeof(int), fp);

        TRAIN = (Train *)malloc(m * sizeof(Train));

        for (int i = 0; i < n; i++)
        {
            TRAIN[i].id = i + 1;
            printf("Enter name for train_id %d : ", i + 1);
            scanf("%s", TRAIN[i].Name);
            TRAIN[i].num = 0;
            TRAIN[i].date_root = NULL;

            fwrite(&TRAIN[i], 1, sizeof(Train), fp);
            fflush(stdin);
        }
    }
    else
        printf("file cannot be open!!\n");

    fclose(fp);
    return TRAIN;
}

Train *intialize_train(int *train_Size, int *max_size)
{
    FILE *fp = fopen("intialize_train.txt", "rb");
    Train *TRAIN;
    if (fp != NULL)
    {
        fread(max_size, 1, sizeof(int), fp);
        fread(train_Size, 1, sizeof(int), fp);
        TRAIN = (Train *)malloc((*max_size) * sizeof(Train));
        for (int i = 0; i < (*train_Size); i++)
        {
            // fflush(fp);
            fread(&TRAIN[i], 1, sizeof(Train), fp);
        }
    }
    else
        printf("file cannot be open!!\n");

    fclose(fp);
    return TRAIN;
}
//-------------------------------------------------------------//

void Display_all(Train *TRAIN, int Train_Size)
{

    for (int i = 0; i < Train_Size; i++)
    {
        printf("==============================================\n");
        printf("---TRAIN ID: %d---NAME: %s\n", TRAIN[i].id, TRAIN[i].Name);
        printf("==============================================\n");
        if (TRAIN[i].date_root == NULL)
        {
            printf("\n!!!_______Empty Train_______!!!\n");
        }
        else
        {
            inorder_travel(TRAIN[i].date_root);
        }
    }
}

Train *Insert_new_Train(Train *TRAIN, int *Train_size, int *max_size)
{
    if (*Train_size == *max_size) // increase array size
    {
        printf("\ndynamic increasing !!\n");

        *max_size = (*max_size) * 2;
        Train *new_train = (Train *)malloc((*max_size) * sizeof(Train));

        for (int i = 0; i < (*Train_size); i++)
        {
            new_train[i].id = TRAIN[i].id;
            strcpy(new_train[i].Name, TRAIN[i].Name);
            new_train[i].num = TRAIN[i].num;
            new_train[i].date_root = TRAIN[i].date_root;
        }

        free(TRAIN);
        TRAIN = new_train;
    }

    (*Train_size)++;
    int i = (*Train_size) - 1;
    TRAIN[i].id = i + 1;
    printf("Enter name for train_id %d : ", i + 1);
    scanf("%s", TRAIN[i].Name);
    TRAIN[i].date_root = NULL;

    return TRAIN;
}