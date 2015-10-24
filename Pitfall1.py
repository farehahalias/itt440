import socket
import sys
import errno
import os

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

server_address = ('localhost',10000)
#server_address=socket.htonl(127.0.0.1)
#server_address=socket.htons(80)
print>>sys.stderr, 'starting up on %s port %s' % server_address
sock.bind(server_address)

while True:
   print >>sys.stderr,'\nwaiting to receieve message'
   data,address = sock.recvfrom(4096)
   print >>sys.stderr, 'received %s bytes from %s' %(len(data),address)
   print >>sys.stderr, data

   if data:
      sent = sock.sendto(data,address)
      print >>sys.stderr, 'sent %s bytes back to %s'%(sent,address)

       

   get = sock.getsockopt(socket.SOL_SOCKET,socket.SO_SNDBUF)
   print "GET SNDBUF :",get

   if get > 0:    #pitfall 1
       print "Already Set"
   elif get<0:
      print "Error ",errno.EUSERS
      print "DESCRIPTION: ",os.strerror(errno.EUSERS)
      data.close(sock) #pitfall 2

   set = sock.setsockopt(socket.SOL_SOCKET,socket.SO_SNDBUF,1)
   print "SET SNDBUF : ",sock.getsockopt(socket.SOL_SOCKET,socket.SO_SNDBUF)
   break

#pitfall 3

   sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
   print 'add socket'
   ret = sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
try:

   sock.bind(('localhost',10000))

except socket.error, msg:
        print 'Bind FAILED.ERROR code : '+str(msg[0])+ 'Message\n' +msg[1]
        sys.exit()
print 'Socket bind 2 completed !!'
sock.close()
