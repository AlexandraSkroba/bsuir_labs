﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace _153504_Skroba_Lab7
{
    public class Integral
    {
        public delegate void ForEvent(string message);

        public event ForEvent? LeadTime;
        public event ForEvent? Progress;

        public  Semaphore semaphore = new Semaphore(2, 2);

        public void SinX(object Data)
        {
            Stopwatch stopWatch = Stopwatch.StartNew();
            stopWatch.Start();

            semaphore.WaitOne();

            (double, double, int) data = ((double, double, int))Data;
            var a = data.Item1;
            var b = data.Item2;
            var n = data.Item3;

            double h = ((double)b - (double)a) / (int)n;
            double sum = 0;

            for (double i = 0; i <= n; i++)
            {
                var x = a + i * h;
                sum += Math.Sin(x);

                if (i / n * 10 == (int)(i / (int)n * 10))
                {
                    Progress?.Invoke($"\rПоток {Thread.CurrentThread.ManagedThreadId}: [{new String('=', (int)(i / n * 10)) + ">",-11}] {(int)(i / n * 100)}%");
                }
            }

            Console.WriteLine($"\nПоток {Thread.CurrentThread.ManagedThreadId}: Завершён с результатом: {h * sum} ");

            stopWatch.Stop();
            TimeSpan timeSpan = stopWatch.Elapsed;

            LeadTime?.Invoke("RunTime: " + String.Format($"{timeSpan.Seconds:0}.{timeSpan.Milliseconds:000}\n"));

            semaphore.Release();
        }
    }
}
