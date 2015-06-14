#!/usr/bin/env python
# -*- coding:utf-8 -*-

class UnionFind(object):
    def __init__(self, N, root_node=0):
        self.N = N
        self.root_node = root_node
        self.par = list(range(self.N))
        self.rank = [0] * self.N
    def __str__(self):
        return "#<{0.__class__.__name__}>".format(self)
    def __repr__(self):
        return self.__str__()
    def find(self, x):
        if self.par[x] == x:
            return x;
        else:
            self.par[x] = self.find(self.par[x])
            return self.par[x]
    def is_connected(self, x, y):
        return self.find(x) == self.find(y)
    def unite(self, x, y):
        x = self.par[x]
        y = self.par[y]
        if x == y:
            return
        rank = self.rank
        if rank[x] < rank[y]:
            self.par[x] = y
        else:
            self.par[y] = x
            if rank[x] == rank[y]:
                rank[x] += 1
