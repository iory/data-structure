#!/usr/bin/env python
# -*- coding:utf-8 -*-

class SegmentTree(object):
    INF = float('inf')
    def __init__(self, n):
        self.n = 1
        while self.n < n:
            self.n <<= 1
        self.data = [SegmentTree.INF for i in range(self.n)]
    def update(self, k, value):
        k += self.n - 1
        self.data[k] = value
        while k > 0:
            k = (k-1)/2
            self.data[k] = min(self.data[k*2+1], self.data[k*2+2])
    def query(self, a, b):
        return self.query_(a, b, 0, 0, self.n)
    def query_(self, a, b, k, l, r):
        if r <= a or b <= l:
            return SegmentTree.INF
        if a <= l and r <= b:
            return self.data[k]
        mid = (l+r)/2
        vl = self.query_(a, b, k*2+1, l, mid)
        vr = self.query_(a, b, k*2+2, mid, r)
        return min(vl, vr)
    def __str__(self):
        return "#<{0.__class__.__name__}>".format(self)
    def __repr__(self):
        return self.__str__()

def main():
    print("hello python!")

if __name__ == "__main__":
    main()
