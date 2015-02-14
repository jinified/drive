import sys


def h(n):
    count = 0
    while n/2 > 0:
        count += 1
        n /= 2

    return count


def d(n):
    count = 0
    m = 1
    while m < n:
        count += 1
        m *= 2

    return count

if __name__ == "__main__":
    for i in range(int(eval(sys.argv[1])), int(eval(sys.argv[2])+1)):
        print "----------"
        print "%d: h(n) = %d; d(n) = %d" % (i, h(i), d(i))
        print "----------"
