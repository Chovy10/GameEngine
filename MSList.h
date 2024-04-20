#pragma once

template <typename T>
class MSNode
{
public:
    MSNode(T data);
    ~MSNode();
    

    T data;
    MSNode* next_node;
};


template <typename T>
class MSList
{
public:
    MSList();
    ~MSList();

    int get_size();
    void add(T data);
    // Operator[] ¿À¹ö·Îµù
    T& operator[](int index);

private:
    MSNode<T>* _head;
    int _size;

};