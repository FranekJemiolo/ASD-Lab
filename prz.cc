#include <cstdio>
#include <iostream>
#include <algorithm>
#include <new>
#include <cmath>
#include <cassert>
// Returns how many intervals are in node.
long long getSize (long long f, long long l)
{
    return (((l-f+2)*(l-f+1))/2);
};

struct Node
{
    // First and last of given interval.
    long long first, last; 
    // Right subtree sum and left subtree sum.
    long long rightSum, leftSum;
    // My node sum.
    long long nodeSum;
    // Left and right son and parent.
    Node* parent;
    Node* left;
    Node* right;
    // Balance factor.
    long long bf;
    
    Node (long long x, long long y) : first (x), last (y), rightSum (0), leftSum (0), bf (0) 
    {
        nodeSum = (getSize (x, y));
        left = NULL;
        right = NULL; 
        parent = NULL;
    }
};

struct Tree
{
    Node* root;
    Tree ()
    {
        root = NULL;
    }
    
    
    // Returns the right interval at given number with O(logn).
    std::pair<long long, long long> getInterval (Node* n, long long num)
    {
        assert (n != NULL);
        // The difference in interval.
        long long diff = n->last - n->first + 1;
        long long all = ((diff * (diff + 1))/2);
        long long i = 0;
        long long s = diff / 2;
        long long l = 0;
        long long p = diff;
        
        //printf ("All to : %lld a num to %lld\n", all, num);
        while ((l < p)&& (l >= 0))
        {
            //getchar ();
            s = (l + p)/2;
            //printf ("%lld\n", s);
            if (all - (((diff-s-1))*((diff-s))/2) > num)
            {
                p = s;
                if (all - (((diff-s))*((diff-s)+1)/2) <= num)
                    break;
            }
            else
            {
                l = s+1;
            }
        }
        //printf ("%lld %lld %lld\n", l, p, s);
        /*while ((i + diff <= num)&& (diff > 0))
        {
            i += diff;
            diff--;
        }*/
        //printf ("Rozznica %lld\n", ((diff-s)*((diff-s)+1)/2));
        i = num - (all - ((diff-s)*((diff-s)+1))/2);
        assert (i >= 0);
        return std::make_pair<long long, long long> ((n->first + s), (n->first + s + i));  
    }
    
    // Right 1-rotation.
    void rotationRR (Node* n)
    {
        assert (n != NULL);
        Node* npar;
        Node* nright;
        // Now rotating.
        nright = n->right;
        npar = n->parent;
        assert (nright != NULL);
        n->right = nright->left;
        if (n->right != NULL)
            n->right->parent = n;
        nright->left = n;
        nright->parent = npar;
        n->parent = nright;
        if (npar != NULL)
        {
            if (npar->left == n)
                npar->left = nright;
            else
                npar->right = nright;
        }
        else
        {
            root = nright;
        }
        
        // Update balance factor.
        if (nright->bf == -1)
        {
            n->bf = 0;
            nright->bf = 0;
        }
        else
        {
            n->bf = -1;
            nright->bf = 1;
        }
        
        // Update nodes count. (how many subintervals)
        if (nright->right != NULL)
        {
            nright->rightSum = nright->right->nodeSum + nright->right->leftSum + nright->right->rightSum;
        }
        else
        {
            nright->rightSum = 0;
        }
        
        if (n->left != NULL)
        {
            n->leftSum = n->left->nodeSum + n->left->leftSum + n->left->rightSum;
        }
        else
        {
            n->leftSum = 0;
        }
        
        if (n->right != NULL)
        {
            n->rightSum = n->right->nodeSum + n->right->leftSum + n->right->rightSum;
        }
        else
        {
            n->rightSum = 0;
        }
        
        // We know that nright and n aren't NULL for sure.
        nright->leftSum = n->nodeSum + n->leftSum + n->rightSum;
        
    }
    
