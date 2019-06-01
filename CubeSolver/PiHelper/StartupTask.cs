using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Http;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using Windows.ApplicationModel.Background;
using System.IO;

// The Background Application template is documented at http://go.microsoft.com/fwlink/?LinkID=533884&clcid=0x409

namespace PiHelper {
    public sealed class StartupTask : IBackgroundTask {
        public static void StartListening() {
            List<byte[]> positions = new List<byte[]>();

            byte[] buffer = new byte[54];
            //IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
            byte[] ip = new byte[4];
            ip[0] = 169;
            ip[1] = 254;
            ip[2] = 24;
            ip[3] = 74;

            IPAddress iPAddress = new IPAddress(ip);
            //IPAddress iPAddress = ipHostInfo.AddressList[1];
            IPEndPoint localEndPoint = new IPEndPoint(iPAddress, 11000);

            Socket listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try {
                listener.Bind(localEndPoint);
                listener.Listen(10);

                while (true) {
                    Socket handler = listener.Accept();
                    positions.Clear();

                    int num = int.MaxValue;
                    int count = -1;
                    do {
                        int data = handler.Receive(buffer);
                        if (count == -1) {
                            num = BitConverter.ToInt32(buffer, 0);
                        }
                        count++;
                        if (data > 4)
                            positions.Add(buffer);
                    } while (count < num);

                    List<byte[]> removed = new List<byte[]>();

                    foreach (byte[] pos in positions) {
                        if (removed.Count > 0) {
                            bool seen = false;
                            foreach (byte[] p in removed)
                                if (p.Equals(pos))
                                    seen = true;
                            if (!seen)
                                removed.Add(pos);
                        } else
                            removed.Add(pos);
                    }

                    byte[] size = BitConverter.GetBytes(removed.Count);

                    foreach (byte[] pos in removed) {
                        handler.Send(pos);
                    }

                    int r = handler.Receive(buffer);

                    handler.Shutdown(SocketShutdown.Both);
                    handler.Dispose();
                }
            } catch (Exception e) {
            }
        }

        public void Run(IBackgroundTaskInstance taskInstance) {
            StartListening();
            // 
            // TODO: Insert code to perform background work
            //
            // If you start any asynchronous methods here, prevent the task
            // from closing prematurely by using BackgroundTaskDeferral as
            // described in http://aka.ms/backgroundtaskdeferral
            //
        }
    }
}
