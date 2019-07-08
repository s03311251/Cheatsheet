/*----------Install----------*/
/*
# Install
[Source](http://wiki.ros.org/kinetic/Installation/Ubuntu)

		sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
		sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
		sudo apt-get update && sudo apt-get install ros-kinetic-desktop-full
		sudo apt-get install python-rosinstall python-rosinstall-generator python-wstool build-essential



# Initialize rosdep
		sudo rosdep init
		rosdep update
		echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc



# Setup workspace
		mkdir -p ~/Documents/Megaman_2/world/src
		cd ~/Documents/Megaman_2/world/
		catkin_make
		echo "source ~/Documents/Megaman_2/world/devel/setup.bash" >> ~/.bashrc
		echo $ROS_PACKAGE_PATH
should give sth like "/home/s03311251/Documents/Megaman_2/world/src:/opt/ros/kinetic/share"
*/



/*----------Some useful command----------*/
/*
# rospack

## Find
		rospack find serial
/opt/ros/kinetic/share/serial

## Dependencies
stored in package.xml
(1st order dependencies)
		rospack depends1 beginner_tutorials
roscpp
rospy
std_msgs

(Indirect dependencies)
		rospack depends beginner_tutorials
cpp_common
rostime
...(ry



# roscd
		roscd serial
now located in /opt/ros/kinetic/share/serial

		roscd log



# rosls
		rosls serial
cmake  package.xml



# catkin

## Create Package
		cd ~/Documents/Megaman_2/world/src
		catkin_create_pkg <package_name> [depend1] [depend2] [depend3]
		catkin_create_pkg beginner_tutorials std_msgs rospy roscpp

## Build
		cd ~/Documents/Megaman_2/world
		catkin_make
		. devel/setup.bash (add the workspace to your ROS environment)

*/


/*----------Run ros----------*/
/*
# Core
		roscore



# Node
		rosnode list
		rosnode info /rosout
When sth wrong
		rosnode cleanup



# Run
		rosrun [package_name] [node_name]
e.g.	rosrun turtlesim turtlesim_node

## Use another name in list (remapping argument)
		rosrun turtlesim turtlesim_node _name:=my_turtle (get_param('~hello'))
		rosnode ping my_turtle

## Show relationship with rqt graph
		rosrun rqt_graph rqt_graph
		rqt_graph		// the same
*/



/*----------Topics----------*/
/*
		rostopic --help

### Topic list
		rostopic list --help
		rostopic list -v

### Show data of a topic
		rostopic echo /turtle1/cmd_vel

### Show type of message in a topic
		rostopic type /turtle1/cmd_vel
-> geometry_msgs/Twist
		rosmsg show geometry_msgs/Twist
geometry_msgs/Vector3 linear
  float64 x
  float64 y
  float64 z
geometry_msgs/Vector3 angular
  float64 x
  float64 y
  float64 z

Combo:	rostopic type /turtle1/cmd_vel | rosmsg show

#### Send messages directly
		rostopic pub [topic] [msg_type] [args]
e.g.	rostopic pub -1 /turtle1/cmd_vel geometry_msgs/Twist -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, 1.8]'
args in YAML syntax (http://wiki.ros.org/ROS/YAMLCommandLine)

### Show frequency of data published
		rostopic hz /turtle1/pose

### Display 
		rosrun rqt_plot rqt_plot
Type /turtle1/pose/x



### Create own message
http://wiki.ros.org/ROS/Tutorials/CreatingMsgAndSrv

e.g.
In msg/Num.msg:
int64 num

In package.xml, uncommend:
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>

In CMakeLists.txt:
add_message_files(
  FILES
  Num.msg
)
generate_messages(
  DEPENDENCIES
  std_msgs
)
*/

/*----------Service----------*/
/*
# print information about active services
		rosservice list



# service type
		rosservice type [service]

e.g.	rosservice type /clear
			std_srvs/Empty <- i.e. it takes no argument

e.g.	rosservice type /spawn
			turtlesim/Spawn
Combo	rosservice type /spawn | rossrv show
			float32 x
			float32 y
			float32 theta
			string name
			---
			string name



# service call
		rosservice call [service] [args]
e.g.	rosservice call /clear

After we know service type
		rosservice call /spawn 2 2 0.2 ""
*/



