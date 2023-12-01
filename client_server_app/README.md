# client_server_app

Description:
Client/Server application to load files from remote HOST.
- Communication in between client and server is done via port 7500
- client sends list of files in his folder
- server requests to load a specific file from the list via specific port. Ex port (7505)
- client sends the file to the server via port 7505

Use makefiles to compile the code. There is a separate makefile for both client and server in corresponding directories.

Works for both windows and linux.
