#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_and_struct.h"

Travel_Date *get_travel_date(int Date[])
{
    Travel_Date *new_node = (Travel_Date *)malloc(sizeof(Travel_Date));

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
    //======================================
    // intialised all seat to -1;
    for (int i = 0; i < SL_COACH; i++)
    {
        for (int j = 0; j < SL_SEAT; j++)
        {
            new_node->sleeper_class[i][j] = -1;
        }
    }
    for (int i = 0; i < AC1_COACH; i++)
    {
        for (int j = 0; j < AC1_SEAT; j++)
        {
            new_node->AC_class1[i][j] = -1;
        }
    }
    for (int i = 0; i < AC2_COACH; i++)
    {
        for (int j = 0; j < AC2_SEAT; j++)
        {
            new_node->AC_class2[i][j] = -1;
        }
    }
    for (int i = 0; i < AC3_COACH; i++)
    {
        for (int j = 0; j < AC3_SEAT; j++)
        {
            new_node->AC_class3[i][j] = -1;
        }
    }
    // -----------------------------------

    new_node->pngr_root = NULL;

    return new_node;
}

tNode *make_tNode()
{
    tNode *temp = (tNode *)malloc(sizeof(tNode));
    temp->count = 0;
    for (int i = 0; i <= MAX; i++)
        temp->branch[i] = NULL;

    return temp;
}

tNode *Search_travel(tNode *root, int target[], int *pos)
{
    tNode *ret_val;

    if (root == NULL)
        ret_val = NULL;
    else if (Search_tNode(root, target, pos))
        ret_val = root;
    else
        ret_val = Search_travel(root->branch[*pos], target, pos);

    return ret_val;
}

Boolean Search_tNode(tNode *p, int target[], int *pos)
{
    if (p == NULL)
        return FALSE;

    if (campare_date(target, p->key[1]->date) == -1)
    {
        (*pos) = 0;
        return FALSE;
    }
    else
    {
        (*pos) = p->count;
        while ((campare_date(target, p->key[*pos]->date) == -1) && ((*pos) > 1))
            (*pos)--;
        return (campare_date(target, p->key[*pos]->date) == 0);
    }
}

tNode *insert_travel(tNode *root, Travel_Date *new_key)
{
    Travel_Date *x;
    tNode *xr;
    Boolean pushUp;

    pushUp = PushDown_travel(root, new_key, &x, &xr);

    if (pushUp == TRUE)
    {
        tNode *temp = make_tNode();
        temp->count = 1;
        temp->key[1] = x;
        temp->branch[0] = root;
        temp->branch[1] = xr;

        root = temp;
    }

    return root;
}

Boolean PushDown_travel(tNode *root, Travel_Date *new_key, Travel_Date **x, tNode **xr)
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
        if (Search_tNode(root, new_key->date, &k))
        {
            printf("Error: duplicate value!!\n");
        }
        else if (PushDown_travel(root->branch[k], new_key, x, xr))
        {
            if (root->count < MAX)
            {
                PushIn_travel(*x, *xr, root, k);
                return FALSE;
            }
            else
            {
                Split_travel(*x, *xr, root, k, x, xr);
                return TRUE;
            }
        }
        return FALSE;
    }
}
void PushIn_travel(Travel_Date *x, tNode *xr, tNode *p, int k)
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
void Split_travel(Travel_Date *x, tNode *xr, tNode *root, int k, Travel_Date **y, tNode **yr)
{
    int median;

    if (k <= MIN)
        median = MIN;
    else
        median = MIN + 1;

    tNode *temp = make_tNode();

    for (int i = median + 1; i <= MAX; i++)
    {
        temp->key[i - median] = root->key[i];
        temp->branch[i - median] = root->branch[i];
    }

    temp->count = MAX - median;
    root->count = median;

    if (k <= MIN)
        PushIn_travel(x, xr, root, k);
    else
        PushIn_travel(x, xr, temp, k - median);

    *y = root->key[root->count];
    temp->branch[0] = root->branch[root->count];
    (root->count)--;

    *yr = temp;
}

void inorder_travel(tNode *root)
{
    if (root != NULL)
    {
        for (int i = 1; i <= root->count; i++)
        {
            inorder_travel(root->branch[i - 1]);
            display_travel(root->key[i]);
            inorder_pngr(root->key[i]->pngr_root);
        }

        inorder_travel(root->branch[root->count]);
    }
}

void display_travel(Travel_Date *node)
{
    printf("\n-----------------------------------------\n");
    printf("date: %d/%d/%d \n", node->date[0], node->date[1], node->date[2]);
    printf("\n-----------------------------------------\n");
}

//-----------------------deletion ------------------------------------\n

