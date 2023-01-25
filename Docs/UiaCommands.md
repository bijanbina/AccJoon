## Table of Content 
- [uia_getVal](#uia_getVal)
- [uia_setVal](#uia_setVal)
- [uia_list](#uia_list)
- [uia_listChild](#uia_listChild)
- [uia_getParent](#uia_getParent)
- [uia_getChild](#uia_getChild)
- [uia_search](#uia_search)
- [uia_getType](#uia_getType)
- [uia_getState](#uia_getState)
- [uia_getName](#uia_getName)
- [uia_toggle](#uia_toggle)
- [uia_getToggle](#uia_getToggle)

## uia_getVal
```
string uia_getVal("uia_path")
```

Get value from an `uia_path`

## uia_setVal
```
void uia_setVal("uia_path", "value")
```

Set value for an `uia_path`

## uia_list
```
void uia_list("uia_path")
```

List all children in a recursive manner
	
### <uia_path>

`optional`

Uia path is the parent uia that the listing process begins, can be remained empty.

## uia_listChild
```
void uia_listChild("uia_path")
```

List all children of uia from `uia_path`

### <uia_path>

`optional`

Uia path is the parent uia that the listing process begins, can be remained empty.

## uia_getParent
```
string uia_getParent("uia_path")
```

Get parent path of `uia_path`

## uia_getChild
```
string uia_getParent("uia_path", "name")
```

Get child match with `name` and from path of `uia_path`

## uia_search
```
string uia_search("uia_path", "name")
```

Search path by replacing `?` with possible cases of `uia_path` 
to find uia match with `name`, then returns true path

### <uia_path>

Uia path is a known path with only few unknown steps represented by `?`

## uia_getType
```
string uia_getParent("uia_path")
```

Get type of uia from path of `uia_path`

## uia_getState
```
string uia_getState("uia_path")
```

Get State of uia from path of `uia_path`

## uia_getName
```
string uia_getName("uia_path")
```

Get name of uia from path of `uia_path`

## uia_toggle
```
void uia_toggle("uia_path")
```

Toggle value of component from path of `uia_path`, if it supports UIA_ToggleToggleStatePropertyId.

## uia_toggle
```
string uia_getToggle("uia_path")
```

Get toggle value of component from path of `uia_path`, if it supports UIA_ToggleToggleStatePropertyId.
