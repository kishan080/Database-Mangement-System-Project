#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree_and_struct.h"

Passenger *get_new_passenger()
{
    Passenger *temp = (Passenger *)malloc(sizeof(Passenger));
    return temp;
}

pNode *make_pNode()
{
    pNode *temp = (pNode *)malloc(sizeof(pNode));
    temp->count = 0;
    for (int i = 0; i <= MAX; i++)
        temp->branch[i] = NULL;

    return temp;
}

pNode *Search_pngr(pNode *root, int target, int *pos)
{
    pNode *ret_val;

    if (root == NULL)
        ret_val = NULL;
    else if (Search_pNode(root, target, pos))
        ret_val = root;
    else
        ret_val = Search_pngr(root->branch[*pos], target, pos);

    return ret_val;
}

Boolean Search_pNode(pNode *p, int target, int *pos)
{
    if (p == NULL)
        return FALSE;

    if (target < p->key[1]->PNR)
    {
        (*pos) = 0;
        return FALSE;
    }
    else
    {
        (*pos) = p->count;
        while ((target < p->key[*pos]->PNR) && ((*pos) > 1))
            (*pos)--;
        return ((target) == (p->key[*pos]->PNR));
    }
}

pNode *insert_pngr(pNode *root, Passenger *new_key)
{
    Passenger *x;
    pNode *xr;
    Boolean pushUp;

    pushUp = PushDown_pngr(root, new_key, &x, &xr);

    if (pushUp == TRUE)
    {
        pNode *temp = make_pNode();
        temp->count = 1;
        temp->key[1] = x;
        temp->branch[0] = root;
        temp->branch[1] = xr;

        root = temp;
    }

    return root;
}

Boolean PushDown_pngr(pNode *root, Passenger *new_key, Passenger **x, pNode **xr)
{
    int k;

    if (root == NULL)
    {
        *x = new_key;
        *xr = NULL;
        return TRUE;
    }
    else
    {
        if (Search_pNode(root, new_key->PNR, &k))
        {
            printf("Error: duplicate value!!\n");
        }
        else if (PushDown_pngr(root->branch[k], new_key, x, xr))
        {
            if (root->count < MAX)
            {
                PushIn_pngr(*x, *xr, root, k);
                return FALSE;
            }
            else
            {
                Split_pngr(*x, *xr, root, k, x, xr);
                return TRUE;
            }
        }
        return FALSE;
    }
}

void PushIn_pngr(Passenger *x, pNode *xr, pNode *p, int k)
{

    for (int i = p->count; i > k; i--)
    {
        p->key[i + 1] = p->key[i];
        p->branch[i + 1] = p->branch[i];
    }
    p->key[k + 1] = x;
    p->branch[k + 1] = xr;
    (p->count)++;
}

void Split_pngr(Passenger *x, pNode *xr, pNode *root, int k, Passenger **y, pNode **yr)
{
    int median;

    if (k <= MIN)
        median = MIN;
    else
        median = MIN + 1;

    pNode *temp = make_pNode();

    for (int i = median + 1; i <= MAX; i++)
    {
        temp->key[i - median] = root->key[i];
        temp->branch[i - median] = root->branch[i];
    }

    temp->count = MAX - median;
    root->count = median;

    if (k <= MIN)
        PushIn_pngr(x, xr, root, k);
    else
        PushIn_pngr(x, xr, temp, k - median);

    *y = root->key[root->count];
    temp->branch[0] = root->branch[root->count];
    (root->count)--;

    *yr = temp;
}

void inorder_pngr(pNode *root)
{
    if (root != NULL)
    {
        for (int i = 1; i <= root->count; i++)
        {
            inorder_pngr(root->branch[i - 1]);
            Display_pngr(root->key[i]);
        }

        inorder_pngr(root->branch[root->count]);
    }
}

void Display_pngr(Passenger *pngr_data)
{
    if (pngr_data == NULL)
        return;
    printf("==================================================\n");
    printf("PNR: %d\n", pngr_data->PNR);
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
    // printf("want to promote(1=yes,0=no): %d\n", pngr_data->hasToPromote);

    printf("==================================================\n");
}

// deletion..
pNode *Delete_pngr(pNode *root, int PNR)
{
    if (!RecDelete_pngr(root, PNR))
        printf("Error: element not found!!\n");
    else if (root->count == 0)
    {
        pNode *p = root;
        root = root->branch[0];
        free(p);
    }
    return root;
}

