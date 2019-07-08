import java.util.Scanner;



public class Java_cheatsheet {
	// static method all use static method and variable!!!!!!!!!!!
	public static void main (String[] args){
		System.out.print ("Change has come to America.");
		System.out.println ("Change has come to America."); // argument: Object
	}
}



// # Data type
		byte b;
		short s;
		int i;
		long l;
		float f;
		double d;
		char c;
		boolean b1 = true;
		boolean b2 = false;
		//all others are objects



// # String
// https://docs.oracle.com/javase/7/docs/api/java/lang/String.html
		String s = new String ("Peanut butter");
		String s = "Peanut butter"; // the same as above

		s = s + " and Jelly"; // concatenation
		System.out.print (s);

// ## Immutable: once created, cannot change its value nor length, but some methods can return new String objects

// e.g.
	name = name.replace('e', 'x');
// name	originally point to -> "Peanut butter"
// now point to -> "Pxanut buttxr"

// ## Method

	// String Length
	String phrase = "Change is inevitable";
	System.out.println ("Length of string: " + phrase.length());
	// Length of string: 20

	// Concatenation
	String mutation1;
	mutation1 = phrase.concat (", except from vending machines.");
	System.out.println ("Mutation #1: " + mutation1);
	// Change is inevitable, except from vending machines.

	// To Upper Case
	String mutation2;
	mutation2 = mutation1.toUpperCase();
	System.out.println ("Mutation #2: " + mutation2);
	// Mutation #2: CHANGE IS INEVITABLE, EXCEPT FROM VENDING MACHINES.

	// Replace
	String mutation3;
	mutation3 = mutation2.replace ('E', 'X');
	System.out.println ("Mutation #3: " + mutation3);
	// Mutation #3: CHANGX IS INXVITABLX, XXCXPT FROM VXNDING MACHINXS.
	// remove all whitespace
	str = str.replace( " " , "" );

	// Substring
	String mutation4;
	mutation4 = mutation3.substring (3, 30);
	System.out.println ("Mutation #4: " + mutation4);
	// Mutation #4: NGX IS INXVITABLX, XXCXPT F

	// String Indexes
	System.out.println (mutation4.charAt(1));
	// G

	// Trim
	// return a copy of the string with leading and trailing whitespace omitted

	// IndexOf(ch/String, int)
	// return the index within this string of the first occurrence of the specified character, starting the search at the specified index
	// -1 if no occurrence
	
	// boolean equals(String s)
	if (name1.equals(name2))
		System.out.println ("Same name");

	// int compareTo(String s)
	// equal -> 0, less than -> negative, greater than -> positive
	// base on lexicographic ordering: uppercase < lowercase
	// short < long ("book" < "bookcase")



// # Data Convesion
// Widening conversions VS Narrowing conversions

// Assignment Conversion
// only widening can happen
		float money;
		int dollars = 10;
		money = dollars;

// Promotion
		float sum = 100;
		int count = 10;
		result = sum / count;

// Casting
// both widening and narrowing
		int total = 10;
		int count = 3;
		result = (float) total / count;



// # Reading Input
import java.util.Scanner;

		Scanner scan = new Scanner (System.in); //System.in: keyboard input
		String answer = scan.nextLine(); //until the end of the line is found
		int i = scan.nextInt();
		double d = scan.nextDouble();



// # !!!!! Can use return in void !!!!!



// # Classes
//State: defined by attributes
//Behaviors: defined by operations

public class Die{	
	private int faceValue;

	//Constructors
	//no return type
	public Die(){
		faceValue = 1;
	}

	/	oString
	public String toString(){
		String result = Integer.toString(faceValue);
		return result;
	}

	public int roll(){
		faceValue = (int)(Math.random() * 6) + 1;
		return faceValue;
	}

	public void setFaceValue (int value){
		faceValue = value;
	}

	public int getFaceValue(){
		return faceValue;
	}
}



// # Object variable
// contain address of the object
// Garbage: no valid references, Java has garbage collection

	Die die1;
	die1 = new Die(2); // instantiation
	
// == operator: if 2 references are aliases of each other
// equals(Object o): if not define: same as == operator

// # This
public class Account {
	String name;
	long acctNumber;
	double balance;

	public Account(Sring name,		 
		long acctNumber, 
		double balance){

	 this.name = name;
	 this.acctNumber = acctNumber;
	 this.balance = balance;
	}
}



// # Encapsulation
// Any changes to the object's state (itstance variables) should be made by that object's methods
// Public constants not violate encapsulation: cannot be changed

// ## Accessor Method (getX): returns current value of a variable
// ## Mutator Method (setX): changes the value of a variable
// able to restrict a client's options to modify



// # Data Scope
// declared at class: all method in class
// declared within method: in that method only



