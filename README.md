

# NOTE
This is a command line tool to store/search/organize/review/... every signle note you added.


# Feature
**Smart** and **scientific** review algorithm to overcome [The Forgetting Curve](https://en.wikipedia.org/wiki/Forgetting_curve)

[访问 Repo](https://github.com/JayeWang/dic)

# 命令列表 Command Table

Command | Parameter(s) | Mode | Usage scenario
:-------|:-------|:------- |:-------
**rm** |  i0, i1, i3...| remove mutliple notes | developer's remove mode to manage data 
**rm last** | none | remove showed note | remove any note be seen if it is too easy 
**rv rd** | num deafult:10  | num's random review |  review num of notes added anytime randomly 
**rv st** | num deafult:10 | num's smart review | review num of notes added 1,2,4,7,11 ago randomly 
**rv td** | num deafult:10 | today's review| review num of notes added today randomly 
**q/Q** | none | break current process | go back to previous process, exit if in main process
**clear** | none | clear current console | similiar ways: Command + L & Command + option + L
**other** | none | default serach/update | search based on input, ask insertion if nothing matches 
-------- | -----| --------------|--------------------------------------



# 代码分析 Code Report
cloc|github.com/AlDanial/cloc v 1.72  T=0.13 s (135.4 files/s, 19235.2 lines/s)
cloc|github.com/AlDanial/cloc v 1.72  T=0.15 s (132.8 files/s, 18560.9 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C++|10|404|271|1103
C/C++ Header|9|247|411|318
Markdown|1|17|0|25
--------|--------|--------|--------|--------
SUM:|20|668|682|1446


