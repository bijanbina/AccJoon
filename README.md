# AccJoon
AccJoon is a tool that exerts MSAA/UIA library to offer a scripting language to interact with any software. If you know the acc/uia path of a controller then AccJoon can find the controller and run an action on or read/write it's value. AccJoon is capable of even do conditional expression. 

Please checkout [AccScript](https://github.com/bijanbina/AccJoon/blob/main/Docs/AccScript.md) to learn more about the `acc` language.

## Usage

Two options are available

### Scripts Dir
You can create a `Scripts` directory beside `AccJoon` executable and put all of your `acc` script inside. `AccJoon` then execute them in an alphabetically order or you can give the script path and let the software to run it.

```accjoon <script_address> <arg1> <arg2> ... <argN>```

`<script_address>` is the relative path of a `.acc` script regard to the `AccJoon` executable path.

`<argN>` these arguments can be accessed with `"$N"` inside `AccScript`.

## Acknowledgment
Brought to you by Dr. E. Akhavan, One of the best programmer on earth!