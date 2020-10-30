#include <iostream>
#include "allocator.cpp"

size_t		testCanCreate()
{
	Allocator	a;

	a.makeAllocator(1);
	return (a.alloc(1) == nullptr);
}

size_t		testDoubleCheck()
{
	Allocator	a;
	char*		p;

	a.makeAllocator(2);
	p = a.alloc(1);
	return ((a.alloc(1) - p) != 1);
}

size_t		testRealloc()
{
	Allocator	a;
	char*		p1;
	char*		p2;

	a.makeAllocator(2);
	p1 = a.alloc(1);
	a.makeAllocator(2);
	p2 = a.alloc(1);
	return ((p2 - p1) != 1);
}

size_t		testRemake()
{
	Allocator	a;
	char*		p1;
	char*		p2;

	a.makeAllocator(8);
	p1 = a.alloc(4);
	a.reset();
	p2 = a.alloc(1);
	return (p2 != p1);
}


/*
size_t		test2Big()
{
	Allocator	a;

	a.makeAllocator(0xFFFFFFFF);
	return (a.alloc(1) != nullptr);
}
*/

size_t		testBound()
{
	Allocator	a;

	a.makeAllocator(1);
	return (a.alloc(2) != nullptr);
}

size_t		testBound2()
{
	Allocator	a;
	char*		p1;
	char*		p2;

	a.makeAllocator(2);
	p1 = a.alloc(1);
	p2 = a.alloc(2);
	return ((p1 == nullptr) or (p2 != nullptr));
}

void		printErrorState(size_t e)
{
	if(e)
		std::cout << "TEST IS FAILED." <<std::endl;
	else
		std::cout << "TEST IS OK." << std::endl;
}

int		main()
{
	size_t		errs = 0;
	size_t		curr = 0;

	std::cout << "============================ Starting tests ============================" << std::endl;
	std::cout << std::endl;

	curr = testCanCreate();
	errs += curr;
	std::cout << "		Allocator is creating 1-element seq: ";
	printErrorState(curr);

	curr = testDoubleCheck();
	errs += curr;
	std::cout << "		Allocator is creating 2-element seq and alloc twice: ";
	printErrorState(curr);

	curr = testRealloc();
	errs += curr;
	std::cout << "		Allocator is creating 2-element seq and try makeAllocator twice: ";
	printErrorState(curr);

	curr = testRemake();
	errs += curr;
	std::cout << "		Allocator is creating seq alloc and reset: ";
	printErrorState(curr);

	curr = testBound();
	errs += curr;
	std::cout << "		Allocator can not alloc outside the seq: ";
	printErrorState(curr);

	curr = testBound2();
	errs += curr;
	std::cout << "		Allocator can not alloc outside the seq after successfull alloc: ";
	printErrorState(curr);

	std::cout << "========================== Finished with "<< errs <<" errors =========================" << std::endl;

	return 0;
}
