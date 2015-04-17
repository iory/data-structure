#!/usr/bin/env python
# -*- coding:utf-8 -*-

import priority_queue

def dijkstra(graph, start):
    '''
    @property
    start: int
    '''
    V = len(graph)
    dist = [float('inf') for i in range(V)]
    used = [False for i in range(V)]
    q = priority_queue()
    q.push((0, start), 0)
    while not q.empty():
        _, _, (d, current_node) = q.pop()
        if used[current_node]: continue
        used[current_node] = True
        dist[current_node] = d
        for next_node, edge_cost in graph[current_node]:
            if dist[next_node] <= d + edge_cost:
                continue
            q.push((d+edge_cost, next_node), -(d+edge_cost))
    return dist

def main():
    print("dijkstra!")

if __name__ == "__main__":
    main()
