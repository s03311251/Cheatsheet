#include <iostream>
using namespace std;

/*----------print----------*/

/* special symbol */
	"\a" //alert (bell) character 
	"\b" //backspace 
	"\n" = 12 = 0x0A //newline 
	"\r" //carriage return
	"\t" //horizontal tab
	"\v" //vertical tab
	"\\" //backslash
	"\?" //question mark
	"\'" //single quote
	"\"" //double quote

/* ASCII */
	'0'=48; '9'=57;
	'A'=65;	'Z'=90;
	'a'=97;	'z'=122;
/* oct, dec, hex */
    int n = 70;
    std::cout << std::dec << n << '\n'; // 70
    std::cout << std::hex << n << '\n'; // 46
    std::cout << std::oct << n << '\n'; // 106


/*----------continue----------*/
// In for-loop, i++ still being executed after continue


/*----------pass by reference----------*/
void loadProducts(Database &d, string fileName) //"&" here

/*----------switch----------*/
	switch(grade) //bool,int,char only
	{
		case 'A':
			cout << "Excellent!\n";
			break;
		case 'B':
			break;
		default:
			cout << "Invalid grade\n";
			/* Made for Misra-C Compliance. */
        	break;
	}

/*----------float----------*/
	// Infinity
#include <iostream>
#include <cmath>

int main() {
	double a = 10;
	double b = 0;
	a = a/b;
	if (a == INFINITY) {
		std::cout << "Beyond the time!\n";
	}
	return 0;
}



/*----------array----------*/
	double price[] = {1,2,3}; //become price[3]
	double price[5] = {1,2}; //become {1,2,0,0,0}

	// 2D array: x[2nd dimension][1st dimension]
	int x[3][2] = {
		{1,2},
		{3,4},
		{5,6}
	};

