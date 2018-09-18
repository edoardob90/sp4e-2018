import sys
import series.py

print("Hello World!") # print "Hello"
#print(len(sys.argv),type(sys.argv)) # check the type of sys.argv
print("Your number is ",int(sys.argv[1]))
computeSeries(sys.argv[1])
