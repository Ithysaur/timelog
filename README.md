#timelog
Timelog is a simple command-line tool for tracking time spent on various tasks and projects. It allows users to log time entries. Data is stored in C:\Users\<username>\log\timelog
Valid Usage: timelog <username> <--log <logname> | --report [logname|all] | --clear [times|reports|all]>
##username
The username must be a valid user profile on the system.
##--log
The --log option records a new time entry for the specified logname. If the logname does not exist, it will be created. Use --log with the same logname when starting or stopping an entry.
##--report
The --report option generates a report of time entries. You can specify a particular logname to get a report for that log, or use "all" to get a report for all logs. If there are an odd number of time entries for a log, the last entry will be ignored when generating a report.
##--clear
The --clear option deletes time entries or reports. You can specify "times" to clear time entries, "reports" to clear generated reports, or "all" to clear both.