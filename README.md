# 📅 PyCalendar-CLI

A sleek, lightweight, terminal-based calendar generator written in Python. **PyCalendar-CLI** allows users to seamlessly display full-year calendars or individual monthly views directly in their terminal with clean formatting, adaptive OS screen clearing, and built-in input validation.

---

## 🚀 Features

- **Full-Year & Single-Month Views**: Quickly render an entire 12-month calendar or target a specific month on demand.
- **Sunday-First Layout**: Standard Sunday-start weekly format using Python's built-in `calendar.TextCalendar`.
- **Cross-Platform Compatibility**: Fully functional on Windows, Linux, and macOS terminal environments.
- **Robust Input Validation**: Gracefully handles invalid user inputs (non-integers, out-of-bounds months) without crashing.
- **Zero External Dependencies**: Built entirely on standard Python libraries—no `pip install` required!

---

## 🛠️ Project Architecture

```text
pycalendar-cli/
│
├── main.py            # Primary application entry point & input logic
├── utils.py           # UI rendering utilities & OS screen clearing
├── requirements.txt   # Standard dependency declaration
├── LICENSE            # MIT License
└── README.md          # Project documentation