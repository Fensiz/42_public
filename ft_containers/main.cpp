#include <sys/time.h>
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include "RBTree.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#ifndef lib
# define lib std
#endif
#define xstr(x) str(x)
#define str(x) #x
#define _vector lib::vector
#define _map	lib::map
#define _stack	lib::stack
#define _set	lib::set
#define OK "\x1b[32mOK\x1b[0m"
#define FAIL "\x1b[31mFAIL\x1b[0m"


template<class T>
void printV(T x)
{
for (typename T::iterator it = x.begin(); it < x.end(); ++it)
	std::cout << *it << " ";
std::cout << std::endl;
}


template <typename T>
struct vecs
{
	vecs()
	:S(),
	F() {}
	vecs(const vecs<T>& source)
	:S(source.S),
	F(source.F) {}
	
	std::vector<T> S;
	ft::vector<T> F;
};

class Timer
{
public:
	static void Start() {
		gettimeofday(&start, NULL);
	}
	static void Stop() {
		gettimeofday(&end, NULL);
		res = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
	}
	static long getRes() {
		return res;
	}
private:
	static struct timeval start;
	static struct timeval end;
	static long res;
};

std::string red(const std::string& s) {
	return std::string("\x1b[31m" + s + "\x1b[0m");
}

std::string green(const std::string& s) {
	return std::string("\x1b[32m" + s + "\x1b[0m");
}

struct timeval Timer::start;
struct timeval Timer::end;
long Timer::res;


template <typename T>
void vec_equals(T& A, T& B) {
	char* pA = reinterpret_cast<char*>(&A[0]);
	char* pB = reinterpret_cast<char*>(&B[0]);
	bool contOk = true;

	std::cout << " Size: ";
	A.size() == B.size() ? std::cout << OK << " " << A.size() : std::cout << FAIL << "A=" << A.size() << " B=" << B.size();
	std::cout << " Capacity: ";
	A.capacity() == B.capacity() ? std::cout << OK : std::cout << FAIL << "A=" << A.capacity() << " B=" << B.capacity();
	for (size_t i = 0; i < A.size() * sizeof(typename T::value_type); ++i) {
		if (pA[i] != pB[i]) {
			contOk = false;
			break;
		}
	}
	std::cout << " Content: ";
	contOk ? std::cout << OK : std::cout << FAIL;
	std::cout << std::endl;
}

template <typename T>
void vec_equals(std::vector<T>& A, ft::vector<T>& B) {
	char* pA = reinterpret_cast<char*>(&A[0]);
	char* pB = reinterpret_cast<char*>(&B[0]);
	bool contOk = true;

	std::cout << " Size: ";
	A.size() == B.size() ? std::cout << OK << " " << A.size() : std::cout << FAIL << "A(std)=" << A.size() << " B(ft)=" << B.size();
	std::cout << " Capacity: ";
	A.capacity() == B.capacity() ? std::cout << OK : std::cout << FAIL << "A(std)=" << A.capacity() << " B(ft)=" << B.capacity();
	for (size_t i = 0; i < A.size() * sizeof(T); ++i) {
		if (pA[i] != pB[i]) {
			contOk = false;
			break;
		}
	}
	std::cout << " Content: ";
	contOk ? std::cout << OK : std::cout << FAIL;
	std::cout << std::endl;
}

void _FAIL() {
	std::cout << FAIL << std::endl;
}

/* insert range test */
template <class T>
void push_res(vecs<typename T::value_type>& X, T& __vector) {
    X.S.push_back(__vector.front());
    X.S.push_back(__vector.back());
    X.S.push_back((typename T::value_type)__vector.size());
    X.S.push_back((typename T::value_type)__vector.capacity());
    X.F.push_back(__vector.front());
    X.F.push_back(__vector.back());
    X.F.push_back((typename T::value_type)__vector.size());
    X.F.push_back((typename T::value_type)__vector.capacity());
}

