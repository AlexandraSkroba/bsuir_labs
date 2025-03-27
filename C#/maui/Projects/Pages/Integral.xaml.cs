using System.Diagnostics;
using System.Threading;

namespace Projects.Pages;

public partial class Integral : ContentPage
{

    private bool isCalculating;
    private CancellationTokenSource cancellationTokenSource;

    public Integral()
	{
		InitializeComponent();
        isCalculating = false;
        cancellationTokenSource = new CancellationTokenSource();
    }

    private async void OnStartClicked(object sender, EventArgs e)
    {
        if (!isCalculating)
        {
            isCalculating = true;
            resultLabel.Text = "Вычисление...";
            startButton.IsEnabled= false;
            progressBar.Progress = 0;
            await CalculateIntegralAsync();
            MainThread.BeginInvokeOnMainThread(() =>
            {
                startButton.IsEnabled = true;
            });
            
            //Debug.WriteLine($"-----------> {startButton.IsEnabled}");
        }
    }

    private void OnCancelClicked(object sender, EventArgs e)
    {
        if (isCalculating)
        {            
            cancellationTokenSource.Cancel();
            isCalculating = false;
            startButton.IsEnabled = true;
        }
    }

    private async Task CalculateIntegralAsync()
    {
        double x = 0;
        double sum = 0;
        int iterations = 0;
        await Task.Run(async () =>
        {
            while (x < 1 && !cancellationTokenSource.IsCancellationRequested)
            {
                sum += Math.Sin(x) * 0.00000001;
                x += 0.00000001;
                iterations++;
                if (iterations % 100000 == 0)
                {
                    double progress = x;
                    await MainThread.InvokeOnMainThreadAsync(() =>
                    {
                        progressBar.Progress = progress;
                        progressLabel.Text = $"{(progress * 100).ToString("N2")}%";
                    });
                }
            }
        },cancellationTokenSource.Token);
        if (!cancellationTokenSource.IsCancellationRequested)
        {
            resultLabel.Text = $"Результат: {sum}";
            progressLabel.Text = "Готово!";
            startButton.IsEnabled= true;
            isCalculating = false;
        }
        else
        {
            resultLabel.Text = "Задание отменено";
            isCalculating = false;
            cancellationTokenSource = new CancellationTokenSource();
            startButton.IsEnabled = true;
        }
    }
}