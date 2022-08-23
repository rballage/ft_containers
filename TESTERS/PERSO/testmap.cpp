
#include "testutils.hpp"


static void test_simple_insert()
{
    NS::map<int, int> m;

    m.insert(NS::make_pair(0, 2));
    assert(m.size() == 1);
    m.insert(NS::make_pair(1, 5));
    assert(m.size() == 2);
    m.insert(NS::make_pair(1, 8));
    assert(m.size() == 2);

    for (size_t l = 0; l < 50; l++)
        m.insert(NS::make_pair(l, 2 * l));

    assert(m.size() == 50);
}

static void test_accessors()
{
    NS::map<int, int> m;

    assert(m.empty());
    assert(m.size() == 0);
    m.insert(NS::make_pair(0, 2));
    assert(!m.empty());
    assert(m.size() == 1);
    m.insert(NS::make_pair(1, 5));
    assert(m.size() == 2);
    m.insert(NS::make_pair(1, 8));
    assert(m.size() == 2);

    for (size_t l = 0; l < 50; l++)
        m.insert(NS::make_pair(l, 2 * l));

    assert(m[0] == 2);
    assert(m[1] == 5);
    assert(m[2] == 4);
    assert(m[3] == 6);
    assert(m[4] == 8);
    assert(m[49] == 49 * 2);
    assert(!m.empty());

    m.clear();
    assert(m.empty());
    assert(m.size() == 0);
    m.insert(NS::make_pair(0, 2));
    assert(!m.empty());
    assert(m.size() == 1);
    m.insert(NS::make_pair(1, 5));
    assert(m.size() == 2);
    m.insert(NS::make_pair(1, 8));
    assert(m.size() == 2);

    assert(!m.empty());
}

static void test_index()
{
    NS::map<int, int> m;

    assert(m.empty());
    assert(m.size() == 0);
    m[0] = 2;
    assert(m[0] == 2);
    assert(!m.empty());
    assert(m.size() == 1);
    m[1] = 5;
    assert(m[1] == 5);
    assert(m.size() == 2);
    m[1] = 8;
    assert(m[1] == 8);
    assert(m.size() == 2);

    for (size_t l = 0; l < 50; l++)
        m.insert(NS::make_pair(l, 2 * l));

    assert(m[0] == 2);
    assert(m[1] == 8);
    assert(m[2] == 4);
    assert(m[3] == 6);
    assert(m[4] == 8);
    assert(m[49] == 49 * 2);
    assert(!m.empty());

    m.clear();
    assert(m.empty());
    assert(m.size() == 0);
    m.insert(NS::make_pair(0, 2));
    assert(!m.empty());
    assert(m.size() == 1);
    m.insert(NS::make_pair(1, 5));
    assert(m.size() == 2);
    m.insert(NS::make_pair(1, 8));
    assert(m.size() == 2);

    assert(!m.empty());
}

static void test_constructors()
{
    NS::map<int, int> m;
    m[0] = 50;
    m[90] = 5;
    m[2] = 80;

    assert(m.size() == 3);

    NS::map<int, int> cpy;
    assert(cpy.size() == 0);

    cpy = m;
    assert(cpy.size() == 3);
    assert(cpy[0] == 50);
    assert(cpy[90] == 5);
    assert(cpy[2] == 80);

    cpy[5] = 8;
    m[5] = 80;
    m[9] = 80;
    assert(cpy[5] == 8);
    assert(m[5] == 80);

    NS::swap(cpy, m);
    assert(m[5] == 8);
    assert(cpy[5] == 80);

    assert(m.size() == 4);
    assert(cpy.size() == 5);

    NS::map<int, int> cpy2(cpy);

    assert(cpy2.size() == 5);
    assert(cpy[5] == 80);
    assert(cpy2[5] == 80);
}

static void test_iterators()
{
    NS::map<int, int> m;
    m[0] = 50;
    m[90] = 5;
    m[2] = 80;

    NS::map<int, int>::iterator ite = m.begin();
    assert(ite->first == 0);
    assert(ite->second == 50);
    assert((++ite)->first == 2);
    assert((ite++)->second == 80);
    assert(ite->first == 90);
    assert(ite->second == 5);

    NS::pair<int, int> pair = *ite;
    assert(pair.first == 90);
    assert(pair.second == 5);

    assert(++ite == m.end());
    assert(--ite != m.end());

    const NS::map<int, int> &m2 = m;

    NS::map<int, int>::const_iterator ite2 = m2.end();
    --ite2;

    assert(ite2->first == 90);
    assert(ite2->second == 5);
    assert((--ite2)->first == 2);
    assert((ite2--)->second == 80);
    assert(ite2->first == 0);
    assert(ite2->second == 50);

    assert(ite2 == m2.begin());
}

static void test_reverse_iterators()
{
    NS::map<int, int> m;
    m[0] = 50;
    m[90] = 5;
    m[2] = 80;

    NS::map<int, int>::reverse_iterator ite = m.rbegin();
    assert(ite->first == 90);
    assert(ite->second == 5);
    assert((++ite)->first == 2);
    assert((ite++)->second == 80);
    assert(ite->first == 0);
    assert(ite->second == 50);

    NS::pair<int, int> pair = *ite;
    assert(pair.first == 0);
    assert(pair.second == 50);

    assert(++ite == m.rend());
    assert(--ite != m.rend());

    const NS::map<int, int> &m2 = m;

    NS::map<int, int>::const_reverse_iterator ite2 = m2.rend();
    --ite2;

    assert(ite2->first == 0);
    assert(ite2->second == 50);
    assert((--ite2)->first == 2);
    assert((ite2--)->second == 80);
    assert(ite2->first == 90);
    assert(ite2->second == 5);

    assert(ite2 == m2.rbegin());
}

