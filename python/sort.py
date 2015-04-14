#!/usr/bin/env python
# -*- coding:utf-8 -*-

import random
import heapq

def bubble_sort(v):
    N = len(v)
    for i in range(N):
        for j in range(i+1, N):
            if v[i] > v[j]:
                v[i], v[j] = v[j], v[i]
    return v

def insertion_sort(v):
    N = len(v)
    for i in range(1, N):
        tmp = v[i]
        if v[i-1] > tmp:
            j = i
            v[j] = v[j-1]
            j -= 1
            while j > 0 and v[j-1] > tmp:
                v[j] = v[j-1]
                j -= 1
            v[j] = tmp
    return v

def merge_sort(v):
    N = len(v)
    if N <= 1:
        return v
    mid = N/2
    left = v[:mid]
    right= v[mid:]

    left = merge_sort(left)
    right= merge_sort(right)
    return list(heapq.merge(left, right))

def heap_sort(v):
    ret = []
    for value in v:
        heapq.heappush(ret, value)
    return [heapq.heappop(ret) for i in range(len(ret))]

def quick_sort(v):
    N = len(v)
    if N < 1:
        return v
    p = random.randrange(0, N)
    pivot = v[p]
    left = []
    right= []

    for i in range(N):
        if i==p:
            continue
        if v[i] <= pivot:
            left.append(v[i])
        else:
            right.append(v[i])
    left = quick_sort(left)
    right= quick_sort(right)
    return left + [pivot] + right

def main():
    sorts_func = {'bubble sort':bubble_sort,
                  'insertion sort':insertion_sort,
                  'heap sort':heap_sort,
                  'quick sort':quick_sort,
                  'merge sort':merge_sort}
    v = [i for i in range(20)]
    print("generated random array")
    random.shuffle(v)
    print(v)

    for sort_name, sortf in sorts_func.items():
        print(sort_name)
        random.shuffle(v)
        v = sortf(v)
        print(v)

if __name__ == "__main__":
    main()
