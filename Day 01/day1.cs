namespace AdventOfCode
{
  public class Program
  {
    static void Main(string[] args)
    {
      bool isPreviousLineEmpty = false;
      string line = string.Empty;
      List<int> numbers = new List<int>();
      int sum = 0;

      Console.WriteLine("Press enter three times after entering the input:");

      do
      {
        isPreviousLineEmpty = string.IsNullOrEmpty(line);
        line = Console.ReadLine();

        if (string.IsNullOrEmpty(line))
        {
          numbers.Add(sum);
          sum = 0;
        }
        else
        {
          sum += int.Parse(line);
        }
      }
      // read until two consecutive lines are empty
      while (!isPreviousLineEmpty || !string.IsNullOrEmpty(line));

      // the Elf carrying the most Calories
      Console.WriteLine($"Part 1: {numbers.Max()}");
      // the top three Elves carrying the most Calories
      Console.WriteLine($"Part 2: {numbers.OrderByDescending(_ => _).Take(3).Sum()}");
    }
  }
}