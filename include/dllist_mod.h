/****************************
 * File name: dllist_mod.h
 * Authors: MMM
 * This file contains the class definition for a doubly linked list used for redo functionality
 * loosely based on dllist.h by Matthew Morrison
 **************************/

#ifndef DLLIST_MOD_H
#define DLLIST_MOD_H

#include<iostream>

template<typename T>
struct dllist_node{

	T data;
	dllist_node<T>* prev_node;
	dllist_node<T>* next_node;
	//Templated dllist 
	
	//dllist_node<T>() : data(), prev_node();
	dllist_node<T>() : data(), prev_node( NULL ), next_node( NULL ) {}
	//default constructor
	
	dllist_node<T>( const T& data_in ):
		data( data_in ), prev_node( NULL ), next_node( NULL ) {
	// this is te overloaded constructor;
		}

};
		
template< typename T > 
struct dllist{

	private:

		dllist_node<T>*head_node;
		dllist_node<T>*tail_node;
		dllist_node<T>*curr_node;

		
		void destructor( dllist_node<T>* currNode ){
			
			// Base Case - End of the List
			if( currNode == NULL )
				return;
			
			// Recursive Case - Call the next node
			destructor( currNode->next_node );
			
			// On the way back up - Delete the currNodeent node
			delete currNode;
		}

	public:
		
		dllist<T>( ): head_node( NULL ), tail_node( NULL), curr_node( NULL ) {}

		~dllist<T>() {
			if( this->empty() )
				return;

			destructor( this->head_node );
		}

		bool empty() {

			return this->head_node == NULL && this->tail_node == NULL;

		}

		T front() {
			return this->head_node->data;
		}

		T end() {
			return this->tail_node->data;
		}
		dllist_node<T>* curr() {
			return this->curr_node;
		}
		bool inc() {
			if( empty() ) return false;
			if( this->curr_node == this->tail_node ){
				return false;
			}
				this->curr_node = this->curr_node->next_node;
			return true;
		}
		bool dec() {
			if( empty() ) return false;
			if( this->curr_node == head_node ){
				return false;
			}
				this->curr_node = this->curr_node->prev_node;
			return true;
		}

		void push_curr( const T& insert_val ){

			dllist_node<T>* insert_node = new dllist_node<T> ( insert_val );

			if( this->empty() ){
				this->head_node = insert_node;
				this->tail_node = insert_node;
				this->curr_node = insert_node;
			
				return;
			}


			dllist_node<T>* reference = this->curr_node;
			
		 	this->curr_node = insert_node;
			this->curr_node->prev_node = reference;
			this->curr_node->next_node = reference->next_node;

			this->curr_node->prev_node->next_node = this->curr_node;
			
			destructor( this->curr_node->next_node);
			this->curr_node->next_node = NULL;
			this->tail_node = this->curr_node;
			return;
			
			
		}
};


#endif

