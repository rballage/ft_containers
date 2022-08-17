// Implementing RED-BLACK Tree in C++

#include <iostream>
using namespace std;

#pragma once

#include "utils.hpp"
// https://github.com/pmouhali/ft_containers/blob/main/map.hpp
namespace ft
{

	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class map
	{
	public:
		typedef  Key								key_type;
		typedef  T									mapped_type;
		typedef typename std::pair<key_type, mapped_type>	value_type;
	private:
		typedef enum		_node_color
		{
			BLACK, RED
		}t_color;
		class		node
		{
		public:
			value_type		data;
			node	*parent;
			node	*left;
			node	*right;
			t_color		color;
			node(void) : data(0), parent(0), left(0), right(0), color(RED) {};
			node(const value_type &d) : data(d), parent(0), left(0), right(0), color(RED) {};
			node(const node &n) : data(n.data), parent(0), left(0), right(0), color(RED) {};
			~node()
			{
				parent = left = right = 0;

			};
			node& operator=( const node& other )
			{
				(void)other;
			};
			node* _next(node *n)
			{
				if (n->right)
					return _min(n->right);
				while (n->parent && n->parent->left != n)
					n = n->parent;
				return n->parent ? n->parent : n;
			};
			node* _prev(node *n)
			{
				if (n->left)
					return _max(n->left);
				while (n->parent && n->parent->right != n)
					n = n->parent;
				return n->parent ? n->parent : n;
			};
			node* operator++()
			{

				return _next(&(*this));
			};
			node* operator++(int)
			{
				node tmp = *this;
				++(*this);
				return tmp;
			};
			bool operator==(const bidirectional_iterator< T >& other) {return (_current == other._current);};
			bool operator!=(const bidirectional_iterator< T >& other) {return (_current != other._current);};
			reference operator*() const {return *_current;};
			pointer operator->() const {return &(operator*());};
			node& operator--()
			{
				--_current;
				return *this;
			};
			node operator--(int)
			{
				node tmp = *this;
				--(*this);
				return tmp;
			};
		};

	public:
		typedef typename Alloc::template rebind<node>::other	allocator_type;
		typedef Compare							key_compare;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename ft::bidirectional_iterator<value_type>				iterator;
		typedef typename ft::bidirectional_iterator<const value_type> 		const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> 				const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type			difference_type;

	private:

		key_compare _comparator;
		allocator_type _allocator;
		node *_NIL;
		node *root;

		node *_new_node(const value_type &ref)
		{
			node *ptr;
			_allocator.construct(ptr = _allocator.allocate(1), node(ref));
			ptr->parent = 0;
			ptr->left = 0;
			ptr->right = 0;
			return ptr;
		};

		void _rotate_left(node* x)
		{
			node* y = x->right;
			x->right = y->left;
			if (y->left != _NIL)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == 0)
				this->root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		};

