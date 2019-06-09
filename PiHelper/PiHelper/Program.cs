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

                    int total = 0;
                    byte[] byteS = new byte[4];
                    do {
                        int r = handler.Receive(byteS);
                        Console.WriteLine("Revieved {0} bytes", r);
                        data.Add(byteS);
                        total += r;
                    } while (total < 4);

                    List<byte> s = new List<byte>();
                    foreach (byte[] bt in data)
                        foreach (byte bb in bt)
                            s.Add(bb);
                    data.Clear();

                    int loops = 0;
                    int count = 0;
                    int size = BitConverter.ToInt32(s.ToArray(), 0);
                    Console.WriteLine("Expecting {0} bytes", size);
                    total = 0;
                    while (total < size) {
                        int recieved = handler.Receive(bytes);
                        byte[] rb = new byte[recieved];
                        for (int i = 0; i < recieved; i++) {
                            rb[i] = bytes[i];
                        }
                        data.Add(rb);
                        total += recieved;
                        if (recieved == bytes.Length)
                            count++;
                        loops++;
                    }
                    data.Distinct();

                    Console.WriteLine("Buffer filled {0} times out of {1}", count, loops);
                    Console.WriteLine("Average bytes: {0}", total / loops);
                    Console.WriteLine("Percent: {0}", ((float)count / (float)loops) * 100);

                    Console.WriteLine("{0} bytes recieved", total);
                    Console.WriteLine("List size {0}", total / 54);

                    Console.Write("Reorganising data... ");

                    List<byte> b = new List<byte>();
                    foreach (byte[] ba in data)
                        foreach (byte bb in ba)
                            b.Add(bb);

                    data.Clear();

                    for (int j = 0; j < b.Count; j += 54) {
                        byte[] d = new byte[54];
                        if (j + 54 > b.Count)
                            d = new byte[b.Count - j];
                        for (int i = 0; i < d.Length; i++) {
                            d[i] = b[j + i];
                        }
                        data.Add(d);
                    }

                    data.Distinct();

                    Console.WriteLine("Done");

                    Console.Write("Sending back for clarification... ");
                    handler.Send(b.ToArray());

                    b.Clear();

                    byte[] checkB = new byte[1];
                    handler.Receive(checkB);

                    Console.Write("Done. ");

                    if (BitConverter.ToBoolean(checkB))
                        Console.WriteLine("All Correct");
                    else {
                        Console.WriteLine("Data wrong");
                        return;
                    }

                    Console.Write("Removing Duplicates... ");
                    List<byte[]> check = new List<byte[]>();
                    for (int i = data.Count - 1; i >= 0; i--) {
                        if (check.Count < 1) {
                            check.Add(data[i]);
                            data.RemoveAt(i);
                        } else {
                            bool seen = false;

                            for (int j = 0; j < check.Count; j++) {
                                if (data[i].SequenceEqual(check[j])) {
                                    seen = true;
                                    break;
                                }
                            }

                            if (!seen)
                                check.Add(data[i]);

                            data.RemoveAt(i);
                        }
                    }

                    data.Clear();

                    for (int i = check.Count - 1; i >= 0; i--) {
                        data.Add(check[i]);
                        check.RemoveAt(i);
                    }

                    check.Clear();
                    Console.WriteLine("Done. New length: {0}", data.Count);

                    Console.Write("Reorganising data... ");
                    foreach (byte[] ba in data)
                        foreach (byte bb in ba)
                            b.Add(bb);

                    Console.WriteLine("Done");
                    data.Clear();

                    Console.Write("Sending data back... ");
                    handler.Send(BitConverter.GetBytes(b.Count));
                    handler.Send(b.ToArray());
                    Console.WriteLine("Done");
                    handler.Receive(bytes);
                    Console.WriteLine("Closing connection");
                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                    handler.Dispose();
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