tNode *Delete_travel(tNode *root, int date[])
{
    if (!RecDelete_travel(root, date))
        printf("Error: element not found!!\n");
    else if (root->count == 0)
    {
        tNode *p = root;
        root = root->branch[0];
        free(p);
    }
    return root;
}
Boolean RecDelete_travel(tNode *root, int date[])
{
    int k; // tell next position in branch were we can find element
    Boolean found;

    if (root == NULL) // empty tree case
        return FALSE;
    else
    {

        if ((found = Search_tNode(root, date, &k))) // search in present node for target
        {
            if (root->branch[0] != NULL) // not a leaf node
            {
                Successor_travel(root, k); // replace p->key[k] with its
                                           // successor
                // node delete successor in leaf
                if (!(found = RecDelete_travel(root->branch[k], root->key[k]->date)))
                {
                    // we know key is there in leaf
                    // but just for sake of debuggingadded condition check
                    printf("Error: key not found (succesor)\n");
                }
            }
            else // leaf node just simply delete
                Remove_travel(root, k);
        }
        else // target was not found in present node ,..make recursive call to next node
            found = RecDelete_travel(root->branch[k], date);
        // recususion is winding up so resotre devoid node if any
        if (root->branch[k] != NULL) // not a leaf node
        {
            if (root->branch[k]->count < MIN) // childern is devoid of keys
                Restore_travel(root, k);      // restore kth branch of node root // deletion happen in k
        }

        return found;
    }
}
void Remove_travel(tNode *p, int k)
{
    Travel_Date *temp = p->key[k];

    for (int i = k + 1; i <= p->count; i++)
    {
        p->key[i - 1] = p->key[i];
        p->branch[i - 1] = p->branch[i];
    }
    (p->count)--;

    free(temp);
    temp = NULL;
}

void Restore_travel(tNode *p, int k)
{
    /// deletion happen in key "k"

    if (k == 0) // left most key
    {
        if (p->branch[1]->count > MIN)
            MoveLeft_travel(p, 1);
        else
            Combine_travel(p, 1);
    }
    else if (k == p->count) // right most key
    {
        if (p->branch[k - 1]->count > MIN)
            MoveRight_travel(p, k);
        else
            Combine_travel(p, k);
    } // rest case i.e k>0 && k< count //check for both siblning
    else if (p->branch[k - 1]->count > MIN)
        MoveRight_travel(p, k);
    else if (p->branch[k + 1]->count > MIN)
        MoveLeft_travel(p, k + 1);
    else // both sibling devoid of key then combine
        Combine_travel(p, k);
}

void copy_travel(Travel_Date *d1, Travel_Date *d2)
{
    d1->cnt = d2->cnt;
    d1->booking_number = d2->booking_number;

    d1->date[0] = d2->date[0];
    d1->date[1] = d2->date[1];
    d1->date[2] = d2->date[2];

    // -----------------------------------
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
            d1->book_upto[i][j] = d2->book_upto[i][j];
    }
    // -----------------------------------

    for (int i = 0; i < SL_COACH; i++)
    {
        for (int j = 0; j < SL_SEAT; j++)
        {
            d1->sleeper_class[i][j] = d2->sleeper_class[i][j];
        }
    }
    for (int i = 0; i < AC1_COACH; i++)
    {
        for (int j = 0; j < AC1_SEAT; j++)
        {
            d1->AC_class1[i][j] = d2->AC_class1[i][j];
        }
    }
    for (int i = 0; i < AC2_COACH; i++)
    {
        for (int j = 0; j < AC2_SEAT; j++)
        {
            d1->AC_class2[i][j] = d2->AC_class2[i][j];
        }
    }
    for (int i = 0; i < AC3_COACH; i++)
    {
        for (int j = 0; j < AC3_SEAT; j++)
        {
            d1->AC_class3[i][j] = d2->AC_class3[i][j];
        }
    }
    // -----------------------------------

    d1->pngr_root = d2->pngr_root;
}
void Successor_travel(tNode *p, int k)
{
    tNode *q;
    for (q = p->branch[k]; q->branch[0] != NULL; q = q->branch[0])
        ;
    copy_travel(p->key[k], q->key[1]);
}
void MoveLeft_travel(tNode *p, int k)
{
    // move parent to left node
    tNode *t = p->branch[k - 1];
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

void MoveRight_travel(tNode *p, int k)
{
    tNode *t = p->branch[k];

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

void Combine_travel(tNode *p, int k)
{
    tNode *q = p->branch[k]; // q is right node which will be emptied and deleted
    tNode *l = p->branch[k - 1];

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
    Travel_Date *temp1, *temp2, *temp3, *temp4, *temp5;
    int date[3] = {1, 2, 2022};
    temp1 = get_travel_date(date);
    date[0] = 2;
    temp2 = get_travel_date(date);
    date[0] = 3;
    temp3 = get_travel_date(date);
    date[0] = 4;
    temp4 = get_travel_date(date);
    date[0] = 5;
    temp5 = get_travel_date(date);

    tNode *root = NULL;

    printf("\nsuccess\n");
    root = insert_travel(root, temp5);
    root = insert_travel(root, temp1);
    root = insert_travel(root, temp2);
    root = insert_travel(root, temp4);
    root = insert_travel(root, temp3);
    inorder_travel(root);
    printf("\nsuccess\n");

    date[0] = 8;
    int pos;
    tNode *found = Search_travel(root, date, &pos);
    if (found == NULL)
    {
        printf("\nNULLLLLLL\n");
    }
    else
    {
        printf("\nnot NULL\n");
        display_travel(found->key[pos]);
    }

    free(temp1);
    free(temp2);
    free(temp3);
    free(temp4);
    free(temp5);
    return 0;
}
*/