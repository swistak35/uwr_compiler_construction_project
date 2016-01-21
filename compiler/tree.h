

#ifndef TREE_INCLUDED
#define TREE_INCLUDED  1


#include <iostream>
#include <vector>
#include <string>

class tree;


// Possible values of a node:

struct nodevalue
{
   virtual void print( std::ostream& out ) const = 0;
   virtual ~nodevalue( ) { }
};


struct stringvalue : public nodevalue
{
   std::string s;

   stringvalue( const std::string& s )
      : s{s}
   { }

   stringvalue( std::string&& s )
      : s{ std::move(s) }
   { }

   void print( std::ostream& out ) const override
      { out << "string: " << s; }
};


struct doublevalue : public nodevalue
{
   double d;

   doublevalue( double d )
      : d{d}
   { }

   void print( std::ostream& out ) const override
      { out << "double: " << d; }
};


// struct trnode should be invisible to the user of tree. This can be
// obtained by making it a private number of tree.
// In this exercise, we leave it like this, because it is simpler.
// In real code, trnode should be defined inside tree.


struct trnode
{
   const nodevalue* val;
   std::vector< tree > subtrees;

   size_t refcnt;
      // The reference counter: Counts how often this trnode is referred to.

   trnode( const std::string& f, const std::vector< tree > & subtrees )
      : val{ new stringvalue(f) },
        subtrees{ subtrees },
        refcnt{1}
   { }

   trnode( const std::string& f, std::vector< tree > && subtrees )
      : val{ new stringvalue(f) },
        subtrees{ std::move( subtrees )},
        refcnt{1}
   { }

   trnode( double d, const std::vector< tree > & subtrees )
      : val{ new doublevalue(d) },
        subtrees{ subtrees },
        refcnt{1}
   { }

   trnode( double d, std::vector< tree > && subtrees )
      : val{ new doublevalue(d) },
        subtrees{ std::move( subtrees )},
        refcnt{1}
   { }


   trnode( ) = delete;
   void operator = ( const trnode& ) = delete;
   trnode( const trnode& ) = delete;

   ~trnode( ) { delete val; }

};


struct tree
{
   trnode* pntr;

public:
   tree( const char* c, const std::vector< tree > & subtrees )
      : pntr( new trnode( std::string(c), subtrees ))
   { }

   tree( const char* c, std::vector< tree > && subtrees = { } )
      : pntr( new trnode( std::string(c), std::move( subtrees ) ))
   { }

   tree( const std::string& f, const std::vector< tree > & subtrees )
      : pntr( new trnode( f, subtrees ))
   { }

   tree( const std::string& f, std::vector< tree > && subtrees = { } )
      : pntr( new trnode( f, std::move( subtrees ) ))
   { }

   tree( double d, const std::vector< tree > & subtrees )
      : pntr( new trnode( d, subtrees ))
   { }

   tree( double d, std::vector< tree > && subtrees = { } )
      : pntr( new trnode( d, std::move( subtrees ) ))
   { }


   tree( const tree& t )
      : pntr{ t. pntr }
   {
      ++ ( pntr -> refcnt );
   }

   void operator = ( tree&& t ) { std::swap( pntr, t. pntr ); }
   void operator = ( const tree& t ) { (*this) = tree( t ); }

   bool hasstring( ) const { return dynamic_cast< const stringvalue* > ( pntr -> val ); }
   bool hasdouble( ) const { return dynamic_cast< const doublevalue* > ( pntr -> val ); }

   const std::string& getstring( ) const
      { return ( dynamic_cast< const stringvalue* > ( pntr -> val ) ) -> s; }
   double getdouble( ) const
      { return ( dynamic_cast< const doublevalue* > ( pntr -> val ) ) -> d; }

   const tree& operator [] ( size_t i ) const { return pntr -> subtrees[i]; }
   size_t nrsubtrees( ) const { return pntr -> subtrees. size( ); }


   ~tree( )
   {
      -- ( pntr -> refcnt );
      if( ( pntr -> refcnt ) == 0 )
         delete pntr;
   }

   void printnode( std::ostream& out ) const
   {
      pntr -> val -> print( out );
   }

};

std::ostream& operator << ( std::ostream& stream, const tree& t );
   // Doesn't need to be friend, because it uses only functor( ),
   // nrsubtrees( ) and [ ].


#endif

