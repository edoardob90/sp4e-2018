#!/usr/bin/env python3
class Series:
    """
    Series main class (abstract)
    """
    def __init__(self):
        self.current_step = 0
        self.current_result = 0.

    def compute(self, N):
        if self.current_step <= N:
            N -= self.current_step
        else:
            self.current_step = 0
            self.current_result = 0.

        for k in range(0,N):
            self.addTerm()

    def addTerm(self):
        self.current_step += 1
        self.current_result += self.computeTerm(self.current_result)
    
    def computeTerm(self, k):
        pass


# Arithmetic computation class
class ComputeArithmetic(Series):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.name = "Arithmetic series"

    def compute(self, N=100):
        super().compute(N)
        return self.result
    
    def computeTerm(self, k):
        return float(k)

# Pi computation class
class ComputePi(Series):

    # We need the square root here
    math = __import__('math')

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.name = "Pi series"

    def compute(self, N):
        super().compute(N)
        return math.sqrt(6.*self.current_result)

    def computeTerm(self, k):
        return 1./k**2.


