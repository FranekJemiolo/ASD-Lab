#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <new>

#define RED true
#define BLACK false

// Returns number of intervals stored in node.
long long getSum (long long f, long long l)
{
    return (((l - f + 1) * (l - f + 2)) / 2);
}

// This tree is a form of red-black tree with added sums of intervals in right,
// left node and also the sum of intervals inside a node.
class QueryTree
{
    private:

        struct Node
        {
            // The interval is identified by first and last number [first, last]
            long long first, last;
            // How many intervals are in this node.
            long long nodeSum;
            // How many intervals are in left subtree, right subtree.
            long long leftSum, rightSum;
            // Color of the node. True=red, False=black.
            bool color;
            Node *left, *right, *parent;
            // Constructor.
            Node (long long nfirst, long long nlast) : first (nfirst), 
                last (nlast), leftSum (0), rightSum (0), nodeSum (0) {}
        };

        
        

    public:
        // Represents the leaf node of red-black tree.
        Node *guard;
        Node *root;
        // Constructor
        QueryTree ()
        {
            guard = new Node (-1, -1);
            guard->left = guard;
            guard->right = guard;
            guard->parent = guard;
            guard->color = BLACK;
            root = guard;
        }

        // Returns the right interval of given number with O(logn).
        std::pair<long long, long long> getInterval (Node *nd, long long num)
        {
            assert (nd != nullptr);
            // The difference in interval.
            long long diff = nd->last - nd->first + 1;
            // How many intervals there are in this node.
            long long all = ((diff * (diff + 1))/2);
            // Variables used in binary search.
            long long l, r, s;
            long long i = 0;
            l = 0;
            r = diff;
            s = diff / 2;
            // The result will be in s.
            while ((l < r) && (l >= 0))
            {
                s = (l + r) / 2;
                if ((all - (((diff - s - 1)) * ((diff - s)) / 2)) > num)
                {
                    r = s;
                    if (all - (((diff - s)) * ((diff - s) + 1) / 2) <= num)
                        break;
                }
                else
                {
                    l = s+1;
                }
            }
            // Getting the difference between intervals.
            i = num - (all - (((diff - s) * ((diff - s) + 1)) / 2));
            assert (i >= 0);
            return std::make_pair<long long, long long> 
                ((nd->first + s), (nd->first + s + i));  

        }

        // Updates sums in a node.
        void updateNode (Node* nd)
        {
            if (nd != guard)
            {
                if (nd->left != guard)
                    nd->leftSum = nd->left->nodeSum + nd->left->leftSum + 
                        nd->left->rightSum;
                else
                    nd->leftSum = 0;

                if (nd->right != guard)
                    nd->rightSum = nd->right->nodeSum + nd->right->leftSum +
                        nd->right->rightSum;
                else
                    nd->rightSum = 0;
            }
        }   

        // Removes the value of nodesum in given nd in every node until end.
        void updateOnRemove (Node* nd, Node* end)
        {
            Node* help;
            long long val = nd->nodeSum;
            if (nd != end)
            {
                help = nd->parent;
                while (help != end)
                {
                    if (help->right == nd)
                        help->rightSum -= val;
                    else
                        help->leftSum -= val;
                    nd = nd->parent;
                    help = nd->parent;
                }
            }
        }

        // Returns minimal element from tree.
        Node* minTree (Node* nd)
        {
            if (nd != guard)
                while (nd->left != guard)
                    nd = nd->left;
            return nd;
        }

        // Successor.
        Node* successor (Node* nd)
        {
            Node* n;
            if (nd != guard)
            {
                if (nd->right != guard) 
                {
                    n = minTree (nd->right);
                    updateOnRemove (n, nd);
                    return n;
                }
                else
                {
                    n = nd->parent;
                    while ((n != guard) && (nd == n->right))
                    {
                        nd = n;
                        n = n->parent;
                    }
                    updateOnRemove (n, guard);
                    return n;
                }
            }
            return guard;
        }

        // Right rotation.
        void rotationR (Node *nd)
        {
            Node *leftnd, *parentnd;
            leftnd = nd->left;
            if (leftnd != guard)
            {
                parentnd = nd->parent;
                nd->left = leftnd->right;
                if (nd->left != guard)
                    nd->left->parent = nd;
                leftnd->right = nd;
                leftnd->parent = parentnd;
                nd->parent = leftnd;
                if (parentnd != guard)
                {
                    if (parentnd->left == nd)
                        parentnd->left = leftnd;
                    else
                        parentnd->right = leftnd;
                }
                else
                    root = leftnd;

                // Updating sums stored in nodes.
                updateNode (nd);
                updateNode (leftnd);
                updateNode (parentnd);
            }
        }

