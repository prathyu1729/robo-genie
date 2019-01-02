using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System;  
using System.Net;  
using System.Net.Sockets;  
using System.Text;  
//using System.Diagnostics;
using System.Threading;

public class control: MonoBehaviour {

	// Use this for initialization
	Vector3 finalcd;
	string file_path;
	string inp_ln;
	StreamReader inp_stm;
	private TcpClient socketConnection; 	
	private Thread clientReceiveThread;
	//Socket sender;
	//byte[] bytes = new byte[1024];
	void Start () 
	{
		ConnectToTcpServer();
		/* file_path="/home/sourabha235/Desktop/test.txt";
		inp_stm = new StreamReader(file_path);
		IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());  
		IPAddress ipAddress = IPAddress.Parse("192.168.43.123");
		IPEndPoint remoteEP = new IPEndPoint(ipAddress,8080);
		sender = new Socket(ipAddress.AddressFamily,SocketType.Stream, ProtocolType.Tcp );
		try {  
                sender.Connect(remoteEP);  
  
                Debug.Log("Socket connected to {0}"+sender.RemoteEndPoint.ToString());  
  
                // Encode the data string into a byte array.  
                byte[] msg = Encoding.ASCII.GetBytes("This is a test<EOF>");  
  
                // Send the data through the socket.  
                int bytesSent = sender.Send(msg); 
                }
                catch (ArgumentNullException ane) {  
                Debug.Log("ArgumentNullException : {0}"+ane.ToString());  
            } catch (SocketException se) {  
                Debug.Log("SocketException : {0}"+se.ToString());  
            } catch (Exception e) {  
                Debug.Log("Unexpected exception : {0}"+e.ToString());  
            } 
            int bytesRec = sender.Receive(bytes);  
            Debug.Log("Echoed test = {0}"+Encoding.ASCII.GetString(bytes,0,bytesRec));
            */
	}
	
	// Update is called once per frame
	void Update () 
	{
		/*int bytesRec = sender.Receive(bytes);  
                Debug.Log("Echoed test = {0}"+Encoding.ASCII.GetString(bytes,0,bytesRec));
		 if (Input.GetKey("escape"))
        {
        sender.Shutdown(SocketShutdown.Both);  
            sender.Close();
            Application.Quit();
        }*/
		
                 //!inp_stm.EndOfStream
		    /*while(!inp_stm.EndOfStream)
			{
				inp_ln = inp_stm.ReadLine( );
				 
			 /*if(string.Equals(inp_ln,"R"))
			    {
				Vector3 position = this.transform.position;
				position.x=position.x+0.5f;
				this.transform.position = position;
				Debug.Log (inp_ln);
				return;
			    }

			 if(string.Equals(inp_ln,"L"))
			  {  
				Vector3 position = this.transform.position;
				position.x-=0.5f;
				this.transform.position = position;
				Debug.Log (inp_ln);
				return;
			   }

			 if(string.Equals(inp_ln,"U"))
			  {
				Vector3 position = this.transform.position;
				position.z+=+0.5f;
				this.transform.position = position;
				Debug.Log (inp_ln);
				return;
			  }

			if(string.Equals(inp_ln,"D"))
			 { 
				Vector3 position = this.transform.position;
				position.z-=+0.5f;
				this.transform.position = position;
				Debug.Log (inp_ln);
				return;
			 }*/
                                Vector3 position = this.transform.position;
				position.x = StringToVector3(inp_ln).x/10;
				position.z = StringToVector3(inp_ln).z/10;
				this.transform.position = position;
				//Debug.Log (inp_ln);
				return;

/*
		}

		inp_stm.Close( ); */


	}

private void ConnectToTcpServer () { 		
		try {  			
			clientReceiveThread = new Thread (new ThreadStart(ListenForData)); 			
			clientReceiveThread.IsBackground = true; 			
			clientReceiveThread.Start();  		
		} 		
		catch (Exception e) { 			
			Debug.Log("On client connect exception " + e); 		
		} 	
	} 
private void ListenForData() { 		
		try { 			
			socketConnection = new TcpClient("10.10.37.87", 8105);  			
			Byte[] bytes = new Byte[100];
			try { 			
			// Get a stream object for writing. 			
			NetworkStream stream = socketConnection.GetStream(); 			
			if (stream.CanWrite) {                 
				string clientMessage = "This is a message from one of your clients."; 				
				// Convert string message to byte array.                 
				byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage); 				
				// Write byte array to socketConnection stream.                 
				stream.Write(clientMessageAsByteArray, 0, clientMessageAsByteArray.Length);                 
				Debug.Log("Client sent his message - should be received by server");             
			}         
		} 		
		catch (SocketException socketException) {             
			Debug.Log("Socket exception: " + socketException);         
		}             
			while (true) { 	
			Debug.Log("Redache message received as: ");			
				// Get a stream object for reading 				
				using (NetworkStream stream = socketConnection.GetStream()) { 					
					int length; 	
									
					// Read incomming stream into byte arrary. 					
					while ((length = stream.Read(bytes, 0, 100)) != 0) { 						
						var incommingData = new byte[length]; 						
						Array.Copy(bytes, 0, incommingData, 0, length); 						Debug.Log(length);
						Array.Clear(bytes, 0, bytes.Length);
						// Convert byte array to string message. 						
						string serverMessage = Encoding.ASCII.GetString(incommingData); 					 	inp_ln = serverMessage;
						stream.Flush();
						//break;
						//strcpy(inp_ln, serverMessage);
						//finalcd = StringToVector3(inp_ln);
						//Debug.Log("server message received as: " + serverMessage); 					
					} 				
				} 			
			} 
			        
		}         
		catch (SocketException socketException) {             
			Debug.Log("Socket exception: " + socketException);         
		}     
	}  	
	
       Vector3 StringToVector3(string sVector)
     {
         // Remove the parentheses
         if (sVector.StartsWith ("(") && sVector.EndsWith (")")) {
             sVector = sVector.Substring(1, sVector.Length-2);
         }
 	
 	 //Debug.Log("\nstart  "+sVector+"  +++++++ \n");
         // split the items
         string[] sArray = sVector.Split(',');
 
         // store as a Vector3
         Vector3 result = new Vector3(
             float.Parse(sArray[0]),
             float.Parse(sArray[1]),
             float.Parse(sArray[2]));
 
         return result;
     }













}
