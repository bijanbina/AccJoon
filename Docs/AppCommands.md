## shortcut
```
shortcut("name", "title")
{
	...
}
```
Focus on an application by providing

### \<name\>

`case-insensitive`

name is part of application shortcut's name. 

Examples: `Qt`, `Altium`, `Telegram`

### <title>

`optional`

To match better, you can specify a string that the matched window title should have

## open
```
void open("check", "arg", workspace)
```
open an application
	
### \<check\>
	
`optional`
	
process name that will be checked to prevent opening a duplicated app
	
### \<arg\>

`optional`
	
Open application with arguments of `arg`
	
### \<workspace\>
`optional`
	
Open application in the specified `workspace` number, start from 1