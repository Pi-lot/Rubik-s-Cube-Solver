using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace PiHelper {
    class Program {
        public static void StartListening() {
            List<byte[]> data = new List<byte[]>();

            byte[] bytes = new byte[1024];

            IPHostEntry iPHostInfo = Dns.GetHostEntry(Dns.GetHostName());
            Console.WriteLine(Dns.GetHostName());
            byte[] ip = new byte[4];
            ip[0] = 169;
            ip[1] = 254;
            ip[2] = 253;
            ip[3] = 84;
            IPAddress iPAddress = new IPAddress(ip);//iPHostInfo.AddressList[1];
            IPEndPoint localEndPoint = new IPEndPoint(iPAddress, 11000);

            Socket listener = new Socket(iPAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            try {
                listener.Bind(localEndPoint);
                listener.Listen(10);

                bool listen = true;
                while (listen) {
                    Console.WriteLine("Waiting for connection on {0}", iPAddress.ToString());
                    Socket handler = listener.Accept();
                    data.Clear();
                    Console.WriteLine("Connection recieved from {0}", handler.RemoteEndPoint);

                    int t = 0;
                    int r = 0;
                    byte[] byteS = new byte[4];
                    do {
                        r = handler.Receive(byteS);
                        Console.WriteLine("Revieved {0} bytes", r);
                        data.Add(byteS);
                        t += r;
                    } while (t < 4);

                    byte[] s = new byte[4];
                    if (data.Count > 1)
                        for (int i = 0; i < data.Count; i++)
                            for (int j = 0; j < data[i].Length; j++)
                                s[i + j] = data[i][j];
                    else
                        s = data[0];
                    data.Clear();

                    int loops = 0;
                    int count = 0;
                    int size = BitConverter.ToInt32(s, 0);
                    Console.WriteLine("Expecting {0} bytes", size);
                    int total = 0;
                    do {
                        int recieved = handler.Receive(bytes);
                        data.Add(bytes);
                        total += recieved;
                        if (recieved == bytes.Length)
                            count++;
                        loops++;
                    } while (total < size);
                    Console.WriteLine("Buffer filled {0} times out of {1}", count, loops);
                    Console.WriteLine("Average bytes: {0}", total / loops);
                    Console.WriteLine("Percent: {0}", ((float)count / (float)loops) * 100);

                    Console.WriteLine("{0} bytes recieved", total);
                    Console.WriteLine("List size {0}", total / 54);

                    Console.WriteLine("Sending back for clarification");
                    foreach (byte[] piece in data)
                        handler.Send(piece);

                    Console.Write("Reorganising data... ");

                    List<byte> b = new List<byte>();
                    for (int i = 0; i < data.Count; i++)
                        for (int j = 0; j < data[i].Length; j++)
                            b.Add(data[i][j]);

                    data.Clear();

                    byte[] d = new byte[54];
                    for (int i = 0; i < b.Count; i++) {
                        d[i % 54] = b[i];
                        if (i % 54 == 53)
                            data.Add(d);
                    }
                    Console.WriteLine("Done");

                    for (int i = 0; i < 4 * 54; i++) {
                        Console.Write("|{0}|", b[i]);
                        if (i % 54 == 53) {
                            Console.WriteLine();

                            foreach (byte pb in data[i % 54])
                                Console.Write("|{0}|", pb);
                            Console.WriteLine();
                        }
                    }

                    b.Clear();

                    Console.Write("Removing Duplicates... ");
                    byte[][] check = new byte[data.Count][];
                    data.CopyTo(check);
                    data.Clear();
                    for (int i = 0; i < check.Length; i++) {
                        if (data.Count < 1)
                            data.Add(check[i]);
                        else {
                            bool seen = false;

                            for (int j = 0; j < data.Count; j++) {
                                if (check[i].SequenceEqual(data[j])) {
                                    seen = true;
                                    break;
                                }
                            }

                            if (!seen)
                                data.Add(check[i]);
                        }
                    }
                    check = new byte[0][];
                    Console.WriteLine("Done. New length: {0}", data.Count);

                    Console.Write("Reorganising data... ");
                    foreach (byte[] ba in data)
                        foreach (byte bb in ba)
                            b.Add(bb);
                    data.Clear();
                    Console.WriteLine("Done");

                    Console.Write("Sending data back... ");
                    handler.Send(b.ToArray());
                    Console.WriteLine("Done");
                    Console.WriteLine("Closing connection");
                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                }
            } catch (Exception e) {
                Console.WriteLine(e.ToString());
            }
        }
        static void Main(string[] args) {
            StartListening();
            Console.WriteLine("Stopping");
        }
    }
}
