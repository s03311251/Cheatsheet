#!/usr/bin/python
# https://docs.python.org/2.7/

# I/O

print "Hello world!"

print "Hello",	# no newline but a space
print "world!"

s = raw_input("What's your name? ")	
# input() in python3
# "What's your name? " is printed
# always get string
n = int(s)
print "Half of " + s + " is " + str(n/2)


# VARIABLE

a = 5		# a is an int
b = 3.0		# b is a float
c = "10"	# c is a string

	# ++, -- are not supported !!!!!
 
print a/2 
print b/2 
print a/b # int divided by float -> 1.66666666667


## CHECK IF EXIST
## https://stackoverflow.com/questions/843277/how-do-i-check-if-a-variable-exists

if 'my_local_var' in locals():
	pass

if 'my_global_var' in globals():
    pass

if hasattr(obj, 'my_attr_in_obj'):
    pass

if hasattr(self, 'my_attr_in_obj'):
    pass

### Use exception
try:
	myVar
except NameError:
	pass



# ROUND FLOAT
round(1.2345, 2) # 1.23
round(1234, -3) # 1000.0



# STRING
s = "abc" + "def"  # string concatenation
print s            # print the entire string s
print s[3]         # character access
print s[1:5]       # substring from s[1] to s[4]
print s[:4]        # substring from start to s[3]
print s[1:]        # substring from s[1] to the end
print len(s)       # string length

## SPLIT
# e.g.
line = "0,Problem Solving in C++,104.26,0.jpg, ..."
words = line.split(',')
	# words = {"0","Problem Solving in C++","104.26","0.jpg"," ..."}
	# words[0] = "0"

## TO BYTEARRAY
mybytes = mystr.encode('utf-8') # more Pythonic
mybytes = bytes(mystr, 'utf-8') # OK too

## REMOVE SOME CHARATERS
mystr = 'abcdeabced'
mystr = mystr.strip('a')
# 'bcdeabced'

## FIND APPEARANCE
### https://www.tutorialspoint.com/python/string_find.htm

str1 = "this is string example....wow!!!";
str2 = "exam";

print str1.find(str2) # 15
print str1.find(str2, 10) # 15
print str1.find(str2, 40) # -1

### https://www.tutorialspoint.com/python/string_rfind.htm

str1 = "this is really a string example....wow!!!";
str2 = "is";

print str1.rfind(str2)
print str1.rfind(str2, 0, 10)
print str1.rfind(str2, 10, 0)

## FORMAT
### https://pyformat.info/
print ('%s %s' % ('one', 'two')) # old
print ('{} {}'.format('one', 'two')) # new
'{1} {0}'.format('one', 'two') # -> two one

### data type
'%d' % (42,) 
'{:d}'.format(42) # new
'%4d' % (42,) # padding
'{:4d}'.format(42) # new

### aligned
'%10s' % ('test',) # right-aligned, padded to 10 char
'{:>10}'.format('test') # new

'%-10s' % ('test',) # left-aligned, padded to 10 char
'{:10}'.format('test') # new

'{:^10}'.format('test') # centre-aligned

### placeholder
data = {'first': 'Hodor', 'last': 'Hodor!'}
'%(first)s %(last)s' % data

'{first} {last}'.format(first='Hodor', last='Hodor!') # new

### list and dictionary
data = [4, 8, 15, 16, 23, 42]
'{d[4]} {d[5]}'.format(d=data) # 23 42

person = {'first': 'Jean-Luc', 'last': 'Picard'}
'{p[first]} {p[last]}'.format(p=person) # Jean-Luc Picard

### datetime
from datetime import datetime
'{:%Y-%m-%d %H:%M}'.format(datetime(2001, 2, 3, 4, 5)) # 2001-02-03 04:05

### f-string (Python 3.6+)
a = 5
b = 10
print (f'Five plus ten is {a + b} and not {2 * (a + b)}.')



# CHANGE OF DATA TYPES
	# temporatory

a = "12" + "3"
b = 3
print a
print int(a) + b	# 126
print a + str(b)	# 1233



# LIST
	# list is dynamic array in Python
	# http://docs.python.org/2/tutorial/datastructures.html

L = []
L = [expression, ...]
L = [expression for variable in sequence]

A = B = [] # both names will point to the same list
A = []; B = A # both names will point to the same list
A = []; B = [] # independent lists
# ; -> several Python statements on the same line

len(L) # return number of items in the list

## list to string
list1 = ['1', '2', '3']
str1 = ''.join(list1)
str1 = ' '.join(list1) # separated with space

## list of int to string
list1 = [1, 2, 3]
str1 = ' '.join(str(e) for e in list1) # '1 2 3'

## list of strings to list of int
results = map(int, results) # Python 2
results = list(map(int, results)) # Python 3

## string to list of int
## '3 6 99' -> [3, 6, 99]
list(map(int, results.split()))

