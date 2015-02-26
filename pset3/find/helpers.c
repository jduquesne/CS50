/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm

    // make sure the size of the array (n) is positive
    if (n < 1)
    {
        return false;
    }

    // set up the low (0) and high (n-1) for the comparison
    int low = 0;
    int high = n - 1;
    int middle;
    
    // loop until we find the number searched
    while (low <= high)
    {
        middle = (low + high) / 2;
        
        // search the left side of the list
        if (value < values[middle])
        {
            high = middle - 1;
        }
        
        // search the right side of the list
        else if (value > values[middle])
        {
            low = middle + 1;
        }
        
        // found it !
        else
        {
            return true;
        }
    }
    
    // if the loop fails to find the number, then return false
    return false;
}

//    for (int i = 0; i < n; i++)
//    {
//        if (value == values[i])
//        {
//           return true;
//        }
//    }
//    return false;
//}


/**
 * Sorts array of n values.
 */
 
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // Implementing an "Insertion Sort" type of algorithm

    // iterate over each element in the list except the 1st (which is already in the sorted part)
    for (int i = 1; i < n ; i++)
    {

        // Where are we in the unsorted portion ?
        int element = values[i];
        int j = i;        
        int temp;
        
        // iterate through the sorted portion from right to left
        while (j > 0 && values[j-1] > element)
        {

            // shift the element once we find the place it needs to go to
            temp        = values[j];
            values[j]   = values[j-1];
            values[j-1] = temp;
            
            j--;
        }
        values[j] = element;
    }   
    return;
}