/*----------Parameter----------*/
/*
# YAML markup language
e.g.	List		[1, 2, 3]
		Dictionary	{a: b, c: d}

# available data type
 * 32-bit integers
 * booleans
 * strings
 * doubles
 * iso8601 dates
 * lists
 * base64-encoded binary data

# parameter list
		rosparam list
		/background_b
		/background_g
		/background_r
		/rosdistro
		/roslaunch/uris/host_s03311251_thinkpad_x220__42207
		/rosversion
		/run_id

# get & set
		rosparam get [param_name]
		rosparam set [param_name] [value]

e.g.	rosparam get /
			(get all)

e.g.	rosparam get /background_r
			69
		rosparam set /background_r 255
		rosservice call /clear
			(background change to purple)

# dump & load
e.g.	rosparam dump params.yaml

		rosparam load params.yaml copy
		rosparam get /copy/background_b

# Parameter Server

## NodeHandler Version

*/
	ros::NodeHandle nh("~"); // "~" - private, so that you can use relative_name
	std::string global_name, relative_name, default_param;

	// ### Parameter exist
	if (nh.hasParam("my_param")){
		// ...
	}

	// ### Get Parameter
	// return false if not exist/wrong type
	if (nh.getParam("/global_name", global_name)) {
		// ...
	}
	if (nh.getParam("relative_name", relative_name)) {
		// ...
	}

	// Default value version
	nh.param<std::string>("default_param", default_param, "default_value");

	// ### Set Parameter
	nh.setParam("/global_param", 5);
	nh.setParam("relative_param", "my_string");
	nh.setParam("bool_param", false);

	// ### Delete Parameters
	nh.deleteParam("my_param");

	// ### Private Parameters
	ros::NodeHandle nh("~");
	std::string param;
	nh.getParam("private_name", param);

	// ### Search Parameter Keys
	// !!! I don't know what it's talking about !!!
	string key;
	if (nh.searchParam("bar", key)) {
		std::string val;
		nh.getParam(key, val);
	}

	// ### Retrieving Lists
	// List/Dictionary -> vector/map/...
	ros::NodeHandle nh;

	// Construct a map of strings
	std::map<std::string,std::string> map_s, map_s2;
	map_s["a"] = "foo";
	map_s["b"] = "bar";
	map_s["c"] = "baz";

	// Set and get a map of strings
	nh.setParam("my_string_map", map_s);
	nh.getParam("my_string_map", map_s2);

	// Sum a list of doubles from the parameter server
	std::vector<double> my_double_list;
	double sum = 0;
	nh.getParam("my_double_list", my_double_list);
	for(unsigned i=0; i < my_double_list.size(); i++) {
		sum += my_double_list[i];
	}

/*

## Bare Version
*/
	std::string global_name, relative_name, default_param;

	// ### Parameter exists
	if (ros::param::has("my_param")) {
		...
	}

	// ### Get Parameters
	// return false if not exist/wrong type
	if (ros::param::get("/global_name", global_name)) {
		...
	}
	if (ros::param::get("relative_name", relative_name)) {
		...
	}

	// Default value version
	ros::param::param<std::string>("default_param", default_param, "default_value");

	// ### Set Parameters
	ros::param::set("/global_param", 5);
	ros::param::set("relative_param", "my_string");
	ros::param::set("bool_param", false);

	// ### Delete Parameters
	ros::param::del("my_param");


	// ### Private Parameters
	std::string param;
	ros::param::get("~private_name", param);

	// ### Search Parameter Keys
	// !!! I don't know what it's talking about !!!
	std::string key;
	if (ros::param::search("bar", key)) {
		std::string val;
		ros::param::get(key, val);
	}


/*
# Param vector
<launch>
	<node pkg="beginner_tutorials" name="sandbox" type="sandbox" output="screen">
		<rosparam param="my_int"> [-1, 3, 24, 777, 2] </rosparam>  
	</node>
</launch>
*/
	ros::NodeHandle nh;
	std::vector<int> my_int;
	nh.getParam("/sandbox/my_int", my_int);



/*----------Rqt----------*/
/* 		sudo apt-get install ros-<distro>-rqt ros-<distro>-rqt-common-plugins

# Logging Level: rqt_console
http://wiki.ros.org/roscpp/Overview/Logging

		rosrun rqt_console rqt_console
		rosrun rqt_logger_level rqt_logger_level

rqt_console read outputs while rqt_logger_level change logging levels. Logging levels are prioritized in the decending order:
 * Fatal
 * Error
 * Warn
 * Info
 * Debug
*/



/*----------Launch----------*/
/*
# Make launch file
not necessarily need to be stored /launch but good practice

		roscd beginner_tutorials
		mkdir launch && cd launch
		pluma turtlemimic.launch

## turtlemimic.launch
<launch>
	<!-- when in a group, get a prefix for nodes, topics...: -->

	<!-- group: turtlesim1, node: /turtlesim1/sim -->
	<group ns="turtlesim1">
		 <node pkg="turtlesim" name="sim" type="turtlesim_node"/>
	</group>

	<!-- group: turtlesim2, node: /turtlesim2/sim -->
	<group ns="turtlesim2">
		<node pkg="turtlesim" name="sim" type="turtlesim_node"/>
	</group>

	<!-- node that let output mimics input -->
	<!-- subscribe /turtlesim1/turtle1/pose -->
	<!-- publish /turtlesim2/turtle1/cmd_vel -->
	<node pkg="turtlesim" name="mimic" type="mimic">
		<remap from="input" to="turtlesim1/turtle1"/>
		<remap from="output" to="turtlesim2/turtle1"/>
	</node>
</launch>

# roslaunch
		roslaunch [package] [filename.launch]

		roslaunch beginner_tutorials turtlemimic.launch
		rostopic pub /turtlesim1/turtle1/cmd_vel geometry_msgs/Twist -r 1 -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, -1.8]'

Both turtlesim1 and turtlesim2 spin

## Print ROS_INFO when roslaunch
https://answers.ros.org/question/11302/why-roslaunch-couldnt-show-the-ros_info-message/

	<node pkg="basic_node" name="basic" type="basicNode" output="screen" />
*/



