#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>
#include <stack>

/*
StackFrame declaration
*/
class StackFrame {
    int opStackMaxSize; // max size of operand stack
    int localVarSpaceSize; // size of local variable array
public:
    /*
    Constructor of StackFrame
    */
    StackFrame();
     class DLinkedList
    {
    public:
        class Node;

    protected:
        Node *head;
        Node *tail;
        int count;

    public:
        DLinkedList() : head(nullptr), tail(nullptr), count(0) {};
      //  ~DLinkedList();
        void add(float value, int type)
        {
            Node *tmp = new Node(value, type);
            if (count == 0)
            {
                head = tail = tmp;
            }
            else
            {
                tail->next = tmp;
                tmp->previous = tail;
                tail = tmp;
            }
            count++;
        }
        int size()
        {
            return count;
        }
        bool full()
        {
            return count == 16;
        }
        bool empty()
        {
            return count == 0;
        }
        float get_value(int index)
        {
            Node *tmp = head;
            for (int i = 0; i < index; i++)
            {
                tmp = tmp->next;
            }
            return tmp->data;
        }
        int get_top_type(int index)
        {
            Node *tmp = head;
            for (int i = 0; i < index; i++)
            {
                tmp = tmp->next;
            }
            return tmp->type;
        }
        void removeAt(int index)
        {
            Node *current = head;
            if (index == 0)
            {
                head = head->next;
                if (head != nullptr)
                {
                    head->previous = nullptr;
                }
                else
                {
                    tail = nullptr;
                }
            }
            else
            {
                for (int i = 0; i < index; ++i)
                {
                    current = current->next;
                }
                current->previous->next = current->next;
                if (current->next != nullptr)
                {
                    current->next->previous = current->previous;
                }
                else
                {
                    tail = current->previous;
                }
            }
            delete current;
            --count;
        }
        void clear()
        {
            Node *current = head;
            while (current != nullptr)
            {
                Node *next = current->next;
                delete current;
                current = next;
            }
            head = tail = nullptr;
            count = 0;
        }

    public:
        class Node
        {
        private:
            int type;
            float data;
            Node *next;
            Node *previous;
            friend class DLinkedList;

        public:
            Node()
            {
                this->previous = NULL;
                this->next = NULL;
            }

            Node(float data, int type)
            {
                this->type = type;
                this->data = data;
                this->previous = NULL;
                this->next = NULL;
            }
        };
    };
    class Stack
    {
    protected:
        DLinkedList list;

    public:
        Stack() {}
        void push(float value, int type)
        {
            list.add(value, type);
        }
        void pop()
        {
            list.removeAt(list.size() - 1);
        }
        float top_value()
        {
            return list.get_value(list.size()-1);
        }
        int top_type()
        {
            return list.get_top_type(list.size()-1);
        }
        int below_type()
        {
            return list.get_top_type(list.size() - 2);
        }
        bool full()
        {
            return list.full();
        }
        bool empty()
        {
            return list.empty();
        }
        int size()
        {
            return list.size();
        }
        void clear()
        {
            list.clear();
        }
    };
    enum BalanceValue
    {
    LH = -1,
    EH = 0,
    RH = 1
    };
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    int compareKey(std::string insertKey, std::string nodeKey) {
        if ((insertKey.compare(nodeKey)) > 0) {
            return 1;  
        }
        else if((insertKey.compare(nodeKey)) < 0) {
            return -1;  
        }
        else return 0;
    }
int getBalance(Node*subroot){
    if(!subroot) return 0;
    return getHeightRec(subroot->pLeft)- getHeightRec(subroot->pRight);
}
    Node* rotateLeft(Node* node)
    {
        Node* newRoot = node->pRight;
        node->pRight = newRoot->pLeft;
        newRoot->pLeft = node;
        return newRoot;
    }

    Node* rotateRight(Node* node)
    {
        Node* newRoot = node->pLeft;
        node->pLeft = newRoot->pRight;
        newRoot->pRight = node;
        return newRoot;
    }