// # Modifiers
//How about objects???

	// without modifier: any class in the same package


	// constant
	final int MAX = 6

	// anywhere
	// follow with static
	public

	// only within that class (not object! Other objects of the same class can access)
	// follow with static
	private

	
	protected

	// ## Static
	static

	// ### Static variables = class variables
	// only one copy of the variable exists, memory space is created when first referenced

	// ### Static methods
	// only static or local variables can be referenced
	// non-static variables and methods (e.g. this) cannot be referenced from a static context


// # Class Library: collection of classes

// ## Java Standard Class Library e.g. System, Scanner, String 
// java.lang			General support
//						e.g. java.lang.System, java.lang.String
//						(automatically imported into all programs)
// java.applet			Creating applets for the web
// java.awt				Graphics and graphical user interfaces
// javax.swing			Additional graphics capabilities
// java.net				Network communication
// java.util			Utilities
// javax.xml.parsers	XML document processing

// import 
import java.util.Scanner;
// import all classes in a particular package
import java.util.*;

// ## Math Class
// part of java.lang
// static methods: no object of Math is needed
//e.g.
	value = Math.cos(90) + Math.sqrt(delta);
//e.g.
	int num = -10;
	num =  Math.abs(num);
	System.out.println(num);
	// 10

// ## Random Class
import java.util.Random;

//e.g.
	Random generator = new Random();
	//a random number from the range of int
	int num1 = generator.nextInt(); 
	//a random number from 0 to 9
	num1 = generator.nextInt(10);
	// a random float falls in [0, 1)
	float num2 = generator.nextFloat();

// ## NumberFormat, DecimalFormat
// format floating point value
import java.text.NumberFormat;
import java.text.DecimalFormat;

//e.g.
	DecimalFormat formatter = new DecimalFormat("#.#####");
	System.out.println("The value of PI is "+formatter.format(Math.PI)+".");
	// 3.14159
//e.g.
	NumberFormat fmt1 = NumberFormat.getCurrencyInstance();
	NumberFormat fmt2 = NumberFormat.getPercentInstance();
	double price = 12;
	System.out.println("Price: " + fmt1.format(price));
	// HKD12.00
	double tax_rate = 0.06;
	System.out.println("Tax Rate: " fmt2.format(tax_rate));
	// 6%



// # Wrapper Classes
// part of java.lang
// contain Wrapper Class that correspond to each Primitive Type
// start with Capital letter 
// required as some methods require parameters to be objects
//e.g.
	Integer age = new Integer(40);

//comparison operator == checks whether the operands on both sides are the same. If the operands are object references, the comparison is true when the object references both point to the same object. The comparison is false if the object references are pointing to different objects, even the instance variables of the two objects carry the same value

// ## Autoboxing: automatic conversion
	Integer obj;
	int num = 42;
	obj = num; // new Integer object created
	//Integer objects created through autoboxing with values -128 to 127 are cached. That is, when an Integer object with value -128 to 127 is needed through autoboxing, the same Integer object is used in each autoboxing
	// ++ involves autoboxing too

// ## Unboxing: reverse of Autoboxing
	Integer obj = new Integer(40);
	int num = obj;

// ## Method

	// parseInt
	// for String
	String str = "42";
	int num = Integer.parseInt(str);
	System.out.println(num+1);
	// 43
	// for int (decimal, binary, octal, or hexadecimal)
	int b = Integer.parseInt("444",16);
	// 1092

	// Min and Max
	System.out.println(Integer.MIN_VALUE);
	System.out.println(Integer.MAX_VALUE);
	//-2147483648
	//2147483647

	// toString: return a String
	// byteValue, doubleValue, floatValue... : return the value as a (datatype)



// # Enumerated Types
// a special kind of class
	enum Season {WINTER, SPRING, SUMMER, FALL}

	Season time;
	time = Season.SPRING;
	time.ordinal(); // 1
	time.name(); // SPRING

// can define construtors, methods, instance variable
// Every enum contains values() that returns a array of all possible values
// use .values()[n] to get the n-th kind in the enum

public enum Season {
	WINTER ("December through February"),
	SPRING ("March through May"),
	SUMMER ("June through August"),
	FALL ("September through November");

	private String span;

	// Constructor
	Season (String months) {
		span = months;
	}

	public String getSpan() {
		return span;
	}
}

import java.util.*;

public class SeasonTester {
	public static void main(String[] args) {
	 for (Season time : Season.values())
		System.out.println(time + "\t" + time.getSpan());
	}
}



// # Arrays
// an object
	int[] scores;
	int scores[]; // the same
	scores = new int[10]; // must be instantiated, has fixed size

	int[] scores = {1,2,3,4,5};

	String[] words = new String[5]; // hold null

	int[][] scores = new int[12][50]; // 2D

	socres.length; // length

// Object Array
// !!!!!need 2 new!!!!!
	p = new Player[n];
	for (int i=0 ; i<n ; i++)
		p[i] = new Player(i, c);