        // Left rotation.
        void rotationL (Node *nd)
        {
            Node *rightnd, *parentnd;
            rightnd =  nd->right;
            if (rightnd != guard)
            {
                parentnd = nd->parent;
                nd->right = rightnd->left;
                if (nd->right != guard)
                    nd->right->parent = nd;
                rightnd->left = nd;
                rightnd->parent = parentnd;
                nd->parent = rightnd;
                if (parentnd != guard)
                {
                    if (parentnd->left == nd)
                        parentnd->left = rightnd;
                    else
                        parentnd->right = rightnd;
                }
                else
                    root = rightnd;

                // Updating sums stored in nodes.
                updateNode (nd);
                updateNode (rightnd);
                updateNode (parentnd);
            }
        }

        // Inserting given interval into QueryTree.
        long long insert (long long f, long long l)
        {
            Node *inserted = new Node (f, l);
            Node *help;

            // Initialize new node. Leafs linked to guard.
            inserted->left = guard;
            inserted->right = guard;
            inserted->parent = root;
            inserted->nodeSum = getSum (f, l);
            inserted->rightSum = 0;
            inserted->leftSum = 0;


            if (inserted->parent == guard)
            {
                root = inserted;
            }
            else
            {
                // Finding the spot to insert wanted element.
                while (1)
                {
                    if (f < inserted->parent->first)
                    {
                        if (inserted->parent->left == guard)
                        {
                            inserted->parent->left = inserted;
                            updateNode (inserted->parent);
                            break;
                        }
                        inserted->parent->leftSum += getSum (f, l);
                        inserted->parent = inserted->parent->left;
                        
                    }
                    else
                    {
                        if (inserted->parent->right == guard)
                        {
                            inserted->parent->right = inserted;
                            updateNode (inserted->parent);
                            break;
                        }
                        inserted->parent->rightSum += getSum (f, l);
                        inserted->parent = inserted->parent->right;
                    }
                }
            }

            // Now coloring the node.
            inserted->color = RED;
            // Now we have to repair tree property.
            while ((inserted != root) && (inserted->parent->color == RED))
            {
                if (inserted->parent == inserted->parent->parent->left)
                {
                    help = inserted->parent->parent->right;
                    if (help-> color == BLACK)
                    {
                        if (inserted == inserted->parent->right)
                        {
                            inserted = inserted->parent;
                            rotationL (inserted);
                        }
                        inserted->parent->color = BLACK;
                        inserted->parent->parent->color = RED;
                        rotationR (inserted->parent->parent);
                        break;
                    }
                    else
                    {
                        inserted->parent->color = BLACK;
                        help->color = BLACK;
                        inserted->parent->parent->color = RED;
                        inserted = inserted->parent->parent;
                    }
                }
                else
                {
                    help = inserted->parent->parent->left;
                    if (help->color == BLACK)
                    {
                        if (inserted == inserted->parent->left)
                        {
                            inserted = inserted->parent;
                            rotationR (inserted);
                        }
                        inserted->parent->color = BLACK;
                        inserted->parent->parent->color = RED;
                        rotationL (inserted->parent->parent);
                        break;
                    }
                    else
                    {
                        inserted->parent->color = BLACK;
                        help->color = BLACK;
                        inserted->parent->parent->color = RED;
                        inserted = inserted->parent->parent;
                    }
                }
            }
            // Now coloring root.
            root->color = BLACK;
            return getSum (f, l);
        }

