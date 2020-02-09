#pragma once
#ifndef DSA_LIB_H
#define	DSA_LIB_H
#include <vector>

namespace DSAlib
{
	template <class T> class DynArray {
	private:
		T* A;
		int size, begA, endA;
		void create(int mem, int len, int beg) {
			if (mem < 1) mem = 1;
			if (len < 0) len = 0;
			size = mem;
			begA = beg;
			endA = beg + len;
			A = new T[mem];
		};
	public:
		DynArray() {
			create(1, 0, 0);
		};
		DynArray(int sz) {
			create(sz, sz, 0);
		};
		~DynArray() {
			delete[]A;
		};
		int lenght() { 
			return endA - begA; 
		};
		DynArray& clear() {
			delete[]A;
			create(1, 0, 0);
			return *this;
		};
		DynArray& init(int n) {
			delete[]A;
			create(n, n, 0)
			return *this;
		};
		DynArray& pushFront(T a) {
			if (begA == 0) {
				T* temp = A;
				create(size + lenght() / 2 + 1, lenght(), begA + lenght() / 2 + 1);
				for (int i = 0; i < lenght(); ++i) {
					A[begA + i] = temp[i];
				}
				delete[]temp
			}
			--begA;
			A[begA] = a;
			return *this;
		};
		DynArray& pushBack(T a) {
			if (endA == size) {
				T* temp = A;
				create(size + lenght() / 2 + 1, lenght(), begA);
				for (int i = begA; i < endA; ++i) {
					A[i] = temp[i];
				}
				delete[]temp
			}
			A[endA] = a;
			++endA;
			return *this;
		};
		T popFront() {
			if (begA > lenght())
			{
				T* temp = A;
				int begTemp = begA;
				create(size - begA, lenght(), 0);
				for (int i = 0; i < lenght(); ++i) {
					A[i] = temp[begTemp + 1];
				}
				delete[]temp;
			}
			if (lenght() > 0) ++begA;
			return A[begA - 1];
		};
		T popBack() {
			if (size - endA > lenght())
			{
				T* temp = A;
				create(endA, lenght(), begA);
				for (int i = begA; i < endA; ++i) {
					A[i] = temp[i];
				}
				delete[]temp;
			}
			if (lenght() > 0) --endA;
			return A[endA];
		};
		T& operator [] (int i) {
			if (i < 0) i = 0;
			else if (i >= lenght()) i = lenght() - 1;
			return A[begA + i];
		};
	};
	
	template <class T> class Matrix {
	private:
		std::vector<std::vector<T> > data;
	public:
		class BadSize { };
		Matrix(unsigned int nrows, unsigned int ncols) : data(nrows) {
			if (nrows == 0 || ncols == 0)
				throw BadSize();
			for (unsigned int i = 0; i < nrows; ++i)
				data[i].resize(ncols);
		};
		T& operator() (unsigned int row, unsigned int col) {
			if (row >= getNrows() || col >= getNcols()) throw BoundsViolation();
			return data[row][col];
		};
		T const& operator() (unsigned int row, unsigned int col) const {
			if (row >= getNrows() || col >= getNcols()) throw BoundsViolation();
			return data[row][col];
		};
		class BoundsViolation { };
		unsigned getNrows() const { return data.size(); };  // #rows in this matrix
		unsigned getNcols() const { return data[0].size(); };  // #columns in this matrix
	};

	template <class T> class LinkList {
	public:
		LinkList()
		{
			Size = 0;
			head = nullptr;
		};
		~LinkList() { clear(); };
		void popFront()						// delete the 1st elem of Linked List
		{
			Node<T> *temp = head;
			head = head->pNext;
			delete temp;
			Size--;
		};				
		void pushBack(T data)				// insert in the end of Linked List
		{        
			if (head == nullptr)
			{
				head = new Node<T>(data);
			}
			else 
			{
				Node<T> *current = this->head;

				while (current->pNext != nullptr)
				{
					current = current->pNext;
				}
				current->pNext = new Node<T>(data);
			}
			Size++;
		};
		void clear() 
		{
			while (Size)
			{
				popFront();
			}
		};
		int GetSize() { return Size; };
		T& operator[] (const unsigned int index) {
			
			unsigned int counter = 0;
			
			Node<T> *current = this->head;
			
			while (current != nullptr)
			{
				if (counter == index)
				{
					return current->data;
				}
				current = current->pNext;
				counter++;
			}
		};
		void pushFront(T data) 
		{
			head = new Node<T>(data, head);
			Size++;
		};
		void popBack() 
		{
			removeAt(Size - 1);
		};
		void insert(T data, unsigned int index) 
		{
			if (index == 0)
			{
				pushFront(data);
			}
			else
			{
				Node<T> *previous = this->head;
				
				for (int i = 0; i < index - 1; i++)
				{
					previous = previous->pNext;
				}

				Node<T> *newNode = new Node<T>(data, previous->pNext);
				previous->pNext = newNode;

				Size++;
			}
						
		};
		void removeAt(unsigned int index) 
		{
			if (index == 0)
			{
				popFront();
			}
			else
			{
				Node<T>* previous = this->head;

				for (int i = 0; i < index - 1; i++)
				{
					previous = previous->pNext;
				}

				Node<T> *toDelete = previous->pNext;
				previous->pNext = toDelete->pNext;
				delete toDelete;
				Size--;
			}
		};

	private:

		template <class T> class Node {
		public:
			Node* pNext;
				T data;
				Node(T data = T(), Node* pNext = nullptr) {
					this->data = data;
					this->pNext = pNext;
				}
		};
		unsigned int Size;
		Node<T> *head;
	};
	
