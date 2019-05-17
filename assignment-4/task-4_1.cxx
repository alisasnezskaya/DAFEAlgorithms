/****************************************************************************
Задача № 4. Динамика на дереве (6 баллов)

Дано невзвешенное дерево. Расстоянием между двумя вершинами будем
называть количество ребер в пути, соединяющем эти две вершины.

****************************************************************************/

/****************************************************************************

Самая удаленная вершина.

Для каждой вершины определите расстояние до самой удаленной от нее
вершины. Время работы должно быть O(n).

*Формат входных данных:*

В первой строке записано количество вершин n ≤ 10000. Затем следует n --
1 строка, описывающая ребра дерева. Каждое ребро -- это два различных
целых числа -- индексы вершин в диапазоне [0, n-1]. Индекс корня -- 0.
В каждом ребре родительской вершиной является та, чей номер меньше.

*Формат выходных данных:*

Выход должен содержать n строк. В i-ой строке выводится расстояние от
i-ой вершины до самой удаленной от нее.

+-----+-----+
| in  | out |
+-----+-----+
| 3   | 2   |
| 0 1 | 1   |
| 1 2 | 2   |
+-----+-----+

****************************************************************************/

#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

struct node {
    vector<int> branch;
    int distance = 0;
    int height = 0;
    int heavy_road = -1;
    int less_road = -1;
    
    node () {}
    ~node () {}
};

class tree_class {
public:
    tree_class (int n) {
        tree_node.resize(n);
    }
    ~tree_class () {}
    
    void add_edge (int, int);
    void dfs_set_h (int);
    void dfs_set_dist (int, int);
    void set_max_height (int);
    
    void distances ();
    void print_tree (int, int);
private:
    vector<node> tree_node;
};

void tree_class::add_edge (int dep, int des) {
    if (dep > des)
        swap (dep, des);
    tree_node[dep].branch.push_back(des);
}

void tree_class::dfs_set_h (int cur) {      //  fill height for elements
    for (int i = 0; i < tree_node[cur].branch.size(); i++) {
        dfs_set_h (tree_node[cur].branch[i]);
    }
    set_max_height (cur);
}

void tree_class::dfs_set_dist (int cur, int add_dist) {     //  fill distance for elements using prev dist and height
    tree_node[cur].distance = max (add_dist, tree_node[cur].height);
    for (int i = 0; i < tree_node[cur].branch.size(); i++) {
        if (i == tree_node[cur].heavy_road)
            if (tree_node[cur].less_road != -1)
                dfs_set_dist (tree_node[cur].branch[i], max (add_dist + 1, tree_node[ tree_node[cur].branch[tree_node[cur].less_road] ].height + 2));
            else
                dfs_set_dist (tree_node[cur].branch[i], add_dist + 1);
        else
            dfs_set_dist (tree_node[cur].branch[i], max (add_dist + 1, tree_node[ tree_node[cur].branch[tree_node[cur].heavy_road] ].height + 2));
    }
}

void tree_class::set_max_height (int cur) {     //  compare childrens' heights
    if (tree_node[cur].branch.empty())
        return;
    int max_height = 0;
    tree_node[cur].heavy_road = -1;
    
    for (int i = 0; i != tree_node[cur].branch.size(); i++) {
        int h = tree_node[ tree_node[cur].branch[i] ].height + 1;
        if (max_height <  h) {
            tree_node[cur].less_road = tree_node[cur].heavy_road;
            max_height = h;
            tree_node[cur].heavy_road = i;
        } else if (tree_node[cur].less_road == -1 || tree_node[ tree_node[cur].branch[tree_node[cur].less_road] ].height + 1 < h) {
            tree_node[cur].less_road = i;
        }
    }
    tree_node[cur].height = max_height;
}

void tree_class::distances () {     //  return answer
    for (int i = 0; i < tree_node.size(); i++) {
        cout << tree_node[i].distance << endl;
    }
}

int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
    
    tree_class tree(n);
    for (int i = 0; i < n-1; i++) {
        int dep = 0;
        int des = 0;
        cin >> dep;
        cin >> des;
        tree.add_edge (dep, des);
    }
    tree.dfs_set_h (0);
    tree.dfs_set_dist (0, 0);
    tree.distances ();
    return 0;
}
