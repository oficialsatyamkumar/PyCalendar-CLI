import os

def clear_screen():
    """Clears the terminal screen based on OS."""
    os.system('cls' if os.name == 'nt' else 'clear')

def print_banner():
    """Displays CLI banner."""
    banner = """
    ****************************************
    *             PyCalendar CLI           *
    *      Command-Line Calendar Viewer     *
    ****************************************
    """
    print(banner)