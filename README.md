# AccJoon
AccJoon is a little tool that exerts MSAA library to present a command line interface to interact with any software. If you know the `acc path` of a controller then AccJoon can find the controller for you and run an action on it. Currently, supported actions are listed below. Hope to extend AccJoon capabilities in the near future

### Actions
- Left Click (L)
- Double Click (D)
- Middle Click (M)
- Right Click (R)
- Return Child ID (C)
- Key Press (K)

### Usage
`accjoon <action> <acc_path> <offset_x> <offset_y> <child_name> <child_offset>`
* The last child id can be excluded from the path and pass as a string argument. AccJoon will match the input with the corresponding child
* Click can have offset from the center of the acc object
* Add A as a prefix to action and you will get a admin right with the help of rebound!
* Child offset is the optional offset from child name
* If using key press action, child name become key

### Key Codes
Key codes are in match with AHK key code conventions. Some example are available below:

Ctrl+R: ^R

Ctrl+Alt+Del: ^!R

### Acknowledgment
Brought to you by only and only DR AKHAVAN! BTW I'm in love with him :)
