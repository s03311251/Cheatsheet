/*----------Heading----------*/
/* Sub-Heading */
// Sub-Sub-Heading

// use "$ man (function)" in BASH to check how to use the function
// standard library are usually located in:
// /usr/local/include <- usually 3rd-party files
// /usr/include <- usually OS header files like <stdio.h>

#include <stdio.h>

int main(){
	printf( "Hello world!\n" );
	return 0; // return 0 if success
}

/*----------Data Type----------*/
	char c;
	int i; // >=16 bit
	short s;  // usually half of int
	long l; // >= 32 bit
	float f;
	double d;
	
	unsigned int u;
	long long ll;
	long double ld;

// casting
	int x = 7;
	int y = 2;
	float z = (float)x / (float)y;
	printf("z = %f\n", z);





/*----------global variable----------*/
// not put in stack but global in memory



/*----------static----------*/

/* static variable */

/* static function */
// https://stackoverflow.com/questions/5025394/effect-of-return-type-being-static
// The function is static, not the return type. This means that its name is only visible from within the current compilation unit, which is used as an encapsulation mechanism.
static int hello();



/*----------boolean----------*/
// true and false only available >C99
0 = false;
others = true;

// & | can replace && || but they won't skip second condition



/*----------Output----------*/
/* printf() */
// f stands for formatted
// write to Standard Output, ./a.out > out.txt to redirect to a file

	int a = 10;
	printf( "The value of a is %d.\n" , a );

/*	Format Specifier	%[flags][width][.precision][length]specifier
	http://www.cypress.com/file/54441/download

	%d   int (decimal)
	%x   hex
	%f   float/double
	%.2f 2 decimal places
	%c   char
	%s   string
	%p   pointer (remember it's just virtual address allocated by OS)
	%g   removing trailing zeros for float and double (e.g. 12.3400 <- 0 here)
    
    %+       always show +/- sign
	%(space) always show  /- sign (space instead of +)
	%X       (X for a number) right justifying
	%-X      (X for a number) left justifying
	%0X      (X for a number) pad with trailing 0s
*/

	int a = 1;
	double b = -10.5;
	printf ("Input %d %f\n", a, b);	//1 -10.500000
	printf ("Sum = %f\n", a+b);	//-9.500000 (is double value bcz %f)

	// each column will be of width of 8 characters, right-justified
	printf( "%8s %8s %8s\n", "Name", "Age", "Weight");
	//	Name	 Age   Weight

/* puts(), fputs() */

	// printf() interpret formatting string
	puts("Only 80% finished?"); // ignore %, with newline
	fputs("Only 80% finished?", stdout); // without newline
	printf("Only 80%% finished?\n");

	char str[] = "Only 80% finished?";
	puts(str); // OK, string only
	printf(str); // not OK
	printf("%s", str); // OK



/* fprintf() */
	fprintf(stdout, "Who said that?"); // same as printf
	fprintf(stderr, "Who said that?"); // redir to standard error



/* sprintf() */
// format to string
	uint32_t i = 0;
	char i_str[11];
	sprintf(i_str, "%d", i);


/* perror() */
void perror(const char *s);



/*----------Input----------*/
/* scanf() */

/*	Format Specifier	%[flags][width][.precision][length]specifier
	%2s     string with width = 2, remember there's \0 at the end
	%9[^\n] string that is 9-char long or reach \n
	        (often use "%9[^\n]%c" and check if the %c == \n)
*/

	int a;
	float b;
	scanf( "%d%f", &a, &b); // & here !!!!!
	// return no. of values able to read
	// return -1 when it can’t read anything more

	char name[100];
	scanf( "%s", name);	//not &name because name is array
	printf( "Hello %s!",name);

// Read char after char
// https://stackoverflow.com/questions/5240789/scanf-leaves-the-new-line-char-in-the-buffer
// scanf() normally removes whitespae, but not after %[sth]
	scanf("%c",a);
	scanf(" %c",b);

// Read One-by-one
	while ( scanf("%9s", word) == 1 ) {
		// do sth
	}



/* Comma-separated Input */
	int x;
	char y[10];
	// input: 10,ABC
	scanf("%d,%9s", &x, y); // output: x:10 y:ABC

// String
	char x[10], y[10];
	// input: AAA,BBB
	scanf("%9s,%9s", x, y); // output: x:AAA,BBB y:�@
	scanf("%9[^,],%9s", x, y); // output: x:AAA y:BBB

// String Size Limit
	char x[5]; 
	scanf ("%s", x) // input: qwertyuiop
	// stack smashing detected
	scanf ("%5s", x) // input: qwertyuiop
	printf("%s\n", x); // output: qwert !!!!! not counting \0 !!!!!



// sscanf()
	int x;
	char y[10];
	char input[] = "10,ABC";
	sscanf(input, "%d,%9s", &x, y);

    printf("%d %s\n", x, y); // output: 10 ABC



/* fgets() VS scanf() */
// safer than scanf() and won't stop at space, but takes 1 field at a time only
// there's sth called gets() which is VERY DANGEROUS
	fgets(x, sizeof(x), stdin); // 2nd parameter takes max size of string



/*----------for-loop----------*/
// for is in c99 standard
// $ gcc -std=c99 variable.c



/*----------string----------*/

	char name[] = "Alan"; // String Literals
	printf ("%s", name); // Alan
	// name[4] = \0, size of name is 5



/* String Formatter */
	char buffer [50];
	int n, a=5, b=3;
	n = sprintf (buffer, "%d plus %d is %d", a, b, a+b);
	// return total number of characters, -1 if failed