/*----------selection sort----------*/
void swap (int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void sort(int a[], int size)
{
	int min;
	int slotIdOfMin;
	for (int i=0;i<size-1;i++)
	{
		min = a[i];
		slotIdOfMin = i;
		for (int j=i;j<size;j++)
		{
			if (a[j]<min)
			{
				min = a[j];
				slotIdOfMin = j;
			}
		}
		swap (a[i],a[slotIdOfMin]);
	}
}

/*----------string----------*/
	//get a string and save in xxx, ignoring space
	getline(cin,xxx); // cin<="Chris Wong" => xxx="Chris Wong"

	//addition
	string a = "a";
	string b = "b";
	string result = a+b; //result = "ab"

	//operator >, operator <
	//compare lexicographically (Capital letters first)

	//return number of element
	xxx.size();
	xxx.length();

	//return true if empty
	xxx.empty();

	//return a substring starting from 0th having length of 10
	xxx.substr(0,10);
	xxx.substr(0); //from 0th to the end

	//search and return position of str at the string
	//-1 if no occurence
	xxx.find(str); // eg. "XXstrXXX" => return 2
	xxx.find(str,pos); //search characters only at or after pos

	//search and return the last occurrence
	xxx.rfind(str);

	//insert content specified and return the resultant string
	xxx.insert(3,str); //eg. "ABCDE" => "ABCDstrE"

	//erase 2 characters starting at 8th and return the resultant string
	xxx.erase(8,2); //eg. "Dirk is unhappy" => "Dirk is happy"

	//replace 7 characters starting at 8th by content "very happy" and return the resultant string
	xxx.replace(8,7,"very happy"); //eg "Dirk is unhappy." => "Dirk is very happy."

	//assign 6 characters starting at 5th to xxx
	xxx.assign("caterpillar", 5, 6); //xxx = "pillar"

/*----------file I/O----------*/
#include <fstream>

	//Declare a ifstream
	ifstream fin;

	//Open file
	fin.open("/(location)");
	//can written as
	ifstream fin("/(location)");

	//Open file with string
	string s= "/(location)";
	fin.open(s.c_str());

	//Check if fails => return 1
	//Also fails when get to end of file
	if (fin.fail())
	{
		cout << "Error\n";
	}

	//Read content
	fin >> a; /*space and \n -> new item
				if it has read the end of the file, fin will always give the last string*/
	fin.ignore(); //if fin before: not to include space before the string; no need for newline
	getline(fin,xxx); //cin<="Chris Wong" => xxx="Chris Wong"

	//Check if is end of file in the previous reading=> return 1
	if (fin.eof())
	{
		cout << "End\n";
	}

	//Close file
	fin.close();

--------------------
	//declare an ofstream
	ofstream fout;

	//Open file
	fout.open("/(location)");
	//Open file with string
	string s= "/(location)";
	fin.open(s.c_str());
	/*new file will be created
	content of the existing file will be erased*/
	//Open file while keeping original data
	fout.open("\(location)", ios::app);

	//Write content
	fout << a;

	//Close file
	fin.close();

/*----------structure----------*/
struct Product
{
	string name;
	double price;
	void someFunction()
		{
			price++;
		}
}; //there is ";" here

int main()
{
	//declare variable of this structure type
	Product p1,p2;
	Product p1 = {"Chicken",20}; //can't do this after declaration
	//declare an array of struct
	Product p[3];
	Product p[3] = {{"Chicken",20},{"Banana",3.2},{"Dirk",1024}};

	//access members
	p1.name = "Chicken";
	p1.price = 20;

	//copy
	p2 = p1; //other operators (like +, *, >, ==) don't work

}

/*----------pointer----------*/
	int aaa = 25;
	//reference operator
	xxx = &aaa; //eg. xxx = 1776;
	//dereference operator
	yyy = *xxx; //eg. yyy = 25;

	//declare pointer
	int *ip;

	//eg. with string
	string name("Chris Wong");
	string *sp = &name;
	cout << (*sp)[3]; //print "i"

	//eg. with struct
	Product p1 = {"Chicken",20};
	Product *pp = &p1;
	cout << (*pp).price; //print 20
	cout << pp->price; //the same
	//當(*pp)就係嗰個variable就得㗎啦

	//eg. with array
	double a[4] = {1,2,3,4};
	double *p = a; //no & here //p points at a[0] //array is a pointer?!
	cout << *(p+1); //print a[1] = 2 
	//個+1唔係真係+1，例如int係+4，double係+8
	//even p++ 都係+4/+8...

	//initialise as NULL=0
	int *ip = NULL;

--------------------
	//dynamic variables
	int *p;
	p = new int; //new address is allocated
	*p = 8;
	delete p; //value of pointer become invalid = dangling pointer
	//if we move away p before delete-> inaccessible = memory leak

	//dynamically allocated arrays
	int *p;
	p = new int[3];
	p[0]=0; //no * here
	p[1]=1;
	p[2]=2;
	delete []p;

	//dynamic arrays
string *addEntry(string *array, int &size, string newEntry)
{
	string *tmp = new string[size];
	for (int i=0;i<size;i++)
		tmp[i] = array[i];
	delete[] array;
	
	array = new string[size+1];
	for (int i=0;i<size;i++)
		array[i] = tmp[i];
	array[size] = newEntry;
	size++;
	return array;
}

string *deleteEntry(string *array, int &size, string entryToDelete)
{
	int index = -1;
	for (int i=0;i<size;i++)
		if (array [i]==entryToDelete) index = i;
	if (index == -1) return array;

	string *newArray = new string[size-1];
	
	for (int i=0;i<index;i++)
		newArray[i] = array[i];
	for (int i=index+1;i<size;i++)
		newArray[i-1] = array[i];
	delete[] array;
	size--;
	return newArray;
}

int main(){
	int size = 3;
	string *list = new string[size];
	list[0] = "a";
	list[1] = "b";
	list[2] = "c";
	list = addEntry(list,size,"ddd");
	cout << list [3]; //print "ddd"
	list = deleteEntry(list,size,"b");
	cout << list [1]; //print "c"
	return 0;
}

/*----------linked list----------*/
struct Product
{
	string name;
	double price;
	Product *next; //<=========
};

	//insert at the head
Product *insert(Product *head, string name, double price)
{
	Product *p = new Product; //1. creat a new node
	p->name = name;
	p->price = price;
	p->next = head; //2. new node's next is the first node
	head = p; //3. head points to the new node
	return head;
}

	//search
void search(Product *head, string searchName)
{
	Product *current; //1. create a pointer current
	current = head; //2. initialize current = head
	while (current !=NULL) 
	{
		if (current->name == searchName)
			cout << current->price << endl;
		current = current->next; //3. traverse the linked list by: current = current->next
	}
}

	//remove


//3. remove the node: delete current

void remove(Product *&head, string n)
{
	Product *current, *previous; //1. create 2 pointers current, previous
	previous = NULL;
	current = head;
	//2. search for the node to delete, and update the pointers; previous->next=current->next
	if (current->name == n) 
	{
		head = current->next;
		delete current;
		return;
	}
	while (current!=NULL)
	{
		if (current->name == n)
		{
			previous->next = current->next;
			delete current;
			return;
		}
		previous = current;
		current = current->next;
	}
}

	//make use of the linked list
void print(Product *head) //<=========
{
	for (Product *current=head;current!=NULL;)
	{
		cout << current->name << ": "<< current->price << endl;
		current = current->next; //traverse the linked list by: current = current->next
	}
}

int main()
{
	Product *head = NULL; //<=========
	head = insert(head, "Chicken", 20);
	head = insert(head, "Milk", 6.5);
	head = insert(head, "Chocolate", 10);
	print(head);
}

/*----------static cast----------*/
	int myint =10;
	cout << static_cast<float>(myint) / 3; //output 3.33333
	cout << (float) myint/3; // old-fashion

/*----------GetAsyncKeyState---------*/
#include <windows.h>

	//has UP button clicked before
	GetAsyncKeyState(VK_UP); //=1
	/*VK_UP Up key
	VK_DOWN Down key
	VK_LEFT Left key
	VK_RIGHT Right key
	VK_LSHIFT Left-shift key
	VK_RSHIFT Right-shift key*/

	//sleep for n milliseconds
	Sleep(1000);

/*----------sort----------*/
#include <algorithm>

struct Products
{
	double unitPrice;
	string name;
};

bool acompare(Products lhs, Products rhs)
{
	return (lhs.unitPrice < rhs.unitPrice); 
}

int main()
{
	Products array[3]=
	{
		{5,"a"},
		{435,"B"},
		{-7,"CC"},
	};
	sort(array, array+3, acompare);
}

/*----------get bit-by-bit data----------*/
//bit masking is used
	int n = 13;
	for (int i=3;i>=0;i--)
	cout << ((n >> i) & 1); //get the i-th bit of n
	//
	//get 1101

/*----------class----------*/
/*	e.g. main.cpp + BigInteger.h + BigInteger.cpp
	compile in Linux:
		g++ main.cpp BigInteger.cpp
	compile -> main.o
	linker -> links main.o and BigInterger.o

	Capitalize user-defined class name*/

//BjgInteger.h (header file)
#include <string>
using namespace std;
class BigInteger{
//can access member variables by "." and can call the member function by "."
	public:
		BigInteger(string number);	//constructor: usage: BigInteger a(string);
		void setNumber(string);
		string getNumber() const;	//const -> the function cannot modify member variable
//accessed only by the member functions (eg. setNumber(), getNumber()) of the class
//無寫當private
	private:
		char sign;
		int length;
		int value[100];
	friend BigInteger add(const BigInteger &a, const BigInteger &b);
	friend BigInteger operator+( const BigInteger & a, const BigInteger & b );
	friend istream & operator>>( istream& cin, BigInteger& b ); 
	friend ostream & operator<<( ostream &cout, BigInteger &b );
}; //!!!!! ; after it

BigInteger add(const BigInteger &a, const BigInteger &b);	//const & -> no modify the variable
istream & operator>>( istream &cin, BigInteger &b ); 
ostream & operator<<( ostream &cout, BigInteger &b );
BigInteger operator+( const BigInteger &a, const BigInteger &b );
void operator+=( const BigInteger &a, const BigInteger &b );

//BigInteger.cpp (implementation file)
#include <iostream>
#include <string>
//We need to also include the header file BigInteger.h in the implementation file BigInteger.cpp.
#include "BigInteger.h"
using namespace std;

// the scope resolution operator :: indicates that we are defining a member function of the class BigInteger

// Constructor
// usage: BigInteger a("123456");
// !!!!! BigInteger:: here
BigInteger::BigInteger(string number){
	 if( number[0]=='-' ){
		sign='-';
		number = number.substr( 1 );
	}else{
		sign = '+';
	}
	length = number.length();
	int j = 0;
	for( int i=number.length()-1; i>=0; i-- ){
		value[j] = number[i]-'0';
		j++;
	}
}

void BigInteger::setNumber(string number){
	 if( number[0]=='-' ){
		sign='-';
		number = number.substr( 1 );
	}else{
		sign = '+';
	}
	length = number.length();
	int j = 0;
	for( int i=number.length()-1; i>=0; i-- ){
		value[j] = number[i]-'0';
		j++;
	}
}

string BigInteger::getNumber() const{
	string s;
	s = s + (sign=='-'?"-":"");
	for( int i=length-1; i>=0; i-- )
		s = s + (char)(value[i]+'0');
	return s;
}

istream & operator>>( istream &cin, BigInteger &b ){
	string s;
	cin >> s;
	b.setNumber( s );
	return cin;
} 

ostream & operator<<( ostream &cout, BigInteger &b ){
	cout << b.getNumber();
	return cout;
} 

BigInteger operator+( const BigInteger &a, const BigInteger &b ){
	BigInteger c;
	if( a.sign=='+' && b.sign=='+' ){
		c.sign = '+';
		int carry = 0;
		int i;
		for( i = 0 ; i<a.length || i<b.length; i++ ){
			c.value[i] = ( (i<a.length?a.value[i]:0) + (i<b.length?b.value[i]:0) + carry )%10;
			carry = ( (i<a.length?a.value[i]:0) + (i<b.length?b.value[i]:0) + carry )/10;
		}
		if( carry > 0 ){
			c.value[i] = carry;
			i++;
		}
		c.length = i;
		return c;
	}
	else if( a.sign=='-' && b.sign=='-' ){
		BigInteger a2 = a;
		a2.sign = '+';
		BigInteger b2 = b;
		b2.sign = '+';
		c = a2 + b2;
		c.sign = '-';
		return c;
	}
	else if( a.sign=='+' && b.sign=='-' ){
		int carry = 0;
		int i;
		for( i = 0 ; i<a.length || i<b.length; i++ ){
			//we first borrow 10 from the digit on the left and find the difference
			c.value[i] = ( (i<a.length?a.value[i]:0) + 10 - (i<b.length?b.value[i]:0) + carry )%10;
			//Since we have borrowed 10 from the digit on the left,
			//the carry is one less than the original carry
			carry = ( (i<a.length?a.value[i]:0) + 10 - (i<b.length?b.value[i]:0) + carry )/10 - 1;
		}
		c.sign = '+';
		c.length = i;
		while( c.value[c.length-1]==0 && c.length>0 ){
			c.length--;
		}
		c.length = c.length>0?c.length:1;
		if( carry == 0 ){
			return c;
		}
		else{
			//we have actually borrowed 1000...000 (totally i 0's), so minus it back
			BigInteger d;
			d.sign = '+';
			d.length = i+1;
			for( int j=0; j<i; j++ )
				d.value[j] = 0;
			d.value[i] = 1;
			c.sign = '-';
			c = d + c;
			c.sign = '-';
			return c;
		}
	}
	else{
		return b + a;
	}
}

void operator+=( BigInteger &a, const BigInteger &b ){
	a=a+b;
}


//main.cpp
#include <iostream>
#include "BigInteger.h"
using namespace std;

int main(){
	BigInteger b;
	string s;
	cout << "Please enter a BigInteger value:\n";
	cin >> s;
	b.setNumber(s);		//written in BigInteger.cpp
	cout << "The BigInteger value is: " << b.getNumber();
	
	BigInteger b1, b2, b3;
	cin >> b1 >> b2;
	b3 = b1 + b2;
	cout << "Sum of b1 and b2 :" << b3 << endl;
	return 0;
}

/*-----Overloading typecasts-----*/
*********************************************


/*-----Constructor----*/
/* Initialisation list */
// https://stackoverflow.com/questions/2785612/c-what-does-the-colon-after-a-constructor-mean#2785639
// only way to initialize const and reference
class Demo
{
    Demo(int& val) : m_val(val)
     {
     }
private:
    const int& m_val;
};



/*----------Compilation Process----------*/

//Separate compilation
	$ g++ -c BigInteger.cpp
	$ g++ -c census.cpp
	$ g++ BigInteger.o census.o -o census

/* .cpp -> 
1. Preprocessing -> 
2. Syntax checking ->
3. Object code generation ->
4. Linking ->
executable */

/*-----Preprocessing-----*/

// preprocessed_census.cpp serves as the input of the upcoming compilation processes. 
//C++ library: eg. <iostream>, <string> located in /usr/include/c++/(version number)
	$ g++ -E census.cpp > preprocessed_census.cpp 

/* #include directive instructs the preprocessor to replace the line with the file specified
eg. The first part of the code is the content of the iostream file.
(Scroll down) Followed by the content of the BigInteger.h file.
(Scroll down) Followed by the original content in the census.cpp. */

/* #define directive is replaced
eg. #define PI 3.141592 -> all PI is replaced with 3.141592 */

/* #if ... #endif directive
The enclosed lines will be included in preprocessed code for compilation if and only if the condition is true. -> Conditional Compilation 

#if A || B
#elif C && D
#else
#endif

eg. */
	#define DEBUG 1
	...
	#if DEBUG
		cout << "debugging";
	#endif

/* #ifdef/#ifndef...#endi directive

eg.*/
	#ifdef x
	-> checks if the symbol x has been defined previously using #define x. If yes, the lines marked by #ifdef … #endif will be included.

	#ifndef x
	-> if NOT been defined

/* used as Include Guard -> avoid include same header file multiple times -> otherwise returns compilation error in later step -> used in every header file

eg.	*/
	x.cpp include "a.h" & "b.h"
	b.h include "a.h"
	BOMB! -> need Include Guard

/*eg.*/
	in "BigInteger.h"
	#ifndef BIGINTEGER_H
	#define BIGINTEGER_H
	...
	#endif

/*-----Syntax Checking-----*/
/*
1. All statements are syntactically correct. 
2. All functions and variables used are DECLARED. 
3. All classes used are DEFINED.
1> Assembly code
2> issue syntax errors
*/

	$ g++ -S census.cpp

/*
Declaration:	Introduces an "name" (identifier)
				No storage is allocated
Definition:		allocates program storage (variable and function only, not class)
*/


/* Declared but undefined */
#include <iostream>
using namespace std;
extern int a;	//variable
void display (int x);	//function

int main(){
...

/*-----Object code generation-----*/
	$ g++ -c census.cpp

/* in Object code
1. Memory for variables DEFINED
2. Memory for functions DEFINED
3. Reference for variable and functions DECLARED -> to be linked
(Reference are temporary addresses which will be substituted with real addresses in linking)
*/

/*-----Linking-----*/
/*
1. ensures main() is defined exactly ONCE
2. ensures all functions and variables are defined exactly ONCE
3. resolves the references
*/
	$ g++ census.o BigInteger.o -o census

/*---------------Standard Template Library (STL)---------------*/
/*
Container:	class for storing data
Iterator:	class for accessing items in containers
Algorithms:	e.g. sorting, searching
*/

/*----------Container----------*/
/* 
Vector:	organize data using dynamically resizing array.
List:	organize data using doubly linked list.
Map:	organize data using balanced binary search tree.
Stack:	organizes data using LIFO stack.
Queue:	organize data using FIFO (First-in first-out) queue.
Priority Queue:	organize data using heap.
Set:	organize data using binary search tree. 
Others:	http://www.cplusplus.com/reference/stl/ 
*/

/*-----Vector-----*/
//more efficient for random access
#include <vector>

	//declare int type vector
	vector <int> ivector; 
	vector<BigInteger> ivector; //can declare class!
	vector <int> ivector(5, 10); //=5 elements of "10"={10,10,10,10,10}
	//declare with array
	int num[] = {5, 10, 15, 20, 25, 30};
	vector <int> vector2(num, num + 6); //=1st element of num to 6th element of num={5,10,15,20,25,30}
	vector <int> vector3(num + 1, num + 5); //=2nd element of num to 5th element of num={10,15,20,25}

	//write in a new element at the end	[O(1)]
	ivector.push_back(369);

	//remove last element	[O(1)]
	ivector.pop_back();

	//read out vector	[O(1)]
	ivector[i];

	//copy vector	[Ω(n)]
	vector2 = vector1;

	//return number of elements	[O(1)]
	ivector.size();
	//return the size of the storage space currently allocated for the vector
	ivector.capacity();
	//return the maximum number of elements that the vector can hold
	ivector.max_size();

	//use pass by constant reference for efficiency purpose -> not copy once 
void print(const vector<int> &ivector){
	cout << "Content of the array" << endl;
		 for( int i = 0; i < ivector.size() ;  i++ )
			   cout << ivector[i] << " ";
	cout << endl;			   
}

	//insert
	//1st parameter: iterator that point to thelocation where insertion begins
	//2nd parameter: iterator that point to the location where COPY begins
	//3rd parameter: iterator that point to the location where COPY ends
	string a[] = {"apple", "apple", "boy", "cat", "dog"};
	vector <string> v;
	v.insert (v.begin(), a, a+5);



	// void resize (size_type n, value_type val = value_type());
	// before: 1 2 3 4 5 6
	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);
	// after: 1 2 3 4 5 100 100 100 0 0 0 0


    // erase item at certain position
    myvector.erase(myvector.begin()+5); // remove myvector[5]
    // return an iterator pointing to the new location of the element that followed the last element erased by the function call



	// clear
	myvector.clear();



/*-----List-----*/
//Doubly linked list: contains pointers to the next and previous node -> allows bidirectional list traversal
//very efficient to access first and last item
//Singly linked list <- forward_list

#include <list>

	list <string> names;
	list <string> names2;

	//insert to the front	[O(1)]
	names.push_front("689");
	//insert to the back	[O(1)]
	names.push_back("689");

	//access, return the object [O(1)]
	names.front();
	names.back();

	//search
	list<Record> phoneBook;	//Record has "string name" and "int number"
	list<Record>::iterator itr;

			for (itr=phoneBook.begin();itr != phoneBook.end(); itr++){
				if ((*itr).name == name)
				cout << (*itr).number << endl;
			}

	//=	[Ω(n)]
	names = names2;

	//remove the item at the front	[O(1)]
	names.pop_front();
	//remove the item at the back	[O(1)]
	names.pop_back();

	//size	[O(1)]
	names.size();

	//sort
#include <algorithm>
	names.sort();

/*-----Map-----*/
//Balanced binary search tree: more efficient searching	[O(log n)]

#include <map>

	//A map container stores items in <key,value> pairs
	//No 2 elements can have equivalent keys
	map <string, int> phoneBook;

	//insert	[O(log n)]
	//Value& operator[](const Key& k);
	phoneBook["Alan"] = 98765432;

	phoneBook["Bob"] //set a arbitary value
	cout << phoneBook["Can"];	//is valid since a arbitary value is set

	//check if exist	[O(log n)]
	phoneBook.count("Key");
	//always check first, otherwise a arbitary value is created
	//e.g.
	if ( phoneBook.count(name) > 0 ){
		// The key with name (name’s value) exists
	}else
		cout << "Name not found" << endl;

	//size	[O(1)]
	phoneBook.size();

	//=
	m1 = m2;

	//use class as key
class Record{ 
	public: 
		string name; 
		int number;
};
bool operator<(const Record& a, const Record& b){	// < for sorting in map
	return a.name < b.name;
}

	//iterators
	(*itr).first	//key
	(*itr).second	//value

	//combo
	map<string,vector<int> > phoneBook;	//must have ' ' between < <
	cin >> number;
	phoneBook[name].push_back(number); //*****

/*----------Iterators----------*/
//iterator is an object, pointer in an address
//iterator is designed to avoid low level memory manipulation

//iterators must match the type of container
	vector <int> data;
	vector <int>::iterator itr;

/*
1. Forward iterator
	can use =,++,*,==
2. Bidirectional iterator	(e.g. lists, maps)
	can use -- too
	support access to next or previous items only
3. Random access iterator	(e.g. vectors)
	can use a+689, a-b, a>b, a+=5, *(a+5) too
*/


//begin() and end() are iterator object (like &)
//end() points to the location 1 item after the last item
//++ for all container, -- for some (vector, list, map), itr=itr+1 for none
	for (itr = data.begin();itr != data.end(); itr++)
		cout << *itr << ' ';

// find and erase
int main()
{
	map<int,int> m ;
	m.insert( make_pair( 1,1 ) ) ;
	map<int,int>::iterator iter = m.find(1) ;
	if( iter != m.end() )
		m.erase( iter );
	else puts( "not found" ) ;
}

//const_iterator
void print( const vector<int> & v){
	vector<int>::const_iterator itr;	//if container object is a const -> const_iterator
	for (itr=v.begin();itr!=v.end();itr++)
		cout << *itr << " ";
	cout << endl;
}



/*----------Algorithms----------*/
#include <algorithm> //!!!!!

/*-----Sort-----*/
void sort (RandomAccessIterator first, RandomAccessIterator last)

//sort elements in the vector in a ascending order
//Random Access Iterator only
//not that "end()" is not included in sorting
	sort(ivector.begin(), ivector.end());

//sort a particular range
	sort(ivector.begin(), ivector.begin()+5);

//user-defined order
	sort(ivector.begin(), ivector.end(), compare);
	...

bool compare(int a, int b){ // compare(a,b) -> 1 if a<b
	return a>b;
} 

//overload
bool operator<(const Email & a, const Email & b ){
	//something
}

//check if sorted
#include <ext/algorithm>
	is_sorted(phoneBook.begin(), phoneBook.end())

//sort elements in the vector in a descending order
//Random Access Iterator only
	reverse(ivector.begin(), ivector.end());

/*-----Binary Search-----*/
bool binary_search (ForwardIterator first, ForwardIterator last, const T& target)
//return 1 if target is in the range

//use if items in a container are sorted in ASCENDING ORDER
//for Forward Iterators only = For All Iterators
//Random access iterators: O(log n)
//Others: O(n)

//return if exist in the range
	binary_search(input.begin(), input.end(), target);

//overload operator< if the class not yet defined

/*-----Lower Bound-----*/
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& target)
//return the EARLIEST location in the range that target can be insert while the range remains sorted

