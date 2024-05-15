#include <stdio.h>
#include <stdlib.h>

// Structure for a single term in a polynomial
struct Term {
    int coefficient;
    int exponent;
    struct Term *next;
};

typedef struct Term Term;

// Function to create a new term
Term* createTerm(int coeff, int exp) {
    Term* newTerm = (Term*)malloc(sizeof(Term));
    if (newTerm == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newTerm->coefficient = coeff;
    newTerm->exponent = exp;
    newTerm->next = NULL;
    return newTerm;
}

// Function to insert a term into a polynomial
void insertTerm(Term **poly, int coeff, int exp) {
    Term *newTerm = createTerm(coeff, exp);
    if (*poly == NULL) {
        *poly = newTerm;
        return;
    }
    Term *current = *poly;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newTerm;
}

// Function to add two polynomials
Term* addPolynomials(Term *poly1, Term *poly2) {
    Term *result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            insertTerm(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            insertTerm(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            int sumCoeff = poly1->coefficient + poly2->coefficient;
            if (sumCoeff != 0) {
                insertTerm(&result, sumCoeff, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    // Add remaining terms from poly1
    while (poly1 != NULL) {
        insertTerm(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }
    // Add remaining terms from poly2
    while (poly2 != NULL) {
        insertTerm(&result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }
    return result;
}

// Function to display a polynomial
void displayPolynomial(Term *poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    while (poly != NULL) {
        printf("%dx^%d", poly->coefficient, poly->exponent);
        poly = poly->next;
        if (poly != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to free memory allocated for polynomials
void freePolynomial(Term *poly) {
    Term *temp;
    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
}

int main() {
    Term *poly1 = NULL;
    Term *poly2 = NULL;

    // Input for first polynomial
    int n, coeff, exp;
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &n);
    printf("Enter the coefficients and exponents of the terms:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly1, coeff, exp);
    }

    // Input for second polynomial
    printf("Enter the number of terms in the second polynomial: ");
    scanf("%d", &n);
    printf("Enter the coefficients and exponents of the terms:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly2, coeff, exp);
    }

    // Display the input polynomials
    printf("First polynomial: ");
    displayPolynomial(poly1);
    printf("Second polynomial: ");
    displayPolynomial(poly2);

    // Add the polynomials
    Term *result = addPolynomials(poly1, poly2);

    // Display the result
    printf("Result of addition: ");
    displayPolynomial(result);

    // Free memory
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);

    return 0;
}
