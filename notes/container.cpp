//cpp note

除了熟悉业务，再把c++的基本数据结构玩熟练，主要是文件的增删改查，数据流的操作，string vector map熟练使用
c++ http server client ，c++解析json xml
string

/***********************************************/
vector
vector<T> 容器是包含 T 类型元素的序列容器，不同的是 vector<T> 容器的大小可以自动增长，从而可以包含任意数量的元素；因此类型参数 T 不再需要模板参数 N。只要元素个数超出 vector 当前容量，就会自动分配更多的空间。只能在容器尾部高效地删除或添加元素。
vector<T> 容器可以方便、灵活地代替数组。在大多数时候，都可以用 vector<T> 代替数组存放元素。只要能够意识到，vector<T> 在扩展容量，以 及在序列内部删除或添加元素时会产生一些开销；但大多数情况下，代码不会明显变慢。 为了使用 vector<T> 容器模板，需要在代码中包含头文件 vector。

创建vector<T>容器
std::vector<double> values; 
std::vector<double> values(20);
std::vector<long> numbers(20, 99L);//第二个参数指定了所有元素的初始值
std::vector<unsigned int> primes {2u, 3u, 5u, 7u, 11u, 13u, 17u, 19u};


可以用元素类型相同的容器来初始化 vector<T> 容器
std::array<std :: string, 5> words {"one", "two","three", "four", "five"};
std::vector<std::string> words_copy {std::begin(words) , std::end(words)};

获取大小和容量
std::cout << "The size is " << primes.size() << std::endl;
std::cout << "The capacity is" << primes.capacity() << std::endl;

通过调用 reserve() 来增加容器的容量
values.reserve(20);  //如果当前的容量已经大于或等于 20 个元素，那么这条语句什么也不做。
resize() 可以改变容器大小
values.resize (5);
values.resize (7, 99);//第二个参数指定了元素的初始值

获取、访问元素
std::cout << values[0] << values.front () << values.front () << std::endl; //  front() 和 back() 分別返回序列中第一个和最后一个元素的引用,们可以出现在赋值运算符的左边。



/***********************************************/
map

map 容器有 4 种，每一种都是由类模板定义的。所有类型的 map 容器保存的都是键值对类型的元素。map 容器的元素是 pair<const K，T> 类型的对象，这种对象封装了一个 T 类型的对象和一个与其关联的 K 类型的键。pair 元素中的键是 const，因为修改键会扰乱容器中元素的顺序。每种 map 容器的模板都有不同的特性：
	1、map<K，T>容器，保存的是 pair<const K，T> 类型的元素。pair<const K,T> 封装了一对键对象，键的类型是 K，对象的类型是 T。每个键都是唯一的，所以不允许有重复的键；但可以保存重复的对象，只要它们的键不同。map 容器中的元素都是有序的，元素在容器内的顺序是通过比较键确定的。默认使用 less<K> 对象比较。

	2、multimap<K，T> 容器和 map<K，T> 容器类似， 也会对元素排序。 它的键必须是可比较的， 元素的顺序是通过比较键确定的。 和 map<K，T> 不同的是，multimap<K，T> 允许使用重复的键。因此，一个 multimap 容器可以保存多个具有相同键值的 <const K,T> 元素。

	3、unordered_map<K，T> 中 pair< const K，T>元素的顺序并不是直接由键值确定的，而是由键值的哈希值决定的。哈希值是由一个叫作哈希的过程生成的整数，本章后面会解释这一点。unordered_map<K，T>不允许有重复的键。

	4、unordered_multimap<K,T> 也可以通过键值生成的哈希值来确定对象的位置，但它允许有重复的键。

*multi前缀表明键不必唯一，但如果没有这个前缀，键必须唯一。
*unordered_prefix 前缀表明容器中元素的位置是通过其键值所产生的哈希值来决定的，而不是通过比较键值决定的。如果没有该前缀，那么元素的位置就由比较键值决定。


