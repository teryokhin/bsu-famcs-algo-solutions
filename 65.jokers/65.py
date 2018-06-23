
INF = int(1e9)


def score(state):
    result = 0
    cur = t
    for pair in a:
        if state[pair[1]] != 0:
            count = state[pair[1]]
            while cur > 0 and count > 0:
                result += pair[0]
                count -= 1
                cur -= 1
            while count > 0:
                result -= pair[0]
                count -= 1
    return result


max_score_mem = {}


def max_score(nj, state):
    key = (nj, state)
    if key in max_score_mem:
        return max_score_mem[key]

    if nj == 0:
        sc = score(state)
        max_score_mem[key] = sc
        return sc

    mx = -INF
    for i in range(0, len(state)):
        if state[i] != 0:
            for j in range(1, nj+1):
                new_state = list(state)
                new_state[i] -= 1
                new_state[i+j] += 1
                mx = max(mx, max_score(nj-j, tuple(new_state)))

    max_score_mem[key] = mx
    return mx


with open('jokers.in') as f:
    k, c, J, t = [int(x) for x in next(f).split()]
    a = sorted(((int(x), i) for i, x in enumerate(next(f).split())), reverse=True)

    n = int(f.readline())
    cards = [0] * (k+1)
    for x in next(f).split():
        cards[int(x)] += 1

    start_j = cards[0]
    start_state = [0] * (c+J+1)
    for x in cards[1:]:
        start_state[x] += 1
    with open('jokers.out', 'w') as out:
        out.write(str(max_score(start_j, tuple(start_state))))

