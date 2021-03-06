#include <time.h>
#include <stdio.h>
#include <limits.h>

#define CROSSOVER   30

/* structure to store the result */
typedef struct {
    int left;
    int right;
    int sum;
} max_subarray_tuple;

/* brute force method */
max_subarray_tuple find_max_subarray_bf(int A[], int low, int high)
{
    int i, j, temp_sum;
    max_subarray_tuple ret = {0, 0, INT_MIN};

    for (i = low; i < high; i++) {
        temp_sum = 0;
        for (j = i; j < high; j++) {
            temp_sum += A[j];
            if (temp_sum > ret.sum) {
                ret.sum = temp_sum;
                ret.left = i;
                ret.right = j + 1;
            }
        }
    }
    return ret;
}

/* function for finding crossing maximum sub-array */
max_subarray_tuple find_max_crossing_subarray(int A[], int low, int mid, int high)
{
    int i, j;
    max_subarray_tuple ret = {0, 0, 0};
    int left_sum = INT_MIN;
    int right_sum = INT_MIN;
    int sum = 0;

    for (i = mid - 1; i >= low; i--) {
        sum += A[i];
        if (sum > left_sum) {
            left_sum = sum;
            ret.left = i;
        }
    }

    sum = 0;
    for (j = mid; j < high; j++) {
        sum += A[j];
        if (sum > right_sum) {
            right_sum = sum;
            ret.right = j + 1;
        }
    }
    ret.sum = left_sum + right_sum;

    return ret;
}

/* recursive method */
max_subarray_tuple find_max_subarray_rc(int A[], int low, int high)
{
    if (high == low + 1) {
        max_subarray_tuple ret = {low, high, A[low]};
        return ret;
    } else {
        int mid = (low + high) / 2;
        max_subarray_tuple left = find_max_subarray_rc(A, low, mid);
        max_subarray_tuple right = find_max_subarray_rc(A, mid, high);
        max_subarray_tuple cross = find_max_crossing_subarray(A, low, mid, high);

        if (left.sum >= right.sum && left.sum >= cross.sum)
            return left;
        else if (right.sum >= left.sum && right.sum >= cross.sum)
            return right;
        else
            return cross;
    }
}

/* modified mixed method */
max_subarray_tuple find_max_subarray_mx(int A[], int low, int high)
{
    if (high - low < CROSSOVER) {
        return find_max_subarray_bf(A, low, high);
    } else {
        int mid = (low + high) / 2;
        max_subarray_tuple left = find_max_subarray_rc(A, low, mid);
        max_subarray_tuple right = find_max_subarray_rc(A, mid, high);
        max_subarray_tuple cross = find_max_crossing_subarray(A, low, mid, high);

        if (left.sum >= right.sum && left.sum >= cross.sum)
            return left;
        else if (right.sum >= left.sum && right.sum >= cross.sum)
            return right;
        else
            return cross;
    }
}

/* driver code to measure performance */
int main()
{
    int i, n = 2, flag = 0;
    int Arr[100] = {20, -21, 43, -23, -92, 45, -56, -5, 34, -17,
                    34, 65, 89, -109, 125, 2, -10, 89, 46, 65, -49,
                    3, -45, 34, 76, 32, -76, -2, 3, -45, 44, 34, 67,
                    -67, 99, -104, 11, -37, 44, 76, -90, 89, -32, 34,
                    88, 56, -6, -89, -90, -34, -56, 23, 29, 2, 6, 9,
                    2, -34, -45, 34, 22, -177, 44, 90, -45, -36, 55,
                    23, 56, -56, -167, -54, 23, 45, 14, 62, -46, -56,
                    -34, 45, 32, 20, -87, 39, 82, 95, -67, -45, 88,
                    -36, 21, 18, 16, 81, -102, 99, -45, -67, -45, -76};

    clock_t start, stop;
    double time_bf, time_rc;

    printf("Size BruteForce Recursive Mixed\n");
    printf("-------------------------------\n");
    while(!flag) {
        printf("%d   ",n);
        start = clock();
        for (i = 0; i < 1000000; i++) {
            max_subarray_tuple R1 = find_max_subarray_bf(Arr, 0, n);
        }
        stop = clock();
        time_bf = ((double) (stop - start)) / CLOCKS_PER_SEC;
        printf("%f   ",time_bf);
        start = clock();
        for (i = 0; i < 1000000; i++) {
            max_subarray_tuple R2 = find_max_subarray_mx(Arr, 0, n);
        }
        stop = clock();
        time_rc = ((double) (stop - start)) / CLOCKS_PER_SEC;
        printf("%f   \n",time_rc);
        n++;
        if (time_bf > time_rc) {
            flag = 1;
        }
    }

    return 0;
}