初始化
std::map<std::string, size_t> people{ {"Ann", 25}, {"Bill", 46},{"Jack", 32},{"Jill", 32} };
查找获取
auto value = people.at("Ann");
插入数据
auto ret_pr = people.insert({ "Fred", 22 });
if (!ret_pr.second)
	std::cout << "insert error" << std::endl;
构造元素
class Name
{
public:
	Name(const std::string& name1, const std::string& name2) : first(name1), second(name2) {}
private:
	std::string first{};
	std::string second{};
};
auto pr = people.emplace (Name { "Dan","Druff"},77);
删除元素
value = people.erase(key)
if(value)
	std::cout << "removed success" << std::endl;

创建元素组合四种方法
std::string s1 {"test"}, s2{"that"};
std::pair<std::string, std::string> my_pair{s1, s2};
std::pair<std::string, std::string> your_pair{std::string {"test"},std::string {"that"}};
std::pair<std::string, std::string> his_pair{"test", std::string {"that"}};
std::pair<std::string, std::string> her_pair{"test", "that"};
或
auto my_pair = std::make_pair(s1, s2);
auto your_pair = std::make_pair(std::string {"test"},std::string {"that"});
auto his_pair = std::make_pair<std::string, std::string>("test",std::string {"that"});
auto her_pair = std::make_pair<std::string, std::string>("test", "that");
抑或
std::pair<std::string, std:: string> new_pair{my_pair}; // 复制pair对象
std::pair<std::string, std::string>
	old_pair{std::make_pair(std::string{"his"},std::string{"hers"})};


生成 tuple 对象
函数 make_tuple() 可以接受不同类型的任意个数的参数，返回的 tuple 的类型由参数的类型决定
auto my_tuple = std::make_tuple (Name{"Peter"，"Piper"},42,std::string{"914 626 7890"})；

std::tuple<std::string, size_t> my_tl;//Default initialization
std:: tuple<Name, std::string> my_t2 {Name {"Andy", "Capp"},std::string{“Programmer”}};
std::tuple<Name,std::string> copy_my_t2{my_t2}; // Copy constructor
std::tuple<std::string, std::string> my_t3 {"this", "that"};

可以用 pair 对象构造只有两个元素的 tuple 对象
auto the_pair = std::make_pair("these","those");
std::tuple<std::string, std::string> my_t4 {the_pair}; std::tuple<std::string, std::string> my_t5 {std::pair <std::string, std::string > { "this", "that"}};

tuple 对象的成员函数 swap() 可以将它的元素和参数交换。参数的类型必须和 tuple 对象的类型一致。
my_t4.swap (my_t5);

get<>() 可以返回 tuple 中的一个元素
auto my_tuple = std::make_tuple (Name {"Peter","Piper"}, 42, std::string {"914 626 7890"});
std::cout << std::get<0>(my_tuple)<< "age = "<<std::get<1>(my_tuple)<< " tel: " << std::get<2>(my_tuple) << std::endl;
--------------------------------------------------------------
eter Piper age = 42 tel: 914 626 7890

tie<>() 提供了另一种访问 tuple 元素的方式
std::tie(Name name,size_t age,std::string phone) = my_tuple;
或者只取第一和第三个：
std::tie(name, std::ignore,phone) = my_tuple;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
multimap

multimap 容器的成员函数 insert() 可以插入一个或多个元素，而且插入总是成功。
std::multimap<string, string> pets; // Element is pair{pet_type, pet_name}
auto iter = pets.insert (std::pair<string, string>{string{"dog"}, string{"Fang"}});
iter = pets.insert(iter, std::make_pair("dog", "Spot")); // Insert Spot before Fang
pets.insert(std::make_pair("dog", "Rover"));// Inserts Rover after Fang
pets.insert (std::make_pair ("cat", "Korky"));// Inserts Korky before all dogs
pets.insert ({{ "rat", "Roland"}, {"pig", "Pinky" }, {"pig", "Perky"}});//Inserts list elements