template <class T>
vecs<typename T::value_type> insert_n_range(T& __vector) {
	vecs<typename T::value_type> X;
	__vector.insert(__vector.begin(), 1, 4);
	__vector.push_back(1);
	__vector.push_back(2);
	__vector.push_back(3);
	Timer::Start();
	__vector.insert(__vector.begin() + 1, 1000000, 666666666);
    push_res(X, __vector);
	__vector.insert(__vector.end(), 1000000, 611111111);
    push_res(X, __vector);
	__vector.insert(__vector.end() - 10, 1000000, 8);
    push_res(X, __vector);
	__vector.insert(__vector.begin(), 1000000, 3);
    push_res(X, __vector);
	__vector.insert(__vector.begin() + 1, 10, 666666662);
    push_res(X, __vector);
	__vector.insert(__vector.end(), 10, 611111112);
    push_res(X, __vector);
	__vector.insert(__vector.end() - 10, 10, 81);
    push_res(X, __vector);
	__vector.insert(__vector.begin(), 10, 32);
    push_res(X, __vector);
	Timer::Stop();
	char buf[1024];
	long res = Timer::getRes();
	sprintf(buf, " %.3ld.%.3ld.%.3ldus", res / 1000000, res / 1000 % 1000, res % 1000);
	std::cout << std::string(buf);
	return X;
}

template <typename T>
void insert_n_test() {
	vecs<T> M;
	std::vector<T>&	A = M.S;
	ft::vector<T>&	B = M.F;
	vecs<T> Ax(insert_n_range(A));
	vecs<T> Bx(insert_n_range(B));
	std::cout << '\n';
	vec_equals(A, B);
	vec_equals(Ax.S, Bx.S);
	vec_equals(Ax.F, Bx.F);
	printV(Ax.S);
	std::cout << std::endl;
	printV(Bx.S);
	std::cout << std::endl;
}


template <class T>
void erase_iter_range(T& __vector) {
	std::vector<typename T::value_type> X;
	
	__vector.insert(__vector.begin(), 5, 5);
	__vector.insert(__vector.begin(), 5, 6);
	__vector.insert(__vector.begin(), 5, 7);
	__vector.insert(__vector.begin(), 5, 1);
	__vector.insert(__vector.begin(), 5, 2);
	__vector.insert(__vector.begin(), 5, 3);
	__vector.insert(__vector.begin(), 5, 8);
	X.push_back((typename T::value_type)__vector.size());
	X.push_back((typename T::value_type)__vector.capacity());
	std::cout << std::endl;
	printV(__vector);
	std::cout << std::endl;
	Timer::Start();
	__vector.erase(__vector.begin() + 7, __vector.begin() + 14);
	Timer::Stop();
	char buf[1024];
	long res = Timer::getRes();
	sprintf(buf, " %.3ld.%.3ld.%.3ldus", res / 1000000, res / 1000 % 1000, res % 1000);
	std::cout << std::string(buf);
}


template <typename T>
void erase_iter_range_test() {
	std::vector<T>	A;
	ft::vector<T>	B;
	erase_iter_range<std::vector<T> >(A);
	erase_iter_range<ft::vector<T> >(B);
	std::cout << '\n';
	vec_equals(A, B);
	printV(A);
	std::cout << std::endl;
	printV(B);
	std::cout << std::endl;
}

template <class T>
void insert_range(T& __vector) {
    T tempVec;
    tempVec.assign(2500, 1);
    for (int i = 1; i < 150000; ++i) {
        tempVec.push_back(i);
    }
    __vector.insert(__vector.begin(), tempVec.begin(), tempVec.end());
    __vector.insert(__vector.end() - 1000, tempVec.begin(), tempVec.end());
    __vector.insert(__vector.begin() + 5, tempVec.begin() + 9, tempVec.begin() + 12);
}

template <typename T>
void insert_test() {
    std::vector<T> A;
    ft::vector<T> B;
    insert_range(A);
    insert_range(B);
    vec_equals(A, B);

}

