/**
 * @file
 * Copyright (C) 2024-present Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Mar 4, 2024
 *
 */

#ifndef HOF_LINKED_LIST_LINKED_LIST_HH_
#define HOF_LINKED_LIST_LINKED_LIST_HH_

#include <iostream>
#include <utility>

// #include <fmt/core.h>

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
    void traverse(Visit_f const& visit) const;

    template<typename Container_t>
    Container_t to_container() const;

    void print() const;


    // static methods

    template<Visitable<T> Visit_f>
    static void traverse(node const* head, Visit_f const& visit);
    template<Visitable<T> Visit_f>
    static void traverse(node const& head, Visit_f const& visit);

    template<typename... Ts>
    static void append(linked_list& llist, Ts const&... data);
    template<typename... Ts>
    static void append(linked_list& llist, Ts&&... data);

    template<typename Container_t>
    static Container_t to_container(linked_list const& llist);

    static void print(linked_list const& llist);

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
void linked_list<T>::traverse(
    linked_list<T>::node const* head,
    Visit_f const& visit
) {
    while(nullptr != head) {
        if(visit_result_t::do_end_by_visit == visit(head->data)) {
            return;
        }
        head = head->next;
    }
}
template<typename T>
template<Visitable<T> Visit_f>
void linked_list<T>::traverse(
    linked_list<T>::node const& head,
    Visit_f const& visit
) {
    traverse(&head, visit);
}

template<typename T>
void linked_list<T>::append_single(linked_list<T>& llist, T const& data) {
    // fmt::print("linked_list<T>::append_single(linked_list<T>&, T const&)\n");
    auto* item = new node{data, nullptr};
    if(nullptr == llist.head && nullptr == llist.tail) {
        llist.tail = item;
        llist.head = item;
        return;
    }
    llist.tail->next = item;
    llist.tail = item;
}
template<typename T>
void linked_list<T>::append_single(linked_list<T>& llist, T&& data) {
    // fmt::print("linked_list<T>::append_single(linked_list<T>&, T&&)\n");
    auto* item = new node{std::move(data), nullptr};
    if(nullptr == llist.head && nullptr == llist.tail) {
        llist.tail = item;
        llist.head = item;
        return;
    }
    llist.tail->next = item;
    llist.tail = item;
}


template<typename T>
template<typename... Ts>
void linked_list<T>::append(linked_list<T>& llist, Ts const&... data) {
    // fmt::print("linked_list<T>::append(linked_list<T>&, Ts const&...)\n");
    (linked_list<T>::append_single(llist, data), ...);
}
template<typename T>
template<typename... Ts>
void linked_list<T>::append(linked_list<T>& llist, Ts&&... data) {
    // fmt::print("linked_list<T>::append(linked_list<T>&, Ts&&...)\n");
    (linked_list<T>::append_single(llist, std::forward<Ts>(data)), ...);
}

template<typename T>
template<typename Container_t>
Container_t linked_list<T>::to_container(linked_list<T> const& llist) {
    Container_t result{};
    // result.reserve(128);
    linked_list<T>::node* current = llist.head;

    while(nullptr != current) {
        result.push_back(current->data);
        current = current->next;
    }

    return result;
}


template<typename T>
void linked_list<T>::print(linked_list<T> const& llist) {
    auto const l_print = [](T const& elem) {
        std::cout << "elem: " << elem << '\n';
        return visit_result_t::do_end_normally;
    };
    linked_list<T>::traverse(llist.head, l_print);
    // std::string beg = "[";
    // auto const l_print = [&](T const& elem) {
    //     std::cout <<beg <<elem <<"]";
    //     beg = " -> [";
    //     return visit_result_t::do_end_normally;
    // };
    // linked_list<T>::traverse(llist.head, l_print);
    // std::cout <<'\n';
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
linked_list<T>::linked_list(node* a_head) noexcept
: head(a_head)
, tail(a_head) {
    while(nullptr != tail->next) {
        tail = tail->next;
    }
}

template<typename T>
linked_list<T>::linked_list(T const& data)
: head(new node{data, nullptr})
, tail(head) {
    /* Empty */
}

template<typename T>
linked_list<T>::linked_list(T&& data)
: head(new node{std::move(data), nullptr})
, tail(head) {
    /* Empty */
}

template<typename T>
linked_list<T>::~linked_list() {
    destroy(head);
}

template<typename T>
template<typename... Ts>
void linked_list<T>::append(Ts const&... data) {
    // fmt::print("linked_list<T>::append(Ts const&...)\n");
    linked_list<T>::append(*this, data...);
}
template<typename T>
template<typename... Ts>
void linked_list<T>::append(Ts&&... data) {
    // fmt::print("linked_list<T>::append(T&&...)\n");
    linked_list<T>::append(*this, std::forward<Ts>(data)...);
}

template<typename T>
template<Visitable<T> Visit_f>
void linked_list<T>::traverse(Visit_f const& visit) const {
    if(nullptr == head) {
        return;
    }
    linked_list<T>::traverse(*head, visit);
}

template<typename T>
template<typename Container_t>
Container_t linked_list<T>::to_container() const {
    return linked_list<T>::to_container<Container_t>(*this);
}
template<typename T>
void linked_list<T>::print() const {
    linked_list<T>::print(*this);
}

} /* namespace hof */

#endif /* HOF_LINKED_LIST_LINKED_LIST_HH_ */
