import time
import subprocess

subprocess.call(['cl', 'test.cpp'])

def test_func():
	starttime = time.time()
	subprocess.call(['test.exe'])
	endtime = time.time()
	return (endtime - starttime)
	
n = 10
if n < 3:
	print "n must >= 3"
	exit(0)
	
result = []	
for i in range(n):
	result.append(test_func())
	print "%d %.4fs" % (i, result[i])
	
max_time = result[0]
min_time = result[1]
total = 0.0
for i in range(len(result)):
	if result[i] > max_time:
		max_time = result[i]
	if result[i] < min_time:
		min_time = result[i]
	total = total + result[i]
	
print "\naverage: %.4fs" % ((total - max_time- min_time) / (len(result) - 2))

#print "%.4fs" % (endtime-starttime)
#print "%.4fm" % ((endtime-starttime)/60)