bool iterator_traits_test() {
	std::vector<std::string> res;
	std::vector<std::string> res2;

	res.push_back(typeid(std::vector<int>::iterator::iterator_category).name());
	res.push_back(typeid(std::vector<int>::iterator::value_type).name());
	res.push_back(typeid(std::vector<int>::iterator::difference_type).name());
	res.push_back(typeid(std::vector<int>::iterator::iterator_type).name());
	res.push_back(typeid(std::vector<int>::iterator::pointer).name());
	res.push_back(typeid(std::vector<int>::iterator::reference).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::iterator_category).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::value_type).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::difference_type).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::pointer).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::reference).name());

	res2.push_back(typeid(ft::vector<int>::iterator::iterator_category).name());
	res2.push_back(typeid(ft::vector<int>::iterator::value_type).name());
	res2.push_back(typeid(ft::vector<int>::iterator::difference_type).name());
	res2.push_back(typeid(ft::vector<int>::iterator::iterator_type).name());
	res2.push_back(typeid(ft::vector<int>::iterator::pointer).name());
	res2.push_back(typeid(ft::vector<int>::iterator::reference).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::iterator_category).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::value_type).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::difference_type).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::pointer).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::reference).name());

	if (res != res2) {
		printV(res);
		printV(res2);
	}
	
	return res == res2;

}

/* ----------------MAIN PART------------------- */

template <typename T>
void prepare_vec(T &A) {
	for (int i = 0; i < 100000; ++i) {
		A.push_back(3);
		A.push_back(5);
		A.push_back(7);
	}
}

template <typename T>
void push_info(T& A, std::vector<long>& res) {
	res.push_back(A.front());
	res.push_back(A.back());
	res.push_back(A.size());
	res.push_back(A.capacity());
}

/* push_back */

template <typename T>
long push_back_subtest(std::vector<long>& res) {
	T A;
	Timer::Start();
	prepare_vec(A);
	Timer::Stop();
	push_info(A, res);
	return Timer::getRes();
}

/* pop_back */

template <typename T>
long pop_back_subtest(std::vector<long>& res) {
	T A;
	prepare_vec(A);
	push_info(A, res);
	Timer::Start();
	for (int i = 0; i < 300000; ++i)
		A.pop_back();
	Timer::Stop();
	A.push_back(9);
	push_info(A, res);
	return Timer::getRes();
}


template <typename T>
long constructor_subtest(std::vector<long>& res) {
	T A;
	prepare_vec(A);
	Timer::Start();
	T B(A.begin(), A.end());
	Timer::Stop();
	push_info(A, res);
	return Timer::getRes();
}

template <typename T>
long size_subtest(std::vector<long>& res) {
	T A;
	prepare_vec(A);
	Timer::Start();
	A.size();
	Timer::Stop();
	push_info(A, res);
	return Timer::getRes();
}

template <typename T>
long iterators_subtest(std::vector<long>& res) {
	T A;
	prepare_vec(A);
	Timer::Start();
	A.begin();
	A.end();
	size_t x = A.begin() - A.end();
	typename T::iterator it = A.begin();
	it += 1000;
	int val = *it;
	res.push_back(val);
	res.push_back(x);
	res.push_back(*++it);
	Timer::Stop();
	(void)it;
	(void)val;
	(void)x;
	return Timer::getRes();
}

template <typename T>
long copy_subtest(std::vector<long>& res) {
	T A, B;
	prepare_vec(A);
	Timer::Start();
	B = A;
	Timer::Stop();
	push_info(B, res);
	return Timer::getRes();
}

template <typename T>
long element_access_subtest(std::vector<long>& res) {
	T A, B;
	prepare_vec(A);
	Timer::Start();
	int x = A[10];
	x = A.front;
	res.push_back(x);
	x = A.back;
	res.push_back(x);
	Timer::Stop();
	return Timer::getRes();
}

template <typename T>
long assign_subtest(std::vector<long>& res) {
	T A, B;
	prepare_vec(A);
	Timer::Start();
	B.assign(A.begin(), A.end());
	Timer::Stop();
	push_info(B, res);
	return Timer::getRes();
}

template <typename T>
long insert_iter_subtest(std::vector<long>& res) {
	T A, B;
	prepare_vec(A);
	prepare_vec(B);
	Timer::Start();
	B.insert(B.begin() + 10, A.begin() + 10, A.end() - 10);
	Timer::Stop();
	push_info(B, res);
	return Timer::getRes();
}

template <typename T>
long insert_subtest(std::vector<long>& res) {
	T A, B;
	prepare_vec(A);
	Timer::Start();
	B.insert(10, 10000, 8);
	Timer::Stop();
	push_info(B, res);
	return Timer::getRes();
}

