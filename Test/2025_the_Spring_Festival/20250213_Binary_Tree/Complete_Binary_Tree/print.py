"""
class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

class BinaryTree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        if self.root is None:
            self.root = Node(value)
        else:
            queue = [self.root]
            while queue:
                current = queue.pop(0)
                if current.left is None:
                    current.left = Node(value)
                    return
                elif current.right is None:
                    current.right = Node(value)
                    return
                queue.append(current.left)
                queue.append(current.right)

    def print_tree(self, node, level=0):
        if node is not None:
            self.print_tree(node.right, level + 1)
            print(' ' * (level * 4) + str(node.value))
            self.print_tree(node.left, level + 1)

# Example usage:
bt = BinaryTree()
# Inserting values to create a complete binary tree
values = [1, 2, 3, 4, 5, 6,7, 8, 9, 10, 11, 12]
for value in values:
    bt.insert(value)

# Printing the tree
bt.print_tree(bt.root)
"""

from graphviz import Digraph

class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

class BinaryTree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        if self.root is None:
            self.root = Node(value)
        else:
            queue = [self.root]
            while queue:
                current = queue.pop(0)
                if current.left is None:
                    current.left = Node(value)
                    return
                elif current.right is None:
                    current.right = Node(value)
                    return
                queue.append(current.left)
                queue.append(current.right)

    def generate_graph(self, node, graph=None):
        if graph is None:
            graph = Digraph('binary_tree')

        if node:
            if node.left:
                graph.node(str(node.left.value))
                graph.edge(str(node.value), str(node.left.value))
                self.generate_graph(node.left, graph)
            if node.right:
                graph.node(str(node.right.value))
                graph.edge(str(node.value), str(node.right.value))
                self.generate_graph(node.right, graph)

        return graph

    def render_tree(self):
        graph = self.generate_graph(self.root)
        graph.render('binary_tree', format='png', cleanup=True)
        print("Tree has been rendered as 'binary_tree.png'")

# Example usage:
bt = BinaryTree()
# Inserting values to create a complete binary tree
values = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
for value in values:
    bt.insert(value)

# Render the tree as an image
bt.render_tree()

