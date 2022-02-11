//
// Created by Nathan Dilla on 2/4/22.
//

#ifndef MAZESOLVER_MYQ_H
#define MAZESOLVER_MYQ_H

template<class T>
class MyQ{
public:
    void push(T);
    void pop();
    bool empty()const;
    int size()const;
    T front()const;
};

#endif //MAZESOLVER_MYQ_H
