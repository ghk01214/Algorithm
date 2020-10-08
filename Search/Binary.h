#include <iostream>

template <typename T>
class Tree;

template <typename T>
class TreeNode
{
    friend class Tree<T>;
private:
    T data;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(T data = 0, TreeNode* left = NULL, TreeNode* right = NULL)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
    friend std::ostream& operator<<(std::ostream& os, const TreeNode<T>& node)
    {
        os << "데이터 : " << node.data << std::endl;
        if (node.left != NULL) {
            os << "왼쪽 : " << node.left->data << std::endl;
        }
        if (node.right != NULL) {
            os << "오른쪽 : " << node.right->data << std::endl;
        }
        return os;
    }
};

template <typename T>
class Tree
{
private:
    TreeNode<T>* root;
public:
    Tree(T data = 0)
    {
        root = new TreeNode<T>(data);
    }
    void buildSearchTree()
    {
        insertNode(new TreeNode<int>(3));
        insertNode(new TreeNode<int>(10));
        insertNode(new TreeNode<int>(14));
        insertNode(new TreeNode<int>(2));
        insertNode(new TreeNode<int>(5));
        insertNode(new TreeNode<int>(11));
        insertNode(new TreeNode<int>(16));
    }
    void insertNode(TreeNode<T>* node)
    {
        if (search(root, node->data) == NULL)
        {
            TreeNode<T>* parent = NULL;
            TreeNode<T>* current = root;

            while (current != NULL)
            {
                parent = current;
                if (node->data < parent->data)
                    current = current->left;
                else
                    current = current->right;
            }

            if (node->data < parent->data)
                parent->left = node;
            else
                parent->right = node;

            std::cout << "삽입 완료 " << node->data << std::endl;
        }
    }
    TreeNode<T>* getRoot() { return root; }
    void preorder(TreeNode<T>* current)
    {
        if (current != NULL)
        {
            visit(current);
            preorder(current->left);
            preorder(current->right);
        }
    }
    void visit(TreeNode<T>* current)
    {
        std::cout << current->data << " ";
    }
    TreeNode<T>* search(TreeNode<T>* current, T data)
    {
        if (current == NULL)
            return NULL;

        if (data == current->data)
            return current;
        else if (data < current->data)
            search(current->left, data);
        else
            search(current->right, data);
    }
};

void operate()
{
    Tree<int> tree(8);
    tree.buildSearchTree();

    std::cout << "전위 순회 >> ";
    tree.preorder(tree.getRoot());
    std::cout << std::endl;

    tree.insertNode(new TreeNode<int>(4));
    std::cout << "전위 순회 >> ";

    tree.preorder(tree.getRoot());
    std::cout << std::endl;

    int number;

    std::cout << "찾을 번호를 입력 : ";
    std::cin >> number;

    TreeNode<int>* found = tree.search(tree.getRoot(), number);

    if (found != NULL)
    {
        std::cout << "노드 발견." << std::endl;
        std::cout << *found;
    }
    else
    {
        std::cout << "노드 없음." << std::endl;
    }
}