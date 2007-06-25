import java.io.*;
import java.nio.*;
import java.nio.channels.*;
import java.net.*;

public class RL_netlib
{
    protected Socket socket;
    protected SocketChannel socketChannel;
    protected ByteBuffer byteBuffer;
    protected DataInputStream inputStream;
    protected DataOutputStream outputStream;

    public static final int kExperimentConnection = 1;
    public static final int kAgentConnection = 2;
    public static final int kEnvironmentConnection = 3;

    public static final int kAgentInit = 4;
    public static final int kAgentStart = 5;
    public static final int kAgentStep = 6;
    public static final int kAgentEnd = 7;
    public static final int kAgentCleanup = 8;
    public static final int kAgentFreeze = 30;
    public static final int kAgentMessage = 31;

    public static final int kEnvInit = 9;
    public static final int kEnvStart = 10;
    public static final int kEnvStep = 11;
    public static final int kEnvCleanup = 12;
    public static final int kEnvSetState = 13;
    public static final int kEnvSetRandomSeed = 14;
    public static final int kEnvGetState = 15;
    public static final int kEnvGetRandomSeed = 16;
    public static final int kEnvMessage = 32;

    public static final int kRLInit = 17;
    public static final int kRLStart = 18;
    public static final int kRLStep = 19;
 

    public static final int kRLCleanup = 20;
    public static final int kRLReturn = 21;
    public static final int kRLNumSteps = 22;
    public static final int kRLNumEpisodes = 23;
    public static final int kRLEpisode = 24;
    public static final int kRLSetState = 25;
    public static final int kRLSetRandomSeed = 26;
    public static final int kRLGetState = 27;
    public static final int kRLGetRandomSeed = 28;
    public static final int kRLFreeze = 29;
    public static final int kRLAgentMessage = 33;
    public static final int kRLEnvMessage = 34;

    public static final String kLocalHost = "127.0.0.1";
    public static final int kDefaultPort = 4096;
    public static final int kRetryTimeout = 10;


    public RL_netlib(String host, int port) throws Exception
    {
	/* Setup SocketChannel for communication */
	InetSocketAddress address = new InetSocketAddress(host, port);
	socketChannel = SocketChannel.open();
	socketChannel.configureBlocking(true);
	socketChannel.connect(address);
	socket = socketChannel.socket();
	socket.setTcpNoDelay(true);
	inputStream = new DataInputStream(socket.getInputStream());
	outputStream = new DataOutputStream(socket.getOutputStream());
    }

    public void close() throws Exception
    {
	inputStream.close();
	outputStream.close();
	socket.close();
    }

    public DataInputStream getInputStream() 
    {
	return inputStream;
    }

    public DataOutputStream getOutputStream() 
    {
	return outputStream;
    }

    public byte[] read(int numBytes) throws Exception
    {
	int bytesRecv = 0;
	int msgError = 0;

	byte[] buffer = new byte[numBytes];

	while (bytesRecv < numBytes) {
	    msgError = inputStream.read(buffer, bytesRecv, numBytes-bytesRecv);
	    if (msgError <= 0) { throw new IOException(); }
	    else { bytesRecv += msgError; }
	}
	return buffer;
    }

    public void writeAbstractType(RLAbstractType rlat) {
	outputStream.writeInt(rlat.getNumInts());
	outputStream.writeInt(rlat.getNumDoubles());
	if (rlat.getNumInts() > 0) {
	    for (int i = 0; i < rlat.getNumInts(); i++) {
		outputStream.writeInt(rlat.getIntArray()[i]);
	    }
	}
	if (rlat.getNumDoubles() > 0) {
	    for (int i = 0; i < rlat.getNumDoubles(); i++) {
		outputStream.writeDouble(rlat.getDoubleArray()[i]);
	    }
	}
    }
		
    public RLAbstractType readAbstractType() {
	numInts = inputStream.readInt();
	numDoubles = inputStream.readInt();
	int[] intArray;
	double[] doubleArray;
	if (numInts > 0) {
	    intArray = new int[numInts];
	    for (int i = 0; i < numInts; i++) {
		intArray[i] = inputStream.readInt();
	    }
	}
	if (numDoubles > 0) {
	    doubleArray = new double[numDoubles];
	    for (int i = 0; i < numDoubles; i++) {
		doubleArray[i] = inputStream.readDouble();
	    }
	}
	return new RLAbstractType(numInts,numDoubles,intArray,doubleArray);
    }
}