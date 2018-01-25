/*
 *  dataTypes.h
 *  C Input-Output
 *
 *  Created by jean-yves hervé on 2009/02/09.
 *	Updated 2016-01-31, revised , revised 2018-01-24
 *
 */

//	You need to "protect" your header files against multiple loads
#ifndef DATA_TYPES_H
#define DATA_TYPES_H

//	 This data type is used for ascii I/O
typedef struct DataPoint {

	int		x;
	int		y;
	float	z;
	char	c[4];
} DataPoint;


//	This one is not used anywhere but I wanted to show you o
//	situation where a "forward declaration" is absolutely needed.
//
//	I want to create a "Node" type for my very own home-made double-linked
//	list.  Of course, a Node would need to store a pointer to a "next" Node and
//	to a "prev" Node.   However, the definition of the struct is not complete
//	until we close the }, which precludes something like this:
//
//	struct Node {
//      int data;
//      Node* next;    -----> Node is not defined (yet)
//      Node* prev;
//
//  }   ----> only at this point is Node actually defined
//	;   ----> [I separate the } from the ; because the definition ends at the } and
//		       the statement is terminated by the ;]
//
//	Adding a "typedef" does not solve the problem
//  I am going to give a different name to the typedef to distinguish the two
//	aspects:
//
//	typedef struct Node {
//      int data;
//      struct Node* next;   -----> Node is not defined (yet): error
//      NodeType* prev;      -----> NodeType is not defined either: error
//
//  }   ----> only at this point is Node actually defined
//	NodeType;    ----> NodeType is defined at this point
//
//
//	The solution is to provide a "forward" definition.  Basicaly you are saying
//	"trust me, Node is a struct, coming later"
//
//	struct Node; -----------------+
//                                |
//	typedef struct Node {         |
//      int data;                 |
//      struct Node* next;  -->  Node has been announced here as a struct
//      struct Node* prev;  -->  NodeType has not been defined.  Can't be used yet
//
//  }
//	NodeType;    ----> NodeType is defined at this point
//
//	And now, because there is no point having two different names for what is 
//	basically the same thing, we get:

struct Node;
typedef struct Node {
      int data;
      struct Node* next;
      struct Node* prev;

} Node;


#endif	//	DATA_TYPES_H
