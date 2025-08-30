#ifndef CIRCULARBUF_H
#define CIRCULARBUF_H

class CircularBuf
{
public:
    CircularBuf(int cap);
    int getPutIndex();
    int getGetIndex();
    void setGetIndex(int getIndex);
    bool putElement(int element);
    int getElement();
    int getElementNoIndexChange();
    int getElementCount();
    void addCount();
    void subCount();
    void clear();
private:
    int *buffer;
    int capacity;
    int putIndex;
    int getIndex;
    int count;
};

#endif // CIRCULARBUF_H
