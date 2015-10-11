import socket
from socket import *
server_socket = socket(AF_INET,SOCK_STREAM)
server_name = 'localhost'
server_port = 1026
server_socket.bind((server_name,server_port))
server_socket.listen(5)
get = ''

while True:
   c,address = server_socket.accept()
   print "WE GOT CONNECTION FROM", address
   c.send("hello, how are you?")
   get = server_socket.getsockopt(SOL_SOCKET,SO_RCVBUF)
   print "Get RCVBUF : ",get
   set = server_socket.setsockopt(SOL_SOCKET,SO_RCVBUF,1)
   print "Set RCVBUF : ",server_socket.getsockopt(SOL_SOCKET,SO_RCVBUF)

c.close