	template <class T> class DoubleLinkList {
	public:
		DoubleLinkList() {
			Size = 0;
			head = nullptr;
			tail = nullptr;
		};
		~DoubleLinkList() { clear(); };
		
		int GetSize() { return Size; };
		void clear()
		{
			while (Size)
			{
				popFront();
			}
		};
		T& operator[] (const unsigned int index) {

			unsigned int counter = 0;

			Node<T>* current = this->head;

			while (current != nullptr)
			{
				if (counter == index)
				{
					return current->data;
				}
				current = current->pNext;
				counter++;
			}
		};

		void pushFront(T data)
		{
			Node<T>* newNode = new Node<T>(data);
			if (head == nullptr && tail == nullptr)
			{
				head = newNode;
				tail = newNode;
			}
			else
			{
				newNode->pNext = head;
				newNode->pPrevious = nullptr;
				head->pPrevious = newNode;
				head = newNode;
			}
			Size++;
		};
		void pushBack(T data)
		{
			Node<T>* newNode = new Node<T>(data);
			if (head == nullptr && tail == nullptr)
			{
				head = newNode;
				tail = newNode;
			}
			else
			{
				newNode->pPrevious = tail;
				newNode->pNext = nullptr;
				tail->pNext = newNode;
				tail = newNode;
			}
			Size++;
		};
		void Insert(T data, unsigned int index)
		{
			// Check if the index is out of bound
			if (index < 0 || index > Size)
				return;

			// If inserting a new Head
			if (index == 0)
			{
				pushFront(data);
				return;
			}
			// If inserting a new Tail
			else if (index == Size)
			{
				pushBack(data);
				return;
			}

			Node<T>* prevNode = head;
			for (int i = 0; i < index - 1; ++i)
			{
				prevNode = prevNode->pNext;
			}
			
			Node<T>* nextNode = prevNode->pNext;

			Node<T>* node = new Node<T>(data);
						
			node->pNext = nextNode;
			node->pPrevious = prevNode;
			prevNode->pNext = node;
			nextNode->pPrevious = node;

			Size++;

		};
		void popFront()
		{
			if (Size == 0)
				return;
			
			Node<T>* node = head;
			head = head->pNext;
			delete node;
			
			if (head != nullptr)
				head->pPrevious = nullptr;
			
			Size--;
		};
		void popBack()
		{
			if (Size == 0)
				return;
			
			if (Size == 1)
			{ 	popFront();
				return;
			}
			
			Node<T>* node = tail;
			tail = tail->pPrevious;
			tail->pNext = nullptr;
			delete node;
			
			Size--;
		};
		void removeAt(unsigned int index)
		{
			if (Size == 0)
				return;
			
			if (index < 0 || index >= Size)
				return;

			if (index == 0)
			{
				popFront();
				return;
			}

			else if (index == Size - 1)
			{
				popBack();
				return;
			}
			Node<T>* prevNode = head;
			for (int i = 0; i < index - 1; ++i)
			{
				prevNode = prevNode->pNext;
			}
			Node<T>* node = prevNode->pNext;
			Node<T>* nextNode = node->pNext;
			prevNode->pNext = nextNode;
			nextNode->pPrevious = prevNode;
			delete node;
			Size--;
		};
	private:
		template <class T> class Node {
		public:
			Node* pNext;
			Node* pPrevious;
			T data;
			Node(T data = T(), Node* pPrevious = nullptr, Node* pNext = nullptr)
			{
				this->data = data;
				this->pPrevious = pPrevious;
				this->pNext = pNext;
			}
		};
		
		unsigned int Size = NULL;
		
		Node<T>* head;
		Node<T>* tail;
	};

	template <class T> class Stack {

	public:
		Stack()
		{
			Size = 0;
			pTop = nullptr;
		};
		~Stack() { clear(); };
		int GetSize() { return Size; };
		T GetTopData() { return pTop->data; };
		bool IsEmpty()
		{
			return Size <= 0;
		};
		void clear()
		{
			while (Size)
			{
				Pop();
			}
		};
		void Push(T data)
		{
			Node<T>* newNode = new Node<T>(data);
			newNode->pNext = pTop;
			pTop = newNode;
			Size++;
		};
		void Pop()
		{
			if (IsEmpty())
				return;
			Node<T>* Node = pTop;
			pTop = pTop->pNext;
			delete Node;
			Size--;
		};

	private:		
		template <class T> class Node {
		public:
			Node* pNext;
			T data;
			Node(T data = T(), Node* pNext = nullptr)
			{
				this->data = data;
				this->pNext = pNext;
			}
		};
		unsigned int Size = NULL;
		Node<T>* pTop;

	};

