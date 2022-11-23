## Qt Example
```
shortcut("Qt")
{
	open("mom.exe", "", 6)
	sleep(2000)
	click("4.1.3.3.1.7", "L", "Mom")
	sleep(2000)
	key("F5")
	sleep(2000)
	key("Ctrl+1")
}
```

`shortcut` will find the shortcut which contains `Qt` in its name. then get the application `exe_name` and try to find the processor with the same `exe_name`. if the process was successful then Accjoon will focus on that process window and record it's `hwnd`.

`sleep` sleep amount of `2000` miliseconds.

`click` will find the acc object of `4.1.3.3.1.7`, then find the child with name `Mom`, and then perform `Left click` on center of acc object.

then `sleep` 2000ms more.

`key` will press `F5`

and so on ... 