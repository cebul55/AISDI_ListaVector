#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

namespace aisdi
{

    template <typename Type>
    class LinkedList
    {

    public:

        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = Type;
        using pointer = Type*;
        using reference = Type&;
        using const_pointer = const Type*;
        using const_reference = const Type&;

        class Node;
        class ConstIterator;
        class Iterator;
        using iterator = Iterator;
        using const_iterator = ConstIterator;

        Node *head;
        Node *tail;
        size_type nodeCounter;
        /*tworzy straznika, tail wskazuje na node przed straznikiem , a it.end()na straznika */
        LinkedList()
        {
            Node *guard = new Node();
            guard->setPrevNode(nullptr);
            guard->setNextNode(nullptr);
            tail = guard;
            head = guard;
            nodeCounter = 0;
        }

        LinkedList(std::initializer_list<Type> l):
                LinkedList()
        {
            for( auto& a : l){ append(a); }
        }

        LinkedList(const LinkedList& other): LinkedList()
        {
            head = other.head;
            tail = other.tail;
            nodeCounter = other.nodeCounter;
        }

        LinkedList(LinkedList&& other)
        {
            head = other.head;
            tail = other.tail;
            nodeCounter = other.nodeCounter;
            other.head = nullptr;
            other.tail = nullptr;
            other.nodeCounter = 0;
        }

        ~LinkedList()
        {}

        LinkedList& operator=(const LinkedList& other)
        {
/*    (void)other;
    throw std::runtime_error("TODO");*/
            if ( this == &other) return *this;
            erase(begin(), end());
            head = other.head;
            tail = other.tail;
            nodeCounter = other.nodeCounter;
            return *this;
        }

        LinkedList& operator=(LinkedList&& other)
        {
/*    (void)other;
    throw std::runtime_error("TkODO");*/
            erase(begin(), end());
            nodeCounter = other.nodeCounter;
            head = other.head;
            tail = other.tail;
            other.nodeCounter = 0;
            other.head = nullptr;
            other.tail = nullptr;
            return *this;
        }

        bool isEmpty() const
        {
            if(nodeCounter == 0)return true;
            else return false;
        }

        size_type getSize() const
        {
            return nodeCounter;
        }

        void append(const Type& item)
        {
            if ( nodeCounter == 0) {
                prepend(item);
            }
            else
            {
                Node *newNode = new Node();

                Node *warden = tail->getNextNode();
                newNode->setNextNode(tail->getNextNode());
                newNode->setPrevNode(tail);
                warden->setPrevNode(newNode);
                tail->setNextNode(newNode);
                tail = newNode;

                newNode->value_ = new Type(item);

                ++nodeCounter;
            }

        }

        void prepend(const Type& item) {
            /*(void)item;
            throw std::runtime_error("TODO");*/
            Node *newNode = new Node();
            newNode->setNextNode(head);
            newNode->setPrevNode(nullptr);

            head->setPrevNode(newNode);
            //new(newNode->value_) Type(item);
            newNode->value_ = new Type(item);
            head = newNode;

            if(nodeCounter == 0)
                tail = newNode;

            ++nodeCounter;
        }

        void insert(const const_iterator& insertPosition, const Type& item)
        {
            if(insertPosition == begin())
                prepend(item);
            else if(insertPosition == end())
                append(item);
            else
            {
                Node *newNode = new Node();
                iterator i = insertPosition;
                Node *node = i.current_;

                newNode->setPrevNode(node->getPrevNode());
                newNode->setNextNode(node);
                node->getPrevNode()->setNextNode(newNode);
                node->setPrevNode(newNode);
//          new(newNode->value_) Type(item);
                newNode->value_ = new Type(item);

                nodeCounter++;
            }
        }

        Type popFirst()
        {
/*
    throw std::runtime_error("TODO");
*/
            if(nodeCounter == 0)throw std::logic_error("List is empty");
            Type *typeValue = new Type;
            typeValue = head->value_;
            Node *tmp = head->getNextNode();
            tmp->setPrevNode(nullptr);
            delete head;
            head = tmp;
            nodeCounter--;
            return *typeValue;
        }

        Type popLast()
        {
            if(nodeCounter == 0)throw std::logic_error("List is empty");
            Type *typeValue = new Type;
            typeValue = tail->value_;
            Node *tmp = tail->getNextNode();
            tmp->setPrevNode(tail->getPrevNode());
            if(tmp->getPrevNode() != nullptr)
            {
                tail->getPrevNode()->setNextNode(tmp);
            }
            delete tail;
            tail = tmp->getPrevNode();
            nodeCounter--;
            return *typeValue;
        }

        void erase(const const_iterator& possition)
        {
            if(possition == end()) throw std::out_of_range("You can't erase GUARD");
            const_iterator i = possition;
            Node *node = i.current_;


            Node *nextNode = node->getNextNode();
            //node->value_->~Type();
            if(node->getPrevNode() == nullptr) {
                head = node->getNextNode();
                if(head->getNextNode() == nullptr) tail = head;
            }
            else {
                Node *prevNode = node->getPrevNode();
                prevNode->setNextNode(node->getNextNode());
            }

            nextNode->setPrevNode(node->getPrevNode());
            delete node->value_;
            delete node;
            nodeCounter--;
        }

