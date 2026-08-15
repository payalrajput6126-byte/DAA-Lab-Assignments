#include <iostream> 
#include <string> 
using namespace std; 
 
void merge(string orders[], int left, int mid, int right) 
{ 
    int i = left; 
    int j = mid + 1; 
    int k = 0; 
 
    int size = right - left + 1; 
    string *temp = new string[size]; 

    while (i <= mid && j <= right) 
    { 
        if (orders[i] <= orders[j]) 
        { 
            temp[k] = orders[i]; 
            i++; 
        } 
        else 
        { 
            temp[k] = orders[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i <= mid) 
    { 
        temp[k] = orders[i]; 
        i++; 
        k++; 
    } 
 
    while (j <= right) 
    { 
        temp[k] = orders[j]; 
        j++; 
        k++; 
    } 
 
    for (i = 0; i < size; i++)  
{ 
        orders[left + i] = temp[i]; 
    } 
 
    delete[] temp; 
} 
void mergeSort(string orders[], int left, int right) 
{ 
    if (left >= right) 
        return; 
 
    int mid = left + (right - left) / 2; 
  
    mergeSort(orders, left, mid); 
    mergeSort(orders, mid + 1, right); 
    merge(orders, left, mid, right); 
} 
 
int main() 
 
    int n; 
 
    cout << "Enter number of customer orders: "; 
    cin >> n; 
 
    string *orders = new string[n]; 

    cout << "Enter order timestamps (HH:MM):" << endl; 
 
    for (int i = 0; i < n; i++) 
    { 
        cin >> orders[i]; 
    } 
   mergeSort(orders, 0, n - 1); 
 
    cout << "\nSorted customer orders by timestamp:" << endl; 
    for (int i = 0; i < n; i++) 
    { 
        cout << orders[i] << " "; 
    } 
    cout << endl; 
 
    delete[] orders; 

 return 0; 
}                         
