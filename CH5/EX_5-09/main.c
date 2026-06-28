#include <stdio.h>

/* Number of days in each month.
   day_tab[0] -> Normal year
   day_tab[1] -> Leap year
*/
char day_tab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_the_year(int year, int month, int day);
int month_day(int year, int day, int *pday, int *pmonth);

int main(void)
{
    int year, month, day;
    int yearday;
    int result_month, result_day;

    printf("Enter year month day (e.g. 2024 12 31): ");
    scanf("%d %d %d", &year, &month, &day);

    /* Convert month/day to day of the year */
    yearday = day_of_the_year(year, month, day);

    if (yearday == -1)
    {
        printf("Error! Invalid date.\n");
        return 1;
    }

    printf("\nDay of the year: %d\n", yearday);

    /* Convert day of the year back to month/day */
    if (month_day(year, yearday, &result_day, &result_month) == -1)
    {
        printf("Error! Invalid day of the year.\n");
        return 1;
    }

    printf("Converted back: %02d/%02d/%d\n",
           result_day, result_month, year);

    return 0;
}

/* Convert a month/day into the corresponding day of the year. */
int day_of_the_year(int year, int month, int day)
{
    int i, leap;

    /* Leap year or normal year. */
    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    /* Error checking */
    if (year < 1 ||
        month < 1 || month > 12 ||
        day < 1 || day > *(*(day_tab + leap) + month))
        return -1;

    /* Add the days in all months preceding the given month. */
    for (i = 1; i < month; i++)
        day += *(*(day_tab + leap) + i);

    return day;
}

/* Convert a day of the year into its corresponding month and day. */
int month_day(int year, int day, int *pday, int *pmonth)
{
    int i, leap;

    /* Leap year or normal year. */
    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    /* Error checking */
    if (year < 1 ||
        day < 1 ||
        day > (leap ? 366 : 365))
        return -1;

    /* Find the month by subtracting each month's length until
       the remaining number of days fits in the current month. */
    for (i = 1; day > *(*(day_tab + leap) + i); i++)
        day -= *(*(day_tab + leap) + i);

    /* Store the resulting day and month. */
    *pday = day;
    *pmonth = i;

    return 0;
}
