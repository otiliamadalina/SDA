//
// Created by ASUS on 31.05.2024.
//


int linear_search(int * array, int n, int key)
{
    for(int i=0; i<n; i++)
    {
        if(array[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int _binary_search(int* array, int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (array[mid] == x)
            return mid;

        if (array[mid] > x)
        {
            return _binary_search(array, l, mid - 1, x);
        }
        else
        {
            return _binary_search(array, mid + 1, r, x);
        }
    }

    return -1;
}


int binary_search(int * array, int n, int key)
{
    return _binary_search(array,0, n-1, key);
}


int sentinel_search(int * array, int n, int key)
{

    // Last element of the array
    int last = array[n - 1];

    // Element to be searched is
    // placed at the last index
    array[n - 1] = key;
    int i = 0;

    while (array[i] != key)
        i++;

    // Put the last element back
    array[n - 1] = last;

    if ((i < n - 1) || (array[n - 1] == key)) {
        return i;
    } else {
        return -1;
    }
}