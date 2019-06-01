using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.IO;
using RubiksCube;

namespace CubeSolver {
    class Program {
        static private Cube cube;
        static private Cube[] randSolver;
        static private Random random;
        static private readonly Cube.Positions[] original = new Cube().GetPositions();

        static bool solved = false;

        /// <summary>
        /// Prints the cube to the console
        /// </summary>
        /// <param name="cube">Cube to print</param>
        static private void PrintCube(Cube cube) {
            string[] cubeString = cube.GetCubeDisplay();

            string breakLine = "        +-+-+-+";

            Console.WriteLine(breakLine);
            Console.WriteLine("        |" + cubeString[0].ElementAt(0) + "|" + cubeString[0].ElementAt(1) + "|" + cubeString[0].ElementAt(2) + "|");
            Console.WriteLine(breakLine);
            Console.WriteLine("        |" + cubeString[0].ElementAt(3) + "|" + cubeString[0].ElementAt(4) + "|" + cubeString[0].ElementAt(5) + "|");
            Console.WriteLine(breakLine);
            Console.WriteLine("        |" + cubeString[0].ElementAt(6) + "|" + cubeString[0].ElementAt(7) + "|" + cubeString[0].ElementAt(8) + "|");
            Console.WriteLine(breakLine);
            Console.WriteLine("+-+-+-+ +-+-+-+ +-+-+-+");
            Console.Write("|" + cubeString[2].ElementAt(0) + "|" + cubeString[2].ElementAt(1) + "|" + cubeString[2].ElementAt(2) + "| ");
            Console.Write("|" + cubeString[1].ElementAt(0) + "|" + cubeString[1].ElementAt(1) + "|" + cubeString[1].ElementAt(2) + "| ");
            Console.WriteLine("|" + cubeString[4].ElementAt(0) + "|" + cubeString[4].ElementAt(1) + "|" + cubeString[4].ElementAt(2) + "|");
            Console.WriteLine("+-+-+-+ +-+-+-+ +-+-+-+");
            Console.Write("|" + cubeString[2].ElementAt(3) + "|" + cubeString[2].ElementAt(4) + "|" + cubeString[2].ElementAt(5) + "| ");
            Console.Write("|" + cubeString[1].ElementAt(3) + "|" + cubeString[1].ElementAt(4) + "|" + cubeString[1].ElementAt(5) + "| ");
            Console.WriteLine("|" + cubeString[4].ElementAt(3) + "|" + cubeString[4].ElementAt(4) + "|" + cubeString[4].ElementAt(5) + "|");
            Console.WriteLine("+-+-+-+ +-+-+-+ +-+-+-+");
            Console.Write("|" + cubeString[2].ElementAt(6) + "|" + cubeString[2].ElementAt(7) + "|" + cubeString[2].ElementAt(8) + "| ");
            Console.Write("|" + cubeString[1].ElementAt(6) + "|" + cubeString[1].ElementAt(7) + "|" + cubeString[1].ElementAt(8) + "| ");
            Console.WriteLine("|" + cubeString[4].ElementAt(6) + "|" + cubeString[4].ElementAt(7) + "|" + cubeString[4].ElementAt(8) + "|");
            Console.WriteLine("+-+-+-+ +-+-+-+ +-+-+-+");
            Console.WriteLine(breakLine);
            Console.WriteLine("        |" + cubeString[3].ElementAt(0) + "|" + cubeString[3].ElementAt(1) + "|" + cubeString[3].ElementAt(2) + "|");
            Console.WriteLine(breakLine);
            Console.WriteLine("        |" + cubeString[3].ElementAt(3) + "|" + cubeString[3].ElementAt(4) + "|" + cubeString[3].ElementAt(5) + "|");
            Console.WriteLine(breakLine);
            Console.WriteLine("        |" + cubeString[3].ElementAt(6) + "|" + cubeString[3].ElementAt(7) + "|" + cubeString[3].ElementAt(8) + "|");
            Console.WriteLine(breakLine);
            Console.WriteLine(breakLine);
            Console.WriteLine("        |" + cubeString[5].ElementAt(0) + "|" + cubeString[5].ElementAt(1) + "|" + cubeString[5].ElementAt(2) + "|");
            Console.WriteLine(breakLine);
            Console.WriteLine("        |" + cubeString[5].ElementAt(3) + "|" + cubeString[5].ElementAt(4) + "|" + cubeString[5].ElementAt(5) + "|");
            Console.WriteLine(breakLine);
            Console.WriteLine("        |" + cubeString[5].ElementAt(6) + "|" + cubeString[5].ElementAt(7) + "|" + cubeString[5].ElementAt(8) + "|");
            Console.WriteLine(breakLine);
        }

        static private void Par() {
            Console.WriteLine("Entered Auto Parallel Mode");

            List<Cube.Positions[]> positions = new List<Cube.Positions[]>();

            // Replicate the current postions 12 times (one for each possible move)
            for (int i = 0; i < 12; i++) {
                positions.Add(cube.GetPositions());
            }

            int count = 0;

            // While the cube isn't solved, make every possible move for that cube, check if solved, if not save the current combinations
            // and replicate each one 12 times then repeat (check moves in parallel)
            while (!solved) {
                Console.WriteLine("Starting pass {1}. Contains {0} combinations", positions.Count, count + 1);

                var sw = Stopwatch.StartNew();

                // Make all possible moves
                Parallel.For(0, positions.Count, i => {
                    Cube tester = new Cube(positions[i]);

                    if (i % 12 == 0)
                        tester.RotateSide(Cube.Positions.front, true);
                    else if (i % 12 == 1)
                        tester.RotateSide(Cube.Positions.back, true);
                    else if (i % 12 == 2)
                        tester.RotateSide(Cube.Positions.top, true);
                    else if (i % 12 == 3)
                        tester.RotateSide(Cube.Positions.bottom, true);
                    else if (i % 12 == 4)
                        tester.RotateSide(Cube.Positions.left, true);
                    else if (i % 12 == 5)
                        tester.RotateSide(Cube.Positions.right, true);
                    else if (i % 12 == 6)
                        tester.RotateSide(Cube.Positions.front, false);
                    else if (i % 12 == 7)
                        tester.RotateSide(Cube.Positions.back, false);
                    else if (i % 12 == 8)
                        tester.RotateSide(Cube.Positions.top, false);
                    else if (i % 12 == 9)
                        tester.RotateSide(Cube.Positions.bottom, false);
                    else if (i % 12 == 10)
                        tester.RotateSide(Cube.Positions.left, false);
                    else if (i % 12 == 11)
                        tester.RotateSide(Cube.Positions.right, false);

                    if (tester.GetPositions().Equals(original)) {
                        solved = true;
                        Console.WriteLine("Found solution! Combination number: {0}", i);
                        PrintCube(tester);
                        positions.Clear();
                        return;
                    } else {
                        positions[i] = tester.GetPositions();
                        positions.TrimExcess();
                    }
                });

                sw.Stop();

                Console.WriteLine("Passed finished. Completed in: {0}ms", sw.ElapsedMilliseconds);

                // Check if solved, if not save the current positions and duplicate
                if (!solved) {
                    Console.WriteLine("Cube not solved\nSaving...");

                    sw = Stopwatch.StartNew();

                    List<Cube.Positions[]> tempPos = new List<Cube.Positions[]>();

                    for (int i = positions.Count; i > 0; i--) {
                        tempPos.Add(positions[positions.Count - 1]);

                        positions.RemoveAt(positions.Count - 1);
                    }

                    positions.Clear();

                    for (int i = tempPos.Count; i > 0; i--) {
                        for (int j = 0; j < 12; j++) {
                            positions.Add(tempPos[tempPos.Count - 1]);
                        }

                        tempPos.RemoveAt(tempPos.Count - 1);
                    }

                    tempPos.Clear();

                    sw.Stop();

                    Console.WriteLine("Saved. Took {0}ms to save.", sw.ElapsedMilliseconds);
                }
                count++;

                Console.WriteLine("Pass: {0} Completed", count);
            }
        }

