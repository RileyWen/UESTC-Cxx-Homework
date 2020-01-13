#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <memory>

namespace riley {

template <typename T>
class list {
   private:
    struct node_t;

   public:
    class iterator;

    using value_type = T;
    using reference = T&;

    list() : _M_size(0) { _M_head = std::make_shared<node_t>(node_t{}); }

    iterator begin() { return iterator(_M_head->next); }

    iterator end() { return iterator(nullptr); }

    size_t size() { return _M_size; }

    void push_front(const value_type& val) {
        _M_head->next = std::make_shared<node_t>(node_t{val, _M_head->next});
        _M_size++;
    }

    class iterator {
       public:
        iterator() = default;

        iterator(const iterator& it) { node_ptr = it.node_ptr; }

        iterator(iterator&& it) { node_ptr = std::move(it.node_ptr); }

        iterator(std::shared_ptr<node_t> ptr) { node_ptr = ptr; }

        ~iterator() = default;

        bool operator!=(const iterator& rhs) {
            return this->node_ptr != rhs.node_ptr;
        }

        iterator& operator++() {
            node_ptr = node_ptr->next;
            return *this;
        }

        reference operator*() { return node_ptr->val; }

       private:
        std::shared_ptr<node_t> node_ptr;
    };

   private:
    struct node_t {
        T val;
        std::shared_ptr<node_t> next;
    };

    std::shared_ptr<node_t> _M_head;
    size_t _M_size;
};

}  // namespace riley

#endif