    // Left 1-rotation.
    void rotationLL (Node* n)
    {
        assert (n != NULL);
        Node* npar;
        Node* nleft;
        // Now rotating.
        assert (n->left != NULL);
        nleft = n->left;
        npar = n->parent;
        n->left = nleft->right;
        if (n->left != NULL)
            n->left->parent = n;
        nleft->right = n;
        nleft->parent = npar;
        n->parent = nleft;
        if (npar != NULL)
        {
            if (npar->left == n)
                npar->left = nleft;
            else
                npar->right = nleft;
        }
        else
        {
            root = nleft;
        }
        
        // Update balance factor.
        if (nleft->bf == 1)
        {
            n->bf = 0;
            nleft->bf = 0;
        }
        else
        {
            n->bf = 1;
            nleft->bf = -1;
        }
        
        // Update interval count.
        if (nleft->left != NULL)
        {
            nleft->leftSum = nleft->left->nodeSum + nleft->left->leftSum + nleft->left->rightSum;
        }
        else
        {
            nleft->leftSum = 0;
        }
        if (n->right != NULL)
        {
            n->rightSum = n->right->nodeSum + n->right->leftSum + n->right->rightSum;
        }
        else
        {
            n->rightSum = 0;
        }
        if (n->left != NULL)
        {
            n->leftSum = n->left->nodeSum + n->left->leftSum + n->left->rightSum;
        }
        else
        {
            n->leftSum = 0;
        }
        // Both nleft and n cannot be NULL.
        nleft->rightSum = nleft->right->nodeSum + nleft->right->leftSum + nleft->right->rightSum;
        
    }
    
    // 2 rotations.
    
    /*void rotationRL (Node* n)
    {
        rotationLL (n->right);
        rotationRR (n);
    }*/
    
    /*void rotationLR (Node* n)
    {
        rotationRR (n->left);
        rotationLL (n);
    }*/
    
    
    void rotationRL (Node* n)
    {
        Node* mid;
        Node* low;
        Node* par;
        assert (n != NULL);
        mid = n->right;
        low = mid->left;
        par = n->parent;
        assert (mid != NULL);
        assert (low != NULL);
        mid->left = low->right;
        if (mid->left != NULL)
        {
            mid->left->parent = mid;
        }
        n->right = low->left;
        if (n->right !=  NULL)
        {
            n->right->parent = n;
        }
        low->left = n;
        low->right = mid;
        n->parent = low;
        mid->parent = low;
        low->parent = par;
        if (par != NULL)
        {
            if (par->left == n)
            {
                par->left = low;
            }
            else
            {
                par->right = low;
            }
        }
        else
        {
            root = low;
        }
        
        // Update balance factor.
        if (low->bf == -1)
        {
            n->bf = 1;
        }
        else
        {
            n->bf = 0;
        }
        if (low->bf == 1)
        {
            mid->bf = -1;
        }
        else
        {
            mid->bf = 0;
        }
        low->bf = 0;
        
        // Update sums.
        if (n->left != NULL)
        {
            n->leftSum = n->left->nodeSum + n->left->leftSum + n->left->rightSum;
        }
        else
        {
            n->leftSum = 0;
        }
        if (n->right != NULL)
        {
            n->rightSum = n->right->nodeSum + n->right->leftSum + n->right->rightSum;
        }
        else
        {
            n->rightSum = 0;
        }
        if (mid->right != NULL)
        {
            mid->rightSum = mid->right->nodeSum + mid->right->leftSum + mid->right->rightSum;
        }
        else
        {
            mid->rightSum = 0;
        }
        if (mid->left != NULL)
        {
            mid->leftSum = mid->left->nodeSum + mid->left->leftSum + mid->left->rightSum;
        }
        else
        {
            mid->leftSum = 0;
        }
        low->rightSum = mid->leftSum + mid->rightSum + mid->nodeSum;
        low->leftSum = n->leftSum + n->rightSum + n->nodeSum;
        
    }
    
