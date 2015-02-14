import random

if __name__ == "__main__":
    with open('sample6.in', 'w') as f:
        f.writelines("1\n")

        n = random.randint(1, 501)
        f.writelines(str(n) + "\n")

        perm = range(1, n + 1)
        for i in xrange(0, 2*n):
            random.shuffle(perm)
            f.write(" ".join(map(lambda n: str(n), perm)))
            f.write("\n")