/* String Array */
// !!!!! remember x[2nd dimension][1st dimension] !!!!!

	char strings[][4] = {"abc", "bca", "rat", "tar", "far", "bra"}; // remember \0
	char strings[6][4] = {"abc", "bca", "rat", "tar", "far", "bra"}; // OK
	char strings[][] = {"abc", "bca", "rat", "tar", "far", "bra"}; // not OK
	char *strings[] = {"abc", "bca", "rat", "tar", "far", "bra"}; // they're string literals



#include <string.h>

/* Copy string value */
// str1 = str2 ins't working

	strcpy (char s1[], char s2[]);	//Copy char array s2 to s1

	// memcpy
	void * memcpy ( void * destination, const void * source, size_t num );

	//e.g.
	strcpy(str, "abc");



/* Copy on the heap */
// usually use along with dynamic allocation
	char *copy = strdup(s);
	...
	free(copy); // as "copy" is on the heap



/* Compare 2 string */
	strcmp (char s1[], char s2[]);	//Return negative if s1<s2, return 0 if s1==s2, return positive if s1>s2.

	//e.g.
	if (strcmp(a,b) == 0)
		printf("They are the same\n");



/* Concatenate == Append s2 after the end of s1 */
	strcat (char s1[], char s2[]);



/* Return the length of the string stored in the char array s1 */
// null terminator = '\0' -> end of string
// not counting '\0'

	strlen (char s1[]);



/* Search */

	strchr("Hello", 'e'); // 0x4005e5: & of e in the str
	strstr("dysfunctional", "fuck")); // 0x40064b: & of 2nd str in 1st str
	// return NULL if not exists
	// if (NULL) -> don't execute

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! have sth like pop.back, erase???



/*----------stdlib.h----------*/
// = cstdlib in C++

// parse string to int
	myInt = atoi(myStr);
// atof(): to double
// atol(): to long

// terminate
	exit (EXIT_SUCCESS); // =	exit (0);
	exit (EXIT_FAILURE); // =	exit (1);

// srand()

// malloc()

// abs()



/*----------Argument----------*/
// argc: argument count; argv: string array
int main( int argc, char* argv[] )
{
	// Something Here
}

/* e.g.
	./myprogram -fullscreen somefile.sav
	->
		argc = 3
		argv[0] = "./myprogram"
		argv[1] = "-fullscreen"
		argv[2] = "somefile.sav"
*/



/* Get Option: getopt() */
// e.g. ./order_pizza Tomato Pineapple -d Alice -t
// optarg, optind are extern

#include <unistd.h> // access POSIX API, not standard C library, same name in C++
#include <getopt.h> // if using c99/c11 instead of ANSI C/gnu99/gnu11

int main(int argc, char* argv[])
{
	char* delivery = "";
	int thick = 0;
	char ch;

	// "d:t": accept -d and -t (and -td), "d:" means after -d there's an argument (= optarg) 
	while ((ch = getopt(argc, argv, "d:t")) != EOF) { // EOF == -1
		switch (ch) {
		case 'd':
			delivery = optarg; // argument after -d
			break;
		case 't':
			thick = 1;
			break;
		default:
			fprintf(stderr, "Unknown option: '%s'\n", optarg);
			return 1;
		}
		// printf("%d", optind); // optind = idx after reading current option and argument: 5(-d) 6(-t) in this case, use optind if need multiple optind
	}

	// now "Tomato Pineapple" is at end of argv[], optind = 4
	argc -= optind;
	argv += optind;

	if (thick)
		puts("Thick crust.");

	if (delivery[0])
		printf("To be delivered %s.\n", delivery);

	puts("Ingredients:");
	for (int i = 0; i < argc; i++)
		puts(argv[i]);
	return 0;
}

// getopt() stops reading options after --
// e.g. ./i_want_negative_number -c -- -4



/*----------pointer----------*/
// place the * close to the variable name not pointer type



/* sizeof() */
// sizeof() is not a function but a operator: calculated when compile

void myfun (char s[]) {
	printf ("%lu\n",sizeof(s));
}

int main() {
	char s[] = "Hello";
	printf ("%lu %lu\n",sizeof(int),sizeof(s)); // int: 4 (bytes); string: 6 (remember there's \0)
	myfun(s); // 8 because s is a pointer
	return 0;
}



/* pass by pointer */

void swap (int* x, int* y) {
	int z = *x; // remember * here
	*x = *y;
	*y = z;
}

int main() {
	int x = 1, y = 2;
	swap(&x, &y); // remember & here
	return 0;
}



/* array VS pointer */

	char s[] = "Hello, World!";
	chat *t = s;

	printf("%lu\n",sizeof(s)); // 14
	printf("%lu\n",sizeof(t)); // 8

	printf("%d\n", &s==s); // true
	printf("%d\n", &t==t); // false

	s = t; // error

// Array decays to pointer when pass to functions i.e. size of array is unknown



/* action on string */

	char msg_from_amy[] = "Don't call me";
	puts(msg_from_amy+6); // call me



/* 3[dose] is working */

	int dose[] = {1,2,3,1000};
	printf("I've taken %d and now I'm dead\n", 3[dose]); // 1000

// dose[3] == *(dose + 3) == *(3 + dose) == 3[dose]



/* string literals */
// string literals are constants in memory (read-only), hence can't be changed with pointer
	char *cards = "JQK";
	cards[2] = cards[1]; // Segmentation fault



