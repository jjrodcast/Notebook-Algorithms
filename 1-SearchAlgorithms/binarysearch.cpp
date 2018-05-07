#include <iostream>
#include <algorithm>

using namespace std;

// This is the principal function, do not change the code of it.
bool binarysearch(int arr[], int left, int right, int value) {
   
   int mid = (left + right) / 2;

   if(left > right) return false;
   else if(value < arr[mid]) return binarysearch(arr, left, mid - 1, value);
   else if(value > arr[mid]) return binarysearch(arr, mid + 1, right, value); 
   else return true;
}

// All code inside main is just to show if the algorithm is working well
// feel free to change the code below, be careful and don't change the 
// binarysearch function because it does the "magic"
int main() {
   
    // You can change the length, value to search and the elments of the array
   int n = 10;
   int search = 8;
   int arr[n] = {1, 12, 20, 8, 45, 16, 70, 120, 125, 50};

   //1.- Sort the array
   sort(arr, arr + n);

   //2.-Call the function then return true if the element exist or false otherwise.
   bool pos = binarysearch(arr, 0, n-1, search);

   //3.- Just check if exists or not 
   (pos == true)? cout << "Exists\n" : cout << "Doesn't exists\n";
   
   // uncomment the line below to see the console in case it closes.
   //system("pause");
   
   return 0;
}