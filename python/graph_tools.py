#!/usr/bin/env python
# -*- coding:utf-8 -*-

class Edge(object):
    def __init__(self, src, dst, weight):
        self.src = src
        self.dst = dst
        self.weight = weight
    def __str__(self):
        return "#<{0.__class__.__name__} src={0.src} dst={0.dst} weight={0.weight}>".format(self)
    def __repr__(self):
        return self.__str__()

def maximumFlow(graph, s, t):
    n = len(graph)
    flow = [[0 for _ in range(n)] for _ in range(n)]
    capacity = [[0 for _ in range(n)] for _ in range(n)]
    for u in range(n):
        for e in graph[u]:
            capacity[e.src][e.dst] += e.weight

    total = 0
    while True:
        que = [s]
        prev = [-1 for i in range(n)]
        prev[s] = s
        while que and prev[t] < 0:
            u = que[-1]
            que.pop()
            for e in graph[u]:
                if prev[e.dst] < 0 and capacity[u][e.dst] - flow[u][e.dst] > 0:
                    prev[e.dst] = u
                    que.append(e.dst)
        if prev[t] < 0:
            return total
        inc = float('inf')
        j = t
        while prev[j] != j:
            inc = min(inc, capacity[prev[j]][j] - flow[prev[j]][j])
            j = prev[j]
        j = t
        while prev[j] != j:
            flow[prev[j]][j] += inc
            flow[j][prev[j]] -= inc
            j = prev[j]
        total += inc

def main():
    print("hello python!")

if __name__ == "__main__":
    main()