在插入具有相同键的元素时，可以使用 multimap 的成员函数 emplace_hint()，可以通过为这个函数提供一个迭代器形式的提示符来控制元素的生成位置
auto iter = pets.emplace("rabbit","Flopsy");
iter = pets.emplace_hint (iter, "rabbit", "Mopsy");// Create preceding "Flopsy" 

访问给定键对应的所有元素
auto pr = people.equal_range("Ann");
if(pr.first != std::end(people))
{
    for (auto iter = pr.first ; iter != pr.second; ++iter)
        std:cout << iter->first << " is " << iter->second << std::endl;
}






/**********************************************************************/
<json>

{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}"; 
{
	"uploadid": "UP000000",
	"code": 100,
	"msg": "none",
	"files": "none"
} 

json配置过程

看了网上的博客和一些文章整了半天整不出来，vs也各种报错，真是气人。
好像又回到了过去一天到晚百度就是为了解决vs各种环境记语法问题。

后来再反复找源代码，并仔细对比各个博客异同之处，并在vs上一步步操作，总算完成一部输出

	*首先下载源文件解压 https://github.com/open-source-parsers/jsoncpp/releases
	*将include\json和src\lib_json目录里的文件手动添加到VS工程中（在vs中工程目录下新建filter文件夹，然后将之前提到的这些文件全都add 进来）
	*将filter文件夹中的json_reader.cpp、json_value.cpp和json_writer.cpp三个文件右键属性，Precompiled Header属性设置为Not Using Precompiled Headers，否则编译会出现错误。
	*在VS工程的属性C/C++下General中Additional Include Directories包含头文件目录\include。在使用的cpp文件中包含json头文件即可，代码头部加入#include "json/json.h"。

参考文章 
https://www.cnblogs.com/liaocheng/p/4243731.html
https://www.cnblogs.com/yelongsan/p/4134384.html
https://blog.csdn.net/xt_xiaotian/article/details/5648388

{\"Id\" :1, \"Name\" : \"cctrys\" , \"Age\" :23,\"Address\" :[{ \"City\" : \"Beijing\" , \"ZipCode\" : \"111111\" }, { \"City\" : \"Shanghai\" , \"ZipCode\" : \"222222\" }], \"Email\" : \"cctrys@163.com\"}";
{
	"Id" : 1,
	"Name" : "cctrys" ,
	"Age" :23,
	"Address" : 
	[
		{ "City" : "Beijing" , 	"ZipCode" : "111111" }, 
		{ "City" : "Shanghai" , "ZipCode" : "222222" }
	], 
	"Email" : "cctrys@163.com"
}

#include "json/json.h"
Json::Reader read;
Json::Value jsonObj;
在主函数中加入语句，运行正常
string strValue2 = "{\"Id\" :1, \"Name\" : \"cctrys\" , \"Age\" :23,\"Address\" :[{ \"City\" : \"Beijing\" , \"ZipCode\" : \"111111\" }, { \"City\" : \"Shanghai\" , \"ZipCode\" : \"222222\" }], \"Email\" : \"cctrys@163.com\"}";
if (read.parse(strValue2, jsonObj)) {
	std::string name = jsonObj["Name"].asCString();
	std::cout << name << std::endl;
}
输出cctrys
//------------------------------------
访问子节点
if (!jsonObj["Address"].isNull())
{
	int file_size = jsonObj["Address"].size();
	std::cout << "address size" << file_size  << std::endl;
	// 遍历数组

	Json::Value val_address;
	if (file_size >= 1)
		val_address = jsonObj["Address"];


	for (int i = 0; i < file_size; ++i)
	{
		std::string citys = val_address[i]["City"].asString();
		std::cout  << " city " << citys << std::endl;
	}
}
输出 
address size 2
city Beijing
city Shanghai
//------------------------------------
迭代器获取json的key
Json::Value myjson = jsonObj["Address"][0];//getJsonFromFile(“test.json”);
Json::Value::Members members(myjson.getMemberNames());

for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it) {
	const std::string &key = *it;
	std::cout << key << std::endl;
}
输出 
City
ZipCode