## concatenate
listone = [1,2,3]
listtwo = [4,5,6]
mergedlist = listone + listtwo

## append
results.append(x)
results[len(results):] = [x] # the same

## for with index
for index, item in enumerate(items):
    print(index, item)

## remove
your_list.pop(1) # item_index, return popped item (last item)
your_list.remove('a') # item
del your_list[1] # item_index
del your_list[1:] # item_index

## sort
## https://wiki.python.org/moin/HowTo/Sorting
student_tuples = [
        ('john', 'A', 15),
        ('jane', 'B', 12),
        ('dave', 'B', 10),
]
sorted(student_tuples, key=lambda student: student[2])   # sort by age
sorted(student_tuples, key=lambda student: student.age)   # the same if student[2] == student.age
student_tuples.sort(key=lambda student: student[2])   # the same
## [('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]

## lingest sublist
a = [[9],[2,3]]
max (a) # [9]
max (a,key=len) # [2, 3]

## Empty list with certain size
## https://stackoverflow.com/questions/10712002/create-an-empty-list-in-python-with-certain-size
l = [None]*10
## [None, None, None, None, None, None, None, None, None, None]

## Queue
from collections import deque
queue = deque(["Eric", "John", "Michael"])
queue.append("Terry")           # Terry arrives
queue.append("Graham")          # Graham arrives
queue.popleft()                 # The first to arrive now leaves: 'Eric'



# DICTIONARY
# use {} instead of []
dict = {'Name': 'Zara', 'Age': 7, 'Class': 'First'}

dict['Age'] = 8; # update existing entry
dict['School'] = "DPS School"; # Add new entry

print ("dict['Age']: ", dict['Age'])
print ("dict['School']: ", dict['School'])

for key, value in d.iteritems(): # Python 2
for key, value in d.items(): # Python 3

## insert
dict.update({'a':1}) # OR
dict.update(dict(a=1))

## Ctrl+C
if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print 'Interrupted'
        sys.exit(0)

## KeyError
try:
	print (dict['NotExist'])
except KeyError:
	print ('Key NotExist does not exist')

# SET
basket = set() # empty set

basket = {'apple', 'orange', 'apple', 'pear', 'orange', 'banana'} # After Python 2.7
print(basket) # {'orange', 'banana', 'pear', 'apple'}
basket.add('plum')
'orange' in basket  # True
'crabgrass' in basket # False

printstr = ''
for item in basket:
	printstr = printstr + item + '\n'
print(printstr)



# TUPLE
xxx = (1, 2, 3)




# MATHEMATICAL FUNCTIONS
	# https://docs.python.org/2.7/library/math.html?highlight=power
import math

round(10/3,3)	# 3 decimal places
math.pow(a,b)	# x^y
math.ceil(a/b)	# (float) smallest integer value greater than or equal to x



# IF-ELSE
	# condition is similar to C++
	# Python uses indentation to determine the body
	# use “and”, “or”, “not” !!!!!

if condition:	# : is important!!!!!
	statement
	statement
elif condition:
	statement
else:
	statement

	# eg
a = 10
if a < 5:
	a += 1
	a += 2
print a
	# even indentation not same for 2 "if" -> OK



# LOOP

x = 10
while x >= 0:
	print x,
	x -= 1	# no ++ -- in Python !!!!!

for i in list:
	statement
	statement

	# e.g.
for season in ["spring", "summer", "autumn", "winter"]:
	print "The " + str(i) + "-th season is " + season
	i += 1

	# RANGE
for i in range( 0 , 71 ):
	if i % 7 == 0:
		print i,
	# 0 7 14 21 28 35 42 49 56 63 70

	# BREAK and CONTINUE
n = int( raw_input("Please enter a number: "))
found = 0
for i in range(2,n-1): #for i in [2, ..., n-1 ]
	if n%i==0:
		print str(n) + " can be divided by " + str(i)
		found = 1
		break	 #finish the while loop immediately
if n==1 or found ==1:
	print str(n) + " is not a prime number."
else:
	print str(n) + " is a prime number."

	# INFINITE LOOP
while True:
    do_something()



# Default arguments in methods
def student(firstname, lastname ='Mark', standard ='Fifth'):
	print(firstname, lastname, 'studies in', standard, 'Standard') 



# Class
class playPlayer(threading.Thread): # parent
	def __init__(self):
		threading.Thread.__init__(self) # <- parent instructor
		self.queue = deque([]) # self. first

	def enqueue(self, filename): # remember include self in arguments
		pass








# File manipulation
	# with open( "filename", "mode" ) as f:
	# f.close()

with open ("number.txt", "r") as f:	# f is file object refering to file content
	count = f.read()
	n = int (count)
f.close()

with open ("number.txt", "w") as f:
	f.write( str(n+1) )
