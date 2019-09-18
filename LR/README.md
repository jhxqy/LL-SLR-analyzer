# SLR-analyzer
SLR的文法分析器

## 简介
LR文法分析，构造LR(0)项集族，以及语法分析表。

--- 

## 例子
### 文法：
 E -> E + T | T

 T -> T * F | F

 F -> ( E ) | id

```cpp
//构造LRParser

 stringstream ss;
    ss<<"E -> E + T | T"<<endl;
    ss<<"T -> T * F | F"<<endl;
    ss<<"F -> ( E ) | id"<<endl;
    
    LRParser lr("E",ss,unordered_set<std::string>{"(",")","+","*","ε","id"});
```

### 规范LR(0)项集族
```
id:11
F -> ( E ) .

id:5
E -> E . + T 
E' -> E .

id:10
T -> T . * F 
E -> E + T .

id:8
F -> . ( E ) 
F -> . id 
T -> T * . F 

id:4
T -> T . * F 
E -> T .

id:9
T -> T * F .

id:6
F -> . id 
F -> . ( E ) 
T -> . T * F 
T -> . F 
E -> E + . T 

id:7
E -> E . + T 
F -> ( E . ) 

id:3
T -> F .

id:2
F -> id .

id:1
F -> . id 
F -> . ( E ) 
T -> . F 
T -> . T * F 
E -> . T 
E -> . E + T 
F -> ( . E ) 

id:0
F -> . id 
F -> . ( E ) 
T -> . F 
T -> . T * F 
E -> . E + T 
E -> . T 
E' -> . E 
```

### Action 表：

| | (| id| +| )| *| ε| $|
---|---|---|---|---|---|---|---|
0|S1| S2| | | | | | 
1|S1| S2| | | | | | 
2|| | R5| R5| R5| | R5| 
3|| | R3| R3| R3| | R3| 
4|| | R1| R1| S8| | R1| 
5|| | S6| | | | AC| 
6|S1| S2| | | | | | 
7|| | S6| S11| | | | 
8|S1| S2| | | | | | 
9|| | R2| R2| R2| | R2| 
10|| | R0| R0| S8| | R0| 
11|| | R4| R4| R4| | R4| 


### GOTO表：

| | E| T| F|
---|---|---|---|
0|5| 4| 3| 
1|7| 4| 3| 
2|0| 0| 0| 
3|0| 0| 0| 
4|0| 0| 0| 
5|0| 0| 0| 
6|0| 10| 3| 
7|0| 0| 0| 
8|0| 0| 9| 
9|0| 0| 0| 
10|0| 0| 0| 
11|0| 0| 0| 