//similar to binary_search(), but return the location
//Random access iterators: O(log n)
//Others: O(n)

//e.g.	v = { "apple","apple","boy","cat","dog","dog","egg"}
	lower_bound (v.begin(), v.end(), "apple")
//return 0 (location of the first "apple")

/*-----Upper Bound-----*/
ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& target)
//return the LATEST location

//e.g.	v = { "apple","apple","boy","cat","dog","dog","egg"}
	lower_bound (v.begin(), v.end(), "apple")
//return 2 (location of "boy")

//return number of "apple"
	itr = lower_bound( v.begin() , v.end(), "apple");
	itr2 = upper_bound( v.begin() , v.end(), "apple");
	cout << "apple " <<  itr2 - itr << endl;
//return 2

/*-----Random Shuffle-----*/
#include<cstdlib>
#include<ctime>

void random_shuffle (RandomAccessIterator first, RandomAccessIterator last)

//srand(): seed function; time(): current time
	srand(time(NULL));
	random_shuffle(v.begin(), v.end());

/*-----Replace-----*/
void replace (ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value);
//Assigns new_value to all the elements in the range [first,last) that compare equal to old_value.

//require operator==() to be overloaded

/*-----Max, Min, Swap-----*/
**********************************************************

/*----------Templete----------*/
/*-----class-----*/
template <class T> //class or typename
class MyClass{
	public:
		T items[100];
}

	...
	MyClass<int> a; //a.items are int