template <typename T>
long erase_subtest(std::vector<long>& res) {
	T A;
	prepare_vec(A);
	Timer::Start();
	A.erase(A.begin() + 33);
	Timer::Stop();
	push_info(A, res);
	return Timer::getRes();
}

template <typename T>
long erase_iter_subtest(std::vector<long>& res) {
	T A;
	prepare_vec(A);
	Timer::Start();
	A.erase(A.begin() + 33, A.end() - 33);
	Timer::Stop();
	push_info(A, res);
	return Timer::getRes();
}

template <typename T>
long clear_subtest(std::vector<long>& res) {
	T A;
	prepare_vec(A);
	Timer::Start();
	A.clear();
	Timer::Stop();
	res.push_back(A.size());
	res.push_back(A.capacity());
	return Timer::getRes();
}

template <typename T>
long swap_subtest(std::vector<long>& res) {
	T A, B;
	prepare_vec(A);
	Timer::Start();
	A.swap(B);
	Timer::Stop();
	push_info(B, res);
	return Timer::getRes();
}

template <typename T>
long resize_subtest(std::vector<long>& res) {
	T A;
	prepare_vec(A);
	Timer::Start();
	A.resize(1000);
	Timer::Stop();
	push_info(A, res);
	return Timer::getRes();
}

template <typename T>
long reserve_subtest(std::vector<long>& res) {
	T A;
	prepare_vec(A);
	Timer::Start();
	A.reserve(1000000);
	Timer::Stop();
	push_info(A, res);
	return Timer::getRes();
}

template <typename T>
long compare_subtest(std::vector<long>& res) {
	T A;
	prepare_vec(A);
	Timer::Start();
	res.push_back(A[2] <  A[3]);
	res.push_back(A[4] <= A[5]);
	res.push_back(A[6] >  A[7]);
	res.push_back(A[8] >= A[9]);
	res.push_back(A[3] == A[1]);
	res.push_back(A[5] != A[3]);
	Timer::Stop();
	return Timer::getRes();
}

template <typename T>
long compare2_subtest(std::vector<long>& res) {
	T A;
	typename T::iterator it;
	typename T::iterator it2;
	typename T::const_iterator cit;
	prepare_vec(A);
	it = A.begin() + 100;
	it2 = A.begin() + 101;
	cit = A.begin() + 200;
	Timer::Start();
	res.push_back(it <  cit);
	res.push_back(it <= cit);
	res.push_back(it >  cit);
	res.push_back(it <= cit);
	res.push_back(it == cit);
	res.push_back(it != cit);
	res.push_back(it <  it2);
	res.push_back(it <= it2);
	res.push_back(it >  it2);
	res.push_back(it <= it2);
	res.push_back(it == it2);
	res.push_back(it != it2);
	Timer::Stop();
	return Timer::getRes();
}

/* map */

template <typename T>
void prepare_map(T& A) {
	for (int i = 0; i < 3000; ++i) {
		A[i] = 3 * i;
	}
	for (int i = 3000; i < 6000; ++i) {
		A[i] = i / 2;
	}
	for (int i = 6000; i < 10000; ++i) {
		A[i] = i - i / 2;
	}
}

template <typename T>
void push_map_info(T& A, std::vector<long>& res) {
	if (A.begin() != A.end()) {
		res.push_back(A.begin()->second);
		res.push_back((--A.end())->second);
	}
	res.push_back(A.size());
}

template <typename T>
long map_assign_index_subtest(std::vector<long>& res) {
	T A;
	Timer::Start();
	prepare_map(A);
	Timer::Stop();
	push_map_info(A, res);
	return Timer::getRes();
}


template <typename T>
long map_constructor_subtest(std::vector<long>& res) {
	T A;
	prepare_map(A);
	Timer::Start();
	T B(A);
	Timer::Stop();
	push_map_info(B, res);
	return Timer::getRes();
}

template <typename T>
long map_copy_subtest(std::vector<long>& res) {
	T A, B;
	prepare_map(A);
	Timer::Start();
	B = A;
	Timer::Stop();
	push_map_info(B, res);
	return Timer::getRes();
}