    Node* balanceLeft(Node* node)
    {
        if (node->pLeft->balance == LH)
        {
            node = rotateRight(node);
            node->balance = EH;
            node->pRight->balance = EH;
        }
        else
        {
            node->pLeft = rotateLeft(node->pLeft);
            node = rotateRight(node);
            if (node->balance == LH)
            {
                node->pLeft->balance = EH;
                node->pRight->balance = RH;
            }
            else if (node->balance == RH)
            {
                node->pLeft->balance = LH;
                node->pRight->balance = EH;
            }
            else
            {
                node->pLeft->balance = EH;
                node->pRight->balance = EH;
            }
            node->balance = EH;
        }
        return node;
    }

    Node* balanceRight(Node* node)
    {
        if (node->pRight->balance == RH)
        {
            node = rotateLeft(node);
            node->balance = EH;
            node->pLeft->balance = EH;
        }
        else
        {
            node->pRight = rotateRight(node->pRight);
            node = rotateLeft(node);
            if (node->balance == LH)
            {
                node->pLeft->balance = EH;
                node->pRight->balance = RH;
            }
            else if (node->balance == RH)
            {
                node->pLeft->balance = LH;
                node->pRight->balance = EH;
            }
            else
            {
                node->pLeft->balance = EH;
                node->pRight->balance = EH;
            }
            node->balance = EH;
        }
        return node;
    }

    Node *insertRec(Node *node, std::string key, float value, int type, bool &taller)
    {
        if (node == NULL)
        {
            node = new Node(value, type, key);
            taller = true;
            return node;
        }

        int comparison = compareKey(key, node->key);

        if (comparison < 0)
        {
            node->pLeft = insertRec(node->pLeft, key, value, type, taller);
            if (taller)
            {
                if (node->balance == LH)
                {
                    node = balanceLeft(node);
                    taller = false;
                }
                else if (node->balance == EH)
                {
                    node->balance = LH;
                    taller = true;
                }
                else
                {
                    node->balance = EH;
                    taller = false;
                }
            }
        }
        else if (comparison > 0)
        {
            node->pRight = insertRec(node->pRight, key, value, type, taller);
            if (taller)
            {
                if (node->balance == RH)
                {
                    node = balanceRight(node);
                    taller = false;
                }
                else if (node->balance == EH)
                {
                    node->balance = RH;
                    taller = true;
                }
                else
                {
                    node->balance = EH;
                    taller = false;
                }
            }
        }
        return node;
    }
    void insert(std::string key, float value, int type)
    {
        bool taller = false;
        this->root = insertRec(this->root, key, value, type, taller);
    }
    Node *search_key(Node *node, std::string key)
    {
        if (node == nullptr)
            return nullptr;

        int comparison = compareKey(key, node->key);

        if (comparison == 0)
            return node;
        else if (comparison < 0)
            return search_key(node->pLeft, key);
        else
            return search_key(node->pRight, key);
    }
    void deleteTree(Node*& root) {
    if (!root) return;
    deleteTree(root->pLeft);
    deleteTree(root->pRight);
    delete root;
    root = NULL; 
}
int countNode(Node* root) {
        if (root == NULL)
            return 0;
        else {
            return 1 + countNode(root->pLeft) + countNode(root->pRight);
        }
    }
Node *find_parent(Node *node, std::string key)
    {
        if (node == NULL || node->key == key)
            return NULL;

        if ((node->pLeft != NULL && node->pLeft->key == key) || (node->pRight != NULL && node->pRight->key == key))
            return node;

        int comparison = compareKey(key, node->key);

        if (comparison < 0)
            return find_parent(node->pLeft, key);
        else
            return find_parent(node->pRight, key);
    }

    class Node
    {
    public:
        float data;
        int type;
        std::string key;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree;

    public:
        Node(float value, int type, std::string key) : data(value), type(type), key(key), pLeft(NULL), pRight(NULL), balance(EH) {}
        // ~Node() {}
    };
    public:
        void insertNode(std::string key, float value, int type){
            if(type == 0) insert(key, (int)value, type);
            else insert(key, (float)value, type);
        }
        int size(){
            return countNode(root);
        }
        Node* searchKey(std::string key){
            return search_key(root, key);
        }
        Node* parent(std::string key){
            return find_parent(root, key);
        }
        void destroyTree(){
            deleteTree(root);
        }
};
    
    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);
};

#endif // !__STACK_FRAME_H__