//--------------------------
{
   "a" : [
      {
         "date" : "2011-11-11",
         "date2" : "2011-11-12",
         "date3" : "2011-11-13"
      },
      {
         "time" : "11:11:11"
      }
   ],
   "code" : 100,
   "date" : "2011-11-11",
   "datex" : 666,
   "datexx" : {
      "date" : "2011-11-11",
      "date2" : "2011-11-12",
      "date3" : "2011-11-13"
   },
   "files" : "",
   "msg" : "",
   "uploadid" : "UP000000"
}
这其中那个“[]”是否有特殊意义？
//源自 https://www.cnblogs.com/gimin/p/5295952.html
在JavaScript中，通常用[]创建的数据格式称为数组，用{}创建的东西称为对象。
有一个数组a=[1,2,3,4]，还有一个对象a={0:1,1:2,2:3,3:4}，运行alert(a[1])，两种情况下的运行结果是相同的！这就是说，数据集合既可以用数组表示，也可以用对象表示，那么到底该用哪一种呢？ 
其实数组表示有序数据的集合，而对象表示无序数据的集合。如果数据的顺序很重要，就用数组，否则就用对象。 
当然，数组和对象的另一个区别是，数组中的数据没有“名称”（name），对象中的数据有“名称”（name）。但是问题是，很多编程语言中，都有一种叫 做“关联数组“（associativearray）的东西。这种数组中的数据是有名称的。


//========================================示例测试代码

#include "json/json.h"
Json::Reader read;
Json::Value jsonObj;

using std::string;
using std::vector;
//初始化
std::map<std::string, size_t> people{ {"Ann", 25}, {"Bill", 46},{"Jack", 32},{"Jill", 32} };

class Name
{
public:
	Name(const std::string& name1, const std::string& name2) : first(name1), second(name2) {}
	//~Name();

private:
	std::string first{};
	std::string second{};
};

int main()
{
	//    std::cout << "Hello World!\n"; 
	string strValue = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";  
	string strValue2 = "{\"Id\" :1, \"Name\" : \"cctrys\" , \"Age\" :23,\"Address\" :[{ \"City\" : \"Beijing\" , \"ZipCode\" : \"111111\" }, { \"City\" : \"Shanghai\" , \"ZipCode\" : \"222222\" }], \"Email\" : \"cctrys@163.com\"}";
	Json::Value root;
	if (read.parse(strValue, root)) {
		std::string out = root.toStyledString();
		std::cout << out << std::endl;
//		root.append("xx:xx");    
		Json::Value arrayObj=root;   // 构建对象  
		Json::Value new_item, new_item1;
		new_item["date"] = "2011-11-11";
		new_item["date2"] = "2011-11-12";
		new_item["date3"] = "2011-11-13";
		new_item1["time"] = "11:11:11";
		arrayObj["date"] = "2011-11-11";
		arrayObj["datex"] = Json::Value(666);
		arrayObj["datexx"] = ne
		w_item;

		arrayObj["a"].append(new_item);  // 插入数组成员  
		arrayObj["a"].append(new_item1); // 插入数组成员
		out = arrayObj.toStyledString();//arrayObj.toStyledString();
		std::cout << out << std::endl;

		new_item["key_array"].append("array_string");
		new_item["key_array"].append(1234);
		out = new_item.toStyledString();//arrayObj.toStyledString();
		std::cout << out << std::endl;

		int root_size = root.size();
		std::cout << "root size " << root_size << std::endl;
	}

	if (read.parse(strValue2, jsonObj)) {
		std::string code;
		if (!jsonObj["Address"].isNull())  // 访问节点，Access an object value by name, create a null member if it does not exist.
			code = jsonObj["Name"].asString();
		std::cout << code << std::endl;
		// 访问节点，Return the member named key if it exist, defaultValue otherwise.
		code = jsonObj.get("uploadid", "null").asString();

		// 得到"files"的数组个数
		int file_size = jsonObj["Address"].size();
		std::cout << " size " << file_size  << std::endl;
		
		file_size = jsonObj["Address"][0].size();
		std::cout << " size " << file_size << std::endl;

//		std::string name = jsonObj["Address"][0].asCString();
//		std::cout << name << std::endl;

		//迭代器获取json的key
		Json::Value myjson = jsonObj["Address"][0];//getJsonFromFile(“test.json”);
		Json::Value::Members members(myjson.getMemberNames());

		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it) {
			const std::string &key = *it;
			std::cout << key << std::endl;
		}


		Json::Value val_address;
		if (file_size >= 1)
			val_address = jsonObj["Address"];


		for (int i = 0; i < file_size; ++i)
		{
			std::string citys = val_address[i]["City"].asString();
			std::cout  << " city " << citys << std::endl;
	/*		Json::Value val_image = jsonObj["files"][i]["images"];
			int image_size = val_image.size();
			for (int j = 0; j < image_size; ++j)
			{
				std::string type = val_image[j]["type"].asString();
				std::string url = val_image[j]["url"].asString();
			}
	*/

		}
//		std::string name = jsonObj["Address"].asCString();
//		std::cout << name << std::endl;
	}

