open('output.txt','w').write('\n'.join(str(i) for i in range(64) if str(bin(int(open('input.txt').read()))).rjust(64,'0')[::-1][i]=='1'))
