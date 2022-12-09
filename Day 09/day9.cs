namespace AdventOfCode
{
  public class Point
  {
    public int x;
    public int y;

    public Point(Point point)
    {
      this.x = point.x;
      this.y = point.y;
    }

    public Point(int x = 0, int y = 0)
    {
      this.x = x;
      this.y = y;
    }
  }

  public class Program
  {
    public static string inputFile = "../../../in.txt";
    public static string outputFile = "../../../out.txt";

    static bool IsAdjacent(Point h, Point t)
    {
      return Math.Abs(h.x - t.x) <= 1 && Math.Abs(h.y - t.y) <= 1;
    }

    private static Point MoveTail(Point head, Point tail)
    {
      var newTail = new Point(tail);
      if (head.x == tail.x) // up/down
      {
        if (head.y > tail.y)
        {
          newTail.y++;
        }
        else if (head.y < tail.y)
        {
          newTail.y--;
        }
      }
      else if (head.y == tail.y) // right/left
      {
        if (head.x > tail.x)
        {
          newTail.x++;
        }
        else if (head.x < tail.x)
        {
          newTail.x--;
        }
      }
      else if (head.x < tail.x && head.y < tail.y)
      {
        newTail.x--;
        newTail.y--;
      }
      else if (head.x > tail.x && head.y > tail.y)
      {
        newTail.x++;
        newTail.y++;
      }
      else if (head.x < tail.x && head.y > tail.y)
      {
        newTail.x--;
        newTail.y++;
      }
      else if (head.x > tail.x && head.y < tail.y)
      {
        newTail.x++;
        newTail.y--;
      }
      return newTail;
    }

    static void Main(string[] args)
    {
      int n = 10;
      List<Point> t = new List<Point>();
      for (int i = 0; i < n; i++)
      {
        t.Add(new Point());
      }
      var visitedPart1 = new HashSet<(int, int)>();
      var visitedPart2 = new HashSet<(int, int)>();

      using (StreamReader stream = new StreamReader("../../../in.txt"))
      {
        string line;
        while ((line = stream.ReadLine()) != null)
        {
          char direction = line[0];
          int distance = int.Parse(line.Substring(1));

          Point offset = new Point();
          if (direction == 'R')
          {
            offset = new Point(0, 1);
          }
          else if (direction == 'L')
          {
            offset = new Point(0, -1);
          }
          else if (direction == 'U')
          {
            offset = new Point(-1, 0);
          }
          else if (direction == 'D')
          {
            offset = new Point(1, 0);
          }

          while (distance-- > 0)
          {
            t[0].x += offset.x;
            t[0].y += offset.y;
            for (int i = 1; i < n; i++)
            {
              if (!IsAdjacent(t[i], t[i - 1]))
              {
                t[i] = MoveTail(t[i - 1], t[i]);
              }
            }
            visitedPart1.Add((t[1].x, t[1].y));
            visitedPart2.Add((t[9].x, t[9].y));
          }
        }
      }

      StreamWriter file = new StreamWriter(outputFile);
      file.WriteLine($"Part 1: {visitedPart1.Count()}");
      file.WriteLine($"Part 2: {visitedPart2.Count()}");
      file.Close();
    }
  }
}