// ## For loop

	int[] scores = new int[10];
	for (int score : scores)
		System.out.println (score);
	// score = scores[i], but score itself is not scores[i], changing the value of score does not change the value of scores[i]

	// same as:
	int[] scores = new int[10];
	for (int i=0; i < 10; i++)
		System.out.println (scores[i]);

	// 2D
	int sth[][] = new int[3][4];
	for (int[] row:sth){
		for (int ent:row)
			System.out.println("Hello! "); // 12 Hello!
	}



// # Command-Line Arguments
	args[0];

	if (args.length > 0) {
		try {
			firstArg = Integer.parseInt(args[0]);
		} catch (NumberFormatException e) {
			System.err.println("Argument" + args[0] + " must be an integer.");
			System.exit(1);
		}
	}

// In Eclipse: Run -> Run Configuration -> Tab "(x)=Arguments" -> Program arguments


// # Method: Variable Length Parameter Lists
// can accept other parameter, variable parameter must come last e.g. (int v, int ... list)
// single method cannot accept 2 sets of varying parameters
	public double average (int ... list){
		double result = 0;
		if (list.length != 0) {
			int sum = 0;
			for (int num : list)
				sum += num;
			result = (double)sum / list.length;
		}
		return result;
	}

	// somewhere
	mean1 = average (42, 69, 37); 
	mean2 = average (35, 43, 93, 23, 40, 21, 75);



// # ArrayList
// part of java.util
// adjustable capacity
// https://docs.oracle.com/javase/7/docs/api/java/util/ArrayList.html
import java.util.ArrayList;
	ArrayList<Integer> intList = new ArrayList<Integer>(); // can't use <int>
	ArrayList objList;

	// public ArrayList(Collection<? extends E> c): Constructs a list containing the elements of the specified collection, in the order they are returned by the collection's iterator.
import java.util.Arrays;
// ...
	ArrayList<Integer> temp = new ArrayList<Integer>(Arrays.asList(4,2,7,8,9));

	// print
	System.out.println(intList);
	// e.g. [1, 2, 3, 4, 5]

	// get element
	iniList.get(0); // (index)

	// set element
	iniList.set(0, 5); // (index, element)

	// add element
	intList.add(5); // (element)
	intList.add(0, 5); // (index, element)

	// remove element by pos
	intList.remove(1) // (index)
	// the removed element is returned

	// remove element by Object
	intList.remove(Integer(15))
	// first occurrence is removed
	// return true if success

	// size
	iniList.size()

	// empty
	iniList.empty()

	// indexOf (Object o)
	iniList.indexOf (Integer(15))
	// return index of first occurrence, -1 if absent

// # Comparing Float Values
	final float TOLERANCE = 0.000001;
	if (Math.abs(f1 - f2) < TOLERANCE)
		System.out.println ("Essentially equal");



// # Interface
// a collection of abstract methods (method header without a method body) and constants (no instance variables)

public interface Hello {
	// public be default
	public void sayHello();
}

public class Chinese implements Hello {

	private String familyname, givenname;

	public Chinese(String familyname, String givenname) {
		this.familyname = familyname;
		this.givenname = givenname;
	}

	// must override abstract method sayHello() in Hello
	public void sayHello() {
	System.out.println(familyname + " " + givenname + " says Ni Hao.");

	public void sayBye() {
		System.out.println(familyname + " " + givenname + " says Zai Jian.");
	}
}

public class HelloDriver {
	
	public static void main (String[] args) {

		// interface can be used as a type to declare a reference
		Hello c1, c2, e1;

		c1 = new Chinese("Ying", "Zheng");
		c2 = new Chinese("Liu", "Bang");
		e1 = new English("Trump", "Donald", "John");

		c1.sayHello();
		c2.sayHello();
		e1.sayHello();
		((Chinese)c1).sayBye();	// use child's method <- typecast ancestor reference
		// !!!!! typecast need 2 brackets !!!!!
	}
}

// ## Comparable
// compareTo(): less -> -1, equal -> 0, greater -> 1

// Method 1 (which gives warnings)
public class Fraction implements Comparable {

	private int numerator, denominator;

	// !!!!! parameter should be Object !!!!!
	public int compareTo(Object other){
		Fraction f = (Fraction) other;
		return Float.compare((float)numerator/denominator, (float)f.numerator/f.denominator);
	}
}

// Method 2
public class Fraction implements Comparable<Fraction> {
// <T>: generic type
// As Fraction should only compare with Fraction
// f.compareTo(String) -> syntax error rather than runtime error

	private int numerator, denominator;

	public int compareTo(Fraction f){
		return Float.compare((float)numerator/denominator, (float)f.numerator/f.denominator);
	}

public class ComparableDemo {

	// interface as parameter
	public static Comparable largest (Comparable c1, Comparable c2, Comparable c3) {
		if (c1.compareTo(c2) > 0 && c1.compareTo(c3) > 0) return c1;
		if (c2.compareTo(c1) > 0 && c2.compareTo(c3) > 0) return c2;
		return c3;
	}

