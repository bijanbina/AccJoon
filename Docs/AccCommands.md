## Table of Content 
- [acc_getVal](#acc_getVal)
- [acc_setVal](#acc_setVal)
- [acc_list](#acc_list)
- [acc_listChild](#acc_listChild)
- [acc_getParent](#acc_getParent)
- [acc_getChild](#acc_getChild)
- [acc_search](#acc_search)
- [acc_getType](#acc_getType)
- [acc_getState](#acc_getState)
- [acc_getName](#acc_getName)

## acc_getVal
```
string acc_getVal("acc_path")
```

Get value from an `acc_path`

## acc_setVal
```
void acc_setVal("acc_path", "value")
```

Set value for an `acc_path`

## acc_list
```
void acc_list("acc_path")
```

List all children in a recursive manner
	
### <acc_path>

`optional`

Acc path is the parent acc that the listing process begins, can be remained empty.

## acc_listChild
```
void acc_listChild("acc_path")
```

List all children of acc from `acc_path`

### <acc_path>

`optional`

Acc path is the parent acc that the listing process begins, can be remained empty.

## acc_getParent
```
string acc_getParent("acc_path")
```

Get parent path of `acc_path`

## acc_getChild
```
string acc_getParent("acc_path", "name")
```

Get child match with `name` and from path of `acc_path`

## acc_search
```
string acc_search("acc_path", "name")
```

Search path by replacing `?` with possible cases of `acc_path` 
to find acc match with `name`, then returns true path

### <acc_path>

Acc path is a known path with only few unknown steps represented by `?`

## acc_getType
```
string acc_getParent("acc_path")
```

Get type of acc from path of `acc_path`

## acc_getState
```
string acc_getState("acc_path")
```

Get State of acc from path of `acc_path`

## acc_getName
```
string acc_getName("acc_path")
```

Get name of acc from path of `acc_path`