f.close()

	# r		read only, file pointer placed at beginning of file
	# r+	read and write, file pointer placed at beginning of file
	# w		write only, overwrite if exists, create if not exist
	# w+	read and write, overwrite if exists, create if not exist
	# a		append, file pointer placed at end of file, create if not exist
	# a+	read and a = datetime.now()

	# Get last line
	with open ("number.txt", "r") as f:
		last_line = f.readlines()[-1]
	f.close()

	# Remove last line
	with open ("number.txt", "r") as f:
		lines = f.readlines()
	f.close()

	with open ("number.txt", "w") as f:
		f.writelines(lines[:-1])
	f.close()

## Find files
## https://stackoverflow.com/questions/3964681/find-all-files-in-a-directory-with-extension-txt-in-python
import os
for file in os.listdir("/mydir"):
    if file.endswith(".txt"):
        print(os.path.join("/mydir", file))

### recursively
import os
for root, dirs, files in os.walk("/mydir"):
    for file in files:
        if file.endswith(".txt"):
             print(os.path.join(root, file))



# DYNAMIC WEBSITES
	# print "Content-type:text/html\n\n", \n\n for recognization by browsers
	# """ """ multiple lines, don't care "

#!/usr/local/bin/python
# \n\n for recognization by browsers
# """ """ multiple lines, don't care "
url = "http://i1-test.cs.hku.hk/~h3527142/store1/"
usdexchange = 7.8

print "Content-type:text/html\n\n"
print "<html>\n"
print "<body>\n"
print "<link rel=\"Stylesheet\" href=\"" + url + "style.css\" type=\"text/css\" >\n"
print "<img src=\""+url+"banner.jpg\" > \n"
print """<table>
<tr>
<th>ProductID</th>
<th>Name</th>
<th>Unit Price (HKD)</th>
<th>Unit Price (USD)</th>
<th>Product Details</th>
</tr>"""
with open("Catalogue.txt","r") as input:
	for line in input:	# input is already a list, when lines as entries
		words = line.split(',')
		print "<tr>"
		print "<td>"+words[0]+"</td>"
		print "<td>"+words[1]+"</td>"
		print "<td>"+str(float(words[2]))+"</td>"
		print "<td>"+str(round( float(words[2])/usdexchange , 2 ))+"</td>"
		print "<td><a href=\""+words[4]+"\"> <img src=\""+url+words[3]+"\"></a></td>"
input.close()
print "</body>\n</html>"



# XML (Extensible Markup language)
	# Elements
		# <element-name> Content </element-name>
		# Names cannot start with the letters “xml” (or XML, or Xml, etc).
		# Names cannot start with a number or punctuation character. 
		# Names cannot contain spaces. 

		# Root Element
			# e.g. <WeatherForecast> is the root element
				<?xml version = "1.0" encoding = "UTF-8" ?>
				<WeatherForecast>
					  <City name = "Hong Kong" >
							<Weather date = "2013-4-23">Light Rain</Weather>
							<Weather date = "2013-4-24">Sunny</Weather>
					  </City>
					  <City name = "Beijing" >
							<Weather date = "2013-4-23">Sunny</Weather>
							<Weather date = "2013-4-24">Thunder Storm</Weather>
					  </City>
				</WeatherForecast>

	# Attribute
		# <element-name attribute-name = "attribute-value">
		# Attribute value MUST be enclosed by quotes

#!/usr/bin/python
import xml.etree.ElementTree as ET
# ET as the name to any libraries defined under xml.etree.ElementTree

# parse the XML and returns an ElementTree object
tree = ET.parse("Weather.xml")

# get the root Element node of tree
r = tree.getroot()

# name of the root Element node
print r.tag
# r.tag == "WeatherForecast"

# traverse the child of r
listOfCities = r.findall("City")
	# listOfCities is a list of Elements
for c in listOfCities:
	# c.get() return the value of attribute named "name"
	cityName = c.get("name")
	listOfWeather = c.findall("Weather")
	for w in listOfWeather:
		# w.text return the value of the text node
		if w.text == "Sunny":
			print cityName,
			weatherDate = w.get('date')
			print weatherDate,
			print w.text

# WeatherForecast
# Hong Kong 2013-4-24 Sunny
# Beijing 2013-4-23 Sunny

# DATE
# https://docs.python.org/2/library/datetime.html

## Difference between dates
from datetime import datetime

a = datetime.now()
b = datetime(2017,6,27)
a.hour, a.minute, a.second

c = a-b # datetime.timedelta
c.hours # In hours
c.total_seconds() # In seconds (c.seconds give c.total_seconds() (mod 24))



# FUNCTION
def foo():
	# if need global variable
	global bar

## Variable arguments
def manyArgs(*arg):
	for a in arg:
		print a
manyArgs(1,2,3)

## Lambda Functions = condom functions
def f (x):
	return x**2
