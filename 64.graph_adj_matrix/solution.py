with open('input.txt') as f:
    n, m = [int(x) for x in next(f).split()]
    res = [[0]*n for i in range(n)]
    for _ in range(m):
        u, v = [int(x) for x in next(f).split()]
        res[u-1][v-1] = 1
        res[v-1][u-1] = 1

    with open('output.txt', 'w') as out:
        for line in res:
            for number in line:
                out.write(str(number) + ' ')
            out.write('\n')
