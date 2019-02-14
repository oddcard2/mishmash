import sys

s = sys.stdin.readline().strip()

l1 = len(s)+1
dp = [l1*[0] for _ in range(l1)]
dp[0][0] = 1
for i in range(1, l1):
    for b in range(i):
        ss = s[i-1]
        if ss == '?' or ss == '(':
            dp[i][b+1] += dp[i-1][b]
        if ss == '?' or ss == ')':
            if b > 0 and dp[i-1][b] > 0:
                dp[i][b - 1] += dp[i - 1][b]

# for 100*'?' ans is 2257117854077248073253720 (> 2^64)
print(dp[l1-1][0])

# print('?'*100)