        static private void SeqChunk() {
            Console.WriteLine("Entered Auto Sequential Mode, done in chunks"); // then breadth for each element in that layer (to a max of 7 layers for this search).

            List<Cube.Positions[]> starts = new List<Cube.Positions[]>();
            List<Cube.Positions[]> positions = new List<Cube.Positions[]>();

            for (int i = 0; i < 12; i++) {
                positions.Add(cube.GetPositions());
            }

            var totalTime = Stopwatch.StartNew();

            int num = 0;

            for (int z = 0; z < 7; z++) {
                List<Cube.Positions[]> newPositions = new List<Cube.Positions[]>();

                if (z != 6) {
                    Console.WriteLine("Starting pass {1}. Contains {0} combinations", positions.Count, num + 1);

                    var sw = Stopwatch.StartNew();

                    for (int i = positions.Count - 1; i >= 0; i--) {
                        cube.SetPositions(positions[i]);

                        if (i % 12 == 0)
                            cube.RotateSide(Cube.Positions.front, true);
                        else if (i % 12 == 1)
                            cube.RotateSide(Cube.Positions.back, true);
                        else if (i % 12 == 2)
                            cube.RotateSide(Cube.Positions.top, true);
                        else if (i % 12 == 3)
                            cube.RotateSide(Cube.Positions.bottom, true);
                        else if (i % 12 == 4)
                            cube.RotateSide(Cube.Positions.left, true);
                        else if (i % 12 == 5)
                            cube.RotateSide(Cube.Positions.right, true);
                        else if (i % 12 == 6)
                            cube.RotateSide(Cube.Positions.front, false);
                        else if (i % 12 == 7)
                            cube.RotateSide(Cube.Positions.back, false);
                        else if (i % 12 == 8)
                            cube.RotateSide(Cube.Positions.top, false);
                        else if (i % 12 == 9)
                            cube.RotateSide(Cube.Positions.bottom, false);
                        else if (i % 12 == 10)
                            cube.RotateSide(Cube.Positions.left, false);
                        else if (i % 12 == 11)
                            cube.RotateSide(Cube.Positions.right, false);

                        if (cube.SamePositions(original)) {
                            solved = true;
                            Console.WriteLine("Found solution! Combination number: {0}", i);
                            positions.Clear();
                            positions.TrimExcess();
                            newPositions.Clear();
                            newPositions.TrimExcess();
                            break;
                        } else {
                            newPositions.Add(cube.GetPositions());
                            positions.RemoveAt(i);
                        }
                    }
                    positions.Clear();
                    positions.Capacity = 0;

                    sw.Stop();

                    Console.WriteLine("Passed finished. Completed in: {0}ms", sw.ElapsedMilliseconds);

                    if (!solved) {
                        Console.WriteLine("Cube not solved\nSaving...");

                        sw = Stopwatch.StartNew();

                        for (int i = newPositions.Count - 1; i >= 0; i--) {
                            for (int j = 0; j < 12; j++) {
                                positions.Add(newPositions[i]);
                            }

                            newPositions.RemoveAt(i);
                        }

                        newPositions.Clear();
                        newPositions.Capacity = 0;

                        sw.Stop();

                        Console.WriteLine("Saved. Took {0}ms to save.", sw.ElapsedMilliseconds);
                    }
                    num++;

                    Console.WriteLine("Pass: {0} Completed", num);
                } else {
                    if (!solved) {
                        if (starts.Count == 0) {
                            foreach (Cube.Positions[] pos in positions) {
                                starts.Add(pos);
                            }

                            positions.Clear();
                            positions.TrimExcess();
                            GC.Collect();
                            GC.WaitForPendingFinalizers();

                            Console.WriteLine("Starting Chunk Sequence");
                        }

                        for (int i = 0; i < 12; i++) {
                            positions.Add(starts[i]);

                            int count = 0;

                            while (count < 8) {
                                Console.WriteLine("Starting pass {1} of chunk {2}. Contains {0} combinations", positions.Count,
                                    count + 1, i + 1);

                                var sw = Stopwatch.StartNew();

                                for (int j = positions.Count - 1; j >= 0; j--) {
                                    cube.SetPositions(positions[j]);

                                    if (j % 12 == 0)
                                        cube.RotateSide(Cube.Positions.front, true);
                                    else if (j % 12 == 1)
                                        cube.RotateSide(Cube.Positions.back, true);
                                    else if (j % 12 == 2)
                                        cube.RotateSide(Cube.Positions.top, true);
                                    else if (j % 12 == 3)
                                        cube.RotateSide(Cube.Positions.bottom, true);
                                    else if (j % 12 == 4)
                                        cube.RotateSide(Cube.Positions.left, true);
                                    else if (j % 12 == 5)
                                        cube.RotateSide(Cube.Positions.right, true);
                                    else if (j % 12 == 6)
                                        cube.RotateSide(Cube.Positions.front, false);
                                    else if (j % 12 == 7)
                                        cube.RotateSide(Cube.Positions.back, false);
                                    else if (j % 12 == 8)
                                        cube.RotateSide(Cube.Positions.top, false);
                                    else if (j % 12 == 9)
                                        cube.RotateSide(Cube.Positions.bottom, false);
                                    else if (j % 12 == 10)
                                        cube.RotateSide(Cube.Positions.left, false);
                                    else if (j % 12 == 11)
                                        cube.RotateSide(Cube.Positions.right, false);

                                    if (cube.SamePositions(original)) {
                                        solved = true;
                                        sw.Stop();
                                        Console.WriteLine("Found solution! Combination number: {0}. Time taken on pass {1}",
                                            j * (i + 1) * (z + 1), sw.ElapsedMilliseconds);
                                        PrintCube(cube);
                                        positions.Clear();
                                        positions.TrimExcess();
                                        newPositions.Clear();
                                        newPositions.TrimExcess();
                                        break;
                                    } else {
                                        newPositions.Add(cube.GetPositions());
                                        positions.RemoveAt(j);
                                    }

                                    if (j % 1200000 == 1199999) {
                                        GC.Collect();
                                        GC.WaitForPendingFinalizers();
                                    }
                                }

                                positions.Clear();
                                positions.Capacity = 0;

                                sw.Stop();

                                Console.WriteLine("Passed finished. Completed in: {0}ms", sw.ElapsedMilliseconds);

                                if (!solved && count != 7) {
                                    Console.WriteLine("Cube not solved\nSaving...");

                                    sw = Stopwatch.StartNew();

                                    for (int j = newPositions.Count - 1; j >= 0; j--) {
                                        for (int k = 0; k < 12; k++) {
                                            positions.Add(newPositions[j]);
                                        }

                                        newPositions.RemoveAt(j);
                                    }

                                    newPositions.Clear();
                                    newPositions.Capacity = 0;

                                    sw.Stop();

                                    Console.WriteLine("Saved. Took {0}ms to save.", sw.ElapsedMilliseconds);
                                }
                                count++;

                                Console.WriteLine("Pass: {0} Completed", count);

                                GC.Collect();
                                GC.WaitForPendingFinalizers();
                            }

                            Console.WriteLine("Chunk {0} Finished", i + 1);

                            if (solved) {
                                totalTime.Stop();
                                Console.WriteLine("Cube Solved, stopping checks. Took {0}ms to find solution", totalTime.ElapsedMilliseconds);
                                positions.Clear();
                                positions.TrimExcess();
                                newPositions.Clear();
                                newPositions.TrimExcess();
                                break;
                            }
                            positions.Clear();
                            positions.TrimExcess();

                            newPositions.Clear();
                            newPositions.TrimExcess();
                            GC.Collect();
                            GC.WaitForPendingFinalizers();
                        }
                        GC.Collect();
                        GC.WaitForPendingFinalizers();
                    }
                }
                GC.Collect();
                GC.WaitForPendingFinalizers();
            }
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }

        static void Seq() {
            Console.WriteLine("Entered Auto Sequential Mode");

            List<byte[]> positions = new List<byte[]>();
            List<byte[]> newPositions = new List<byte[]>();

            for (int i = 0; i < 12; i++) {
                Cube.Positions[] pos = cube.GetPositions();
                byte[] p = new byte[pos.Length];
                for (int k = 0; k < p.Length; k++)
                    p[k] = (byte)pos[k];

                positions.Add(p);
            }

            int count = 0;

            while (!solved) {
                Console.WriteLine("Starting pass {1}. Contains {0} combinations", positions.Count, count + 1);

                var sw = Stopwatch.StartNew();

                for (int i = positions.Count - 1; i >= 0; i--) {
                    Cube.Positions[] test = new Cube.Positions[positions[i].Length];
                    for (int k = 0; k < test.Length; k++)
                        test[k] = (Cube.Positions)positions[i][k];

                    cube.SetPositions(test);

                    if (i % 12 == 0)
                        cube.RotateSide(Cube.Positions.front, true);
                    else if (i % 12 == 1)
                        cube.RotateSide(Cube.Positions.back, true);
                    else if (i % 12 == 2)
                        cube.RotateSide(Cube.Positions.top, true);
                    else if (i % 12 == 3)
                        cube.RotateSide(Cube.Positions.bottom, true);
                    else if (i % 12 == 4)
                        cube.RotateSide(Cube.Positions.left, true);
                    else if (i % 12 == 5)
                        cube.RotateSide(Cube.Positions.right, true);
                    else if (i % 12 == 6)
                        cube.RotateSide(Cube.Positions.front, false);
                    else if (i % 12 == 7)
                        cube.RotateSide(Cube.Positions.back, false);
                    else if (i % 12 == 8)
                        cube.RotateSide(Cube.Positions.top, false);
                    else if (i % 12 == 9)
                        cube.RotateSide(Cube.Positions.bottom, false);
                    else if (i % 12 == 10)
                        cube.RotateSide(Cube.Positions.left, false);
                    else if (i % 12 == 11)
                        cube.RotateSide(Cube.Positions.right, false);

                    if (cube.SamePositions(original)) {
                        solved = true;
                        Console.WriteLine("Found solution! Combination number: {0}", i);
                        positions.Clear();
                        positions.TrimExcess();
                        newPositions.Clear();
                        newPositions.TrimExcess();
                        break;
                    } else {
                        Cube.Positions[] pos = cube.GetPositions();
                        byte[] p = new byte[pos.Length];
                        for (int k = 0; k < p.Length; k++)
                            p[k] = (byte)pos[k];

                        newPositions.Add(p);
                        positions.RemoveAt(i);
                    }
                }
                positions.Clear();
                positions.Capacity = 0;

                sw.Stop();

                Console.WriteLine("Passed finished. Completed in: {0}ms", sw.ElapsedMilliseconds);

                if (!solved) {
                    Console.WriteLine("Cube not solved\nSaving...");

                    sw = Stopwatch.StartNew();

                    for (int i = newPositions.Count - 1; i >= 0; i--) {
                        for (int j = 0; j < 12; j++) {
                            positions.Add(newPositions[i]);
                        }

                        newPositions.RemoveAt(i);
                    }

                    newPositions.Clear();
                    newPositions.Capacity = 0;

                    sw.Stop();

                    Console.WriteLine("Saved. Took {0}ms to save.", sw.ElapsedMilliseconds);
                }
                count++;

                Console.WriteLine("Pass: {0} Completed", count);
            }
        }

        static void Smart() {
            Console.WriteLine("Entered Other Test Mode");

            List<byte[]> seenCombinations = new List<byte[]>();
            List<byte[]> toTestCombinations = new List<byte[]>();
            List<byte[]> newCombination = new List<byte[]>();

            Cube.Positions[] p = cube.GetPositions();
            byte[] toTest = new byte[p.Length];
            for (int i = 0; i < toTest.Length; i++)
                toTest[i] = (byte)p[i];
            toTestCombinations.Add(toTest);

            int count = 0;

            while (!solved) {
                Console.WriteLine("Starting pass {1}. Combinations to test {0} combinations, with {2} seen combinations", toTestCombinations.Count, count + 1, seenCombinations.Count);

                var sw = Stopwatch.StartNew();

                for (int i = toTestCombinations.Count - 1; i >= 0; i--) {
                    for (int j = 0; j < 12; j++) {
                        Cube.Positions[] test = new Cube.Positions[toTestCombinations[i].Length];
                        for (int k = 0; k < test.Length; k++)
                            test[k] = (Cube.Positions)toTestCombinations[i][k];
                        cube.SetPositions(test);

                        if (j == 0)
                            cube.RotateSide(Cube.Positions.front, true);
                        else if (j == 1)
                            cube.RotateSide(Cube.Positions.back, true);
                        else if (j == 2)
                            cube.RotateSide(Cube.Positions.top, true);
                        else if (j == 3)
                            cube.RotateSide(Cube.Positions.bottom, true);
                        else if (j == 4)
                            cube.RotateSide(Cube.Positions.left, true);
                        else if (j == 5)
                            cube.RotateSide(Cube.Positions.right, true);
                        else if (j == 6)
                            cube.RotateSide(Cube.Positions.front, false);
                        else if (j == 7)
                            cube.RotateSide(Cube.Positions.back, false);
                        else if (j == 8)
                            cube.RotateSide(Cube.Positions.top, false);
                        else if (j == 9)
                            cube.RotateSide(Cube.Positions.bottom, false);
                        else if (j == 10)
                            cube.RotateSide(Cube.Positions.left, false);
                        else if (j == 11)
                            cube.RotateSide(Cube.Positions.right, false);

                        if (cube.SamePositions(original)) {
                            solved = true;
                            Console.WriteLine("Found solution!");
                            toTestCombinations.Clear();
                            toTestCombinations.TrimExcess();
                            seenCombinations.Clear();
                            seenCombinations.TrimExcess();
                            newCombination.Clear();
                            newCombination.TrimExcess();
                            break;
                        } else {
                            Cube.Positions[] positions = cube.GetPositions();
                            byte[] pos = new byte[positions.Length];
                            for (int k = 0; k < pos.Length; k++)
                                pos[k] = (byte)positions[k];

                            newCombination.Add(pos);
                        }
                    }
                    if (solved)
                        break;

                    toTestCombinations.RemoveAt(i);
                }
                toTestCombinations.Clear();

                sw.Stop();

                Console.WriteLine("Passed finished. Completed in: {0}ms", sw.ElapsedMilliseconds);

                if (!solved) {
                    Console.WriteLine("Cube not solved");

                    if (seenCombinations.Count <= 0) {
                        Console.WriteLine("Adding combinations to seen and test lists");
                        for (int i = newCombination.Count - 1; i >= 0; i--) {
                            seenCombinations.Add(newCombination[i]);
                            toTestCombinations.Add(newCombination[i]);
                            newCombination.RemoveAt(i);
                        }
                    } else {
                        Console.WriteLine("Checking {0} combinations against {1} combinations for duplicates...", newCombination.Count, seenCombinations.Count);

                        sw = Stopwatch.StartNew();
                        int startNum = newCombination.Count();
                        int numSeen = 0;

                        //for (int i = newCombination.Count - 1; i >= 0; i--) {
                        //    bool seen = true;
                        //    for (int j = 0; j < seenCombinations.Count; j++) {
                        //        BitArray n = new BitArray(newCombination[i]);
                        //        BitArray s = new BitArray(seenCombinations[j]);

                        //        s.Not();
                        //        for (int k = 0; k < n.Count; k++) {
                        //            for (int x = 0; x < s.Count; x++) {
                        //                if (n[k] & s[x]) {
                        //                    seen = false;
                        //                }
                        //            }

                        //            if (!seen)
                        //                break;
                        //        }

                        //        if (!seen) {
                        //            break;
                        //        }

                        //        numSeen++;
                        //    }

                        //    if (!seen) {
                        //        seenCombinations.Add(newCombination[i]);
                        //        toTestCombinations.Add(newCombination[i]);
                        //    }

                        //    newCombination.RemoveAt(i);
                        //}

                        for (int i = newCombination.Count - 1; i >= 0; i--) {
                            bool seen = false;
                            for (int j = 0; j < seenCombinations.Count; j++) {
                                if (newCombination[i].SequenceEqual(seenCombinations[j])) {
                                    numSeen++;
                                    seen = true;
                                    break;
                                }
                            }

                            if (!seen) {
                                seenCombinations.Add(newCombination[i]);
                                toTestCombinations.Add(newCombination[i]);
                            }

                            newCombination.RemoveAt(i);
                        }

                        sw.Stop();

                        newCombination.Clear();

                        Console.WriteLine("Done. Took {0}ms to check.", sw.ElapsedMilliseconds);
                        Console.WriteLine("Added {1} combinations to test. Already seen {0} combinations", startNum - toTestCombinations.Count + numSeen, toTestCombinations.Count());
                    }
                    count++;

                    Console.WriteLine("Pass: {0} Completed", count);
                }
            }
        }

