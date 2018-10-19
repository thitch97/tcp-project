# Protocol

## Type of messages
Type: format string 
===
Syntax: | to_format |\0|
to_format: 2 bytes

Type: name string
===
Syntax: | to_name |\0|
to_name: 256 bytes

Type: 
- Syntax: 

## Rules (Order of Operations)

1. Send to_format string to server
2. Send to_name string to server
3. Send file to server as a collection of the individual bytes in the file
4. Server sends confirmation or failure message

## Usage
- Open a terminal window and run ./server <port_number>
- In a new terminal window, run ./client <server_IP> <port_numnber> <file_path> <to_format> <to_name>

## Compilation
Client:
- gcc -o client client.c dwerror.c

Server:
- gcc -o server server.c dwerror.c hndl_client.c

## Code Base Referenced
TCP/IP Sockets in C: Practical Guide for Programmers, Donahoo, M., Kenneth, C.L. (2001)