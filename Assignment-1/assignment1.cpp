
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void merge(vector<string>& orders, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;

    vector<string> temp;

    while (i <= mid && j <= right)
    {
        if (orders[i] <= orders[j])
        {
            temp.push_back(orders[i]);
            i++;
        }
        else
        {
            temp.push_back(orders[j]);
            j++;
        }
    }

    while (i <= mid)
    {
        temp.push_back(orders[i]);
        i++;
    }

    while (j <= right)
    {
        temp.push_back(orders[j]);
        j++;
    }

    for (int k = 0; k < (int)temp.size(); k++)
    {
        orders[left + k] = temp[k];
    }
}

void mergeSort(vector<string>& orders, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(orders, left, mid);
    mergeSort(orders, mid + 1, right);

    merge(orders, left, mid, right);
}

int main()
{
    ifstream file("orders.csv");

    if (!file.is_open())
    {
        cout << "Error: Could not open orders.csv" << endl;
        return 1;
    }

    vector<string> orders;
    string timestamp;

    // Skip CSV header
    getline(file, timestamp);

    // Read timestamps from CSV
    while (getline(file, timestamp))
    {
        if (!timestamp.empty())
            orders.push_back(timestamp);
    }

    file.close();

    cout << "Enter number of customer orders: "
         << orders.size() << endl;

    if (orders.empty())
        return 0;

    mergeSort(orders, 0, (int)orders.size() - 1);

    cout << "\nSorted customer orders by timestamp:" << endl;

    for (const string& order : orders)
    {
        cout << order << endl;
    }

    return 0;
}