        static int Heuristic(Cube.Positions[] pos) {
            Cube infoCube = new Cube(pos);

            Corner[] corners = infoCube.GetCorners();
            Edge[] edges = infoCube.GetEdges();

            int score = 0;

            for (int i = 0; i < corners.Length; i++) {
                int count = 0;
                Cube.Colours[] colours = corners[i].GetColours();
                Cube.Positions[] positions = corners[i].GetPosition();

                for (int j = 0; j < positions.Length; j++) {
                    if (colours[j].Equals(Cube.Colours.green) && positions[j].Equals(Cube.Positions.top))
                        count++;
                    else if (colours[j].Equals(Cube.Colours.yellow) && positions[j].Equals(Cube.Positions.front))
                        count++;
                    else if (colours[j].Equals(Cube.Colours.red) && positions[j].Equals(Cube.Positions.right))
                        count++;
                    else if (colours[j].Equals(Cube.Colours.blue) && positions[j].Equals(Cube.Positions.bottom))
                        count++;
                    else if (colours[j].Equals(Cube.Colours.orange) && positions[j].Equals(Cube.Positions.left))
                        count++;
                    else if (colours[j].Equals(Cube.Colours.white) && positions[j].Equals(Cube.Positions.back))
                        count++;
                }

                score += (count * colours.Length);

                if (colours.Contains(Cube.Colours.green) && corners[i].InSide(Cube.Positions.top))
                    score++;
                if (colours.Contains(Cube.Colours.blue) && corners[i].InSide(Cube.Positions.bottom))
                    score++;
                if (colours.Contains(Cube.Colours.yellow) && corners[i].InSide(Cube.Positions.front))
                    score++;
                if (colours.Contains(Cube.Colours.white) && corners[i].InSide(Cube.Positions.back))
                    score++;
                if (colours.Contains(Cube.Colours.orange) && corners[i].InSide(Cube.Positions.left))
                    score++;
                if (colours.Contains(Cube.Colours.red) && corners[i].InSide(Cube.Positions.right))
                    score++;
            }

            for (int i = 0; i < edges.Length; i++) {
                int count = 0;
                Cube.Colours[] colours = edges[i].GetColours();
                Cube.Positions[] positions = edges[i].GetPosition();

                for (int j = 0; j < positions.Length; j++) {
                    if (colours[j].Equals(Cube.Colours.green) && positions[j].Equals(Cube.Positions.top))
                        count++;
                    else if (colours[j].Equals(Cube.Colours.yellow) && positions[j].Equals(Cube.Positions.front))
                        count++;
                    else if (colours[j].Equals(Cube.Colours.red) && positions[j].Equals(Cube.Positions.right))
                        count++;
                    else if (colours[j].Equals(Cube.Colours.blue) && positions[j].Equals(Cube.Positions.bottom))
                        count++;
                    else if (colours[j].Equals(Cube.Colours.orange) && positions[j].Equals(Cube.Positions.left))
                        count++;
                    else if (colours[j].Equals(Cube.Colours.white) && positions[j].Equals(Cube.Positions.back))
                        count++;
                }

                score += (count * colours.Length);

                if (colours.Contains(Cube.Colours.green) && edges[i].InSide(Cube.Positions.top))
                    score++;
                if (colours.Contains(Cube.Colours.blue) && edges[i].InSide(Cube.Positions.bottom))
                    score++;
                if (colours.Contains(Cube.Colours.yellow) && edges[i].InSide(Cube.Positions.front))
                    score++;
                if (colours.Contains(Cube.Colours.white) && edges[i].InSide(Cube.Positions.back))
                    score++;
                if (colours.Contains(Cube.Colours.orange) && edges[i].InSide(Cube.Positions.left))
                    score++;
                if (colours.Contains(Cube.Colours.red) && edges[i].InSide(Cube.Positions.right))
                    score++;
            }

            return score;
        }

