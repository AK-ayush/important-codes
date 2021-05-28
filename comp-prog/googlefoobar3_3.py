from collections import deque



def solution(map):
    # Your code here
    m = len(map)
    n = len(map[0])

    seen = [[10000000 for i in range(n)] for j in range(m)]
    dirs = [[1,0], [-1, 0], [0, 1], [0, -1]]

    seen[0][0] = 0
    q = deque()
    q.append([0, 0, 0])
    step = 1
    while len(q) > 0:
        ll = len(q)
        for i in range(ll):
            curr = q.popleft()
            r = curr[0]
            c = curr[1]
            if r == m-1 and c == n-1:
                return step
            for d in dirs:
                r1 = r+d[0]
                c1 = c+d[1]
                if r1 < 0 or r1 >= m or c1 < 0 or c1 >= n:
                    continue
                print r1, c1
                obs = curr[2] + map[r1][c1]
                if obs >= seen[r1][c1] or obs > 1:
                    continue
                seen[r1][c1] = obs
                q.append([r1, c1, obs])

        step += 1

print solution([[0,1,0,0,0],[0,0,0,1,0],[1,1,1,1,0]])