	public static void main(String[] args) {

		int n1 = 1, n2 = 8, n3 = 6;
		System.out.println("The largest among n1-n3 is " + largest(n1, n2, n3));

		String s1 = "apple", s2 = "bye", s3 = "ELEC2543";
		System.out.println("The largest among s1-s3 is " + largest(s1, s2, s3));

		Fraction f1 = new Fraction(1, 2), f2 = new Fraction(2, 3), f3 = new Fraction(1, 3);
		System.out.println("The largest among f1-f3 is " + largest(f1, f2, f3));
	}
}



// # Inheritance
// parent class VS child class
// inherits data and methods except constructors

// private cannot be referenced by child class
// protected can be referenced by child class

public class Book {
	protected int pages;

	public Book() {
		pages = 1500;
	}
}

public class Dictionary extends Book {
	private int definitions;

	public Dictionary() {
		// super(<parameter>): parent's constructor
		// call to super must be first statement in constructor
		// if no explicit statement (e.g. super()) in the constructor, parent's no-argument constructor will be called AUTOMATICALLY
		super();
		definitions = 52500;
	}
}

// Java ONLY single inheritance VS C++ multiple inheritance (multiple parents)
// Turtle: Inheritance -> "With legs", Interface -> "Can swim"

// ## Shadowing Variables
// same name with parent
// don't use!
public void confusing () { 
	sv;				// variable sv in class C
	this.sv;		// variable sv in class C 
	super.sv;		// variable sv in class B 
	((B)this).sv  	// variable sv in class B 
	((A)this).sv  	// variable sv in class A
	super.super.sv	// ILLEGAL IN JAVA
}

// ## Overriding Methods
// same name and parameters with parent
public class Thought
{
	public void message()
	{
		System.out.println ("I feel like I'm diagonally parked in a parallel universe.");
	}
}

public class Advice extends Thought
{
	public void message()
	{
		System.out.println ("Warning: Dates in calendar are closer than they appear.");
		super.message();  // explicitly invokes the parent's version
	}
}
// results:
// Warning: Dates in calendar are closer than they appear.
// I feel like I'm diagonally parked in a parallel universe.

// ## Object
// in java.lang
// all classes are derived from Object
// if parent not explicitly defined -> parent = Object
// e.g. equals(), toString()

// ## final
// final method: cannot be overridden in descendant
// final class: cannot be used to derive any children
public final class UGStudent {
	// contents
}

// ## abstract class
// cannot be instantiated, used to represent a generic concept
// often contains abstract methods with no definitions
// abstract must be applied to each abstract method
// can contain non-abstract methods (unlike interface)
// child must override all abstract methods; or be considered as abstract too
// never abstract and final together
public abstract class Product {
	// contents
}



// # Polymorphism
// polymorphic reference: variable that can refer to diff type of objects
	Parent p;
	p = new Child();	// widening conversion

