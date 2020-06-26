using System;
using System.Diagnostics;
using System.Threading;

namespace HLS_TO_MP4
{
    class Program
    {
        static string FolderPath = String.Format("E:\\videos\\{0}월", DateTime.Now.Month);
        static string URL = "http://220.69.244.50";
        static Process proc = new Process();
        static void Main(string[] args)
        {
            proc = new Process();
            proc.StartInfo = new ProcessStartInfo();
            proc.StartInfo.FileName = "ffmpeg\\ffmpeg.exe";
            proc.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            proc.StartInfo.Arguments = String.Format(" -y -i {0}:5000/hls/test.m3u8 -t {1} -acodec copy -bsf:a aac_adtstoasc -vcodec copy {2}"
                , URL, leftTime(), videoName());

            proc.Start();
            proc.WaitForExit();
            proc.Kill();


            while (DateTime.Now.Hour == 0 && DateTime.Now.Minute <= 1)
                Thread.Sleep(100);
            Console.WriteLine("Ended, Start to record new file.");

            Environment.Exit(0);
        }

        static string videoName()
        {
            System.IO.DirectoryInfo directoryInfo = new System.IO.DirectoryInfo(FolderPath);
            if (!directoryInfo.Exists)
            {
                System.IO.Directory.CreateDirectory(FolderPath);
            }


            return String.Format("{0}\\HLS_Record({1}년_{2}월_{3}일_{4}).mp4", FolderPath, DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day, DateTime.Now.DayOfWeek);
        }

        static string leftTime(int Hour = 0, int Minute = 0, int Seconds = 0)
        {
            int oneDay_Time;
            int OneDay_Left;

            if (Hour == 0)
                Hour = 24;
            if (Minute == 0)
                Minute = 0;
            if (Seconds == 0)
                Seconds = 0;
            oneDay_Time = Hour * 3600 + Minute * 60 + Seconds;


            OneDay_Left = oneDay_Time
                - (DateTime.Now.Hour * 3600 + DateTime.Now.Minute * 60 + DateTime.Now.Second);
            TimeSpan timeSpan = TimeSpan.FromSeconds(OneDay_Left);

            return timeSpan.ToString(@"hh\:mm\:ss");
        }
    }
}
