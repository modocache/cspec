
# CSpec

  BDD test framework for the C programming language.

## Todo

  * fix nesting
  * fix expression ... tries to convert it "should foo" into an assertion
  * refactor messy parser and lame buffering
  
## Installation

     $ make
     $ make install
  
## Usage

    $ cspec --help
    $ cspec < spec/foo_spec.c > spec/foo.c

## Example CSpec

The following example uses the CSpec grammar, which is compiled to 
the literal C code below it.

    #include "cspec.h"
    
    static int nbefore_each;
    
    describe "CSpec before_each"
      before_each
        ++nbefore_each;
      end
      
      it "should be called before each spec"
        nbefore_each should equal 1
      end
      
      it "should be called before each spec"
       nbefore_each should equal 2
      end
    end

## Literal C
  
    #include "cspec.h"
    
    static int nbefore_each;
    
    void block_0_callback() {
      ++nbefore_each;
    }
    
    void block_1_callback() {
      expect((match_equal(nbefore_each,  1)));
    }
    
    void block_2_callback() {
      expect((match_equal(nbefore_each,  2)));
    }
    
    int main() {
      Suite *suite_0 = Suite_new("CSpec before_each");
      Block *block_0 = Block_new(blockTypeBeforeEach, NULL, &block_0_callback);
      Block *block_1 = Block_new(blockTypeSpec, "should be called before each spec", &block_1_callback);
      Block *block_2 = Block_new(blockTypeSpec, "should be called before each spec", &block_2_callback);
      Suite_push_block(suite_0, block_0);
      Suite_push_block(suite_0, block_1);
      Suite_push_block(suite_0, block_2);
      Suite_run(suite_0);
      CSpec_stats();
      return 0;
    }

## Output

Below is example stdout with a failed assertion.

    CSpec before
      should be called before each suite .
      should not be called before each spec .
    
    CSpec after
      should be called after each suite .
      should not be called after each spec .
    
    CSpec before_each
      should be called before each spec .
      should be called before each spec .
        failed:
          (match_equal(nbefore_each, 1))
    
    CSpec after_each
      should be called after each spec .
      should be called after each spec .
      
    Passes: 8 Failures: 0
  
## Core Matchers

    - be, equal, point_to
    
      foo should be NULL;
      foo should point_to bar;
      str should equal "foo";
      
    - include
    
      "foobar" should include "foo";
      "foobar" should include "bar";
      
    - start_with
    
      "foobar" should start_with "foo";
      "foobar" should not start_with "bar";
      
## Example Matcher Definitions

    #define match_be(A, E) (A == E)
    #define match_equal(A, E) (A == E)
    #define match_point_to(A, E) (A == E)
    #define match_include(A, E) (strstr(A, E))
    #define match_start_with(A, E) (strstr(A, E) == A)
      
## More Information

  * [Example Spec from YAMP](http://gist.github.com/246057)
  
## License 

(The MIT License)

Copyright (c) 2008 - 2009 TJ Holowaychuk &lt;tj@vision-media.ca&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

