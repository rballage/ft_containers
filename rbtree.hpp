// Implementing Red-Black Tree in C++

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
			black, red
		}t_color;
		class		node
		{
		public:
			value_type		data;
			node	*parent;
			node	*left;
			node	*right;
			t_color		color;
			node(void) : data(0), parent(0), left(0), right(0), color(red) {};
			node(const value_type &d) : data(d), parent(0), left(0), right(0), color(red) {};
			node(const node &n) : data(n.data), parent(0), left(0), right(0), color(red) {};
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
		// node *_nil;
		node *_root;
		// node *_left_most;
		// node *_right_most;

		// const std::string _range_err_message(size_type val) const
		// {
		// 	std::string message;
		// 	std::ostringstream out;
		// 	out << "map::_M_range_check: __n (which is " << val << ") >= this->size() (which is " << size() << ")";
		// 	message = out.str();
		// 	return message;
		// };
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
			if (y->left != TNULL)
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
			if (y->right != TNULL)
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
			while (k->parent->color == red)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == red) {
						u->color = black;
						k->parent->color = black;
						k->parent->parent->color = red;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							_rotate_right(k);
						}
						k->parent->color = black;
						k->parent->parent->color = red;
						_rotate_left(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;
					if (u->color == red)
					{
						u->color = black;
						k->parent->color = black;
						k->parent->parent->color = red;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							_rotate_left(k);
						}
						k->parent->color = black;
						k->parent->parent->color = red;
						_rotate_right(k->parent->parent);
					}
				}
				if (k == _root)
					break;
			}
			root->color = black;
		};

		node *_insert_(node *n, const value_type &data)
		{
			if (!n)
			{
				n = _new_node(data);
				// n->data = data;
				if (!_root)
				_root = n;
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
			if (!_root)
			{
				_root = _new_node(data);
				// _root->data = data;
				return _root;
			}
			return _insert_(_root, data);
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
			node *n = _search(key, _root);
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

		void _delete_all(node *n) //must pass _root as it recursively erase all nodes
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
		_comparator(comp), _allocator(alloc), _root(0) {};
		// template <class InputIterator>
		// map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		map(const map& x) : _root(_deep_copy(x._root, NULL)) {};

		map& operator=(const map& other)
		{
			if ((*this)._root == other._root)
				return *this;
			clear();
			_root = _deep_copy(other._root, NULL);
			return *this;
		};

		~map()
		{
			_delete_all(_root);
		};
		void print()
		{
			_print_inorder(_root);
		};
		void clear()
		{
			_delete_all(_root);
			_root = 0;
		};
		size_type size(void) const
		{
			return _size(_root);
		};
		size_type count(const Key& key) const
		{
			if (!_root)
				return 0;
			return _search(key, _root) ? 1 : 0;
		};
		iterator find( const Key& key )
		{
			return _search(key, _root);
		};
		const_iterator find( const Key& key ) const
		{
			return _search(key, _root);
		};

		size_type max_size(void) const {return allocator_type().max_size();};

		void insert(const value_type &value)
		{
			// (void)pos;
			_insert_(_root, value);
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

class RedBlackTree {
   private:
  node* root;
  node* TNULL;

  void initializeNULLNode(node* node, node* parent) {
    node->data = 0;
    node->parent = parent;
    node->left = 0;
    node->right = 0;
    node->color = black;
  }

  // Preorder
  void preOrderHelper(node* node) {
    if (node != TNULL) {
      cout << node->data << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }

  // Inorder
  void inOrderHelper(node* node) {
    if (node != TNULL) {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void postOrderHelper(node* node) {
    if (node != TNULL) {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }

  node* searchTreeHelper(node* node, int key) {
    if (node == TNULL || key == node->data) {
      return node;
    }

    if (key < node->data) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(node* x) {
    node* s;
    while (x != root && x->color == black) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == red) {
          s->color = black;
          x->parent->color = red;
          _rotate_left(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == black && s->right->color == black) {
          s->color = red;
          x = x->parent;
        } else {
          if (s->right->color == black) {
            s->left->color = black;
            s->color = red;
            _rotate_right(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = black;
          s->right->color = black;
          _rotate_left(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == red) {
          s->color = black;
          x->parent->color = red;
          _rotate_right(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == black && s->right->color == black) {
          s->color = red;
          x = x->parent;
        } else {
          if (s->left->color == black) {
            s->right->color = black;
            s->color = red;
            _rotate_left(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = black;
          s->left->color = black;
          _rotate_right(x->parent);
          x = root;
        }
      }
    }
    x->color = black;
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
    node* z = TNULL;
    node* x, y;
    while (node != TNULL) {
      if (node->data == key) {
        z = node;
      }

      if (node->data <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == TNULL) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
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
    if (y_original_color == black) {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void insertFix(node* k) {
    node* u;
    while (k->parent->color == red) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == red) {
          u->color = black;
          k->parent->color = black;
          k->parent->parent->color = red;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            _rotate_right(k);
          }
          k->parent->color = black;
          k->parent->parent->color = red;
          _rotate_left(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == red) {
          u->color = black;
          k->parent->color = black;
          k->parent->parent->color = red;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            _rotate_left(k);
          }
          k->parent->color = black;
          k->parent->parent->color = red;
          _rotate_right(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = black;
  }

  // void printHelper(node* root, string indent, bool last) {
  //   if (root != TNULL) {
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
  RedBlackTree() {
    TNULL = new Node;
    TNULL->color = black;
    TNULL->left = 0;
    TNULL->right = 0;
    root = TNULL;
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
    while (node->left != TNULL) {
      node = node->left;
    }
    return node;
  }

  node* maximum(node* node) {
    while (node->right != TNULL) {
      node = node->right;
    }
    return node;
  }

  node* successor(node* x) {
    if (x->right != TNULL) {
      return minimum(x->right);
    }

    node* y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  node* predecessor(node* x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }

    node* y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void _rotate_left(node* x) {
    node* y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
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
    if (y->right != TNULL) {
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
    node->left = TNULL;
    node->right = TNULL;
    node->color = red;

    node* y = 0;
    node* x = this->root;

    while (x != TNULL) {
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
      node->color = black;
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
  RedBlackTree bst;
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
