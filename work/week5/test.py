#!/usr/bin/env python3

import SeriesClass as sc
import DumperClass as dc

a = sc.ComputeArithmetic()
b = dc.PrintSeries(series=a)
b.dump(1000)

#what = input("Compute Pi or Arithmetic series? [ar | pi ] ")
#if what == "ar":
#    aseries = ComputeArithmetic()
#    aseries.compute(10)
#    aseries.printResult()
#elif what == "pi":
#    piseries = ComputePi()
#    piseries.compute(100)
#    piseries.printResult()
#else:
#    raise Exception("choose either [ar]ithmetic or [pi] computation!")