// cards[] here is an array of the copy of the string literal "JQK"
	char cards[] = "JQK";
	cards[2] = cards[1]; // OK!



// if you want literal only
	const char *cards = "JQK"; // the same as char *cards = "JQK", but compiler would stop you if you want to change



/*----------Conditional Operator----------*/
// [condition] ? [if] : [else]
s = s + (b.sign == '-' ? "-" : "");
//The ? : expression means if (b.sign == '-') returns true, then the expression returns "-", otherwise returns "" (empty string).




/*----------Power----------*/
// https://www.tutorialspoint.com/c_standard_library/c_function_pow.htm
// x^y
double pow(double x, double y)


/*----------XOR----------*/
	int a = 32;
	printf("g%i\n", a ^ 33); // ^ = xor
	// 1



/*----------File I/O----------*/
// "r": read, "w": write, "a": append
// usually maximum 256 streams

	char line[80];
	FILE* in = fopen("in.txt", "r"); // return 0 if failed
	FILE* out = fopen("out.txt", "w");
	while (fscanf(in, "%79[^\n]\n", line) == 1) {
		if (strstr(line, "WTF"))
			fprintf(out, "%s\n", line);
	}
	fclose(in);
	fclose(out);



/*----------dynamic memory allocation----------*/

#include <stdlib.h>
	// malloc: Memory ALLOCation
	void* malloc (int size);
	// returns null if the memory allocation fails
	// void* is a general-purpose pointer

	// free
	void free (void *ptr);

//e.g.
	int size;
	int *a;

	printf("How many slots in the array?");
	scanf("%d", &size);
	printf("%d\n",size);
	
	a = (int*) malloc ( size * sizeof(int) );	//sizeof(int) function returns the number of bytes required by each int.
	for( int i = 0; i < size ; i++ )
		a[i] = i;
	for( int i = 0; i < size ; i++ )
		printf( "%d ",a[i]);


	free(a);  // All the 10 slots of memory are released

/* calloc() vs malloc() */
// https://vorpus.org/blog/why-does-calloc-exist/

void* buffer2 = calloc(count, size);

/* Equivalent to the calloc() call above -- OR IS IT?? */
void* buffer3 = malloc(count * size);
memset(buffer3, 0, count * size);

// calloc() prevents multiplication overflow
// calloc() is faster for large buffer
//   calloc() lives inside the memory allocator
//   memory comes from OS is already be zeroed, and calloc() knows it, so no memset again
//   memory in virtual memory -> not even accessing the RAM, and calloc() knows it
//     OS swap "virtual" page more effectively (on a page-by-page basis)

/* realloc(): Reallocate memory block */
int *arr = calloc(1000, sizeof(int)); // size of 1000 int
int *arr2 = realloc(arr, sizeof(int) * 2000); // size of 2000 int
free(arr2); // no need to free arr
// arr and arr2 may and may not be the same address



/* valgrind */
// $ gcc -g my_program.c (-g record line number so can debug easily)
// $ valgrind --leak-check=full ./a.out
// look at "total heap usage:"



/*----------struct----------*/
// all members are public
// cannot have member functions
// no constructor or destructor
// fields are stored in memory in the same order as in the code

struct student{
	char name[20];
	int uid;
	struct id identity;
};

	struct student a;	//need "struct" again
	struct student a = {"Chris Wong", 123, {"HK", "WW"}};
	struct student a = {.uid = 123, .identity = {"HK", "WW"}};
	...
	b = a; // copy data, unlike Java

/* typedef */
// possible to have the alias name the same as the structure name

struct student{
	char name[20];
	int uid;
};
typedef struct student student;
int main(){
	student a;
	...
}

// combine
typedef struct profile_t {
	string sid;
	string name;
	string phoneNum;
} Profile;

typedef struct { // skip struct name is ok
	string sid;
	string name;
	string phoneNum;
} Profile;



/* Pass by value */
typedef struct {
	int x;
	char y;
} mystruct;

void increment (mystruct sth){
	sth.x++;
	printf("Result: %d ", sth.x);
}

int main(){
	mystruct a = {89, 'a'};
	increment(a); // copy a new struct and pass to the function
	printf("%d\n", a.x);
	return 0;
}
// Result: 90 89

/* Pass by pointer */
void increment (mystruct *sth){
	sth->x++;
	printf("Result: %d ", sth->x);
}

int main(){
	mystruct a = {89, 64};
	increment(&a); // copy a new struct and pass to the function
	printf("%d\n", a.x);
	return 0;
}
// Result: 90 90



/*----------union----------*/
// reuse memory space
// reserve space for largest field

typedef union {
	short count;
	float weight;
	float volume;
} quantity;

	quantity q;
	q.volume = 3.7;

	quantity q = {.weight = 1.5};

	quantity q = {4}; // .count = 4, for 1st field only

// combine with struct
typedef struct {
	const char *name;
	quantity amount;
} fruit;

	fruit apples = {"apples", .amount.weight = 4.2};



/*----------enum----------*/
typedef enum {
	COUNT, POUNDS
} units_of_measure;
typedef union {
	short count;
	float weight;
} quantity;

typedef struct {
	const char *name;
	quantity amount;
	units_of_measure units;
} fruit;

int main(){
	fruit apples = {"apples", {.weight = 4.2}, POUNDS};
	switch (apples.units){
		case COUNT:
			printf("%d %s\n", apples.amount.count, apples.name);
			break;
		case POUNDS:
			printf("%f pounds of %s\n", apples.amount.weight, apples.name);
	}
	return 0;
}