print f(8) # 64

g = lambda x: x**2
print g(8) # 64



## function override
[Method overriding in PythonThe Digital Cat](http://blog.thedigitalcatonline.com/blog/2014/05/19/method-overriding-in-python/)

class Parent(object): # inherit object so that super(Parent, self) can be used
	def sth(self):
		pass

class Child(Parent):
	def sth(self):
		Parent.sth() # old method
		super(Parent, self).sth() # Python2
		super().sth() # Python3



# CUT WITH DELIMITER

line = "2017/6/26 80000"
data = line.split(" ")
print data[0] # 2017/6/26

	# Multiple Delimiters
import re

line = "2017/6/26 80000"
data = re.split("/| ",line)
print data[0] # 2017



# PARSE COMMAND-LINE ARGUMENTS
import sys

# $ python test.py arg1 arg2 arg3
print 'Number of arguments:', len(sys.argv) # Number of arguments: 4
print 'Argument List:', str(sys.argv) # Argument List: ['test.py', 'arg1', 'arg2', 'arg3']



# SLEEP
import time

time.sleep(10) # 10 sec



# NOTIFICATION
import notify2

notify2.init("App Name")

notice = notify2.Notification("Title", "Content", "Icon.jpg")
notice.set_timeout(1000) # 1 sec
notice.set_timeout(notify2.EXPIRES_NEVER) # never
notice.set_urgency(notify2.URGENCY_CRITICAL) # become red
notice.set_urgency(notify2.URGENCY_LOW) # become grey
notice.show()

notice.update("New Title", "New Content") # Change content
notice.show()



# SYNCHRONIZED BLOCK IN MULTITHREADING

lock = threading.Lock()
lock = threading.RLock() # block other threads only = can do recursion 

lock.acquire()
try:
	# ... access shared resource
finally:
	lock.release() # release lock, no matter what



# EVENT IN MULTITHREADING
# a client thread can wait for the flag to be set
event.wait()

# a server thread can set or reset it
event.set()
event.clear()



# QUEUE IN MULTITHREADING
# can share resources
import queue
my_queue = queue.Queue()
my_queue.put(1)
my_queue.get()
my_queue.quque # return deque <- list with queue implementation

my_queue.empty() # empty() then get() -> not threadsafe
try: # threadsafe
	my_queue.put(1)
except Queue.Empty:
	# do sth


# RANDOM
import random
random.random() # float:  0.0 <= x < 1.0
random.uniform(2.5, 10.0) # float:  2.5 <= x < 10.0
random.randrange(10) # Integer from 0 to 9 inclusive
random.randrange(0, 101, 2) # Even integer from 0 to 100 inclusive

random.choice(['win', 'lose', 'draw']) # Single random element from a sequence
# 'draw'

deck = 'ace two three four'.split()
random.shuffle(deck) # Shuffle a list
deck
# ['four', 'two', 'ace', 'three']

random.sample([10, 20, 30, 40, 50], k=4) # Four samples without replacement
# [40, 10, 50, 30]



# NaN
x = float('nan')
import math
if math.isnan(x): # numpy.isnan(x) ok too
	print "Yes, it's nan"



# __main__
if __name__ == '__main__':
    do_sth()



# Numpy
## numpy array
a = np.array((1,2,3))
b = np.array((2,3,4))
c = np.hstack((a,b))
# array([1, 2, 3, 2, 3, 4])

a = np.array([[1],[2],[3]])
b = np.array([[2],[3],[4]])
np.hstack((a,b))
# array([[1, 2],
#        [2, 3],
#        [3, 4]])



# Reimport a package
>>> import mypackage
>>> import importlib
>>> importlib.reload(mypackage)



# Subprocess
import subprocess

## Blocking
subprocess.call(['sleep', '5'])
subprocess.call('sleep 5', shell=True)

ls_output = subprocess.check_output('ls *.mp3', shell=True)

## Hide output
## https://stackoverflow.com/questions/11269575/how-to-hide-output-of-subprocess-in-python-2-7
import os
FNULL = open(os.devnull, 'w')
retcode = subprocess.call(['echo', 'foo'], stdout=FNULL, stderr=subprocess.STDOUT)

## Non-blocking
## https://stackoverflow.com/questions/16071866/non-blocking-subprocess-call
## https://docs.python.org/3/library/subprocess.html#popen-objects
p = subprocess.Popen(['sleep', '5'])
p.poll() # terminated: == return code (usually 0), not: == None
p.wait(timeout=1) # timeout in seconds, raise subprocess.TimeoutExpired


# SIGTERM handler
# https://stackoverflow.com/questions/18499497/how-to-process-sigterm-signal-gracefully
try:
    print "Hello"
    i = 0
    while True:
        i += 1
        print "Iteration #%i" % i
        sleep(1)
finally:
    print "Goodbye"







