#pragma once
#include<malloc.h>
void Selection_Sort(int arr[], int n) {		//��������
	int min,tmp;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j =i+1; j <n; j++) {
			if (arr[j] < arr[min]) {
				min=j;
			}
		}
		tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
	}
}
void Bubble_Sort(int arr[], int n) {		//��������
	int tmp;
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}
void Insertion_Sort(int arr[], int n) {		//��������
	int key, j;
	for (int i = 1; i < n; i++) {
		key = arr[i];
		for (j = i - 1; j >= 0 && arr[j] > key; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}
void merge(int arr[], int left, int mid, int right) {	//�պ�
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));
	for (i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];
	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
	free(L);
	free(R);
}
void Merge_Sort(int arr[], int left, int right) {	//��������
	if (left < right) {
		int mid = left + (right - left) / 2;
		Merge_Sort(arr, left, mid);
		Merge_Sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
void Quick_Sort(int arr[], int L, int R) {			//������
	int left = L, right = R;
	int pivot = arr[(L + R) / 2];
	int temp;
	while (left <= right) {
		while (arr[left] < pivot)
			left++;
		while (arr[right] > pivot)
			right--;
		if (left <= right){
			temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
			left++;
			right--;
		}
	}
	if (L < right)
		Quick_Sort(arr, L, right);
	if (left < R)
		Quick_Sort(arr, left, R);
}
void Radix_Sort(int arr[], int n) {			//�������
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	for (int exp = 1; max / exp > 0; exp *= 10) {
		int* output = (int*)malloc(n * sizeof(int));
		int count[10] = { 0 };
		for (int i = 0; i < n; i++) {
			count[(arr[i] / exp) % 10]++;
		}
		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}
		for (int i = n - 1; i >= 0; i--) {
			output[count[(arr[i] / exp) % 10] - 1] = arr[i];
			count[(arr[i] / exp) % 10]--;
		}
		for (int i = 0; i < n; i++) {
			arr[i] = output[i];
		}
		free(output);
	}
}
void Counting_Sort(int arr[], int n) {		//�������
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}

	}
	int* countingArray = (int*)malloc((max + 1) * sizeof(int));
	for (int i = 0; i <= max; i++) {
		countingArray[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		countingArray[arr[i]]++;
	}
	int index = 0;
	for (int i = 0; i <= max; i++) {
		while (countingArray[i] > 0) {
			arr[index] = i;
			index++;
			countingArray[i]--;
		}
	}
	free(countingArray);
}

void heapify(int arr[], int n, int i) {
	int largest = i;  // �ִ밪�� ���� ���� �ʱ�ȭ
	int left = 2 * i + 1;  // ���� �ڽ� ���
	int right = 2 * i + 2;  // ������ �ڽ� ���

	// ���� �ڽ��� ��Ʈ���� ũ�ٸ� largest�� ������Ʈ
	if (left < n && arr[left] > arr[largest])
		largest = left;

	// ������ �ڽ��� ��Ʈ���� ũ�ٸ� largest�� ������Ʈ
	if (right < n && arr[right] > arr[largest])
		largest = right;

	// largest�� ���� ��尡 �ƴ϶�� ��带 ��ȯ�ϰ� heapify�� ��������� ȣ��
	if (largest != i) {
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		heapify(arr, n, largest);
	}
}

// �� ������ �����ϴ� �Լ�
void Heap_Sort(int arr[], int n) {			//������
	// ���� ����
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// ������ ��Ҹ� �ϳ��� ������ ����
	for (int i = n - 1; i > 0; i--) {
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
// �ִ밪�� �迭 ������ �̵�
		heapify(arr, i, 0);      // ���� �ٽ� ����
	}
}

