# LL-1-analyzer
LL(1)的文法分析器

## 简介
用于LL(1)的文法分析，计算FIRST，FOLLOW集合，构造预测分析表。

## FIRST集合计算方法
> 计算FIRST(X)时，不断应用以下规则，直到没有新的终结符号或ε可以被加入到任何FIRST集合中为止。
1. 如果X是一个终结符号，那么FIRST(X)=X:
2. 如果X是一个非终结符号，且X -> Y<sub>1</sub>Y<sub>2</sub>……Y<sub>k</sub>是一个产生式，FIRST(Y<sub>1</sub>)中的所有符号一定都在FIRST(X)中，Y<sub>1</sub>可以推导出ε，那么也将FIRST(Y<sub>2</sub>)中的所有符号加入FIRST(X),以此类推。

## FOLLOW集合计算方法
> 不断应用以下规则，直到没有新的终结符号被加入到任何FOLLOW集合中为止。
1. 将$放到FOLLOW(S)中，其中S是开始符号，而$是输入右端的结束标记。
2. 

## 演示
### 文法
 E -> T E

 E' -> + T E' | ε 

 T -> F T'

 T' -> * F T' | ε
 
 F -> ( E ) | id

 ```
    stringstream ss;
    ss<<"E -> T E'"<<endl;
    ss<<"E' -> + T E' | ε"<<endl;
    ss<<"T -> F T'"<<endl;
    ss<<"T' -> * F T' | ε"<<endl;
    ss<<"F -> ( E ) | id"<<endl;
    LLParser ll("E",ss,unordered_set<string>{"ε","id","(",")","*","+"});
 ```
 使用输入流，输入文法，文法符号之间使用空格间隔
```
LLParser(const std::string &,std::basic_istream<char> &,std::unordered_set<std::string>);

```
构造函数参数分别为 开始符号，文法输入流，终结符号集合。
```
//打印FOLLOW集合

void LLParser::PrintAllFollow();
```
```
F:* $ ) + 
T:+ ) $ 
T':$ ) + 
E':) $ 
E:$ )
```


```
//打印FIRST集合

void LLParser::PrintAllFirst();
```
```
F:id ( 
T:( id 
T':ε * 
E':ε + 
E:id (
```
```
//打印预测分析表

void LLParser::PrintTable();
```
```

		$  	    	*   	  	(  	    	id      		)  	    	+  
F	                          F -> (E)    F -> id      
T	                          T -> FT'    T -> FT'      
T'	T' -> ε     T' -> *FT'                                T' -> ε    T' -> ε  
E'	E' -> ε                                               E' -> ε    E' -> +TE'  
E	                          E -> TE'    E -> TE'      
```
