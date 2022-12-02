using System.Reflection;

namespace AdventOfCode
{
  public class Program
  {
    public static string inputFile = "../../../in.txt";
    public static string outputFile = "../../../out.txt";

    public static List<string> split(string line, string delimiters = ",./;= ")
    {
      List<string> words = new List<string>();
      if (string.IsNullOrEmpty(line))
      {
        return words;
      }

      string[] split = line.Split(delimiters.ToCharArray(), StringSplitOptions.RemoveEmptyEntries);
      return split.ToList();
    }

    static void Main(string[] args)
    {
      int part1 = 0, part2 = 0;
      using (StreamReader stream = new StreamReader(inputFile))
      {
        string line;
        while ((line = stream.ReadLine()) != null)
        {
          var words = split(line);
          var a = words.First();
          var b = words.Last();
          if (a == "A") // Rock
          {
            if (b == "X")
            {
              part1 += 1; part1 += 3; // Rock
              part2 += 3; part2 += 0; //Scissors
            }
            else if (b == "Y")
            {
              part1 += 2; part1 += 6; // Paper
              part2 += 1; part2 += 3; // Rock
            }
            else if (b == "Z")
            {
              part1 += 3; part1 += 0; //Scissors
              part2 += 2; part2 += 6; // Paper
            }
          }
          else if (a == "B") // Paper
          {
            if (b == "X")
            {
              part1 += 1; part1 += 0; // Rock
              part2 += 1; part2 += 0; // Rock
            }
            else if (b == "Y")
            {
              part1 += 2; part1 += 3; // Paper
              part2 += 2; part2 += 3; // Paper
            }
            else if (b == "Z")
            {
              part1 += 3; part1 += 6; // Scissors
              part2 += 3; part2 += 6; // Scissors
            }
          }
          else if (a == "C") // Scissors
          {
            if (b == "X")
            {
              part1 += 1; part1 += 6; // Rock
              part2 += 2; part2 += 0; // Paper
            }
            else if (b == "Y")
            {
              part1 += 2; part1 += 0; // Paper
              part2 += 3; part2 += 3; // Scissors
            }
            else if (b == "Z")
            {
              part1 += 3; part1 += 3; // Scissors
              part2 += 1; part2 += 6; // Rock
            }
          }
        }
      }

      StreamWriter file = new StreamWriter(outputFile);
      file.WriteLine($"Part 1: {part1}");
      file.WriteLine($"Part 2: {part2}");
      file.Close();
    }
  }
}