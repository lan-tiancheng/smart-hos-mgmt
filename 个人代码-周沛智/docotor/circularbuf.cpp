#include "circularbuf.h"

CircularBuf::CircularBuf(int cap)
{
    capacity = cap;
    buffer = new int[capacity];
    clear();
}
int CircularBuf::getElement()
{
    int temp = buffer[getIndex];
    buffer[getIndex] = 0;
    getIndex++;
    getIndex %= capacity;
    subCount();
    return temp;
}
int CircularBuf::getElementNoIndexChange()
{
    int temp = buffer[getIndex];
    //buffer[getIndex] = 0;
    getIndex++;
    getIndex %= capacity;
    subCount();
    return temp;
}
bool CircularBuf::putElement(int element)
{

    buffer[putIndex] = element;
    putIndex++;
    putIndex %= capacity;
    addCount();
    return true;
}
int CircularBuf::getGetIndex()
{
    return getIndex;
}
int CircularBuf::getPutIndex()
{
    return putIndex;
}
int CircularBuf::getElementCount()
{
    return count;
}
void CircularBuf::setGetIndex(int index)
{
    getIndex = index;
}
void CircularBuf::addCount()
{
    count++;
}
void CircularBuf::subCount()
{
    count--;
}
void CircularBuf::clear()
{
    for(int i = 0; i < capacity; i++)
    {
        buffer[i] = 0;
    }
    putIndex = 0;
    getIndex = 0;
    count = 0;
}

