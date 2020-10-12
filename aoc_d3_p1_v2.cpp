#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>


//Function declarations
int stringConvert(std::string);


//Global variable and array declarations
std::vector<std::string> line1;
std::vector<std::string> line2;
long int line1Elements = 0;
long int line2Elements = 0;
long int count1 = 0;
long int count2 = 0;
long int oneRight = 0;
long int oneUp = 0;
long int twoRight = 0;
long int twoUp = 0;

struct segment
{
	int ax;
	int ay;
	int bx;
	int by;
	char orient;
};

struct coordpairs
{
	int x;
	int y;
};


int main()
{

	std::string instruction1 = "a";
	std::string instruction2 = "a";
	std::ifstream myfile1("example1.txt");
	std::ifstream myfile2("example2.txt");
	//Extract all the values from example 1 and populate a vector line1
	if (myfile1.is_open()) {
		while (getline(myfile1, instruction1, ',')) // This is really useful re-usable code for dragging things out of a file.
		{
			//std::cout << "Read: " << instruction1 << " from the file" << std::endl;
			line1.push_back(instruction1);
			//std::cout << "Read: " << instruction1 << " into the array." << std::endl;
			line1Elements = line1.size();
		}
		myfile1.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}

	//Extract all the values from example 2 and populate a vector line2
	if (myfile2.is_open()) {
		while (getline(myfile2, instruction2, ',')) // This is really useful re-usable code for dragging things out of a file.
		{
			//std::cout << "Read: " << instruction2 << " from the file" << std::endl;
			line2.push_back(instruction2);
			//std::cout << "Read: " << instruction2 << " into the array." << std::endl;
			line2Elements = line2.size();
		}
		myfile2.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}

	const long int sizeOfLine1 = line1.size();
	std::cout << "Line one contains: " << sizeOfLine1 << " elements." << std::endl;
	const long int sizeOfLine2 = line2.size();
	std::cout << "Line two contains: " << sizeOfLine2 << " elements." << std::endl;


	
		
	std::vector<segment> line1Segs;
	std::vector<segment> line2Segs;
	std::vector<segment> intersections1;
	std::vector<segment> intersections2;
	std::vector<coordpairs> coordpairs1;
	std::vector<coordpairs> coordpairs2;


	segment currentSegment1{0, 0, 0, 0, 'N'};
	segment currentSegment2{0, 0, 0, 0, 'N'};

	int ax = 0;
	int ay = 0;
	int bx = 0;
	int by = 0;
	int intersectCandidateCount = 0;
	int combinations = 0;

	while (count1 < sizeOfLine1)
	{
		//Line 1
		//Extract direction for this element
		char direction1 = line1[count1].at(0);
		//set element[0] to 0 to expunge the direction prior to conversion to int
		line1[count1].at(0) = '0';
		//Extract distance for this element 
		int distance1 = stringConvert(line1[count1]);


		//Determine which variable to update and update it.
		switch (direction1)
		{
		case 'U':
			currentSegment1.by += distance1;// Add the distance to the y coord of the b point.
			currentSegment1.orient = 'V';// Set the orientation for this segment
			line1Segs.push_back(currentSegment1); //Add the struct to the vector
			currentSegment1.ax = currentSegment1.bx; ////These two statements reset the segment start point to the previous segments endpoint.
			currentSegment1.ay = currentSegment1.by; //Only AFTER the current segment has been copied to the vector
			//std::cout << "Added A(" << line1Segs.back().ax << ", " << line1Segs.back().ay << "), B(" << line1Segs.back().bx << ", " << line1Segs.back().by << "), to line 1." << std::endl;
			break;
		case 'R':
			currentSegment1.bx += distance1;// Add the distance to the x coord of the b point.
			currentSegment1.orient = 'H';// Set the orientation for this segment
			line1Segs.push_back(currentSegment1); //Add the struct to the vector
			currentSegment1.ax = currentSegment1.bx; ////These two statements reset the segment start point to the previous segments endpoint.
			currentSegment1.ay = currentSegment1.by; //Only AFTER the current segment has been copied to the vector
			//std::cout << "Added A(" << line1Segs.back().ax << ", " << line1Segs.back().ay << "), B(" << line1Segs.back().bx << ", " << line1Segs.back().by << "), to line 1." << std::endl;
			break;
		case 'D':
			currentSegment1.by -= distance1;// Add the distance to the x coord of the b point.
			currentSegment1.orient = 'V';// Set the orientation for this segment
			line1Segs.push_back(currentSegment1); //Add the struct to the vector
			currentSegment1.ax = currentSegment1.bx; ////These two statements reset the segment start point to the previous segments endpoint.
			currentSegment1.ay = currentSegment1.by; //Only AFTER the current segment has been copied to the vector
			//std::cout << "Added A(" << line1Segs.back().ax << ", " << line1Segs.back().ay << "), B(" << line1Segs.back().bx << ", " << line1Segs.back().by << "), to line 1." << std::endl;
			break;
		case 'L':
			currentSegment1.bx -= distance1;// Add the distance to the x coord of the b point.
			currentSegment1.orient = 'H';// Set the orientation for this segment
			line1Segs.push_back(currentSegment1); //Add the struct to the vector
			currentSegment1.ax = currentSegment1.bx; ////These two statements reset the segment start point to the previous segments endpoint.
			currentSegment1.ay = currentSegment1.by; //Only AFTER the current segment has been copied to the vector
			//std::cout << "Added A(" << line1Segs.back().ax << ", " << line1Segs.back().ay << "), B(" << line1Segs.back().bx << ", " << line1Segs.back().by << "), to line 1." << std::endl;
			break;
		}

		count1++;

	}

	std::cout << "Line 1 contains: " << line1Segs.size() << " segments." << std::endl;

	while (count2 < sizeOfLine2)
	{
		//Line 2
		//std::cout << "Element: " << line2[count2] << ", of line 2 is " << line2[count2].size() << " characters long." << std::endl;
		//Extract direction for this element
		char direction2 = line2[count2].at(0);
		//set element[0] to 0 to expunge the direction prior to conversion to int
		line2[count2].at(0) = '0';
		//Extract distance for this element 
		int distance2 = stringConvert(line2[count2]);
		//std::cout << "Direction for this element of line 2 is " << direction2 << std::endl;
		//std::cout << "Distance for this element of line 2 is " << distance2 << std::endl;

		//Determine which variable to update and update it.
		switch (direction2)
		{
		case 'U':
			currentSegment2.by += distance2;// Add the distance to the y coord of the b point.
			currentSegment2.orient = 'V';// Set the orientation for this segment
			line2Segs.push_back(currentSegment2); //Add the struct to the vector
			currentSegment2.ax = currentSegment2.bx; ////These two statements reset the segment start point to the previous segments endpoint.
			currentSegment2.ay = currentSegment2.by; //Only AFTER the current segment has been copied to the vector
			//std::cout << "Added A(" << line2Segs.back().ax << ", " << line2Segs.back().ay << "), B(" << line2Segs.back().bx << ", " << line2Segs.back().by << "), to line 2." << std::endl;
			break;
		case 'R':
			currentSegment2.bx += distance2;// Add the distance to the x coord of the b point.
			currentSegment2.orient = 'H';// Set the orientation for this segment
			line2Segs.push_back(currentSegment2); //Add the struct to the vector
			currentSegment2.ax = currentSegment2.bx; ////These two statements reset the segment start point to the previous segments endpoint.
			currentSegment2.ay = currentSegment2.by; //Only AFTER the current segment has been copied to the vector
			//std::cout << "Added A(" << line2Segs.back().ax << ", " << line2Segs.back().ay << "), B(" << line2Segs.back().bx << ", " << line2Segs.back().by << "), to line 2." << std::endl;
			break;
		case 'D':
			currentSegment2.by -= distance2;// Add the distance to the x coord of the b point.
			currentSegment2.orient = 'V';// Set the orientation for this segment
			line2Segs.push_back(currentSegment2); //Add the struct to the vector
			currentSegment2.ax = currentSegment2.bx; ////These two statements reset the segment start point to the previous segments endpoint.
			currentSegment2.ay = currentSegment2.by; //Only AFTER the current segment has been copied to the vector
			//std::cout << "Added A(" << line2Segs.back().ax << ", " << line2Segs.back().ay << "), B(" << line2Segs.back().bx << ", " << line2Segs.back().by << "), to line 2." << std::endl;
			break;
		case 'L':
			currentSegment2.bx -= distance2;// Add the distance to the x coord of the b point.
			currentSegment2.orient = 'H';// Set the orientation for this segment
			line2Segs.push_back(currentSegment2); //Add the struct to the vector
			currentSegment2.ax = currentSegment2.bx; ////These two statements reset the segment start point to the previous segments endpoint.
			currentSegment2.ay = currentSegment2.by; //Only AFTER the current segment has been copied to the vector
			//std::cout << "Added A(" << line2Segs.back().ax << ", " << line2Segs.back().ay << "), B(" << line2Segs.back().bx << ", " << line2Segs.back().by << "), to line 2." << std::endl;
			break;
		}
		count2++;

	}

	std::cout << "Line 2 contains: " << line2Segs.size() << " segments." << std::endl;


	std::cout << "Comparing segments to find intersections" << std::endl;

	int line1SegsSize = line1Segs.size();
	int line2SegsSize = line2Segs.size();

	for (int i = 0; i < line1SegsSize; i++)
	{

		for (long int j = 0; j < line2SegsSize; j++)
		{
			

			if ((line1Segs[i].orient == 'V' && line2Segs[j].orient == 'V') || (line1Segs[i].orient == 'H' && line2Segs[j].orient == 'H'))
			{
				//std::cout << "These segments are both Horizontal or both Vertical. Moving on.." << std::endl;
			}	
			else if (line1Segs[i].orient == 'V' && line2Segs[j].orient == 'H') //ie L1 is vert and L2 is horiz
			{
				//std::cout << "Line 1 segment: A(" << line1Segs[i].ax << ", " << line1Segs[i].ay << "), B(" << line1Segs[i].bx << ", " << line1Segs[i].by
					//<< ") is vertical, and Line 2 segment: A(" << line2Segs[j].ax << ", " << line2Segs[j].ay << "), B(" << line2Segs[j].bx << ", " << line2Segs[j].by << ") is horizontal." << std::endl;
				
				if ((line1Segs[i].ax > std::min(line2Segs[j].ax, line2Segs[j].bx)) && line1Segs[i].ax < std::max(line2Segs[j].ax, line2Segs[j].bx) && (line2Segs[j].ay > std::min(line1Segs[i].ay, line1Segs[i].by)) && line2Segs[j].ay < std::max(line1Segs[i].ay, line1Segs[i].by))
				{
				//std::cout << "Intersection found with a vertical Line 1 and a horizontal line 2" << std::endl;
				//std::cout << "Line 1 segment: A(" << line1Segs[i].ax << ", " << line1Segs[i].ay << "), B(" << line1Segs[i].bx << ", " << line1Segs[i].by
					//<< ") (vertical), and Line 2 segment: A(" << line2Segs[j].ax << ", " << line2Segs[j].ay << "), B(" << line2Segs[j].bx << ", " << line2Segs[j].by << ") (horizontal) INTERSECT!!" << std::endl;
				intersections1.push_back(line1Segs[i]);
				intersections2.push_back(line2Segs[j]);
				intersectCandidateCount += 1;
				}
				
			}
			else if (line1Segs[i].orient == 'H' && line2Segs[j].orient == 'V') //ie L1 is horiz and L2 is vert
			{
				//std::cout << "Line 1 segment: A(" << line1Segs[i].ax << ", " << line1Segs[i].ay << "), B(" << line1Segs[i].bx << ", " << line1Segs[i].by
				//<< ") is horizontal, and Line 2 segment: A(" << line2Segs[j].ax << ", " << line2Segs[j].ay << "), B(" << line2Segs[j].bx << ", " << line2Segs[j].by << ") is vertical." << std::endl;
				
				if ((line2Segs[j].ax > std::min(line1Segs[i].ax, line1Segs[i].bx)) && line2Segs[j].ax < std::max(line1Segs[i].ax, line1Segs[i].bx) && (line1Segs[i].ay > std::min(line2Segs[j].ay, line2Segs[j].by)) && line1Segs[i].ay < std::max(line2Segs[j].ay, line2Segs[j].by))
				{
					//std::cout << "Intersection found with a horizontal Line 1 and a vertical line 2" << std::endl;
					//std::cout << "Line 1 segment: A(" << line1Segs[i].ax << ", " << line1Segs[i].ay << "), B(" << line1Segs[i].bx << ", " << line1Segs[i].by
						//<< ") (horizontal), and Line 2 segment: A(" << line2Segs[j].ax << ", " << line2Segs[j].ay << "), B(" << line2Segs[j].bx << ", " << line2Segs[j].by << ") (vertical) INTERSECT!!" << std::endl;
					intersections1.push_back(line1Segs[i]);
					intersections2.push_back(line2Segs[j]);
					intersectCandidateCount += 1;
				}
			}

			combinations += 1;
		}
		

	}

	for (unsigned int i = 0; i < intersections1.size(); i++)
	{
		std::cout << "Intersection " << i + 1 << ": " << "Line1: A(" << intersections1[i].ax << ", " << intersections1[i].ay << "), B(" << intersections1[i].bx << ", " << intersections1[i].by << "). Orientation: " << intersections1[i].orient << "." 
		" Line2: A(" << intersections2[i].ax << ", " << intersections2[i].ay << "), B(" << intersections2[i].bx << ", " << intersections2[i].by << "). Orientation: " << intersections2[i].orient << "." << std::endl;
	}
	std::cout << "Tested " << combinations << " combinations. Discovered " << intersectCandidateCount << " intersections." << std::endl;
	std::cout << "Program ends" << std::endl;


	//Copy all the coord pairs from all the points in intersections1 entry into a temporary comparison vector
	//Copy all the coord pairs from all the points in intersections2 entry into a temporary comparison vector
	//Compare the intersections1 and intersections2 coord pairs. Copy matching sets into an intersections pair vector
	//Sort the intersections pair vector to find the shortest manhattan distance
	//Profit

	std::cout << "Intersections1 array  contains " << intersections1.size() << " elements." << std::endl;
	std::cout << "Intersections2 array  contains " << intersections2.size() << " elements." << std::endl;


	return 0;

}


int stringConvert(std::string stringIn)
{
	int n = std::stoi(stringIn);
	//std::cout << "String conversion of " << n << " completed." << std::endl;
	return n;
}