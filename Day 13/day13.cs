
namespace AdventOfCode
{
  public class Node
  {
    public int? Number;
    public Node Parent;
    public List<Node> Children = new List<Node>();
    public string Name { get; set; }
    public Node()
    {

    }
    public Node(int n, Node parent)
    {
      Number = n;
      Parent = parent;
    }
  }

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

    public static List<int> split2(string line, string delimiters = ",./;= ")
    {
      List<int> ints = new List<int>();
      string[] split = line.Split(delimiters.ToCharArray(), StringSplitOptions.RemoveEmptyEntries);
      foreach (var word in split.ToList())
      {
        ints.Add(int.Parse(word));
      }
      return ints;
    }

    public class Pair
    {
      public Node First;
      public Node Second;

      public Pair(Node node1, Node node2)
      {
        First = node1;
        Second = node2;
      }
      public Pair()
      {

      }
    }

    static int Main(string[] args)
    {
      List<Pair> pairs = new List<Pair>();
      List<Node> nodesPart2 = new List<Node>();

      using (StreamReader stream = new StreamReader("../../../in.txt"))
      {
        string line;
        List<string> words = new List<string>();
        while ((line = stream.ReadLine()) != null)
        {
          string line2 = stream.ReadLine();
          var pair = new Pair();
          pair.First = GetTree(line);
          pair.Second = GetTree(line2);
          pairs.Add(pair);

          nodesPart2.Add(pair.First);
          nodesPart2.Add(pair.Second);
          line = stream.ReadLine();
        }


        int sumPart1 = 0;
        for (int i = 0; i < pairs.Count(); i++)
        {
          var isInRightOrder = IsInRightOrder(pairs[i].First, pairs[i].Second);
          if (isInRightOrder != null && isInRightOrder.Value == true)
          {
            sumPart1 += i + 1;
          }
        }
        StreamWriter file = new StreamWriter(outputFile);
        file.WriteLine($"Part 1: {sumPart1} ");


        //part 2
        nodesPart2.Add(GetTree("[[2]]"));
        nodesPart2.Add(GetTree("[[6]]"));

        for (int i = 0; i < nodesPart2.Count(); i++)
        {
          for (int j = i + 1; j < nodesPart2.Count(); j++)
          {
            bool? val = IsInRightOrder(nodesPart2[i], nodesPart2[j]);
            if (val.HasValue && val == false)
            {
              var aux = nodesPart2[i];
              nodesPart2[i] = nodesPart2[j];
              nodesPart2[j] = aux;
            }
          }
        }

        int index1 = 0;
        int index2 = 0;

        for (int i = 0; i < nodesPart2.Count(); i++)
        {
          if (nodesPart2[i].Name == "[[2]]")
          {
            index1 = i+1;
          }
          if (nodesPart2[i].Name == "[[6]]")
          {
            index2 = i+1;
          }
        }

        file.WriteLine($"Part 2: {index1 * index2} ");
        file.Close();
        return 0;
      }
    }

    private static bool IsAscending(List<int> i1, List<int> i2)
    {
      for (int i = 0; i < Math.Min(i1.Count(), i2.Count()); i++)
      {
        if (i1[i] < i2[i])
        {
          return true;
        }
        if (i1[i] > i2[i])
        {
          return false;
        }
      }
      return i1.Count() < i2.Count();
    }


    private static bool? IsInRightOrder(Node i1, Node i2)
    {
      // compare lists
      if (i1.Number == null && i2.Number == null)
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
      else if (i1.Number != null && i2.Number != null)
      {
        if (i1.Number < i2.Number)
        {
          return true;
        }
        else if (i1.Number > i2.Number)
        {
          return false;
        }
        else
        {
          return null;
        }
      }
      else if (i1.Number != null)
      {
        var node = new Node((int)i1.Number, i1);
        i1.Number = null;
        i1.Children.Add(node);
        return IsInRightOrder(i1, i2);
      }
      else if (i2.Number != null)
      {
        var node = new Node((int)i2.Number, i2.Parent);
        i2.Children.Add(node);
        i2.Number = null;
        return IsInRightOrder(i1, i2);
      }
      return null;
    }

    private static Node GetTree(string s)
    {
      if (s == "[1,1,3,1,1]")
      {
        int bkp = 0;
      }
      var root = new Node();
      root.Name = s;
      s = s.Substring(1, s.Count() - 2);
      var node = root;
      for (int i = 0; i < s.Count();)
      {
        char ch = s[i];
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
          ch = s[i];
          while (i < s.Count() && Char.IsDigit(s[i]))
          {
            n += s[i];
            i++;
            if (i < s.Count() && s[i] == ',')
            {
              node.Children.Add(new Node(Convert.ToInt32(n), node));
              n = String.Empty;
              i++;
            }
          }
          if (!string.IsNullOrEmpty(n))
          {
            node.Children.Add(new Node(Convert.ToInt32(n), node));
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