	template <class T> class Queue {
	
	public:
		Queue()
		{
			Size = 0;
			pFront = nullptr;
			pBack = nullptr;
		};
		~Queue() {clear()};
		bool IsEmpty() 
		{
			return Size <= 0;
		};
		void clear()
		{
			while (Size)
			{
				Pop();
			}
		};
		T GetFrontData() {return pFront->data};
		void Push(T data)
		{
			Node<T>* newNode = new Node<T>(data);
			if (IsEmpty())
			{
				newNode->pNext = nullptr;
				pFront = newNode;
				pBack = pFront;
				
			}
			else
			{
				pBack->pNext = newNode;
				pBack = newNode;
			}
			Size++;
		};
		void Pop()
		{
			if (IsEmpty())
				return;
			Node<T>* Node = pFront;
			pFront = pFront->pNext;
			delete Node;
			Size--;
		};
	private:
		unsigned int Size = NULL;
		template <class T> class Node {
		public:
			Node* pNext;
			T data;
			Node(T data = T(), Node* pNext = nullptr)
			{
				this->data = data;
				this->pNext = pNext;
			}
		};
		Node<T>* pFront;
		Node<T>* pBack;

	};

	template <class T> class Deque {
	public:
		Deque() {
			Size = 0;
			head = nullptr;
			tail = nullptr;
		};
		~Deque() { clear(); };
		bool IsEmpty()
		{
			return Size <= 0;
		};
		int GetSize() { return Size; };
		void clear()
		{
			while (Size)
			{
				popFront();
			}
		};
		T GetFrontData() { return pFront->data };
		T GetBackData() { return pBack->data };
		void pushFront(T data)
		{
			Node<T>* newNode = new Node<T>(data);
			
			newNode->pNext = pFront;
			if (pFront != nullptr)
				pFront->pPrevious = newNode;
			
			pFront = newNode;
			
			if (IsEmpty())
				pBack = pFront;
			Size++;
		};
		void pushBack(T data)
		{
			if (IsEmpty())
			{
				pushFront(data);
				return;
			}

			Node<T>* newNode = new Node<T>(data);
			
			pBack->pNext = newNode;
			
			newNode->pPrevious = pBack;
			
			pBack = newNode;
			
			Size++;
		};
		
		void popFront()
		{
			if (IsEmpty())
				return;

			Node<T>* Node = pFront;
			pFront = pFront->pNext;
			delete Node;

			if (pFront != nullptr)
				pFront->pPrevious = nullptr;

			Size--;
		};
		void popBack()
		{
			if (Size == 0)
				return;

			if (Size == 1)
			{
				popFront();
				return;
			}

			Node<T>* Node = pBack;
			pBack = pBack->pPrevious;
			pBack->pNext = nullptr;
			delete Node;

			Size--;
		};
		
	private:
		template <class T> class Node {
		public:
			Node* pNext;
			Node* pPrevious;
			T data;
			Node(T data = T(), Node* pPrevious = nullptr, Node* pNext = nullptr)
			{
				this->data = data;
				this->pPrevious = pPrevious;
				this->pNext = pNext;
			}
		};
		unsigned int Size = NULL;
		Node<T>* pFront;
		Node<T>* pBack;
	};

	template <class T> class BinarySearchTree{
	public:
		BinarySearchTree() 
		{
			root = nullptr;
		};
		~BinarySearchTree()
		{
			
		};
		void Insert(T data)
		{
			PrivateInsert(root, data);
		};
		bool Search(T data)
		{
			TreeNode<T>* result = PrivateSearch(root, data);
			return result == nullptr ? 
				false : 
				true;
		};

	private:
		template <class T> class TreeNode
		{
		public:
			T data;
			TreeNode* pLeft;
			TreeNode* pRight;
			TreeNode* pParent;
			TreeNode(T data = T(), TreeNode* pLeft = nullptr, TreeNode* pRight = nullptr, TreeNode* pParent = nullptr) 
			{
				this->data = data;
				this->pLeft = pLeft;
				this->pRight = pRight;
				this->pParent = pParent;
			}
		};
		TreeNode<T>* root;

		TreeNode* PrivateInsert(TreeNode* node, T data)
		{
			if (node == nullptr)
			{
				node = new TreeNode<T>;
				node->data = data;
				node->pLeft = nullptr;
				node->pRight = nullptr;
				node->pParent = nullptr;
			}
			else if (node->data < data)
			{
				node->pRight = PrivateInsert(node->pRight, data);
				node->pRight->pParent = node;
			}
			else
			{
				node->pLeft = PrivateInsert(node->pLeft, data);
				node->pLeft->pParent = node;
			}

			return node;
		};
		TreeNode* PrivateSearch(TreeNode* node, T data)
		{
			if (node == nullptr)
				return nullptr;
			else if (node->data == data)
				return node;
			else if (node->data < data)
				return PrivateSearch(node->pRight, data);
			else
				return PrivateSearch(node->pLeft, data);
		};
	};
}

#endif