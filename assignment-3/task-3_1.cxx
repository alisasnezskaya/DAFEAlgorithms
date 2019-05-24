/****************************************************************************
Задача 3_1. Солдаты. Использование АВЛ-дерева

В одной военной части решили построить в одну шеренгу по росту. Т.к. часть
была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и
вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако
солдаты в процессе прихода и ухода должны были всегда быть выстроены по
росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат
отвечал прапорщик, который заметил интересную особенность – все солдаты в
части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику
правильно расставлять солдат, а именно для каждого приходящего солдата
указывать, перед каким солдатом в строе он должен становится. Требуемая
скорость выполнения команды - O(log n).

*Формат входных данных.*

Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000). В каждой
следующей строке содержится описание команды: число 1 и X если солдат приходит
в строй (X – рост солдата, натуральное число до 100 000 включительно) и число
2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя. Солдаты
в строе нумеруются с нуля.

*Формат выходных данных.*

На каждую команду 1 (добавление в строй) вы должны выводить число K – номер
позиции, на которую должен встать этот солдат (все стоящие за ним двигаются
назад).

  in    | out
  ----- | ---
  5     | 0
  1 100 | 0
  1 200 | 2
  1 50  | 1
  2 1   |
  1 150 |

****************************************************************************/

 

#include <iostream>

#define u       unsigned

using namespace std;


template<typename T>
struct Node {
    T key;
    short height;
    u long childs;
    
    Node* left, * right;
    
    Node(T key) {
        this->key = key;
        this->height = 0;
        this->childs = 0;
        
        this->left = nullptr;
        this->right = nullptr;
    }
};

template<typename T>
class Tree {
    bool (*less)(T, T);
    
    Node<T>* root;
    
public:
    Tree(bool (*less)(T, T)) {
        this->root = nullptr;
        
        this->less = less;
    }
    
    Tree(Node<T>*& root, bool (*less)(T, T)) {
        this->root = root;
    }
    
    Node<T>* getRoot() {
        return root;
    }
    
    void add(T key) {
        root = insert(root, key);
    }
    
    void del(T key) {
        root = remove(root, key);
    }
    
    u long index(T key) {
        return indexOf(key, root, 0);
    }
    
    T keyAt(u long index) {
        return findKeyAt(index, root, 0);
    }
    
private:
    short height(Node<T>* node);
    int balanceFactor(Node<T>* node);
    u long childs(Node<T>* node);
    
    void fixHeight(Node<T>* node);
    void fixChilds(Node<T>* node);
    void fixAll(Node<T>* node);
    
    Node<T>* rotateLeft(Node<T>*& node);
    Node<T>* rotateRight(Node<T>*& node);
    Node<T>* balance(Node<T>*& node);
    
    Node<T>* insert(Node<T>*& node, T key);
    
    Node<T>* findMin(Node<T>* node);
    Node<T>* removeMin(Node<T>* node);
    Node<T>* remove(Node<T>*& node, T key);
    
    u long indexOf(T key, Node<T>* node, u long currentIndex);
    T findKeyAt(u long index, Node<T>* node, u long currentIndex);
};

template<typename T>
short Tree<T>::height(Node<T>* node) {
    return node != nullptr ? node->height : 0;
}

template<typename T>
int Tree<T>::balanceFactor(Node<T>* node) {
    return int(height(node->left) - height(node->right));
}

template<typename T>
u long Tree<T>::childs(Node<T>* node) {
    return node != nullptr ? node->childs : 0;
}

template<typename T>
void Tree<T>::fixHeight(Node<T>* node) {
    auto hl = height(node->left);
    auto hr = height(node->right);
    
    node->height = (hl > hr ? hl : hr) + 1;
}

template<typename T>
void Tree<T>::fixChilds(Node<T>* node) {
    node->childs = 0;
    
    if (node->left != nullptr) {
        node->childs += childs(node->left) + 1;
    }
    
    if (node->right != nullptr) {
        node->childs += childs(node->right) + 1;
    }
}

template<typename T>
void Tree<T>::fixAll(Node<T>* node) {
    fixHeight(node);
    fixChilds(node);
}

template<typename T>
Node<T>* Tree<T>::rotateLeft(Node<T>*& node) {
    auto tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    
    fixAll(node);
    fixAll(tmp);
    
    return tmp;
}

template<typename T>
Node<T>* Tree<T>::rotateRight(Node<T>*& node) {
    auto tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    
    fixAll(node);
    fixAll(tmp);
    
    return tmp;
}

template<typename T>
Node<T>* Tree<T>::balance(Node<T>*& node) {
    fixAll(node);
    
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    } else if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    
    return node;
}

template<typename T>
Node<T>* Tree<T>::insert(Node<T>*& node, T key) {
    if (node == nullptr) {
        return new Node<T>(key);
    }
    
    ++node->childs;
    
    if (less(key, node->key)) {
        node->left = insert(node->left, key);
    } else {
        node->right = insert(node->right, key);
    }
    
    return balance(node);
}

template<typename T>
Node<T>* Tree<T>::findMin(Node<T>* node) {
    return node->left == nullptr ? node : findMin(node->left);
}

template<typename T>
Node<T>* Tree<T>::removeMin(Node<T>* node) {
    if (node->left == nullptr) {
        return node->right;
    }
    
    node->left = removeMin(node->left);
    
    return balance(node);
}

template<typename T>
Node<T>* Tree<T>::remove(Node<T>*& node, T key) {
    if (node == nullptr) {
        return nullptr;
    }
    
    if (less(key, node->key)) {
        --node->childs;
        
        node->left = remove(node->left, key);
    } else if (key != node->key) {
        --node->childs;
        
        node->right = remove(node->right, key);
    } else {
        auto left = node->left;
        auto right = node->right;
        
        delete node;
        
        if (right == nullptr) {
            return left;
        } else {
            auto min = findMin(right);
            
            min->right = removeMin(right);
            min->left = left;
            
            return balance(min);
        }
    }
    
    return balance(node);
}

template<typename T>
u long Tree<T>::indexOf(T key, Node<T>* node, u long currentIndex) {
    if (node == nullptr) {
        return 0;
    }
    
    u long leftNodeIndex = node->left != nullptr ? (childs(node->left) + 1) : 0;
    
    if (node->key == key) {
        return currentIndex + leftNodeIndex;
        
    } else if (less(key, node->key)) {
        return indexOf(key, node->left, currentIndex);
    } else {
        return indexOf(key, node->right, currentIndex + leftNodeIndex + 1);
    }
}

template<typename T>
T Tree<T>::findKeyAt(u long index, Node<T>* node, u long currentIndex) {
    if (node == nullptr) {
        return 0;
    }
    
    u long nodeIndex = currentIndex + (node->left != nullptr ? (childs(node->left) + 1) : 0);
    
    if (nodeIndex == index) {
        return node->key;
    }
    
    if (index < nodeIndex) {
        return findKeyAt(index, node->left, currentIndex);
    } else {
        return findKeyAt(index, node->right, nodeIndex + 1);
    }
}

template<typename T>
bool myLess(T lhs, T rhs) {
    return lhs > rhs;
}

int main() {
    u long N;

    cin >> N;
    
    Tree<u long> tree(myLess);
    
    for (u long i = 0; i < N; ++i) {
        short command;
        
        cin >> command;
        
        if (command == 1) {
            u long height;
            
            cin >> height;
            
            tree.add(height);
        
            cout << tree.index(height) << "\n";
        } else if (command == 2) {
            u long index;
            
            cin >> index;
            
            tree.del(tree.keyAt(index));
        }
    }
}
