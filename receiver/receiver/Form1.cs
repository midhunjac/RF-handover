using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.Windows.Forms.DataVisualization.Charting;
using System.Drawing.Text;
using Excel = Microsoft.Office.Interop.Excel;
using Microsoft.Office.Interop.Excel;
using System.Runtime.Remoting.Messaging;


namespace receiver
{

    public partial class Form1 : Form
    {
        SerialPort comport = new SerialPort();
        volatile bool stream = true;
        static string port = null;
        string cmd = null;
        bool cmd_accept = false;
        Thread streamthread = new Thread(start_stream);
        //Series Series1 = new Series();
        private DateTime start = DateTime.Now;
        int rowindex = 1;
        int colindex = 1;
        Excel.Application excelapp;
        Worksheet excelsheet;
        Workbook excelworkbook;
        string savepath = Environment.CurrentDirectory + "\\" + "test.xlsx";

        public Form1()
        {
            InitializeComponent();

            //load_chart();

            startread();
            
        }



        #region plotting

        /*private void load_chart()
        {
            //Chart chart = new Chart();
            chart.Series.Clear();
            Series1.Color = Color.Green;
            Series1.Name = "Measurement";
            Series1.IsXValueIndexed = true;
            Series1.ChartType = SeriesChartType.Line;
            chart.Series.Add(Series1);
            for(int i=0;i<100;i++)
            {
                f(i);
            }

        }

        public int f(int i)
        {
            double f = 59894 - (8128 * i) + (262 * i * i) - (1.6 * i * i * i);
            int num = Convert.ToInt32(f);
            Series1.Points.AddXY(num, i);
            return num;
        }
        

        private void plot_chart(int i)
        {
            var delta = DateTime.Now - start;
            Series1.Points.AddXY( delta.Milliseconds, i);

        }
        */
        #endregion


        #region excel export

        public void setupexcel()
        {
            try
            {
                excelapp = new Excel.Application();
                excelworkbook = excelapp.Workbooks.Add();
                excelapp.Visible = false;
                excelsheet = (Worksheet)excelworkbook.ActiveSheet;
                excelsheet.Visible = XlSheetVisibility.xlSheetVisible;

            }
            catch (Exception ex)
            {

            }
        }

        public void exporttoexcel(string[] val)
        {
            try
            {
                
                excelsheet.Cells[rowindex,colindex] = val[1];
                excelsheet.Cells[rowindex, colindex + 1] = val[2];
                excelsheet.Cells[rowindex, colindex + 2] = val[3];
                excelsheet.Cells[rowindex, colindex + 3] = val[4];
                excelsheet.Cells[rowindex, colindex + 4] = val[5];
                rowindex++;
                
                
            }
            catch (Exception ex)
            {

            }
        }
        
        public void stop_exporttoexcel()
        {
            try
            {
                excelworkbook.SaveAs(savepath);
                excelworkbook.Close();
                excelapp.Quit();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        #endregion

        public void startread()
        {

            try
            {
                setupexcel();
                comport.PortName = "N/A";
                string[] portnames = SerialPort.GetPortNames();
                foreach (string portname in portnames)
                {
                    cmbportnames.Items.Add(portname);
                }
                comport.BaudRate = 115200;
                comport.Parity = Parity.None;
                comport.StopBits = StopBits.One;
                comport.DataBits = 8;
                comport.Handshake = Handshake.None;
               
                
            }
            catch(Exception ex)
            {
                Console.WriteLine("Terminated : " + ex.Message);
            }
        }
        public void startdatastream()
        {
            Console.WriteLine("starting data stream");
            comport.PortName = port;
            comport.Open();
            
            while (true)
            {
                string message = comport.ReadLine();
                //string message = "SCAN";
                //Console.WriteLine(message);
                if(message.Contains("SCAN"))
                {
                    stream_measurements();
                    break;
                }
                if(cmd_accept == true)
                {
                    comport.WriteLine(cmd);
                }
            }
        }
        public static void start_stream()
        {
            Form1 form = new Form1();
            form.startdatastream();
        }
        public void stream_measurements()
        {
            while (true)
            {
                string message = comport.ReadLine();
                //string message = "24 34 54 64";
                string[] measurements; 
                measurements = message.Split(' ');
                Console.WriteLine(measurements[1]);
                if (measurements[1] == "END")
                {
                    stop_exporttoexcel();
                    break;
                }
                exporttoexcel(measurements);
                //plot_chart(Int32.Parse(measurements[1]));
            }

        }

        private void cmbportnames_SelectedIndexChanged(object sender, EventArgs e)
        {
            comport.PortName = cmbportnames.SelectedItem.ToString();
            port = cmbportnames.SelectedItem.ToString();
        }

        private void butopencom_Click(object sender, EventArgs e)
        {
            try
            {
                stream = true;
                //startdatastream();
                streamthread.Start();
                
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void butclosecom_Click(object sender, EventArgs e)
        {
            //stream = false;
           
            streamthread.Abort();
            //stop_exporttoexcel();

            comport.Close();
            Console.WriteLine("Closed the COM port");
        }

        private void cmdtb1_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Enter)
            {
                cmd = cmdtb1.Text;
                cmd_accept = true;
            }
        }
    }
}
