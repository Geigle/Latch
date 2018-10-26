/*!
 * 	\file	latch-example.cpp
 * 	\brief	An example usage of the latch class.
 */

#include <iostream>
#include <string>
#include "../latch.h"

using namespace std;

int num(int number)
{
    return number;
}

std::string echo(string str)
{
    return str;
}

void printOut(string str)
{
    cout << str << endl;
}

int int_printOut(string str)
{
    printOut(str);
    return 0;
}

int printIt(string str)
{
    cout << str << endl;
    return 0;
}


int main()
{
    /* A latch can have two actions, one is activated with set(), the other
     * with unset(). */
    Latch<int, int> i(num, num);

    /* In this example, set() will call num(5). */
    i.set(5);
    cout << "i.set(5): " << (i.flipped() ? i.result() : (-1)) << endl;

    /* With the latch already set, nothing will happen. */
    i.set(6);
    cout << "i.set(6): " << (i.flipped() ? i.result() : (-1)) << endl;

    /* While the latch is set, unset() will execute num(4); */
    i.unset(4);
    cout << "i.unset(4): " << (i.flipped() ? i.result() : (-1)) << endl;


    /* A latch may optionally have only a single action, under set(). */
    Latch<string, string> s(echo);

    s.set("Hello World");
    cout << "s.set(\"Hello World\"):" << (s.flipped() ? s.result() : "No Flip")
         << endl;
    s.set("Goodbye World");
    cout << "s.set(\"Goodbye World\"):" << (s.flipped() ? s.result() : "No Flip")
         << endl;

    /* Since unset() will do nothing, an empty string will print from line 53. */
    s.unset("Herpdy Derp");
    cout << "s.unset(\"Herpdy Derp\"):" << (s.flipped() ? s.result() : "No Flip")
         << endl;

    /* You aren't required to use the output of a function, such as printIt(). */
    Latch<int, string> pi(printIt, printIt);
    pi.set("printIt");
    pi.set("printIt also");
    pi.unset("finally, printIt");

//  /* A latch is a templated class, and so may not use the type "void". */
//	Latch<void, string> po(printOut, printOut);	/*	Deleting "void*" is undefined.
//	                                            Invalid use of "void".
//	                                            "void*" is not a
//	                                                pointer-to-object type. */
//
//	po.set("printOut");
//	po.set("printOut also");
//	po.unset("finally, printOut");

    /* However, you can encapsulate it in a function that doesn't return "void".
    (see line 27) */
    Latch<int, string> po(int_printOut, int_printOut);

    po.set("printOut");
    po.set("printOut also");
    po.unset("finally, printOut");


    return 0;
}