// Changing default values of enum
enum suit_t {
	club = 0,
	diamonds = 10,
	hearts = 20,
	spades = 3,
};


/*----------Bit-field----------*/
// should be int or unsigned int
typedef struct {
	unsigned int eat_rice:1; // 1-bit of storage
	unsigned int month:4;
	unsigned int day:5;
} synth;



/*----------math.h----------*/
	//$ gcc sincos.c -lm
#include <math.h>
	sin(radian);
	cos(radian);



/*----------binary search tree----------*/
//height of empty tree is -1
//height of tree 1-2-3-4-5-6-7 is 6
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode treeNode;
struct treeNode{
	int key;
	treeNode *left;
	treeNode *right;
};

treeNode * Insert(treeNode *currentNode,int key){
	if (currentNode==NULL){
		treeNode *temp;
		temp = (treeNode *) malloc(sizeof(treeNode));
		temp->key = key;
		temp -> left = temp -> right = NULL;
		return temp;
	}
	if(key >( currentNode ->key)){
		currentNode ->right = Insert(currentNode ->right,key);
	}else if(key < (currentNode->key)){
		currentNode ->left = Insert(currentNode ->left,key);
	}
	return currentNode;
}

treeNode * Find(treeNode * currentNode, int key){
        if(currentNode ==NULL){
                // Element is not found
                return NULL;
        }
        printf("Access node %d \n", currentNode->key);
        if(key > currentNode->key){
                // Search in the right sub tree. 
                return Find(currentNode->right , key);
        }else if(key < currentNode->key){  
                // Search in the left sub tree. 
                return Find(currentNode->left , key);
        }else{   
                // Element Found 
                return currentNode;
        }
}

treeNode* FindMin(treeNode *currentNode){
        if(currentNode==NULL){
                /* There is no element in the tree */
                return NULL;
        }
        if(currentNode->left != NULL) 
                return FindMin(currentNode->left);
        else 
                return currentNode;
}

treeNode* FindMax(treeNode *currentNode){
        if(currentNode==NULL){
                /* There is no element in the tree */
                return NULL;
        }
        if(currentNode->right != NULL) 
                return FindMax(currentNode->right);
        else 
                return currentNode;
}

int main(){
	treeNode *root = NULL;
	root = Insert(root, 8);
     root = Insert(root, 10);
     root = Insert(root, 3);
     root = Insert(root, 1);
     root = Insert(root, 6);
     root = Insert(root, 14);
     root = Insert(root, 7);
     root = Insert(root, 4);
     root = Insert(root, 13);

	treeNode * temp;
        temp = Find(root,14);
        if(temp==NULL){
                printf("Element 14 not found\n");
        }
        else{
                printf("Element 14 Found\n");
        }  

	temp = FindMin(root);
	printf("Minimum element is %d\n", temp->key);
	temp = FindMax(root);
	printf("Maximum element is %d\n", temp->key);

	return 0;
}



/*----------AVL tree----------*/
//height of left and right subtrees differs not more than 1
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

typedef struct treeNode treeNode;
struct treeNode{
	int key;
	treeNode *left;
	treeNode *right;
};

treeNode * Insert(treeNode *currentNode,int key);
int maximum(int a, int b);
treeNode* balance_tree( treeNode * currentNode );
treeNode* R_rotation(treeNode *parent);
treeNode* L_rotation(treeNode *parent);
treeNode* LR_rotation(treeNode *parent);
treeNode* RL_rotation(treeNode *parent);
void PrintInorder(treeNode *currentNode);

int main(){
	treeNode *root = NULL;
	root = Insert(root, 5);
	root = Insert(root, 4);
	root = Insert(root, 3);
	root = Insert(root, 7);
	root = Insert(root, 9);
	root = Insert(root, 1);
	root = Insert(root, 2);
	root = Insert(root, 14);
	root = Insert(root, 10);
	
	PrintInorder(root);
	
	return 0;
}

treeNode * Insert(treeNode *currentNode,int key){
	if (currentNode==NULL){
    	#if DEBUG
    	    printf("Added key %d\n",key);
    	#endif
		currentNode = (treeNode *) malloc(sizeof(treeNode));
		currentNode->key = key;
		currentNode -> left = currentNode -> right = NULL;
	}
	else if(key >( currentNode ->key)){
    	currentNode ->right = Insert(currentNode ->right,key);
    	currentNode  = balance_tree( currentNode );
    }
    else if(key < (currentNode->key)){
    	currentNode ->left = Insert(currentNode ->left,key);
    	currentNode  = balance_tree( currentNode );
    }
    else{
         printf("fail! - duplicated key\n");
         exit(-1);
    }
	return currentNode;
}

int maximum(int a, int b){
    return (a > b ? a : b);
}

int get_height(treeNode *currentNode){ 
    if(currentNode == NULL)
        return -1;
    else{     
        int height = 1 + maximum(get_height(currentNode->left) ,get_height(currentNode->right)); 
        return height; 
    }
}

int get_balance(treeNode *currentNode){ 
	if(currentNode == NULL) 
		return 0;
	else 
		return get_height(currentNode->left) - get_height(currentNode->right); 
}

treeNode* balance_tree( treeNode * currentNode ){ 

	int height_diff = get_balance( currentNode ); 
     
	if( height_diff > 1 ){ 
		if(get_balance( currentNode -> left ) > 0){
			// Case 1 Right rotation
			currentNode = R_rotation(currentNode); 
		}else{  
			// Case 3 Double rotation: Left + Right
			currentNode = LR_rotation(currentNode); 
		}
	}else if( height_diff < -1 ){ 
	if(get_balance( currentNode ->right ) < 0){ 
			// Case 2 Left rotation
			currentNode = L_rotation(currentNode);
		}else{ 
			// Case 4 Double rotation: Right + Left
			currentNode = RL_rotation(currentNode); 
		}
	} 
	return currentNode ; 
}

