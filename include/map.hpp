#include <functional>

namespace stl {

template <typename Key, typename Value, typename Compare = std::less<Key>> 
class map {
private:
    struct Node
    {
        std::pair<Key, Value> data;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;

        Node(const Key &k, const Value &v, Node *p)
            : data(k, v),
              parent(p)
        {
        }
    };

    Node* root_ = nullptr;
    std::size_t size_ = 0;
    Compare comp_;

public:
    map() = default;

    // no copy/ move semantics for now
    map(const map&) = delete;
    map& operator=(const map&) = delete;

    // cant use defualt destructor as this wouldnt recursively delete nodes
    ~map() {
        destroy(root_);
    }

   std::size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    bool insert(const Key& key, const Value& value) {
        Node** curr = &root_;
        Node* parent = nullptr;
        while (*curr){
            parent = *curr;
            if (comp_(key, (*curr)->data.first)) {
                curr = &(*curr)->left;
            } else if (comp_((*curr)->data.first, key)) {
                curr = &(*curr)->right;
            } else {
                return false;
            }
        }
        *curr = new Node(key, value, parent);
        size_ ++;
        return true;
    }

    Value* find(const Key& key) {
        Node* node = find_node(key);

        if (node) {
            return &(node->data.second);
        }

        return nullptr;
    }

    const Value* find(const Key& key) const {
        Node* node = find_node(key);

        if (node) {
            return &(node->data.second);
        }

        return nullptr;
    }

    Value& operator[](const Key& key) {
        Node** curr = &root_;
        Node* parent = nullptr;
        while (*curr){
            parent = *curr;
            if (comp_(key, (*curr)->data.first)) {
                curr = &(*curr)->left;
            } else if (comp_((*curr)->data.first, key)) {
                curr = &(*curr)->right;
            } else {
                return (*curr)->data.second;
            }
        }
        *curr = new Node(key, Value(), parent);
        size_ ++;
        return (*curr)->data.second;
    }

private:
    Node* find_node(const Key& key) const {
        Node* curr = root_;
        while (curr) {
            if (comp_(key, curr->data.first)) {
                curr = curr->left;
            } else if (comp_(curr->data.first, key)) {
                curr = curr->right;
            } else {
                return curr;
            }
        }
        return nullptr;
    }

    void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
        return;
    }
};
}