		void _rotate_right(node* x)
		{
			node* y = x->left;
			x->left = y->right;
			if (y->right != _NIL)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == 0)
				this->root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		};

		void _insert_fix(node* k)
		{
			node* u;
			while (k->parent->color == RED)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == RED) {
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							_rotate_right(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						_rotate_left(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;
					if (u->color == RED)
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							_rotate_left(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						_rotate_right(k->parent->parent);
					}
				}
				if (k == root)
					break;
			}
			root->color = BLACK;
		};

		node *_insert_(node *n, const value_type &data)
		{
			if (!n)
			{
				n = _new_node(data);
				// n->data = data;
				if (!root)
					root = n;
				return n;
			}
			if (data.first < n->data.first)
			{
				n->left = _insert_(n->left, data);
				n->left->parent = n;
			}
			else if (data.first > n->data.first)
			{
				n->right = _insert_(n->right, data);
				n->right->parent = n;
			}
			_insert_fix(n);
			return n;
		};

		node *_insert(const value_type &data)
		{
			if (!root)
			{
				root = _new_node(data);
				// root->data = data;
				return root;
			}
			return _insert_(root, data);
		};

		node *_min(node* n)
		{
			if (n == NULL)
				return NULL;
			else if (n->left == NULL)
				return n;
			else
				return _min(n->left);
		};
		node *_max(node* n)
		{
			if (n == NULL)
				return NULL;
			else if (n->right == NULL)
				return n;
			else
				return _max(n->right);
		};

		void _delete_fix(node* x)
		{
			node* s;
			while (x != root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						_rotate_left(x->parent);
						s = x->parent->right;
					}
					if (s->left->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->right->color == BLACK)
						{
							s->left->color = BLACK;
							s->color = RED;
							_rotate_right(s);
							s = x->parent->right;
						}
						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->right->color = BLACK;
						_rotate_left(x->parent);
						x = root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						_rotate_right(x->parent);
						s = x->parent->left;
					}
					if (s->right->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->left->color == BLACK)
						{
							s->right->color = BLACK;
							s->color = RED;
							_rotate_left(s);
							s = x->parent->left;
						}
						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->left->color = BLACK;
						_rotate_right(x->parent);
						x = root;
					}
				}
			}
			x->color = BLACK;
		};

		void rbTransplant(node* u, node* v)
		{
			if (u->parent == 0)
				root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		};
		void _delete(node n)
		{
			if (!n)
				return ;
			if (!n->left && !n->right)
			{
				if (n->parent)
				{
					if (n->parent->left == n)
						n->parent->left = NULL;
					else
						n->parent->right = NULL;
				}
				_allocator.destroy(n);
				_allocator.deallocate(n, 1);
				n = NULL;
			}
			if ((n->left && !n->right) || (!n->left && n->right))
			{
				node *child = n->left ? n->left : n->right;
				if (n->parent)
				{
					if (n->parent->left == n)
						n->parent->left = child;
					else
						n->parent->right = child;
					child->parent = n->parent;
				}
				_allocator.destroy(n);
				_allocator.deallocate(n, 1);
				n = NULL;
			}
			else
			{
				node *successor = _min(n->right);
				successor->left = n->left;
				successor->parent = n->parent;
				if (n->parent && n->parent->left == n)
					n->parent->left = successor;
				if (n->parent && n->parent->right == n)
					n->parent->right = successor;
				_allocator.destroy(n);
				_allocator.deallocate(n, 1);
				n = successor;
			}
		};
		void _delete(key_type &key)
		{
			node *n = _search(key, root);
			if (!n)
				return ;
			_delete(n);
		};
		node *_search(key_type &key, node *n)
		{
			if (!n || (!_comparator(key, n->data.first) && !_comparator(n->data.first, key)))
				return n;
			if (_comparator(key, n->data.first))
				return _search(key, n->left);
			return _search(key, n->right);
		};
		void _print_inorder(node *n)
		{
			if (!n)
				return ;
			_print_inorder(n->left);
			std::cout << n->data.first << ": " << n->data.second << std::endl;
			_print_inorder(n->right);
		};
		size_type _size(node *n) const
		{
			if (!n)
				return 0;
			return 1 + _size(n->left) + _size(n->right);
		};

		void _delete_all(node *n) //must pass root as it recursively erase all nodes
		{
			if (!n)
				return ;
			_delete_all(n->left);
			_delete_all(n->right);
			_allocator.destroy(n);
			_allocator.deallocate(n, 1);
			n = 0;
		};
		node *_deep_copy(node *n, node *parent)
		{
			if (!n)
				return n;
			node* copy = _new_node(n->data);
			copy->parent = parent;
			copy->left = _deep_copy(n->left, copy);
			copy->right = _deep_copy(n->right, copy);
			return copy;
		};
	public:
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_comparator(comp), _allocator(alloc), root(0) {};
		// template <class InputIterator>
		// map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		map(const map& x) : root(_deep_copy(x.root, NULL)) {};

		map& operator=(const map& other)
		{
			if ((*this).root == other.root)
				return *this;
			clear();
			root = _deep_copy(other.root, NULL);
			return *this;
		};

		~map()
		{
			_delete_all(root);
		};
		void print()
		{
			_print_inorder(root);
		};
		void clear()
		{
			_delete_all(root);
			root = 0;
		};
		size_type size(void) const
		{
			return _size(root);
		};
		size_type count(const Key& key) const
		{
			if (!root)
				return 0;
			return _search(key, root) ? 1 : 0;
		};
		iterator find( const Key& key )
		{
			return _search(key, root);
		};
		const_iterator find( const Key& key ) const
		{
			return _search(key, root);
		};

		size_type max_size(void) const {return allocator_type().max_size();};

		void insert(const value_type &value)
		{
			// (void)pos;
			_insert_(root, value);
		};
	};

};



struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

typedef Node *node*;

class REDBLACKTree {
   private:
  node* root;
  node* _NIL;

  void initializeNULLNode(node* node, node* parent) {
    node->data = 0;
    node->parent = parent;
    node->left = 0;
    node->right = 0;
    node->color = BLACK;
  }

