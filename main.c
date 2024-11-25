#include <stdio.h>
//uses Zeller's formula to calculate the day of the week
int GetDayOfWeek(int day, int month, int year) {
    if (month == 1 || month == 2) {
        month += 12;
        year--;
    }
    int k = year % 100;
    int j = year / 100;
    int DayOfWeek = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;

    return (DayOfWeek + 6) % 7;
}
//determines if a year is a leap year using the standard rules
int LeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
//main function
void printCalendar(int month, int year) {
    const char *months[] = {
        "january", "february", "march", "april", "may", "june",
        "july", "august", "september", "october", "november", "december"
    };
    const int DaysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = DaysInMonth[month - 1];

    if (month == 2 && LeapYear(year)) {
        days = 29;
    }

    printf("\n    %s %d\n", months[month - 1], year);
    printf("Su Mo Tu We Th Fr Sa\n");
//determines the first day of a month
    int startDay = GetDayOfWeek(1, month, year);

    for (int i = 0; i < startDay; i++) {
        printf("   ");
    }

    for (int day = 1; day <= days; day++) {
        printf("%2d ", day);
        if ((startDay + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int main() {
    int month, year;
//enterind month and years
    printf("Enter month (1-12): ");
    scanf("%d", &month);
    printf("Enter year: ");
    scanf("%d", &year);
//check for correct input
    if (month < 1 || month > 12 || year < 1) {
        printf("ERROR. Month should be (1-12) and year > 0 .\n");
        return 1;
    }

    printCalendar(month, year);

    return 0;
}