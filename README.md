

# NOTE
This is a command line tool to store/search/organize/review/... every signle note you added.


# Feature
**Smart** and **scientific** review algorithm to overcome [The Forgetting Curve](https://en.wikipedia.org/wiki/Forgetting_curve)

[访问 Repo](https://github.com/JayeWang/dic)

# Command Table

Command | Parameter(s) | Mode | Usage scenario
:-------|:-------|:------- |:-------
**rm** |  i0, i1, i3...| remove mutliple notes | developer's remove mode to manage data 
**rm last** | none | remove last note | remove last note be seen if it is too easy 
**rm last** | none | remove current note | remove current note be seen if it is too easy 
**rv rd** | num deafult:10  | num's random review |  review num of notes added anytime randomly 
**rv st** | num deafult:10 | num's smart review | review num of notes added 1,2,4,7,11 ago randomly 
**rv td** | num deafult:10 | today's review| review num of notes added today randomly 
**q/Q** | none | break current process | go back to previous process, exit if in main process
**clear** | none | clear current console | similiar ways: Command + L & Command + option + L
**other** | none | default serach/update | search based on input, ask insertion if nothing matches 
-------- | -----| --------------|--------------------------------------



# Code Report
cloc|github.com/AlDanial/cloc v 1.72  T=0.20 s (100.2 files/s, 15157.5 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C++|10|463|291|1274
C/C++ Header|9|255|426|339
Markdown|1|11|0|28
--------|--------|--------|--------|--------
SUM:|20|729|717|1641
