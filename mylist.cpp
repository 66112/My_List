#include "mylist.h"
using namespace Cbx;


void Test1()
{
	Cbx::MyList<int> l1;
	Cbx::MyList<int> l2(50);
	Cbx::MyList<int> l3(5,100);
	l1 = l3;
	Cbx::MyList<int>::Print(l2);
	Cbx::MyList<int>::Print(l3);
}
void Test2()
{
	Cbx::MyList<int> l1(5, 100);
	Cbx::MyList<int>::iterator pos = l1.Begin();
	pos = l1.Insert(pos, 20);
	Cbx::MyList<int>::Print(l1);
	l1.Erase(pos);
	Cbx::MyList<int>::Print(l1);
	
}
void Test3()
{
	Cbx::Date d1(1999, 6, 11);
	Cbx::Date d2(2000, 11, 11);
	Cbx::Date d3(2001, 8, 20);

	Cbx::MyList<Cbx::Date> ld(d1);
	ld.Push_Back(d2);
	ld.Push_Back(d3);

	Cbx::MyList<Cbx::Date>::Print(ld);
	MyList<Date>::iterator it = ld.Begin();
	Printf(ld);
}
int main()
{
	//Test1();
	//Test2();
	Test3();
	return 0;
}