static void test_insert()
{
    NS::map<int, int> m;
    m[0] = 50;
    m[90] = 5;
    m[2] = 80;

    NS::pair<int, int> tab[6] = {
        NS::make_pair(0, 1),
        NS::make_pair(50, 2),
        NS::make_pair(6, 4),
        NS::make_pair(-45, -5),
        NS::make_pair(4, 98),
        NS::make_pair(6, 9),
    };

    m.insert(tab, tab + 6);
    assert(m.size() == 7);
    assert(m[0] == 50);
    assert(m[90] == 5);
    assert(m[6] == 4);
    assert(m[-45] == -5);
    assert(m[4] == 98);

    m.clear();
    m.insert(tab, tab + 6);
    assert(m.size() == 5);
    assert(m[0] == 1);
    assert(m[6] == 4);
    assert(m[-45] == -5);
    assert(m[4] == 98);
}

static void test_cmp()
{
    NS::map<int, int> m;
    m[0] = 50;
    m[90] = 5;

    NS::map<int, int> m2;
    m2[0] = 50;
    m2[90] = 5;
    m2[2] = 80;

    assert(m != m2);
    assert(m2 < m);
    assert(m2 <= m);
    assert(!(m2 > m));
    assert(!(m2 >= m));

    m[2] = 80;
    assert(m == m2);
    assert(!(m2 < m));
    assert(m2 <= m);
    assert(!(m2 > m));
    assert(m2 >= m);

    m[1] = 4;
    assert(m != m2);
    assert(m2 > m);
    assert(m2 >= m);
    assert(!(m2 < m));
    assert(!(m2 <= m));
}

static void test_swap()
{
    NS::map<int, int> m;
    m[10] = 96;
    m[36] = 9;
    m[8] = 8;

    NS::map<int, int> m2;
    m2[0] = 50;
    m2[90] = 5;

    assert(m.size() == 3);
    assert(m[10] == 96);
    assert(m[36] == 9);
    assert(m[8] == 8);
    assert(m2.size() == 2);
    assert(m2[0] == 50);
    assert(m2[90] == 5);

    NS::swap(m, m2);

    assert(m2.size() == 3);
    assert(m2[10] == 96);
    assert(m2[36] == 9);
    assert(m2[8] == 8);
    assert(m.size() == 2);
    assert(m[0] == 50);
    assert(m[90] == 5);

    m2.swap(m);

    assert(m.size() == 3);
    assert(m[10] == 96);
    assert(m[36] == 9);
    assert(m[8] == 8);
    assert(m2.size() == 2);
    assert(m2[0] == 50);
    assert(m2[90] == 5);
}

static void test_count_find()
{
    NS::map<int, int> m;
    m[10] = 96;
    m[36] = 9;
    m[8] = 8;

    assert(m.find(10)->second == 96);
    assert(m.find(36)->second == 9);
    assert(m.find(99) == m.end());
    assert(m.find(0) == m.end());
    assert(m.find(8) == m.begin());

    assert(m.count(10) == 1);
    assert(m.count(9) == 0);
    assert(m.count(36) == 1);
    assert(m.count(55) == 0);
}

static void test_range()
{
    NS::map<int, int> m;
    m[10] = 96;
    m[36] = 9;
    m[8] = 8;

    NS::map<int, int>::iterator ite = m.begin();
    ++ite;

    assert(m.lower_bound(5) == m.begin());
    assert(m.lower_bound(9) != m.begin());
    assert(m.lower_bound(9) == ite);
    assert(m.lower_bound(60) == m.end());
    ++ite;

    assert(m.lower_bound(35) == ite);
    assert(m.lower_bound(36) == ite);
    assert(m.lower_bound(37) != ite);
    ++ite;
    assert(m.lower_bound(37) == ite);
    assert(m.lower_bound(37) == m.end());

    ite = m.begin();

    assert(m.upper_bound(5) == ite);
    assert(m.upper_bound(6) == ite);
    assert(m.upper_bound(8) != ite);
    ++ite;
    assert(m.upper_bound(8) == ite);
    assert(m.upper_bound(9) == ite);
    assert(m.upper_bound(10) != ite);
    ++ite;
    assert(m.upper_bound(10) == ite);
    assert(m.upper_bound(30) == ite);

    typedef NS::map<int, int>::iterator iter;
    NS::pair<iter, iter> range;

    range = m.equal_range(8);
    ite = m.begin();
    assert(range.first == m.begin() && range.second == ++ite);

    range = m.equal_range(36);
    ite = m.begin();
    ++ite;
    assert(range.first == ++ite && range.second == ++ite);

    range = m.equal_range(50);
    assert(range.first == m.end());
    assert(range.second == m.end());

    range = m.equal_range(0);
    assert(range.first == m.begin());
    assert(range.second == m.begin());
}

void test_map()
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
