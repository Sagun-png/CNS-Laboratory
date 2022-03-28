import java.net.*;
import java.util.*;
public class udpserver {
public static void main(String[] args)
{
try
{
DatagramSocket server = new DatagramSocket(1537);
System.out.println("Enter server message:");
Scanner scan = new Scanner(System.in);
while(true)
{
byte[] buffer = new byte[1000];
DatagramPacket request = new DatagramPacket(buffer,buffer.length);
server.receive(request);
String message = scan.nextLine();
byte[] sendMessage = message.getBytes();
DatagramPacket reply = new DatagramPacket(sendMessage,sendMessage.length, request.getAddress(), request.getPort());
server.send(reply);
server.close();
scan.close();
}
}
catch(Exception ex) {}
}
}
package pgm;
 
import java.net.*;
public class udpclient {
public static void main(String[] args)
{
try
{
DatagramSocket client = new DatagramSocket();
int serverSocket = 1537;
InetAddress host = InetAddress.getByName("127.0.0.1");
String message = "Text Message";
byte[] sendMessage = message.getBytes();
DatagramPacket request = new DatagramPacket(sendMessage,sendMessage.length, host, serverSocket);
client.send(request);
byte[] buffer = new byte[1000];
DatagramPacket reply = new DatagramPacket(buffer, buffer.length);
client.receive(reply);
System.out.println("Client received:\n "+new String(reply.getData()));
client.close();
}
catch(Exception ex) {}
}
}