Boolean RecDelete_pngr(pNode *root, int PNR)
{
    int k; // tell next position in branch were we can find element
    Boolean found;

    if (root == NULL) // empty tree case
        return FALSE;
    else
    {

        if ((found = Search_pNode(root, PNR, &k))) // search in present node for target
        {
            if (root->branch[0] != NULL) // not a leaf node
            {
                Successor_pngr(root, k); // replace p->key[k] with its
                                         // successor
                // node delete successor in leaf
                if (!(found = RecDelete_pngr(root->branch[k], root->key[k]->PNR)))
                {
                    // we know key is there in leaf
                    // but just for sake of debuggingadded condition check
                    printf("Error: key not found (succesor)\n");
                }
            }
            else // leaf node just simply delete
                Remove_pngr(root, k);
        }
        else // target was not found in present node ,..make recursive call to next node
            found = RecDelete_pngr(root->branch[k], PNR);
        // recususion is winding up so resotre devoid node if any
        if (root->branch[k] != NULL) // not a leaf node
        {
            if (root->branch[k]->count < MIN) // childern is devoid of keys
                Restore_pngr(root, k);        // restore kth branch of node root // deletion happen in k
        }

        return found;
    }
}

void Remove_pngr(pNode *p, int k)
{
    Passenger *temp = p->key[k];

    for (int i = k + 1; i <= p->count; i++)
    {
        p->key[i - 1] = p->key[i];
        p->branch[i - 1] = p->branch[i];
    }
    (p->count)--;

    free(temp);
    temp = NULL;
}

void copy_pngr(Passenger *p1, Passenger *p2)
{
    p1->PNR = p2->PNR;
    strcpy(p1->firstName, p2->firstName);
    strcpy(p1->lastName, p2->lastName);
    p1->age = p2->age;
    p1->train_id = p2->train_id;
    strcpy(p1->boarding_train, p2->boarding_train);
    strcpy(p1->boarding_station, p2->boarding_station);
    strcpy(p1->destination_station, p2->destination_station);
    p1->traveling_class = p2->traveling_class;

    p1->travel_date[0] = p2->travel_date[0];
    p1->travel_date[1] = p2->travel_date[1];
    p1->travel_date[2] = p2->travel_date[2];
}
void Successor_pngr(pNode *p, int k)
{
    pNode *q;
    for (q = p->branch[k]; q->branch[0] != NULL; q = q->branch[0])
        ;
    copy_pngr(p->key[k], q->key[1]);
}

void Restore_pngr(pNode *p, int k)
{
    /// deletion happen in key "k"

    if (k == 0) // left most key
    {
        if (p->branch[1]->count > MIN)
            MoveLeft_pngr(p, 1);
        else
            Combine_pngr(p, 1);
    }
    else if (k == p->count) // right most key
    {
        if (p->branch[k - 1]->count > MIN)
            MoveRight_pngr(p, k);
        else
            Combine_pngr(p, k);
    } // rest case i.e k>0 && k< count //check for both siblning
    else if (p->branch[k - 1]->count > MIN)
        MoveRight_pngr(p, k);
    else if (p->branch[k + 1]->count > MIN)
        MoveLeft_pngr(p, k + 1);
    else // both sibling devoid of key then combine
        Combine_pngr(p, k);
}

void MoveRight_pngr(pNode *p, int k)
{
    pNode *t = p->branch[k];

    for (int i = t->count; i > 0; i--) // shit by one in right node
    {
        t->key[i + 1] = t->key[i];
        t->branch[i + 1] = t->branch[i];
    }
    t->branch[1] = t->branch[0];
    (t->count)++;
    // move parent down;
    t->key[1] = p->key[k];
    // move form left to parent
    t = p->branch[k - 1];
    p->key[k] = t->key[t->count];
    p->branch[k]->branch[0] = t->branch[t->count];
    (t->count)--;
}

void MoveLeft_pngr(pNode *p, int k)
{
    // move parent to left node
    pNode *t = p->branch[k - 1];
    (t->count)++;
    t->key[t->count] = p->key[k];
    t->branch[t->count] = p->branch[k]->branch[0];

    // move right node to parent
    t = p->branch[k];
    p->key[k] = t->key[1];
    t->branch[0] = t->branch[1];
    (t->count)--;
    for (int i = 1; i <= t->count; i++) // shift key in right node to left by 1
    {
        t->key[i] = t->key[i + 1];
        t->branch[i] = t->branch[i + 1];
    }
}