/*----------rosed: ROS Editor----------*/
/*
		rosed [package_name] [filename]
e.g.	rosed roscpp Logger.msg
e.g.	rosed beginner_tutorials serial_test.cpp 

# Change default editor
Append ~/.bashrc
		export EDITOR='pluma'

*/

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// >=10 skipped


/*----------Build----------*/
/*
 * Build:
 * 1. $ cd <your ROS workspace>/src
 * 2. $ catkin_create_pkg stepper_serial_test std_msgs rospy roscpp serial
 * 3. $ cd stepper_serial_test/
 * 4. $ mkdir -p src
 * 5. PUT THIS FILE IN /src just made
 * 6. APPEND THESE LINE IN /stepper_serial_test/CMakeLists.txt
 * 
 * include_directories(include ${catkin_INCLUDE_DIRS})
 * 
 * add_executable(stepper_serial_test src/serial_test.cpp)
 * target_link_libraries(stepper_serial_test ${catkin_LIBRARIES})
 * add_dependencies(stepper_serial_test serial ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS}))
 * 
 * 7. cd <your ROS workspace>
 * 8. catkin_make
 *    (catkin_make --pkg <package A> <package B> to select which to be built)
 *    (https://answers.ros.org/question/54181/how-to-exclude-one-package-from-the-catkin_make-build/)
 *    (catkin_make --pkg <pkgA> -DCATKIN_BLACKLIST_PACKAGES="pkgB;pkgC" to exclude some pkg)
 */



/*----------Publisher & Subscriber----------*/

// Publisher

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char **argv) {

	//Initialize ROS
	ros::init(argc, argv, "talker");

	// Access point to communicate with ROS system
	ros::NodeHandle n;

	// Topic type being published
 	//Publisher advertise (const std::string &topic, uint32_t queue_size, bool latch=false)
	// advertise (topic, buffer)
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

	// determine the length of sleep: 10Hz here
	// keep track of how long it has been since the last call to Rate::sleep()
	ros::Rate loop_rate(10);

	int count = 0;
	while (ros::ok()) {
		std_msgs::String msg;
		std::stringstream ss;
		ss << "hello world " << count;
		msg.data = ss.str();

		// ROS version printf()
		ROS_INFO("%s", msg.data.c_str());

		// Publish
		chatter_pub.publish(msg);

		// not necessary if not receiving callbacks
		ros::spinOnce();

		loop_rate.sleep();

		++count;
	}
	return 0;
}

// Subscriber

#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg) {
	ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "listener");
	ros::NodeHandle n;

	// Subscriber subscribe (const std::string &topic, uint32_t queue_size, void(T::*fp)(M), T *obj, const TransportHints &transport_hints=TransportHints())
	// subscribe (topic, buffer, callback)
	ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

	// Enter a loop, exit once ros::ok() == false
	ros::spin();

	return 0;
}



/*----------Shutdown----------*/
// ros::ok() will now return false
	ros::shutdown()



/*----------rosbag----------*/
/*
Use RQT:
		rqt_bag

Check info without RQT:
		rosbag info locationOfMyBag.bag

Play without RQT:
-q, --quiet: No console output
--clock: Publish the clock time
--topics: Select the topics being published, publish all if not 
		rosbag play locationOfMyBag.bag -q --clock --topics /scan /line_markers /line
--rate: n times faster
		rosbag play locationOfMyBag.bag -q --rate 0.1 (it'll play at 0.1x of original speed)

In .launch:
	<node pkg="rosbag" type="play" name="player" output="screen" args="locationOfMyBag.bag --topics /scan"/>
*/



/*----------remote control----------*/
/*
http://wiki.ros.org/robotican/Tutorials/Remote%20monitoring%20and%20control

on remote machine (192.168.0.10):
	roscore
	export ROS_MASTER_URI=http://192.168.0.10:11311
	export ROS_IP=192.168.0.10

my machine (192.168.0.104):
	export ROS_MASTER_URI=http://192.168.0.10:11311
	export ROS_IP=192.168.0.104
	(do what I like e.g. rqt)
*/



/*----------rqt plugin----------*/
/*
http://wiki.ros.org/rqt/Tutorials/Create%20your%20new%20rqt%20plugin
those lines talking about install in CMakeLists.txt (5. Install & Run your plugin) are bullshit

http://wiki.ros.org/rqt/Tutorials/Writing%20a%20Python%20Plugin

Jeffery's UI: https://github.com/m2robocon/umd_board_2018/tree/master/turnturnturn_shooter

To be edited:
    my_pkg/src/rqt_mypkg/
    my_pkg/src/rqt_mypkg.py
    my_pkg/resource/MyPlugin.ui
    my_pkg/CMakeLists.txt
    my_pkg/package.xml
    my_pkg/plugin.xml
*/



