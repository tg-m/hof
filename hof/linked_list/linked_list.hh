/**
 * @file
 * Copyright (C) 2024-present Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Mar 4, 2024
 *
 */

#ifndef HOF_LINKED_LIST_LINKED_LIST_HH_
#define HOF_LINKED_LIST_LINKED_LIST_HH_

#include <utility>

#include "concepts/visitable/visitable.hh"

namespace hof {

template<typename T>
class linked_list final {
public:
    struct node {
        T data;
        node* next;
    };


    linked_list() noexcept;
    linked_list(node* a_head) noexcept;
    linked_list(T const& data);
    linked_list(T&& data);
    ~linked_list();



    template<typename... Ts>
    void append(Ts const&...);
    template<typename... Ts>
    void append(Ts&&...);

    template<Visitable<T> Visit_f>
    void traverse(Visit_f const& visit);


    // static methods

    template<Visitable<T> Visit_f>
    static void traverse(node const& head, Visit_f const& visit);

    template<typename... Ts>
    static void append(linked_list& llist, Ts const&... data);
    template<typename... Ts>
    static void append(linked_list& llist, Ts&&... data);


private:
    node* head{nullptr};
    node* tail{nullptr};


    static void destroy(node* head);

    static void append_single(linked_list& llist, T const& data);
    static void append_single(linked_list& llist, T&& data);


    /* no implementation */
    linked_list(linked_list const&) = delete;
    linked_list(linked_list&&) = delete;
    linked_list& operator=(linked_list const&) = delete;
    linked_list& operator=(linked_list&&) = delete;
};

//
// static methods implementation(s)
//


template<typename T>
template<Visitable<T> Visit_f>
void linked_list<T>::traverse(linked_list<T>::node const& head, Visit_f const& visit) {
    linked_list<T>::node const* current{&head};
    do {

        if(visit_result_t::do_end_by_visit == visit(current->data)) {
            return;
        }
        current = current->next;

    } while(nullptr != current);
}

template<typename T>
void linked_list<T>::append_single(linked_list<T>& llist, T const& data) {
    auto* item = new node{data, nullptr};
    llist.tail->next = item;
    llist.tail = item;
}
template<typename T>
void linked_list<T>::append_single(linked_list<T>& llist, T&& data) {
    auto* item = new node{std::move(data), nullptr};
    llist.tail->next = item;
    llist.tail = item;
}
template<typename T>
template<typename... Ts>
void linked_list<T>::append(linked_list<T>& llist, Ts const&... data) {
    (linked_list<T>::append_single(llist, data), ...);
}
template<typename T>
template<typename... Ts>
void linked_list<T>::append(linked_list<T>& llist, Ts&&... data) {
    (linked_list<T>::append_single(llist, std::forward<Ts>(data)), ...);
}


template<typename T>
void linked_list<T>::destroy(node* head) {
    while(nullptr != head) {
        auto* to_delete = head;
        head = head->next;
        delete to_delete;
    }
}






//
// non-static methods implementation(s)
//

template<typename T>
linked_list<T>::linked_list() noexcept = default;

template<typename T>
linked_list<T>::linked_list(node* a_head) noexcept : head(a_head), tail(a_head) {
    while(nullptr != tail->next) {
        tail = tail->next;
    }
}

template<typename T>
linked_list<T>::linked_list(T const& data)
: head(new node{data, nullptr})
, tail(head)
{
    /* Empty */
}

template<typename T>
linked_list<T>::linked_list(T&& data)
: head(new node{std::move(data), nullptr})
, tail(head)
{
    /* Empty */
}

template<typename T>
linked_list<T>::~linked_list() {
    destroy(head);
}

template<typename T>
template<typename... Ts>
void linked_list<T>::append(Ts const&... data) {
    linked_list<T>::append(*this, data...);
}
template<typename T>
template<typename... Ts>
void linked_list<T>::append(Ts&&... data) {
    linked_list<T>::append(*this, std::forward<Ts>(data)...);
}

template<typename T>
template<Visitable<T> Visit_f>
void linked_list<T>::traverse(Visit_f const& visit) {
    if(nullptr == head) { return; }
    linked_list<T>::traverse(*head, visit);
}


} /* namespace hof */

#endif /* HOF_LINKED_LIST_LINKED_LIST_HH_ */
