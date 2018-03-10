from itertools import combinations

import sys

def powerset_ranges(numbers):
    """Recursively find powerset and add up the largest and smallest number"""
    total = 0
    for i in range(1, len(numbers) + 1):
        combos = list(combinations(numbers, i))
        for combo in [list(c) for c in combos]:
            total += combo[-1] - combo[0]

    return total

with open(sys.argv[1]) as fileobj:
    lines = fileobj.read().splitlines()

cases = int(lines[0])
lineidx = 1
for i in range(0, cases):
    n_numbers = int(lines[lineidx])
    lineidx += 1
    numbers = [int(n) for n in lines[lineidx].split()]
    print("Case #" + str(i + 1) + ": " + str(powerset_ranges(numbers) % 10000000007))
    lineidx += 1
