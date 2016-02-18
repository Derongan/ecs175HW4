#include "graphics.h"

graphics::graphics(int width, int height)
{
	this->width = width;
	this->height = height;
	setColor(1, 1, 1);
	this->buffer = new float[this->width * this->height * 3];
	this->zbuffer = new float[this->width * this->height];
	this->clearZBuffer();
}

graphics::~graphics()
{
	delete[] this->buffer;
	delete[] this->zbuffer;
}

void graphics::setPixel(int x, int y)
{
	this->buffer[x * 3 + y * this->width * 3] = color[0];
	this->buffer[x * 3 + y * this->width * 3 + 1] = color[1];
	this->buffer[x * 3 + y * this->width * 3 + 2] = color[2];
}

void graphics::setColor(float r, float g, float b)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
}


//Taken from book
void graphics::bezier(float * points, int num)
{
	float u;

	int *C = new int[num];
	
	for (int i = 0; i < num; i++) {
		int k = i;
		C[i] = nCr(num-1, k);
	}

	float *pt = new float[2];

	for (int i = 0; i <= 1000; i++) {
		u = i / 1000.0;
		computeBez(u, pt, C, points, num);
		setPixel(pt[0], pt[1]);
	}

	delete[] C;
	delete[] pt;
}

void graphics::computeBez(float u, float res[2], int * C, float * points, int num)
{
	res[0] = res[1] = 0;

	int n = num - 1;
	float blend;

	for (int k = 0; k < num; k++) {
		blend = C[k] * pow(u, k)*pow(1 - u, n - k);
		res[0] += points[k*2] * blend;
		res[1] += points[k*2+1] * blend;
	}
}

void graphics::bLine(int x0, int y0, int xEnd, int yEnd) {
	int dx = xEnd - x0, dy = yEnd - y0;
	int fdx = fabs(dx), fdy = fabs(dy);
	int px = 2 * fdy - fdx, py = 2 * fdx - fdy;
	int x, y, i;

	//We have eight octants.
	//This can be reduced to four cases. 0 < m < 1.0, m > 1.0, m < -1.0, 0 > m > -1.0

	if (fdy <= fdx) {
		if (xEnd < x0) {
			x = xEnd;
			y = yEnd;
			xEnd = x0;
		}
		else {
			x = x0;
			y = y0;
		}

		this->setPixel(x, y);

		while (x < xEnd) {
			x++;
			if (px < 0) {
				px += 2 * fdy;
			}
			else {
				if ((dx>0 && dy>0) || (dx < 0 && dy < 0)) {
					y++;
				}
				else {
					y--;
				}
				px += 2 * (fdy - fdx);
			}
			this->setPixel(x, y);
		}
	}
	else {
		if (yEnd < y0) {
			x = xEnd;
			y = yEnd;
			yEnd = y0;
		}
		else {
			x = x0;
			y = y0;
		}

		this->setPixel(x, y);

		while (y < yEnd) {
			y++;
			if (py < 0) {
				py += 2 * fdx;
			}
			else {
				if ((dx>0 && dy>0) || (dx < 0 && dy < 0)) {
					x++;
				}
				else {
					x--;
				}
				py += 2 * (fdx - fdy);
			}
			this->setPixel(x, y);
		}
	}
}

float * graphics::getCurrentBuffer()
{
	return this->buffer;
}

void graphics::clearBuffer()
{
	for (int i = 0; i < this->width*this->height*3; i++) {
		this->buffer[i] = 0;
	}
}

void graphics::clearZBuffer()
{
	for (int i = 0; i < this->width*this->height; i++) {
		this->zbuffer[i] = 1.0;
	}
}

