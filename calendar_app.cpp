#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

struct Event {
    int day, month, year;
    string title;
    string description;
};

vector<Event> events;

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month - 1];
}

// Zeller's Congruence: returns 0=Sun, 1=Mon, ..., 6=Sat
int firstDayOfMonth(int month, int year) {
    if (month < 3) { month += 12; year--; }
    int k = year % 100;
    int j = year / 100;
    int h = (1 + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
    int d = ((h + 5) % 7); // 0=Mon ... 6=Sun -> convert to 0=Sun
    return (h + 6) % 7;    // 0=Sun, 1=Mon, ..., 6=Sat
}

string monthName(int month) {
    string names[] = {"January","February","March","April","May","June",
                      "July","August","September","October","November","December"};
    return names[month - 1];
}

void printCalendar(int month, int year) {
    cout << "\n  " << monthName(month) << " " << year << "\n";
    cout << " Su Mo Tu We Th Fr Sa\n";

    int startDay = firstDayOfMonth(month, year);
    int totalDays = daysInMonth(month, year);

    // Print leading spaces
    for (int i = 0; i < startDay; i++) cout << "   ";

    for (int day = 1; day <= totalDays; day++) {
        // Mark days that have events
        bool hasEvent = false;
        for (auto& e : events)
            if (e.day == day && e.month == month && e.year == year)
                hasEvent = true;

        if (hasEvent)
            cout << "\033[1;32m" << setw(3) << day << "\033[0m";
        else
            cout << setw(3) << day;

        if ((startDay + day) % 7 == 0) cout << "\n";
    }
    cout << "\n";
}

void addEvent() {
    Event e;
    cout << "Enter date (day month year): ";
    cin >> e.day >> e.month >> e.year;
    cin.ignore();
    cout << "Enter event title: ";
    getline(cin, e.title);
    cout << "Enter description (optional): ";
    getline(cin, e.description);
    events.push_back(e);
    cout << "Event added!\n";
}

void viewEvents(int month, int year) {
    cout << "\nEvents in " << monthName(month) << " " << year << ":\n";
    bool found = false;
    for (auto& e : events) {
        if (e.month == month && e.year == year) {
            cout << "  [" << e.day << "] " << e.title;
            if (!e.description.empty()) cout << " - " << e.description;
            cout << "\n";
            found = true;
        }
    }
    if (!found) cout << "  No events this month.\n";
}

void deleteEvent() {
    int day, month, year;
    cout << "Enter date of event to delete (day month year): ";
    cin >> day >> month >> year;
    cin.ignore();
    cout << "Enter event title to delete: ";
    string title;
    getline(cin, title);

    auto it = remove_if(events.begin(), events.end(), [&](const Event& e) {
        return e.day == day && e.month == month && e.year == year && e.title == title;
    });

    if (it != events.end()) {
        events.erase(it, events.end());
        cout << "Event deleted.\n";
    } else {
        cout << "Event not found.\n";
    }
}

void searchEvents() {
    cin.ignore();
    cout << "Enter keyword to search: ";
    string keyword;
    getline(cin, keyword);
    cout << "\nSearch results for \"" << keyword << "\":\n";
    bool found = false;
    for (auto& e : events) {
        if (e.title.find(keyword) != string::npos || e.description.find(keyword) != string::npos) {
            cout << "  " << e.day << "/" << e.month << "/" << e.year
                 << " - " << e.title;
            if (!e.description.empty()) cout << " (" << e.description << ")";
            cout << "\n";
            found = true;
        }
    }
    if (!found) cout << "  No matching events found.\n";
}

int main() {
    int currentMonth, currentYear;
    cout << "=== C++ Calendar App ===\n";
    cout << "Enter starting month and year (month year): ";
    cin >> currentMonth >> currentYear;

    int choice;
    while (true) {
        printCalendar(currentMonth, currentYear);
        cout << "\n1. Next Month\n";
        cout << "2. Previous Month\n";
        cout << "3. Add Event\n";
        cout << "4. View Events This Month\n";
        cout << "5. Delete Event\n";
        cout << "6. Search Events\n";
        cout << "7. Go to Specific Month/Year\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                currentMonth++;
                if (currentMonth > 12) { currentMonth = 1; currentYear++; }
                break;
            case 2:
                currentMonth--;
                if (currentMonth < 1) { currentMonth = 12; currentYear--; }
                break;
            case 3:
                addEvent();
                break;
            case 4:
                viewEvents(currentMonth, currentYear);
                break;
            case 5:
                deleteEvent();
                break;
            case 6:
                searchEvents();
                break;
            case 7:
                cout << "Enter month and year: ";
                cin >> currentMonth >> currentYear;
                break;
            case 0:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid option.\n";
        }
    }
    return 0;
}
