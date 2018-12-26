#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace BYLib
{

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder,
};

enum BTreeNodePos
{
    ANY,
    LEFT,
    RIGHT,
};

template < typename T >
class BTree : public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;

    virtual BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const
    {
        BTreeNode<T>* ret = NULL;

        if( node != NULL )
        {
            if( node->value == value )
            {
                ret = node;
            }
            else
            {
                if( ret == NULL )
                {
                    ret = find(node->left, value);
                }

                if( ret == NULL )
                {
                    ret = find(node->right, value);
                }
            }

        }

        return ret;
    }

    virtual BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = NULL;

        if( node == obj )
        {
            ret = node;
        }
        else
        {
            if( node != NULL )
            {
                if( ret == NULL )
                {
                    ret = find(node->left, obj);
                }

                if( ret == NULL )
                {
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }

    virtual bool insert(BTreeNode<T>* node, BTreeNode<T>* nodeParent, BTreeNodePos pos)
    {
        bool ret = true;

        if( pos == ANY )
        {
            if( nodeParent->left == NULL )
            {
                nodeParent->left = node;
            }
            else if( nodeParent->right == NULL )
            {
                nodeParent->right = node;
            }
            else
            {
                ret = false;
            }
        }
        else if( pos == LEFT )
        {
            if( nodeParent->left == NULL )
            {
                nodeParent->left = node;
            }
            else
            {
                ret = false;
            }
        }
        else if( pos == RIGHT )
        {
            if( nodeParent->right == NULL )
            {
                nodeParent->right = node;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }

        return ret;
    }

    virtual void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>();

        if( ret == NULL )
        {
            THROW_EXCEPTION(NOEnoughMemoryException, "No memory to create new tree...");
        }
        else
        {
            if( root() == node )
            {
                this->m_root = NULL;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if( parent->left == node )
                {
                    parent->left = NULL;
                }
                else if( parent->right == node )
                {
                    parent->right = NULL;
                }

                node->parent = NULL;
            }

            ret->m_root = node;
        }
    }

    virtual void free(BTreeNode<T>* node)
    {
        if( node != NULL )
        {
            free(node->left);
            free(node->right);

            if( node->flag() )
            {
                delete node;
            }
        }
    }

    int count(BTreeNode<T>* node) const
    {
        return (node != NULL) ? (count(node->left) + count(node->right) + 1) : 0;
    }

    int height(BTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            int lh = height(node->left);
            int rh = height(node->right);

            ret = ( (lh > rh) ? lh : rh ) + 1;
        }

        return ret;
    }

    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            BTreeNode<T>* child[] = { node->left, node->right };

            ret = (!!node->left + !!node->right);

            for( int i = 2; (i < 2) && (ret < 2); i++)
            {
                int d = degree(child[i]);

                if( ret < d )
                {
                    ret = d;
                }
            }
        }

        return ret;
    }

    void preOrderTraversal( BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if( node != NULL )
        {
            queue.add(node);
            preOrderTraversal(node->left, queue);
            preOrderTraversal(node->right, queue);
        }
    }

    void inOrderTraversal( BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if( node != NULL )
        {
            inOrderTraversal(node->left, queue);
            queue.add(node);
            inOrderTraversal(node->right, queue);
        }
    }

    void postOrderTraversal( BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if( node != NULL )
        {
            postOrderTraversal(node->left, queue);
            postOrderTraversal(node->right, queue);
            queue.add(node);
        }
    }

    void levelOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if( node != NULL )
        {
            LinkQueue<BTreeNode<T>*> tmp;

            tmp.add(node);

            while ( tmp.length() > 0 )
            {
                BTreeNode<T>* n = tmp.front();

                if( n->left != NULL )
                {
                    tmp.add(n->left);
                }

                if( n->right != NULL )
                {
                    tmp.add(n->right);
                }

                tmp.remove();
                queue.add(n);
            }
        }
    }

    BTreeNode<T>* clone(BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = NULL;

        if( node != NULL )
        {
            ret = BTreeNode<T>::NewNode();

            if( ret != NULL )
            {
                ret->value = node->value;

                ret->left = clone(node->left);
                ret->right = clone(node->right);

                if( ret->left != NULL )
                {
                    ret->left->parent = ret;
                }
                if( ret->right != NULL )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NOEnoughMemoryException, "No memory to create new node...");
            }
        }

        return ret;
    }

    bool equal(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        if( lh == rh )
        {
            return true;
        }
        else if( (lh != NULL) && (rh != NULL) )
        {
            return (lh->value == rh->value) && (equal(lh->left, rh->left)) && (equal(lh->right, rh->right));
        }
    }

    BTreeNode<T>* add(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        BTreeNode<T>* ret = NULL;

        if( (lh == NULL) && (rh != NULL) )
        {
            ret = clone(rh);
        }
        else if( (lh != NULL) && (rh == NULL) )
        {
            ret = clone(lh);
        }
        else if( (lh != NULL) && (rh != NULL) )
        {
            ret = BTreeNode<T>::NewNode();

            if( ret != NULL )
            {
                ret->value = lh->value + rh->value;

                ret->left = add(lh->left, rh->left);
                ret->right = add(lh->right, rh->right);

                if( ret->left != NULL )
                {
                    ret->left->parent = ret;
                }
                if( ret->right != NULL )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NOEnoughMemoryException, "No memory to create new node...");
            }
        }

        return ret;
    }

    void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*>& queue)
    {

        switch (order)
        {
        case PreOrder:
            preOrderTraversal(root(), queue);
            break;

        case InOrder:
            inOrderTraversal(root(), queue);
            break;

        case PostOrder:
            postOrderTraversal(root(), queue);
            break;

        case LevelOrder:
            levelOrderTraversal(root(), queue);
            break;

        default:
            THROW_EXCEPTION(InvalidParameterException,"Parameter order is invalid...");
            break;
        }

    }

    BTreeNode<T>* connect(LinkQueue<BTreeNode<T>*>& queue)
    {
        BTreeNode<T>* ret = NULL;

        if( queue.length() > 0 )
        {
            ret = queue.front();

            BTreeNode<T>* slider = queue.front();

            queue.remove();

            slider->left = NULL;

            while( queue.length() > 0 )
            {
                slider->right = queue.front();
                queue.front()->left = slider;
                slider = queue.front();
                queue.remove();
            }

            slider->right = NULL;
        }

        return ret;
    }

