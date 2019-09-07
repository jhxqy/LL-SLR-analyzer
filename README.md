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