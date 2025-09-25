import pandas
import plotly.express as plotly
import sys

df = pandas.read_csv(sys.argv[1], header=None, names=['time', 'percentage'])
df['percentage'] = df['percentage'].str.replace('%', '').astype(float)
df['time'] = pandas.to_datetime(df['time'], format='%I:%M:%S %p')
fig = plotly.line(df, x='time', y='percentage', title='Battery Level Over Time')
fig.update_xaxes(title='Time', tickformat='%I:%M:%S %p')
fig.update_yaxes(title='Battery Level (as a % of total capacity)',ticksuffix='%')
fig.show()