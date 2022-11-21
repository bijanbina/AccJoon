## Shortcut
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

## Read
```
string read("acc_path")
```

Read a value from `acc_path`

## Write
```
void write("acc_path", "value")
```

Set an acc object `value`

## Click
```
void click("acc_path", "action", "name", offset_x, offset_y, offset_id)
```

Do an `action` on center of `acc_path`

Possible actions are 

- `L`: Left Click
- `R`: Right Click
- `M`: Middle Click
- `D`: Double Click
- `C`: Report Child ID (Debug Action)

`name` can be used to specify a child in a list

`offset_x` and `offset_y` can be used to add offset to the click position

`offset_id` may be used as an alternative to child ID

## Key
```
void key("key")
```

Press `key`

`key` example: Ctrl+Shift+1, F1, Super+D

## Open
```
void open("check", "arg", workspace)
```

`check` is a process name that will be checked to prevent opening a duplicated app

Open application with argument `arg` in `workspace` number, start from 1

`arg` not support " in itself

## Delay
```
void delay(value)
```

Sleep `value` ms

## Lua
```
void lua("script_path")
```

Run lua from `script_path`

## If
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