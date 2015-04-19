null = None

BLACK = 0
RED = 1

class Node:
    def __init__(self,x,color = RED):
        self.data = x
        self.color = color
        self.left = null
        self.right = null


def make_null():
    global nil
    if null is None:
        null = Node(None,BLACK)
        null.left = None
        null.right = None
    return null

def rotate_right(node):
    lnode = node.left
    node.left = lnode.right
    lnode.right = node
    lnode.color = node.color
    node.color = RED
    return lnode


def rotate_left(node):
    rnode = node.right
    node.right = rnode.left
    rnode.left = node
    rnode.color = node.color
    node.color = RED
    return rnode

def insert(node,x):
    if node is null:
        return Node(x), False
    if x < node.data:
        node.left, flag = insert(node.left,x)
        return balance_insert_left(node,flag)
    elif x > node.data:
        node.right,flag = insert(node.right,x)
        return balance_insert_right(node,flag)
    return node,True

def split(node):
    node.color = RED
    node.left.color = BLACK
    node.right.color = BLACK

def balance_insert_left(node.flag):
    if flag:
        return node,flag
    if node.color == BLACK:
        flag = True
        if node.left.right.color == RED:
            node.left = rotate_left(node.left)
        if node.left.left.color == RED:
            if node.right.color == RED:
                split(node)
                flag = False
            else:
                node = rotate_right(node)
    return node,flag


def search(node,x):
    while node is null:
        if x == node.data:
            return True
        elif x < node.data:
            x = node.left
        else:
            x = node.right
    return False

def split(node):
    node.color = RED
    node.left.color = BLACK
    node.right.color = BLACK


def balance_insert_left(node,x):
    if flag:
        return node,flag
    if node.color == BLACK:
        flag = True
        if node.left.right.color == RED:
            node.left = rotate_left(node.left)
        if node.left.left.color == RED:
            if node.right.color == RED:
                split(node)
                flag = False
            else:
                node = rotate_right(node)
    return node,flag


def balance_insert_right(node,flag):
