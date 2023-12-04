using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

public class Program
{
    public static void Main(string[] args)
    {
        var graph = new Graph();
        var stopwatch = new Stopwatch();

        ReadGraphFromFile(graph, out var start, out var goal);
        AddNeighborsToGraph(graph);

        Console.WriteLine("--------A*--------");
        stopwatch.Start();
        var path = Graph.AStar(start, goal);
        stopwatch.Stop();
        Console.WriteLine($"A* took {stopwatch.ElapsedTicks} ticks");

        Console.WriteLine("--------Depth first traversal--------");

        stopwatch.Restart();
        Graph.DepthFirstTraversal(start, goal, new HashSet<Node>());
        stopwatch.Stop();
        Console.WriteLine($"Depth first traversal took {stopwatch.ElapsedTicks} ticks");

        Console.WriteLine("--------Breadth first traversal--------");
        
        stopwatch.Restart();
        Graph.BreadthFirstTraversal(start, goal);
        stopwatch.Stop();
        Console.WriteLine($"Breadth first traversal took {stopwatch.ElapsedTicks} ticks");
    }

    private static void AddNeighborsToGraph(Graph graph)
    {
        foreach (var node in graph.Nodes)
        {
            var x = node.GetPosition().X;
            var y = node.GetPosition().Y;

            var tempNeighbors = new List<Node>();

            foreach (var otherNode in graph.Nodes)
            {
                var nx = otherNode.GetPosition().X;
                var ny = otherNode.GetPosition().Y;

                if ((nx == x - 1 && ny == y) || (nx == x + 1 && ny == y) || (nx == x && ny == y - 1) ||
                    (nx == x && ny == y + 1))
                {
                    tempNeighbors.Add(otherNode);
                }
            }

            foreach (var neighbor in tempNeighbors)
            {
                node.AddNeighbour(neighbor);
            }
        }
    }

    private static void ReadGraphFromFile(Graph graph, out Node start, out Node goal)
    {
        var lines = File.ReadAllLines("AssignmentNodes.txt");

        start = null;
        goal = null;
        var x = 0;
        var y = 0;

        foreach (var line in lines)
        {
            foreach (var ch in line)
            {
                switch (ch)
                {
                    case 'S':
                    {
                        var node = new Node(y * 20 + x, new Vec2(x, y));
                        graph.Nodes.Add(node);
                        start = node;
                        ++x;
                        break;
                    }
                    case 'G':
                    {
                        var node = new Node(y * 20 + x, new Vec2(x, y));
                        graph.Nodes.Add(node);
                        goal = node;
                        ++x;
                        break;
                    }
                    case 'X':
                        ++x;
                        break;
                    case 'o':
                    {
                        var node = new Node(y * 20 + x, new Vec2(x, y));
                        graph.Nodes.Add(node);
                        ++x;
                        break;
                    }
                }
            }

            ++y;
            x = 0;
        }
    }
}

public class Graph
{
    public readonly List<Node> Nodes = new List<Node>();

    public static IEnumerable<Node> AStar(Node start, Node goal)
    {
        var openSet = new HashSet<Node>();
        var cameFrom = new Dictionary<Node, Node>();
        var gScore = new Dictionary<Node, int>();
        var fScore = new Dictionary<Node, int>();


        openSet.Add(start);

        gScore[start] = 0;
        fScore[start] = Heuristic(start, goal);

        while (openSet.Count != 0)
        {
            var current = openSet.OrderBy(x => fScore[x]).First();

            if (current == goal)
            {
                return ReconstructPath(current, cameFrom);
            }

            openSet.Remove(current);
            foreach (var neighbour in current.GetNeighbours())
            {
                var tentativeGScore = gScore[current] + Distance(current, neighbour);

                if (gScore.ContainsKey(neighbour) && tentativeGScore >= gScore[neighbour]) continue;
                cameFrom[neighbour] = current;
                gScore[neighbour] = tentativeGScore;
                fScore[neighbour] = gScore[neighbour] + Heuristic(neighbour, goal);

                openSet.Add(neighbour);
            }
        }

        return null;
    }

    private static int Heuristic(Node from, Node goal)
    {
        return Math.Abs(from.GetPosition().X - goal.GetPosition().X) +
               Math.Abs(from.GetPosition().Y - goal.GetPosition().Y);
    }

    private static IEnumerable<Node> ReconstructPath(Node current, Dictionary<Node, Node> cameFrom)
    {
        var path = new List<Node> { current };
        while (cameFrom.ContainsKey(current))
        {
            current = cameFrom[current];
            path.Add(current);
        }

        path.Reverse();
        return path;
    }

    private static int Distance(Node from, Node to)
    {
        return (int)Math.Round(Math.Sqrt(Math.Pow(from.GetPosition().X - to.GetPosition().X, 2) +
                                         Math.Pow(from.GetPosition().Y - to.GetPosition().Y, 2)));
    }

    public static void DepthFirstTraversal(Node startNode, Node goalNode, HashSet<Node> visitedNodes)
    {
        //Console.WriteLine($"Visiting node {startNode.GetId()}");
        visitedNodes.Add(startNode);

        if (startNode == goalNode)
        {
            //Console.WriteLine("Found goal node");
            return;
        }

        foreach (var neighbor in startNode.GetNeighbours().Where(neighbor => !visitedNodes.Contains(neighbor)))
        {
            DepthFirstTraversal(neighbor, goalNode, visitedNodes);

            if (visitedNodes.Contains(goalNode))
                return;
        }
    }

    public static void BreadthFirstTraversal(Node startNode, Node goalNode)
    {
        var queue = new Queue<Node>();
        var visitedNodes = new HashSet<Node>();
        if (visitedNodes == null) throw new ArgumentNullException(nameof(visitedNodes));

        queue.Enqueue(startNode);
        visitedNodes.Add(startNode);
        while (queue.Count != 0)
        { 
            var current = queue.Dequeue();
            //Console.WriteLine($"Visiting node {current.GetId()}");
            if (current == goalNode)
            {
                //Console.WriteLine("Found goal node");
                return;
            }

            foreach (var neighbour in current.GetNeighbours().Where(neighbour => !visitedNodes.Contains(neighbour)))
            {
                queue.Enqueue(neighbour);
                visitedNodes.Add(neighbour);
            }
        }
    }
}

public struct Vec2
{
    public Vec2(int x, int y)
    {
        this.X = x;
        this.Y = y;
    }

    public readonly int X;
    public readonly int Y;
}

public class Node
{
    public Node(int id, Vec2 position)
    {
        _position = position;
        _id = id;
        _neighbours = new List<Node>();
    }

    private readonly Vec2 _position;
    private readonly int _id;
    private readonly List<Node> _neighbours;

    public Vec2 GetPosition()
    {
        return _position;
    }

    public int GetId()
    {
        return _id;
    }

    public List<Node> GetNeighbours()
    {
        return _neighbours;
    }

    public void AddNeighbour(Node node)
    {
        _neighbours.Add(node);
        node.GetNeighbours().Add(this);
    }
}