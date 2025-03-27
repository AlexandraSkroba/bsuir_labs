using System.Security.Cryptography;

namespace Projects.Pages;


public partial class Calculator : ContentPage
{
    string mathOperator = "";
    double firstNumber, secondNumber;
    bool firstOperator = true;
    bool dotValue = false;
    bool newNumber = true;
    bool doubleMath = false;

    public Calculator()
	{
		InitializeComponent();
	}

    private void DotClick(object sender, EventArgs e)
    {
        if (dotValue) return;

        dotValue = true;

        result.Text += ",";
    }

    private void OnClick(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        string numberString = button.Text;

        if (numberString == "+/-")
        {
            if (result.Text[0].Equals('-'))
            {
                result.Text = result.Text.Remove(0, 1);
            }
            else
            {
                result.Text = "-" + result.Text;
            }

            if ((mathOperator != "" && newNumber && !doubleMath) || doubleMath)
            {
                firstNumber = Convert.ToDouble(result.Text);
            }
            else
            {
                secondNumber = Convert.ToDouble(result.Text);
            }

            return;
        }

        int number = Convert.ToInt32(numberString);

        if (doubleMath)
        {
            mathOperator = "";
            firstOperator = true;
        }

        if (this.result.Text == "0" || newNumber)
        {
            this.result.Text = numberString;
            newNumber = false;
        }
        else
        {
            this.result.Text += numberString;
        }

        secondNumber = Convert.ToDouble(this.result.Text);
        dotCheck();
    }

    void dotCheck()
    {
        double number = Convert.ToDouble(result.Text);
        if (number != (int)number)
        {
            dotValue = true;
        }
        else
        {
            dotValue = false;
        }
    }

    private void OnClickCalculate(object sender, EventArgs e)
    {
        if (mathOperator != "" && !newNumber)
        {
            switch (mathOperator)
            {
                case "/":
                    firstNumber /= secondNumber;
                    break;
                case "×":
                    firstNumber *= secondNumber;
                    break;
                case "−":
                    firstNumber -= secondNumber;
                    break;
                case "+":
                    firstNumber += secondNumber;
                    break;
            }

            result.Text = firstNumber.ToString();

            dotCheck();

            firstOperator = false;

            doubleMath = true;
        }
    }

    private void OnClickMathOperator(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        string buttonMath = button.Text;

        if (firstOperator == true)
        {
            firstNumber = secondNumber;
            firstOperator = false;
        }
        else if (mathOperator != "" && !newNumber && !doubleMath)
        {
            switch (mathOperator)
            {
                case "/":
                    firstNumber /= secondNumber;
                    break;
                case "×":
                    firstNumber *= secondNumber;
                    break;
                case "−":
                    firstNumber -= secondNumber;
                    break;
                case "+":
                    firstNumber += secondNumber;
                    break;
            }

            dotCheck();

            result.Text = firstNumber.ToString();
        }

        doubleMath = false;

        mathOperator = buttonMath;

        newNumber = true;
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
                newNumber = true;
                firstOperator= true;
                mathOperator = "";
                doubleMath = false;
                break;

            case "CE":
                result.Text = "0";
                if ((mathOperator != "" && newNumber && !doubleMath) || doubleMath)
                {
                    firstNumber = 0;
                }
                else
                {
                    secondNumber = 0;
                }
                dotValue = false;
                doubleMath = false;
                break;

            case "⌫":
                if (result.Text[result.Text.Length - 1].Equals(','))
                {
                    dotValue = false;
                }
                if (result.Text[result.Text.Length - 1].Equals('−'))
                {
                    result.Text = "0";
                    secondNumber = 0;
                }
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
    
    private void OnClickOperator(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        string buttonOperator = button.Text;

        firstNumber = Convert.ToDouble(result.Text);
        dotCheck();
        mathOperator = "";
        firstOperator = true;
        doubleMath = false;

        switch (buttonOperator)
        {
            case "e^x":
                secondNumber = Math.Exp(firstNumber);
                break;
            case "%":
                secondNumber = firstNumber / 100;
                break;
            case "1/x":
                secondNumber = 1 / firstNumber;
                break;
            case "x^2":
                secondNumber = firstNumber * firstNumber;
                break;
            case "√":
                secondNumber = Math.Sqrt(firstNumber);
                break;
        }

        this.result.Text = secondNumber.ToString();
    }
}