#!/usr/bin/env python3
class Series:
    """
    Series main class (abstract)
    """
    def __init__(self):
        pass

    def compute(self, N):
        raise Exception("pure virtual function!")

# I don't know if this will work (probably not)
#    def printResult(self):
#        print("For {:s} the result is {:f}".format(self.name, self.result))

# Arithmetic computation class
class ComputeArithmetic(Series):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.step = 0
        self.result = 0
        self.name = "Arithmetic series"

    def compute(self, N=100):
        for i in range(1,N+1):
            self.step += 1
            self.result += i
        return self.result
    
#    def printResult(self):
#        print("For {:s} the result is {:d}".format(self.name, self.result))

# Pi computation class
class ComputePi(Series):
    # We need the square root here
    math = __import__('math')

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.name = "Pi series"
        self.result = 0.

    def compute(self, N):
        for i in range(1,N+1):
            self.result += 1/float(i)**2
        self.result = self.math.sqrt(6*self.result)
        return self.result

#    def printResult(self):
#        print("For {:s} the result is {:f}".format(self.name, self.result))