void graphics::fillPolygon(float *points, int num)
{
	int i, i1, i2;
	float minv;
	float ymax;
	float xmin;
	float dx;
	float dy;

	list* edgeTable = new list[this->height];
	
	//For every pair of points
	for (i = 0; i < num; i++){
		i1 = (i*2) % (num * 2);
		i2 = ((i + 1) * 2) % (num * 2);
		if (points[i1+1] - points[i2 + 1] == 0)
			continue;

		dx = points[i1] - points[i2];
		dy = points[i1 + 1] - points[i2 + 1];

		minv = dx / dy;
		ymax = fmax(points[i1 + 1], points[i2 + 1]);
		if (ymax == points[i1 + 1])
			xmin = points[i2];
		else
			xmin = points[i1];
		int test = (int)ceil((fmin(points[i1 + 1], points[i2 + 1]) - .5));
		edgeTable[(int)ceil((fmin(points[i1 + 1], points[i2 + 1])-.5))].add(ceil(ymax-.5), xmin, minv, dx, dy);
	}

	/*for (int i = 0; i < height; i++) {
		edgeTable[i].print();
	}*/

	list activeEdgeList = list();

	bool parity = false;
	Bucket* bucket;

	float last;

	int counterL = 0;
	int counterR = 0;

	for (i = 0; i < this->height; i++) {
		activeEdgeList.removeObsolete(i);
		activeEdgeList.prepend(&edgeTable[i]);
		activeEdgeList.sort();

		bucket = activeEdgeList.head;
		while(bucket) {
			if (parity) {
				//int r truncates the int. This means the left side is drawn if the edge is directly on the halfway
				//r<bucket->xmin + 1 will never draw on bucket->xmin if it is passed the .5
				for (int r = ceilf(last - .5); r+.5 < bucket->xmin; r++) {
					setPixel(r, i);
				}
			}
			last = bucket->xmin;
			parity = !parity;

			bucket->xmin += bucket->minv;

			//counterL += dx;
			bucket = bucket->next;
		}
	}

	delete[] edgeTable;
}

void graphics::strokePolygon(float * points, int num)
{
	for (int i = 0; i < num-1; i++) {
		this->bLine(points[i * 2], points[i * 2 + 1], points[(i + 1) * 2], points[(i + 1) * 2 + 1]);
	}
}

void graphics::fillPolygonZ(float *points, int num, float z)
{
	int i, i1, i2;
	float minv;
	float ymax;
	float xmin;
	float dx;
	float dy;

	list* edgeTable = new list[this->height];

	//For every pair of points
	for (i = 0; i < num; i++) {
		i1 = (i * 2) % (num * 2);
		i2 = ((i + 1) * 2) % (num * 2);
		if (points[i1 + 1] - points[i2 + 1] == 0)
			continue;

		dx = points[i1] - points[i2];
		dy = points[i1 + 1] - points[i2 + 1];

		minv = dx / dy;
		ymax = fmax(points[i1 + 1], points[i2 + 1]);
		if (ymax == points[i1 + 1])
			xmin = points[i2];
		else
			xmin = points[i1];
		int test = (int)ceil((fmin(points[i1 + 1], points[i2 + 1]) - .5));
		edgeTable[(int)ceil((fmin(points[i1 + 1], points[i2 + 1]) - .5))].add(ceil(ymax - .5), xmin, minv, dx, dy);
	}

	/*for (int i = 0; i < height; i++) {
	edgeTable[i].print();
	}*/

	list activeEdgeList = list();

	bool parity = false;
	Bucket* bucket;

	float last;

	int counterL = 0;
	int counterR = 0;

	for (i = 0; i < this->height; i++) {
		activeEdgeList.removeObsolete(i);
		activeEdgeList.prepend(&edgeTable[i]);
		activeEdgeList.sort();

		bucket = activeEdgeList.head;
		while (bucket) {
			if (parity) {
				//int r truncates the int. This means the left side is drawn if the edge is directly on the halfway
				//r<bucket->xmin + 1 will never draw on bucket->xmin if it is passed the .5
				for (int r = ceilf(last - .5); r + .5 < bucket->xmin; r++) {
					if (zbuffer[i*this->width + r] > z) {
						zbuffer[i*this->width + r] = z;
						setPixel(r, i);
					}
				}
			}
			last = bucket->xmin;
			parity = !parity;

			bucket->xmin += bucket->minv;

			//counterL += dx;
			bucket = bucket->next;
		}
	}

	delete[] edgeTable;
}

