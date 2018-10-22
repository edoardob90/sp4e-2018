#!/usr/bin/env python3
class DumperSeries(object):
    """
    DumperSeries class (abstract)
    """
    def __init__(self, series):
        self.series = series
        self.name =  "Dumper for " + series.name
        self.step = series.step
        self.precision = 4

    def dump(self):
        raise Exception("Pure virtual function of abstrac class DumperSeries!")

    def __str__(self):
        return self.dump()

class PrintSeries(DumperSeries):
    """
    Output the result of series calculation
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        # freq and maxiter should be read from input
        self.maxiter = maxiter
        self.freq = freq

    def dump(self):
        output = ""
        for i in range(1, int(self.maxiter/self.freq)):
            res = self.series.compute(i*self.freq-1)
            res2 = self.series.compute(i*self.freq)

        output += "\n"
        return output