//-----------------------------------------
	json::value.type()返回值


JsonValueType	0		The JsonValue object is Null.
Boolean			1		The JsonValue object is a Boolean.
Number			2		The JsonValue object is a Double.
String			3		The JsonValue object is a String.
Array			4		The JsonValue object is an Array.
Object			5		The JsonValue object is an Object.
对象数组	[{}{}]	6
多个对象{,,,}    7

//--
普通的json组合方式：
	Json::Value topobj;
	Json::Value subobj;
	subobj[azColName[i]] = Json::Value(argv[i]); 
	topobj["a"].append(subobj);//topobj.append(subobj); 也行
//#############################
<xml>

*	方法和json类似，从 sourceforge.net/projects/tinyxml 下载源文件解压
*	在vs工程属性中 configuration properties -> C/C++ -> general -> additional include directories 添加 tinyxml.h的路径
*	然后再工程目录下新建一个filter，命名xml，添加解压出来的文件的 .cpp / .h 六个文件（除了xxxtest.cpp,因为是测试文件，里面有main函数），
*	其中.cpp 文件的预编译头属性precompiled header设置成no,
*	在主函数中加入头文件引用即可

#include "tinystr.h"   
#include "tinyxml.h"
	//读取在工程目录中的文件demotest.xml
	TiXmlDocument doc("demotest.xml");
	doc.Parse(demoStart);

	if (doc.Error())//读取失败
	{
		printf("Error in %s: %s\n", doc.Value(), doc.ErrorDesc());
		exit(1);
	}
	doc.SaveFile();

	bool loadOkay = doc.LoadFile();

	if (!loadOkay)
	{
		printf("Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
		exit(1);
	}

	//两种输出方式，结果看起来都差不多，整体打印出来
	printf("** Demo doc read from disk: ** \n\n");
	printf("** Printing via doc.Print **\n");
	doc.Print(stdout);


	printf("\n\n\n** Printing via TiXmlPrinter **\n\n");
	TiXmlPrinter printer;
	doc.Accept(&printer);
	fprintf(stdout, "%s", printer.CStr());



//根据节点修改属性
	// --------------------------------------------------------
	// An example of changing existing attributes, and removing
	// an element from the document.
	// --------------------------------------------------------
	TiXmlNode* node = 0;
	TiXmlElement* todoElement = 0;
	TiXmlElement* itemElement = 0;

	// Get the "ToDo" element.
	// It is a child of the document, and can be selected by name.
	node = doc.FirstChild( "ToDo" );
	assert( node );
	todoElement = node->ToElement();
	assert( todoElement  );

	// Going to the toy store is now our second priority...
	// So set the "priority" attribute of the first item in the list.
	node = todoElement->FirstChildElement();	// This skips the "PDA" comment.
	assert( node );
	itemElement = node->ToElement();
	assert( itemElement  );
	itemElement->SetAttribute( "priority", 2 );

	// Change the distance to "doing bills" from
	// "none" to "here". It's the next sibling element.
	itemElement = itemElement->NextSiblingElement();
	assert( itemElement );
	itemElement->SetAttribute( "distance", "here" );

	// Remove the "Look for Evil Dinosaurs!" item.
	// It is 1 more sibling away. We ask the parent to remove
	// a particular child.
	itemElement = itemElement->NextSiblingElement();
	todoElement->RemoveChild( itemElement );

	itemElement = 0;

	// --------------------------------------------------------
	// What follows is an example of created elements and text
	// nodes and adding them to the document.
	// --------------------------------------------------------

//添加属性及字段
	// Add some meetings.
	TiXmlElement item( "Item" );
	item.SetAttribute( "priority", "1" );
	item.SetAttribute( "distance", "far" );

	TiXmlText text( "Talk to:" );

	TiXmlElement meeting1( "Meeting" );
	meeting1.SetAttribute( "where", "School" );

	TiXmlElement meeting2( "Meeting" );
	meeting2.SetAttribute( "where", "Lunch" );

	TiXmlElement attendee1( "Attendee" );
	attendee1.SetAttribute( "name", "Marple" );
	attendee1.SetAttribute( "position", "teacher" );

	TiXmlElement attendee2( "Attendee" );
	attendee2.SetAttribute( "name", "Voel" );
	attendee2.SetAttribute( "position", "counselor" );

//指定层级结构
	// Assemble the nodes we've created:
	meeting1.InsertEndChild( attendee1 );
	meeting1.InsertEndChild( attendee2 );

	item.InsertEndChild( text );
	item.InsertEndChild( meeting1 );
	item.InsertEndChild( meeting2 );

	// And add the node to the existing list after the first child.
	node = todoElement->FirstChild( "Item" );
	assert( node );
	itemElement = node->ToElement();
	assert( itemElement );

	todoElement->InsertAfterChild( itemElement, item );
//打印
	printf( "\n** Demo doc processed: ** \n\n" );
	doc.Print( stdout );


//前后对比
//------ origin
<?xml version="1.0" standalone="no" ?>
<!-- Our to do list data -->
<ToDo>
    <!-- Do I need a secure PDA? -->
    <Item priority="1" distance="close">
        Go to the
        <bold>Toy store!</bold>
    </Item>
    <Item priority="2" distance="none">Do bills</Item>
    <Item priority="2" distance="far &amp; back">Look for Evil Dinosaurs!</Item>
</ToDo>

//------ after
<?xml version="1.0" standalone="no" ?>
<!-- Our to do list data -->
<ToDo>
    <!-- Do I need a secure PDA? -->
    <Item priority="2" distance="close">Go to the
        <bold>Toy store!</bold>
    </Item>
    <Item priority="1" distance="far">Talk to:
        <Meeting where="School">
            <Attendee name="Marple" position="teacher" />
            <Attendee name="Voel" position="counselor" />
        </Meeting>
        <Meeting where="Lunch" />
    </Item>
    <Item priority="2" distance="here">Do bills</Item>
</ToDo>

避免 XML 属性？
因使用属性而引起的一些问题：

属性无法包含多重的值（元素可以）
属性无法描述树结构（元素可以）
属性不易扩展（为未来的变化）
属性难以阅读和维护
请尽量使用元素来描述数据。而仅仅使用属性来提供与数据无关的信息。

不要做这样的蠢事（这不是 XML 应该被使用的方式）：

<note day="08" month="08" year="2008"
to="George" from="John" heading="Reminder" 
body="Don't forget the meeting!">
</note>

//########################################################################################################################//
sqlite  轻量级数据库

在Linux上apt install sqlite 即可
在空白文件夹输入 sqlite test.db 创建并进入Test.db的编辑

.show 显示当前配置
.tables 显示当前已有数据库
select * from company 显示company库中的数据
创建company表
sqlite> 
CREATE TABLE COMPANY(
   ID INT PRIMARY KEY     NOT NULL,
   NAME           TEXT    NOT NULL,
   AGE            INT     NOT NULL,
   ADDRESS        CHAR(50),
   SALARY         REAL
);
向表中插入信息
INSERT INTO COMPANY VALUES (2, 'Allen', 25, 'Texas', 15000.00 );
INSERT INTO COMPANY VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );
INSERT INTO COMPANY VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );
INSERT INTO COMPANY VALUES (5, 'David', 27, 'Texas', 85000.00 );
INSERT INTO COMPANY VALUES (6, 'Kim', 22, 'South-Hall', 45000.00 );
INSERT INTO COMPANY VALUES (7, 'James', 24, 'Houston', 10000.00 );

