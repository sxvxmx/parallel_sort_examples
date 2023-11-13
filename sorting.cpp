#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

void bubsort(vector<int>& v){
    for(int i = 0;i<v.size();i++){
        for(int o = 0;o<v.size()-1;o++)
            if(v[o] > v[o+1])
                swap(v[o],v[o+1]);
    }
}

void oesort(vector<int>& v){
    for (size_t i = 0; i < v.size(); i++) {
	    // (i % 2) ? 0 : 1 возвращает 1, если i четное, 0, если i не четное (установка начальной итерации)
        #pragma omp parallel for
		for (size_t j=(i % 2)?0:1; j < v.size()-1; j+=2)
			if (v[j] > v[j + 1])
				std::swap(v[j], v[j + 1]);
	}
}

void mergesort(vector<int>& a){
    int l = a.size();
	for (int BlockSizeIterator = 1; BlockSizeIterator < l; BlockSizeIterator *= 2){
		for (int BlockIterator = 0; BlockIterator < l - BlockSizeIterator; BlockIterator += 2 * BlockSizeIterator){
			//Производим слияние с сортировкой пары блоков начинающуюся с элемента BlockIterator
			//левый размером BlockSizeIterator, правый размером BlockSizeIterator или меньше
			int LeftBlockIterator = 0;
			int RightBlockIterator = 0;
			int LeftBorder = BlockIterator;
			int MidBorder = BlockIterator + BlockSizeIterator;
			int RightBorder = BlockIterator + 2 * BlockSizeIterator;
			RightBorder = (RightBorder < l) ? RightBorder : l;
			int* SortedBlock = new int[RightBorder - LeftBorder];

			//Пока в обоих массивах есть элементы выбираем меньший из них и заносим в отсортированный блок
			while (LeftBorder + LeftBlockIterator < MidBorder && MidBorder + RightBlockIterator < RightBorder){
				if (a[LeftBorder + LeftBlockIterator] < a[MidBorder + RightBlockIterator]){
					SortedBlock[LeftBlockIterator + RightBlockIterator] = a[LeftBorder + LeftBlockIterator];
					LeftBlockIterator += 1;
				}
				else{
					SortedBlock[LeftBlockIterator + RightBlockIterator] = a[MidBorder + RightBlockIterator];
					RightBlockIterator += 1;
				}
			}
			//После этого заносим оставшиеся элементы из левого или правого блока
			while (LeftBorder + LeftBlockIterator < MidBorder){
				SortedBlock[LeftBlockIterator + RightBlockIterator] = a[LeftBorder + LeftBlockIterator];
				LeftBlockIterator += 1;
			}
			while (MidBorder + RightBlockIterator < RightBorder){
				SortedBlock[LeftBlockIterator + RightBlockIterator] = a[MidBorder + RightBlockIterator];
				RightBlockIterator += 1;
			}
			for (int MergeIterator = 0; MergeIterator < LeftBlockIterator + RightBlockIterator; MergeIterator++){
				a[LeftBorder + MergeIterator] = SortedBlock[MergeIterator];
			}
		}
	}
}

void mergesort_p(vector<int>& a){
    int l = a.size();
	for (int BlockSizeIterator = 1; BlockSizeIterator < l; BlockSizeIterator *= 2){
		#pragma omp for nowait
		for (int BlockIterator = 0; BlockIterator < l - BlockSizeIterator; BlockIterator += 2 * BlockSizeIterator){
			//Производим слияние с сортировкой пары блоков начинающуюся с элемента BlockIterator
			//левый размером BlockSizeIterator, правый размером BlockSizeIterator или меньше
			int LeftBlockIterator = 0;
			int RightBlockIterator = 0;
			int LeftBorder = BlockIterator;
			int MidBorder = BlockIterator + BlockSizeIterator;
			int RightBorder = BlockIterator + 2 * BlockSizeIterator;
			RightBorder = (RightBorder < l) ? RightBorder : l;
			int* SortedBlock = new int[RightBorder - LeftBorder];

			//Пока в обоих массивах есть элементы выбираем меньший из них и заносим в отсортированный блок
			while (LeftBorder + LeftBlockIterator < MidBorder && MidBorder + RightBlockIterator < RightBorder){
				if (a[LeftBorder + LeftBlockIterator] < a[MidBorder + RightBlockIterator]){
					SortedBlock[LeftBlockIterator + RightBlockIterator] = a[LeftBorder + LeftBlockIterator];
					LeftBlockIterator += 1;
				}
				else{
					SortedBlock[LeftBlockIterator + RightBlockIterator] = a[MidBorder + RightBlockIterator];
					RightBlockIterator += 1;
				}
			}
			//После этого заносим оставшиеся элементы из левого или правого блока
			while (LeftBorder + LeftBlockIterator < MidBorder){
				SortedBlock[LeftBlockIterator + RightBlockIterator] = a[LeftBorder + LeftBlockIterator];
				LeftBlockIterator += 1;
			}
			while (MidBorder + RightBlockIterator < RightBorder){
				SortedBlock[LeftBlockIterator + RightBlockIterator] = a[MidBorder + RightBlockIterator];
				RightBlockIterator += 1;
			}
			for (int MergeIterator = 0; MergeIterator < LeftBlockIterator + RightBlockIterator; MergeIterator++){
				a[LeftBorder + MergeIterator] = SortedBlock[MergeIterator];
			}
		}
	}
}

int partition(vector<int>& a, int start, int end){
    int pivot = a[end];
    int pIndex = start;
    for (int i = start; i < end; i++){
        if (a[i] <= pivot){
            swap(a[i], a[pIndex]);
            pIndex++;
        }
    }
    swap (a[pIndex], a[end]);
    return pIndex;
}

void iterativeQuicksort(vector<int>& v){
    vector<pair<int, int>> s;
    int start = 0;
    int end = v.size() - 1;
    s.push_back(make_pair(start, end));
    while(s.size() > 0){
        int m = s.size();
        for(int i = 0;i<m;i++){
            start = s[i].first, end = s[i].second;
            s[i].first = -1, s[i].second = -1;
            int pivot = partition(v, start, end);
            if (pivot - 1 > start) {
                s.push_back(make_pair(start, pivot - 1));
            }
            if (pivot + 1 < end) {
                s.push_back(make_pair(pivot + 1, end));
            }
        }
        while(s[0].first == -1 and s[0].second == -1 and s.size() > 0)
            s.erase(s.begin());
    }
}

void iterativeQuicksort_p(vector<int>& v){
    vector<pair<int, int>> s;
    int start = 0;
    int end = v.size() - 1;
    s.push_back(make_pair(start, end));
    while(s.size() > 0){
        int m = s.size();
		#pragma omp parallel for
        for(int i = 0;i<m;i++){
            int start = s[i].first;
			int end = s[i].second;
            s[i].first = -1, s[i].second = -1;
            int pivot = partition(v, start, end);
            if (pivot - 1 > start) {
				#pragma omp critical
                s.push_back(make_pair(start, pivot - 1));
            }
            if (pivot + 1 < end) {
				#pragma omp critical
                s.push_back(make_pair(pivot + 1, end));
            }
        }
        while(s[0].first == -1 and s[0].second == -1 and s.size() > 0)
            s.erase(s.begin());
    }
}

int main(){
	int n = 1000000;
	for(int i = 10;i<=n;i*=10){
		auto vec = create_vec(i,1);
		double t1 = omp_get_wtime();
		mergesort(vec);
		double t2 = omp_get_wtime();
		cout<<t2-t1<<",";
	}
}