template <typename T>
long map_iterators_subtest(std::vector<long>& res) {
	T A;
	prepare_map(A);
	Timer::Start();
	A.begin();
	A.end();
	A.rbegin();
	A.rend();
	size_t x = A.size();
	typename T::iterator it = A.begin();
	for (int i = 0; i < 1000; ++i)
		++it;
	int val = it->second;
	Timer::Stop();
	res.push_back(val);
	res.push_back(x);
	res.push_back((++it)->second);
	(void)it;
	(void)val;
	(void)x;
	return Timer::getRes();
}

template <typename T>
long map_size_subtest(std::vector<long>& res) {
	T A;
	prepare_map(A);
	Timer::Start();
	A.size();
	Timer::Stop();
	push_map_info(A, res);
	return Timer::getRes();
}

template <typename T>
long map_clear_subtest(std::vector<long>& res) {
	T A;
	prepare_map(A);
	Timer::Start();
	A.clear();
	Timer::Stop();
	push_map_info(A, res);
	return Timer::getRes();
}

template <typename T>
long map_insert_subtest(std::vector<long>& res) {
	T A, B;
	prepare_map(A);
	Timer::Start();
	B.insert(*A.begin());
	Timer::Stop();
	push_map_info(B, res);
	return Timer::getRes();
}

template <typename T>
long map_insert_it_subtest(std::vector<long>& res) {
	T A, B;
	prepare_map(A);
	Timer::Start();
	B.insert(A.begin(), A.end());
	Timer::Stop();
	push_map_info(B, res);
	return Timer::getRes();
}

template <typename T>
long map_erase_subtest(std::vector<long>& res) {
	T A;
	prepare_map(A);
	Timer::Start();
	A.erase(A.begin());
	Timer::Stop();
	push_map_info(A, res);
	return Timer::getRes();
}

template <typename T>
long map_erase_it_subtest(std::vector<long>& res) {
	T A;
	prepare_map(A);
	Timer::Start();
	A.erase(A.begin(), A.end());
	Timer::Stop();
	res.push_back(A.size());
	return Timer::getRes();
}

template <typename T>
long map_erase_key_subtest(std::vector<long>& res) {
	T A;
	prepare_map(A);
	Timer::Start();
	A.erase(10);
	Timer::Stop();
	push_map_info(A, res);
	return Timer::getRes();
}

template <typename T>
long map_find_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_map(A);
	Timer::Start();
	x = A.find(10)->second;
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long map_count_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_map(A);
	Timer::Start();
	x = (int)A.count(10);
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long map_lower_bound_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_map(A);
	Timer::Start();
	x = A.lower_bound(10)->second;
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long map_upper_bound_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_map(A);
	Timer::Start();
	x = A.upper_bound(10)->second;
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long map_empty_subtest(std::vector<long>& res) {
	T A, B;
	int x, y;
	prepare_map(A);
	Timer::Start();
	x = A.empty();
	y = B.empty();
	Timer::Stop();
	res.push_back(x);
	res.push_back(y);
	return Timer::getRes();
}

template <typename T>
long map_swap_subtest(std::vector<long>& res) {
	T A, B;
	prepare_map(A);
	Timer::Start();
	A.swap(B);
	Timer::Stop();
	push_map_info(B, res);
	return Timer::getRes();
}

template <typename T>
long map_index_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_map(A);
	Timer::Start();
	x = A[10];
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long map_at_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_map(A);
	Timer::Start();
	x = A.at(10);
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long map_compare_subtest(std::vector<long>& res) {
	T A;
	prepare_map(A);
	Timer::Start();
	res.push_back(A[2] <  A[3]);
	res.push_back(A[4] <= A[5]);
	res.push_back(A[6] >  A[7]);
	res.push_back(A[8] >= A[9]);
	res.push_back(A[3] == A[1]);
	res.push_back(A[5] != A[3]);
	Timer::Stop();
	return Timer::getRes();
}

template <typename T>
void prepare_stk(T &A) {
	for (int i = 0; i < 100000; ++i) {
		A.push(3);
		A.push(5);
		A.push(7);
	}
}

template <typename T>
void push_stk_info(T& A, std::vector<long>& res) {
	res.push_back(A.top());
	res.push_back(A.size());
}

template <typename T>
long stack_size_subtest(std::vector<long>& res) {
	T A;
	prepare_stk(A);
	Timer::Start();
	A.size();
	Timer::Stop();
	push_stk_info(A, res);
	return Timer::getRes();
}

