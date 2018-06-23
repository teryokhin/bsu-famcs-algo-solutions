# Thanks, Python
open('output.txt', 'w').write(str(sum(set(int(x) for x in open('input.txt')))))