  // Preorder
  void preOrderHelper(node* node) {
    if (node != _NIL) {
      cout << node->data << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }

  // Inorder
  void inOrderHelper(node* node) {
    if (node != _NIL) {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void postOrderHelper(node* node) {
    if (node != _NIL) {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }

  node* searchTreeHelper(node* node, int key) {
    if (node == _NIL || key == node->data) {
      return node;
    }

    if (key < node->data) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void _delete_fix(node* x) {
    node* s;
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == RED) {
          s->color = BLACK;
          x->parent->color = RED;
          _rotate_left(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == BLACK && s->right->color == BLACK) {
          s->color = RED;
          x = x->parent;
        } else {
          if (s->right->color == BLACK) {
            s->left->color = BLACK;
            s->color = RED;
            _rotate_right(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = BLACK;
          s->right->color = BLACK;
          _rotate_left(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == RED) {
          s->color = BLACK;
          x->parent->color = RED;
          _rotate_right(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == BLACK && s->right->color == BLACK) {
          s->color = RED;
          x = x->parent;
        } else {
          if (s->left->color == BLACK) {
            s->right->color = BLACK;
            s->color = RED;
            _rotate_left(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = BLACK;
          s->left->color = BLACK;
          _rotate_right(x->parent);
          x = root;
        }
      }
    }
    x->color = BLACK;
  }

  void rbTransplant(node* u, node* v) {
    if (u->parent == 0) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(node* node, int key) {
    node* z = _NIL;
    node* x, y;
    while (node != _NIL) {
      if (node->data == key) {
        z = node;
      }

      if (node->data <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == _NIL) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == _NIL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == _NIL) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == BLACK) {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void insertFix(node* k) {
    node* u;
    while (k->parent->color == RED) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == RED) {
          u->color = BLACK;
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            _rotate_right(k);
          }
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          _rotate_left(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == RED) {
          u->color = BLACK;
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            _rotate_left(k);
          }
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          _rotate_right(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = BLACK;
  }

  // void printHelper(node* root, string indent, bool last) {
  //   if (root != _NIL) {
  //     cout << indent;
  //     if (last) {
  //       cout << "R----";
  //       indent += "   ";
  //     } else {
  //       cout << "L----";
  //       indent += "|  ";
  //     }
  //
  //     string sColor = root->color ? "RED" : "BLACK";
  //     cout << root->data << "(" << sColor << ")" << endl;
  //     printHelper(root->left, indent, false);
  //     printHelper(root->right, indent, true);
  //   }
  // }

   public:
  REDBLACKTree() {
    _NIL = new Node;
    _NIL->color = BLACK;
    _NIL->left = 0;
    _NIL->right = 0;
    root = _NIL;
  }

  void preorder() {
    preOrderHelper(this->root);
  }

  void inorder() {
    inOrderHelper(this->root);
  }

  void postorder() {
    postOrderHelper(this->root);
  }

  node* searchTree(int k) {
    return searchTreeHelper(this->root, k);
  }

  node* minimum(node* node) {
    while (node->left != _NIL) {
      node = node->left;
    }
    return node;
  }

  node* maximum(node* node) {
    while (node->right != _NIL) {
      node = node->right;
    }
    return node;
  }

  node* successor(node* x) {
    if (x->right != _NIL) {
      return minimum(x->right);
    }

    node* y = x->parent;
    while (y != _NIL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  node* pREDecessor(node* x) {
    if (x->left != _NIL) {
      return maximum(x->left);
    }

    node* y = x->parent;
    while (y != _NIL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void _rotate_left(node* x) {
    node* y = x->right;
    x->right = y->left;
    if (y->left != _NIL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == 0) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void _rotate_right(node* x) {
    node* y = x->left;
    x->left = y->right;
    if (y->right != _NIL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == 0) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // Inserting a node
  void insert(int key) {
    node* node = new Node;
    node->parent = 0;
    node->data = key;
    node->left = _NIL;
    node->right = _NIL;
    node->color = RED;

    node* y = 0;
    node* x = this->root;

    while (x != _NIL) {
      y = x;
      if (node->data < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == 0) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == 0) {
      node->color = BLACK;
      return;
    }

    if (node->parent->parent == 0) {
      return;
    }

    insertFix(node);
  }

  node* getRoot() {
    return this->root;
  }

  void deleteNode(int data) {
    deleteNodeHelper(this->root, data);
  }

  void printTree() {
    if (root) {
      printHelper(this->root, "", true);
    }
  }
};

int main() {
  REDBLACKTree bst;
  bst.insert(55);
  bst.insert(40);
  bst.insert(65);
  bst.insert(60);
  bst.insert(75);
  bst.insert(57);

  bst.printTree();
  cout << endl
     << "After deleting" << endl;
  bst.deleteNode(40);
  bst.printTree();
}
