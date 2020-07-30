
import plotly
import plotly.offline
import plotly.graph_objs as go

# Create random data with numpy
import numpy as np

# Create a trace
def scatterchar(x,y):
    center = go.Scatter(
        x = [0],
        y = [0],
        mode = 'markers',
        marker = dict(size=10,
        color='rgb(0,0,0)',
        symbol=0)
    )
    base = go.Scatter(
        x = [50,-50,50,-50],
        y = [50,-50,-50,50],
        mode = 'markers',
        marker = dict(size=1,
        color=0,
        symbol=0)
    )
    trace = go.Scatter(
        x = [x],
        y = [y],
        mode = 'markers',
        marker = dict(size=30,
        color='rgb(255,0,0)',
        symbol=3)
    )
    data = [center,base,trace]
    return (plotly.offline.plot(data, filename='basic-scatter'))
# Plot and embed in ipython notebook!


scatterchar(10,30)