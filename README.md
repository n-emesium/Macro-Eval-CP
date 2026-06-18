cpp(c preprocessor)--:

This is a macro evaluation tool for a non GNU compliant preprocessor.
It is not complete and only supports simple logic such as ## for definition and !! for inclusion.
It maintains a hash table for efficient lookup and tries not to rely on the standard library functions as much as possible.
It is memory efficient and will run on a small memory footprint.

The reason it is called cpp-- instead of cpp is simply because it does not support the full range of conditional logic that is provided by the GNU cpp, it was created in order to assist with writing assembly code by using and reusing custom replacements or text insertions.

This project is continously being updated and maintained only by me, so if you find bugs please report them.

--EGE
