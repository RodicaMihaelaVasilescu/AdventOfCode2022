using System.Reflection;

namespace AdventOfCode
{
  public class Node
  {
    public string Name;
    public bool IsDirectory;
    public bool IsRoot = false;
    public Int64 Size = 0;
    public Node Parent = null;
    public List<Node> Nodes = new List<Node>();

    public string Id { get; internal set; }

    public Int64 GetSize()
    {
      Int64 sum = 0;
      foreach (Node n in Nodes)
      {
        sum += n.GetSize();
      }
      return Size + sum;
    }
  }

  public class Program
  {
    public static string inputFile = "../../../in.txt";
    public static string outputFile = "../../../out.txt";

    public static List<string> split(string line, string delimiters = ",/;= ")
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

    public static void DFS(Node root)
    {
      if (Directories.ContainsKey(root.Id))
      {
        var size = root.GetSize();
        Directories[root.Id] = size;
      }

      foreach (var item in root.Nodes)
      {
        if (item.IsDirectory)
        {
          DFS(item);
        }
      }
    }

    public static Dictionary<string, Int64> Directories = new Dictionary<string, Int64>();
    static void Main(string[] args)
    {
      List<List<string>> input = new List<List<string>>();
      StreamWriter file = new StreamWriter(outputFile);
      Node root = new Node();
      Node current = new Node();

      string currentCommand = string.Empty;
      int index = 0;
      using (StreamReader stream = new StreamReader("../../../in.txt"))
      {
        string line;
        while ((line = stream.ReadLine()) != null)
        {
          index++;
          var words = split(line);
          if (line == "$ cd /")
          {
            currentCommand = "$ cd /";
            root.Name = "/";
            root.Id = "/";
            current = root;
            Directories.Add(root.Id, 0);

          }
          else if (line == "$ ls")
          {
            currentCommand = "$ ls";
          }
          else if (line.StartsWith("dir"))
          {
            var newNode = new Node { Id = words[1] + index.ToString(), Parent = current, IsDirectory = true, Name = words[1] };
            current.Nodes.Add(newNode);
            Directories.Add(newNode.Id, 0);
          }
          else if (char.IsDigit(line[0]))
          {
            current.Nodes.Add(new Node { Parent = current, IsDirectory = false, Name = words[1], Size = Convert.ToInt64(words[0]) });
          }
          else if (line.StartsWith("$ cd"))
          {
            if (words[2] == "..")
            {
              current = current.Parent;
            }
            else
            {
              current = current.Nodes.First(_ => _.Name == words[2]);
            }
          }
        }
      }

      DFS(root);

      file.WriteLine($"Part 1: {Directories.Where(_ => _.Value <= 100000).Select(x => x.Value).Sum()}");

      var items = Directories.OrderBy(_ => _.Value);
      Int64 unused = 70000000 - root.GetSize();

      foreach (var item in items)
      {
        if (unused + item.Value >= 30000000)
        {
          file.WriteLine($"Part 2: {item.Value}");
          break;
        }

      }
      file.Close();

    }
  }
}