#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "train_system.h"
#include "utility_fxn.h"

void read_data(Passenger *temp)
{
    printf("Enter PNR number:");
    scanf("%d", &temp->PNR);
    fflush(stdin);
    printf("Enter first Name:");
    scanf("%s", temp->firstName);
    fflush(stdin);
    printf("Enter last Name:");
    scanf("%s", temp->lastName);

    printf("Enter age:");
    scanf("%d", &temp->age);

    printf("---------------------------------------\n");
    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        printf("Train id: %d Name: %s\n", i, train_list[i].Name);
    }
    printf("---------------------------------------\n");
    do
    {
        printf("Enter train_id(see above list):");
        scanf("%d", &temp->train_id);
    } while (temp->train_id < 0 && temp->train_id >= TRAIN_SIZE);
    printf("---------------------------------------\n");

    fflush(stdin);
    printf("Enter boarding_station name: \n");
    scanf("%s", temp->boarding_station);
    fflush(stdin);
    printf("Enter destination_station name: \n");
    scanf("%s", temp->destination_station);

    printf("---------------------------------------\n");
    printf("sleeper=0\nAC1=1\nAC2=2\nAC3=3\n");
    printf("---------------------------------------\n");

    do
    {
        printf("Enter traveling class(int)(>=0 && <=3): \n");
        scanf("%d", &temp->traveling_class);
    } while (temp->traveling_class < 0 && temp->traveling_class >= 4);

    printf("Enter date(format: dd<space>mm<space>yyyy ex:1 2 2022): \n");
    scanf("%d", &temp->travel_date[0]);
    scanf("%d", &temp->travel_date[1]);
    scanf("%d", &temp->travel_date[2]);

    if (temp->traveling_class != 1)
    {
        printf("Want to promote to higher coaches(1=yes/0=no)??\n");
        scanf("%d", &temp->hasToPromote);
    }
}

int main()
{

    intialize_train_list();
    // READ();

    for (int i = 0; i < TRAIN_SIZE; i++)
    {
        printf("num %d\n", train_list[i].num);
    }
    Passenger *temp = (Passenger *)malloc(sizeof(Passenger));

    int flag = 1;
    do
    {
        printf("======================================================================\n");
        printf("                               MENU                                   \n");
        printf("======================================================================\n");
        printf("1.Insert passenger\n");
        printf("2.Delete passenger\n");
        printf("3.Get list Destination\n");
        printf("4.Sort by Travel date\n");
        printf("5.Sort Train\n");
        printf("6.PromotePassenger\n");
        printf("7.Display_ALL\n");
        printf("8.Exit\n");
        printf("======================================================================\n");

        int choice;
        printf("Enter choice: ");
        scanf("%d", &choice);
        printf("----------------------------------------------------------------------\n");

        switch (choice)
        {
        case 1:
        {
            read_data(temp);
            Passenger *temp2 = get_new_passenger(temp);
            insert(temp2);
        }
        break;
        case 2:
        {
            Delete();
        }
        break;
        case 3:
        {
            get_listDestination();
        }
        break;
        case 4:
        {
            Sort_Travel_date();
        }
        break;
        case 5:
        {
            SortTrain();
        }
        break;
        case 6:
        {
            PromotePassenger();
        }
        break;
        case 7:
        {
            Display_all();
        }
        break;
        case 8:
        {
            flag = 0;
        }
        break;

        default:
            printf("Enter valid choice\n");
            break;
        }

    } while (flag);

    // WRITE();
    return 0;
}