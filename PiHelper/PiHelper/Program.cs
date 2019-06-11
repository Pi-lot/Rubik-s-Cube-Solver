using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace PiHelper {
    class Program {
        private static int GetSize(Socket handler) {
            List<byte[]> size = new List<byte[]>();

            int total = 0;
            byte[] byteS = new byte[4];
            do {
                int r = handler.Receive(byteS);
                Console.WriteLine("Revieved {0} bytes", r);
                size.Add(byteS);
                total += r;
            } while (total < 4);

            List<byte> s = new List<byte>();
            foreach (byte[] bt in size)
                foreach (byte bb in bt)
                    s.Add(bb);

            return BitConverter.ToInt32(s.ToArray());
        }

        private static List<byte[]> RecieveData(Socket handler) {
            byte[] bytes = new byte[1024];

            List<byte[]> data = new List<byte[]>();
            int loops = 0;
            int count = 0;
            int size = GetSize(handler);
            Console.WriteLine("Expecting {0} bytes", size);
            int total = 0;
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

            return data;
        }

        private static List<byte[]> Reorganise(List<byte[]> list, int sizes = 54) {
            Console.Write("Reorganising data... ");

            List<byte> b = Flatten(list);
            list.Clear();

            list = UnFlatten(b, sizes);
            b.Clear();

            Console.WriteLine("Done");
            return list;
        }

        private static List<byte> Flatten(List<byte[]> list) {
            List<byte> b = new List<byte>();

            for (int i = list.Count - 1; i >= 0; i--) {
                for (int j = list[i].Length - 1; j >= 0; j--) {
                    b.Add(list[i][j]);
                }
                list.RemoveAt(i);
                list.TrimExcess();
            }
            b.Reverse();

            return b;
        }

        private static List<byte[]> UnFlatten(List<byte> list, int chunkSize = 54) {
            List<byte[]> b = new List<byte[]>();

            for (int j = list.Count - chunkSize; j >= 0; j -= chunkSize) {
                byte[] d = new byte[chunkSize];

                if (list.Count < chunkSize)
                    d = new byte[list.Count];
                for (int i = 0; i < d.Length; i++) {
                    d[i] = list[j];
                    list.RemoveAt(j);
                }
                b.Add(d);
                list.TrimExcess();
            }

            if (list.Count > 0) {
                byte[] d = new byte[list.Count];
                for (int i = 0; i < d.Length; i++) {
                    d[i] = list[0];
                    list.RemoveAt(0);
                }
            }
            b.Reverse();
            b.Distinct();
            return b;
        }

        private static void RemoveDuplicates(List<byte[]> data) {
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
        }

        public static void StartListening() {
            List<byte[]> data = new List<byte[]>();

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

                    data = RecieveData(handler);

                    data = Reorganise(data, 1024);

                    Console.Write("Sending back for clarification... ");
                    foreach (byte[] b in data)
                        handler.Send(b.ToArray());
                    byte[] checkB = new byte[1];
                    handler.Receive(checkB);

                    Console.Write("Done. ");

                    if (BitConverter.ToBoolean(checkB))
                        Console.WriteLine("All Correct");
                    else {
                        Console.WriteLine("Data wrong");
                        return;
                    }

                    data = Reorganise(data);

                    RemoveDuplicates(data);

                    Console.Write("Sending data back... ");
                    handler.Send(BitConverter.GetBytes(data.Count * 54));

                    data = Reorganise(data, 1024);

                    foreach (byte[] b in data)
                        handler.Send(b);
                    Console.WriteLine("Done");
                    handler.Receive(checkB);
                    Console.WriteLine("Closing connection");
                    handler.Shutdown(SocketShutdown.Both);
                    handler.Dispose();
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
