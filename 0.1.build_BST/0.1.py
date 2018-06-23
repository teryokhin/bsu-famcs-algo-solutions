
class BinarySearchTree:

    class Node:
        def __init__(self, value):
            self.left = None
            self.right = None
            self.value = value

    def __init__(self):
        self.root = None

    def add(self, value):
        if self.root:
            self._add(value, self.root)
        else:
            self.root = self.Node(value)

    def _add(self, value, node):
        if value < node.value:
            if node.left:
                self._add(value, node.left)
            else:
                node.left = self.Node(value)
        if value > node.value:
            if node.right:
                self._add(value, node.right)
            else:
                node.right = self.Node(value)

    def preorder_left(self):
        return self._preorder_left(self.root)

    def _preorder_left(self, node):
        if node:
            result = str(node.value)+'\n'
            result += self._preorder_left(node.left)
            result += self._preorder_left(node.right)
            return result
        else:
            return ''


def main():
    bst = BinarySearchTree()
    for vertex in open('input.txt'):
        bst.add(int(vertex))
    open('output.txt', 'w').write(bst.preorder_left())


main()
