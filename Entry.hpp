#include "Common.hpp"
#pragma once

template <typename K, typename V>
class Entry
{
    K key;
    V value;
    int index;

public:
    // Implicit conversions were made with this?
    explicit Entry();
    explicit Entry(K, V, int = 0);
    // Entry(const Entry<K, V> &);
    K getKey() const;
    V getValue() const;
    int getIndex() const;
    void setValue(V);
    void setKey(K);
    void setIndex(int);
    // void operator=(const Entry<K, V> &);

    // Not a member function.
    // Must be declared inline or won't work for some reason.
    friend std::ostream &operator<<(std::ostream &os, const Entry<K, V> &e)
    {
        os << "Entry has key: " << e.key << " and has value: " << e.value;
    }
    friend bool operator==(const Entry<K, V> &a, const Entry<K, V> &b)
    {
        if (a.getKey() == b.getKey())
        {
            return true;
        }
        return false;
    }
    friend bool operator<(const Entry<K, V> &a, const Entry<K, V> &b)
    {
        if (a.getKey() < b.getKey())
        {
            return true;
        }
        return false;
    }
    friend bool operator>(const Entry<K, V> &a, const Entry<K, V> &b)
    {
        if (a < b || a == b)
        {
            return false;
        }
        return true;
    }
    friend bool operator<=(const Entry<K, V> &a, const Entry<K, V> &b)
    {
        if (a < b || a == b)
        {
            return true;
        }
        return false;
    }
    friend bool operator>=(const Entry<K, V> &a, const Entry<K, V> &b)
    {
        if (a > b || a == b)
        {
            return true;
        }
        return false;
    }
};

template <typename K, typename V>
Entry<K, V>::Entry()
{
    K k;
    V v;
    this->key = k;
    this->value = v;
    this->index = 0;
}
//--Constructor--//
template <typename K, typename V>
Entry<K, V>::Entry(K key, V value, int index) : key(key), value(value) {}

// template <typename K, typename V>
// Entry<K, V>::Entry(const Entry<K, V> &a)
// {
//     key = a.key;
//     value = a.value;
//     index = a.index;
// }
// template <typename K, typename V>
// void Entry<K, V>::operator=(const Entry<K, V> &a)
// {
//     key = a.key;
//     value = a.value;
//     index = a.index;
// }
//--Accessors--//
template <typename K, typename V>
K Entry<K, V>::getKey() const
{
    return this->key;
}
template <typename K, typename V>
V Entry<K, V>::getValue() const
{
    return this->value;
}
template <typename K, typename V>
int Entry<K, V>::getIndex() const
{
    return index;
}

//--Mutators--//
template <typename K, typename V>
void Entry<K, V>::setValue(V value)
{
    this->value = value;
}
template <typename K, typename V>
void Entry<K, V>::setKey(K key)
{
    this->key = key;
}
template <typename K, typename V>
void Entry<K, V>::setIndex(int i)
{
    index = i;
}
