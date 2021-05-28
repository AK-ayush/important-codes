import itertools as itr

def solution(times, times_limit):
    n = len(times)
    numB = n-2
    idxB = [x+1 for x in range(numB)]

    distMat = allPairBF(times)
    if isNegCycle(distMat[0], times, n) :
        return range(numB)

    for candLen in range(numB , 0, -1):
        perm_list = list(itr.permutations(idxB, candLen))
        for perm in perm_list:
            cost = path_cost(perm, distMat, n)
            if cost <= times_limit:
                return [x-1 for x in sorted(perm)]
    return []
    
def path_cost(bunnies, distMat, n):
    m = len(bunnies)
    cost = distMat[0][bunnies[0]]
    cost += distMat[bunnies[m-1]][n-1]

    for i in range(m-1):
        cost += distMat[bunnies[i]][bunnies[i+1]]
    return cost


def allPairBF(graph):
    n = len(graph)
    distMat = []
    for V in range(n):
        dist = simpleBF(graph, V, n)
        distMat.append(dist)
    return distMat

def simpleBF(graph, src, n):
    dist = [float('inf') for _ in range(n)]
    dist[src] = 0
    for _ in range(n-1):
        for u in range(n):
            for v in range(n):
                if dist[u] != float('inf') and dist[u]+graph[u][v] < dist[v]:
                    dist[v] = dist[u]+graph[u][v]
    return dist

def isNegCycle(dist, graph, n):  # dist is distMat[0]
    for u in range(n):
        for v in range(n):
            if dist[u] != float('inf') and dist[u]+graph[u][v] < dist[v]:
                return True
    return False

# print solution([[0, 1, 1, 1, 1], [1, 0, 1, 1, 1], [1, 1, 0, 1, 1], [1, 1, 1, 0, 1], [1, 1, 1, 1, 0]], 3)
