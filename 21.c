#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Student structure
struct Student {
    char student_name[50];
    int student_roll_no;
    int total_marks;
};

// Function to merge two subarrays
void merge(struct Student arr[], int l, int m, int r, int *swap_count) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    struct Student L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].student_roll_no <= R[j].student_roll_no) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            (*swap_count)++;
        }
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k++] = L[i++];
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Function to perform merge sort
void mergeSort(struct Student arr[], int l, int r, int *swap_count) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, swap_count);
        mergeSort(arr, m + 1, r, swap_count);

        // Merge the sorted halves
        merge(arr, l, m, r, swap_count);
    }
}

int main() {
    int n, i;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student *students = (struct Student *)malloc(n * sizeof(struct Student));

    // Input student details
    for (i = 0; i < n; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].student_name);
        printf("Roll Number: ");
        scanf("%d", &students[i].student_roll_no);
        printf("Total Marks: ");
        scanf("%d", &students[i].total_marks);
    }

    int swap_count = 0; // Initialize swap count

    // Perform merge sort
    mergeSort(students, 0, n - 1, &swap_count);

    // Output sorted student details
    printf("\nSorted Student List:\n");
    printf("Roll No.\tName\tTotal Marks\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%s\t%d\n", students[i].student_roll_no, students[i].student_name, students[i].total_marks);
    }

    printf("\nNumber of swaps performed: %d\n", swap_count);

    free(students); // Free dynamically allocated memory
    return 0;
}
