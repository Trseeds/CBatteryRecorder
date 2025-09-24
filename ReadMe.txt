Selecting the charge test (1) will write to 'charge.csv' and will stop once 100% is reached.
Selecting the discharge test (2) will write to 'discharge.csv' and will stop once 5% is reached.
Previous results in chargecsv and discharge.csv will be erased upon beginning of a new test, make backups if needed.
Battery will be 255% if the WindowsAPI call had an unspecified error, this program will exit with an error if the entire call fails.
Uses:
*   Detect and diagnose charging issues.
*   Detect faulty batteries; if you know generally how much power your system draws and how big your battery is (for example my laptop runs at 20wh average on a 50wh battery), a discrepancy can indicate a damaged battery.
*   Get an accurate battery life figure, manufacuteres and Windows can only guess and tend to stretch it quite a bit.