void graphics::fillPolygonPlanar(float *points, int num) {
	//There must be only three z values present or this fails very ungracefuly
	int i, i1, i2;
	float minv;
	float ymax;
	float xmin;
	float dx;
	float dy;

	float savedColor[3];

	savedColor[0] = color[0];
	savedColor[1] = color[1];
	savedColor[2] = color[2];

	applyTransformationMatrix(points, num);

	project(points, num);


	int oobr, oobl, oobt, oobb;
	oobr = oobl = oobt = oobb = 0;
	//Clip the polygon
	for (int i = 0; i < num; i++) {
		i1 = (i * 3);
		if (points[i1] < 0)
			oobl++;
		if (points[i1] > width)
			oobr++;
		if (points[i1+1] < 0)
			oobb++;
		if (points[i1+1] > height)
			oobt++;
	}

	//Everything is out of bounds
	if ((oobb == num || oobt == num) && (oobr == num || oobl == num))
		return;

	//Cheat and ignore anything outside of range
	if (oobb + oobt + oobr + oobl > 0)
		return;

	list* edgeTable = new list[this->height];

	float vectors[3][3];

	//For every pair of points
	for (i = 0; i < num; i++) {
		i1 = (i * 3) % (num * 3);
		i2 = ((i + 1) * 3) % (num * 3);

		//Lets figure out the plane now.
		if (i < 3){
			vectors[i][0] = points[i1] - points[i2];
			vectors[i][1] = points[i1 + 1] - points[i2 + 1];
			vectors[i][2] = points[i1 + 2] - points[i2 + 2];
		}

		if (points[i1 + 1] - points[i2 + 1] == 0)
			continue;

		dx = points[i1] - points[i2];
		dy = points[i1 + 1] - points[i2 + 1];

		minv = dx / dy;
		ymax = fmax(points[i1 + 1], points[i2 + 1]);
		if (ymax == points[i1 + 1])
			xmin = points[i2];
		else
			xmin = points[i1];
		int test = (int)ceil((fmin(points[i1 + 1], points[i2 + 1]) - .5));
		int yval = (int)ceil((fmin(points[i1 + 1], points[i2 + 1]) - .5));
		edgeTable[yval].add(ceil(ymax - .5), xmin, minv, dx, dy);
	}

	//Find the cross product of two of the vectors

	float A = vectors[0][1] * vectors[1][2] - vectors[0][2] * vectors[1][1];
	float B = -(vectors[0][0] * vectors[1][2] - vectors[0][2] * vectors[1][0]);
	float C = vectors[0][0] * vectors[1][1] - vectors[0][1] * vectors[1][0];

	float D = -(A*points[0] + B*points[1] + C*points[2]);

	/*for (int i = 0; i < height; i++) {
	edgeTable[i].print();
	}*/

	list activeEdgeList = list();

	bool parity = false;
	Bucket* bucket;

	float last;

	int counterL = 0;
	int counterR = 0;

	for (i = 0; i < this->height; i++) {
		activeEdgeList.removeObsolete(i);
		activeEdgeList.prepend(&edgeTable[i]);
		activeEdgeList.sort();

		bucket = activeEdgeList.head;
		while (bucket) {
			if (parity) {
				//int r truncates the int. This means the left side is drawn if the edge is directly on the halfway
				//r<bucket->xmin + 1 will never draw on bucket->xmin if it is passed the .5
				int r = ceilf(last - .5);
				float z = ((-A*r) - B*i - D) / C;
				for (r; r + .5 < bucket->xmin; r++) {
					if (zbuffer[i*this->width + r] >= z) {
						zbuffer[i*this->width + r] = z;
						float modif = fmin(fmax(1 - z, 1 - z + .1), 1.0);
						setColor(modif*savedColor[0], modif*savedColor[1], modif*savedColor[2]);
						setPixel(r, i);
					}
					z -= A / C;
				}
			}
			last = bucket->xmin;
			parity = !parity;

			bucket->xmin += bucket->minv;

			//counterL += dx;
			bucket = bucket->next;
		}
	}

	setColor(savedColor[0], savedColor[1], savedColor[2]);
	delete[] edgeTable;
}