    void rotationLR (Node* n)
    {
        Node* mid;
        Node* low;
        Node* par;
        assert (n != NULL);
        mid = n->left;
        low = mid->right;
        par = n->parent;
        assert (mid != NULL);
        assert (low != NULL);
        if (mid->right != NULL)
        {
            mid->right->parent = mid;
        }
        n->left = low->right;
        if (n->left != NULL)
        {
            n->left->parent = n;
        }
        
        low->right = n;
        low->left = mid;
        n->parent = low;
        mid->parent = low;
        low->parent = par;
        
        if (par != NULL)
        {
            if (par->left == n)
            {
                par->left = low;
            }
            else
            {
                par->right = low;
            }
        }
        else
        {
            root = low;
        }
        
        // Update balance factors.
        if (low->bf == 1)
        {
            n->bf = -1;
        }
        else
        {
            n->bf = 0;
        }
        if (low->bf == -1)
        {
            mid->bf = 1;
        }
        else
        {
            mid->bf = 0;
        }
        low->bf = 0;
        
        // Update sums.
        if (n->left != NULL)
        {
            n->leftSum = n->left->nodeSum + n->left->leftSum + n->left->rightSum;
        }
        else
        {
            n->leftSum = 0;
        }
        if (n->right != NULL)
        {
            n->rightSum = n->right->nodeSum + n->right->leftSum + n->right->rightSum;
        }
        else
        {
            n->rightSum = 0;
        }
        if (mid->right != NULL)
        {
            mid->rightSum = mid->right->nodeSum + mid->right->leftSum + mid->right->rightSum;
        }
        else
        {
            mid->rightSum = 0;
        }
        if (mid->left != NULL)
        {
            mid->leftSum = mid->left->nodeSum + mid->left->leftSum + mid->left->rightSum;
        }
        else
        {
            mid->leftSum = 0;
        }
        low->leftSum = mid->leftSum + mid->rightSum + mid->nodeSum;
        low->rightSum = n->leftSum + n->rightSum + n->nodeSum;
        
    }
    
    
    long long insert (long long f, long long l)
    {
        Node* inserted = new Node (f, l);
        if (root == NULL)
        {
            root = inserted;
            root->parent = NULL;
            root->left = NULL;
            root->right = NULL;
            return getSize (f, l);
        }
        else
        {
            // Have to find the right spot and insert as a leaf.
            Node* act;
            Node* prev;
            Node* rootSkip = NULL;
            act = root;
            prev = root;
            long long insertSize = getSize (f, l);
            // Updating sums;
            while (act != NULL)
            {
                
                if (inserted->first < act->first)
                {
                    prev = act;
                    act = act->left;
                    // prev->bf += 1;   
                    prev->leftSum += insertSize;             
                }
                else if (inserted->first > act->first)
                {
                    prev = act;
                    act = act->right;
                    // prev->bf -= 1;
                    prev->rightSum += insertSize;    
                }
                else
                {
                    // Does nothing.
                    //break;
                    assert (0);
                    return -1;
                }
            }
            // Linking.
            if (inserted->first < prev->first)
            {
                prev->left = inserted;
                inserted->parent = prev;
                inserted->left = NULL;
                inserted->right = NULL;
            }
            else if (inserted->first > prev->first)
            {
                prev->right = inserted;
                inserted->parent = prev;
                inserted->left = NULL;
                inserted->right = NULL;      
            }
            else
                return 0;
            
            // Have to update balance factor.
            if (prev->bf == 0)
            {
                if (prev->left == inserted)
                {
                    prev->bf = 1;
                }
                else
                {
                    prev->bf = -1;
                }
                rootSkip = prev->parent;
                // Updating factors on our way to root.
                while (rootSkip != NULL)
                {
                    if (rootSkip->bf != 0)
                    {
                        if (rootSkip->bf == -1)
                        {
                            if (rootSkip->left == prev)
                            {
                                rootSkip->bf = 0;
                                return getSize (f, l);
                            }
                            else
                            {
                                if (prev->bf == 1)
                                {
                                    rotationRL (rootSkip);
                                }
                                else
                                {
                                    rotationRR (rootSkip);
                                }
                                return getSize (f, l);
                            }
                        }
                        else
                        {
                            if (rootSkip->right == prev)
                            {
                                rootSkip->bf = 0;
                                return getSize (f, l);
                            }
                            else
                            {
                                if (prev->bf == -1)
                                {
                                    rotationLR (rootSkip);
                                }
                                else
                                {
                                    rotationLL (rootSkip);
                                }
                                return getSize (f, l);
                            }
                        }
                    }
                    else if (rootSkip->left == prev)
                    {
                        rootSkip->bf = 1;
                    }
                    else
                    {
                        rootSkip->bf = -1;
                    }
                    prev = rootSkip;
                    rootSkip = rootSkip->parent;
                }
            }
            // Ok the tree is balanced. (either 1 or -1 previously)
            else
            {
                prev->bf = 0;
            }    
            return getSize (f, l);
        }
    
    }
   
    
    Node* findPred (Node* par)
    {
        Node* act = par;
        if (par != NULL)
        {
            if (par->left != NULL)
            {
                par = par->left;
                while (par->right != NULL)
                    par = par->right;
            }
            else
            {
                do
                {
                    act = par;
                    par = par->parent;
                } while ((par != NULL) && (par->right != act));
            }
        }
        return par;

    }
    
