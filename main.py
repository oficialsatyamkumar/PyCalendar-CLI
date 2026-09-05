import calendar
import sys
from utils import clear_screen, print_banner

def display_full_year(year: int):
    """Prints all 12 months for the given year."""
    cal = calendar.TextCalendar(calendar.SUNDAY)
    print(f"\n{'=' * 20} YEAR {year} {'=' * 20}\n")
    for month in range(1, 13):
        cal.prmonth(year, month)
        print("-" * 30)

def display_single_month(year: int, month: int):
    """Prints a specific month for the given year."""
    cal = calendar.TextCalendar(calendar.SUNDAY)
    print("\n")
    cal.prmonth(year, month)
    print("-" * 30)

def main():
    clear_screen()
    print_banner()
    
    try:
        year_input = input("Enter year (e.g., 2026): ").strip()
        if not year_input.isdigit():
            raise ValueError("Year must be a positive integer.")
        year = int(year_input)

        choice = input("Display full year? (y/n, default 'y'): ").strip().lower()
        
        if choice == 'n':
            month_input = input("Enter month (1-12): ").strip()
            if not month_input.isdigit() or not (1 <= int(month_input) <= 12):
                raise ValueError("Month must be an integer between 1 and 12.")
            month = int(month_input)
            display_single_month(year, month)
        else:
            display_full_year(year)

    except ValueError as err:
        print(f"\n[Error]: {err}")
        sys.exit(1)
    except KeyboardInterrupt:
        print("\nProgram interrupted. Exiting...")
        sys.exit(0)

if __name__ == "__main__":
    main()