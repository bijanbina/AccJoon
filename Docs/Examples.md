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

## getVal
```
string getVal("acc_path")
```

Get value from an `acc_path`

## setVal
```
void setVal("acc_path", "value")
```

Set value for an `acc_path`

## click
```
void click("acc_path", "action", "name", offset_x, offset_y, offset_id)
```

Do an `action` on center of `acc_path`

### \<action\> 
	
Possible actions are 

- `L`: Left Click
- `R`: Right Click
- `M`: Middle Click
- `D`: Double Click
- `C`: Report Child ID (Debug Action)
	
### \<name\>

`optional`
	
specify a child in a list
	
### <offset_x, offset_y>
	
`optional`

add offset to the click position
	
### <offset_id>
	
`optional`

add offset to final child Id

## key
```
void key("key")
```

Press `key`

`key` example: Ctrl+Shift+1, F1, Super+D

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
	
Open application with argument `arg`
	
### \<workspace\>
`optional`
	
in `workspace` number, start from 1

`arg` not support " in itself

## accList
```
void accList("acc_path")
```

List all children in a recursive manner
	
### <acc_path>

`optional`

Acc path is the parent acc that the listing process begins, can be remained empty.
	
## sleep
```
void sleep(value)
```

Sleep `value` in miliseconds

## lua
```
void lua("script_path")
```

Run lua from `script_path`

## if
```
if( condition )
{
	...
}
```

## Full Example
```
shortcut("Qt")
{
	open("mom.exe", "", 6)
	delay(2000)
	click("4.1.3.3.1.7", "L", "Mom")
	delay(2000)
	key("F5")
	delay(2000)
	key("Ctrl+1")
}
```