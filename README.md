# RemoteJoy
RemoteJoy v0.1 is a p2p software which can collect input data of your XBox Controller then send it to remote host machine. Thus, you can use this package play "local cooperative" games (Lost Castle, Overcooked, etc) with your friends via internet. These game must support XBox controller.

## Install

Host:
1. Install ScpVBus, you can download and install it from [here](https://github.com/shauleiz/vXboxInterface/releases).
2. Move vXBoxInterface.lib into 'lib' folder.
3. cmake .. && make with VS

Client:
No need to instlal ScpVBus, other steps are same with Host.

## Usage
Host:
1. If you use route, set DMZ to your IP.
2. Open rjHost.exe, and click listen. If client connect to you, the address of client would print in the box below.

Client:
1. Open rjClient.exe, fill remote address and port, then click connect button.
2. You may select frequency to decide how fast you send message to host.

## TODO
1. Viberation force feedback
2. Graphics transsmission (may be long after)