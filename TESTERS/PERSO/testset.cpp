#include "testutils.hpp"


static void test_simple_insert()
{
    NS::set<int> s;

    s.insert(0);
    assert(s.size() == 1);
    s.insert(1);
    assert(s.size() == 2);
    s.insert(1);
    assert(s.size() == 2);

    for (size_t l = 0; l < 50; l++)
        s.insert(l);

    assert(s.size() == 50);
}

static void test_accessors()
{
    NS::set<int> s;

    assert(s.empty());
    assert(s.size() == 0);
    s.insert(0);
    assert(!s.empty());
    assert(s.size() == 1);
    s.insert(1);
    assert(s.size() == 2);
    s.insert(1);
    assert(s.size() == 2);

    for (size_t l = 0; l < 50; l++)
        s.insert(l);

    assert(s.count(0));
    assert(s.count(1));
    assert(s.count(2));
    assert(s.count(3));
    assert(s.count(4));
    assert(s.count(49));
    assert(!s.empty());

    s.clear();
    assert(s.empty());
    assert(s.size() == 0);
    s.insert(0);
    assert(!s.empty());
    assert(s.size() == 1);
    s.insert(1);
    assert(s.size() == 2);
    s.insert(1);
    assert(s.size() == 2);

    assert(!s.empty());
}

static void test_index()
{
    NS::set<int> s;

    assert(s.empty());
    assert(s.size() == 0);
    s.insert(0);
    assert(s.count(0));
    assert(!s.empty());
    assert(s.size() == 1);
    s.insert(1);
    assert(s.count(1));
    assert(s.size() == 2);
    s.insert(1);
    assert(s.count(1));
    assert(s.size() == 2);

    for (size_t l = 0; l < 50; l++)
        s.insert(l);

    assert(s.count(0));
    assert(s.count(1));
    assert(s.count(2));
    assert(s.count(3));
    assert(s.count(4));
    assert(s.count(49));
    assert(!s.empty());

    s.clear();
    assert(s.empty());
    assert(s.size() == 0);
    s.insert(0);
    assert(!s.empty());
    assert(s.size() == 1);
    s.insert(1);
    assert(s.size() == 2);
    s.insert(1);
    assert(s.size() == 2);

    assert(!s.empty());
}

static void test_constructors()
{
    NS::set<int> s;
    s.insert(0);
    s.insert(90);
    s.insert(2);

    assert(s.size() == 3);

    NS::set<int> cpy;
    assert(cpy.size() == 0);

    cpy = s;
    assert(cpy.size() == 3);
    cpy.insert(0);
    cpy.insert(90);
    cpy.insert(2);

    cpy.insert(5);
    s.insert(5);
    s.insert(9);
    assert(cpy.count(5));
    assert(s.count(5));

    NS::swap(cpy, s);
    assert(s.count(5));
    assert(cpy.count(5));

    assert(s.size() == 4);
    assert(cpy.size() == 5);

    NS::set<int> cpy2(cpy);

    assert(cpy2.size() == 5);
    assert(cpy.count(5));
    assert(cpy2.count(5));
}

static void test_iterators()
{
    NS::set<int> s;
    s.insert(0);
    s.insert(90);
    s.insert(2);

    NS::set<int>::iterator ite = s.begin();
    assert(*(ite++) == 0);
    assert(*ite == 2);
    assert(*(++ite) == 90);

    assert(++ite == s.end());
    assert(--ite != s.end());

    const NS::set<int> &s2 = s;

    NS::set<int>::const_iterator ite2 = s2.end();
    --ite2;

    assert(*(ite2--) == 90);
    assert(*ite2 == 2);
    assert(*(--ite2) == 0);

    assert(ite2 == s2.begin());
}

static void test_reverse_iterators()
{
    NS::set<int> s;
    s.insert(0);
    s.insert(90);
    s.insert(2);

    NS::set<int>::reverse_iterator ite = s.rbegin();
    assert(*(ite++) == 90);
    assert(*ite == 2);
    assert(*(++ite) == 0);

    assert(++ite == s.rend());
    assert(--ite != s.rend());

    const NS::set<int> &s2 = s;

    NS::set<int>::const_reverse_iterator ite2 = s2.rend();
    --ite2;

    assert(*(ite2--) == 0);
    assert(*ite2 == 2);
    assert(*(--ite2) == 90);

    assert(ite2 == s2.rbegin());
}

