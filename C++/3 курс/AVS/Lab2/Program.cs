using System.Security.AccessControl;
using System.Text;

internal class Lab2
{
    public static void Main(string[] args)
    {
        string ConvertToDoubleSystem(int x, bool flag)
        {
            int buff = x;
            var binaryNumber = "";

            x = Math.Abs(x);
            if (x == 0) binaryNumber = "0";
            while (x > 0)
            {
                binaryNumber = (x % 2) + binaryNumber;
                x /= 2;
            }
            if (buff <= 0 && !flag) binaryNumber = binaryNumber.Insert(0, "-");
            else binaryNumber = binaryNumber.Insert(0, "+");
            return binaryNumber;
        }

        string ConvertToDirectСode(string binNum, bool flag)
        {
            string dirCodeStr = binNum.Remove(0, 1);
            int length = 41 - binNum.Length;

            string substr = "";
            for (int i = 0; i < length; i++)
            {
                substr += "0";
            }
            dirCodeStr = dirCodeStr.Insert(0, substr);

            if (!flag) dirCodeStr = dirCodeStr.Insert(0, "1");
            else dirCodeStr = dirCodeStr.Insert(0, "0");

            return dirCodeStr;
        }

        string ConvertToBackCode(string binNum, bool flag)
        {
            StringBuilder sb = new StringBuilder(binNum);
            if (!flag)
            {
                for (int i = 1; i < sb.Length; i++)
                {
                    if (sb[i] == '0') sb[i] = '1';
                    else if (sb[i] == '1') sb[i] = '0';
                }
            }
            return sb.ToString();
        }

        string SumFromBackCode(string binNum1, string binNum2)
        {
            StringBuilder sb1 = new StringBuilder(binNum1);
            if (binNum1.Contains('.')) sb1 = sb1.Remove(32, 1);
            StringBuilder sb2 = new StringBuilder(binNum2);
            if (binNum2.Contains('.')) sb2 = sb2.Remove(32, 1);
            string str = "00000000000000000000000000000000000000000";
            StringBuilder sbstr = new StringBuilder(str);

            for (int i = 39; i > -1; i--)
            {
                sbstr[i + 1] += Convert.ToChar(Convert.ToInt32(sb1[i]) + Convert.ToInt32(sb2[i]) - 96);

                if (sbstr[i + 1] == '2')
                {

                    sbstr[i + 1] = '0';

                    sbstr[i] = '1';
                }

                if (sbstr[i + 1] == '3')
                {
                    sbstr[i + 1] = '1';

                    sbstr[i] = '1';
                }

            }

            string one = "00000000000000000000000000000000000000001";
            string str1 = "000000000000000000000000000000000000000000";
            StringBuilder sbone = new StringBuilder(one);
            StringBuilder sbstr1 = new StringBuilder(str1);

            if (sbstr[0] == '1')
            {
                for (int i = 40; i > -1; i--)
                {

                    sbstr1[i + 1] += Convert.ToChar(Convert.ToInt32(sbstr[i]) + Convert.ToInt32(sbone[i]) - 96);

                    if (sbstr1[i + 1] == '2')
                    {

                        sbstr1[i + 1] = '0';

                        sbstr1[i] = '1';
                    }

                    if (sbstr1[i + 1] == '3')
                    {

                        sbstr1[i + 1] = '1';

                        sbstr1[i] = '1';
                    }

                }

            }

            else
            {
                for (int i = 0; i < 41; i++)
                {
                    sbstr1[i + 1] = sbstr[i];
                }

            }

            if (sbstr1[2] == '0')
            {
                return sbstr1.ToString().Remove(0, 2).Insert(32, ".");
            }

            else
            {

                for (int i = 3; i < 42; i++)
                {

                    if (sbstr1[i] == '0') sbstr1[i] = '1';

                    else sbstr1[i] = '0';
                }

                return sbstr1.ToString().Remove(0, 2).Insert(32, ".");
            }

        }

        string NegativeNum(string str)
        {
            StringBuilder sb = new StringBuilder(str);

            for (int i = 0; i < str.Length; i++)
            {
                if (str[i] == '1') sb[i] = '0';
                if (str[i] == '0') sb[i] = '1';
            }

            return sb.ToString();
        }

        string Difference(string backCodeA, string backCodeB)
        {
            string difference = SumFromBackCode(backCodeA, NegativeNum(backCodeB));
            return difference;
        }

        string sdvig(string str, int k)
        {

            StringBuilder sb = new StringBuilder(str);

            for (int i = k; i < 40; i++)
            {

                sb[i - k] = sb[i];

            }

            for (int i = 40 - k; i < 40; i++)
            {

                sb[i] = '0';

            }

            return sb.ToString();
        }

        string Mul(string first, string second)
        {
            string ans = "0000000000000000000000000000000000000000";
            bool sign = true;

            StringBuilder sbfirst = new StringBuilder(first);
            sbfirst = sbfirst.Remove(32, 1);
            StringBuilder sbsecond = new StringBuilder(second);
            sbsecond = sbsecond.Remove(32, 1);


            if ((sbfirst[0] == '1' && sbsecond[0] == '0') || (sbfirst[0] == '0' && sbsecond[0] == '1'))
            {
                sign = false;

            }

            sbfirst[0] = '0';
            sbsecond[0] = '0';

            first = sbfirst.ToString();

            for (int i = 39; i > -1; i--)
            {
                if (sbsecond[i] == '1')
                {
                    int j = 39 - i;
                    string temp = sdvig(first, j);
                    ans = SumFromBackCode(ans, temp);

                }
            }

            StringBuilder sb = new StringBuilder(ans);
            if (!sign) sb[0] = '1';
            ans = sb.ToString();
            ans = ans.Remove(32, 8).Insert(24, ".").Insert(1, "0").Insert(1, "0").Insert(1, "0").Insert(1, "0").Insert(1, "0").Insert(1, "0").Insert(1, "0").Insert(1, "0");



            return ans;
        }

        string Div(string first, string second)
        {
            bool sign = true;

            first = Mul(first, "00000000000000000000001111101000.00000000");
            StringBuilder sbfirst = new StringBuilder(first);
            StringBuilder sbsecond = new StringBuilder(second);


            if ((first[0] == '1' && second[0] == '0') || (first[0] == '0' && second[0] == '1'))
            {
                sign = false;

            }

            sbfirst[0] = '0';
            sbsecond[0] = '0';
            first = sbfirst.ToString();
            second = sbsecond.ToString();


            string ans = "00000000000000000000000000000000.00000000";
            string temp = first;

            while (temp[0] == '0' && (Difference(temp, second)[0] == '0' || Difference(temp, second) == "10000000000000000000000000000000.00000000"))
            {
                temp = Difference(temp, second);
                ans = SumFromBackCode(ans, "00000000000000000000000000000001.00000000");

            }
            StringBuilder sb = new StringBuilder(ans);
            if (!sign) sb[0] = '1';

            ans = sb.ToString();
            ans.Insert(32, ".");
            double ansByThous = 0;
            ansByThous = FromBackToTen(ans) / 1000;
            ans = FractionalNum(ansByThous);
            ans = ConvertToDirectСode(ans, sign);

            return ans;

        }

        double FromBackToTen(string str)
        {
            bool flag = true;

            double result = 0;


            if (str != "00000000000000000000000000000000" && str != "10000000000000000000000000000000")
            {

                if (str[0] == '1')
                {
                    flag = false;
                    str = str.Remove(0, 1);
                }

                while (str[0] == '0')
                {
                    str = str.Remove(0, 1);
                }

                int l = 0;

                while (str[l] != '.')
                {
                    l++;
                }

                l -= 1;

                for (var i = 0; i < str.Length; i++)
                {
                    if (str[i] == '1')
                        result += Convert.ToDouble(Math.Pow(2, l));

                    if (str[i] != '.')
                        l--;
                }

                if (!flag) result = result * (-1);
            }

            else result = 0;
            return result;

        }


        string FractionalNum(double num)
        {
            int intNum = (int)num;
            double afterPointNum = 0;
            bool flag = false;
            if (num > 0)
            {
                afterPointNum = num - intNum;
                flag = true;
            }
            else afterPointNum = intNum - num;

            string doubIntNum = ConvertToDoubleSystem(intNum, flag); ;
            doubIntNum += '.';

            for (int i = 0; i < 8; i++)
            {
                afterPointNum *= 2;
                if (afterPointNum < 1) doubIntNum += '0';

                else
                {
                    doubIntNum += '1';
                    afterPointNum -= 1;
                }

            }

            return doubIntNum;
        }


        Console.WriteLine("Введите 2 числа");

        double a = Convert.ToDouble(Console.ReadLine());
        double b = Convert.ToDouble(Console.ReadLine());
        bool flagA = true;
        bool flagB = true;

        if (a < 0) flagA = false;
        if (b < 0) flagB = false;

        string doubSysA = FractionalNum(a);
        string doubSysB = FractionalNum(b);

        Console.WriteLine("Числа в двоичном коде:");

        Console.WriteLine(doubSysA);
        Console.WriteLine(doubSysB);

        Console.WriteLine("");

        Console.WriteLine("Числа в прямом коде:");

        string dirCodeA = ConvertToDirectСode(doubSysA, flagA);
        string dirCodeB = ConvertToDirectСode(doubSysB, flagB);

        Console.Write(" ");
        Console.WriteLine(dirCodeA);
        Console.Write(" ");
        Console.WriteLine(dirCodeB);


        Console.WriteLine("");
        Console.WriteLine("Числа в обратном коде:");

        string backCodeA = ConvertToBackCode(dirCodeA, flagA);
        string backCodeB = ConvertToBackCode(dirCodeB, flagB);

        Console.Write(" ");
        Console.WriteLine(backCodeA);
        Console.Write(" ");
        Console.WriteLine(backCodeB);

        Console.WriteLine("");
        Console.WriteLine("Сумма чисел c помощью обратного кода:");


        string sum = SumFromBackCode(backCodeA, backCodeB);

        Console.Write(" ");
        Console.WriteLine(sum);

        Console.WriteLine("Эта же сумма в десятичном предcтвлении:");

        double sumInTen = FromBackToTen(sum);
        Console.Write(" ");
        Console.WriteLine(sumInTen);

        Console.WriteLine("Разность первого и второго числа");

        string difference = Difference(backCodeA, backCodeB);

        Console.Write(" ");
        Console.WriteLine(difference);

        Console.WriteLine("Эта же разность в десятичном предcтвлении:");
        double diffInTen = FromBackToTen(difference);
        Console.Write(" ");
        Console.WriteLine(diffInTen);

        Console.WriteLine("Произведение первого и второго числа");
        string mul = Mul(dirCodeA, dirCodeB);
        Console.Write(" ");
        Console.WriteLine(mul);

        Console.WriteLine("Это же произведение в десятичном предcтвлении:");
        double mulInTen = FromBackToTen(mul);
        Console.Write(" ");
        Console.WriteLine(mulInTen);

        Console.WriteLine("Частное первого на второе число");
        string div = Div(dirCodeA, dirCodeB);
        Console.Write(" ");
        Console.WriteLine(div);
        Console.WriteLine("Это же Частное в десятичном предcтвлении:");
        Console.Write(" ");

        double divInTen = FromBackToTen(div);
        Console.WriteLine(divInTen);
    }
}