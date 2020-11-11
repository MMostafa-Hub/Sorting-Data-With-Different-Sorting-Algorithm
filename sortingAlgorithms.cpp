#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <algorithm>
#include <ctime>

#define lli long long int	

using namespace std;
using namespace std::chrono;
struct Timer
{
	time_point<steady_clock> start, end;
	duration<double> duration;
	Timer() : start(high_resolution_clock::now()) {}
	~Timer()
	{
		end = high_resolution_clock::now();
		duration = end - start;
		cout << duration.count() * 1000 << " ms\n";
	}
};
//////////////////////////////////////////////////////////////////*Quick Sort*//////////////////////////////////////////////////////////////////////////////////

lli partition(vector<lli>& vec, lli l, lli r)
{
	lli j = l;
	for (lli i = l + 1; i <= r; i++)
	{
		if (vec[i] <= vec[l])
		{
			swap(vec[j + 1], vec[i]);
			j++;
		}
	}
	swap(vec[l], vec[j]);
	return j;
}
void quickSort(vector<lli>& vec, lli l ,lli r)
{
	srand(time(NULL));
	if (l >= r) return;
	lli k = rand() % (r - l + 1) + l;
	swap(vec[l], vec[k]);
	while (l < r)
	{
		lli m = partition(vec, l, r);
		if (m - l < r - m)
		{
			quickSort(vec, l, m - 1);
			l = m + 1;
		}
		else
		{
			quickSort(vec, m + 1, r);
			r = m - 1;
		}
	}

}
///////////////////////////////////////////////////////////////////*Selection Sort*////////////////////////////////////////////////////////////////////////////

void selectionSort(vector<lli>& vec)
{
	for (lli i = 0; i < vec.size(); i++)
	{
		lli minIndex = i;
		for (lli j = i + 1; j < vec.size(); j++)
		{
			if (vec[j] < vec[minIndex]) minIndex = j;
		}
		swap(vec[i], vec[minIndex]);
	}
}
////////////////////////////////////////////////////////////////////*Merge Sort*////////////////////////////////////////////////////////////////////

vector<lli> Merge(vector<lli> a, vector<lli> b)
{

	vector<lli> D(a.size() + b.size());
	lli i = 0, j = 0, k = 0;
	while (i < a.size() && j < b.size())
	{
		if (a[i] < b[j])
		{
			D[k] = a[i];
			i++;
		}
		else
		{
			D[k] = b[j];
			j++;
		}
		k++;
	}

	while (i < a.size())
	{
		D[k] = a[i];
		i++;
		k++;
	}

	while (j < b.size())
	{
		D[k] = b[j];
		j++;
		k++;
	}

	return D;
}
vector<lli> MergeSort(vector<lli>& vec)
{
	if (vec.size() == 1) return vec;
	lli m = floor(vec.size() / 2);
	vector<lli> a(vec.begin(), vec.begin() + m);
	vector<lli> b(vec.begin() + m, vec.end());

	a = MergeSort(a);
	b = MergeSort(b);
	vec = Merge(a, b);
	return vec;
}	

//////////////////////////////////////////////////////////////////////*3-way Quick Sort*//////////////////////////////////////////////////////////////////////

void partition3(vector<lli>& a, lli l, lli r, lli &i, lli &j)
{
	i = l - 1, j = r;
	lli p = l - 1, q = r;
	lli v = a[r];

	while (true)
	{
		while (a[++i] < v);
		while (v < a[--j])
		{
			if (j == l)
				break;
		}
		if (i >= j) break;
		swap(a[i], a[j]);
		if (a[i] == v)
		{
			p++;
			swap(a[p], a[i]);
		}
		if (a[j] == v)
		{
			q--;
			swap(a[j], a[q]);
		}
	}
	
	swap(a[i], a[r]);
	
	j = i - 1;
	for (lli k = l; k < p; k++, j--)
		swap(a[k], a[j]);


	i++;
	for (lli k = r - 1; k > q; k--, i++)
		swap(a[i], a[k]);
}

