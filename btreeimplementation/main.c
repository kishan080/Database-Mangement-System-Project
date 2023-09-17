#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_and_struct.h"

void read_data(Passenger *temp, Train *TRAIN, int train_size);

int main()
{
    int max_size = 0;
    int train_size = 0;
    Train *TRAIN;
    // TRAIN = READ_TRAIN_CONSOLE(&train_size, &max_size);
    TRAIN = intialize_train(&train_size, &max_size);
    Display_all(TRAIN, train_size);

    // Passenger *temp = (Passenger *)malloc(sizeof(Passenger));

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
        printf("6.Range Search on Travel date for given train\n");
        printf("7.Display_ALL\n");
        printf("8.Insert New Train to Database\n");
        printf("9.Exit\n");
        printf("======================================================================\n");

        int choice;
        printf("Enter choice: ");
        scanf("%d", &choice);
        printf("----------------------------------------------------------------------\n");

        switch (choice)
        {
        case 1:
        {
            Passenger *temp = get_new_passenger();
            read_data(temp, TRAIN, train_size);
            // Display_pngr(temp2);
            INSERT(TRAIN, train_size, temp);
        }
        break;
        case 2:
        {
            DELETE(TRAIN, train_size);
        }
        break;
        case 3:
        {
            get_listDestination(TRAIN, train_size);
        }
        break;
        case 4:
        {
            Sort_Travel_date(TRAIN, train_size);
        }
        break;
        case 5:
        {
            SortTrain(TRAIN, train_size);
        }
        break;
        case 6:
        {
            RangeSearch_travelDate(TRAIN, train_size);
        }
        break;
        case 7:
        {
            Display_all(TRAIN, train_size);
        }
        break;
        case 8:
        {
            TRAIN = Insert_new_Train(TRAIN, &train_size, &max_size);
        }
        break;
        case 9:
        {
            flag = 0;
        }
        break;

        default:
            printf("Enter valid choice\n");
            break;
        }

    } while (flag);

    return 0;
}

void read_data(Passenger *temp, Train *TRAIN, int train_size)
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
    for (int i = 0; i < train_size; i++)
    {
        printf("Train id: %d Name: %s\n", i + 1, TRAIN[i].Name);
    }
    printf("---------------------------------------\n");
    do
    {
        printf("Enter train_id(see above list):");
        scanf("%d", &temp->train_id);
    } while (temp->train_id < 1 && temp->train_id > train_size);
    printf("---------------------------------------\n");

    strcpy(temp->boarding_train, TRAIN[(temp->train_id) - 1].Name);

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

    printf("Enter Travel date(format: dd<space>mm<space>yyyy ex:1 2 2022): \n");
    scanf("%d", &temp->travel_date[0]);
    scanf("%d", &temp->travel_date[1]);
    scanf("%d", &temp->travel_date[2]);
}