public:
    bool insert(TreeNode<T>* node)
    {
        return insert(node, ANY);
    }

    virtual bool insert(TreeNode<T>* node, BTreeNodePos pos)
    {
        bool ret = true;

        if( node != NULL )
        {
            if( this->m_root == NULL )
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                BTreeNode<T>* nodeParent = find(node->parent);

                if( nodeParent != NULL )
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node), nodeParent, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parameter tree node...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "parameter node can not be NULL...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        return insert(value, parent, ANY);
    }

    virtual bool insert(const T& value, TreeNode<T>* parent, BTreeNodePos pos)
    {
        bool ret = true;
        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if( node == NULL )
        {
            THROW_EXCEPTION(NOEnoughMemoryException, "No memory to create new node...");
        }
        else
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);

            if( !ret )
            {
                delete node;
            }
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        BTree<T>* ret = NULL;
        BTreeNode<T>* node = find(value);
        if( node == NULL )
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the tree node via value...");
        }
        else
        {
            remove(node, ret);

            m_queue.clear();
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;

        node = find(node);

        if( node == NULL )
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid...");
        }
        else
        {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);
        }

        return ret;
    }

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());

        m_queue.clear();

        this->m_root = NULL;
    }

    bool begin()
    {
        bool ret = (root() != NULL);

        if( ret )
        {
            m_queue.clear();
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if( ret )
        {
            BTreeNode<T>* node = m_queue.front();

            m_queue.remove();

            if( node->left != NULL )
            {
                m_queue.add(node->left);
            }
            if( node->right != NULL )
            {
                m_queue.add(node->right);
            }
        }

        return ret;
    }

    T current()
    {
        if( !end() )
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current possion...");
        }
    }

    SharedPointer< Array<T> > traversal( BTTraversal order)
    {
        DynamicArray<T>* ret = NULL;
        LinkQueue< BTreeNode<T>* > queue;

        traversal(order, queue);

        ret = new DynamicArray<T>(queue.length());

        if( ret != NULL )
        {
            for( int i = 0; i < ret->length(); i++, queue.remove() )
            {
                ret->set(i, queue.front()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NOEnoughMemoryException, "No memory to create return array...");
        }
        return ret;
    }

    BTreeNode<T>* thread(BTTraversal order)
    {
        BTreeNode<T>* ret = NULL;
        LinkQueue<BTreeNode<T>*> queue;

        traversal(order, queue);

        ret = connect(queue);

        this->m_root = NULL;

        m_queue.clear();

        return ret;
    }

    SharedPointer< BTree<T> > clone() const
    {
        BTree<T>* ret = new BTree<T>();

        if( ret != NULL )
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NOEnoughMemoryException, "No memory to create new tree...");
        }

        return ret;
    }

    bool operator == (const BTree<T>& btree)
    {
        return equal(root(), btree.root());
    }

    bool operator != (const BTree<T>& btree)
    {
        return !equal(root(), btree.root());
    }

    SharedPointer< BTree<T> > add(const BTree<T>& btree) const
    {
        BTree<T>* ret = new BTree<T>();

        if( ret != NULL )
        {
            ret->m_root = add(root(), btree.root());
        }
        else
        {
            THROW_EXCEPTION(NOEnoughMemoryException, "No memory to create new tree...");
        }

        return ret;
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif // BTREE_H
