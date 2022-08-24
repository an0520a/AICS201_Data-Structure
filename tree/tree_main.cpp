#include <iostream>
#include "tree.hpp"
#include "tree.cpp"

int main()
{
    Tree<char> tree;
    tree.createRoot('H');
    Tree<char>::Position root = tree.getRoot();
    tree.createChild(root, 'E');
    Tree<char>::Position root_chi0 = root.getChild(0);
    tree.createChild(root_chi0, 'L');
    tree.createChild(root_chi0, 'L');
    tree.createChild(root_chi0, 'O');

    tree.createChild(root, ',');
    Tree<char>::Position root_chi1 = root.getChild(1);
    tree.createChild(root_chi1, ' ');

    tree.createChild(root, 'W');
    Tree<char>::Position root_chi2 = root.getChild(2);
    tree.createChild(root_chi2, 'O');
    tree.createChild(root_chi2, 'R');
    tree.createChild(root_chi2, 'L');
    tree.createChild(root_chi2, 'D');
    tree.createChild(root_chi2, '!');

    Vector<Tree<char>::Position> vec;

    tree.preorder(root, vec);

    for (int i = 0; i < vec.size(); i++)
        std::cout << *vec[i] << std::endl;
}