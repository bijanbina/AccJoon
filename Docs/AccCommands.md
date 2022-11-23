## Table of Content 
- [getVal](#getVal)
- [setVal](#setVal)
- [click](#click)
- [accList](#accList)

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

## accList
```
void accList("acc_path")
```

List all children in a recursive manner
	
### <acc_path>

`optional`

Acc path is the parent acc that the listing process begins, can be remained empty.