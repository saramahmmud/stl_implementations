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
        Node* curr = root_;
        Node* prev = nullptr;
        while (curr){
            if (comp_(key, curr->data.first)) {
                prev = curr;
                curr = curr->left;
            } else if (comp_(curr->data.first, key)) {
                prev = curr;
                curr = curr->right;
            } else {
                return false;
            }
        }
        Node* new_node = new Node(key, value, prev);
        if (!prev) {
            root_ = new_node;
        } else if (comp_(key, prev->data.first)) {
            prev->left = new_node;
        } else if (comp_(prev->data.first, key)) {
            prev->right = new_node;
        }
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
        Node* curr = root_;
        Node* prev = nullptr;
        while (curr){
            if (comp_(key, curr->data.first)) {
                prev = curr;
                curr = curr->left;
            } else if (comp_(curr->data.first, key)) {
                prev = curr;
                curr = curr->right;
            } else {
                return curr->data.second;
            }
        }
        Node* new_node = new Node(key, Value(), prev);
        if (!prev) {
            root_ = new_node;
        } else if (comp_(key, prev->data.first)) {
            prev->left = new_node;
        } else if (comp_(prev->data.first, key)) {
            prev->right = new_node;
        }
        size_ ++;
        return new_node->data.second;
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