template <typename T>
long stack_top_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_stk(A);
	Timer::Start();
	x = A.top();
	Timer::Stop();
	push_stk_info(A, res);
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long stack_pop_subtest(std::vector<long>& res) {
	T A;
	prepare_stk(A);
	res.push_back(A.top());
	Timer::Start();
	A.pop();
	Timer::Stop();
	push_stk_info(A, res);
	return Timer::getRes();
}

template <typename T>
long stack_empty_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_stk(A);
	Timer::Start();
	x = A.empty();
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long stack_constructor_subtest(std::vector<long>& res) {
	T A;
	prepare_stk(A);
	Timer::Start();
	T B(A);
	Timer::Stop();
	push_stk_info(B, res);
	return Timer::getRes();
}

template <typename T>
long stack_copy_subtest(std::vector<long>& res) {
	T A, B;
	prepare_stk(A);
	Timer::Start();
	B = A;
	Timer::Stop();
	push_stk_info(B, res);
	return Timer::getRes();
}

template <typename T>
long stack_push_subtest(std::vector<long>& res) {
	T A;
	Timer::Start();
	prepare_stk(A);
	Timer::Stop();
	push_stk_info(A, res);
	return Timer::getRes();
}

template <typename T>
long stack_compare_subtest(std::vector<long>& res) {
	T A, B;
	prepare_stk(A);
	prepare_stk(B);
	Timer::Start();
	res.push_back(A <  B);
	res.push_back(A <= B);
	res.push_back(A >  B);
	res.push_back(A >= B);
	res.push_back(A == B);
	res.push_back(A != B);
	Timer::Stop();
	return Timer::getRes();
}

template <typename T>
void prepare_set(T& A) {
	for (int i = 0; i < 10000; ++i) {
		A.insert(i);
	}
}

template <typename T>
void push_set_info(T& A, std::vector<long>& res) {
	if (A.begin() != A.end()) {
		res.push_back(*A.begin());
		res.push_back(*--A.end());
	}
	res.push_back(A.size());
}

template <typename T>
long set_insert_subtest(std::vector<long>& res) {
	T A;
	Timer::Start();
	prepare_set(A);
	Timer::Stop();
	push_set_info(A, res);
	return Timer::getRes();
}

template <typename T>
long set_constructor_subtest(std::vector<long>& res) {
	T A;
	prepare_set(A);
	Timer::Start();
	T B(A);
	Timer::Stop();
	push_set_info(B, res);
	return Timer::getRes();
}

template <typename T>
long set_insert_it_subtest(std::vector<long>& res) {
	T A, B;
	prepare_set(A);
	Timer::Start();
	B.insert(A.begin(), A.end());
	Timer::Stop();
	push_set_info(B, res);
	return Timer::getRes();
}

template <typename T>
long set_empty_subtest(std::vector<long>& res) {
	T A;
	prepare_set(A);
	Timer::Start();
	res.push_back(A.empty());
	Timer::Stop();
	return Timer::getRes();
}

template <typename T>
long set_copy_subtest(std::vector<long>& res) {
	T A, B;
	prepare_set(A);
	Timer::Start();
	B = A;
	Timer::Stop();
	push_set_info(B, res);
	return Timer::getRes();
}

template <typename T>
long set_iterators_subtest(std::vector<long>& res) {
	T A;
	prepare_set(A);
	Timer::Start();
	A.begin();
	A.end();
	A.rbegin();
	A.rend();
	size_t x = A.size();
	typename T::iterator it = A.begin();
	for (int i = 0; i < 1000; ++i)
		++it;
	int val = *it;
	Timer::Stop();
	res.push_back(val);
	res.push_back(x);
	res.push_back(*++it);
	(void)it;
	(void)val;
	(void)x;
	return Timer::getRes();
}

template <typename T>
long set_erase_subtest(std::vector<long>& res) {
	T A;
	prepare_set(A);
	Timer::Start();
	A.erase(A.begin());
	Timer::Stop();
	push_set_info(A, res);
	return Timer::getRes();
}

template <typename T>
long set_erase_it_subtest(std::vector<long>& res) {
	T A;
	prepare_set(A);
	Timer::Start();
	A.erase(A.begin(), A.end());
	Timer::Stop();
	res.push_back(A.size());
	return Timer::getRes();
}

