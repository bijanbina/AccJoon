## Table of Content 
- [app](#app)
- [open](#open)
- [isOpen](#isOpen)
- [waitOpen](#waitOpen)

## app
```
app("name", "title")
{
	...
}
```
Focus on an application by providing

### \<name\>

`case-insensitive`

name is part of application app's name. 

Examples: `Qt`, `Altium`, `Telegram`

### <title>

`optional`

To match better, you can specify a string that the matched window title should have

## open
```
void open("arg", workspace)
```
open an application
		
### \<arg\>

`optional`
	
Open application with arguments of `arg`
	
### \<workspace\>
`optional`
	
Open application in the specified `workspace` number, start from 1

## isOpen
```
int isOpen("process_name")
```
Returns 1 if process_name is existed otherwise returns 0.
		
### \<process_name\>
	
Examples: `X2.exe`, `gitkraken.exe`

## waitOpen
```
void waitOpen("process_name")
```
Wait for opening process_name
		
### \<process_name\>
	
Examples: `X2.exe`, `gitkraken.exe`