treeNode* R_rotation(treeNode *parent){
	#if DEBUG 
		printf("R_rotation on %d\n", parent->key);
	#endif
	
	treeNode *child = parent->left; 
	parent->left = child->right;
	child->right = parent;
	return child;
}

treeNode* L_rotation(treeNode *parent){
	#if DEBUG 
		printf("L_rotation on %d\n", parent->key);
	#endif
	
	treeNode *child = parent->right; 
	parent->right = child->left;
	child->left = parent;
	return child;
}

treeNode* LR_rotation(treeNode *parent){
	#if DEBUG 
		printf("LR_rotation on %d\n", parent->key);
	#endif
	
	treeNode *child = parent->left; 
	parent->left = L_rotation(child); //make sure right subtree is NOT TALLER THAN left subtree
	return R_rotation(parent);
}

treeNode* RL_rotation(treeNode *parent){
	#if DEBUG 
		printf("RL_rotation on %d\n", parent->key);
	#endif
	
	treeNode *child = parent->right; 
	parent->left = R_rotation(child); //make sure right subtree is NOT TALLER THAN left subtree
	return L_rotation(parent);
}

void PrintInorder(treeNode *currentNode){
        if(currentNode ==NULL){
                return;
        }
        PrintInorder(currentNode->left);
        printf("%d ", currentNode->key);
        PrintInorder(currentNode->right);
}



/*----------Goto----------*/
#include <stdio.h>
 
int main () {

	/* local variable definition */
	int a = 10;

	/* do loop execution */
	LOOP:do {
   
		if( a == 15) {
			/* skip the iteration */
			a = a + 1;
			goto LOOP;
		}
		
		printf("value of a: %d\n", a);
		a++;
	  
	}while( a < 20 );
 
	return 0;
}



/*----------Function pointer----------*/
// return type (*pointer variable) (param. types);
	char** album_names(char* singer, int year);

	char** (*names_fn)(char*,int); // declare
	names_fn = &album_names;
	names_fn = album_names; // the same
	char** results = (*names_fn)("Sacha Distel", 1972);
	char** results = names_fn("Sacha Distel", 1972); // the same

	char** (*names_fn[])(char*,int); // declare array 

// use with enum
typedef enum {DUMP, SECOND_CHANCE, MARRIAGE} response_type; // they are 0, 1, 2

	void (*replies[])(char*) = {dump, second_chance, marriage};
	response_type sth = DUMP;
	(replies[sth])("Hello"); // no switch anymore!



/* qsort */
#include <stdlib.h>
void qsort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*)); // compar is the function pointer
// modify original array, not make a copy

// return +ve if a>b
int compare_scores(const void* score_a, const void* score_b){
	int a = *(int*)score_a; // void* need to be casted before use
	int b = *(int*)score_b;
	return a-b;
}

	int scores[] = {30, 70, 40, 55};
	qsort (scores, 7, sizeof(int), compare_scores);



/*----------Variadic function = variable arguments----------*/
#include <stdarg.h>
#include <stdio.h>

double average(int count, ...) { // need >= 1 arguments before variable arguments
	va_list ap;
	int j;
	double sum = 0;

	va_start(ap, count); // read arguments after count (count not included)
	for (j = 0; j < count; j++) {
		sum += va_arg(ap, int); // va_arg(va_list, data type)
	}
	va_end(ap); // tell the program that finish reading arguments

	return sum / count;
}
// va_start, va_arg, va_end are macros not functions


int main()
{
	printf("%f\n", average(3, 1, 2, 3) ); // there are total 3 no.
	// 2
	return 0;
}



/*----------Static library----------*/
/* e.g. /home/my_header_files/encrypt.h */

#include "/home/my_header_files/encrypt.h"
// or
#include <encrypt.h>
// 		$ gcc -I/home/my_header_files sandbox.c -o sandbox



/* e.g. + /home/my_header_files/encrypt.o */
// 		$ gcc -c encrypt.c -o encrypt.o // -c: separate compilation
// 		$ gcc -I/home/my_header_files sandbox.c /home/my_header_files/encrypt.o -o sandbox

/* Archive */
// if you have many .o files

// 		$ ar -rcs libhfsecurity.a encrypt.o checksum.o
// -r: updated if .a already exist
// -c: be created without feedback
// -s: create index
// lib*****.a

// 		$ gcc sandbox.c -lhfsecurity -o sandbox
// 		$ gcc sandbox.c -L/my_lib -lhfsecurity -o sandbox // if libhfsecurity.a is put in /my_lib

// check inside the archive
// 		$ nm libhfsecurity.a
// 0000000000000000 T _main <- start with T = function



/*----------Dynamic library----------*/

// Position-independent code
// 		$ gcc -I/includes -fPIC -c encrypt.c -o encrypt.o

// Turn into dynamic library
// 		$ gcc -shared encrypt.o -o /libs/libhfcal.so
// .dll on Bighard Windows, .so on Linux, .dylib on Mac
// !!!!! if need to rename library, recompile is needed !!!!!

// Execute
// 		$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/libs
// 		C:\code> PATH="%PATH%:C:\libs" // Bighard Win
// 		$ ./my_function