        // Removes given node from QueryTree.
        void remove (Node *nd)
        {
            // Nodes.
            Node *ndx, *ndy, *ndz;
            // Setting ndx.
            if ((nd->left == guard) || (nd->right == guard))
            {
                ndx = nd;
                updateOnRemove (nd, guard);
            }
            else
            {
                ndx = successor (nd);
                updateOnRemove (nd, guard);
            }

            // Setting ndy.
            if (ndx->left != guard)
                ndy = ndx->left;
            else
                ndy = ndx->right;
            ndy->parent = ndx->parent;

            if (ndx->parent != guard)
            {
                if (ndx == ndx->parent->left)
                    ndx->parent->left = ndy;
                else
                    ndx->parent->right = ndy;
            }
            else
            {
                root = ndy;
            }

            if (ndx != nd)
            {
                assert (ndx != guard);
                nd->first = ndx->first;
                nd->last = ndx->last;
                nd->nodeSum = ndx->nodeSum;
                updateNode (nd);
            }

            // We have to restore BR property only if removed is black.
            if (ndx->color != RED)
            {
                while ((ndy != root) && (ndy->color == BLACK))
                {
                    if (ndy == ndy->parent->right)
                    {
                        // Symetrical situation.
                        ndz = ndy->parent->left;
                        if (ndz->color != BLACK)
                        {
                            ndz->color = BLACK;
                            ndy->parent->color = RED;
                            rotationR (ndy->parent);
                            ndz = ndy->parent->left;
                        }

                        if ((ndz->left->color == RED) || 
                            (ndz->right->color == RED))
                        {
                            if (ndz->left->color != RED)
                            {
                                ndz->right->color = BLACK;
                                ndz->color = RED;
                                rotationL (ndz);
                                ndz = ndy->parent->left;
                            }
                            ndz->color = ndy->parent->color;
                            ndy->parent->color = BLACK;
                            ndz->left->color = BLACK;
                            rotationR (ndy->parent);
                            ndy = root;
                        }
                        else
                        {
                            ndz->color = RED;
                            ndy = ndy->parent;
                        }
                    }
                    else
                    {
                        // Symetrical situation.
                        ndz = ndy->parent->right;
                        if (ndz->color != BLACK)
                        {
                            ndz->color = BLACK;
                            ndy->parent->color = RED;
                            rotationL (ndy->parent);
                            ndz = ndy->parent->right;
                        }

                        assert (ndz->left != nullptr);
                        if ((ndz->left->color == RED) || 
                            (ndz->right->color == RED))
                        {
                            if (ndz->right->color != RED)
                            {
                                ndz->left->color = BLACK;
                                ndz->color = RED;
                                rotationR (ndz);
                                ndz = ndy->parent->right;
                            }
                            ndz->color = ndy->parent->color;
                            ndy->parent->color = BLACK;
                            ndz->right->color = BLACK;
                            rotationL (ndy->parent);
                            ndy = root;
                        }
                        else
                        {
                            ndz->color = RED;
                            ndy = ndy->parent;
                        }
                    }
                }
            }
            ndy->color = BLACK;
            delete ndx;

        }

        // Searches for the node which stores wanted interval.
        Node* findRecursive (Node *nd, long long& intervals, long long num)
        {
            if (nd != nullptr)
            {
                if ((num >= nd->leftSum + intervals) && 
                    (num < nd->leftSum + nd->nodeSum + intervals))
                // Right node of interval.
                {
                    intervals += nd->leftSum;
                    return nd;   
                }
                else if (num < nd->leftSum+intervals)
                {
                    return findRecursive (nd->left, intervals, num);
                }
                else
                {
                    // Adding nodes sum and his whole left subtree.
                    intervals += (nd->leftSum + nd->nodeSum);
                    return findRecursive (nd->right, intervals, num);
                }
            }
            else
            {
                return nd;
            } 
        }

        // Searches for the given interval and removes it from the QueryTree
        // and then inserts what is left of the nodes interval.
        std::pair<long long, long long> findInterval (long long num)
        {
            long long intervals = 0;
            std::pair<long long, long long> p;
            Node* result = findRecursive (root, intervals, num);
            if (result != guard)
            {
                p = getInterval (result, num - intervals);
                long long f = result->first, l = result->last;
                remove (result);
                if (f < p.first)
                {
                    insert (f, p.first - 1);
                }
                if (l > p.second)
                {
                    insert (p.second + 1, l);
                }

                return p;
            }
            else
            {
                // No such interval!
                return std::make_pair<long long, long long> (-1, -1);
            }
        }

};

int main ()
{
    // Main function of the program...
    // Plain simple, return wanted interval and then remove it.
    QueryTree qt;
    long long x, all;
    long long y, z;
    scanf ("%lld", &x);
    // Have to insert to tree interval from 1 to x.
    all = getSum (1, x);
    qt.insert (1, x);
    printf ("%lld\n", qt.root->nodeSum + qt.root->leftSum + qt.root->rightSum);
    bool end = false;
    while (!end)
    {
         // Read query.
        scanf ("%lld", &x);
        // Answer query.
        if ((x >= 0) && (x < all))
        {
            std::pair <long long, long long> p = qt.findInterval (x);
            printf ("%lld %lld\n", p.first, p.second);
            if (qt.root != qt.guard)
            {
                printf ("%lld\n", qt.root->nodeSum + qt.root->leftSum + 
                    qt.root->rightSum);
            }
            else
            {
                printf ("0\n");
            }
        }
        else if (x == -1)
        {
            end = true;
        }
        else
        {
            printf ("Undefined behaviour\n");
        }
    }
    return 0;
}