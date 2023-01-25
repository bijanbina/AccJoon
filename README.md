# AccJoon
AccJoon is a tool that exerts MSAA library to offer a scripting language to interact with any software. If you know the acc path of a controller then AccJoon can find the controller for you and run an action on it, read/wirte it's value and even do conditional expression. 

Please checkout [AccScript](https://github.com/bijanbina/AccJoon/blob/main/Docs/AccScript.md) page to learn more about the `acc` language.

## Usage

Two options are available

### Scripts Dir
You can create a `Scripts` directory beside `AccJoon` executable and put all of your `acc` script inside. `AccJoon` then execute them in an alphabetically order.

### Run with Command Line

```accjoon -c <script_address>```

`<script_address>` is the relative path of a `.acc` script regard to the `AccJoon` executable path

## Acknowledgment
Brought to you by Dr. E. Akhavan, One of the best programmer on earth!