template <typename T>
long set_erase_key_subtest(std::vector<long>& res) {
	T A;
	prepare_set(A);
	Timer::Start();
	A.erase(10);
	Timer::Stop();
	push_set_info(A, res);
	return Timer::getRes();
}

template <typename T>
long set_find_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_set(A);
	Timer::Start();
	x = *A.find(10);
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long set_count_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_set(A);
	Timer::Start();
	x = (int)A.count(10);
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long set_lower_bound_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_set(A);
	Timer::Start();
	x = *A.lower_bound(10);
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long set_upper_bound_subtest(std::vector<long>& res) {
	T A;
	int x;
	prepare_set(A);
	Timer::Start();
	x = *A.upper_bound(10);
	Timer::Stop();
	res.push_back(x);
	return Timer::getRes();
}

template <typename T>
long set_swap_subtest(std::vector<long>& res) {
	T A, B;
	prepare_set(A);
	Timer::Start();
	A.swap(B);
	Timer::Stop();
	push_set_info(B, res);
	return Timer::getRes();
}

template <typename T>
long set_clear_subtest(std::vector<long>& res) {
	T A;
	prepare_set(A);
	Timer::Start();
	A.clear();
	Timer::Stop();
	res.push_back(A.size());
	return Timer::getRes();
}

template <typename T>
long set_size_subtest(std::vector<long>& res) {
	T A;
	prepare_set(A);
	Timer::Start();
	res.push_back(A.size());
	Timer::Stop();
	return Timer::getRes();
}

template <typename T>
long set_compare_subtest(std::vector<long>& res) {
	T A;
	prepare_set(A);
	T B(A);
	B.insert(999999999);
	Timer::Start();
	res.push_back(A <  B);
	res.push_back(A <= B);
	res.push_back(A >  B);
	res.push_back(A >= B);
	res.push_back(A == B);
	res.push_back(A != B);
	Timer::Stop();
	return Timer::getRes();
}

long test_form(const std::string& test_name, long (*subtest)(std::vector<long>& res), int x, std::vector<long>& res) {
	long sum = 0;
	for (int i = 0; i < x; ++i) {
		sum += subtest(res);
	}
	sum /= x;
	std::string temp(test_name + "(" + xstr(lib) + "):");
	char buf[100];
	sprintf(buf, "%-20s", temp.c_str());
	std::cout << buf << sum << '\n';
	return sum;
}

template <typename T>
void complex_test_vec() {
	std::vector<long> res;
	long time = 0;
	int test_count = 100;
	std::cout << "Vector\n";
	time += test_form("push_back", push_back_subtest<T>, test_count, res);
	time += test_form("pop_back", pop_back_subtest<T>, test_count, res);
	time += test_form("constructor", constructor_subtest<T>, test_count, res);
	time += test_form("size", size_subtest<T>, test_count, res);
	time += test_form("iterators", iterators_subtest<T>, test_count, res);
	time += test_form("copy", copy_subtest<T>, test_count, res);
	time += test_form("assign", assign_subtest<T>, test_count, res);
	time += test_form("insert(it)", insert_iter_subtest<T>, test_count, res);
	time += test_form("insert", insert_iter_subtest<T>, test_count, res);
	time += test_form("erase(it)", erase_iter_subtest<T>, test_count, res);
	time += test_form("erase", erase_subtest<T>, test_count, res);
	time += test_form("clear", clear_subtest<T>, test_count, res);
	time += test_form("swap", swap_subtest<T>, test_count, res);
	time += test_form("resize", resize_subtest<T>, test_count, res);
	time += test_form("reserve", reserve_subtest<T>, test_count, res);
	time += test_form("compare", compare_subtest<T>, test_count, res);
	time += test_form("compare2", compare2_subtest<T>, test_count, res);
	std::cout << "Total: " << time << "\n\n";
	printV(res);
}

