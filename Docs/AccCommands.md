## Table of Content 
- [getVal](#getVal)
- [setVal](#setVal)
- [click](#click)
- [accList](#accList)
- [accListChild](#accListChild)
- [getParent](#getParent)
- [getChild](#getChild)
- [accSearch](#accSearch)
- [getType](#getType)
- [getState](#getState)
- [getName](#getName)

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

## accListChild
```
void accListChild("acc_path")
```

List all children of acc from `acc_path`

### <acc_path>

`optional`

Acc path is the parent acc that the listing process begins, can be remained empty.

## getParent
```
string getParent("acc_path")
```

Get parent path of `acc_path`

## getChild
```
string getParent("acc_path", "name")
```

Get child match with `name` and from path of `acc_path`

## accSearch
```
string accSearch("acc_path", "name")
```

Search path by replacing `?` with possible cases of `acc_path` 
to find acc match with `name`, then returns true path

### <acc_path>

Acc path is a known path with only few unknown steps represented by `?`

## getType
```
string getParent("acc_path")
```

Get type of acc from path of `acc_path`

## getState
```
string getState("acc_path")
```

Get State of acc from path of `acc_path`

## getName
```
string getName("acc_path")
```

Get name of acc from path of `acc_path`