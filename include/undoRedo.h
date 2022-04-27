// Filename: printTxt.h
// Authors: Matty's Merry Militia
// This file will contain the function declarations for printTxt.cpp



#ifndef undoRedo_H
#define undoRedo_H

#include "dllist_mod.h"

struct Line{
	public:
		unsigned int row;
		STRING data;

		Line( ): row( 0 ), data( "" ) { }
		Line( unsigned int rowIn, STRING dataIn ): row( rowIn ), data( dataIn ) { }
		~Line( ) { } 

};

class undoRedo {

	private:
		dllist< Line > list;
		bool clean;

	public:
		
		undoRedo( ): list( ), clean( true ) { }
		~undoRedo( ) { }
		
		bool checkClean( ) const {
			return clean;
		}

		void addNode( unsigned int row, STRING data ) {
			Line insert( row, data );
			list.push_curr( insert );
		}

		bool getData( Line& editLine ) {
			dllist_node< Line >* node = list.curr();
			if (node == NULL)
				return false;
			editLine = node->data;
			return true;
		}

		bool prevNode( ) {
			return list.dec();
		}

		bool nextNode( ) {
			return list.inc();
		}

		void makeClean( ) {
			clean = true;
		}

		void makeDirty( ) {
			clean = false;
		}

};


#endif 
