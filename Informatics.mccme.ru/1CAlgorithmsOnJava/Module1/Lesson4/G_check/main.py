import sys

if __name__ == '__main__':
    #if len(sys.argv) < 2:
    #    print('Use application - app file_path')
    #    sys.exit()

    a = 0
    b = 0

    lines = sys.stdin.readlines()
    params = [int(s) for s in lines[0].split()]
    assert len(params) == 2, 'incorrect first line'
    v1 = params[0]
    v2 = params[1]

    for l in lines[1:]:
        l = l.strip()
        if len(l) == 2:
            if l[0] == '>':
                if l[1] == 'A':
                    a = v1
                    print('>A {} {}'.format(a, b))
                else:
                    b = v2
                    print('>B {} {}'.format(a, b))
            elif l[0] == 'A':
                a = 0
                print('A> {} {}'.format(a, b))
            else:
                b = 0
                print('B> {} {}'.format(a, b))
        elif len(l) == 3:
            if l[0] == 'A':
                v = min(a, v2-b)
                b += v
                a -= v
                print('A>B {} {}'.format(a, b))
            else:
                v = min(b, v1-a)
                a += v
                b -= v
                print('B>A {} {}'.format(a, b))

print('{} {}'.format(a, b))
