#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef header_h
#define header_h

struct translation {
	string mainWord;
	string definition;
};

template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
	Comparable element;
	BinaryNode  *left;
	BinaryNode  *right;

	BinaryNode( const Comparable & theElement,
		BinaryNode *lt, BinaryNode *rt )
		: element( theElement ), left( lt ), right( rt ) { }

	friend class BinarySearchTree<Comparable>;
};


template <class Comparable>
class BinarySearchTree
{
public:
	explicit BinarySearchTree( const Comparable & notFound );
	BinarySearchTree( const BinarySearchTree & rhs );
	~BinarySearchTree( );

	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const;
	Comparable  find( const string & x ) const;
	bool isEmpty( ) const;
	void printTree( ) const;

	void makeEmpty( );
	void insert( const Comparable & x );
	void remove( const Comparable & x );

	const BinarySearchTree & operator=( const BinarySearchTree & rhs );
	void findAndChange( const string & x , string toChange);

private:
	BinaryNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;
	const Comparable & elementAt( BinaryNode<Comparable> *t ) const;

	void insert( const Comparable & x,  BinaryNode<Comparable> * & t ) const;
	void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * find(const string & x,
		BinaryNode<Comparable> *t ) const;
	void makeEmpty( BinaryNode<Comparable> * & t ) const;
	void printTree( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;
};


template <class Comparable>
void BinarySearchTree<Comparable>::findAndChange( const string & x , string toChange)
{
	static BinaryNode<Comparable> *a = root;
	if( x < a->element.mainWord ){
		a = a->left ;
		findAndChange( x, toChange );

	}
	else if( a->element.mainWord < x ){
		a = a->right ;
		findAndChange( x, toChange );
	}
	else{
		toChange = toChange.replace(toChange.begin(), toChange.end(), L' ', L',');
		a->element.definition = a->element.definition + ", ";    // Match
		a->element.definition =a->element.definition+ toChange;
		a = root;
	}
}

/**
* Construct the tree.
*/
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable & notFound ) :
	ITEM_NOT_FOUND( notFound ), root( NULL )
{}

/**
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::
	elementAt( BinaryNode<Comparable> *t ) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}


/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable>
Comparable BinarySearchTree<Comparable>::find( const string & x ) const
{
	return elementAt( find( x, root ) );
}

/**
* Internal method to find an item in a subtree.
* x is item to search for.
* t is the node that roots the tree.
* Return node containing the matched item.
*/
template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::find(const string & x, BinaryNode<Comparable> *t ) const
{
	if( t == NULL )
		return NULL;
	else if( x < t->element.mainWord )
		return find( x, t->left );
	else if( t->element.mainWord < x )
		return find( x, t->right );
	else
		return t;    // Match
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin( ) const
{
	return elementAt( findMin( root ) );
}

/**
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t )const
{
	if( t == NULL )
		return NULL;
	if( t->left == NULL )
		return t;
	return findMin( t->left );
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{
	return elementAt( findMax( root ) );
}

/**
* Internal method to find the largest item in a subtree t.
* Return node containing the largest item.
*/
template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t )const
{
	if( t != NULL )
		while( t->right != NULL )
			t = t->right;
	return t;
}

/**
* Insert x into the tree; duplicates are ignored.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x )
{
	insert( x, root );
}

/** x
* Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::
	insert( const Comparable & x, BinaryNode<Comparable> * & t ) const
{
	if( t == NULL ) //  create a new node at the right place
		t = new BinaryNode<Comparable>( x, NULL, NULL );
	else if( x.mainWord < t->element.mainWord )
		insert( x, t->left );  // insert at the left or
	else if( t->element.mainWord < x.mainWord )
		insert( x, t->right );  // right subtree
	else
		;  // Duplicate; do nothing
}


/**
* Remove x from the tree. Nothing is done if x is not found.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x )
{
	remove( x, root );
}

/**
* Internal method to remove from a subtree.
* x is the item to remove.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode<Comparable> * & t ) const
{
	if( t == NULL )
		return;   // Item not found; do nothing
	if( x < t->element )
		remove( x, t->left );
	else if( t->element < x )
		remove( x, t->right );
	else if( t->left != NULL && t->right != NULL ) // Two children
	{
		t->element = findMin( t->right )->element;
		remove( t->element, t->right );
	}
	else // one or no children
	{
		BinaryNode<Comparable> *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}
}

/**
* Make the tree logically empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
	makeEmpty( root );
}

/**
* Internal method to make subtree empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( BinaryNode<Comparable> * & t ) const
{
	if( t != NULL )
	{
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}
	t = NULL;
}

/*
* Internal method to print a subtree rooted at t in sorted order.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::printTree( BinaryNode<Comparable> *t ) const
{
	if( t != NULL )
	{
		printTree( t->left );
		cout << t->element.mainWord << "---->" << t->element.definition<< endl;
		printTree( t->right );
	}
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const {
	BinaryNode<Comparable> * temp = root;
	//if (temp->element == ITEM_NOT_FOUND) {
	if (root == NULL) {
		return true;
	}
	else
		return false;
}

/**
* Print the tree contents in sorted order.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::printTree( ) const
{
	if( isEmpty( ) )
		cout << "Empty tree" << endl;
	else
		printTree( root );
}

/**
* Destructor for the tree.
*/
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
	makeEmpty( );
}

