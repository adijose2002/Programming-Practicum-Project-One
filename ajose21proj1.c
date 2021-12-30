//
// Class: CS 211- Programming Practicum
// Author: Adithya Jose, UIC, Fall 2021
// Assignment: Project 01
//
//
// Project Description:
// The overall goal of this C program is to:
//   1. Read in a list of integers from standard input and store those values into an            array. (Stop reading the input when the value of -999 is read in.)
//   2. Make a copy of that array
//   3. Sort the copy of the array
//   4. Read in a second list of integers from standard input (again stop reading the            input when the value of -999 is read in). For each integer:
//     a. Do a linear search on that value in the unsorted array
//     b. Do a binary search on that value in the sorted array
//     c. Print out the following information from each search:
//       i. Was the value found or not found?
//       ii. How many comparisons were needed to determine if it was found or not
//       iii. If found, in what position was the value found in each array
//
//

#include <stdio.h>
#include <stdlib.h>

// function to sort objects in an array in order
void myFavorateSort(int arr[], int size)
{
  int plcHldr;

  for(int i = 0; i < size; ++i)
  {
    for(int j = 0; j < ((size - 1) - i); ++j)
    {
      if(arr[j] > arr[j + 1])
      {
        plcHldr = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = plcHldr;
      }
    }
  }
}


//function to copy objects from one array to another
void arrayCopy(int fromArray[], int toArray[], int size)
{
  for(int i = 0; i < size; ++i)
  {
    toArray[i] = fromArray[i];
  }
}


// function to run a linear search on an array and returns position of the target, if 
// not found returns -1
// also stores number of iterations needed to find the target and returns it too
int linSearch(int arr[], int size, int target, int* numComparisons)
{
  for(int i = 0; i < size; ++i)
  {
    (*numComparisons)++;
    if(arr[i] == target)
    {
      return i + 1;      
    }
  }

  return -1;   
}


// function to run a binary search on an array and returns position of the target, if 
// not found returns -1
// also stores number of iterations needed to find the target and returns it too
int binSearch(int arr[], int size, int target, int* numComparisons)
{
  int i = 0;
  int j = size - 1;

  while(i <= j)
  {
    int half = (i + j) / 2; 

    (*numComparisons)++;
    if(arr[half] == target)
    {
      return half + 1;         
    }
    else if(arr[half] < target)
    {
      i = half + 1;
    }
    else
    {
      j = half - 1;
    }
  }

  return -1;
}


int main()
{
  int dataIntegers;
  int size = 100;
  int *Arr1 = (int*) malloc(size * sizeof(int));

  int Arr1Size = 0;

  scanf("%d", &dataIntegers);


  // read in data for the first array until the data reads in -999
  while (dataIntegers != -999)
  {
    Arr1[Arr1Size] = dataIntegers;
    Arr1Size += 1;

    if (Arr1Size == 100)
    {
      Arr1 = realloc(Arr1, 2 * size * sizeof(int));
      size *= 2;
    }

    scanf("%d", &dataIntegers);

  }

  int *ArrCopy = (int*) malloc(Arr1Size * sizeof(int));

  // copy the data of Arr1 to ArrCopy
  arrayCopy(Arr1, ArrCopy, Arr1Size);

  // sorting the array ArrCopy
  myFavorateSort(ArrCopy, Arr1Size);

  int Arr2Size = 0;
  size = 100;

  int *Arr2 = (int*) malloc(size * sizeof(int));

  scanf("%d", &dataIntegers);

  // read in data for the second array until the data reads in -999
  while(dataIntegers != -999)
  {
    Arr2[Arr2Size] = dataIntegers;              
    Arr2Size += 1;

    if(Arr2Size == 100)
    {
      Arr2 = realloc(Arr2, 2 * size * sizeof(int));
      size *= 2;
    }

    scanf("%d", &dataIntegers);
  }

  // print out the unsorted array with positions displayed 
  printf("\n\nRead in Array: ");
  for(int i = 0; i < Arr1Size; ++i)
  {
    printf("(%d): %d ", i + 1, Arr1[i]);
  }

  // print out the sorted array with positions displayed
  printf("\n\nSorted Array: ");
  for(int i = 0; i < Arr1Size; ++i)
  {
    printf("(%d): %d ",i + 1, ArrCopy[i]);
  }
  // print out details of the arrays and our functions, and shows positions or results of Arr2
  for(int i = 0; i < Arr2Size; ++i)
  {
    int numComparisons = 0;

    printf("\n\nLinear Search Function Test:");
    int pos = linSearch(Arr1, Arr1Size, Arr2[i], &numComparisons);
      if(pos != -1)
      {
        printf("\nObject %d found at position %d in the read-in Array (unsorted).\n", Arr2[i], pos);
        printf("# of Comparisons: %d\n", numComparisons);
      }
      else
      {
        printf("\n** Object %d not found ** \n # of Comparisons: %d\n", Arr2[i], numComparisons);
      }

      numComparisons = 0;

      printf("\nBinary Search Function Test:");
      pos = binSearch(ArrCopy, Arr1Size, Arr2[i], &numComparisons);
      if(pos != -1)
      {
        printf("\nObject %d found at position %d in the sorted Array.\n", Arr2[i], pos);
        printf("# of Comparisons: %d\n", numComparisons);
      }
      else
      {
        printf("\n** Object %d not found ** \n # of Comparisons: %d\n", Arr2[i], numComparisons);
      }
  }

   // mitigation to stay clear from memory leaks or errors
  free(Arr1);
  free(ArrCopy);
  free(Arr2);

	return 0;
}