void graphics::applyTransformationMatrix(float * points, int num)
{
	for (int i = 0; i < num; i++) {
		int i1 = (i * 3) % (num * 3);
		points[i1] = points[i1] * transformationMatrix[0][0] + points[i1 + 1] * transformationMatrix[0][1] + points[i1 + 2] * transformationMatrix[0][2] + 1 * transformationMatrix[0][3];
		points[i1+1] = points[i1] * transformationMatrix[1][0] + points[i1 + 1] * transformationMatrix[1][1] + points[i1 + 2] * transformationMatrix[1][2] + 1 * transformationMatrix[1][3];
		points[i1+2] = points[i1] * transformationMatrix[2][0] + points[i1+1] * transformationMatrix[2][1] + points[i1 + 2] * transformationMatrix[2][2] + 1 * transformationMatrix[2][3];
	}
}

void graphics::addTransform(float matrix[][4])
{
	float product[4][4] = { 0 };
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			for (int inner = 0; inner < 4; inner++) {
				product[row][col] += matrix[row][inner] * transformationMatrix[inner][col];
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			transformationMatrix[i][j] = product[i][j];
		}
	}
}

void graphics::resetTransform()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			transformationMatrix[i][j] = resetMatrix[i][j];
		}
	}
}

void graphics::rotate(float x, float y, float theta)
{
	float translate[4][4] = {
		{ 1,0,0,-x },
		{ 0,1,0,-y },
		{ 0,0,1,0 },
		{ 0,0,0,1 }
	};

	float rotate[4][4] = {
		{ cosf(theta),-sinf(theta),0,0 },
		{ sinf(theta),cosf(theta),0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 }
	};


	float translate2[4][4] = {
		{ 1,0,0,x },
		{ 0,1,0,y },
		{ 0,0,1,0 },
		{ 0,0,0,1 }
	};

	addTransform(translate);
	addTransform(rotate);
	addTransform(translate2);
}

void graphics::translate(float x, float y, float z)
{
	float translate[4][4] = {
		{ 1,0,0,x },
		{ 0,1,0,y },
		{ 0,0,1,z },
		{ 0,0,0,1 }
	};

	addTransform(translate);
}

void graphics::setViewPoint(float x, float y, float z)
{
	viewPoint[0] = x;
	viewPoint[1] = y;
	viewPoint[2] = z;
}

void graphics::setViewUp(float dx, float dy, float dz)
{
	viewUp[0] = dx;
	viewUp[1] = dy;
	viewUp[2] = dz;
}

void graphics::setZView(float dx, float dy, float dz)
{
	zView[0] = dx;
	zView[1] = dy;
	zView[2] = dz;
}

void graphics::project(float* points, int num)
{
	float zvp = -1;
	for (int i = 0; i < num; i++) {
		int i1 = i * 3;
		points[i1] = points[i1] * (viewPoint[2] / (viewPoint[2] - points[i1 + 2])) + viewPoint[0] * (-points[i1 + 2] / (viewPoint[2] - points[i1 + 2]));
		points[i1+1] = points[i1+1] * (viewPoint[2] / (viewPoint[2] - points[i1 + 2])) + viewPoint[1] * (-points[i1 + 2] / (viewPoint[2] - points[i1 + 2]));
	}
}

unsigned int graphics::factorial(unsigned int n)
{
	if (n == 0) {
		return 1;
	}
	unsigned int ret = 1;
	for (unsigned int i = 1; i <= n; ++i)
		ret *= i;
	return ret;
}

unsigned int graphics::nCr(unsigned int n, unsigned int r)
{
	return factorial(n) / (factorial(r)*factorial(n - r));
}