    void actualizeRoot ()
    {
        if (root != NULL)
        {
            if (root->left != NULL)
            {
                root->leftSum = root->left->nodeSum + root->left->leftSum + root->left->rightSum;
            }
            if (root->right != NULL)
            {
                root->rightSum = root->right->nodeSum + root->right->leftSum + root->right->rightSum;
            }
        }
    }
    
    Node* removeAVL (Node* removed) 
    {
        Node* act;
        Node* prev;
        act = root;
        prev = NULL;
        assert (removed != NULL);
        long long removedVal = getSize (removed->first, removed->last);
        
        // Updating sums.
        while (act != NULL)
        {
            if (act->first < removed->first)
            {
                prev = act;
                act->rightSum -= removedVal;
                act = act->right;
            }
            else if (act->first > removed->first)
            {
                prev = act;
                act->leftSum -= removedVal;
                act = act->left;
            }
            else
            {
                break;
            }
        }
        if (removed == NULL)
            printf ("Error not found\n");
        // Ok node found.
        Node* pred = NULL;
        Node* help = NULL;
        Node* helpt = NULL;
        bool nest = false;
        // Now all the code to remove.
        if (removed->left && removed->right) //((removed->left == NULL) || (removed->right == NULL))
        {
            // Node has two sons.
            pred = removeAVL (findPred (removed));
            nest = false;

        }
        else
        {
            if (removed->left != NULL)
            {
                pred = removed->left;
                removed->left = NULL;
            }
            else
            {
                pred = removed->right;
                removed->right = NULL;
            }
            removed->bf = 0;
            nest = true;
        }
        
        if (pred)
        {
            pred->parent = removed->parent;
            pred->left = removed->left;
            if (pred->left)
            {
                pred->left->parent = pred;
            }
            pred->right = removed->right;
            if (pred->right)
            {
                pred->right->parent = pred;
            }
            pred->bf = removed->bf;
        }
        
        if (removed->parent)
        {
            if (removed->parent->left == removed)
            {
                removed->parent->left = pred;
            }
            else
            {
                removed->parent->right = pred;
            }
        }
        else
        {
            root = pred;
        }
        if (nest)
        {
            help = pred;
            pred = removed->parent;
            //act = NULL;
            
            while (pred)
            {
                if (!pred->bf)
                {
                    if (pred->left == help)
                        pred->bf = -1;
                    else
                        pred->bf = 1;
                    break;
                }
                else
                {
                    if (((pred->bf == 1) && (pred->left == help)) || 
                        ((pred->bf == -1) && (pred->right == help)))
                    {
                        pred->bf = 0;
                        help = pred;
                        pred = pred->parent;
                        //continue;
                    }
                    else
                    {
                        if (pred->left == help)
                        {
                            helpt = pred->right;
                        }
                        else
                        {
                            helpt = pred->left;
                        }
                        
                        if (!helpt->bf)
                        {
                            if (pred->bf == 1)
                            {
                                rotationLL (pred);
                            }
                            else
                            {
                                rotationRR (pred);
                            }
                            break;
                        }
                        else
                        {
                            if (pred->bf == helpt->bf)
                            {
                                if (pred->bf == 1)
                                {
                                    rotationLL (pred);
                                }
                                else
                                {
                                    rotationRR (pred);
                                }
                                help = helpt;
                                pred = helpt->parent;
                                //continue;
                            }
                            else
                            {
                                if (pred->bf == 1)
                                {
                                    rotationLR (pred);
                                }
                                else
                                {
                                    rotationRL (pred);
                                }
                                help = pred->parent;
                                pred = help->parent;
                            }
                            
                        }
                    }
                }
            }
        }
        return removed;
            
        
    } 
    