/*----------System Call----------*/

/* <time.h> */
#include <time.h>

	time_t t;
	time(&t);
	return asctime(localtime (&t));
}
// Thu Nov  9 16:10:37 2017



/* system() */
	system("echo 'Hello' | cowsay");
// _______
//< Hello >
// -------
//        \   ^__^
//         \  (oo)\_______
//            (__)\       )\/\
//                ||----w |
//                ||     ||










/*----------Multi-Process----------*/
#include <unistd.h>
#include <sys/types.h> // for (sth)_t

/* fork() */
pid_t fork(void);
// return 0 in child
// >0 = child pid
// <0 = fail



/* getpid(), getppid() */
pid_t getpid();
// return pid

pid_t getppid();
// return parent's pid



/* exit() */
#include <stdlib.h>

void exit(int status)
	exit(-1); // similar to return in main()
	_exit(-1); // the same, when exec() fails or no exec()
	_Exit(-1); // the same

	abort(); // abnomral termination


/* sleep() */
unsigned int sleep(unsigned int seconds);
unsigned int usleep(useconds_t milliseconds); // deprecated
unsigned int nanosleep(const struct timespec *req, struct timespec *rem);

/* wait(), waitpid() */
#include <sys/wait.h>

pid_t wait(int *statloc);
// wait until a child terminates
// return pid or -1 (error)
// child = zombie, terminate child immediately
// Note: zombie won't be terminated until wait(), if parent terminated before, init will handle it

	wait(NULL);

// get status
	int status;
	...
	wait(&status); // status = returned status by child



pid_t waitpid(pid_t pid, int *statloc, int options);
// return pid or -1 (error)

// pid: >0 = child's pid = pid
//       0 = child that is the same group as parent
//      -1 = any child = wait()

// options:    0 = nothing
//    WCONTINUED = if child continued but status not reported -> returned
//       WNOHANG = if child not available -> don't block and return 0
//     WUNTRACED = if child stopped but status not reported -> returned
// can bitwise e.g. (WCONTINUED | WNOHANG)



// macros
WIFEXITED(status) // true if terminated normally, WEXITSTATUS(status) fetch low-order 8 bits 
WIFSIGNALED(status) // true if terminated abnormally, WTERMSIG(status) fetch signal number causing termination
WIFSTOPPED(status) // true if stopped, WSTOPSIG(status) fetch signal number causing stop
WIFCONTINUED(status) // (waitpid only) true if continued after a job control stop



/* exec() */
int execl(const char *pathname, const char *arg0, ... /* (char *)0 */ );
int execle(const char *pathname, const char *arg0, ... /* (char *)0 */, char *const envp[]);
int execlp(const char *filename, const char *arg0, ... /* (char *)0 */ );
int execv(const char *pathname, char *const argv[]);
int execve(const char *pathname, char *const argv[], char *const envp[]);
int execvp(const char *filename, char *const argv[]);
// return -1 on error
// use after fork()

	execl("/bin/date", "date", NULL);
	execlp("ls", "ls", "-l", (char *)0); // (char *)0, NULL act the same



/* system() */
	system("ls");



/* Signal Handling */
// kill process
	kill(pid, SIGINT); // SIGINT = ctrl+C

// signal handler
void int_handler(int sig) {
	printf("Process %d received signal %d\n", getpid(), sig);
	exit(0);
}
	...
	signal(SIGINT, int_handler);
	...
	// if receive SIGINT later, do int_handler()



/* pipe() */
int pipe( int fd[2] );
// fd[0] is set up for reading, fd[1] is set up for writing

	int fd[2], nbytes;
	char string[] = "Hello, world!\n";
	char readbuffer[80];

	pipe(fd);
	if(fork() == 0) {
		/* Child process closes up input side of pipe */
		close(fd[0]);
		/* Send "string" through the output side of pipe */
		write(fd[1], string, (strlen(string)+1));
		exit(0);
	} else {
		/* Parent process closes up output side of pipe */
		close(fd[1]);
		/* Read in a string from the pipe */
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		printf("Received string: %s", readbuffer);
	}




























/*----------Multithreading----------*/
// $ gcc -pthread sandbox.c
#include <pthread.h>

// Create
int pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
/*
*tid			return pointer to created thread
*attr			attributes (stack size, NULL for default)
*start_routine	function this thread executes
*arg			arguments pass to thread function above

return 0 if success
*/

// Create thread with desired stack size
	size_t size = PTHREAD_STACK_MIN + 0x4000;
	/* PTHREAD_STACK_MIN : platform dependent */
	/* initialized with default attributes */
	ret = pthread_attr_init(&tattr);
	/* setting the size of the stack also */
	ret = pthread_attr_setstacksize(&tattr, size);
	/* only size specified in tattr */
	ret = pthread_create(&tid, &tattr, start_routine, arg);

// Terminate
void pthread_exit(void *value_ptr);
/*
*value_ptr		return value of the thread
*/

void pthread_join(pthread_t thread, void **value_ptr);
/*
thread			thread_id of the waiting thread
**value_ptr		return value of the thread
*/

// Get stack size
pthread_attr_getstacksize();



// Example: Hello, World!
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 10

typedef struct _thread_data_t {
	int tid;
	double stuff;
} thread_data_t;

void *thr_func(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;

	printf("hello from thr_func, thread id: %d\n", data->tid);

	pthread_exit(NULL);
}

