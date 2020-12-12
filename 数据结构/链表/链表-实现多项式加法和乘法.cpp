#include<bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 10;


struct node
{
    int coef;
    int exp;
    node *link;
    node():link(NULL){}
    node(int i, int j):coef(i), exp(j), link(NULL){}
};

class List
{
    node *first;
public:
    List(){first = new node;}
    List(const List & a)
    {
        first = new node;
        node *p = a.first->link;
        while (p)
        {
            this->insert(p->coef, p->exp);
            p = p->link;
        }
    }
    ~List()
    {
        node *p = first;
        while (p)
        {
            node *q = p->link;
            delete p;
            p = q;
        }
    }
    void clear()
    {
        node *p = first->link;
        while (p)
        {
            node *q = p->link;
            delete p;
            p = q;
        }
        first->link = NULL;
    }
    pair<bool, pair<int, int> > find(int e)
    {
        node *p = first->link;
        while (p)
        {
            if (p->exp == e) return make_pair(true, make_pair(p->coef, p->exp));
            p = p->link;
        }
        return make_pair(false, make_pair(0, 0));
    }
    void insert(int c, int e)
    {
        node *p = first->link;
        node *q = first;
        while (p)
        {
            q = p;
            p = p->link;
        }
        p = new node(c, e);
        q->link = p;
    }
    bool del(int e)
    {
        node *p = first->link;
        node *q = first;
        while (p) 
        {
            if (p->exp == e) break;
            q = p;
            p = p->link;
        }
        if (!p) return false;
        q->link = p->link;
        delete p;
        return true;
    }
    bool output()
    {
        node *p = first->link;
        while (p)
        {
            if (p->coef == 1 && p->exp == 1) 
            {
                if (p == first->link) printf("x");
                else printf("+x");
            }
            else if (p->coef != 1 && p ->exp == 1)
            {
                if (p == first->link) printf("%dx", p->coef);
                else printf("%+dx", p->coef);
            }
            else if (p->coef == 1 && p->exp != 1)
            {
                if (p == first->link) printf("x^%d", p->exp);
                else printf("+x^%d", p->exp);
            }
            else
            {
                if (p == first->link) printf("%dx^%d", p->coef, p->exp);
                else printf("%+dx^%d", p->coef, p->exp);
            }
            p = p->link;
        }
        printf("\n");
        return true;
    }
    bool update(int c, int e)
    {
        node *p = first->link;
        while (p)
        {
            if (p->exp == e) 
            {
                p->coef += c;
                return true;
            }
            p = p->link;
        }
        return false;
    }
    List & operator = (const List & a)
    {
        this->clear();
        node *p = a.first->link;
        while (p)
        {
            this->insert(p->coef, p->exp);
            p = p->link;
        }
        return *this;
    }
    List operator + (const List & a)
    {
        List t;
        node *p = this->first->link;
        while (p)
        {
            t.insert(p->coef, p->exp);
            p = p->link;
        }
        p = a.first->link;
        while (p)
        {
            if (!t.update(p->coef, p->exp)) t.insert(p->coef, p->exp);
            p = p->link;
        }
        return t;
    }
    List operator * (const List & a)
    {
        List t;
        node *p = this->first->link;
        while (p)
        {
            node *q = a.first->link;
            while (q)
            {
                if (!t.update(p->coef*q->coef, p->exp+q->exp)) t.insert(p->coef*q->coef, p->exp+q->exp);
                q = q->link;
            }
            p = p->link;
        }
        return t;
    }
    List operator ^ (int n)
    {
        List t;
        t.insert(1, 0);
        while (n--) {t = t * *this;}
        return t;
    }
    
} L1, L2, L3;

int main()
{   
    L1.insert(-4, 5);
    L1.insert(-3, 3);
    L1.insert(1, 2);
    L1.insert(2, 1);
    printf("L1 = ");
    L1.output();
    printf("\n");
    L1.del(5);
    printf("L1 = ");
    L1.output();
    printf("\n");
    L2.insert(2, 1);
    printf("L2 = ");
    L2.output();
    printf("\n");
    L3 = L1 + L2;
    printf("L3 = L1 + L2 = ");
    L3.output();
    printf("\n");
    L3 = L1 * L2;
    printf("L3 = L1 * L2 = ");
    L3.output();
    printf("\n");
    printf("L3 = L1 ^ 5 = ");
    L3 = L1 ^ 5;
    L3.output();
    printf("\n");
    return 0;
}
