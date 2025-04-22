#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__
#include <string>
/*
StackFrame declaration
*/
class StackFrame
{
    int opStackMaxSize;  // max size of operand stack
    int localVarArrSize; // size of local variable array
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
        // int get_below_type(int index)
        // {
        //     Node *tmp = head;
        //     for (int i = 0; i < index - 1; i++)
        //     {
        //         tmp = tmp->next;
        //     }
        //     return tmp->type;
        // }
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

    class Array
    {
        int markIndex[256];
        float localArray[256];

    public:
        Array()
        {
            for (int i = 0; i < 256; i++)
            {
                markIndex[i] = 0;
            }
        }
        int type(int index)
        {
            return (int)localArray[index];
        }
        float value_at(int index)
        {
            return localArray[index + 1];
        }
        void put_value(float dataValue, int dataType, int index)
        {
            markIndex[index] = 1;
            localArray[index] = dataType;
            localArray[index + 1] = dataValue;
        }

        bool check_index(int index)
        {
            if (markIndex[index] == 0)
                return false;
            else
                return true;
        }
    };
    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);
};
#endif // !__STACK_FRAME_H__