template <typename T>
void complex_test_stack() {
	std::vector<long> res;
	long time = 0;
	int test_count = 100;
	std::cout << "Stack\n";
	time += test_form("size", stack_size_subtest<T>, test_count, res);
	time += test_form("push", stack_push_subtest<T>, test_count, res);
	time += test_form("pop", stack_pop_subtest<T>, test_count, res);
	time += test_form("top", stack_top_subtest<T>, test_count, res);
	time += test_form("constructor", stack_constructor_subtest<T>, test_count, res);
	time += test_form("copy", stack_copy_subtest<T>, test_count, res);
	time += test_form("compare", stack_compare_subtest<T>, test_count, res);
	std::cout << "Total: " << time << "\n\n";
	printV(res);
}

template <typename T>
void complex_test_map() {
	std::vector<long> res;
	long time = 0;
	int test_count = 100;
	std::cout << "Map\n";
	time += test_form("assign_index", map_assign_index_subtest<T>, test_count, res);
	time += test_form("constructor", map_constructor_subtest<T>, test_count, res);
	time += test_form("copy", map_copy_subtest<T>, test_count, res);
	time += test_form("iterators", map_iterators_subtest<T>, test_count, res);
	time += test_form("size", map_size_subtest<T>, test_count, res);
	time += test_form("clear", map_clear_subtest<T>, test_count, res);
	time += test_form("insert", map_insert_subtest<T>, test_count, res);
	time += test_form("insert(it)", map_insert_it_subtest<T>, test_count, res);
	time += test_form("erase", map_erase_subtest<T>, test_count, res);
	time += test_form("erase(key)", map_erase_key_subtest<T>, test_count, res);
	time += test_form("erase(it)", map_erase_it_subtest<T>, test_count, res);
	time += test_form("count", map_count_subtest<T>, test_count, res);
	time += test_form("find", map_find_subtest<T>, test_count, res);
	time += test_form("upper_bound", map_upper_bound_subtest<T>, test_count, res);
	time += test_form("lower_bound", map_lower_bound_subtest<T>, test_count, res);
	time += test_form("empty", map_empty_subtest<T>, test_count, res);
	time += test_form("swap", map_swap_subtest<T>, test_count, res);
	time += test_form("at", map_at_subtest<T>, test_count, res);
	time += test_form("operator[]", map_index_subtest<T>, test_count, res);
	time += test_form("compare", map_compare_subtest<T>, test_count, res);
	std::cout << "Total: " << time << "\n\n";
	printV(res);
}

template <typename T>
void complex_test_set() {
	std::vector<long> res;
	long time = 0;
	int test_count = 100;
	std::cout << "Set\n";
	time += test_form("insert", set_insert_subtest<T>, test_count, res);
	time += test_form("constructor", set_constructor_subtest<T>, test_count, res);
	time += test_form("insert(it)", set_insert_it_subtest<T>, test_count, res);
	time += test_form("empty", set_empty_subtest<T>, test_count, res);
	time += test_form("copy", set_copy_subtest<T>, test_count, res);
	time += test_form("iterators", set_iterators_subtest<T>, test_count, res);
	time += test_form("erase", set_erase_subtest<T>, test_count, res);
	time += test_form("erase(key)", set_erase_key_subtest<T>, test_count, res);
	time += test_form("erase(it)", set_erase_it_subtest<T>, test_count, res);
	time += test_form("count", set_count_subtest<T>, test_count, res);
	time += test_form("find", set_find_subtest<T>, test_count, res);
	time += test_form("upper_bound", set_upper_bound_subtest<T>, test_count, res);
	time += test_form("lower_bound", set_lower_bound_subtest<T>, test_count, res);
	time += test_form("swap", set_swap_subtest<T>, test_count, res);
	time += test_form("size", set_size_subtest<T>, test_count, res);
	time += test_form("clear", set_clear_subtest<T>, test_count, res);
	time += test_form("compare", set_compare_subtest<T>, test_count, res);
	
	std::cout << "Total: " << time << "\n\n";
	printV(res);
}


int main() {
/* vector insert test & traits
	std::cout << "\tSTD\t\tFT" << std::endl;
	insert_n_test<int>();
	erase_iter_range_test<int>();
	std::cout << std::endl;
    insert_test<int>();
	iterator_traits_test();
 */

	complex_test_vec<_vector<int> >();
	complex_test_map<_map<int, int> >();
	complex_test_stack<_stack<int> >();
	complex_test_set<_set<int> >();
}