int main(int argc, char **argv) {
	pthread_t thr[NUM_THREADS];
	int i, rc;

	thread_data_t thr_data[NUM_THREADS];


	for (i = 0; i < NUM_THREADS; ++i) {
		thr_data[i].tid = i;
		if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}
	}

	for (i = 0; i < NUM_THREADS; ++i) {
		pthread_join(thr[i], NULL);
	}

	return EXIT_SUCCESS;
}

// Example: Return value
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <omp.h>

/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
	int tid;
	long long limit;
	int num_threads;
	long long answer;
} thread_data_t;

/* thread function */
void *thr_func(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;
	int myID = data->tid;
	long long workload =  data->limit/data->num_threads + 1;
	long long start = myID * workload;
	long long end = start + workload > data->limit ? data->limit + 1: start + workload;
	long long my_sum = 0;
	long long i;
	for(i = start; i < end; i++) {
		my_sum += i;
	}
//	printf("thread[%d]:workload: %lld, start: %lld, end: %lld, thread_sum: %lld\n", 
//			data->tid, workload, start, end, my_sum);

#if 0	
	//*** Method 1: passing in the answer pointer ***//
	data->answer = my_sum; 
	pthread_exit(NULL);
#endif

#if 1	
	//*** Method 2: dynamic allocate memory ***//
	long long *answer = malloc(sizeof(*answer));
	*answer = my_sum;
	pthread_exit(answer);
#endif
}

int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Usage: %s <num to cal> <NUM_THREADS>\n", argv[0]);
		return EXIT_SUCCESS;
	}
	long long limit = atoll(argv[1]);
	int NUM_THREADS = atoi(argv[2]);
	printf("Using %d threads to calculate the sum form 1 to %lld.\n", NUM_THREADS, limit);
	pthread_t thr[NUM_THREADS];
	int i, rc;
	thread_data_t thr_data[NUM_THREADS];
	double timer = omp_get_wtime();
	/* create threads */
	for (i = 0; i < NUM_THREADS; ++i) {
		thr_data[i].tid = i;
		thr_data[i].limit = limit;
		thr_data[i].num_threads = NUM_THREADS;
		if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}
	}
	long long sum = 0;
#if 0
	//*** Method 1 ***//
	for (i = 0; i < NUM_THREADS; ++i) {
		pthread_join(thr[i], NULL);
		sum += thr_data[i].answer;
	}
#endif
#if 1 	
	//*** Method 2 ***//
	long long *thread_sum;
	for (i = 0; i < NUM_THREADS; ++i) {
		pthread_join(thr[i], (void**) &thread_sum);
		sum += *thread_sum;
	}
#endif
	timer = omp_get_wtime() - timer;
	printf("sum is : %lld, time use: %f\n", sum, timer); 
	return EXIT_SUCCESS;
}



// Semaphore = Lock
// process/thread both OK!

#include <semaphore.h>

sem_init(sem_t *sem, int pshared, unsigned int value)
/*
	*sem		ptr to semaphore obj
	pshared		0 if semaphore shares among threads
	value		initial value of semaphore
*/

sem_wait(sem_t *sem) // request a key
sem_trywait(&right_chopstick_sem) // 0 if wait successfully
sem_post(sem_t *sem) // return the key

int sem_destroy(sem_t *sem)
// destroy by the thread created it

// Example
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TOTAL_COUNT 10000


sem_t sem1;

int count = 0;

void *func(void *arg) {
	int i;
	for(i = 0; i < TOTAL_COUNT; i++) {
		sem_wait(&sem1);
		count++;
		if ((count % 2500) == 0) {
			int id = *((int*)arg);
			printf("Thread %d: current count = %d\n", id, count);
		}
		sem_post(&sem1);
	}
	pthread_exit(0);
}

int main() {
	sem_init(&sem1,0,1) ; 
	pthread_t thread1, thread2,thread3;

	int id1 = 1;
	if(pthread_create(&thread1, NULL, &func, (void*)&id1)) {
		printf("ERROR creating thread 1\n");
		exit(1);
	}  
	int id2 = 2;
	if(pthread_create(&thread2, NULL, &func, (void*)&id2)) {
		printf("ERROR creating thread 2\n");
		exit(1);
	}
	int id3 = 3;
	if(pthread_create(&thread3, NULL, &func, (void*)&id3)) {
		printf("ERROR creating thread 3\n");
		exit(1);
	}

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	if (count != 3 * TOTAL_COUNT)
		printf("Error! current count is %d. total count should be %d\n", 
				count, 2 * TOTAL_COUNT);
	else
		printf("OK. current count is %d\n", count);
	sem_destroy(&sem1);

	return 0;
}

// Example: Multiple threads on 1 Semaphore
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#define NUM_CHOPSTICKS 3
#define NUM_PEOPLE 10


sem_t left_chopstick_sem;
sem_t right_chopstick_sem;

int count = 0;

void *eat(void *arg) {
	int tid = *(int*) arg;
	int isFull = 0;
	time_t t;
	/* Intializes random number generator */
	srand((unsigned) time(&t));
	while(isFull == 0)
	{
		sem_wait(&left_chopstick_sem);
		printf("Philosopher(%d) picks up left chopstick\n", tid);
		fflush(stdout);
		if(sem_trywait(&right_chopstick_sem) == 0)
		{
			t = time(NULL);
			printf("Philosopher(%d) picks up right chopstick\n", tid);
			fflush(stdout);
			printf("\tPhilosopher(%d): eating... \n", tid);
			fflush(stdout);
			sleep(rand() % 15);  // randomly sleep 
			printf("\tPhilosopher(%d): Yummy yummy!\n", tid);
			fflush(stdout);
			isFull = 1;
			sem_post(&right_chopstick_sem);
			printf("Philosopher(%d) puts down right chopstick\n", tid);
			fflush(stdout);
		}
		sem_post(&left_chopstick_sem);
		printf("Philosopher(%d) puts down left chopstick\n", tid);
		fflush(stdout);
	}
	pthread_exit(0);
}

