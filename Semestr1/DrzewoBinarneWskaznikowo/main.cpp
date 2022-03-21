#include <iostream>

using namespace std;

typedef int Telement;

struct Node
{
    Telement info;
    Node *left;
    Node *right;
};
typedef Node *PNode;

class BinaryTree
{
protected:
    PNode T;
    void MAKENULL(PNode p); //jak jest public i ktos to wywola to program sie wysypuje :c

public:
    BinaryTree();
    ~BinaryTree();
    PNode PARENT(PNode n);
    PNode PARENT1(PNode n, PNode T);
    PNode LEFT_CHILD(PNode n);
    PNode RIGHT_CHILD(PNode n);
    Telement GetLabel(PNode n);
    PNode BuildTree1(int n);
    void BuildTree(int n);
    PNode ROOT();
};

BinaryTree::BinaryTree()
{ //tworzy puste drzewo
    T = NULL;
}

BinaryTree::~BinaryTree()
{ //usuwa wszystkie węzły drzewa
    MAKENULL(T);
}

void BinaryTree::MAKENULL(PNode p)
{ //zwalnia pamięć zajętą przez poddrzewo o korzeniu p
    if (p != NULL)
    {
        if (p->left != NULL)
            MAKENULL(p->left);
        if (p->right != NULL)
            MAKENULL(p->right);
        delete p;
        p = NULL;
    }
}

PNode BinaryTree::ROOT()
{ //zwraca węzeł, który jest korzeniem lub NULL jeśli drzewo jest puste
    return T;
}

PNode BinaryTree::PARENT1(PNode n, PNode T)
{ //funkcja pomocnicza, szuka rodzica węzła w poddrzewie T
    if ((T->left == n) || (T->right == n))
        return T;
    PNode tmp1 = NULL;
    PNode tmp2 = NULL;
    if (T->left != NULL)
        tmp1 = PARENT1(n, T->left);
    if (T->right != NULL)
        tmp2 = PARENT1(n, T->right);
    return (tmp1 != NULL) ? tmp1 : tmp2;
}

PNode BinaryTree::PARENT(PNode n)
{ //zwraca rodzica węzła n w drzewie T. Jeśli n to korzeń to zwraca NULL
    if (n == T)
        return NULL;
    return PARENT1(n, T);
}

PNode BinaryTree::LEFT_CHILD(PNode n)
{ //zwraca lewe dziecko wezla n
    return n->left;
}

PNode BinaryTree::RIGHT_CHILD(PNode n)
{ //zwraca prawe dziecko wezla n
    return n->right;
}

Telement BinaryTree::GetLabel(PNode n)
{ //zwraca etykietę węzła n w T
    if (n != NULL)
        return n->info;
    else
    {
        cout << "Operacja niezdefiniowana!" << endl;
        exit(-1);
    }
}

PNode BinaryTree::BuildTree1(int n)
{ //buduje drzewo wyważone o n węzłach
    if (n == 0)
        return NULL;
    int nl, np;
    Telement x;
    PNode tmp;
    nl = n / 2;
    np = n - nl - 1;

    cout << "Podaj wartosc do wstawienia:";
    cin >> x;
    tmp = new Node;
    tmp->info = x;
    tmp->left = BuildTree1(nl);
    tmp->right = BuildTree1(np);
    return tmp;
}

void BinaryTree::BuildTree(int n)
{
    T = BuildTree1(n);
}

void PreOrder(PNode t)
{
    if (t != NULL)
    {
        cout << t->info;
        PreOrder(t->left);
        PreOrder(t->right);
    }
}

void InOrder(PNode t)
{
    if (t != NULL)
    {
        InOrder(t->left);
        cout << t->info;
        InOrder(t->right);
    }
}

void PostOrder(PNode t)
{
    if (t != NULL)
    {
        PostOrder(t->left);
        PostOrder(t->right);
        cout << t->info;
    }
}

int main()
{
    BinaryTree Tree;
    Tree.BuildTree(9);                                            //buduje drzewo o 9 wezlach
    cout << Tree.GetLabel(Tree.ROOT()) << endl;                   //zwracam etykiete wezla ktory jest korzeniem
    cout << Tree.GetLabel(Tree.LEFT_CHILD(Tree.ROOT())) << endl;  //zwracam lewe dziecko korzenia
    cout << Tree.GetLabel(Tree.RIGHT_CHILD(Tree.ROOT())) << endl; //zwracam prawe dziecko korzenia
    //wypisuje wartość węzła, który jest rodzicem węzła będącego prawym dzieckiem korzenia
    cout << Tree.GetLabel(Tree.PARENT(Tree.RIGHT_CHILD(Tree.ROOT()))) << endl;
    //Wypisuje wartość węzła, który jest rodzicem węzła będącego prawym dzieckiem lewego dziecka korzenia
    cout << Tree.GetLabel(Tree.PARENT(Tree.RIGHT_CHILD(Tree.LEFT_CHILD(Tree.ROOT())))) << endl;

    PreOrder(Tree.ROOT());
    cout << "\n";
    InOrder(Tree.ROOT());
    cout << "\n";
    PostOrder(Tree.ROOT());
    cout << "\n";
    //rodzic prawego dziecka prawego dziecka korzenia
    cout << Tree.GetLabel(Tree.PARENT(Tree.RIGHT_CHILD(Tree.RIGHT_CHILD(Tree.ROOT())))) << endl;
    return 0;
}
//wprowadzamy 1,2,3,4,5,6,7,8,9
//taka mamy miec kolejnosc
//preorder 1,2,3,4,5,6,7,8,9 - (porządek wzdłużny) – odwiedzamy korzeń przed poddrzewami
//inorder 4,3,2,5,1,8,7,6,9 - (porządek poprzeczny) – odwiedzamy lewe poddrzewo, korzeń, prawe poddrzewo
//postorder 4,3,5,2,8,7,9,6,1 - (porządek wsteczny) – odwiedzamy korzeń po poddrzewach 