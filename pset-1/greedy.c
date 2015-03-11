#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    float change;
    int cents;
    int NumCoins = 0;
    
    // Get amount of change owed. 
    // Float change must be positive and converted to Integer giving cents total.
    
    do
    {
        printf("how much change is owned : ");
        change = GetFloat();
        cents = (round(change * 100)); 
    }
    while (change < 0);
    
    // Calculate the number of coins to be given back.
    // Starting with quarters, then dimes, then nickels, then pennies.
    
    while (cents > 24)
    {
        NumCoins = NumCoins + 1;
        cents = cents - 25;
    }
    
    while (cents > 9)
    {
        NumCoins = NumCoins + 1;
        cents = cents - 10;
    }

    while (cents > 4)
    {
        NumCoins = NumCoins + 1;
        cents = cents - 5;
    }

    while (cents > 0)
    {
        NumCoins = NumCoins + 1;
        cents = cents - 1;
    }
       
    // print number of coins to give back
       
    printf("%d\n", NumCoins);
}
