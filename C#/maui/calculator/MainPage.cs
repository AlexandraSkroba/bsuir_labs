namespace calculator;

public partial class MainPage : ContentPage
{
	string mathOperator = "";
	double firstNumber, secondNumber;
	bool dotValue = false;
	bool newNumber = false;
	bool doubleMath = false;
	public MainPage()
	{
		InitializeComponent();
	}

    private void DotClick(object sender, EventArgs e)
    {
		if (dotValue) return;

		dotValue= true;
		
		result.Text += ",";
		secondNumber = Convert.ToDouble(result.Text);
    }

    private void OnClickOperator(object sender, EventArgs e)
    {
		Button button = (Button)sender;
		string mathThing = button.Text;

		switch (mathThing)
		{
			case "1/x":
				firstNumber = 1/firstNumber;
				break;

			case "x^2":
				firstNumber *= firstNumber;
				break;
		}

        result.Text = firstNumber.ToString();
    }

    private void ClearClick(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        string clear = button.Text;

		switch (clear)
		{
			case "C":
				result.Text = "0";
				firstNumber = 0;
				secondNumber = 0;
				dotValue = false;
				newNumber = false;
				mathOperator = "";
                doubleMath = false;
                break;

			case "CE":
                result.Text = "0";
                secondNumber = 0;
                dotValue = false;
				newNumber = false;
                break;

			case "⌫":
				if (result.Text[result.Text.Length - 1].Equals(',')) dotValue = false;
				if (result.Text.Length == 1)
				{
					result.Text = "0";
				}
				else
				{
					result.Text = result.Text.Remove(result.Text.Length - 1);
				}

				secondNumber = Convert.ToDouble(result.Text);
                break;

        }
    }

    private void OnClickMathOperator(object sender, EventArgs e)
    {
        Button button = (Button)sender;

		if (mathOperator != "" && !newNumber && doubleMath) { 
			switch (mathOperator)
			{
				case "/":
					firstNumber = firstNumber / secondNumber;
					break;

				case "×":
					firstNumber = firstNumber * secondNumber;
					break;

				case "−":
					firstNumber = firstNumber - secondNumber;
					break;

				case "+":
					firstNumber = firstNumber + secondNumber;
                    break;
            }

			result.Text = firstNumber.ToString();
			
		}
		else
		{
            firstNumber = secondNumber;
        }

        mathOperator = button.Text;
        newNumber = true;
    }

    private void OnClickCalculate(object sender, EventArgs e)
    {
		if (mathOperator != "" && !newNumber)
		{
            switch (mathOperator)
            {
                case "/":
                    secondNumber = firstNumber / secondNumber;
                    break;

                case "×":
                    secondNumber = firstNumber * secondNumber;
                    break;

                case "−":
                    secondNumber = firstNumber - secondNumber;
                    break;

                case "+":
                    secondNumber = firstNumber + secondNumber;
                    break;
            }

			doubleMath = false;

            result.Text = secondNumber.ToString();
        }
		
    }

    void OnClick(object sender, EventArgs e)
	{
		Button button = (Button)sender;
		string numString = button.Text;

		if(result.Text == "0" || newNumber)
		{
			result.Text = numString;
			newNumber = false;
			doubleMath = true;
		}
		else
		{
			result.Text += numString;
		}

		secondNumber = Convert.ToDouble(result.Text);
    }
}

