<html>
<head>
    <title>destinyDB</title>
    <meta charset="GBK" content="text/html;charset=GBK" />
</head>
<body>
    <p>
        <pre>
destinyRegex
            Regular Expression(正则表达式实现)
            打算实现C和C++的接口
            使用时需要包含headers.h头文件
    
            author:	Sword-Destiny
            作者:	天命剑主(武汉大学国际软件学院2013级袁浩)
            QQ:	1948281915
            邮箱:	yuanhonglong@outlook.com

            version: 0.1
    
C++:    示例文件test.cpp
            语法：
            各个特殊字符含义如下定义
            #define OR_CHAR '|'
            #define LEFT_LARGE_BRACE '{'
            #define RIGHT_LARGE_BRACE '}'
            #define LEFT_MID_BRACKET '['
            #define RIGHT_MID_BRACKET ']'
            #define LEFT_BRACKET '('
            #define RIGHT_BRACKET ')'
            #define CHANGE_LETTER '\\' //双斜线转义
<<<<<<< HEAD
            #define TAB 't' //需要转义
            #define RETURN_ 'r' //需要转义
            #define NEW_LINE 'n' //需要转义
            #define NEW_PAGE 'f' //需要转义
            #define TAB_V 'v' //需要转义
=======
            #define TAB 't' 
            #define RETURN_ 'r' 
            #define NEW_LINE 'n' 
            #define NEW_PAGE 'f' 
            #define TAB_V 'v' 
>>>>>>> 8f8126bf8bf76ec1f24baffc0d3c3ff7ea04d4f6
            #define BLANK ' ' //空格
            #define COMMA ',' //逗号
            #define DOT '.' //通配符
            #define MULTI_MATCH_LETTER '*' //多次匹配符
            #define QUES '?' //0或1个
            #define PLUS '+' //一个或多个
            #define DECIMAL 'd' //一个十进制数字,需要转义
            #define LOWER_LETTER 'l' //一个小写字母,需要转义
            #define SPACE 's' //一个空白符（空格符，制表符等）,需要转义
            #define UPER_LETTER 'u'//一个大写字母,需要转义
<<<<<<< HEAD
            #define SIMPLE_LETTER 'w' //一个字母a～z或A～Z或数字0～9或下划线_,需要转义
=======
            #define SIMPLE_LETTER 'w' //一个字母（a～z或A～Z）或数字（0～9）或下划线（_）,需要转义
>>>>>>> 8f8126bf8bf76ec1f24baffc0d3c3ff7ea04d4f6
            #define NOT_DECIMAL 'D' //除了\d之外的字符,需要转义
            #define NOT_LOWER_LETTER 'L' //除了\l之外的字符,需要转义
            #define NOT_SPACE 'S' //除了\s之外的字符,需要转义
            #define NOT_UPER_LETTER 'U' //除了\u之外的字符,需要转义
            #define NOT_SIMPLE_LETTER 'W' //除了\w之外的字符,需要转义
            #define RANGE_LETTER '-' //范围表示符

            \是转义符
            t,r,n,f,v等普通字符通过转义可以作为特殊字符
            -,.+*\?{}[]()等具有特殊用途的符号经过转义之后可以作为普通字符
            \t 横向tab
            \n 换行
            \r Return
            \f 换页
            \v 纵向tab

            |代表逻辑或,比如[a]{2,3}[b]{2}|[c]{2,7}
            由|符分割出来的表达式[a]{2,3}[b]{2}和[c]{2,7}称为"情形"或"匹配条件"

            [a]{2,3}[b]{2}又可以分为[a]{2,3}和[b]{2},称为单一情形或者单一匹配条件

            单一匹配条件 组成 匹配条件
            匹配条件 组成 正则表达式

            单一匹配条件 = 可选字符 + 匹配次数

            可选字符：
            []之间的字符代表可选字符,如[a\.\?b]代表   a或b或.或?
            单独的字符或者转义字符等同于可选字符,即a等同于[a],\d等同于[\d]

            匹配次数：
            {}代表匹配次数,如{2}代表匹配2次,{2,4}代表匹配2-4次,{3,}代表匹配大于等于3次,
            后面一个数字不能大于前面的数字,比如{2,1}是非法的,{}前面必须为可选字符

            匹配次数可以省略，缺省值为{1}

            一个字符串只要和任何一个"匹配条件"相匹配即视为和整个正则表达式相匹配

            regex_match返回字符串是否与正则表达式匹配
            regex_search返回字符串是否存在与正则表达式匹配的子串

            sregex_token_iterator类使用正则表达式分割字符串,比如字符串baaabbaabbab
            可以被正则表达式[a]{2,3}分割为 b,aaa,bb,aa,bbab
            而不是 b,aa,abb,aa,bbab
            因为在分割时优先考虑较长的匹配,所以[a]{2,3}优先匹配aaa而不是aa
            最后的sregex_token_iterator中包含的字符串为b,bb,bbab

            不同的是,在regex_match和regex_search中优先考虑较短的匹配

            NOTICE:暂时不支持使用()进行多个正则表达式的连接

<<<<<<< HEAD
            C++的版本使用的是作者自己写的string类，作者为了模仿C++11标准库中得std::string类把该类写得
            和std::string的用法都差不多,所以大家在使用时要注意命名空间的变化,不要把这两个类弄混了
=======
            C++的版本使用的是作者自己写的string类，作者为了模仿C++11标准库中得std::string类把该类写得和std::string
            的用法都差不多,所以大家在使用时要注意命名空间的变化,不要把这两个类弄混了
>>>>>>> 8f8126bf8bf76ec1f24baffc0d3c3ff7ea04d4f6

C:      示例文件test.c
            正则表达式基本语法与C++相同,参照C++,具体使用参照test.c
            不同的是在C语言的版本中没有sregex_token_iterator类,所以直接给出了regex_splite函数，分割后的
            字符串存放于regex结构体中,具体情况可以看test.c示例代码

<<<<<<< HEAD
            C语言的版本中不仅在regex-&gt;token_strs中得到分割的字符串，
            还可以在regex-&gt;match_strs中得到匹配的字符串,
            比C++版本强大一些

            C++的版本没有提供regex_splite函数,而是提供了sregex_token_iterator类.之所以如此,
            是因为作者在模仿C++11标准库中的sregex_token_iterator的语法,
            大家很容易就可以自己参照C版本写出C++版本的代码
=======
            C语言的版本中不仅在regex->token_strs中得到分割的字符串，还可以在regex->match_strs中得到匹配的字符串
            比C++版本强大一些

            C++的版本没有提供regex_splite函数,而是提供了sregex_token_iterator类.之所以如此,是因为作者在模仿C++11标准库中的
            sregex_token_iterator的语法,大家很容易就可以自己参照C版本写出C++版本的代码
>>>>>>> 8f8126bf8bf76ec1f24baffc0d3c3ff7ea04d4f6
        </pre>
    </p>
</body>
</html>
