#!/usr/bin/python
# -*- coding: utf8 -*-
# cp936

import time
import subprocess
import sys

#注意关闭编译器优化选项
if sys.platform == 'win32':
    subprocess.call(['cl', '/O2', 'test.cpp'])
    exe_file = 'test.exe'
else:
    subprocess.call(['g++', '-O0', '-std=c++11', '-o', 'test', 'test.cpp'])
    exe_file = './test'

def test_func():
	starttime = time.time()
	subprocess.call([exe_file])
	endtime = time.time()
	return (endtime - starttime)
	
total = test_func()
	
print "\naverage: %.4fs" % total

#print "%.4fs" % (endtime-starttime)
#print "%.4fm" % ((endtime-starttime)/60)