    Node* find (long long f, long long l)
    {
        Node* act = root;
        while (act != NULL)
        {
            if (act->first < f)
            {
                act = act->right;
            }
            else if (act->first > f)
            {
                act = act->left;
            }
            else
            {
                return act;
            }
        }
        assert (0);
        return act;
    }
    
    void writeTree (Node* n, long long space)
    {

        if (n != NULL)
        {
            
            //
            writeTree (n->right, space+2);
            for (long long i = 0; i < space; i++)
            {
                printf (" ");
            }
            printf ("%lld i moj bf to %lld\n", n->first, n->bf);
            //
            writeTree (n->left, space+2);

        }
        else
        {
            for (long long i = 0; i < space+4; i++)
            {
                printf (" ");
            }
            printf ("NULL\n");
        }
    }

    Node* findRekur (Node* nd, long long &intervals, long long num)
    {
        if (nd != NULL)
        {
            if ((num >= nd->leftSum + intervals) && (num < nd->leftSum + nd->nodeSum + intervals))
            // Right node of interval.
            {
                intervals += nd->leftSum;
                return nd;   
            }
            else if (num < nd->leftSum+intervals)
            {
                return findRekur (nd->left, intervals, num);
            }
            else
            {
                // Adding nodes sum and his whole left subtree.
                intervals += (nd->leftSum + nd->nodeSum);
                return findRekur (nd->right, intervals, num);
            }
        }
        else
        {
            assert (0);
            return nd;
        }   
    }

    
    
    // Searches for right interval and removes it from tree.
    std::pair<long long, long long> findInterval (long long num)
    {
        long long intervals = 0;
        std::pair<long long, long long> p;
        //printf ("Finding\n");
        Node* result = findRekur (root, intervals, num);
        //printf ("Before :\n");
        //writeTree (root);
        //printf ("Found\n");
        assert (result != NULL);
        if (result != NULL)
        {
            p = getInterval (result, num-intervals);
            //printf ("Removing\n");
            Node* n = removeAVL (result);
            //printf ("After :\n");
            // writeTree (root);
            //printf ("Removed\n");
            if (n->first < p.first)
            {
                insert (n->first, p.first-1);
            }
            //printf ("After 1 insertion :\n");
            //writeTree (root);
            if (n->last > p.second)
            {
                insert (p.second+1, n->last);
            }
            //printf ("After 2 insertion :\n");
            // writeTree (root);
            delete (n);
            actualizeRoot ();
            return p;
        }
        else
        {
            return p;
        }
    }
    
};

int main ()
{
    // Main function of the program...
    // Plain simple, return wanted interval and then remove it.
    Tree t;
    long long x, all;
    long long y, z;
    scanf ("%lld", &x);
    // Have to insert to tree interval from 1 to x.
    all = getSize (1, x);
    t.insert (1, x);
    printf ("%lld\n", t.root->nodeSum+ t.root->leftSum + t.root->rightSum);
    bool end = false;
    while (!end)
    {
        // Read query.
        scanf ("%lld", &x);
        // Answer query.
        if ((x >= 0) && (x < all))
        {
            std::pair <long long, long long> p = t.findInterval (x);
            printf ("%lld %lld\n", p.first, p.second);
            if (t.root != NULL)
            {
                printf ("%lld\n", t.root->nodeSum+ t.root->leftSum + t.root->rightSum);
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
        
        /*
        scanf ("%lld", &y);//, &z);
        if (y > 0)
            t.insert (y, y);
        else if (y < 0)
            t.removeAVL (t.find (-y, -y));
        z = 0;
        printf ("-----------------------------------------------------\n");
        t.writeTree (t.root, z);
        */
            
        
    }
    return 0;
};
