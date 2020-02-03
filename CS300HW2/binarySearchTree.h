#include <iostream>
#include <string>

using namespace std;

#ifndef binarySearchTree_h
#define binarySearchTree_h

struct translation {
	wstring mainWord;
	wstring definition;

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
	Comparable  find( const wstring & x ) const;
	bool isEmpty( ) const;
	void printTree( ) const;

	void makeEmpty( );
	void insert( const Comparable & x );
	void remove( const Comparable & x );

	const BinarySearchTree & operator=( const BinarySearchTree & rhs );
	void findAndChange( const wstring & x , wstring toChange);

private:
	BinaryNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;
	const Comparable & elementAt( BinaryNode<Comparable> *t ) const;

	void insert( const Comparable & x,  BinaryNode<Comparable> * & t ) const;
	void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * find(const wstring & x,
		BinaryNode<Comparable> *t ) const;
	void makeEmpty( BinaryNode<Comparable> * & t ) const;
	void printTree( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;
};




template <class Comparable>
void BinarySearchTree<Comparable>::findAndChange( const wstring & x , wstring toChange)
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
		a->element.definition = a->element.definition + L", ";    // Match
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
Comparable BinarySearchTree<Comparable>::find( const wstring & x ) const
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
BinaryNode<Comparable> *BinarySearchTree<Comparable>::find(const wstring & x, BinaryNode<Comparable> *t ) const
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
		wcout << t->element.mainWord << L"---->" << t->element.definition<< endl;
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
		wcout << L"Empty tree" << endl;
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


#endif binarySearchTree_h