	Child c;
	c = new Parent();	// narrowing: incompatible types
	c = (Child) new Parent();	// narrowing: usually runtime error

// Executive, Clerk, Volunter are child class of StaffMember
public class Firm {
	public static void main(String[] args) {
		StaffMember[] staffList = new StaffMember[4];

		staffList[0] = new Executive ("Sam", 2423.07);
		staffList[1] = new Clerk ("Diane", 1246.15, 10.55);
		staffList[2] = new Volunteer ("Norm");
		staffList[3] = new Volunteer ("Cliff");

		((Executive)staffList[0]).awardBonus (500.00);	// use child's method <- typecast ancestor reference
		((Clerk)staffList[1]).addHours (40);

		double amount;
		for (int count=0; count < staffList.length; count++)
		{
			System.out.println (staffList[count]);
			amount = staffList[count].pay();  // polymorphic
			System.out.println ("Paid: " + amount);
			System.out.println ("-----------------------------------");
		}
	}
}



// # Exceptions
// e.g. ÷0, array out of bound, null ref, cannot open file

// ## Uncaught Exceptions
// produce Call Stack Trace = line and method that lead to the exception

// ## try
import java.util.*;
import java.lang.*;
import java.io.*;

public class DemoCatch {
	public static void main (String[] args)
	{
	  Scanner scan;

		try {
			scan = new Scanner(new File("test.txt"));
			// stop once exception is caught
			scan.nextInt();
	
		} catch (FileNotFoundException e) {
			System.out.println("test.txt does not exist.");

		} catch (InputMismatchException e) {
			System.out.println("IO exception");

		} finally {
			// always executed
			System.out.println("finally");
		}

		System.out.println ("This text WILL BE printed :-)");
	}
}
// (depend on the exception)
// finally
// This text WILL BE printed :-)

// Multiple Exception
	} catch (FileNotFoundException|InputMismatchException e) { 


// ### print Call Stack Trace
// e.g.
      catch (Exception e)
      {
         e.printStackTrace();
      }
// java.lang.ArithmeticException: / by zero
//		at Zero2.main(Zero2.java:12)



// ## Exception Propagation
// handling programming at other point of the program



// ## Throwable _____ Error
//               |___ Exception _____ IOException
//                               |___ RuntimeException _____ ArithmeticException
//                                                      |___ IndexOutOfBoundsException _____ ArrayIndexOutOfBoundsException

// ## Checked exceptions: mush be caught or listed in throws clause, otherwise compilation error
// e.g. IOException
public class DemoChecked {
	public static void main (String[] args) throws FileNotFoundException {
		Scanner scan;
		scan = new Scanner(new File("test.txt"));
		scan.nextInt(); 
   }

// ## Unchecked exceptions
// RuntimeExcepotion is the only unchecked exception

// ## Define an Exception
public class OutOfRangeException extends Exception {
	OutOfRangeException (String message)
	{
		super (message);
	}
}

import java.util.Scanner;
public class CreatingExceptions {
	public static void main (String[] args) throws OutOfRangeException
	{
		final int MIN = 25, MAX = 40;

		Scanner scan = new Scanner (System.in);

		OutOfRangeException problem =
			new OutOfRangeException ("Input value is out of range.");

		System.out.print ("Enter an integer value between " + MIN +
								" and " + MAX + ", inclusive: ");
		int value = scan.nextInt();

		//  Determine if the exception should be thrown
		if (value < MIN || value > MAX)
			throw problem;

		System.out.println ("End of main method.");  // may never reach
	}
}

// Exception in thread "main" OutOfRangeException: Input value is out of range.
//	at CreatingExceptions.main(CreatingExceptions.java:20)

import java.util.Scanner;

public class MakeSureInputCorrect {
	final static int MIN = 25, MAX = 40;

	public static int userInput() throws OutOfRangeException {
		Scanner scan = new Scanner (System.in);

		System.out.print ("Enter an integer value between " + MIN + " and " + MAX + ", inclusive: ");

		int value = scan.nextInt();

		if (value < MIN || value > MAX)
			throw new OutOfRangeException ("Input value is out of range.");
		else
			return value;
	}

	public static void main (String[] args) {
		int value;
		boolean done = false;

		while (!done) {
			 try {
				  value = userInput(); 
				  done = true;
			 }
			 catch (OutOfRangeException e) {
				  System.out.println("The input was invalid");
			 }
		}
		System.out.println ("End of main method.");
	}
}

// Enter an integer value between 25 and 40, inclusive: 99
// The input was invalid
// Enter an integer value between 25 and 40, inclusive: 33
// End of main method.



// # Inner Class
// class within another class
// Outer class and Inner class can access the instance variables of each other directly.



// # Abstract data type (ADT)
// organized collection of info & set of operation used to manage

// Static data structure: fixed size, e.g. array
// Dynamic data structure: grows and shrinks at execution time, e.g. link

// # Link List
public class MyList {
	
	private class MyNode { 
		Object obj;
		MyNode next;

		MyNode(Object item) {
			obj = item;
			next = null;
		}
	}
   private MyNode list;
}

// # Doubly Linked List
// has next & previous
	class MyDLNode {
		Object obj;
		MyDLNode next, prev;

		public MyDLNode(Object item) {
			obj = item;
			next = prev = null;
		}
	}
......................................................................

// # Queues
// linear data structures
// FIFO

// enqueue
// dequeue
// empty
// size

public class MyQueue {
	
	private class MyNode { 
		Object obj;
		MyNode next;

		MyNode(Object item) {
			obj = item;
			next = null;
		}
	}

	private MyNode front, rear;

	public MyQueue() {
		front = rear = null;
	}

	public boolean empty() {
		return (front == null);
	}

	public void enqueue(Object item) {
		MyNode newNode = new MyNode(item);
		if (empty()) {
		front = rear = newNode;
		return;
		}
		rear.next = newNode;
		rear = newNode;
	}

	public Object dequeue () {
		if (empty()) return null;
		Object obj = front.obj;
		if (front == rear) 
			front = rear = null;
		else
		front = front.next;

		return obj;
	}
}
......................................................................

// # Stacks
// linear data structures
// FILO
// in java.util

// push
// pop
// peek/top: retrives the top item w/o removing it
// empty
// size

// # Binary Tree: a node has at most 2 childen
// nonlinear data structures
// siblings: nodes having same parents
// leaf: node have no child
// internal node: node having 1-2 childen
// ancestor: parent of parent of parent...
// descendant: reverse of ancestor
// height of tree: no. of edges on the longest path from root to leaf

// ## Tree Traversal
// Preorder: root -> left subtree -> right subtree
// Inorder: left subtree -> root -> right subtree
// Postorder: left subtree -> right subtree -> root

// ## Deletion !!!!!
// leaf: simply remove it
// 1 child: promote the child
// 2 childen: promote LEFTMOST child on RIGHT subtree = just larger than the node

public class BinTree {

	public class BinTreeNode {
		private BinTreeNode parent, left, right;
		private int item;

		public BinTreeNode(int item) {
			this.item = item;
			parent = left = right = null;
		}
	}

	private BinTreeNode root;

	public BinTree() {
		root = null;
	}

	public int size() {
		BinTree leftSub = new BinTree();
	}
}



// # Sort
import java.util.Arrays
...
	Arrays.sort(arr)
...





































// # Merge Sort
// T(n) = kn log n + cn
//		= O(n log n)

public class MergeSort {

	public static void mergeSort(int[] list) {
		if (list.length <= 1) return;

		// Split the array in half
		int[] first = new int[list.length / 2];
		int[] second = new int[list.length - first.length];
		for (int i = 0; i < list.length / 2; i++)
			first[i] = list[i];
		for (int i = 0; i < list.length - first.length; i++)
			second[i] = list[list.length / 2 + i];

		// Sort each half
		mergeSort(first);
		mergeSort(second);

		// Merge the halves together, overwriting the original array
		int iFirst = 0, iSecond = 0, i = 0;
		while (iFirst < first.length && iSecond < second.length) {
			if (first[iFirst] <= second[iSecond]) {
				list[i++] = first[iFirst++];
			} else {
				list[i++] = second[iSecond++];
			}
		}

		while (iFirst < first.length)
			list[i++] = first[iFirst++];
		while (iSecond < second.length)
			list[i++] = second[iSecond++];
	}
}



// # Quick Sort
// Average: O(n log n)
// Worst: O(n^2)
// When many repeated values -> tends to worst case
public class QuickSort {

	public static void sort(int[] list) {
		qsort(list, 0, list.length - 1);
	}

	// Swap list[i] with list[j]
	private static void swap(int[] list, int i, int j) {
		int temp;
		temp = list[i];
		list[i] = list[j];
		list[j] = temp;
	}

	// Recursive function to sort list[i] to list[j]
	private static void qsort(int[] list, int i, int j) {
		if (i >= j) return;

		if (i + 1 == j) {
			if (list[i] > list[j]) swap(list, i, j);
			return;
		}

		// Find the pivot position
		int pos = findPivot(list, i, j);

		if (pos == i) {
			qsort(list, i + 1, j);
			return;
		} else if (pos == j) {
			qsort(list, i, j - 1);
			return;
		} else { // Sort the two sublists divided by the pivot
			qsort(list, i, pos - 1);
			qsort(list, pos + 1, j);
		}
	}

	// list[i] is the pivot
	// Re-arrange the elements from list[i] to list[j] s.t.
	// the elements smaller than the pivot are on the left
	// while the elements larger than the pivot are on the right
	// pivot is in its right position
	private static int findPivot(int[] list, int i, int j) {
		int pivot = list[i];

		int left = i + 1, right = j;
		while (left < right) {
			while (left <= j && list[left] <= pivot) left++;
			while (right > i && list[right] > pivot) right--;

			if (left < right) {
				swap(list, left, right);
				left++;
				right--;
			}
		}

		int k = i + 1;
		while (k <= j && list[k] <= pivot) {
			list[k - 1] = list[k];
			k++;
		}
		if (k == j) {
			list[j] = pivot;
			return j;
		} else {
			list[k - 1] = pivot;
			return k - 1;
		}
	}

}



// # Time Measurement
		  long startTime = System.currentTimeMillis();
		  QuickSort.sort(input);
		  long endTime = System.currentTimeMillis();
		  long timeNeeded = endTime - startTime;
		  System.out.println("The time needed to sort " + size + " numbers is " + timeNeeded + " ms.");


// # Memory Measurement
// https://docs.oracle.com/javase/7/docs/api/java/lang/Runtime.html

public class MeasureMemory {

	 public static long memoryUsed() {
		  Runtime runtime = Runtime.getRuntime();
		  runtime.gc(); //garbage collector
		  long memory = runtime.totalMemory() - runtime.freeMemory();
		  return memory;
	 }

}



// # Process
// 0 ... max
// text data heap ... stack

// text: compiled program codes (fixed size)
// data: global and static variables (fixed size)
// heap: dynamic memory for NEW objects created (may grow)
// stack: local variables (may grow)

// when heap meets stack -> no memory, program terminates

// # Threading
public class ThreadArrayCopyDemo {

	public static int[] x = { 1, 2, 3, 4, 5 }, y;

	static class CopyThread extends Thread {

		// Copy the even elements from x to y
		public void run() {
			for (int i = 0; i < x.length; i = i + 2)
				y[i] = x[i];
		}
	}

	public static void main(String[] args) {
		y = new int[x.length];

		// !!!!! Remember to start the thread before run in main thread !!!!!
		CopyThread thread = new CopyThread();
		thread.start();

		// !!!!! Because this is BLOCKING !!!!!
		for (int i = 1; i < x.length; i = i + 2)
			y[i] = x[i];

		// !!!!! Remember to start the thread before run in main thread !!!!!

		// Make the main thread sleep for 1000 ms
		try {
			Thread.currentThread().sleep(1000);
		} catch (InterruptedException ie) {
			System.exit(1);
		}
		

		System.out.print("The original x[] is: ");
		for (int i = 0; i < x.length; i++)
			System.out.print(x[i] + " ");
		System.out.println();

		System.out.print("y[] is: ");
		for (int i = 0; i < y.length; i++)
			System.out.print(y[i] + " ");
		System.out.println();
	}

}



// Two Version
// It is possible to implement Runnable and derive from other classes -> preferred

// Runnable Interface
	public class RunnableThread implements Runnable {
		public void run() {
			for (int i = 0; i < 5; i++)
				System.out.println("Runnable: " + i);
		}
	}

	// ... somewhere ...
	Thread t = new Thread(new RunnableThread());
	t.start();

// Thread Class
	public class ExtendedThread extends Thread {
		public void run() {
			for (int i = 0; i < 5; i++)
				System.out.println("Extended Thread: " + i);
	}

	// ... somewhere ...
	Thread t = new ExtendedThread();
	t.start();

// Passing Parameters
// start() and run() do not accept parameters
// use constructors

public class SwapArrEltThread extends Thread {
	private int[] arr;

	public SwapArrEltThread(int[] list){
		arr = list;
	}

	public void run(){
		int temp = arr[0];
		arr[0] = arr[1];
		arr[1] = temp;
	}
}

public class SwapArrEltDemo{
	public static void main(String[] args){
		int arr[] = {4, 8};
		System.out.println("arr = " + arr[0] + ", " + arr[1]);

		Thread t = new SwapArrEltThread(arr);
		t.start();

		try {
			Thread.sleep(100);
		} catch (InterruptedException e){
			System.exit(1);
		} // can use even not threading

		System.out.println("arr = " + arr[0] + ", "+ arr[1]);
	}
}

// # Thread Synchronization

// ## Critical Section
// Object lock = new Object ();
// synchronized (lock) {
// Only one thread can access lock at a time.

// ## Thread Joining
// thread1.join();
// pauses the execution of a thread until a certain thread completes

public class ThreadInterleaveSharedDataMutex {

	public static int sharedData = 0;
	// For thread synchronization
	public static Object lock = new Object();

	static class MyThread extends Thread {

		private int id;

		public MyThread(int i) { id = i; }

		public void run() {
			synchronized(lock) {
				System.out.println("Thread " + id + " before update: " + sharedData++);
			}
				System.out.println("Thread " + id + " after update: " + sharedData);
		}

	}

	public static void main(String[] args) {
		MyThread thread1 = new MyThread(1);
		MyThread thread2 = new MyThread(2);
		MyThread thread3 = new MyThread(3);
		MyThread thread4 = new MyThread(4);

		thread1.start();
		thread2.start();
		thread3.start();
		thread4.start();

/*		// Make the main thread sleep for 1000 ms
		try {
			Thread.currentThread().sleep(1000);
		} catch (InterruptedException ie) {
			System.exit(1);
		}
*/
		// Leave join
		try {
			thread1.join();
			thread2.join();
			thread3.join();
			thread4.join();
		} catch (InterruptedException ie) {
			System.exit(1);
		}

		System.out.println("Final value = " + sharedData);
	}

}

// Thread 1 before update: 0
// Thread 1 after update: 1
// Thread 2 before update: 1
// Thread 2 after update: 2
// Thread 3 before update: 2
// Thread 3 after update: 3
// Thread 4 before update: 3
// Thread 4 after update: 4
// Final value = 4

// # Socket Programming

// ## Server
import java.io.*;
import java.net.*;

public class ReverseStringServer {

	// implementation here
	// Returns a String that is the reverse of the parameter s
	public static String reverse(String s) {
		String result = "";
		int length = s.length();

		for (int i = length - 1; i >= 0; i--) {
			result = result + s.charAt(i);
		}

		return result;
	}
	// implementation stop

	public static void main(String[] args) throws Exception {
		// Create server socket listening on port
		int port = 3333;  // 0-1023 reserved for well-known program
		ServerSocket serverSocket = new ServerSocket(port);

		// Declare client socket
		Socket clientSocket;

		while (true) { // Provide service continuously
			clientSocket = serverSocket.accept();

			ObjectOutputStream out = new ObjectOutputStream(clientSocket.getOutputStream());
			ObjectInputStream in = new ObjectInputStream(clientSocket.getInputStream());

			// implementation here
			String s = (String) in.readObject();

			String result = reverse(s);
			// implementation stop

			out.writeObject(result);
			out.flush();
			
			out.close();
			in.close();
			clientSocket.close();
		}
	}
}

// ## Client
import java.io.*;
import java.net.*;
import java.util.*;

public class ReverseStringClient {

	public static void main(String[] args) throws Exception {
		// Bind the socket to the server with the appropriate port
		Socket socket = new Socket("localhost", 3333); // change to server IP here

		// Setup I/O streams
		ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
		ObjectInputStream in = new ObjectInputStream(socket.getInputStream());

		// implementation here
		System.out.print("Enter the string you want to reverse: ");
		Scanner scan = new Scanner(System.in);
		String s;
		s = scan.nextLine();
		// implementation stop
		
		out.writeObject(s);
		out.flush();
		
		String result = (String) in.readObject();
		
		// implementation here
		System.out.println("The result is: " + result);
		// implementation stop
	}

}



// # UDP

// ## Server
// 1. Create a datagram socket and bind it with a port number
// 2. Create a buffer for incoming data
// 3. Accept an incoming datagram
// 4. Read input from the datagram
// 5. Perform the job and produce the result
// 6. Retrieve the IP address and port number of the client
// 7. Send the result back to the client through a datagram

import java.io.*;
import java.net.*;

public class ReverseStringUDPServer {
	public static void main(String args[]) throws Exception {
		// Create a datagram socket and bind it with a port number
		DatagramSocket serverSocket = new DatagramSocket(1234);

		// Create a buffer for incoming data
		byte[] sendData, receiveData;
		DatagramPacket sendPacket, receivePacket;

		while (true) {
			// Accept an incoming datagram
			receiveData = new byte[1024];
			receivePacket = new DatagramPacket(receiveData, receiveData.length);
			serverSocket.receive(receivePacket);

			// Read input from the datagram
			String s = new String(receivePacket.getData());

			// Perform the job and produce the result
			String result = reverse(s);

			// Retrieve the IP address and port number of the client
			sendData = result.getBytes();
			InetAddress ipAddress = receivePacket.getAddress();
			int port = receivePacket.getPort();
			sendPacket = new DatagramPacket(sendData, sendData.length, ipAddress, port);

			// Send the result back to the client through a datagram
			serverSocket.send(sendPacket);
		}
	}
}

// ## Client
// 1. Create a datagram socket
// 2. Prepare datagram packets for send and receive
// 3. Put the data in the datagram packet
// 4. Specify the server IP and port in the datagram packet for sending
// 5. Send the data out to the server
// 6. Read the reply from the server

import java.io.*;
import java.net.*;
import java.util.*;

public class ReverseStringUDPClient {

	public static void main(String[] args) throws Exception {

		// Create a datagram socket
		DatagramSocket clientSocket = new DatagramSocket();
		DatagramPacket sendPacket, receivePacket;

		// Prepare datagram packets for send and receive
		byte[] sendData; // = Data to be sent out

		// Ask for user input
		System.out.print("Enter the string you want to reverse: ");
		Scanner scan = new Scanner(System.in);
		String s;
		s = scan.nextLine();
		sendData = s.getBytes();

		// Get the IP address as an InetAddress object
		InetAddress addr = InetAddress.getByName("localhost");
		// Create the outgoing datagram
		sendPacket = new DatagramPacket(sendData, sendData.length, addr, 1234);

		// Send out the packet using the socket
		clientSocket.send(sendPacket);

		// Accept an incoming packet
		byte[] receiveData = new byte[1024];
		receivePacket = new DatagramPacket(receiveData, receiveData.length);
		clientSocket.receive(receivePacket);

		String result = new String(receivePacket.getData());

		System.out.println("The result is: " + result);

		clientSocket.close();
	}

}

// ## Library

// ### DatagramSocket
	// port number
	DatagramSocket serverSocket = new DatagramSocket(1234);
	// if no paramemter -> available port will be selected
	DatagramSocket clientSocket = new DatagramSocket();

// ### DatagramPacket
// space is needed for storing the data

	// Create incoming packet
	DatagramPacket incomingPacket = new DatagramPacket(buffer, buffer.length);

	// Create outgoing packet: IP and port have to be specified
	DatagramPacket outgoingPacket = new DatagramPacket(buffer, buffer.length, IPAddress, 1234);

// #### byte[] is used <- have to transform into byte[]

// sending
	String objects;
	String s = "Hello!";
	byte[] data = s.getBytes();
// must be Serializable: implement Serializable interface

// sending: if no method to encode into byte[] -> use IO stream
	ByteArrayOutputStream byteOS = new ByteArrayOutputStream();
	ObjectOutputStream objOS = new ObjectOutputStream(byteOS);
	objOS.writeObject(data);
	byte[] sendData = byteOS.toByteArray();

// receiving: if no method to decode from byte[] -> use IO stream
	byte[] dataInByte = incomingPacket.getData();
	ByteArrayInputStream byteIS = new ByteArrayInputStream(dataInByte);
	ObjectInputStream objIS = new ObjectInputStream(byteIS);
	MyData data = (MyData) objIS.readObject();

// ### InetAddress
// specify IP address in a datagram

	// create an InetAddress object: IP/hostname
	InetAddress addr = InetAddress.getByName("127.0.0.1");
	InetAddress addr = InetAddress.getByName(“localhost”);

	// get IP address from an incoming packet
	InetAddress addr = receivePacket.getAddress();












