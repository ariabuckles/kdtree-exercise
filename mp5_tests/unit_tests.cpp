/**
 * MP6 Test Cases.
 * Ported by Aria Buckles
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "easypng.h"
#include "proxy.h"
#include "kdtree.h"

using namespace std;
using namespace util;

#define GENERATE_SOLUTIONS 0

template <int K>
string printTree(const KDTree<K> & tree)
{
	stringstream output;
	tree.printVectors(output);
	return output.str();
}

#if GENERATE_SOLUTIONS
#define ASSERT_TREE_EQUALS(tree, filename)        \
	do {                                          \
		string output = printTree(tree);          \
		ofstream fout(string(filename).c_str());  \
		fout << output;                           \
		fout.close();                             \
	} while (0)
#else
#define ASSERT_TREE_EQUALS(tree, filename)        \
	do {                                          \
		string output = printTree(tree);          \
		cout << output;                           \
		ASSERT(output == readFile(filename));     \
	} while (0)
#endif

#if MP_PART(1)

#if MONAD_SPLIT
UNIT_TEST(testSmallerDimVal, 4, 3, 5000)
{
	vector<Point<3> > pts;
	KDTree<3> tree(pts);
	Point<3> a(1, 2, 3);
	Point<3> b(3, 2, 1);
	
	ASSERT_EQUALS(true,  tree.smallerDimVal(a, b, 0));
	ASSERT_EQUALS(false, tree.smallerDimVal(a, b, 2));
	ASSERT_EQUALS(true,  tree.smallerDimVal(a, b, 1));
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testShouldReplace, 4, 3, 5000)
{
	vector<Point<3> > pts;
	KDTree<3> tree(pts);
	
	Point<3> target(1, 3, 5);
	Point<3> currentBest1(1, 3, 2);
	Point<3> possibleBest1(2, 4, 4);
	Point<3> currentBest2(1, 3, 6);
	Point<3> possibleBest2(2, 4, 4);
	Point<3> currentBest3(0, 2, 4);
	Point<3> possibleBest3(2, 4, 6);

	ASSERT_EQUALS(true,  tree.shouldReplace(target, currentBest1, possibleBest1));
	ASSERT_EQUALS(false, tree.shouldReplace(target, currentBest2, possibleBest2));
	ASSERT_EQUALS(false, tree.shouldReplace(target, currentBest3, possibleBest3));
}
#endif


#if MONAD_SPLIT
template <int K>
void testLinearCtor(int size)
{
	vector<Point<K> > points;
	points.reserve(size);
	for (int i = 0; i < size; i++)
	{
		Point<K> p;
		for (int j = 0; j < K; j++)
			p[j] = i;
		points.push_back(p);
	}

	KDTree<K> tree(points);

	ASSERT_TREE_EQUALS(tree, "soln_testLinearCtor_" + to_string(K) + "_" + to_string(size) + ".out");
}

UNIT_TEST(testLinearCtor_1_10, 6, 4, 5000) { testLinearCtor<1>(10); }
UNIT_TEST(testLinearCtor_3_31, 6, 4, 5000) { testLinearCtor<3>(31); }
UNIT_TEST(testLinearCtor_2_14, 6, 4, 5000) { testLinearCtor<2>(14); }
#endif


#if MONAD_SPLIT
template <int K>
void testLinearNNS(int size)
{
	vector< Point<K> > points;
	points.reserve(size);
	for (int i = 0; i < size; i++)
	{
		Point<K> p;
		for (int j = 0; j < K; j++)
			p[j] = i;
		points.push_back(p);
	}
	
	KDTree<K> tree(points);

	for (size_t i = 0; i < points.size(); i++)
		ASSERT_EQUALS(points[i], tree.findNearestNeighbor(points[i]));
}

UNIT_TEST(testLinearNNS_1_10, 6, 4, 5000) { testLinearNNS<1>(10); }
UNIT_TEST(testLinearNNS_3_31, 6, 4, 5000) { testLinearNNS<3>(31); }
UNIT_TEST(testLinearNNS_2_14, 6, 4, 5000) { testLinearNNS<2>(14); }
#endif


#if MONAD_SPLIT
UNIT_TEST(testDeceptiveNNOneLevelCtor, 4, 4, 5000)
{
	double coords[6][2] = {{-15, 7}, {6, 7}, {-13, -1}, {-5, 0}, {14, -3}, {14, 2}};

	vector< Point<2> > points;
	for (int i = 0; i < 6; ++i)
		points.push_back(Point<2>(coords[i]));

	KDTree<2> tree(points);
	ASSERT_TREE_EQUALS(tree, "soln_testDeceptiveNNOneLevelCtor.out");
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testDeceptiveNNOneLevelNNS, 4, 3, 5000)
{
	double coords[6][2] = {{-15, 7}, {6, 7}, {-13, -1}, {-5, 0}, {14, -3}, {14, 2}};
	double targetCoords[2] = {-13,1};
	double expectedCoords[2] = {-13,-1};

	vector< Point<2> > points;
	for (int i = 0; i < 6; ++i)
		points.push_back(Point<2>(coords[i]));
	Point<2> target(targetCoords);
	Point<2> expected(expectedCoords);

	KDTree<2> tree(points);
	
	ASSERT_EQUALS(expected, tree.findNearestNeighbor(target));
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testMinesCtor, 4, 3, 5000)
{
	//                              NN
	double coords[10][2] = {{-8, 7}, {-6, 4}, {-5, 6}, {-3, 5}, {0, 7}, 
	                       {2, -7}, {3, 0}, {5, -4}, {6, -3}, {7, -6}};
	//                     M        M       M        M        M
	bool isMine[10] = { false, false, false, false, false, true, true, true, true, true };

	vector< Point<2> > points;
	for (int i = 0; i < 10; ++i)
		points.push_back(Point<2>(coords[i], isMine[i]));
	
	KDTree<2> tree(points);
	ASSERT_TREE_EQUALS(tree, "soln_testMinesCtor.out");
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testMinesNNS, 4, 4, 5000)
{
	//                              NN
	double coords[10][2] = {{-8, 7}, {-6, 4}, {-5, 6}, {-3, 5}, {0, 7}, 
	                       {2, -7}, {3, 0}, {5, -4}, {6, -3}, {7, -6}};
	//                     M        M       M        M        M
	bool isMine[10] = { false, false, false, false, false, true, true, true, true, true };
	double targetCoords[2] = {-7,5};
	double expectedCoords[2] = {-6,4};

	vector< Point<2> > points;
	for (int i = 0; i < 10; ++i)
		points.push_back(Point<2>(coords[i], isMine[i]));
	Point<2> target(targetCoords);
	Point<2> expected(expectedCoords);
	
	KDTree<2> tree(points);
	// Turn on land mines to make sure we don't step on them
	Point<2>::enable_mines = true;
	ASSERT_EQUALS(expected, tree.findNearestNeighbor(target));
	Point<2>::enable_mines = false;
}
#endif


#if MONAD_SPLIT
double deceptiveMinesCoords[20][2] = {
	{84, 44}, // mine
	{74, 0},  // mine
	{54, 62}, // mine
	{59, 0},  // mine
	{34, 15}, // mine
	{42, 63},
	{96, 56}, // mine
	{44, 79},
	{44, 43},
	{28, 10}, // mine
	{60, 30}, // mine
	{88, 72}, // mine
	{75, 68}, // mine
	{43, 65},
	{48, 0},  // mine
	{14, 15}, // mine
	{49, 83},
	{51, 35},
	{95, 50}, // mine
	{82, 20}};// mine
bool deceptiveMinesIsMine[20] = { 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1};

UNIT_TEST(testDeceptiveMinesCtor, 4, 3, 5000)
{
	double targetCoords[2] = {45, 59};
	double expectedCoords[2] = {42, 63};

	vector< Point<2> > points;
	for (int i = 0; i < 20; ++i)
		points.push_back(Point<2>(deceptiveMinesCoords[i], deceptiveMinesIsMine[i]));
	Point<2> target(targetCoords);
	Point<2> expected(expectedCoords);
	
	KDTree<2> tree(points);
	ASSERT_TREE_EQUALS(tree, "soln_testDeceptiveMinesCtor.out");
}

UNIT_TEST(testDeceptiveMinesNNS, 4, 5, 5000)
{
	double targetCoords[2] = {45, 59};
	double expectedCoords[2] = {42, 63};

	vector< Point<2> > points;
	for (int i = 0; i < 20; ++i)
		points.push_back(Point<2>(deceptiveMinesCoords[i], deceptiveMinesIsMine[i]));
	Point<2> target(targetCoords);
	Point<2> expected(expectedCoords);
	
	KDTree<2> tree(points);

	// Turn on land mines to make sure we don't step on them
	Point<2>::enable_mines = true;
	ASSERT_EQUALS(expected, tree.findNearestNeighbor(target));
	Point<2>::enable_mines = false;
}
#endif


#if MONAD_SPLIT
double tieBreakingCoords[14][3] = {
	{0, 0, 100}, // mine
	{0, 100, 100},  // mine
	{0, 50, 50},  // mine
	{0, 0, 50}, // mine
	{100, 0, 100}, // mine
	{100, 100, 0},
	{0, 0, 0},
	{0, 50, 0},  // mine
	{50, 0, 0}, // mine
	{50, 0, 50}, // mine
	{100, 0, 0}, // mine
	{50, 50, 0},
	{0, 100, 0},  // mine
	{50, 50, 50}
};

UNIT_TEST(testTieBreakingCtor, 4, 3, 5000)
{
	vector< Point<3> > points;
	for (int i = 0; i < 14; ++i)
		points.push_back(Point<3>(tieBreakingCoords[i]));
	
	KDTree<3> tree(points);
	ASSERT_TREE_EQUALS(tree, "soln_testTieBreakingCtor.out");
}

UNIT_TEST(testTieBreakingNNS, 4, 3, 5000)
{
	double targetCoords[3] = {50, 100, 0};
	double expectedCoords[3] = {0, 100, 0};
	double targetCoords2[3] = {14, 17, 20};
	double expectedCoords2[3] = {0, 0, 0};

	vector< Point<3> > points;
	for (int i = 0; i < 14; ++i)
		points.push_back(Point<3>(tieBreakingCoords[i]));
	Point<3> target(targetCoords);
	Point<3> expected(expectedCoords);
	Point<3> target2(targetCoords2);
	Point<3> expected2(expectedCoords2);
	
	KDTree<3> tree(points);

	// Turn on land mines to make sure we don't step on them
	Point<3>::enable_mines = true;
	ASSERT_EQUALS(expected,  tree.findNearestNeighbor(target));
	ASSERT_EQUALS(expected2, tree.findNearestNeighbor(target2));
	Point<3>::enable_mines = false;
}
#endif


#if MONAD_SPLIT
double leftRecurseCoords[10][3] = {
	{5, 3, 1},
	{3, 1, 10},
	{2, 0, 8},
	{4, 3, 0},
	{0, 2, 9},
	{10, 10, 10},
	{11, 11, 11},
	{12, 12, 12},
	{13, 13, 13},
	{14, 14, 14}
};

UNIT_TEST(testLeftRecurseCtor, 4, 3, 5000)
{
	double targetCoords[3] = {1, 1, 9};
	double expectedCoords[3] = {0, 2, 9};

	vector< Point<3> > points;
	for (int i = 0; i < 10; ++i)
		points.push_back(Point<3>(leftRecurseCoords[i]));
	Point<3> target(targetCoords);
	Point<3> expected(expectedCoords);
	
	KDTree<3> tree(points);
	ASSERT_TREE_EQUALS(tree, "soln_testLeftRecurseCtor.out");
}

UNIT_TEST(testLeftRecurseNNS, 4, 3, 5000)
{
	double targetCoords[3] = {1, 1, 9};
	double expectedCoords[3] = {0, 2, 9};

	vector< Point<3> > points;
	for (int i = 0; i < 10; ++i)
		points.push_back(Point<3>(leftRecurseCoords[i]));
	Point<3> target(targetCoords);
	Point<3> expected(expectedCoords);
	
	KDTree<3> tree(points);

	// Turn on land mines to make sure we don't step on them
	Point<3>::enable_mines = true;
	ASSERT_EQUALS(expected, tree.findNearestNeighbor(target));
	Point<3>::enable_mines = false;
}
#endif


#if MONAD_SPLIT
int32_t power(int32_t a, int32_t exp)
{
	int32_t val = 1;
	while (exp-- > 0)
		val *= a;
	return val;
}

int32_t digitof(int32_t val, int32_t digit, int32_t digitcount)
{
	int divby = power(10, digitcount - digit - 1);
	return (val / divby) % 10;
}

template <int K>
vector<Point<K> > makeFromRandom(uint32_t * array, bool * mines, size_t len)
{
	vector<Point<K> > points;
	points.reserve(len);
	
	for (size_t i = 0; i < len; i++)
	{
		double vals[K];
		for (size_t digit = 0; digit < K; digit++)
		{
			vals[digit] = digitof(array[i], digit, K);
		}
		points.push_back(Point<K>(vals, mines[i]));
	}

	return points;
}

uint32_t random1pts[] = { 44, 68, 151, 253, 258, 383, 594, 613, 631, 634, 665, 746, 756, 762, 793, 827, 847, 862, 896, 932 };
bool random1mines[] =   {  0,  0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };

UNIT_TEST(testRandom1Ctor, 4, 3, 5000)
{
	vector<Point<3> > point = makeFromRandom<3>(random1pts, random1mines, (sizeof random1pts) / (sizeof random1pts[0]));
	KDTree<3> tree(point); // separate from above to avoid pass-by-reference compile errors
	ASSERT_TREE_EQUALS(tree, "soln_testRandom1Ctor.out");
}

UNIT_TEST(testRandom1NNS, 4, 3, 5000)
{
	vector<Point<3> > point = makeFromRandom<3>(random1pts, random1mines, (sizeof random1pts) / (sizeof random1pts[0]));
	KDTree<3> tree(point); // separate from above to avoid pass-by-reference compile errors
	Point<3>::enable_mines = true;
	ASSERT_EQUALS(Point<3>(6, 3, 4), tree.findNearestNeighbor(Point<3>(4, 3, 6)));
	Point<3>::enable_mines = false;
	ASSERT_EQUALS(Point<3>(6, 3, 4), tree.findNearestNeighbor(Point<3>(5, 4, 3)));
	ASSERT_EQUALS(Point<3>(7, 9, 3), tree.findNearestNeighbor(Point<3>(7, 9, 2)));
}


uint32_t random2pts[] = { 89, 1800, 7297, 4917, 878, 836, 3409, 2404, 5896, 9614, 7215, 7082, 4513, 7783, 6113, 915, 1111, 5034, 8820, 5633, 5474, 452, 3950, 9442, 4571, 886, 5102, 28, 8416, 1193, 2562, 6993, 3535, 1377, 2644, 9232, 4011, 2558, 3671, 4260, 1576, 840, 6887, 3422, 4175, 5135, 8110, 582, 1916, 2088, 3579 };
bool random2mines[] =   {  0,    0,    0,    0,   0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0,    0,    0,    0,    0,    0,   0,    0,    0,    0,   0,    0,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0,    0,    0,    0,    0,    0,   0,    0,    0,    0 };

UNIT_TEST(testRandom2Ctor, 4, 3, 5000)
{
	vector<Point<4> > points = makeFromRandom<4>(random2pts, random2mines, (sizeof random2pts) / (sizeof random2pts[0]));
	KDTree<4> tree(points); // separate from above to avoid pass-by-reference compile errors
	ASSERT_TREE_EQUALS(tree, "soln_testRandom2Ctor.out");
}

UNIT_TEST(testRandom2NNS, 4, 3, 5000)
{
	vector<Point<4> > points = makeFromRandom<4>(random2pts, random2mines, (sizeof random2pts) / (sizeof random2pts[0]));
	KDTree<4> tree(points); // separate from above to avoid pass-by-reference compile errors
	ASSERT_EQUALS(Point<4>(0, 0, 2, 8), tree.findNearestNeighbor(Point<4>(3, 1, 2, 9)));
	ASSERT_EQUALS(Point<4>(6, 8, 8, 7), tree.findNearestNeighbor(Point<4>(9, 9, 7, 7)));
	ASSERT_EQUALS(Point<4>(5, 4, 7, 4), tree.findNearestNeighbor(Point<4>(5, 4, 8, 3)));
}
#endif

#endif

#if MP_PART(2)

#if MONAD_SPLIT
#include "maptiles.h"
#include "maptiles.cpp"

TileImage tileFromRGB(int red, int green, int blue)
{
	PNG bmp(1, 1);
	*bmp(0, 0) = RGBAPixel(red, green, blue);
	return TileImage(bmp);
}

UNIT_TEST(testCheckeredMosaic, 0, 12, 5000)
{
	PNG sourcePNG("testsource.png");
	SourceImage source(sourcePNG, 8);

	vector<TileImage> tileList;
	tileList.push_back(tileFromRGB(255, 0, 0));
	tileList.push_back(tileFromRGB(0, 255, 0));
	tileList.push_back(tileFromRGB(0, 0, 255));

	MosaicCanvas* canvas = mapTiles(source, tileList);
	if (canvas == NULL)
		FAIL("ERROR: Returned NULL MosaicCanvas when shouldn't have");

	PNG soln_testmaptiles("soln_testmaptiles.png");
	ASSERT(canvas->drawMosaic(10) == soln_testmaptiles);

	delete canvas;
}

UNIT_TEST(testPrimaryColorMosaic, 0, 6, 5000)
{
	PNG sourcePNG(3, 3);
	*sourcePNG(0, 0) = RGBAPixel(45, 99, 180);
	*sourcePNG(0, 1) = RGBAPixel(200, 3, 109);
	*sourcePNG(0, 2) = RGBAPixel(1, 2, 3);
	*sourcePNG(1, 0) = RGBAPixel(100, 200, 44);
	*sourcePNG(1, 1) = RGBAPixel(255, 0, 130);
	*sourcePNG(1, 2) = RGBAPixel(192, 73, 0);
	*sourcePNG(2, 0) = RGBAPixel(90, 40, 230);
	*sourcePNG(2, 1) = RGBAPixel(160, 130, 110);
	*sourcePNG(2, 2) = RGBAPixel(90, 200, 60);
	SourceImage source(sourcePNG, sourcePNG.width());

	vector<TileImage> tileList;
	tileList.push_back(tileFromRGB(64, 64, 64));
	tileList.push_back(tileFromRGB(191, 64, 64));
	tileList.push_back(tileFromRGB(64, 191, 64));
	tileList.push_back(tileFromRGB(64, 64, 191));
	tileList.push_back(tileFromRGB(191, 191, 64));
	tileList.push_back(tileFromRGB(191, 64, 191));
	tileList.push_back(tileFromRGB(64, 191, 191));
	tileList.push_back(tileFromRGB(191, 191, 191));

	MosaicCanvas* canvas = mapTiles(source, tileList);
	if (canvas == NULL)
		FAIL("ERROR: Returned NULL MosaicCanvas when shouldn't have");

	ASSERT_EQUALS(RGBAPixel(64, 64, 191), canvas->getTile(0, 0).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(64, 191, 64), canvas->getTile(0, 1).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(64, 64, 191), canvas->getTile(0, 2).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(191, 64, 64), canvas->getTile(1, 0).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(191, 64, 191), canvas->getTile(1, 1).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(191, 191, 64), canvas->getTile(1, 2).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(64, 64, 64), canvas->getTile(2, 0).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(191, 64, 64), canvas->getTile(2, 1).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(64, 191, 64), canvas->getTile(2, 2).getAverageColor());

	delete canvas;
}

UNIT_TEST(testRandomMosaic, 0, 6, 5000)
{
	PNG sourcePNG(4, 4);
	*sourcePNG(0, 0) = RGBAPixel(178, 193, 119);
	*sourcePNG(0, 1) = RGBAPixel(168, 113, 20);
	*sourcePNG(0, 2) = RGBAPixel(90, 27, 141);
	*sourcePNG(0, 3) = RGBAPixel(137, 197, 162);
	*sourcePNG(1, 0) = RGBAPixel(211, 128, 242);
	*sourcePNG(1, 1) = RGBAPixel(211, 128, 242);
	*sourcePNG(1, 2) = RGBAPixel(248, 76, 27);
	*sourcePNG(1, 3) = RGBAPixel(208, 133, 253);
	*sourcePNG(2, 0) = RGBAPixel(74, 180, 7);
	*sourcePNG(2, 1) = RGBAPixel(17, 40, 216);
	*sourcePNG(2, 2) = RGBAPixel(173, 83, 238);
	*sourcePNG(2, 3) = RGBAPixel(161, 49, 81);
	*sourcePNG(3, 0) = RGBAPixel(176, 252, 255);
	*sourcePNG(3, 1) = RGBAPixel(186, 245, 238);
	*sourcePNG(3, 2) = RGBAPixel(156, 70, 85);
	*sourcePNG(3, 3) = RGBAPixel(78, 139, 46);
	SourceImage source(sourcePNG, sourcePNG.width());

	vector<TileImage> tileList;
	tileList.push_back(tileFromRGB(207, 146, 140));
	tileList.push_back(tileFromRGB(33, 73, 16));
	tileList.push_back(tileFromRGB(79, 225, 41));
	tileList.push_back(tileFromRGB(201, 123, 46));
	tileList.push_back(tileFromRGB(20, 247, 58));
	tileList.push_back(tileFromRGB(79, 242, 189));
	tileList.push_back(tileFromRGB(90, 198, 130));
	tileList.push_back(tileFromRGB(107, 185, 96));
	tileList.push_back(tileFromRGB(126, 218, 42));
	tileList.push_back(tileFromRGB(99, 200, 238));
	tileList.push_back(tileFromRGB(145, 206, 166));
	tileList.push_back(tileFromRGB(234, 176, 169));
	tileList.push_back(tileFromRGB(156, 223, 8));
	tileList.push_back(tileFromRGB(51, 203, 32));
	tileList.push_back(tileFromRGB(129, 192, 117));
	tileList.push_back(tileFromRGB(113, 24, 90));
	tileList.push_back(tileFromRGB(78, 177, 208));
	tileList.push_back(tileFromRGB(162, 126, 168));
	tileList.push_back(tileFromRGB(50, 191, 245));
	tileList.push_back(tileFromRGB(162, 173, 205));
	tileList.push_back(tileFromRGB(184, 160, 19));
	tileList.push_back(tileFromRGB(48, 213, 205));

	MosaicCanvas* canvas = mapTiles(source, tileList);
	if (canvas == NULL)
		FAIL("ERROR: Returned NULL MosaicCanvas when shouldn't have");

	ASSERT_EQUALS(RGBAPixel(129, 192, 117), canvas->getTile(0, 0).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(162,173,205), canvas->getTile(0, 1).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(51,203,32), canvas->getTile(0, 2).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(99,200,238), canvas->getTile(0, 3).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(201,123,46), canvas->getTile(1, 0).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(162,173,205), canvas->getTile(1, 1).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(78,177,208), canvas->getTile(1, 2).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(162,173,205), canvas->getTile(1, 3).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(113,24,90), canvas->getTile(2, 0).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(201,123,46), canvas->getTile(2, 1).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(162,126,168), canvas->getTile(2, 2).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(113,24,90), canvas->getTile(2, 3).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(145,206,166), canvas->getTile(3, 0).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(162,173,205), canvas->getTile(3, 1).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(113,24,90), canvas->getTile(3, 2).getAverageColor());
	ASSERT_EQUALS(RGBAPixel(51,203,32), canvas->getTile(3, 3).getAverageColor());

	delete canvas;
}
#endif

#endif