eg.
template <class T>
class MyCollection{
	vector <T> data;
	public:
		void Add(const T&);
};

template <class T> //template <class T> has to be appear right before the definition of the member function too
void MyCollection<T>:: Add(const T& d){
	data.push_back(d);
}

/*-----function-----*/
template <class T> 
T maximum( const T & a, const T & b){
	return a < b ? b : a;
}

	...
	cout << maximum<int>(c1, c2) << " "; 
	...

/* default parameter */
void display(char = '*', int = 1);

void display(char c, int n) {
    ...



/*-----with iterator & friend-----*/
//typename is needed
typename vector<T>::const_iterator itr;

//friend (one-to-one)
//including the definition of the operator<<() function inside the definition of the MyCollection class
template <class T>
class MyCollection{
		vector<T> data;
	public:
		void Add(T const &);
		T & Draw();
   friend ostream & operator<<( ostream & cout, const MyCollection<T>& q){
		cout<<"Collection"<<endl;
		typename vector<T>::const_iterator itr;  
		for ( itr = q.data.begin() ; itr != q.data.end() ; itr++ )
			 cout << " " << *itr <<endl;
		return cout;
	}
};

//friend (many-to-many)
//this enables separate compilation
template <class T>
class MyCollection{
		vector<T> data;
	public:
		void Add(T const &);
		T & Draw();
	template <class U>
   friend ostream & operator<<( ostream & cout, const MyCollection<U>& q);  
};

template <class U> 
ostream & operator<<( ostream & cout, const MyCollection<U>& q){
		cout<<"Collection"<<endl;	 
		typename vector<U>::const_iterator itr;  
		for ( itr = q.data.begin() ; itr != q.data.end() ; itr++ )
			 cout << " " << *itr <<endl;
		return cout;
}











