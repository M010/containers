
namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2  second_type;
		T1 first;
		T2 second;

		pair(): first(), second() {}

		template<class T, class U>
		pair (const T& a, const U& b): first(a), second(b) {}

		template<class T, class U>
		pair& operator=(const pair<T, U>& other) {
			if(*this != &other)
			{
				first = other.first;
				second = other.second;
			}
			return *this;
		}

		template<class T, class U>
		pair(const pair<T, U>& other) : first(other.first), second(other.second) {
		}

		bool operator==(const pair &rhs) const;
//		bool operator!=(const pair &rhs) const;
//		bool operator<(const pair &rhs) const;
//		bool operator>(const pair &rhs) const;
//		bool operator<=(const pair &rhs) const;
//		bool operator>=(const pair &rhs) const;
	};

//	template<class T1, class T2>
//	bool pair<T1, T2>::operator<(const pair &rhs) const
//	{
//		if (first < rhs.first)
//			return true;
//		if (rhs.first < first)
//			return false;
//		return second < rhs.second;
//	}
//
//	template<class T1, class T2>
//	bool pair<T1, T2>::operator>(const pair &rhs) const
//	{
//		return rhs < *this;
//	}
//
//	template<class T1, class T2>
//	bool pair<T1, T2>::operator<=(const pair &rhs) const
//	{
//		return !(rhs < *this);
//	}
//
//	template<class T1, class T2>
//	bool pair<T1, T2>::operator>=(const pair &rhs) const
//	{
//		return !(*this < rhs);
//	}

//	template<class T1, class T2>
//	bool pair<T1, T2>::operator==(const pair &rhs) const
//	{
//		return first == rhs.first &&
//			   second == rhs.second;
//	}
//
//	template<class T1, class T2>
//	bool pair<T1, T2>::operator!=(const pair &rhs) const
//	{
//		return !(rhs == *this);
//	}


	template< class T1, class T2 >
	pair<T1,T2> make_pair(T1 t, T2 u)
	{
		return pair<T1, T2>(t, u);
	}

}

