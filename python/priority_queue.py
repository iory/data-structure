#!/usr/bin/env python
# -*- coding:utf-8 -*-

import heapq
class priority_queue(object):
    def __init__(self, init_list=None):
        if init_list:
            self.quque = init_list
            heapq.heapify(self.queue)
        else:
            self.queue = []
        self.index = 0
        self.size = len(self.queue)
    def push(self, item, priority):
        heapq.heappush(self.queue, (-priority, self.index, item))
        self.index += 1
    def pop(self):
        self.index -= 1
        return heapq.heappop(self.queue)
    def top(self):
        return self.queue[0]
    def __str__(self):
        return "#<{0.__class__.__name__} size={0.index} elements={0.queue}>".format(self)
    def __repr__(self):
        return self.__str__()
    def empty(self):
        if self.index:
            return False
        else:
            return True


class Item(object):
    def __init__(self, name):
        self.name = name
    def __str__(self):
        return "#<{0.__class__.__name__} name={0.name}>".format(self)
    def __repr__(self):
        return self.__str__()

def _heap_test():
    q = priority_queue()
    q.push(Item('foo'), 1)
    q.push(Item('bar'), 5)
    q.push(Item('spam'), 4)
    print(q)
    print(q.pop())
    print(q)
    print(q.pop())
    print(q.pop())

if __name__ == "__main__":
    _heap_test()
