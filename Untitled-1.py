# Program to print the calendar of any given year

import calendar
y = int(input("Enter the year: "))
m = 1
print("\n******** CALENDAR *******")
Cal = calendar.TextCalendar(calendar.SUNDAY)
# An instance of TextCalendar class is created and calendar. SUNDAY means that you want to start displaying the calendar from sunday
i=1
while i<=12:
    Cal.prmonth(y,i)
    i+=1
#prmonth() is a function of the class that prints the calendar for given month and year
