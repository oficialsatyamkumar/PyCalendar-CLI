# C Calendar & Event Reminder Application

An enhanced Command-Line Interface (CLI) Calendar and Event Reminder system built in **C**.

## Features

- **Monthly & Full Year Views**: Render clean grid calendars for any given month or full year using Zeller's Congruence.
- **Event Indicators**: Dates with scheduled reminders are visualised with an asterisk (`*`) on the grid (e.g. ` 16*`).
- **Persistent Storage**: Save notes and reminders to `events.txt` automatically so data persists across app runs.
- **Leap Year Verification**: Native support for Gregorian leap-year adjustments.

## Prerequisites

- GCC compiler
- Make utility (optional)

## Build and Run

```bash
# Build binary
make

# Run application
./calendar

# Cleanup build outputs
make clean
```

Alternatively, compile manually with:
```bash
gcc main.c -o calendar
./calendar
```

## License

Distributed under the [MIT License](LICENSE).
