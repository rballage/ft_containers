// 1	Input Iterator				Can scan the container forward only once, can't change the value it points to (read-only);
// 2	Output Iterator				Can scan the container forward only once, can't read the value it points to (write-only);
// 3	Forward Iterator			Can scan the container forward multiple times, can read and write the value it points to;
// 4	Bidirectional Iterator		Same as previous one but can scan the container back and forth;
// 5	Random Access Iterator		Same as previous one but can access the container also non-sequentially (i.e. by jumping around);
// 6								Contiguous Iterator	Same as previous one, with the addition that logically adjacent elements are also physically adjacent in memory.
class iterator {
public:
	typedef typename A::difference_type difference_type;
	typedef typename A::value_type value_type;
	typedef typename A::reference reference;
	typedef typename A::pointer pointer;
	typedef std::random_access_iterator_tag iterator_category; //or another tag

	iterator();
	iterator(const iterator&);
	~iterator();

	iterator& operator=(const iterator&);
	bool operator==(const iterator&) const;
	bool operator!=(const iterator&) const;
	bool operator<(const iterator&) const; //optional
	bool operator>(const iterator&) const; //optional
	bool operator<=(const iterator&) const; //optional
	bool operator>=(const iterator&) const; //optional

	iterator& operator++();
	iterator operator++(int); //optional
	iterator& operator--(); //optional
	iterator operator--(int); //optional
	iterator& operator+=(size_type); //optional
	iterator operator+(size_type) const; //optional
	friend iterator operator+(size_type, const iterator&); //optional
	iterator& operator-=(size_type); //optional
	iterator operator-(size_type) const; //optional
	difference_type operator-(iterator) const; //optional

	reference operator*() const;
	pointer operator->() const;
	reference operator[](size_type) const; //optional
};
