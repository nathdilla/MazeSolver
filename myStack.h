//
// Created by Nathan Dilla on 2/4/22.
//

#ifndef MAZESOLVER_MYSTACK_H
#define MAZESOLVER_MYSTACK_H

template <class T>
struct Node{//contains data, points to data
    T data;
    Node(T newData){//constructor
        data = newData;
        next = NULL;
    }
    struct Node* next;
};

template <class T>
class MyStack{
private:
    Node<T>* head=NULL;
    int length=0;
public:
    void push(T data){//stack new data on top
        Node<T> *newNode = new Node<T>(data);//make new node with data
        newNode->next=head;//node now points to whatever head was pointing to
        head=newNode;//head now points to new node
        length++;
    };
    int size()const{//returns size
        return length;
    };
    bool empty()const{//returns if empty
        return (length==0);
    };
//    T& top(){
//        return head;
//    };
    T top()const{//returns the node at top of the stack
        return head->data;
    };
    void pop(){//removes node at the top of the stack
        if(empty()){//return because there is nothing to remove
            return;
        }
        Node<T>*temp=head;
        head=head->next;//reassign head to point to node below top node
        delete temp;//delete top node
        length--;
    };
};

#endif //MAZESOLVER_MYSTACK_H
