## Read
string read(acc_path)
Read a value from `acc_path`

## Write
void write(acc_path, value)
Set an acc object `value`

## Click
void click(acc_path, action, name, offset_x, offset_y, offset_id)
Do an `action` on center of `acc_path`
Possible `action` can be L/R/M/D/C
`name` can be used to specify a child acc
`offset_x` and `offset_y` can be used to add offset to click position
`offset_id` may be used as an alternative to child ID

## Key
void key(key)
Press `key`
`key` example: Ctrl+Shift+1, F1, Super+D

## Open
void open(check, workspace)
`check` is a process name that will be checked to prevent opening a duplicated app
Open application in `workspace` number, start from 1

## Delay
void delay(value)
Sleep `value` ms

## Lua
void lua(script_path)
Run lua from `script_path`