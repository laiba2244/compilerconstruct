using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace Question3
{
    internal class Program

    {
        private static readonly Random random = new Random();

        public static string GeneratePassword(string firstName, string lastName, string registrationNumbers)
        {
            string initials = firstName.Substring(0, 1).ToUpper() + lastName.Substring(0, 1).ToUpper();
            string oddLettersFirstName = GetOddLetters(firstName);
            string evenLettersLastName = GetEvenLetters(lastName);

            string specialCharacters = "!@#$%^&*()-_+=";
            string numbers = GetNumbers(registrationNumbers);

            string password = initials + oddLettersFirstName + evenLettersLastName + numbers + GenerateRandomCharacters(specialCharacters, 2);

            
            password = password.Substring(0, Math.Min(password.Length, 16));

            return ShuffleString(password);
        }

        private static string GetOddLetters(string str)
        {
            string result = "";
            for (int i = 0; i < str.Length; i++)
            {
                if (i % 2 == 0)
                {
                    result += str[i];
                }
            }
            return result;
        }

        private static string GetEvenLetters(string str)
        {
            string result = "";
            for (int i = 1; i < str.Length; i += 2)
            {
                result += str[i];
            }
            return result;
        }

        private static string GetNumbers(string registrationNumbers)
        {
            string result = "";
            Regex regex = new Regex("[0-9]+");
            MatchCollection matches = regex.Matches(registrationNumbers);
            foreach (Match match in matches)
            {
                result += match.Value;
            }
            if (result.Length < 4)
            {
                throw new ArgumentException("Registration numbers must contain at least 4 numbers");
            }
            return result.Substring(0, 4);
        }

        private static string GenerateRandomCharacters(string characters, int count)
        {
            string result = "";
            for (int i = 0; i < count; i++)
            {
                result += characters[random.Next(characters.Length)];
            }
            return result;
        }

        private static string ShuffleString(string str)
        {
            char[] array = str.ToCharArray();
            int n = array.Length;
            while (n > 1)
            {
                n--;
                int k = random.Next(n + 1);
                char value = array[k];
                array[k] = array[n];
                array[n] = value;
            }
            return new string(array);
        }

        static void Main(string[] args)
        {
            Console.Write("Enter your first name: ");
            string firstName = Console.ReadLine();

            Console.Write("Enter your last name: ");
            string lastName = Console.ReadLine();

            Console.Write("Enter your registration numbers: ");
            string registrationNumbers = Console.ReadLine();

            try
            {
                string password = GeneratePassword(firstName, lastName, registrationNumbers);
                Console.WriteLine("Generated Password: " + password);
            }
            catch (ArgumentException e)
            {
                Console.WriteLine("Error: " + e.Message);
            }
        }
}
}