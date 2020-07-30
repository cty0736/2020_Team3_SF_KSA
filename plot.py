
import plotly
import plotly.graph_objs as go

# Create random data with numpy
import numpy as np

# Create a trace
def scatterchar(x,y):
    trace = go.Scatter(
        x = [0,x],
        y = [0,y],
        mode = 'markers'
    )
    data = [trace]
    return (plotly.offline.plot(data, filename='basic-scatter'))
# Plot and embed in ipython notebook!
