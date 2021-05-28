def solve(n, m, dp):

    # base conditions
    if n == 0:
        return 1
    if m < 1:
        return 0
    if m == 1:
        return 1 if n <= 1 else 0
    if n == 1:
        return 1

    if dp[n][m] != -1:
        return dp[n][m]

    ans = 0
    i = min(n, m)
    while i >= 1:
        ans += solve(n-i, i-1, dp)
        i -= 1

    dp[n][m] = ans;
    return dp[n][m]


def solution(n):
    if n < 5:
        return 1
    ans = 0
    dp = [[-1 for i in range(n)] for j in range(n)]
    for i in range(1,n):
        ans += solve(n-i, i-1, dp)
    return ans

print solution(4)