修改显示配置项以便更清楚的查看数据库表格
sqlite> .header on  			//输出表头
		.mode column 			//制表输出
		.width 10, 20, 10       //设置第一列的宽度为 10，第二列的宽度为 20，第三列的宽度为 10

select * from company
select id,name,salary from company
select * from company where age>=25 and salary>=10000

查看表单详细信息
sqlite>.schema COMPANY

删除表单
sqlite>DROP TABLE COMPANY;

使用 SQLite .dump 点命令来导出完整的数据库在一个文本文件中
$sqlite3 test.db .dump > test.sql
抑或反向操作
$sqlite3 testDB.db < testDB.sql


//	24+16+13+13+1+2+5+8   =82 *0.78 =60
//	26+27+22+14+18+9+4+13 =124*0.69 =87

C++环境配置

从这里下载 "https://www.sqlite.org/download.html" 三个文件
"https://www.sqlite.org/2019/sqlite-amalgamation-3270200.zip"    //源码
shell.c sqlite3.c sqlite3.h sqlite3ext.h
"https://www.sqlite.org/2019/sqlite-dll-win64-x64-3270200.zip"   //dll、def 用于生成lib文件
sqlite3.dll  sqlite3.def
"https://www.sqlite.org/2019/sqlite-tools-win32-x86-3270200.zip" //Windows可执行程序，添加环境用
sqlite3.exe sqldiff.exe sqlite3_analyzer.exe 

