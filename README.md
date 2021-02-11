# cpptbb
Header-only C++ Wrapper for Intel's TBB (Threading Building Blocks).

The goal of this wrapper is to encapsulate the TBB toolset into modern C++ elements, like smart pointers.

# Environment setup
`sudo apt-get install libtbb-dev`

# How To Use

## cpptbb std::shared_ptr encapsulation
In order to use TBB as a standard C++ std::shared_ptr<>, just include `cpptbb/shared_ptr.h` and call  
  
For simple classes:  
`auto ptr = cpptbb::make_shared<SomeSimpleStruct>(some, argument, list);`  
NOTE: For now we don't support elaborate classes, because we rely on temporary stack allocation and raw copy to the TBB scalabable pointer.
  
For primitive types:  
`auto ptr = cpptbb::make_shared_raw<SomePrimitiveType>(number_of_elements_to_allocate);`  
This includes `uint8_t`, `uint16_t`, etc. This mode creates a standard shared pointer allocated via TBB `scalable_malloc` with custom deleter `scalable_free`.