void quickSort3(vector<lli>& vec, lli l, lli r)
{
	srand(time(NULL));
	if (l >= r) return;
	lli i = 0, j = 0;
	lli k = rand() % (r - l + 1) + l;
	swap(vec[l], vec[k]);
	partition3(vec, l, r, i, j);
	quickSort3(vec, l, j);
	quickSort3(vec, i, r);
}
//////////////////////////////////////////////////////////Heap Sorting////////////////////////////////////
class Heap
{
private:
	vector<lli> H;

	lli parent(lli i) { return (i - 1) / 2; }
	lli leftChild(lli i) { return (2 * i + 1); }
	lli rightChild(lli i) { return (2 * i + 2); }
	void siftUp(lli i)
	{
		while (i > 0 && H[parent(i)] < H[i])
		{
			swap(H[i], H[parent(i)]);
			i = parent(i);
		}
	}
	void siftDown(lli i)
	{
		lli maxIndex = i;
		lli l = leftChild(i);
		maxIndex = (l < H.size() && H[maxIndex] < H[l]) ? l : maxIndex;
		lli r = rightChild(i);
		maxIndex = (r < H.size() && H[maxIndex] < H[r]) ? r : maxIndex;
		if (i != maxIndex)
		{
			swap(H[maxIndex], H[i]);
			siftDown(maxIndex);
		}
	}
public:
	Heap(vector<lli> vec) : H(vec)
	{
		for (lli i = floor(vec.size() / 2); i <= 1; i--)
			siftDown(i);
	}
	Heap() {};
	void insert(lli num)
	{
		H.push_back(num);
		siftUp(H.size() - 1);
	}
	lli ExtractMax()
	{
		lli x = H[0];
		H[0] = H[H.size() - 1];
		H.pop_back();
		siftDown(0);
		return x;
	}
	void remove(lli i)
	{
		H[i] = LLONG_MAX;
		siftUp(i);
		ExtractMax();
	}
	void changePriority(lli i, lli p)
	{
		lli oldP = H[i];
		H[i] = p;
		if (oldP < p) siftUp(i);
		else siftDown(i);
	}
};
vector<lli> HeapSort(vector<lli> vec)
{
	Heap k;
	vector<lli> SortedVec(vec.size());
	for (lli i = 0; i < vec.size(); i++)
	{
		k.insert(vec[i]);
	}
	for (lli i = vec.size() - 1; i >= 0; i--)
	{
		SortedVec[i] = k.ExtractMax();
	}
	return SortedVec;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream& stream, const vector<lli>& vec)
{
	for (long long int i = 0; i < vec.size(); i++)
	{
		stream << vec[i] << " ";
	}
	cout << endl;
	return stream;
}
int main()
{
	cout << "Data size :";
	lli n,x;
	cin >> n;
	vector<lli> vec(n);
	cout << "Enter Data:\n";
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		vec[i] = x;
	}
	

	{
		
		Timer time;
		vector<lli> vecQuick = vec;
		quickSort(vecQuick, 0, vecQuick.size() - 1);
		cout << "Quick Sort:";
	}
	{
		
		Timer time;
		vector<lli> vecSelect = vec;
		selectionSort(vecSelect);
		cout << "Selection Sort:";
	}
	{
		Timer time;
		vector<lli> vecMerge = vec;
		MergeSort(vecMerge);
		cout << "Merge Sort:";
	}
	{
		Timer time;
		vector<lli> vec3WayQuick = vec;
		quickSort3(vec3WayQuick, 0, vec3WayQuick.size() - 1);
		cout << "3-way Quick Sort:";
	}
	{
		Timer time;
		vector<lli> vecHeap = vec;
		HeapSort(vecHeap);
		cout << "Heap Sort :";
	}
}