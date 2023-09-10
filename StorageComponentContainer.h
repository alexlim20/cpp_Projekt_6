#ifndef STORAGECOMPONENTCONTAINER_H
#define STORAGECOMPONENTCONTAINER_H
#include <iostream>

template <typename T>class StorageComponentContainerIterator
{
    T** ItemPointer;
    public:
        StorageComponentContainerIterator(T** Item);
        StorageComponentContainerIterator operator++();
        StorageComponentContainerIterator operator++(int i);
        bool operator==(const StorageComponentContainerIterator<T>& rhs) const;
        bool operator!=(const StorageComponentContainerIterator<T>& rhs)const;
        T& operator*();
        T* operator->();
};

template <typename T> StorageComponentContainerIterator<T>::StorageComponentContainerIterator(T** Item)
:ItemPointer(Item){}


template <typename T> StorageComponentContainerIterator<T> StorageComponentContainerIterator<T>::operator++()
{
    this->ItemPointer++;
    return *this;
}

template <typename T> StorageComponentContainerIterator<T> StorageComponentContainerIterator<T>::operator++(int i)
{
    this->Itempointer++;
    StorageComponentContainerIterator<T> a = this;
    return *a;
}

template <typename T> bool StorageComponentContainerIterator<T>::operator==(const StorageComponentContainerIterator<T>& rhs) const
{
    return (ItemPointer==rhs);
}

template <typename T> bool StorageComponentContainerIterator<T>::operator!=(const StorageComponentContainerIterator<T>& rhs) const
{
    return (ItemPointer!=rhs.ItemPointer);
}

template <typename T> T& StorageComponentContainerIterator<T>::operator*()
{
    return **ItemPointer;
}

template <typename T> T* StorageComponentContainerIterator<T>::operator->()
{
    return *ItemPointer;
}

template<typename T> class StorageComponentContainer
{
    T** ContentList;
    int MaxSize;
    int CurrentSize;
    int CurrentPos;
    public:
    StorageComponentContainer(int MaxSize = 10);
    ~StorageComponentContainer();
    void add(T* burner);
    T* operator[](int i);
    int getNr();
    StorageComponentContainerIterator<T> begin();
    StorageComponentContainerIterator<T> end();
    T* current();
};

template<typename T> StorageComponentContainer<T>::StorageComponentContainer(int MaxSize)
:MaxSize(MaxSize)
{
    CurrentSize = 0;
    CurrentPos = 0;
    ContentList = new T*[MaxSize]();
}

template<typename T> StorageComponentContainer<T>::~StorageComponentContainer()
{
    for(int i = 0 ; i<MaxSize ; i++)
    {
        delete ContentList[i];
        ContentList[i] = NULL;
    }
    delete [] ContentList;
    ContentList = NULL;
}

template<typename T> void StorageComponentContainer<T>::add(T* burner)
{
    for(int i = 0; i<MaxSize ; i++)
    {
        if(ContentList[i] == NULL)
        {
            ContentList[i] = burner;
            CurrentSize++;
            break;
        }
    }

}

template<typename T> T* StorageComponentContainer<T>::operator[](int i)
{
    if(i > CurrentSize-1)
    {
        std::cout<< "Array index out of bound, exiting";
        exit(0);
    }else
    {
        return ContentList[i];
    }
}

template<typename T> int StorageComponentContainer<T>::getNr()
{
    return CurrentSize;
}

template <typename T> StorageComponentContainerIterator<T> StorageComponentContainer<T>::begin()
{
    return StorageComponentContainerIterator<T>(&ContentList[0]);
}

template <typename T> StorageComponentContainerIterator<T> StorageComponentContainer<T>::end()
{
    return StorageComponentContainerIterator<T>(&ContentList[CurrentSize]);
}

/*template<typename T> T* StorageComponentContainer<T>::current()
{
    if(atEnd()!= true)
    {
        return ContentList[CurrentPos];
    }else
    {
        exit(0);
    }
}*/

#endif