        static void AStar() {
            Console.WriteLine("Entering A* Search Mode");
            List<Tuple<Cube.Positions[], int, int>> openList = new List<Tuple<Cube.Positions[], int, int>>();
            List<Tuple<Cube.Positions[], int, int>> closedList = new List<Tuple<Cube.Positions[], int, int>>();

            closedList.Add(new Tuple<Cube.Positions[], int, int>(cube.GetPositions(), Heuristic(cube.GetPositions()), 0));

            for (int i = 0; i < 12; i++) {
                cube.SetPositions(closedList[0].Item1);
                MoveCubeSide(i, cube);
                openList.Add(new Tuple<Cube.Positions[], int, int>(cube.GetPositions(), Heuristic(cube.GetPositions()), closedList[0].Item3 + 1));
            }

            Cube offByOne = new Cube();
            MoveCubeSide(0, offByOne);
            int oneMoveLeft = Heuristic(offByOne.GetPositions());
            Console.WriteLine("Off by one: {0}", oneMoveLeft);
            int closest = int.MinValue;

            while (!solved) {
                if (closedList.Count % 100 == 0) {
                    int deepest = int.MinValue;
                    int highest = int.MaxValue;

                    foreach (Tuple<Cube.Positions[], int, int> node in closedList) {
                        if (node.Item3 > deepest)
                            deepest = node.Item3;
                        if (node.Item3 < highest)
                            highest = node.Item3;
                    }

                    Console.WriteLine("Elements in closed list: {0}. Elements in open list: {1}.\nClosest Value so far: {2}.", closedList.Count,
                        openList.Count, closest);
                    Console.WriteLine("Most moves: {0}. And the least moves: {1}", deepest, highest);
                }

                int max = int.MinValue;
                int index = 0;
                int lowestMoves = int.MaxValue;

                for (int i = 0; i < openList.Count; i++) {
                    if (openList[i].Item1.SequenceEqual(original)) {
                        solved = true;
                        Console.WriteLine("Solution found. Number of moves {0}. Positions searched {1}", openList[index].Item3, closedList.Count + openList.Count);
                        return;
                    }

                    if (openList[i].Item3 < lowestMoves)
                        lowestMoves = openList[i].Item3;

                    if (openList[i].Item2 == oneMoveLeft) {
                        index = i;
                        break;
                    } else if (openList[i].Item2 > max && openList[i].Item2 <= oneMoveLeft && openList[i].Item3 - lowestMoves <= 40) {
                        max = openList[i].Item2;
                        index = i;
                    }
                }

                if (closedList.Count % 100 == 0) {
                    Console.WriteLine("Current node depth: {0}. Current node value: {1}.", openList[index].Item3, openList[index].Item2);
                }

                if (max > closest)
                    closest = max;

                for (int i = 0; i < 12; i++) {
                    cube.SetPositions(openList[index].Item1);

                    MoveCubeSide(i, cube);

                    if (cube.SamePositions(original)) {
                        solved = true;
                        Console.WriteLine("Solution found. Number of moves {0}. Moves searched {1}", openList[index].Item3 + 1, closedList.Count + openList.Count + 1);
                        return;
                    }

                    Cube.Positions[] c = cube.GetPositions();
                    bool seen = false;
                    Parallel.For(0, openList.Count, j => {
                        if (c.SequenceEqual(openList[j].Item1))
                            seen = true;
                    });

                    Parallel.For(0, closedList.Count, j => {
                        if (c.SequenceEqual(closedList[j].Item1))
                            seen = true;
                    });

                    if (!seen)
                        openList.Add(new Tuple<Cube.Positions[], int, int>(c, Heuristic(c), openList[index].Item3 + 1));
                }

                bool s = false;
                Parallel.For(0, closedList.Count, i => {
                    if (openList[index].Item1.SequenceEqual(closedList[i].Item1))
                        s = true;
                });

                if (!s)
                    closedList.Add(openList[index]);

                openList.Remove(openList[index]);
            }
        }

