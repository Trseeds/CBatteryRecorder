This program records the battery level as a % every time it changes. This number along with the time it was recorded are saved into a .csv so you may inspect them easily.
A Python library is then used to create a line graph, which will generate and load automatically in your browser once recording stops.

Selecting the charge test (1) will write to 'charge.csv' and will stop once 100% is reached.
Selecting the discharge test (2) will write to 'discharge.csv' and will stop once 5% is reached.
Previous results in charge.csv and discharge.csv will be erased upon beginning of a new test, make backups if needed.
Battery will be 255% if the WindowsAPI call had an unspecified error, this program will likely exit with an error if the API call fails.

In order for the plotting to work, Python3, as well as pandas and plotly need to be installed on your system in your path.
Should the automatic plotting fail, you can try yourself by dragging your csv over plot.py, or by running it from the terminal, specifying the path to your csv as the first and only argument.

Uses:
*   Detect and diagnose charging issues.
*   Detect faulty batteries; if you know generally how much power your system draws and how big your battery is (for example my laptop runs at 20wh average on a 50wh battery), a discrepancy can indicate a damaged battery.
*   Get an accurate battery life figure, manufacturers and Windows can only guess and tend to stretch it quite a bit.
Some useful equations:
*   Remaining battery life = (Current Battery % * Time Change) / (Previous Battery % - Current Battery %)
    Example: (98% * 7min) / (100% - 98%) = 343 minutes remaining.
*   Remaining time to full charge = ((Full Capacity % - Current Battery %) * Time Change) / (Current Battery % - Previous Battery %)
    Example: ((100% - 99%) * 4min) / (99% - 96%) = 1.3 minutes remaining.

