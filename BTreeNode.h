#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace BYLib
{

template < typename T >
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    BTreeNode()
    {
        left = NULL;
        right = NULL;
    }

    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret = new BTreeNode();

        if( ret != NULL )
        {
            ret->m_flag = true;
        }

        return ret;
    }

};

}

#endif // BTREENODE_H
