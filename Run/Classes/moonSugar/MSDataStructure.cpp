//
//  MSDataStructure.cpp
//  Run
//
//  Created by RockLee on 14-3-10.
//
//

#include "MSDataStructure.h"

NS_MS_BEGIN
/****************QueueItem*****************/
QueueItem::QueueItem(std::string itemNameValue)
{
    itemName = itemNameValue;
}

QueueItem::~QueueItem()
{
    
}

/***************Queue*********************/
Queue::Queue(std::string nameValue)
{
    name = nameValue;
    queueList = cocos2d::Array::create();
    queueList->retain();
}

Queue::~Queue()
{
    queueList->removeAllObjects();
    queueList->release();
}

int Queue::addItem(moonsugar::QueueItem *itemValue)
{
    //addItemIndex(itemValue, index);
    queueList->addObject(itemValue);
    return queueList->count() - 1;
}

int Queue::addItemIndex(moonsugar::QueueItem *itemValue, int indexValue)
{
    queueList->insertObject(itemValue, indexValue);
    return indexValue;
}

moonsugar::QueueItem * Queue::removeItem(std::string itemName)
{
    int index = checkItem(itemName);
    return removeIndex(index);
}

moonsugar::QueueItem * Queue::removeIndex(int indexValue)
{
    QueueItem * tempItem = (QueueItem*)queueList->getObjectAtIndex(indexValue);
    queueList->removeObjectAtIndex(indexValue);
    return tempItem;
}

moonsugar::QueueItem * Queue::getItem(std::string itemNameValue)
{
    int index = checkItem(itemNameValue);
    return getIndex(index);
}

moonsugar::QueueItem * Queue::getIndex(int indexValue)
{
    return (QueueItem *)queueList->getObjectAtIndex(indexValue);
}

int Queue::checkItem(std::string itemNameValue)
{
    int n = queueList->count();
    for (int i = 0; i < n; i ++)
    {
        QueueItem * tempItem = (QueueItem *)queueList->getObjectAtIndex(i);
        if (tempItem->itemName == itemNameValue)
        {
            return i;
        }
    }
    return -1;
}

/**************Stack***************/
Stack::Stack()
{
    queueList = cocos2d::Array::create();
    queueList->retain();
}

Stack::~Stack()
{
    queueList->removeAllObjects();
    queueList->release();
}

int Stack::addItem(moonsugar::QueueItem *itemValue)
{
    queueList->insertObject(itemValue, 0);
    return 0;
}

moonsugar::QueueItem * Stack::popItem()
{
    return checkNext();
}

moonsugar::QueueItem * Stack::checkNext()
{
    if (queueList->count() <= 0) return nullptr;
    QueueItem * tempItem = (QueueItem *)queueList->getObjectAtIndex(0);
    queueList->removeObjectAtIndex(0);
    return tempItem;
}
NS_MS_END;