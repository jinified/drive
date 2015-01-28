#!/usr/bin/env python

import sys
import math

def half(n):
    count = 0;
    while n != 0:
        print count
        count+=1
        n /=2
    return count


def r_double(ls):
    tmp = map(lambda x:math.ceil(math.log(x,2)),ls)
    return tmp

def r_half(ls):
    tmp = map(lambda x:math.floor(math.log(x,2))+1, ls)
    return tmp
        
if __name__ == "__main__":
    a = [i for i in xrange(1,25)]
    for i in [31,32,33,63,64,65,100,127,128,129,1000,1023,1024,1025,10**6,10**9]:
        a.append(i)
    print(r_half(a))
    print(r_double(a))
