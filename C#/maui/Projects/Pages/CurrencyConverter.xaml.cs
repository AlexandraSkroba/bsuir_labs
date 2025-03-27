using System.Collections.Generic;
using Projects.Entities;
using Projects.Services;

namespace Projects.Pages;

public partial class CurrencyConverter : ContentPage
{
	
	private readonly IRateService _rateService;
    private Rate _curRate { get; set; } = null;
    private List<Rate> RateList { get; set; }

    public CurrencyConverter(IRateService rateService)
	{
        _rateService = rateService;
        InitializeComponent();
        
        datePicker.MaximumDate = DateTime.Now;
        BindingContext = this;
    }

    private void OnConvertClicked(object sender, EventArgs e)
    {
            DisplayAlert("Ошибка", "Это не кнопка", "ОК");
            return;
    }


    private async void OnDateSelected(object sender, DateChangedEventArgs e)
    {
        RateList = (await _rateService.GetRates(datePicker.Date)).ToList();
        currencyPicker.ItemsSource = RateList;
        rublesEntry.Text = "";
        convertedEntry.Text = "";
    }

    private async void OnPageLoad(object sender, EventArgs e)
    {
        RateList = (await _rateService.GetRates(datePicker.Date)).ToList();
        currencyPicker.ItemsSource = RateList;
    }

    public void OnCurrentRateChanged(object sender, EventArgs e)
    {
        _curRate = currencyPicker.SelectedItem as Rate;
        if (rublesEntry.Text == String.Empty)
        {
            convertedEntry.Text = String.Empty;
        }
        else if (_curRate != null)
        {
            rublesEntry.TextChanged -= OnBynEntryTextChanged;
            rublesEntry.Text = $"{ConvertCurrencyToBYN(Convert.ToDecimal(_curRate.Cur_OfficialRate / _curRate.Cur_Scale), Convert.ToDecimal(convertedEntry.Text)):0.##}";
            rublesEntry.TextChanged += OnBynEntryTextChanged;
        }
    }

    public void OnBynEntryTextChanged(object sender, TextChangedEventArgs e)
    {

        if (rublesEntry.Text == String.Empty)
        {
            convertedEntry.Text = String.Empty;
        }
        else
        {

            if (_curRate != null)
            {

                decimal number;

                if (Decimal.TryParse(rublesEntry.Text, out number))
                {
                    convertedEntry.Text = $"{ConvertBYNToCurrency(Convert.ToDecimal(_curRate.Cur_OfficialRate / _curRate.Cur_Scale), number):0.##}";
                }
                else
                {
                    rublesEntry.Text = e.OldTextValue;
                }
            }

        }
    }

    private decimal ConvertBYNToCurrency(decimal curRate, decimal enteredByn)
    {
        return enteredByn / curRate;
    }

    private decimal ConvertCurrencyToBYN(decimal curRate, decimal enteredCurrency)
    {
        return enteredCurrency * curRate;
    }
}