        static void SmartWithHelp() {
            Console.WriteLine("Entered Other Test Mode with Pi help");

            List<byte[]> seenCombinations = new List<byte[]>();
            List<byte[]> toTestCombinations = new List<byte[]>();
            List<byte[]> newCombination = new List<byte[]>();

            Cube.Positions[] p = cube.GetPositions();
            byte[] toTest = new byte[p.Length];
            for (int i = 0; i < toTest.Length; i++)
                toTest[i] = (byte)p[i];
            toTestCombinations.Add(toTest);

            int count = 0;

            while (!solved) {
                Console.WriteLine("Starting pass {1}. Combinations to test {0} combinations, with {2} seen combinations", toTestCombinations.Count, count + 1, seenCombinations.Count);

                var sw = Stopwatch.StartNew();

                for (int i = toTestCombinations.Count - 1; i >= 0; i--) {
                    for (int j = 0; j < 12; j++) {
                        Cube.Positions[] test = new Cube.Positions[toTestCombinations[i].Length];
                        for (int k = 0; k < test.Length; k++)
                            test[k] = (Cube.Positions)toTestCombinations[i][k];
                        cube.SetPositions(test);

                        if (j == 0)
                            cube.RotateSide(Cube.Positions.front, true);
                        else if (j == 1)
                            cube.RotateSide(Cube.Positions.back, true);
                        else if (j == 2)
                            cube.RotateSide(Cube.Positions.top, true);
                        else if (j == 3)
                            cube.RotateSide(Cube.Positions.bottom, true);
                        else if (j == 4)
                            cube.RotateSide(Cube.Positions.left, true);
                        else if (j == 5)
                            cube.RotateSide(Cube.Positions.right, true);
                        else if (j == 6)
                            cube.RotateSide(Cube.Positions.front, false);
                        else if (j == 7)
                            cube.RotateSide(Cube.Positions.back, false);
                        else if (j == 8)
                            cube.RotateSide(Cube.Positions.top, false);
                        else if (j == 9)
                            cube.RotateSide(Cube.Positions.bottom, false);
                        else if (j == 10)
                            cube.RotateSide(Cube.Positions.left, false);
                        else if (j == 11)
                            cube.RotateSide(Cube.Positions.right, false);

                        if (cube.SamePositions(original)) {
                            solved = true;
                            Console.WriteLine("Found solution!");
                            toTestCombinations.Clear();
                            toTestCombinations.TrimExcess();
                            seenCombinations.Clear();
                            seenCombinations.TrimExcess();
                            newCombination.Clear();
                            newCombination.TrimExcess();
                            break;
                        } else {
                            Cube.Positions[] positions = cube.GetPositions();
                            byte[] pos = new byte[positions.Length];
                            for (int k = 0; k < pos.Length; k++)
                                pos[k] = (byte)positions[k];

                            newCombination.Add(pos);
                        }
                    }
                    if (solved)
                        break;

                    toTestCombinations.RemoveAt(i);
                }
                toTestCombinations.Clear();

                sw.Stop();

                Console.WriteLine("Passed finished. Completed in: {0}ms", sw.ElapsedMilliseconds);

                if (!solved) {
                    Console.WriteLine("Cube not solved");

                    if (seenCombinations.Count <= 0) {
                        Console.WriteLine("Adding combinations to seen and test lists");
                        for (int i = newCombination.Count - 1; i >= 0; i--) {
                            seenCombinations.Add(newCombination[i]);
                            toTestCombinations.Add(newCombination[i]);
                            newCombination.RemoveAt(i);
                        }
                    } else {
                        Console.WriteLine("Checking {0} combinations against {1} combinations for duplicates...", newCombination.Count, seenCombinations.Count);

                        sw = Stopwatch.StartNew();
                        int startNum = newCombination.Count();
                        int numSeen = 0;

                        for (int i = newCombination.Count - 1; i >= 0; i--) {
                            seenCombinations.Add(newCombination[i]);
                            toTestCombinations.Add(newCombination[i]);
                            newCombination.RemoveAt(i);
                        }

                        sw.Stop();

                        newCombination.Clear();
                        //if (seenCombinations.Count > 100000) {
                        Console.WriteLine("Sending data to Pi");

                        byte[] bytes = new byte[1024];

                        try {
                            IPHostEntry iPHostInfo = Dns.GetHostEntry("Hornet");
                            IPAddress iPAddress = iPHostInfo.AddressList[0];
                            Console.WriteLine(iPAddress.ToString());
                            IPEndPoint remoteEP = new IPEndPoint(iPAddress, 11000);

                            Socket sender = new Socket(iPAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                            try {
                                sender.Connect(remoteEP);

                                Console.WriteLine("Socket connected to {0}", iPAddress.ToString());

                                byte[] send = new byte[seenCombinations.Count * 54];
                                for (int i = 0; i < seenCombinations.Count; i++) {
                                    for (int j = 0; j < seenCombinations[i].Length; j++) {
                                        send[i + j] = seenCombinations[i][j];
                                    }
                                }
                                //toSend.Clear();
                                //toSend.TrimExcess();

                                int b = sender.Send(BitConverter.GetBytes(send.Count()));

                                int bytesSent = sender.Send(send);
                                Console.WriteLine("{0} bytes sent out of {1}", bytesSent, send.Length);
                                send = new byte[0];

                                int bytesRecieved = sender.Receive(bytes);
                                Console.WriteLine("Recieved {0} bytes", bytesRecieved);
                                sender.Shutdown(SocketShutdown.Both);
                                sender.Close();
                            } catch (ArgumentNullException ane) {
                                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
                            } catch (SocketException se) {
                                Console.WriteLine("SocketException : {0}", se.ToString());
                            } catch (Exception e) {
                                Console.WriteLine("Unexpected exception : {0}", e.ToString());
                            }

                        } catch (Exception e) {
                            Console.WriteLine(e.ToString());
                        }

                        Console.WriteLine("Sent");


                        Console.WriteLine("Done. Took {0}ms to check.", sw.ElapsedMilliseconds);
                        Console.WriteLine("Added {1} combinations to test. Already seen {0} combinations", startNum - toTestCombinations.Count + numSeen, toTestCombinations.Count());
                    }
                    count++;

                    Console.WriteLine("Pass: {0} Completed", count);
                }
            }
        }

        static void Threaded() {
            Console.WriteLine("Entered Smart Test Mode With Threads");

            List<byte[]> seenCombinations = new List<byte[]>();
            List<byte[]> toTestCombinations = new List<byte[]>();
            List<byte[]> newCombination = new List<byte[]>();
            List<byte[]> nextPass = new List<byte[]>();

            bool threadRun = true;
            bool ready = true;
            bool run = false;
            void CheckDuplicates(object threadParameter) {
                int lastRun = int.MinValue;
                while (threadRun) {
                    if (run) {
                        ready = false;
                        if (seenCombinations.Count > lastRun) {
                            List<byte[]> revised = new List<byte[]>();

                            revised.Add(seenCombinations[0]);

                            foreach (byte[] pos in seenCombinations) {
                                bool seen = false;
                                foreach (byte[] rev in revised) {
                                    int same = 0;
                                    for (int i = 0; i < pos.Length; i++)
                                        if (pos[i].CompareTo(rev[i]) == 0)
                                            same++;

                                    if (same == pos.Length)
                                        seen = true;
                                }

                                if (!seen)
                                    revised.Add(pos);
                            }

                            seenCombinations.Clear();
                            for (int i = revised.Count - 1; i >= 0; i--) {
                                seenCombinations.Add(revised[i]);
                                revised.RemoveAt(i);
                            }
                            seenCombinations.Reverse();
                        }
                        ready = true;
                    }

                }
            }

            Thread Checker = new Thread(CheckDuplicates);

            Cube.Positions[] p = cube.GetPositions();
            byte[] toTest = new byte[p.Length];
            for (int i = 0; i < toTest.Length; i++)
                toTest[i] = (byte)p[i];
            toTestCombinations.Add(toTest);

            int count = 0;

            while (!solved) {
                Console.WriteLine("Starting pass {1}. Combinations to test {0} combinations, with {2} seen combinations", toTestCombinations.Count, count + 1, seenCombinations.Count);
                var sw = Stopwatch.StartNew();
                for (int i = toTestCombinations.Count - 1; i >= 0; i--) {
                    for (int j = 0; j < 12; j++) {
                        Cube.Positions[] test = new Cube.Positions[toTestCombinations[i].Length];
                        for (int k = 0; k < test.Length; k++)
                            test[k] = (Cube.Positions)toTestCombinations[i][k];
                        cube.SetPositions(test);

                        if (j == 0)
                            cube.RotateSide(Cube.Positions.front, true);
                        else if (j == 1)
                            cube.RotateSide(Cube.Positions.back, true);
                        else if (j == 2)
                            cube.RotateSide(Cube.Positions.top, true);
                        else if (j == 3)
                            cube.RotateSide(Cube.Positions.bottom, true);
                        else if (j == 4)
                            cube.RotateSide(Cube.Positions.left, true);
                        else if (j == 5)
                            cube.RotateSide(Cube.Positions.right, true);
                        else if (j == 6)
                            cube.RotateSide(Cube.Positions.front, false);
                        else if (j == 7)
                            cube.RotateSide(Cube.Positions.back, false);
                        else if (j == 8)
                            cube.RotateSide(Cube.Positions.top, false);
                        else if (j == 9)
                            cube.RotateSide(Cube.Positions.bottom, false);
                        else if (j == 10)
                            cube.RotateSide(Cube.Positions.left, false);
                        else if (j == 11)
                            cube.RotateSide(Cube.Positions.right, false);

                        if (cube.SamePositions(original)) {
                            solved = true;
                            Console.WriteLine("Found solution!");
                            toTestCombinations.Clear();
                            toTestCombinations.TrimExcess();
                            seenCombinations.Clear();
                            seenCombinations.TrimExcess();
                            newCombination.Clear();
                            newCombination.TrimExcess();
                            threadRun = false;
                            Checker.Join();
                            break;
                        } else {
                            Cube.Positions[] positions = cube.GetPositions();
                            byte[] pos = new byte[positions.Length];
                            for (int k = 0; k < pos.Length; k++)
                                pos[k] = (byte)positions[k];

                            newCombination.Add(pos);
                        }
                    }
                    if (solved)
                        break;

                    toTestCombinations.RemoveAt(i);
                }
                toTestCombinations.Clear();

                sw.Stop();

                Console.WriteLine("Passed finished. Completed in: {0}ms", sw.ElapsedMilliseconds);

                if (Checker.ThreadState == System.Threading.ThreadState.Unstarted)
                    Checker.Start();

                if (!solved) {
                    Console.WriteLine("Cube not solved");

                    if (ready) {
                        run = false;

                        if (seenCombinations.Count <= 0) {
                            Console.WriteLine("Adding combinations to seen and test lists");
                            for (int i = newCombination.Count - 1; i >= 0; i--) {
                                seenCombinations.Add(newCombination[i]);
                                toTestCombinations.Add(newCombination[i]);
                                newCombination.RemoveAt(i);
                            }
                        } else {
                            Console.WriteLine("Checking {0} combinations against {1} combinations for duplicates...", newCombination.Count, seenCombinations.Count);

                            sw = Stopwatch.StartNew();
                            int startNum = newCombination.Count();

                            for (int i = newCombination.Count - 1; i >= 0; i--) {
                                bool seen = false;
                                for (int j = 0; j < seenCombinations.Count; j++) {
                                    int numSeen = 0;

                                    for (int k = 0; k < newCombination[i].Length; k++) {
                                        if (newCombination[i][k].CompareTo(seenCombinations[j][k]) == 0)
                                            numSeen++;
                                    }
                                    if (numSeen == newCombination[i].Length)
                                        seen = true;
                                }

                                if (!seen) {
                                    toTestCombinations.Add(newCombination[i]);
                                }

                                seenCombinations.Add(newCombination[i]);

                                newCombination.RemoveAt(i);
                            }

                            sw.Stop();

                            newCombination.Clear();

                            Console.WriteLine("Done. Took {0}ms to check.", sw.ElapsedMilliseconds);
                            Console.WriteLine("Added {1} combinations to test. Already seen {0} combinations", startNum - toTestCombinations.Count, toTestCombinations.Count());
                        }
                        count++;
                        run = true;
                        Console.WriteLine("Pass: {0} Completed", count);
                    }
                }
            }
        }

        static void Greedy(Cube.Positions[] current, int count, int closest) { // --------------------------------------------------
            if (count == 0)                                                    // TODO alter so that it keeps track of checked nodes
                Console.WriteLine("Entering Greedy Search Mode");              // --------------------------------------------------

            List<Tuple<Cube.Positions[], int>> children = new List<Tuple<Cube.Positions[], int>>();

            for (int i = 0; i < 12; i++) {
                cube.SetPositions(current);
                MoveCubeSide(i, cube);
                Cube.Positions[] p = cube.GetPositions();
                children.Add(new Tuple<Cube.Positions[], int>(p, Heuristic(p)));
            }

            if (count % 4000 == 0)
                Console.WriteLine("Layers deep: {0}. Closest Value so far: {1}", count, closest);

            int max = int.MinValue;
            int index = 0;

            for (int i = 0; i < children.Count; i++) {
                if (children[i].Item1.SequenceEqual(original)) {
                    solved = true;
                    return;
                }

                if (children[i].Item2 > max) {
                    max = children[i].Item2;
                    index = i;
                }
            }

            if (max > closest)
                closest = max;

            if (!solved)
                Greedy(children[index].Item1, count + 1, closest);
        }

        static void Tree() {
            Console.WriteLine("Entered Tree Test Mode");

            LinkedList<Cube.Positions[]> positions = new LinkedList<Cube.Positions[]>();
            LinkedListNode<Cube.Positions[]> start = new LinkedListNode<Cube.Positions[]>(cube.GetPositions());

            Cube.Positions[] p = cube.GetPositions();
            byte[] toTest = new byte[p.Length];
            for (int i = 0; i < toTest.Length; i++)
                toTest[i] = (byte)p[i];
            //toTestCombinations.Add(toTest);

            //int count = 0;

            //while (!solved) {
            //    Console.WriteLine("Starting pass {1}. Combinations to test {0} combinations, with {2} seen combinations", toTestCombinations.Count, count + 1, seenCombinations.Count);

            //    var sw = Stopwatch.StartNew();

            //    for (int i = toTestCombinations.Count - 1; i >= 0; i--) {
            //        for (int j = 0; j < 12; j++) {
            //            Cube.Positions[] test = new Cube.Positions[toTestCombinations[i].Length];
            //            for (int k = 0; k < test.Length; k++)
            //                test[k] = (Cube.Positions)toTestCombinations[i][k];
            //            cube.SetPositions(test);

            //            if (j == 0)
            //                cube.RotateSide(Cube.Positions.front, true);
            //            else if (j == 1)
            //                cube.RotateSide(Cube.Positions.back, true);
            //            else if (j == 2)
            //                cube.RotateSide(Cube.Positions.top, true);
            //            else if (j == 3)
            //                cube.RotateSide(Cube.Positions.bottom, true);
            //            else if (j == 4)
            //                cube.RotateSide(Cube.Positions.left, true);
            //            else if (j == 5)
            //                cube.RotateSide(Cube.Positions.right, true);
            //            else if (j == 6)
            //                cube.RotateSide(Cube.Positions.front, false);
            //            else if (j == 7)
            //                cube.RotateSide(Cube.Positions.back, false);
            //            else if (j == 8)
            //                cube.RotateSide(Cube.Positions.top, false);
            //            else if (j == 9)
            //                cube.RotateSide(Cube.Positions.bottom, false);
            //            else if (j == 10)
            //                cube.RotateSide(Cube.Positions.left, false);
            //            else if (j == 11)
            //                cube.RotateSide(Cube.Positions.right, false);

            //            if (cube.SamePositions(original)) {
            //                solved = true;
            //                Console.WriteLine("Found solution!");
            //                toTestCombinations.Clear();
            //                toTestCombinations.TrimExcess();
            //                seenCombinations.Clear();
            //                seenCombinations.TrimExcess();
            //                newCombination.Clear();
            //                newCombination.TrimExcess();
            //                break;
            //            } else {
            //                Cube.Positions[] positions = cube.GetPositions();
            //                byte[] pos = new byte[positions.Length];
            //                for (int k = 0; k < pos.Length; k++)
            //                    pos[k] = (byte)positions[k];

            //                newCombination.Add(pos);
            //            }
            //        }
            //        if (solved)
            //            break;

            //        toTestCombinations.RemoveAt(i);
            //    }
            //    toTestCombinations.Clear();

            //    sw.Stop();

            //    Console.WriteLine("Passed finished. Completed in: {0}ms", sw.ElapsedMilliseconds);
            //    if (!solved) {
            //        Console.WriteLine("Cube not solved");

            //        if (seenCombinations.Count <= 0) {
            //            Console.WriteLine("Adding combinations to seen and test lists");
            //            for (int i = newCombination.Count - 1; i >= 0; i--) {
            //                seenCombinations.Add(newCombination[i]);
            //                toTestCombinations.Add(newCombination[i]);
            //                newCombination.RemoveAt(i);
            //            }
            //        } else {
            //            Console.WriteLine("Checking {0} combinations against {1} combinations for duplicates...", newCombination.Count, seenCombinations.Count);

            //            sw = Stopwatch.StartNew();
            //            int startNum = newCombination.Count();
            //            int numSeen = 0;

            //            for (int i = newCombination.Count - 1; i >= 0; i--) {
            //                bool seen = false;
            //                for (int j = 0; j < seenCombinations.Count; j++) {
            //                    if (newCombination[i].SequenceEqual(seenCombinations[j])) {
            //                        numSeen++;
            //                        seen = true;
            //                        break;
            //                    }
            //                }

            //                if (!seen) {
            //                    seenCombinations.Add(newCombination[i]);
            //                    toTestCombinations.Add(newCombination[i]);
            //                }

            //                newCombination.RemoveAt(i);
            //            }

            //            sw.Stop();

            //            newCombination.Clear();

            //            Console.WriteLine("Done. Took {0}ms to check.", sw.ElapsedMilliseconds);
            //            Console.WriteLine("Added {1} combinations to test. Already seen {0} combinations", startNum - toTestCombinations.Count + numSeen, toTestCombinations.Count());
            //        }
            //        count++;

            //        Console.WriteLine("Pass: {0} Completed", count);
            //    }
            //}
        }

        static void Manual() {
            Console.WriteLine("Entered Manual Mode");
            while (!cube.IsSolved()) {
                Console.WriteLine("Which face do you wish to Rotate?");
                string side = Console.ReadLine();

                if (side.Equals("top") || side.Equals("bottom") || side.Equals("left") || side.Equals("right") || side.Equals("front") || side.Equals("back")) {
                    Cube.Positions position;
                    bool clockwise;

                    if (side.ToLower().Equals("top"))
                        position = Cube.Positions.top;
                    else if (side.ToLower().Equals("bottom"))
                        position = Cube.Positions.bottom;
                    else if (side.ToLower().Equals("left"))
                        position = Cube.Positions.left;
                    else if (side.ToLower().Equals("right"))
                        position = Cube.Positions.right;
                    else if (side.ToLower().Equals("front"))
                        position = Cube.Positions.front;
                    else
                        position = Cube.Positions.back;

                    Console.WriteLine("Clockwise or Anti?");
                    string key;

                    do {
                        Console.WriteLine("Y/N");
                        key = Console.ReadLine();
                        if (key.ToLower().Equals("y"))
                            clockwise = true;
                        else
                            clockwise = false;
                    } while (!key.ToLower().Equals("y") && !key.ToLower().Equals("n"));

                    cube.RotateSide(position, clockwise);

                    PrintCube(cube);
                }
            }
        }

        static void Random() {
            Console.WriteLine("Entered Random Mode"); // Does this on different threads for multiple copies of the cube

            randSolver = new Cube[7];

            for (int i = 0; i < randSolver.Length; i++) {
                randSolver[i] = new Cube(cube.GetPositions());
            }

            Parallel.For(0, randSolver.Length, i => {
                int count = 0;

                while (!solved) {
                    int num = random.Next(12);
                    MoveCubeSide(num, randSolver[i]);
                    count++;

                    if (randSolver[i].IsSolved()) {
                        solved = true;
                        Console.WriteLine("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
                        Console.WriteLine("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\nSovled on thread: " + i);
                    }

                    if (count % 100000 == 0) {
                        Console.WriteLine(count.ToString() + " random moves done on Thread: " + i);
                    }
                }
            });
        }

        /// <summary>
        /// Moves a side of a cube determined by a number instead of Cube.Positions
        /// </summary>
        /// <param name="num">The number representing the side</param>
        /// <param name="c">The cube whose side is to be moved</param>
        static private void MoveCubeSide(int num, Cube c) {
            if (num == 0)
                c.RotateSide(Cube.Positions.front, true);
            else if (num == 1)
                c.RotateSide(Cube.Positions.back, true);
            else if (num == 2)
                c.RotateSide(Cube.Positions.top, true);
            else if (num == 3)
                c.RotateSide(Cube.Positions.bottom, true);
            else if (num == 4)
                c.RotateSide(Cube.Positions.left, true);
            else if (num == 5)
                c.RotateSide(Cube.Positions.right, true);
            else if (num == 6)
                c.RotateSide(Cube.Positions.front, false);
            else if (num == 7)
                c.RotateSide(Cube.Positions.back, false);
            else if (num == 8)
                c.RotateSide(Cube.Positions.top, false);
            else if (num == 9)
                c.RotateSide(Cube.Positions.bottom, false);
            else if (num == 10)
                c.RotateSide(Cube.Positions.left, false);
            else if (num == 11)
                c.RotateSide(Cube.Positions.right, false);
        }

        static void Main(string[] args) {
            cube = new Cube();
            random = new Random();

            //Console.WriteLine("Heuristic: {0}", Heuristic(cube.GetPositions()));

            byte[] a = new byte[6];
            a[0] = (byte)Cube.Positions.top;
            a[1] = (byte)Cube.Positions.bottom;
            a[2] = (byte)Cube.Positions.front;
            a[3] = (byte)Cube.Positions.back;
            a[2] = (byte)Cube.Positions.left;
            a[3] = (byte)Cube.Positions.right;

            byte[] a1 = new byte[6];
            a1[0] = (byte)Cube.Positions.top;
            a1[1] = (byte)Cube.Positions.right;
            a1[2] = (byte)Cube.Positions.front;
            a1[3] = (byte)Cube.Positions.back;
            a1[2] = (byte)Cube.Positions.bottom;
            a1[3] = (byte)Cube.Positions.left;

            byte[] o = new byte[4];
            o[0] = (byte)Cube.Positions.top;
            o[1] = (byte)Cube.Positions.top;
            o[2] = (byte)Cube.Positions.right;
            o[3] = (byte)Cube.Positions.bottom;

            byte[] o2 = new byte[4];
            o2[0] = (byte)Cube.Positions.top;
            o2[1] = (byte)Cube.Positions.right;
            o2[2] = (byte)Cube.Positions.right;
            o2[3] = (byte)Cube.Positions.bottom;

            byte[] o21 = new byte[4];
            o21[0] = (byte)Cube.Positions.top;
            o21[1] = (byte)Cube.Positions.right;
            o21[2] = (byte)Cube.Positions.left;
            o21[3] = (byte)Cube.Positions.bottom;

            byte[] o24 = new byte[4];
            o24[0] = (byte)Cube.Positions.top;
            o24[1] = (byte)Cube.Positions.right;
            o24[2] = (byte)Cube.Positions.right;
            o24[3] = (byte)Cube.Positions.bottom;

            List<byte[]> ol = new List<byte[]> {
                o,
                o2,
                o2,
                o21,
                o24
            };

            List<byte[]> ot = new List<byte[]>();
            ot.Add(o2);

            //List<byte[]> oc = ol.Except(ot).ToList();

            //List<byte[]> oc = ol.Distinct().ToList();
            //ol = ol.Except(ot).ToList();

            BitArray q = new BitArray(a);
            BitArray q0 = new BitArray(a1);

            //q.Not();
            //foreach (bool bit in q) {
            //    Console.Write("|");
            //    Console.Write(bit);
            //    Console.Write("|");
            //}

            //Console.WriteLine();
            //Console.WriteLine();

            //q.Not();
            q.Not();
            q0.And(q);
            //foreach (bool bit in q0) {
            //    Console.Write("|");
            //    Console.Write(bit);
            //    Console.Write("|");
            //}
            //q0.And(q);
            //for (int i = 0; i < q.Count; i++) {
            //for (int j = 0; j < q0.Count; j++) {
            //Console.Write("|");
            //Console.Write(q0);
            //Console.Write("|");
            //}
            //Console.WriteLine();
            //}

            //foreach (byte[] p in ol) {
            //    foreach (byte pos in p) {
            //        Console.Write("|");
            //        Console.Write(pos);
            //        Console.Write("|");
            //    }
            //    Console.WriteLine();
            //}

            //Console.WriteLine(o24.SequenceEqual(o2));
            //Console.WriteLine(o24.SequenceEqual(o));

            // Randomise the first moves of the cube
            do {
                for (int i = 0; i < 5; i++) {
                    int num = random.Next(12);
                    MoveCubeSide(num, cube);
                }
            } while (cube.IsSolved());

            //Console.WriteLine();

            PrintCube(cube);
            Console.WriteLine("Heuristic: {0}", Heuristic(cube.GetPositions()));
            //Console.WriteLine("Mode");
            //string mode = Console.ReadLine();

            //AStar();
            //Greedy(cube.GetPositions(), 0, int.MinValue);
            // Automatic solving that aren't just random moves
            //if (mode.Equals("Auto-Seq") || mode.Equals("Auto-Par") || mode.Equals("Auto-Seq-Chunk")) {
            //    if (mode.Equals("Auto-Par")) { // Parallel version of the breadth-first search brute force solving mode
            //        Par();
            //    } else if (mode.Equals("Auto-Seq-Chunk")) { // Automatic breadth-depth-breadth brute force solving mode. Does breadth first down 6 layers,
            //        SeqChunk();
            //    } else {
            //Seq();
            //    }
            //} else if (mode.Equals("Smart")) {
            //Smart();
            //} else if (mode.Equals("Tree")) {
            //    Tree();
            //} else if (mode.Equals("Manual")) { // Manual solving mode. User solves the cube manually, controlling it by input the side to rotate and clockwise or not
            //    Manual();
            //} else { // Random solving mode. Just makes random moves on the cube till it's solved, printing milestones as it goes (every 100,000th move).
            //    Random();
            //}
            SmartWithHelp();
            //Threaded();

            Console.WriteLine("Cube Solved!!!");
            Console.WriteLine("Press any key to exit");
            Console.ReadKey();
        }
    }
}
