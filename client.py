import socket

server_socket = socket.socket()
server_name = 'localhost'
server_port = 1026
server_socket.bind((server_name, server_port))
server_socket.listen(5)

while True:

      c, address = server_socket.accept()
      print "WE GOT CONNECTION FROM", address
      c.send("hello, how are you ? ")

c.close()
