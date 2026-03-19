# 📅 C++ Calendar App

A terminal-based calendar application written in C++ that allows you to view monthly calendars, manage events, and search through your schedule.

---

## Features

- **Monthly Calendar View** — Navigate between months with highlighted event days
- **Event Management** — Add, view, and delete events with titles and descriptions
- **Event Search** — Search events by keyword across all months
- **Color Highlighting** — Days with events are highlighted in green in the terminal
- **Navigation** — Move forward/backward through months or jump to any specific month/year

---

## Requirements

- C++ compiler (g++ or clang++) with C++11 support or later
- ANSI-compatible terminal (for color support)

---

## Compilation

```bash
g++ -std=c++11 -o calendar_app calendar_app.cpp
```

Or using clang++:

```bash
clang++ -std=c++11 -o calendar_app calendar_app.cpp
```

---

## Running the App

```bash
./calendar_app
```

You will be prompted to enter a starting month and year:

```
=== C++ Calendar App ===
Enter starting month and year (month year): 3 2025
```

---

## Usage

Once launched, you'll see a calendar for the current month and a menu:

```
  March 2025
 Su Mo Tu We Th Fr Sa
                    1
  2  3  4  5  6  7  8
  9 10 11 12 13 14 15
 16 17 18 19 20 21 22
 23 24 25 26 27 28 29
 30 31

1. Next Month
2. Previous Month
3. Add Event
4. View Events This Month
5. Delete Event
6. Search Events
7. Go to Specific Month/Year
0. Exit
Choice:
```

### Menu Options

| Option | Description |
|--------|-------------|
| `1` | Go to the next month |
| `2` | Go to the previous month |
| `3` | Add a new event (date, title, description) |
| `4` | List all events in the currently displayed month |
| `5` | Delete an event by date and title |
| `6` | Search all events by keyword |
| `7` | Jump to a specific month and year |
| `0` | Exit the application |

### Adding an Event

```
Enter date (day month year): 15 3 2025
Enter event title: Team Meeting
Enter description (optional): Weekly sync with the dev team
Event added!
```

### Deleting an Event

```
Enter date of event to delete (day month year): 15 3 2025
Enter event title to delete: Team Meeting
Event deleted.
```

### Searching Events

```
Enter keyword to search: Meeting

Search results for "Meeting":
  15/3/2025 - Team Meeting (Weekly sync with the dev team)
```

---

## Project Structure

```
calendar_app/
│
├── calendar_app.cpp     # Main source file
└── README.md            # This file
```

---

## Code Overview

### Data Structure

Events are stored in a global `vector<Event>` where each `Event` holds:

| Field | Type | Description |
|-------|------|-------------|
| `day` | `int` | Day of the month (1–31) |
| `month` | `int` | Month number (1–12) |
| `year` | `int` | Full year (e.g., 2025) |
| `title` | `string` | Event name |
| `description` | `string` | Optional details |

### Key Functions

| Function | Description |
|----------|-------------|
| `isLeapYear(year)` | Returns true if the given year is a leap year |
| `daysInMonth(month, year)` | Returns the number of days in a given month |
| `firstDayOfMonth(month, year)` | Returns the weekday of the 1st using Zeller's Congruence (0=Sun) |
| `monthName(month)` | Returns the full month name as a string |
| `printCalendar(month, year)` | Renders the calendar grid to the terminal with color-coded event days |
| `addEvent()` | Interactive prompt to add a new event |
| `viewEvents(month, year)` | Lists all events for a given month/year |
| `deleteEvent()` | Removes an event matching date and title |
| `searchEvents()` | Searches all events by keyword in title or description |

### Calendar Algorithm

The first day of each month is calculated using **Zeller's Congruence**, a mathematical formula that determines the day of the week for any calendar date.

---

## Limitations

- **No persistence** — Events are stored in memory only and are lost when the app exits
- **No input validation** — Invalid dates (e.g., day 32) are not rejected
- **Single session** — No file save/load functionality
- **Terminal colors** — Color highlighting uses ANSI escape codes and may not display correctly on all terminals (e.g., Windows CMD without ANSI support)

---

## Possible Improvements

- Save and load events from a file (CSV or JSON)
- Input validation for dates and month ranges
- Recurring events support
- Cross-platform color support
- Weekly or agenda view modes

---

## License

This project is open-source and free to use for educational and personal purposes.
