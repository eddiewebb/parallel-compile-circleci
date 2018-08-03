#include <stdio.h>
 
int longer() {
    double firstNumber, secondNumber, product;
    printf("Enter two numbers: ");
    // Stores two floating point numbers in variable firstNumber and secondNumber respectively
    scanf("%lf %lf", &firstNumber, &secondNumber);  
    // Performs multiplication and stores the result in variable productOfTwoNumbers
    product = firstNumber * secondNumber;  
    // Result up to 2 decimal point is displayed using %.2lf
    printf("Product = %.2lf", product);



    int year;
    printf("Enter a year: ");
    scanf("%d",&year);
    if(year%4 == 0)
    {
        if( year%100 == 0)
        {
            // year is divisible by 400, hence the year is a leap year
            if ( year%400 == 0)
                printf("%d is a leap year.", year);
            else
                printf("%d is not a leap year.", year);
        }
        else
            printf("%d is a leap year.", year );
    }
    else
        printf("%d is not a leap year.", year);
   return 0;
}