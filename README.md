# DirectoryMonitoringSystem
It was used the version 6.8.1 of the Qt library.
This project implements a directory monitoring system developed as part of a university assignment. The application continuously observes a target folder named myDir and detects: 
  - file creation
  - file modification
  - file deletion.
  
Whenever one of these events occurs, the program logs it in the user interface and assigns a color-coded label depending on the event type
  - Green → file created
  - Blue → file modified
  - Red → file deleted

The monitored directory is initially empty, and the application checks its status every 3 seconds through a timed function.

# Directory Monitoring
Periodic scanning every 3 seconds.
Detection of: new files, changed files and removed files.
Internal comparison with previous directory state

# Graphical User Interface (Qt-based)
Real-time activity log window.
Entries displayed with different colors based on event type.
Automatic loading of previous session logs at startup.
Buttons or controls to:
  - Sort the log by:
    - filename
    - event type
    - timestamp
  - Save the current session log to a file.

# Logging System
Log entries store:
  - filename
  - event type
  - timestamp

On startup, the application checks for an existing log file and loads it if available.

On exit or on user request, the session log can be written to a file.

# How It Works
1.  Timed Directory Scan: A timer runs every 3 seconds to ensure that the application compares the current list of files with the previously stored list and detects changes.

2.  Logging Events: Each detected event generates a log entry. These entries appear in the UI with color-coded formatting.

3.  Sorting Log Entries: The user can sort the log by Filename, Event Type and Timestamp. Sorting have been implemented using Qt's model/view architecture (QTableWidget).

4.  Saving and Loading Logs: At startup, the application looks for a saved log file (for example session_log.txt). When the user selects “Save Log”, the current session is written to file.