全部解压出来的文件如上
1、首先在Windows环境变量 path 中添加 sqlite3.exe 的路径，让cmd和powershell 都能执行sqlite3指令
2、在vs工程中新建filter 添加源码包中的四个.c .h文件,并设置不进行预编译
3、在vs安装目录中找到lib.exe 来将 sqlite3.def 编译成 sqlite3.lib ，打开cmd或者powershell
32位系统用指令 lib.exe /def:sqlite3.def /machine:ix86
64位系统用指令 lib.exe /def:sqlite3.def /machine:x64 或者省略/machine:x64字段
*如果因为路径问题非常难搞，就将vs中的lib.exe link.exe link.exe.config mspdbcore.dll 复制到sqlite3.def 所在文件夹再执行以上命令
生成的sqlite3.lib 需要在vs工程 linker -> input -> additional dependencies 中引用

//-----------------------------------------------
C++工程代码样例

#include <sqlite3.h>

// callback:回调函数,每成功执行一次sql语句就执行一次callback函数
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("test2.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
	

	const char *sql;
	sql = "CREATE TABLE COMPANY("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"NAME           TEXT    NOT NULL," \
		"AGE            INT     NOT NULL," \
		"ADDRESS        CHAR(50)," \
		"SALARY         REAL );";

	const char * insert = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}

	rc = sqlite3_exec(db, insert, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Records created successfully\n");
	}
	sqlite3_close(db);
}






////////////////////////////////////
xml
https://www.cnblogs.com/xudong-bupt/p/3733306.html
**https://www.cnblogs.com/betterwgo/p/7895891.html