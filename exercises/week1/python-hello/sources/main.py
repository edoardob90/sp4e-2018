import sys
import series

print("Hello World!") # print "Hello"
#print(len(sys.argv),type(sys.argv)) # check the type of sys.argv
print("Your number is ",int(sys.argv[1]))
series.computeSeries(sys.argv[1])

