import math


def c(n, k):
    if k > n:
        return 0
    return math.factorial(n)//math.factorial(k)//math.factorial(n-k)


a_mem = [1] + [None]*100
def a(n):
    if a_mem[n] is not None:
        return a_mem[n]
    a_mem[n] = sum(((-1)**(k-1))*c(n, k)*(2**(k*(n-k)))*a(n-k) for k in range(1, n+1)) # via http://mathworld.wolfram.com/AcyclicDigraph.html
    return a_mem[n]


x = int(open('input.txt').read())
open('output.txt', 'w').write(str(a(x)))