static void test_insert()
{
    NS::set<int> s;
    s.insert(0);
    s.insert(90);
    s.insert(2);

    int tab[6] = {
        0,
        50,
        6,
        -45,
        4,
        6,
    };

    s.insert(tab, tab + 6);
    assert(s.size() == 7);
    assert(s.count(0));
    assert(s.count(90));
    assert(s.count(6));
    assert(s.count(-45));
    assert(s.count(4));

    s.clear();
    s.insert(tab, tab + 6);
    assert(s.size() == 5);
    assert(s.count(0));
    assert(s.count(6));
    assert(s.count(-45));
    assert(s.count(4));
}

static void test_cmp()
{
    NS::set<int> s;
    s.insert(0);
    s.insert(90);

    NS::set<int> s2;
    s2.insert(0);
    s2.insert(90);
    s2.insert(2);

    assert(s != s2);
    assert(s2 < s);
    assert(s2 <= s);
    assert(!(s2 > s));
    assert(!(s2 >= s));

    s.insert(2);
    assert(s == s2);
    assert(!(s2 < s));
    assert(s2 <= s);
    assert(!(s2 > s));
    assert(s2 >= s);

    s.insert(1);
    assert(s != s2);
    assert(s2 > s);
    assert(s2 >= s);
    assert(!(s2 < s));
    assert(!(s2 <= s));
}

static void test_swap()
{
    NS::set<int> s;
    s.insert(10);
    s.insert(36);
    s.insert(8);

    NS::set<int> s2;
    s2.insert(0);
    s2.insert(90);

    assert(s.size() == 3);
    assert(s.count(10));
    assert(s.count(36));
    assert(s.count(8));
    assert(s2.size() == 2);
    assert(s2.count(0));
    assert(s2.count(90));

    NS::swap(s, s2);

    assert(s2.size() == 3);
    assert(s2.count(10));
    assert(s2.count(36));
    assert(s2.count(8));
    assert(s.size() == 2);
    assert(s.count(0));
    assert(s.count(90));

    s2.swap(s);

    assert(s.size() == 3);
    assert(s.count(10));
    assert(s.count(36));
    assert(s.count(8));
    assert(s2.size() == 2);
    assert(s2.count(0));
    assert(s2.count(90));
}

static void test_count_find()
{
    NS::set<int> s;
    s.insert(10);
    s.insert(36);
    s.insert(8);

    assert(*s.find(10) == 10);
    assert(*s.find(36) == 36);
    assert(s.find(99) == s.end());
    assert(s.find(0) == s.end());
    assert(s.find(8) == s.begin());

    assert(s.count(10) == 1);
    assert(s.count(9) == 0);
    assert(s.count(36) == 1);
    assert(s.count(55) == 0);
}

static void test_range()
{
    NS::set<int> s;
    s.insert(10);
    s.insert(36);
    s.insert(8);

    NS::set<int>::iterator ite = s.begin();
    ++ite;

    assert(s.lower_bound(5) == s.begin());
    assert(s.lower_bound(9) != s.begin());
    assert(s.lower_bound(9) == ite);
    assert(s.lower_bound(60) == s.end());
    ++ite;

    assert(s.lower_bound(35) == ite);
    assert(s.lower_bound(36) == ite);
    assert(s.lower_bound(37) != ite);
    ++ite;
    assert(s.lower_bound(37) == ite);
    assert(s.lower_bound(37) == s.end());

    ite = s.begin();

    assert(s.upper_bound(5) == ite);
    assert(s.upper_bound(6) == ite);
    assert(s.upper_bound(8) != ite);
    ++ite;
    assert(s.upper_bound(8) == ite);
    assert(s.upper_bound(9) == ite);
    assert(s.upper_bound(10) != ite);
    ++ite;
    assert(s.upper_bound(10) == ite);
    assert(s.upper_bound(30) == ite);

    typedef NS::set<int>::iterator iter;
    NS::pair<iter, iter> range;

    range = s.equal_range(8);
    ite = s.begin();
    assert(range.first == s.begin() && range.second == ++ite);

    range = s.equal_range(36);
    ite = s.begin();
    ++ite;
    assert(range.first == ++ite && range.second == ++ite);

    range = s.equal_range(50);
    assert(range.first == s.end());
    assert(range.second == s.end());

    range = s.equal_range(0);
    assert(range.first == s.begin());
    assert(range.second == s.begin());
}

void test_set()
{
	test_simple_insert();
	test_accessors();
	test_index();
	test_constructors();
	test_iterators();
	test_reverse_iterators();
	test_insert();
	test_cmp();
	test_swap();
	test_count_find();
	test_range();
}