void Combine_pngr(pNode *p, int k)
{
    pNode *q = p->branch[k]; // q is right node which will be emptied and deleted
    pNode *l = p->branch[k - 1];

    (l->count)++;
    l->key[l->count] = p->key[k];
    l->branch[l->count] = q->branch[0];

    for (int i = 1; i <= q->count; i++)
    {
        (l->count)++;
        l->key[l->count] = q->key[i];
        l->branch[l->count] = q->branch[i];
    }
    // delete key k form parent node p

    for (int i = k; i < p->count; i++)
    {
        p->key[i] = p->key[i + 1];
        p->branch[i] = p->branch[i + 1];
    }
    (p->count)--;

    free(q);
}

/*
int main()
{
    Passenger *temp = get_new_passenger();

    temp->PNR = 11;
    strcpy(temp->firstName, "kishan");
    strcpy(temp->lastName, "verma");
    temp->age = 20;
    temp->train_id = 0;
    strcpy(temp->boarding_train, "jaipur_exp");
    strcpy(temp->boarding_station, "palghar");
    strcpy(temp->destination_station, "jaipur");
    temp->traveling_class = 0;

    temp->travel_date[0] = 1;
    temp->travel_date[1] = 2;
    temp->travel_date[2] = 2022;

    Passenger *temp2 = get_new_passenger();

    temp2->PNR = 23;
    strcpy(temp2->firstName, "kishan");
    strcpy(temp2->lastName, "verma");
    temp2->age = 20;
    temp2->train_id = 0;
    strcpy(temp2->boarding_train, "jaipur_exp");
    strcpy(temp2->boarding_station, "palghar");
    strcpy(temp2->destination_station, "jaipur");
    temp2->traveling_class = 0;

    temp2->travel_date[0] = 1;
    temp2->travel_date[1] = 2;
    temp2->travel_date[2] = 2022;

    Passenger *temp3 = get_new_passenger();

    temp3->PNR = 24;
    strcpy(temp3->firstName, "kishan");
    strcpy(temp3->lastName, "verma");
    temp3->age = 20;
    temp3->train_id = 0;
    strcpy(temp3->boarding_train, "jaipur_exp");
    strcpy(temp3->boarding_station, "palghar");
    strcpy(temp3->destination_station, "jaipur");
    temp3->traveling_class = 0;

    temp3->travel_date[0] = 1;
    temp3->travel_date[1] = 2;
    temp3->travel_date[2] = 2022;

    Passenger *temp4 = get_new_passenger();

    temp4->PNR = 25;
    strcpy(temp4->firstName, "kishan");
    strcpy(temp4->lastName, "verma");
    temp4->age = 205;
    temp4->train_id = 0;
    strcpy(temp4->boarding_train, "jaipur_exp");
    strcpy(temp4->boarding_station, "palghar");
    strcpy(temp4->destination_station, "jaipur");
    temp4->traveling_class = 0;

    temp4->travel_date[0] = 1;
    temp4->travel_date[1] = 2;
    temp4->travel_date[2] = 2022;

    Passenger *temp5 = get_new_passenger();

    temp5->PNR = 26;
    strcpy(temp5->firstName, "kishan");
    strcpy(temp5->lastName, "verma");
    temp5->age = 20;
    temp5->train_id = 0;
    strcpy(temp5->boarding_train, "jaipur_exp");
    strcpy(temp5->boarding_station, "palghar");
    strcpy(temp5->destination_station, "jaipur");
    temp5->traveling_class = 0;

    temp5->travel_date[0] = 1;
    temp5->travel_date[1] = 2;
    temp5->travel_date[2] = 2022;

    pNode *root = NULL;

    root = insert_pngr(root, temp);
    printf("\nSuccess\n");

    root = insert_pngr(root, temp2);
    printf("\nSuccess\n");
    root = insert_pngr(root, temp4);
    printf("\nSuccess\n");
    root = insert_pngr(root, temp5);
    printf("\nSuccess\n");
    root = insert_pngr(root, temp3);
    printf("\nSuccess\n");

    inorder_pngr(root);
    int pos;
    pNode *found = Search_pngr(root, 11, &pos);

    if (found == NULL)
        printf("\nnot found\n");
    else
    {
        printf("\nnot null");
        Display_pngr(found->key[pos]);
    }

    // printf("\nsuccces\n");
    // inorder_pngr(root);
    return 0;
}
*/