/**
* Copy constructor.
*/
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :
	root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
	*this = rhs;
}
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////

bool isPrime ( int x ){ // return true if x is a prime number
	for(int i = 2; i <= x / 2; ++i)
	{
		if(x % i == 0)
		{
			return false;
		}
	}
	return true;
}

int nextPrime( int n ) // find next prime number
{
	if( n % 2 == 0 )
		n++;

	for( ; !isPrime( n ); n += 2 )
		;

	return n;
}


template <class HashedObj>
class HashTable
{

public:
	explicit HashTable(  HashedObj & notFound, int size = 53 );
	HashTable(  HashTable & rhs )
		: ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
		array( rhs.array ), currentSize( rhs.currentSize ) { }

	HashedObj & find(  HashedObj & x ) ;

	void makeEmpty( );
	void insert(  HashedObj & x );
	void remove(  HashedObj & x );
	unsigned int currentSize ;
	HashTable & operator=(  HashTable & rhs );
	vector<vector<HashedObj>> array;
private:


	HashedObj ITEM_NOT_FOUND;

	bool isActive( int currentPos ) ;
	unsigned int findPos(  HashedObj & x ) ;
	void rehash( );

	int hash( string key, int tableSize)
	{
		int hashVal=0;

		for(unsigned int i = 0; i < key.length() && i < 3 ; i++)
		{
			hashVal=37*hashVal+ (int)key[i]+ key.length();
		}
		hashVal = hashVal % array.size();
		return(hashVal);
	}
};

/**
* Construct the hash table.
*/
template <class HashedObj>
HashTable<HashedObj>::HashTable(  HashedObj & notFound,
								int size )
								: ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
{
	currentSize = 0;
}



/**
* Find item x in the hash table.
* Return the matching item, or ITEM_NOT_FOUND, if not found.
*/
template <class HashedObj>
HashedObj & HashTable<HashedObj>::find(  HashedObj & x )

{
	int currentPos = hash( x.mainWord, array.size() );
	for(unsigned int i = 0; i < array[currentPos].size(); i++)
	{
		if(array[currentPos][i].mainWord == x.mainWord)
		{
			return array[currentPos][i];
		}
	}
	return   ITEM_NOT_FOUND;
}
/**
* Insert item x into the hash table. If the item is
* already present, then do nothing.
*/
template <class HashedObj>
void HashTable<HashedObj>::insert(  HashedObj & x )
{
	// Insert x as active
	unsigned int currentPos =  hash( x.mainWord, array.size() );
	if(find(x).mainWord == "abcd")
	{
		array[ currentPos ].push_back(x);
		// enlarge the hash table if necessary
		if ( ++currentSize >= array.size( ) / 2 )
			rehash( );
	}
}

/**
* Expand the hash table.
*/
template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
	vector<vector<HashedObj>> oldArray = array;
	// Create new double-sized, empty table
	array.clear();
	array.resize( nextPrime( 2 * oldArray.size( ) ) );
	currentSize = 0;
	// Copy table over
	for ( unsigned int i = 0; i < oldArray.size( ); i++ )
	{
		for(unsigned int j = 0; j < oldArray[i].size(); j++)
		{

			insert(oldArray[i][j]);
		}
	}
	cout << "rehashed..." << endl;
	double loadFactor = double(currentSize)/double(array.size());
	cout << "previous table size: " << oldArray.size() << ", new table size: " << array.size() << ", current unique word count: " << currentSize << ", current load factor: <" << loadFactor << ">" <<endl;
}

#endif header_h