        void erase(const const_iterator& firstExcluded, const const_iterator& firstIncluded)
        {
            //delete first argument , second is the first node that will stay
            for(const_iterator i = firstExcluded; i != firstIncluded; ) erase(i++);
        }

        iterator begin()
        {
            iterator *it = new iterator;
            it->current_ = head;
            return (*it);
        }

        iterator end()
        {
            iterator *it = new iterator;
            if(nodeCounter == 0)
                it->current_ = tail;
            else
                it->current_ = tail->getNextNode();
            return (*it);
        }

        const_iterator cbegin() const
        {
            const_iterator *cit = new const_iterator;
            cit->current_ = head;
            return (*cit);
        }

        const_iterator cend() const
        {
            const_iterator  *cit = new const_iterator;
            if(nodeCounter == 0)
                cit->current_ = tail;
            else
                cit->current_ = tail->getNextNode();
            return (*cit);
        }

        const_iterator begin() const
        {
            return cbegin();
        }

        const_iterator end() const
        {
            return cend();
        }
    };

    template <typename Type>
    class LinkedList<Type>::Node
    {
        Node *next_;
        Node *prev_;
    public:
        Type *value_;

        Node()
        {
            next_= nullptr;
            prev_= nullptr;
        }

        Type getValue()          { return value_; }
        Node* getNextNode()     { return next_; }
        Node* getPrevNode()     { return prev_; }
        //void setValue( Type value )     { value_ = value ; return; }
        void setNextNode( Node *next )  { next_ = next ; return; }
        void setPrevNode( Node *prev )  { prev_ = prev ; return; }
    };

    template <typename Type>
    class LinkedList<Type>::ConstIterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename LinkedList::value_type;
        using difference_type = typename LinkedList::difference_type;
        using pointer = typename LinkedList::const_pointer;
        using reference = typename LinkedList::const_reference;

        Node *current_;

        explicit ConstIterator()
        {
            current_ = nullptr;
        }

        reference operator*() const
        {
/*
    throw std::runtime_error("TODO");
*/
            /* jezeli odwolujesz sie do straznika throw...*/
            if(current_->getNextNode() == nullptr) throw std::out_of_range("Out_of_range");
            return *current_->value_;
        }

        ConstIterator& operator++()   /*preinkrementacja*/
        {
/*    throw std::runtime_error("TODO");*/
            if(current_->getNextNode() == nullptr) throw std::out_of_range("oUt_of_range"); /*ostatni element listy to straznik i od wskazuje na nullptr*/
            current_ = current_->getNextNode();
            return *this;
        }

        ConstIterator operator++(int)     /*postinkrementacja*/
        {
/*  throw std::runtime_error("TODO");*/
            const_iterator preIt = *this;
            ++(*this);
            return preIt;
        }

        ConstIterator& operator--()
        {
            //throw std::runtime_error("TODO");

            if(current_->getPrevNode() == nullptr) throw std::out_of_range("ouT of range");
            current_ = current_->getPrevNode();
            return *this;
        }

        ConstIterator operator--(int)
        {
            //throw std::runtime_error("TODO");
            const_iterator preIt = *this;
            --(*this);
            return preIt;
        }

        ConstIterator operator+(difference_type d) const
        {
/*    (void)d;
    throw std::runtime_error("TODO");*/
            ConstIterator *tmp = new ConstIterator;
            tmp->current_ = current_;
            if( d > 0 ){
                while ( d-- > 0) { ++(*tmp); }
            }
            else if( d < 0){
                while( d++ < 0) {--(*tmp);}
            }
            return *tmp;
        }

        ConstIterator operator-(difference_type d) const
        {
/*    (void)d;
    throw std::runtime_error("TODO");*/
            return operator+(-d);
        }

        bool operator==(const ConstIterator& other) const
        {/*
    (void)other;
    throw std::runtime_error("TODO");*/
            if(current_ == other.current_)return true;
            else return false;
        }

        bool operator!=(const ConstIterator& other) const
        {
/*    (void)other;
    throw std::runtime_error("TODO");*/
            if(current_ == other.current_)return false;
            else return true;
        }
    };

    template <typename Type>
    class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
    {
    public:
        using pointer = typename LinkedList::pointer;
        using reference = typename LinkedList::reference;

        explicit Iterator()
        {}

        Iterator(const ConstIterator& other)
                : ConstIterator(other)
        {}

        Iterator& operator++()
        {
            ConstIterator::operator++();
            return *this;
        }

        Iterator operator++(int)
        {
            auto result = *this;
            ConstIterator::operator++();
            return result;
        }

        Iterator& operator--()
        {
            ConstIterator::operator--();
            return *this;
        }

        Iterator operator--(int)
        {
            auto result = *this;
            ConstIterator::operator--();
            return result;
        }

        Iterator operator+(difference_type d) const
        {
            return ConstIterator::operator+(d);
        }

        Iterator operator-(difference_type d) const
        {
            return ConstIterator::operator-(d);
        }

        reference operator*() const
        {
            // ugly cast, yet reduces code duplication.
            return const_cast<reference>(ConstIterator::operator*());
        }
    };

}

#endif // AISDI_LINEAR_LINKEDLIST_H
