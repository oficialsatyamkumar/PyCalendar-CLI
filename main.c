#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOTE_LEN 100
#define MAX_EVENTS 100
#define FILE_NAME "events.txt"

typedef struct {
    int day;
    int month;
    int year;
    char note[MAX_NOTE_LEN];
} Event;

Event events[MAX_EVENTS];
int event_count = 0;

// Function to check if a year is a leap year
int is_leap_year(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;
    }
    return 0;
}

// Get number of days in a given month
int get_days_in_month(int year, int month) {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days[month];
}

// Zeller's Congruence to find starting day of the month
int get_first_day_of_month(int year, int month) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int k = year % 100;
    int j = year / 100;
    int day = (1 + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) + (5 * j)) % 7;
    return (day + 5) % 7;
}

// Check if an event exists for a given date
int has_event(int day, int month, int year) {
    for (int i = 0; i < event_count; i++) {
        if (events[i].day == day && events[i].month == month && events[i].year == year) {
            return 1;
        }
    }
    return 0;
}

// Load events from storage file
void load_events(void) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return;

    event_count = 0;
    while (fscanf(fp, "%d %d %d ", &events[event_count].day, &events[event_count].month, &events[event_count].year) == 3) {
        if (fgets(events[event_count].note, MAX_NOTE_LEN, fp)) {
            events[event_count].note[strcspn(events[event_count].note, "
")] = 0;
            event_count++;
            if (event_count >= MAX_EVENTS) break;
        }
    }
    fclose(fp);
}

// Save events to storage file
void save_events(void) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) return;

    for (int i = 0; i < event_count; i++) {
        fprintf(fp, "%d %d %d %s
", events[i].day, events[i].month, events[i].year, events[i].note);
    }
    fclose(fp);
}

// Add a new event
void add_event(void) {
    if (event_count >= MAX_EVENTS) {
        printf("
Error: Event capacity full!
");
        return;
    }

    int day, month, year;
    printf("
Enter Date (DD MM YYYY): ");
    if (scanf("%d %d %d", &day, &month, &year) != 3) {
        printf("Invalid date input.
");
        while (getchar() != '
');
        return;
    }

    if (month < 1 || month > 12 || day < 1 || day > get_days_in_month(year, month)) {
        printf("Invalid date provided for year %d.
", year);
        return;
    }

    printf("Enter event note/reminder: ");
    while (getchar() != '
'); // clear buffer
    fgets(events[event_count].note, MAX_NOTE_LEN, stdin);
    events[event_count].note[strcspn(events[event_count].note, "
")] = 0;

    events[event_count].day = day;
    events[event_count].month = month;
    events[event_count].year = year;

    event_count++;
    save_events();
    printf("Event added and saved successfully!
");
}

// View events for a specific date
void view_events_by_date(void) {
    int day, month, year;
    printf("
Enter Date to search (DD MM YYYY): ");
    if (scanf("%d %d %d", &day, &month, &year) != 3) {
        printf("Invalid date input.
");
        while (getchar() != '
');
        return;
    }

    int found = 0;
    printf("
--- Reminders for %02d/%02d/%d ---
", day, month, year);
    for (int i = 0; i < event_count; i++) {
        if (events[i].day == day && events[i].month == month && events[i].year == year) {
            printf("- %s
", events[i].note);
            found = 1;
        }
    }
    if (!found) {
        printf("No reminders scheduled for this date.
");
    }
}

// Print calendar for a single month with event indicators (*)
void print_month_calendar(int year, int month) {
    const char *months[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    printf("
  ------------ %s %d ------------
", months[month], year);
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat
");

    int first_day = get_first_day_of_month(year, month);
    int days_in_month = get_days_in_month(year, month);

    for (int i = 0; i < first_day; i++) {
        printf("     ");
    }

    for (int day = 1; day <= days_in_month; day++) {
        if (has_event(day, month, year)) {
            printf("%4d*", day); // Marked with '*' for event
        } else {
            printf("%5d", day);
        }

        if ((day + first_day) % 7 == 0) {
            printf("
");
        }
    }
    printf("
 (* indicates a scheduled reminder)
");
}

// Display full-year calendar
void print_full_year_calendar(int year) {
    printf("
===========================================
");
    printf("            CALENDAR FOR YEAR %d            
", year);
    printf("===========================================
");

    for (int month = 1; month <= 12; month++) {
        print_month_calendar(year, month);
    }
}

void display_menu(void) {
    printf("
===================================
");
    printf("   C CALENDAR & REMINDER SYSTEM    
");
    printf("===================================
");
    printf("1. Display Specific Month Calendar
");
    printf("2. Display Full Year Calendar
");
    printf("3. Add Event / Reminder
");
    printf("4. View Reminders by Date
");
    printf("5. Check Leap Year
");
    printf("0. Exit
");
    printf("===================================
");
    printf("Select an option: ");
}

int main(void) {
    load_events(); // Load existing persistent events from file

    int choice, year, month;

    while (1) {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid menu number.
");
            while (getchar() != '
');
            continue;
        }

        if (choice == 0) {
            printf("Exiting calendar application. Goodbye!
");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter year and month (e.g., 2026 9): ");
                if (scanf("%d %d", &year, &month) == 2 && year > 0 && month >= 1 && month <= 12) {
                    print_month_calendar(year, month);
                } else {
                    printf("Invalid year or month entered.
");
                    while (getchar() != '
');
                }
                break;

            case 2:
                printf("Enter year (e.g., 2026): ");
                if (scanf("%d", &year) == 1 && year > 0) {
                    print_full_year_calendar(year);
                } else {
                    printf("Invalid year entered.
");
                    while (getchar() != '
');
                }
                break;

            case 3:
                add_event();
                break;

            case 4:
                view_events_by_date();
                break;

            case 5:
                printf("Enter year: ");
                if (scanf("%d", &year) == 1 && year > 0) {
                    if (is_leap_year(year)) {
                        printf("Year %d IS a leap year.
", year);
                    } else {
                        printf("Year %d IS NOT a leap year.
", year);
                    }
                } else {
                    printf("Invalid year entered.
");
                    while (getchar() != '
');
                }
                break;

            default:
                printf("Invalid choice. Try again.
");
                break;
        }
    }

    return 0;
}
