import math

def c(n, m):
    if n < m:
        return 0
    res = 1
    for i in range(n - m + 1, n + 1):
        res *= i
    # 若此处用 /= 会转型为 float，则不能使用 integer 的高精度计算
    for i in range(1, m + 1):
        res //= i
    return res

def parse():
    str = input()
    idx = str.find(" ")
    return int(str[:idx]), int(str[idx + 1:])

k, w = parse()
ans = 0
t = math.ceil(w / k)

for i in range(2, t + 1):
    ans += c(2 ** k - 1, i)
for i in range(2, (2 ** k) - (2 ** ((w - 1) % k + 1))):
    ans -= c(i, w // k)

print(int(ans))