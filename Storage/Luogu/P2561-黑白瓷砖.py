from math import ceil

n = int(input())

ex = int(ceil(n * (n + 1) / 6))
ans = 2 ** (ex + 1) + 2 ** (n * (n + 1) // 2)
ex = 0

for i in range(1, n + 1):
    ex += int(ceil(i / 2))

ans += 3 * (2 ** ex)
ans //= 6
print(ans)