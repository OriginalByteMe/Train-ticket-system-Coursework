// Noah Rijkaard
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


void coachAssign(int array[17][4]);
int buy(int array[17][4],char seatClass, char seatType, int howManySeats);
bool aisleIsFull(int array[17][4]);
bool windowIsFull(int array[17][4]);
void printArray(int array[17][4]);
int refund(int array[17][4],char seatColoumn, char seatClass, int seatNum);

int main(){
    static int coach[17][4];
    int total = 0;
    coachAssign(coach);
    while(1){
        int choice = 0; 
        printf("Menu:");
        printf("\n1. Buy tickets");
        printf("\n2. Cancle tickets");
        printf("\n3. Display available tickets");
        printf("\n4. Display the bought code");
        printf("\n0. exit\n");
        scanf("%d", &choice);
        
        switch(choice){
            
            case 1: {
                char seatClass;
                char seatType;
                char useless;
                int numSeats = 0;
                scanf("%c",&useless);
                printf("Please enter your seat type (B for business G for gold): ");
                scanf("%c", &seatClass);
                seatClass = toupper(seatClass);
                scanf("%c",&useless);
                printf("Please enter whether you would like to have window (W) or aisle (A) seat: ");
                scanf("%c",&seatType);
                seatType = toupper(seatType);
                printf("Please input the number of seats: ");
                scanf("%d",&numSeats);
                total += buy(coach,seatClass,seatType,numSeats);
                printf("\nYour total is now: %d\n", total);
                printArray(coach);
            }
                break;
            case 2:{
                char seatClass;
                char seatType;
                char useless;
                int seatNum = 0;
                scanf("%c",&useless);
                printf("Please enter the seat you'd like to refund (e.g. A1) :");
                scanf("%c%d",&seatType, &seatNum);
                seatType = toupper(seatType);
                scanf("%c",&useless);
                printf("Please enter the seat class (B for business, G for gold): ");
                scanf("%c",&seatClass);
                //seatClass = Character.toUpperCase(seatClass);
                total -= refund(coach,seatType, seatClass, seatNum -1);
                printf("\nYour total is now: %d\n", total);
            }
                break;
            case 3: {
                printArray(coach);
            }
                break;
            case 4:{
                printf("\n0 = non-existant seat");
                printf("\n1 = Aisle seat");
                printf("\n2 = Window seat");
                printf("\n-1 = Taken Aisle seat");
                printf("\n-2 = Taken Window seat\n");
            }
            case 0:
                exit(1);
        }
        

        if(choice == 0){
            break;
        }
        
    }
    
    
    


    return 0;
}
void coachAssign(int array[17][4]){
    /*
    0 = non-existant seat
    1 = Aisle seat
    2 = Window seat
    -1 = Taken Aisle seat
    -2 = Taken Window seat

    */

    //Defining window seats
        // Coloumn A
    for(int i = 0; i<17; i++){
        array[i][0] = 2;
    }
        // COloumn C
    for(int i = 1; i < 6; i++){
        array[i][2] = 2;
    }
        // Coloumn D
    for(int i = 8; i < 17; i++){
        array[i][3] = 2;
    }

    // Defining aisle seats
        // Coloumn B
    for(int i = 1; i < 17;i++){
        array[i][1] = 1;
    }
        // Coloumn C
    for(int i = 7; i < 17; i++){
        array[i][2] = 1;
    }
    
}
int buy(int array[17][4], char seatClass, char seatType,int howManySeats){

    int ticketTotal = 0;
    srand(time(NULL)); // To initialise the seeding of the randomizer
    int randomRow = rand() % 17;
    int randomColoumn = rand() % 4;
    int counter = 0;

    // Getting total price of tickets
    if(seatClass == 'B'){
        for(int i = 0; i < howManySeats; i++){
            ticketTotal +=  100 + (100 * 0.06);
        }
    }

    if(seatClass == 'G'){
        for(int i = 0; i < howManySeats; i++){
            ticketTotal +=  50 + (50 * 0.06);
        }
    }
    // Reserving seats in the array
    if(seatType == 'W'){
        while(counter <= howManySeats){ // Has a counter for how many seats are left to reserve for
            randomRow = rand() % 17;
            randomColoumn = rand() % 4;
            printf("randomRow = %d randomColoumn = %d\n",randomRow, randomColoumn);
            if(array[randomRow][randomColoumn] == 2){
                array[randomRow][randomColoumn] = -2;
                counter++;
            } 
            if(windowIsFull(array)){ // If no more windows seats are available 
               printf("There are no more window seats available. You have booked %d window tickets.", counter);
               break;
            } 
        }
    } else if(seatType == 'A'){
        while(counter < howManySeats){
            randomRow = rand() % 17;
            randomColoumn = rand() % 4;
            if(array[randomRow][randomColoumn] == 1){
                array[randomRow][randomColoumn] = -1;
                counter++;
            } 
            if(aisleIsFull(array)){ // If no more windows seats are available 
               printf("There are no more aisle seats available. You have booked %d aisle tickets.", counter);
               break;
            } 
        }
    }
    
    return ticketTotal;



    
}

int refund(int array[17][4],char seatColoumn, char seatClass, int seatNum){
    /*
        For coloumn in array:
        0 = A
        1 = B
        2 = C
        3 = D
    */
    if(seatColoumn == 'A'){ // Coloumn A only has 2's in it so we only check for 2
        if(array[seatNum][0] == -2){ 
            array[seatNum][0] = 2;
            if(seatClass == 'B'){
                return 50;
            } else if(seatClass == 'G'){
                return 25;
            }
        }
    } else if(seatColoumn == 'B'){ // Coloumn B only has 1's in it so we only check for 1
        if(array[seatNum][1] == -1){
            array[seatNum][1] = 1;
            if(seatClass == 'B'){
                return 50;
            } else if(seatClass == 'G'){
                return 25;
            }
        }
    } else if(seatColoumn == 'C'){ // Coloumn C has 1 and 2's so we check for both
            if(array[seatNum][2] == -2){
                array[seatNum][2] = 2;
                if(seatClass == 'B'){
                    return 50;
                } else if(seatClass == 'G'){
                    return 25;
                }
            }
            if(array[seatNum-1][2] == -1){
                array[seatNum-1][2] = 1;
                if(seatClass == 'B'){
                    return 50;
                    } else if(seatClass == 'G'){
                        return 25;
                    }
                }
        }else if(seatColoumn == 'D'){ // Coloumn D only has 2's so only check for 2
            if(array[seatNum][2] == -2){
                array[seatNum][2] = 2;
                if(seatClass == 'B'){
                    return 50;
                } else if(seatClass == 'G'){
                    return 25;
                }
            }  
        }
}

bool windowIsFull(int array[17][4]){
    int counter = 0;
    bool isFull = false;

    // Goes through array and counts the number of reserved window seats (-2)
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 4; j++){
            if(array[i][j] == 2){
                counter++;
            }
        }
    }

    if(counter == 0){
        isFull = true; // returns true if it is full and false if not
    }

    return isFull;
}

bool aisleIsFull(int array[17][4]){
    int counter = 0;
    bool isFull = false;
    // Same thing as windowIsFull
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 4; j++){
            if(array[i][j] == 1){
                counter++;
            }
        }
    }

    if(counter == 0){
        isFull = true;
    }

    return isFull;
}


// Simple print method for 2D array + adding the coloumn names
void printArray(int array[17][4]){
    printf("\nA  B  C  D\n==========\n");
    for(int i = 0; i <17; i++){
        for(int j = 0; j<4; j++){
            printf("%d  ", array[i][j]);
        }
        printf("\n");
    }
}