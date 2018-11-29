#ifndef __MYLIST_H__
#define __MYLIST_H__
#include <iostream>
namespace Cbx
{
	using namespace std;
	class Date
	{
	public:
		Date(const Date& d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		Date(int year =2018, int month=11, int day=28)
		{
			_year = year;
			_month = month;
			_day = day;
		}
	friend static std::ostream& operator<<(std::ostream& out, const Date& d);

	public:
		int _year;
		int _month;
		int _day;
	};
	static std::ostream& operator<<(std::ostream& out, const Date& d)
	{
		out << d._year << "-" << d._month << "-" << d._day;
		return out;
	}
	
	template<class T>
	struct Node
	{
		Node<T>* _prev;
		Node<T>* _next;
		T _data;
		Node(const T& data = T())
			:_data(data)
			, _prev(nullptr)
			, _next(nullptr)
		{}
	};
	
	template<class T, class Ref, class Ptr>
	struct ListIterator
	{
		typedef Node<T> Node;
		typedef ListIterator<T, Ref, Ptr> Self;   //自己是一个迭代器
		Node* _pNode;                //成员变量，是一个节点的指针

		ListIterator(Node* node)
			:_pNode(node)
		{}

		Ref operator* ()            //返回的是引用
		{
			return _pNode->_data;
		}
		Ptr operator->()            //返回的是指针，
		{
			return &_pNode->_data;
		}
		Self operator++()           //前置++ ，++it; it.operator++(&it)
		{
			_pNode = _pNode->_next;
			return *this;
		}
		Self operator++(int)
		{
			Self tmp(*this);
			_pNode = _pNode->_next;
			return tmp;
		}
		Self operator--()
		{
			_pNode = _pNode->_prev;
			return *this;
		}
		Self operator--(int)
		{
			Self tmp(*this);
			_pNode = _pNode->_prev;
			return tmp;
		}
		bool operator!=(const Self& it)
		{
			return _pNode != it._pNode;
		}
		bool operator==(const Self& it)
		{
			return _pNode == it._pNode;
		}
	};

	template<class T>
	class MyList
	{
		typedef Node<T> Node;               //节点
	public:
		typedef ListIterator<T, T&, T*> iterator;       // 普通迭代器
		typedef ListIterator<T, const T&, const T*> const_iterator;
		MyList()
			:_head(new Node)
			, _sz(0)
		{
			_head->_next = _head;
			_head->_prev = _head;
		}
		MyList(const T& data)
			:_head(new Node)
			, _sz(0)
		{
			_head->_next = _head;
			_head->_prev = _head;
			Push_Back(data);
		}
		MyList(const MyList<T>& l)
			:_head(new Node)
			, _sz(0)
		{
			_head->_next = _head;
			_head->_prev = _head;
			const_iterator first = l.cBegin();
			while (first != l.cEnd())
			{
				Push_Back(*first);
				first++;
			}
		}
		MyList(size_t num, const T& data)
			:_head(new Node)
			, _sz(0)
		{
			_head->_next = _head;
			_head->_prev = _head;
			while (num--)
			{
				Push_Back(data);
			}
		}
		MyList(iterator first, iterator last)
			:_head(new Node)
			, _sz(0)
		{
			_head->_next = _head;
			_head->_prev = _head;
			while (first != last)
			{
				Push_Back(*first);
				first++;
			}
		}

		~MyList()
		{
			Clear();
			delete _head;
			_head = nullptr;
		}
		MyList<T>& operator=(MyList<T> l)  
		{
			swap(this->_head, l._head);
			swap(this->_sz, l._sz);
			return *this;
		}
		iterator Insert(iterator pos, const T& data)
		{
			Node* newnode = new Node(data);
			Node* prev = pos._pNode->_prev;
			Node* cur = pos._pNode;
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			_sz++;
			return iterator(newnode);
		}
		iterator Erase(iterator pos)
		{
			Node* prev = pos._pNode->_prev;
			Node* next = pos._pNode->_next;
			prev->_next = next;
			next->_prev = prev;
			delete pos._pNode;
			_sz--;
			return iterator(next);
		}
		iterator Begin()
		{
			return iterator(_head->_next);
		}
		iterator End()
		{
			return iterator(_head);
		}
		const_iterator cBegin()  const     //迭代器不可修改
		{
			return const_iterator(_head->_next);
		}
		const_iterator cEnd()  const
		{
			return const_iterator(_head);
		}
		void Clear()
		{
			iterator it = Begin();
			while (it != End())
			{
				iterator del = it;
				it++;
				delete del._pNode;
				del._pNode = nullptr;
				_sz--;
			}
			_head->_next = _head;
			_head->_prev = _head;
		}
		void Push_Back(const T& data)
		{
			Insert(End(), data);
		}
		void Pop_Back()
		{
			Erase(--End());
		}
		void Push_Front(const T& data)
		{
			Insert(Begin(), data);
		}
		void Pop_Front()
		{
			Erase(Begin());
		}
		size_t Size()
		{
			return _sz;
		}
		bool Empty()
		{
			return _sz == 0;
		}

		static void Print(const MyList<T>& l)
		{
			MyList<T>::const_iterator it = l.cBegin();
			while (it != l.cEnd())
			{
				cout << (it._pNode)->_data << "->";    //节点的指针 it._pNode, it是一个迭代器的对象
				it++;
			}
			cout << "head" << endl;
		}
		
	private:
		Node* _head;
		size_t _sz;
	};
	
	void Printf(MyList<Date>& l)
	{
		MyList<Date>::iterator it = l.Begin();
		while (it != l.End())
		{
			//cout << (it._pNode)->_data << "->";    //节点的指针 it._pNode, it是一个迭代器的对象
			cout << it->_day << "->";          
			cout << (*it)._year << "->";
			it++;
		}
		cout << "head" << endl;
	}
}
#endif // __MYLIST_H__
