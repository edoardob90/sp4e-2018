#!/usr/bin/env python3
class DumperSeries(object):
    """
    DumperSeries class (abstract)
    """
    def __init__(self, series):
        self.series = series
        self.name =  "Dumper for " + series.name
        self.step = series.step

    def dump(self):
        raise Exception("Pure virtual function of abstrac class DumperSeries!")

class PrintSeries(DumperSeries):
    """
    Output the result of series calculation
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.maxiter = 500
        self.freq = 10

    def dump(self, N=100):
        print("{:s}".format(self.name))
        print(type(self.step))
        print("Result for {:s} after {:d}: {:}".format(self.name, self.step, self.series.compute(N)) )

