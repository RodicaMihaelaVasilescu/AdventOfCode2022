
namespace AdventOfCode
{
  public class Node
  {
    public int? Value;
    public Node Parent;
    public List<Node> Children = new List<Node>();
    public string Name;
  }

  public class Program
  {
    public static string inputFile = "../../../in.txt";
    public static string outputFile = "../../../out.txt";

    static int Main(string[] args)
    {
      List<Node> allPackets = new List<Node>();
      int sumPart1 = 0, index = 0;

      using (StreamReader stream = new StreamReader("../../../in.txt"))
      {
        string line;
        List<string> words = new List<string>();
        while ((line = stream.ReadLine()) != null)
        {
          index++;

          var tree1 = GetTree(line);
          allPackets.Add(tree1);

          string line2 = stream.ReadLine();
          var tree2 = GetTree(line2);
          allPackets.Add(tree2);

          var isInRightOrder = IsInRightOrder(tree1, tree2);
          if (isInRightOrder != null && isInRightOrder.Value == true)
          {
            sumPart1 += index;
          }

          line = stream.ReadLine(); // read empty line
        }

        StreamWriter file = new StreamWriter(outputFile);
        file.WriteLine($"Part 1: {sumPart1} ");

        //part 2
        allPackets.Add(GetTree("[[2]]"));
        allPackets.Add(GetTree("[[6]]"));

        for (int i = 0; i < allPackets.Count(); i++)
        {
          for (int j = i + 1; j < allPackets.Count(); j++)
          {
            bool? val = IsInRightOrder(allPackets[i], allPackets[j]);
            if (val.HasValue && val == false)
            {
              var aux = allPackets[i];
              allPackets[i] = allPackets[j];
              allPackets[j] = aux;
            }
          }
        }

        int index1 = allPackets.IndexOf(allPackets.First(_ => _.Name == "[[2]]")) + 1;
        int index2 = allPackets.IndexOf(allPackets.First(_ => _.Name == "[[6]]")) + 1;

        file.WriteLine($"Part 2: {index1 * index2}");
        file.Close();
        return 0;
      }
    }


    private static bool? IsInRightOrder(Node i1, Node i2)
    {
      // If both values are lists, compare the first value of each list, then the second value, and so on
      if (i1.Value == null && i2.Value == null)
      {
        for (int i = 0; i < Math.Min(i1.Children.Count(), i2.Children.Count()); i++)
        {
          bool? val = IsInRightOrder(i1.Children[i], i2.Children[i]);
          if (val.HasValue && val.Value == true)
          {
            return true;
          }
          else if (val.HasValue && val.Value == false)
          {
            return false;
          }
        }
        if (i1.Children.Count() < i2.Children.Count())
        {
          return true;
        }
        else if (i1.Children.Count() > i2.Children.Count())
        {
          return false;
        }
        else
        {
          return null;
        }
      }
      // If both values are integers, the lower integer should come first
      else if (i1.Value != null && i2.Value != null)
      {
        if (i1.Value < i2.Value)
        {
          return true;
        }
        else if (i1.Value > i2.Value)
        {
          return false;
        }
        else
        {
          return null;
        }
      }
      // If exactly one value is an integer,
      // convert the integer to a list which contains that integer as its only value
      else if (i1.Value != null)
      {
        var node = new Node { Value = i1.Value.Value, Parent = i1 };
        i1.Value = null;
        i1.Children.Add(node);
        return IsInRightOrder(i1, i2);
      }
      else if (i2.Value != null)
      {
        var node = new Node { Value = (int)i2.Value, Parent = i2.Parent };
        i2.Children.Add(node);
        i2.Value = null;
        return IsInRightOrder(i1, i2);
      }
      return null;
    }

    private static Node GetTree(string s)
    {
      var root = new Node();
      root.Name = s;
      s = s.Substring(1, s.Count() - 2);
      var node = root;
      for (int i = 0; i < s.Count();)
      {
        while (s[i] == '[')
        {
          i++;
          var children = new Node();
          children.Parent = node;
          node.Children.Add(children);
          node = children;
        }
        string n = String.Empty;
        if (i < s.Count() && (Char.IsDigit(s[i])))
        {
          while (i < s.Count() && Char.IsDigit(s[i]))
          {
            n += s[i];
            i++;
            if (i < s.Count() && s[i] == ',')
            {
              node.Children.Add(new Node { Value = Convert.ToInt32(n), Parent = node });
              n = String.Empty;
              i++;
            }
          }
          if (!string.IsNullOrEmpty(n))
          {
            node.Children.Add(new Node { Value = Convert.ToInt32(n), Parent = node });
          }
        }

        while (i < s.Count() && s[i] == ']')
        {
          node = node.Parent;
          i++;
        }

        if (i < s.Count() && s[i] == ',')
        {
          i++;
        }
      }
      return root;
    }
  }
}