int main() {
	sem_init(&left_chopstick_sem, 0, NUM_CHOPSTICKS) ; 
	sem_init(&right_chopstick_sem, 0, NUM_CHOPSTICKS) ; 
	pthread_t threads[NUM_PEOPLE];
	int tids[NUM_PEOPLE];
	int i, rc;
	for( i = 0; i < NUM_PEOPLE; i++) {
		tids[i] = i;
		if ((rc = pthread_create(&threads[i], NULL, eat, &tids[i]))){
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}
	}

	for( i = 0; i < NUM_PEOPLE; i++) {
		pthread_join(threads[i], NULL);
	}
	sem_destroy(&left_chopstick_sem);
	sem_destroy(&right_chopstick_sem);

	return 0;
}



// Producer & Consumer
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct sem_pack {
	int tid;
	sem_t *item;
	sem_t *space;
} sem_pack;


void *producer(void *arg)
{
	sem_pack * pack = (sem_pack*) arg;
	int tid = pack->tid;
	sem_t *item = pack->item;
	sem_t *space = pack->space;
	int *num_sem = malloc(sizeof(num_sem)); 

	for (int i=0;i<5;i++) {
		sem_getvalue(space, num_sem);
		printf("th[%d] before wait space(%p), %d\n", 
				tid, space, *num_sem);
		sem_wait(space);
		sem_getvalue(space, num_sem);
		printf("th[%d] space(%p) get, %d\n", 
				tid, space, *num_sem);

		sem_getvalue(item, num_sem);
		printf("th[%d] before post item(%p), %d\n", 
				tid, item, *num_sem);
		sem_post(item);
		sem_getvalue(item, num_sem);
		printf("th[%d] item(%p) posted, %d\n", 
				tid, item, *num_sem);
	}
	free(num_sem);
	pthread_exit(0);
}

void *consumer(void *arg)
{

	sem_pack * pack = (sem_pack*) arg;
	int tid = pack->tid;
	sem_t *item = pack->item;
	sem_t *space = pack->space;
	int *num_sem = malloc(sizeof(num_sem)); 
	for (int i=0;i<5;i++) {
		sem_getvalue(item, num_sem);
		printf("th[%d] before wait item(%p), %d\n", 
				tid, item, *num_sem);
		sem_wait(item);
		sem_getvalue(item, num_sem);
		printf("th[%d] sem(%p) get item, %d\n", 
				tid, item, *num_sem);


		sem_getvalue(space, num_sem);
		printf("th[%d] before post space(%p), %d\n", 
				tid, space, *num_sem);
		sem_post(space);
		sem_getvalue(space, num_sem);
		printf("th[%d] space(%p) posted, %d\n", 
				tid, space, *num_sem);
	}
	free(num_sem);
	pthread_exit(0);
}

sem_t sem_item;
sem_t sem_space;

int main(int argc, char **argv)
{
	int num_threads = 2;
	sem_init(&sem_item, 0, 0);
	sem_init(&sem_space, 0, 1);
	int *num_sem = malloc(sizeof(num_sem));
	sem_getvalue(&sem_item, num_sem);
	printf("Initial item value %d\n", *num_sem);
	sem_getvalue(&sem_space, num_sem);
	printf("Initial space value %d\n", *num_sem);

	sem_pack packs[num_threads];
	pthread_t th[num_threads];

	for (int i = 0; i < num_threads; i++) {
		packs[i].tid   = i;
		packs[i].item  = &sem_item;
		packs[i].space = &sem_space;
	}


	if(pthread_create(&th[0], NULL, producer, &packs[0])) 
		printf("Error creating thread 0\n");

	if(pthread_create(&th[1], NULL, consumer, &packs[1])) 
		printf("Error creating thread 1\n");

	for (int i = 0; i < num_threads; i++) {
		pthread_join(th[i], NULL);
	}
	sem_destroy(&sem_item);
	sem_destroy(&sem_space);
	free(num_sem);
	return 0;
}



/*----------Static Stack Usage Analysis----------*/
/* 
https://gcc.gnu.org/onlinedocs/gcc-6.1.0/gnat_ugn/Static-Stack-Usage-Analysis.html
	$ gcc sandbox.c -fstack-usage -o sandbox
sandbox.so:
	sandbox.c:4:5:main	32	static

https://stackoverflow.com/questions/4175281/what-does-it-mean-to-align-the-stack
This code "and"s ESP (stack pointer) with 0xFFFFFFF0, aligning the stack with the next lowest 16-byte boundary
*/

/*----------Avoid Warning: unused parameters----------*/
// https://stackoverflow.com/questions/4647665/why-cast-an-unused-function-parameter-value-to-void
	(void) the_variable_that_not_used_intentionally;

/*----------Pre-processing----------*/
// https://docs.microsoft.com/en-us/cpp/preprocessor/hash-undef-directive-c-cpp?view=vs-2019
// https://stackoverflow.com/questions/216865/undef-ing-in-practice

#define something
#undef something

// something does not exist anymore

/*----------Compiler (GCC) specific macros----------*/

/* Date and time at compile time */

__DATE__ // == "Jan  3 2020"
__TIME__ // == "16:14:36"
